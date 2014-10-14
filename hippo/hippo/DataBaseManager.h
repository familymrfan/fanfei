//
//  DataBaseManager.h
//  hippo
//
//  Created by familymrfan on 14-10-13.
//  Copyright (c) 2014年 familymrfan. All rights reserved.
//

#import <Foundation/Foundation.h>

@class Entity;
@interface DataBaseManager : NSObject

+ (instancetype)sharedInstace;

// 创建数据库, path 为 nil 默认为document
- (BOOL)createDateBase:(NSString *)dbName path:(NSString *)path;

// 创建表
- (BOOL)createTableByEntity:(Entity *)entity;

// 设置当前的数据库
- (void)setCurrentDB:(NSString *)dbName;

@end
