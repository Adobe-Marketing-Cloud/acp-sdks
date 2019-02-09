//
//  Queue.m
//  Adobe Cloud Platform -- ACP SDK Extension for iOS
//
//  Copyright 1996-2019 Adobe. All Rights Reserved.
//


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
