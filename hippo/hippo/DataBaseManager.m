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

@interface DataBaseManager ()

@property (nonatomic) NSMutableDictionary* dbName2Db;

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
    }
    return self;
}

- (BOOL)createDateBase:(NSString *)dbName path:(NSString *)path;
{
    if (path == nil) {
        path = [PathProvider documentDirectory];
    }
    NSString* fullPath = [path stringByAppendingPathComponent:dbName];
    NSLog(@"database %@ full path is %@", dbName, fullPath);
    FMDatabase* dataBase = [FMDatabase databaseWithPath:fullPath];
    if (dataBase && [dataBase open]) {
       [self.dbName2Db setObject:dataBase forKey:dbName];
    } else {
        NSLog(@"create database %@ failed", dbName);
        return NO;
    }
    return YES;
}

@end
