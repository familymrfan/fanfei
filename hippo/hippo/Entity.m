//
//  Entity.m
//  hippo
//
//  Created by familymrfan on 14-10-14.
//  Copyright (c) 2014年 familymrfan. All rights reserved.
//

#import "Entity.h"
#import <objc/runtime.h>
#import "DataBaseManager.h"

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

- (id)rowId
{
    if ([self.keys count] == 0) {
        return nil;
    }
    return [self valueForKey:self.keyname];
}

- (NSString *)keyname
{
    return [self.keys firstObject];
}

-(NSArray *)keys
{
    NSMutableArray* result = [NSMutableArray array];
    unsigned int outCount;
    objc_property_t *props = class_copyPropertyList([self class], &outCount);
    for(int i=0; i<outCount; i++){
        objc_property_t prop = props[i];
        NSString *propName = [[NSString alloc]initWithCString:property_getName(prop) encoding:NSUTF8StringEncoding];
        [result addObject:propName];
    }
    return result;
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

- (NSString *)tablename
{
    return NSStringFromClass([self class]);
}

- (NSString *)description
{
    return [NSString stringWithFormat:@"%@:%@", self.tablename, self.keyname2Value];
}

- (id)initWithCoder:(NSCoder *)aDecoder
{
    self = [super init];
    if (self != nil) {
        for (NSString* propertyName in [self keys]) {
            if ([propertyName isEqualToString:@"superclass"]
                || [propertyName isEqualToString:@"hash"]
                || [propertyName isEqualToString:@"description"]
                || [propertyName isEqualToString:@"debugDescription"]) {
                continue;
            }
            id value = [aDecoder decodeObjectForKey:propertyName];
            [self setValue:value forKey:propertyName];
        }
    }
    return self;
}

- (void)encodeWithCoder:(NSCoder *)aCoder
{
    for (NSString* propertyName in [self keys]) {
        if ([propertyName isEqualToString:@"superclass"]
            || [propertyName isEqualToString:@"hash"]
            || [propertyName isEqualToString:@"description"]
            || [propertyName isEqualToString:@"debugDescription"]) {
            continue;
        }
        
        id value = [self valueForKey:propertyName];
        [aCoder encodeObject:value forKey:propertyName];
    }
}

- (instancetype)deepCopy
{
    return [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject:self]];
}

- (NSNumber *)save
{
    return [[DataBaseManager sharedInstace] saveByEntity:self];
}

- (Entity *)getEntity
{
    return [[DataBaseManager sharedInstace] getEntity:self];
}

- (NSArray *)getEntity:(NSString *)condition withParam:(NSArray*)param
{
    return [[DataBaseManager sharedInstace] getEntity:self otherCondition:condition withParam:param];
}

@end
