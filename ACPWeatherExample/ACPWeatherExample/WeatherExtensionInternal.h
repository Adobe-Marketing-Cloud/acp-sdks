//
//  WeatherExtensionInternal.h
//  Adobe Cloud Platform -- ACP SDK Extension for iOS
//
//  Copyright 1996-2018 Adobe. All Rights Reserved.
//

#import "ACPExtension.h"

NS_ASSUME_NONNULL_BEGIN

@class WeatherExtensionDataObject;

// A custom extension must inherit from the ACPExtension class, which can be found in the ACPCore_iOS.framework
@interface WeatherExtensionInternal : ACPExtension

- (void) queueEvent: (ACPExtensionEvent*) event;
- (void) processEvents;

@end

NS_ASSUME_NONNULL_END
