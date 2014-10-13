//
//  PathProvider.h
//  hippo
//
//  Created by familymrfan on 14-10-13.
//  Copyright (c) 2014年 familymrfan. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PathProvider : NSObject

+ (NSString*)documentDirectory;

+ (NSString *)tmpDirectory;

@end
