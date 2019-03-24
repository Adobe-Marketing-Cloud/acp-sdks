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

#import "ACPExtension.h"

NS_ASSUME_NONNULL_BEGIN

@class WeatherExtensionDataObject;

// A custom extension must inherit from the ACPExtension class, which can be found in the ACPCore_iOS.framework
@interface WeatherExtensionInternal : ACPExtension

- (void) queueEvent: (ACPExtensionEvent*) event;
- (void) processEvents;

@end

NS_ASSUME_NONNULL_END
