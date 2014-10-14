//
//  Entity.h
//  hippo
//
//  Created by familymrfan on 14-10-14.
//  Copyright (c) 2014年 familymrfan. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Entity : NSObject

@property (nonatomic) NSMutableDictionary* keyname2fieldExtension;

- (id)rowId;
- (NSArray *)keys;
- (NSDictionary *)keyname2Value;
- (NSDictionary *)keyname2Type;

// 数据库同步操作接口
- (NSNumber *)save;

@end
