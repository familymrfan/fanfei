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

@interface ViewController () <CDRTranslucentSideBarDelegate, UITableViewDataSource, UITableViewDelegate>

@property (nonatomic) CDRTranslucentSideBar *sideBar;
@property (weak, nonatomic) IBOutlet UITableView *bookTable;
@property (strong, nonatomic) NSArray* data;

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
    UIPanGestureRecognizer *panGestureRecognizer = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(handlePanGesture:)];
    [self.view addGestureRecognizer:panGestureRecognizer];
    
    self.data = @[@"Awesome content", @"Great content", @"Amazing content", @"Ludicrous content", @"Awesome content", @"Great content", @"Amazing content", @"Ludicrous content", @"Awesome content", @"Great content", @"Amazing content", @"Ludicrous content", @"Awesome content", @"Great content", @"Amazing content", @"Ludicrous content"];
    
    if ([self respondsToSelector:@selector(setEdgesForExtendedLayout:)]) {
        self.edgesForExtendedLayout = UIRectEdgeNone;
    }
    // self.navigationItem.titleView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"nav"]];
    
    // Just call this line to enable the scrolling navbar
    [self followScrollView:self.bookTable withDelay:65];
    [self setShouldScrollWhenContentFits:YES];
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

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [self.data count];
}

- (UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell* cell = [tableView dequeueReusableCellWithIdentifier:@"Identifier"];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"Identifier"];
    }
    
    cell.textLabel.text = self.data[indexPath.row];
    
    return cell;
}

@end
