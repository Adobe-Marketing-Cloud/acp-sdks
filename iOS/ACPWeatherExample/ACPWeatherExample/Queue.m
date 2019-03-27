/*
 ADOBE CONFIDENTIAL
 
 Copyright 2019 Adobe
 All Rights Reserved.
 
 NOTICE: Adobe permits you to use, modify, and distribute this file in
 accordance with the terms of the Adobe license agreement accompanying
 it. If you have received this file from a source other than Adobe,
 then your use, modification, or distribution of it requires the prior
 written permission of Adobe.
 */

#import "Queue.h"
@interface Queue()
@property (strong) NSMutableArray *queuedEvents;
@end

@implementation Queue
- (instancetype)init{
    if (self = [super init]){
        _queuedEvents = [[NSMutableArray alloc] init];
    }
    return self;
}

- (void)add: (ACPExtensionEvent*)event{
    [self.queuedEvents addObject:event];
}

- (ACPExtensionEvent*) poll {
    id headObject = [self.queuedEvents objectAtIndex:0];
    if (headObject != nil) {
        [self.queuedEvents removeObjectAtIndex:0];
    }
    return headObject;
}

- (ACPExtensionEvent*) peek {
    id headObject = [self.queuedEvents objectAtIndex:0];
    return headObject;
}

- (bool) hasNext {
    return [self.queuedEvents objectAtIndex:0] != nil;
}

@end
