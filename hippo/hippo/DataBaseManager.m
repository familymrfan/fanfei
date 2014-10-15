//
//  DataBaseManager.m
//  hippo
//
//  Created by familymrfan on 14-10-13.
//  Copyright (c) 2014年 familymrfan. All rights reserved.
//

#import "DataBaseManager.h"
#import "PathProvider.h"
#import "FMDatabase.h"
#import "Entity.h"

@interface DataBaseManager ()

@property (nonatomic) NSMutableDictionary* dbName2Db;
@property (nonatomic) NSDictionary* fieldMap;
@property (nonatomic) NSString* currentDbName;
@property (nonatomic) NSDictionary* tbName2DbLock;

@end

@implementation DataBaseManager

+ (instancetype)sharedInstace
{
    static DataBaseManager* dbm = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        dbm = [[DataBaseManager alloc] init];
    });
    return dbm;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        self.dbName2Db = [NSMutableDictionary dictionary];
        self.tbName2DbLock = [NSMutableDictionary dictionary];
        self.fieldMap = @{@"NSString":@"TEXT", @"NSNumber":@"INTEGER", @"NSData":@"BLOB"};
    }
    return self;
}

- (BOOL)createDateBase:(NSString *)dbName path:(NSString *)path
{
    if (path == nil) {
        path = [PathProvider documentDirectory];
    }
    NSString* fullPath = [path stringByAppendingPathComponent:dbName];
    NSLog(@"database %@ full path is %@", dbName, fullPath);
    FMDatabase* dataBase = [FMDatabase databaseWithPath:fullPath];
    if (dataBase && [dataBase open]) {
       [self.dbName2Db setObject:dataBase forKey:dbName];
        self.currentDbName = dbName;
    } else {
        NSLog(@"create database %@ failed", dbName);
        return NO;
    }
    return YES;
}

- (NSString *)objectType2SqlType:(NSString *)objectType
{
    NSString* sqlType = [self.fieldMap objectForKey:objectType];
    if (sqlType) {
        return sqlType;
    }
    return @"BLOB";
}

- (BOOL)createTableByEntity:(Entity *)entity
{
    FMDatabase* dataBase = [self.dbName2Db objectForKey:self.currentDbName];
    if (dataBase == nil) {
        return NO;
    }
    // 为每个表分配一个锁，保证同一时刻只有一个操作
    NSLock* lock = [[NSLock alloc] init];
    [self.tbName2DbLock setValue:lock forKey:entity.tablename];
    NSDictionary* keyname2type = [entity keyname2Type];
    NSMutableString* sql = [NSMutableString stringWithFormat:@"CREATE TABLE IF NOT EXISTS %@(", entity.tablename];
    [keyname2type enumerateKeysAndObjectsUsingBlock:^(NSString* key, NSString* type, BOOL *stop) {
        NSString* feildProperty = [entity.keyname2fieldExtension objectForKey:key];
        if (feildProperty == nil) {
            feildProperty = [self objectType2SqlType:type];
        }
        NSString* feild = [NSString stringWithFormat:@"%@ %@,", key, feildProperty];
        [sql appendString:feild];
    }];
    [sql deleteCharactersInRange:NSMakeRange(sql.length-1, 1)];
    [sql appendString:@")"];
    BOOL success = [dataBase executeUpdate:sql];
    NSError *error = [dataBase lastError];
    if (error) {
        NSLog(@"create table %@ failed, error is %@", entity.tablename, error);
    }
    return success;
}

- (NSLock *)lockForEntity:(Entity *)entity
{
    return [self.tbName2DbLock objectForKey:entity.tablename];
}

- (NSNumber *)saveByEntity:(Entity *)entity
{
    NSNumber* rowId = nil;
    FMDatabase* dataBase = [self.dbName2Db objectForKey:self.currentDbName];
    if (dataBase == nil) {
        return nil;
    }
    
    NSLock* lock = [self lockForEntity:entity];
    [lock lock];
    NSMutableArray* marks = [NSMutableArray arrayWithCapacity:[entity.keyname2Value.allKeys count]];
    for (__unused NSString* key in entity.keyname2Value.allKeys) {
        [marks addObject:@"?"];
    }
    NSString* sql = [NSString stringWithFormat:@"REPLACE INTO %@ (%@) VALUES (%@)", entity.class, [entity.keyname2Value.allKeys componentsJoinedByString:@", "],  [marks componentsJoinedByString:@", "]];
    BOOL success = [dataBase executeUpdate:sql withArgumentsInArray:entity.keyname2Value.allValues];
    NSError *error = [dataBase lastError];
    if (!success) {
        NSLog(@"saveByEntity %@ failed, entity is %@, error is %@", entity.tablename, entity, error);
    } else {
        if (entity.rowId == nil) {
            rowId = [NSNumber numberWithLongLong:[dataBase lastInsertRowId]];
        }
    }
    [lock unlock];
    return rowId;
}

// todo keyname array
- (NSArray *)getEntity:(Entity *)entity otherCondition:(NSString *)condition withParam:(NSArray*)param
{
    FMDatabase* dataBase = [self.dbName2Db objectForKey:self.currentDbName];
    if (dataBase == nil) {
        return nil;
    }
    if ([entity rowId] == nil && condition == nil) {
        return nil;
    }
    NSLock* lock = [self lockForEntity:entity];
    [lock lock];
    NSString* sql = nil;
    if (entity.rowId) {
        sql = [NSString stringWithFormat:@"SELECT * FROM %@ WHERE %@ = ?", entity.tablename, entity.keyname];
        param = @[entity.rowId];
    } else {
        sql = [NSString stringWithFormat:@"SELECT * FROM %@", entity.tablename];
    }
    if (condition != nil) {
        sql = [sql stringByAppendingFormat:@" %@", condition];
    }
    FMResultSet* queryResult = [dataBase executeQuery:sql withArgumentsInArray:param];
    if (queryResult == nil) {
        NSLog(@"getEntity %@ failed, entity is %@, error is %@", entity.tablename, entity, dataBase.lastError);
    }
    NSMutableArray* entitys = [NSMutableArray array];
    while (queryResult.next) {
        Entity* newEntity = [entity deepCopy];
        [entity.keys enumerateObjectsUsingBlock:^(NSString* keyname, NSUInteger idx, BOOL *stop) {
            [newEntity setValue:[queryResult objectForColumnName:keyname] forKey:keyname];
        }];
        [entitys addObject:newEntity];
    }
    [lock unlock];
    return entitys;
}

- (Entity *)getEntity:(Entity *)entity
{
    return [self getEntity:entity otherCondition:nil withParam:nil].firstObject;
}

- (BOOL)remove:(Entity *)entity
{
    FMDatabase* dataBase = [self.dbName2Db objectForKey:self.currentDbName];
    if (dataBase == nil) {
        return nil;
    }
    if ([entity rowId] == nil) {
        return nil;
    }
    NSLock* lock = [self lockForEntity:entity];
    [lock lock];
    NSString* sql = [NSString stringWithFormat:@"DELETE FROM %@ WHERE %@ = ?", entity.tablename, entity.keyname];
    BOOL success = [dataBase executeUpdate:sql withArgumentsInArray:@[entity.rowId]];
    NSError *error = [dataBase lastError];
    if (!success) {
        NSLog(@"remove %@ failed, entity is %@, error is %@", entity.tablename, entity, error);
    }
    [lock unlock];
    return success;
}

- (void)setCurrentDB:(NSString *)dbName
{
    self.currentDbName = dbName;
}

@end
