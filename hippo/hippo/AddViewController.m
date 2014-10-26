//
//  AddViewController.m
//  hippo
//
//  Created by FanFamily on 14-10-26.
//  Copyright (c) 2014年 familymrfan. All rights reserved.
//

#import "AddViewController.h"

@interface AddViewController ()

@property (weak, nonatomic) IBOutlet UISwitch *switchInOrOut;
@property (weak, nonatomic) IBOutlet UITextField *txtMoney;
@property (weak, nonatomic) IBOutlet UILabel *labelTitle;

@end

@implementation AddViewController

-(void)viewWillAppear:(BOOL)animated
{
    [self.txtMoney setTextColor:[UIColor greenColor]];
    [self.labelTitle setTextColor:[UIColor greenColor]];
    [super viewWillAppear:animated];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // Do any additional setup after loading the view.
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
        [self.labelTitle setText:[NSString stringWithFormat:@"支出%@元", self.txtMoney.text]];
    } else {
        [self.labelTitle setText:[NSString stringWithFormat:@"收入%@元", self.txtMoney.text]];
    }
}

- (IBAction)changeMoney:(id)sender {
    [self refreshMoneyTitle];
}

@end
