//
//  WeatherExtensionListener.h
//  Adobe Cloud Platform -- ACP SDK Extension for iOS
//
//  Copyright 1996-2019 Adobe. All Rights Reserved.
//

#import "ACPExtensionEvent.h"
#import "ACPExtensionListener.h"

NS_ASSUME_NONNULL_BEGIN

@interface WeatherExtensionListener : ACPExtensionListener

- (void) hear:(ACPExtensionEvent *)event;

@end

NS_ASSUME_NONNULL_END
