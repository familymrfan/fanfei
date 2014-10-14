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
    NSDictionary* keyname2type = [entity keyname2Type];
    NSMutableString* sql = [NSMutableString stringWithFormat:@"CREATE TABLE IF NOT EXISTS %@(", [[entity class] description]];
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
        NSLog(@"create table %@ failed, error is %@", NSStringFromClass([entity class]), error);
    }
    return success;
}

- (NSNumber *)saveByEntity:(Entity *)entity
{
    NSNumber* rowId = nil;
    FMDatabase* dataBase = [self.dbName2Db objectForKey:self.currentDbName];
    if (dataBase == nil) {
        return rowId;
    }
    NSMutableArray* marks = [NSMutableArray arrayWithCapacity:[entity.keyname2Value.allKeys count]];
    for (__unused NSString* key in entity.keyname2Value.allKeys) {
        [marks addObject:@"?"];
    }
    NSString* sql = [NSString stringWithFormat:@"REPLACE INTO %@ (%@) VALUES (%@)", entity.class, [entity.keyname2Value.allKeys componentsJoinedByString:@", "],  [marks componentsJoinedByString:@", "]];
    BOOL success = [dataBase executeUpdate:sql withArgumentsInArray:entity.keyname2Value.allValues];
    NSError *error = [dataBase lastError];
    if (!success) {
        NSLog(@"saveByEntity %@ failed, error is %@", NSStringFromClass([entity class]), error);
    } else {
        if (entity.rowId == nil) {
            rowId = [NSNumber numberWithLongLong:[dataBase lastInsertRowId]];
        }
    }
    return rowId;
}

- (void)setCurrentDB:(NSString *)dbName
{
    self.currentDbName = dbName;
}

@end
