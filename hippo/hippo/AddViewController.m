//
//  AddViewController.m
//  hippo
//
//  Created by FanFamily on 14-10-26.
//  Copyright (c) 2014年 familymrfan. All rights reserved.
//

#import "AddViewController.h"
#import "AccountBook.h"

@interface AddViewController ()

@property (weak, nonatomic) IBOutlet UISwitch *switchInOrOut;
@property (weak, nonatomic) IBOutlet UITextField *txtMoney;
@property (weak, nonatomic) IBOutlet UILabel *labelTitle;
@property (weak, nonatomic) IBOutlet UITextField *txtUse;
@property (weak, nonatomic) IBOutlet UIDatePicker *datePicker;


@end

@implementation AddViewController

-(void)viewWillAppear:(BOOL)animated
{
    [self.txtMoney setTextColor:[UIColor greenColor]];
    [self.labelTitle setTextColor:[UIColor greenColor]];
    
    [self.switchInOrOut setOn:YES];
    [self.txtMoney setText:@""];
    [self.labelTitle setText:@""];
    [self.txtUse setText:@""];
    [self.datePicker setDate:[NSDate date]];
    [self loadAccountBookToUI];
    [super viewWillAppear:animated];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    UITapGestureRecognizer* tapper = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(handleSingleTap:)]; tapper.cancelsTouchesInView = NO; [self.view addGestureRecognizer:tapper];
}

- (void)handleSingleTap:(UITapGestureRecognizer *) sender {
    [self.txtMoney endEditing:YES];
    [self.txtUse endEditing:YES];
}

- (void)loadAccountBookToUI
{
    if (self.abk == nil) {
        return ;
    }
    [self.switchInOrOut setOn:![self.abk.inOrOut boolValue]];
    [self.txtMoney setText:self.abk.money];
    [self.txtUse setText:self.abk.use];
    [self.datePicker setDate:self.abk.date];
}

- (void)saveAccountBook
{
    AccountBook* abk = [[AccountBook alloc] init];
    abk.inOrOut = @(!self.switchInOrOut.isOn);
    abk.money = self.txtMoney.text;
    abk.use = self.txtUse.text;
    abk.date = [self.datePicker date];
    [abk save];
    [self.abk remove];
}

-(void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    
    if ([self.txtMoney.text integerValue] == 0) {
        return ;
    }
    [self saveAccountBook];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)changeInOrOut:(id)sender {
    if (self.switchInOrOut.isOn) {
        [self.txtMoney setTextColor:[UIColor greenColor]];
        [self.labelTitle setTextColor:[UIColor greenColor]];
    } else {
        [self.txtMoney setTextColor:[UIColor redColor]];
        [self.labelTitle setTextColor:[UIColor redColor]];
    }
    [self refreshMoneyTitle];
}

- (void)refreshMoneyTitle
{
    if (self.switchInOrOut.isOn) {
        [self.labelTitle setText:[NSString stringWithFormat:@"-%@元", self.txtMoney.text]];
    } else {
        [self.labelTitle setText:[NSString stringWithFormat:@"+%@元", self.txtMoney.text]];
    }
}

- (IBAction)changeMoney:(id)sender {
    [self refreshMoneyTitle];
}

@end
