//
//  Queue.h
//  Adobe Cloud Platform -- ACP SDK Extension for iOS
//
//  Copyright 1996-2018 Adobe. All Rights Reserved.
//

#import <Foundation/Foundation.h>
#import "ACPExtensionEvent.h"

@interface Queue : NSObject

- (void)add:(nonnull ACPExtensionEvent*)event;
- (ACPExtensionEvent*) peek;
- (ACPExtensionEvent*) poll;
- (bool) hasNext;

@end
