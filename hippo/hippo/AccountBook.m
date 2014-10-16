//
//  AccountBook.m
//  hippo
//
//  Created by FanFamily on 14-10-16.
//  Copyright (c) 2014年 familymrfan. All rights reserved.
//

#import "AccountBook.h"

@implementation AccountBook

- (instancetype)init
{
    self = [super init];
    if (self) {
        [self.keyname2fieldExtension setObject:@"INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL" forKey:@"rowId"];
    }
    return self;
}

@end
