//
//  AccountBook.h
//  hippo
//
//  Created by FanFamily on 14-10-16.
//  Copyright (c) 2014年 familymrfan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Entity.h"

@interface AccountBook : Entity

@property (nonatomic) NSNumber* rowId;
@property (nonatomic) NSNumber* inOrOut;
@property (nonatomic) NSString* money;
@property (nonatomic) NSString* use;
@property (nonatomic) NSDate* date;

- (NSInteger)income;

@end
