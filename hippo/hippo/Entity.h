//
//  Entity.h
//  hippo
//
//  Created by familymrfan on 14-10-14.
//  Copyright (c) 2014年 familymrfan. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Entity : NSObject<NSCoding>

@property (nonatomic) NSMutableDictionary* keyname2fieldExtension;

- (id)rowId;
- (NSString *)keyname;
- (NSArray *)keys;
- (NSDictionary *)keyname2Value;
- (NSDictionary *)keyname2Type;
- (NSString *)name;

// 数据库同步操作接口
- (NSNumber *)save;

// 深复制本对象, 效率较低, 需要实现NSCoding
- (instancetype)deepCopy;

@end
