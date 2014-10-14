//
//  Entity.m
//  hippo
//
//  Created by familymrfan on 14-10-14.
//  Copyright (c) 2014年 familymrfan. All rights reserved.
//

#import "Entity.h"
#import <objc/runtime.h>

@interface Entity ()

@end

@implementation Entity

- (instancetype)init
{
    self = [super init];
    if (self) {
        self.keyname2fieldExtension = [NSMutableDictionary dictionary];
    }
    return self;
}

-(NSDictionary *)keyname2Value
{
    NSMutableDictionary *dict = [NSMutableDictionary dictionary];
    unsigned int outCount;
    objc_property_t *props = class_copyPropertyList([self class], &outCount);
    for(int i=0; i<outCount; i++){
        objc_property_t prop = props[i];
        NSString *propName = [[NSString alloc]initWithCString:property_getName(prop) encoding:NSUTF8StringEncoding];
        id propValue = [self valueForKey:propName];
        if(propValue){
            [dict setObject:propValue forKey:propName];
        }
    }
    free(props);
    return dict;
}

-(NSDictionary *)keyname2Type
{
    NSMutableDictionary *dict = [NSMutableDictionary dictionary];
    unsigned int outCount;
    objc_property_t *props = class_copyPropertyList([self class], &outCount);
    for(int i=0; i<outCount; i++){
        objc_property_t prop = props[i];
        NSString* propName = [[NSString alloc]initWithCString:property_getName(prop) encoding:NSUTF8StringEncoding];
        NSString* propAttribute = [[NSString alloc]initWithCString:property_getAttributes(prop) encoding:NSUTF8StringEncoding];
        NSRange rangeBegin = [propAttribute rangeOfString:@"T@\""];
        NSRange rangeEnd   = [propAttribute rangeOfString:@"\"" options:NSBackwardsSearch];
        NSString* propType = [propAttribute substringWithRange:NSMakeRange(rangeBegin.location + rangeBegin.length, rangeEnd.location - rangeBegin.location - rangeBegin.length)];
        if (propName && propType) {
            [dict setObject:propType forKey:propName];
        }
    }
    free(props);
    return dict;
}

- (NSString *)description
{
    return [NSString stringWithFormat:@"%@:%@", [[self class] description], self.keyname2Value];
}

@end
