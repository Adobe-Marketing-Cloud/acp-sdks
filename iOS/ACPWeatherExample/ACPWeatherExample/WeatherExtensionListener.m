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

#import "ACPCore.h"
#import "WeatherExtensionInternal.h"
#import "WeatherExtensionListener.h"

@implementation WeatherExtensionListener

- (void) hear:(ACPExtensionEvent *)event {
    [ACPCore log:ACPMobileLogLevelDebug tag:@"WeatherExtensionListener" message:[NSString stringWithFormat:@"WeatherExtensionListener heard an event: %@, %@.  Data: %@", event.eventName, event.eventType, event.eventData]];
    WeatherExtensionInternal* parentExtension = [self getParentExtension];
    if (parentExtension == nil) {
        [ACPCore log:ACPMobileLogLevelWarning tag:@"WeatherExtensionListener" message:@"The parent extension was nil, skipping event"];
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
