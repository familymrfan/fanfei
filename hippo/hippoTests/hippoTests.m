//
//  hippoTests.m
//  hippoTests
//
//  Created by FanFamily on 14-10-10.
//  Copyright (c) 2014年 familymrfan. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <XCTest/XCTest.h>
#import "Entity.h"
#import "DataBaseManager.h"

@interface TestA : Entity
@property (nonatomic) NSNumber* rowId;
@property (nonatomic) NSString* a1;
@property (nonatomic) NSNumber* a2;
@property (nonatomic) NSData* a3;

@end

@implementation TestA

@end

@interface hippoTests : XCTestCase

@end

@implementation hippoTests

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testExample {
    TestA* a = [[TestA alloc] init];
    [a.keyname2fieldExtension setObject:@"INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL" forKey:@"rowId"];
    NSLog(@"keyname2Value %@", [a keyname2Type]);
    [[DataBaseManager sharedInstace] createDateBase:@"hippo.db" path:nil];
    [[DataBaseManager sharedInstace] createTableByEntity:a];
}

@end
