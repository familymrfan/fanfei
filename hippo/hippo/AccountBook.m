//
//  AccountBook.m
//  hippo
//
//  Created by FanFamily on 14-10-16.
//  Copyright (c) 2014年 familymrfan. All rights reserved.
//

#import "AccountBook.h"
#import "DataBaseManager.h"
#import "FMDatabase.h"

@implementation AccountBook

- (instancetype)init
{
    self = [super init];
    if (self) {
        [self.keyname2fieldExtension setObject:@"INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL" forKey:@"rowId"];
    }
    return self;
}

- (NSInteger)income
{
    FMDatabase* db = [[DataBaseManager sharedInstace] currentDB];
    NSString* sqlOutMoney = @"select sum(money) from AccountBook where inOrOut = 0";
    NSString* sqlInMoney = @"select sum(money) from AccountBook where inOrOut = 1";
    FMResultSet* resultSet = [db executeQuery:sqlOutMoney];
    if (resultSet == nil) {
        NSLog(@"%s %@", __func__, db.lastError);
        return 0;
    }
    [resultSet next];
    NSNumber* out = [resultSet objectForColumnIndex:0];
    if (![out isKindOfClass:[NSNumber class]]) {
        out = @0;
    }
    resultSet = [db executeQuery:sqlInMoney];
    if (resultSet == nil) {
        NSLog(@"%s %@", __func__, db.lastError);
        return 0;
    }
    [resultSet next];
    NSNumber* in = [resultSet objectForColumnIndex:0];
    if (![in isKindOfClass:[NSNumber class]]) {
        in = @0;
    }
    return in.integerValue - out.integerValue;
}

@end
