//
//  Entity.h
//  hippo
//
//  Created by familymrfan on 14-10-14.
//  Copyright (c) 2014年 familymrfan. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Entity : NSObject

- (NSDictionary *)keyname2Value;
- (NSDictionary *)keyname2Type;

@property (nonatomic) NSMutableDictionary* keyname2fieldExtension;

@end
