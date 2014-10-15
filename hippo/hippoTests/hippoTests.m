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

@interface Hippo : Entity

@property (nonatomic) NSNumber* rowId;
@property (nonatomic) NSString* name;
@property (nonatomic) NSNumber* size;

@end

@implementation Hippo

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
    Hippo* h = [[Hippo alloc] init];
    h.name = @"小白";
    h.size = @100;
    [h.keyname2fieldExtension setObject:@"INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL" forKey:@"rowId"];
    NSLog(@"keyname2Value %@", [h keyname2Type]);
    NSLog(@"test a description %@", [h description]);
    [[DataBaseManager sharedInstace] createDateBase:@"hippo.db" path:nil];
    [[DataBaseManager sharedInstace] createTableByEntity:h];
    h.rowId = [h save];
    h.name = @"小新";
    h.size = @200;
    [h save];
    Hippo* h1 = [h getEntity];
    NSLog(@"h1 %@", h1);
    [h1 remove];
    h1 = [h1 getEntity];
    NSLog(@"h1 %@", h1);
}

@end
