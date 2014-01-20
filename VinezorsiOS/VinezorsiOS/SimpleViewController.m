//
//  SimpleViewController.m
//  VinezorsiOS
//
//  Created by Calvin Phung on 11/3/13.
//
//

#import "SimpleViewController.h"
#import "AppDelegate.h"

@interface SimpleViewController ()

@property (retain, nonatomic) IBOutlet UITextField *TextField_Input;
@property (retain, nonatomic) IBOutlet UISwitch *Switch_Music;

@end

@implementation SimpleViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)dealloc {
    [_TextField_Input release];
    [_Switch_Music release];
    [super dealloc];
}

- (IBAction)buttonBegin_OnPress:(UIButton *)sender {
    AppDelegate *appDelegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
    
    [appDelegate go:_TextField_Input.text :[_Switch_Music isOn]];
}

@end
