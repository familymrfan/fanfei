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
- (NSString *)tablename;

- (instancetype)deepCopy;

// 数据库同步操作接口
- (NSNumber *)save;
// 查询接口
- (id)getEntity;
- (NSArray *)getEntity:(NSString *)condition withParam:(NSArray*)param;
// 删除
- (BOOL)remove;

@end
