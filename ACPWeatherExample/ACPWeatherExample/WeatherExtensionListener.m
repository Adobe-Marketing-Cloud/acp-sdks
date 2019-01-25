//
//  WeatherExtensionListener.h
//  Adobe Cloud Platform -- ACP SDK Extension for iOS
//
//  Copyright 1996-2019 Adobe. All Rights Reserved.
//

#import "WeatherExtensionInternal.h"
#import "WeatherExtensionListener.h"

@implementation WeatherExtensionListener

- (void) hear:(ACPExtensionEvent *)event {
    NSLog(@"WeatherExtensionListener heard an event: %@, %@.  Data: %@", event.eventName, event.eventType, event.eventData);
    WeatherExtensionInternal* parentExtension = [self getParentExtension];
    if (parentExtension == nil) {
        NSLog(@"The parent extension was nil, skipping event");
        return;
    }

    // handle SharedState events
    if ([event.eventType isEqualToString:@"com.adobe.eventType.hub"]) {
        if ([event.eventData[@"stateowner"] isEqualToString:@"com.adobe.module.configuration"]) {
            [parentExtension processEvents];
        }
    }

    // handle WeatherExtension events
    else if ([event.eventType isEqualToString:@"com.acpExample.eventType.weatherExtension"]) {
        [parentExtension queueEvent:event];
        [parentExtension processEvents];
    }
    
    // handle Rules Consequences
    else if ([event.eventType isEqualToString:@"com.adobe.eventType.rulesEngine"] && [event.eventSource isEqualToString:@"com.adobe.eventSource.responseContent"]) {
        // todo: check consequence format
        [parentExtension queueEvent:event];
        [parentExtension processEvents];
    }
}

/**
 * Returns the parent extension that owns this listener
 */
- (WeatherExtensionInternal*) getParentExtension {
    WeatherExtensionInternal* parentExtension = nil;
    if ([[self extension] isKindOfClass:WeatherExtensionInternal.class]) {
        parentExtension = (WeatherExtensionInternal*) [self extension];
    }

    return parentExtension;
}

@end
