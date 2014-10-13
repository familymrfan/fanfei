//
//  PathProvider.m
//  hippo
//
//  Created by familymrfan on 14-10-13.
//  Copyright (c) 2014年 familymrfan. All rights reserved.
//

#import "PathProvider.h"

@implementation PathProvider

+ (NSString *)documentDirectory
{
    return NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0];
}

+ (NSString *)tmpDirectory
{
    return NSTemporaryDirectory();
}

@end
