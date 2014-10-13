//
//  DataBaseManager.h
//  hippo
//
//  Created by familymrfan on 14-10-13.
//  Copyright (c) 2014年 familymrfan. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DataBaseManager : NSObject

+ (instancetype)sharedInstace;

// 创建数据库, path 为 nil 默认为document
- (BOOL)createDateBase:(NSString *)dbName path:(NSString *)path;

@end
