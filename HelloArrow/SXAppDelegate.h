//
//  SXAppDelegate.h
//  HelloArrow
//
//  Created by shin on 12-10-28.
//  Copyright (c) 2012年 Indie Developer. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GLView.h"

@interface SXAppDelegate : UIResponder <UIApplicationDelegate>
{
    GLView *m_view;
}

@property (strong, nonatomic) UIWindow *window;

@end
