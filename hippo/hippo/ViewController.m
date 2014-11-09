//
//  ViewController.m
//  hippo
//
//  Created by FanFamily on 14-10-10.
//  Copyright (c) 2014年 familymrfan. All rights reserved.
//

#import "ViewController.h"
#import "DataBaseManager.h"
#import "CDRTranslucentSideBar.h"
#import "UIViewController+ScrollingNavbar.h"
#import "AccountBook.h"

@interface ViewController () <CDRTranslucentSideBarDelegate, UITableViewDataSource, UITableViewDelegate>

@property (nonatomic) CDRTranslucentSideBar *sideBar;
@property (weak, nonatomic) IBOutlet UITableView *bookTable;
@property (strong, nonatomic) NSMutableDictionary* data;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.sideBar = [[CDRTranslucentSideBar alloc] init];
    self.sideBar.sideBarWidth = 50;
    self.sideBar.translucentAlpha = 0.2f;
    self.sideBar.translucentTintColor = [UIColor blackColor];
    self.sideBar.delegate = self;
    self.sideBar.tag = 0;
    
    // Add PanGesture to Show SideBar by PanGesture
    // UIPanGestureRecognizer *panGestureRecognizer = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(handlePanGesture:)];
    // [self.view addGestureRecognizer:panGestureRecognizer];
    
    
    //if ([self respondsToSelector:@selector(setEdgesForExtendedLayout:)]) {
    //    self.edgesForExtendedLayout = UIRectEdgeNone;
    //}
    
    // self.navigationItem.titleView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"nav"]];
    
    // Just call this line to enable the scrolling navbar
    //[self followScrollView:self.bookTable withDelay:65];
    //[self setShouldScrollWhenContentFits:YES];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Gesture Handler
- (void)handlePanGesture:(UIPanGestureRecognizer *)recognizer {
    self.sideBar.isCurrentPanGestureTarget = YES;
    [self.sideBar handlePanGestureToShow:recognizer inView:self.view];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    
}

- (void)viewWillAppear:(BOOL)animated
{
    NSMutableDictionary* data = [NSMutableDictionary dictionary];
    NSArray* abs = [[DataBaseManager sharedInstace] getEntity:[AccountBook new] otherCondition:@"order by date" withParam:nil];
    [abs enumerateObjectsUsingBlock:^(AccountBook* obj, NSUInteger idx, BOOL *stop) {
        NSDateComponents *components = [[NSCalendar currentCalendar] components:NSCalendarUnitMonth fromDate:obj.date];
        NSMutableArray* absMonth = [data objectForKey:@(components.month)];
        if (absMonth == nil) {
            absMonth = [NSMutableArray array];
            [data setObject:absMonth forKey:@(components.month)];
        }
        [absMonth addObject:obj];
    }];
    self.data = data;
    [self.bookTable reloadData];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [self showNavBarAnimated:NO];
}

- (void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];
    [self showNavBarAnimated:NO];
}

- (void)searchBarTextDidEndEditing:(UISearchBar *)searchBar
{
    // Call this after a small delay, or it won't work
    [self performSelector:@selector(showNavbar) withObject:nil afterDelay:0.2];
}

- (BOOL)scrollViewShouldScrollToTop:(UIScrollView *)scrollView
{
    // This enables the user to scroll down the navbar by tapping the status bar.
    //	[self performSelector:@selector(showNavbar) withObject:nil afterDelay:0.1];  // Use a delay if needed (pre iOS8)
    [self showNavbar];
    return YES;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation
{
    return YES;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return self.data.allKeys.count;
}

- (NSNumber *)monthInSection:(NSInteger)section
{
    NSArray* keysInSort = [self.data.allKeys sortedArrayUsingComparator:^NSComparisonResult(NSNumber* obj1, NSNumber* obj2) {
        return [obj1 compare:obj2];
    }];
    return [keysInSort objectAtIndex:section];
}

- (NSMutableArray *)accountBooksInSection:(NSInteger)section
{
    return [self.data objectForKey:[self monthInSection:section]];
}

- (NSString*)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    return [NSString stringWithFormat:@"%@ 月", [self monthInSection:section]];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [self accountBooksInSection:section].count;
}

- (UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell* cell = [tableView dequeueReusableCellWithIdentifier:@"Identifier"];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"Identifier"];
    }
    
    AccountBook* ab = [[self accountBooksInSection:indexPath.section] objectAtIndex:indexPath.row];
    
    NSDateComponents *components = [[NSCalendar currentCalendar] components:NSCalendarUnitDay|NSCalendarUnitHour|NSCalendarUnitMinute fromDate:ab.date];
    
    cell.textLabel.text = [NSString stringWithFormat:@"%@ %@      %@日%@:%@", ab.money, ab.inOrOut.boolValue ? @"收入":@"支出", @(components.day), @(components.hour), @(components.minute)];
    
    return cell;
}

- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    return YES;
}

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        NSMutableArray* abs = [self accountBooksInSection:indexPath.section];
        AccountBook* ab = [abs objectAtIndex:indexPath.row];
        [ab remove];
        [abs removeObject:ab];
        if (abs.count == 0) {
            [self.data removeObjectForKey:@(indexPath.section)];
        }
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
    }
}

@end
