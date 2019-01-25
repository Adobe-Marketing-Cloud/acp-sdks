//
//  WeatherExtensionInternal.m
//  Adobe Cloud Platform -- ACP SDK Extension for iOS
//
//  Copyright 1996-2018 Adobe. All Rights Reserved.
//

#import "ACPCore.h"
#import "ACPExtensionApi.h"
#import "ACPExtensionEvent.h"
#import "WeatherExtensionInternal.h"
#import "WeatherExtensionListener.h"
#import "WeatherExtensionApiHandler.h"
#import "WeatherExtensionDataObject.h"
#import "Queue.h"

@interface WeatherExtensionInternal()
@property (nonatomic, strong) WeatherExtensionApiHandler *apiHandler;
@property (nonatomic, strong) Queue *eventQueue;
@property (nonatomic, strong) NSString *mid;
@end

@implementation WeatherExtensionInternal

static NSString* ACP_STATE_OWNER = @"stateowner";
static NSString* ACP_CONFIGURATION_SHARED_STATE = @"com.adobe.module.configuration";
static NSString* ACP_IDENTITY_SHARED_STATE = @"com.adobe.module.identity";
static NSString* ACP_IDENTITY_MID_KEY = @"mid";
static NSString* ACP_RULES_TRIGGERED_CONSEQUENCE_KEY = @"triggeredconsequence";
static NSString* ACP_RULES_DETAIL_KEY = @"detail";
static NSString* WEATHER_API_KEY = @"weather.apiKey";
static NSString* WEATHER_ZIP_KEY = @"zip";
static NSString* WEATHER_KEY = @"weather";

#pragma mark - ACPExtension methods
- (nullable NSString *) name {
    return @"com.acpExample.weatherExtension";
}

- (NSString *) version {
    return @"1.0.0";
}

- (instancetype) init {
    if (self = [super init]) {
        NSError *error = nil;
        
        // register a listener for shared state changes
        if ([self.api registerListener:[WeatherExtensionListener class]
                             eventType:@"com.adobe.eventType.hub"
                           eventSource:@"com.adobe.eventSource.sharedState"
                                 error:&error]) {
            NSLog(@"WeatherExtensionListener successfully registered for Event Hub Shared State events");
        } else {
            NSLog(@"There was an error registering WeatherExtensionListener for Event Hub Shared State events: %@", error.localizedDescription ?: @"unknown");
        }
        
        // register a listener for RulesEngine response events
        error = nil;
        if ([self.api registerListener:[WeatherExtensionListener class]
                             eventType:@"com.adobe.eventType.rulesEngine"
                           eventSource:@"com.adobe.eventSource.responseContent"
                                 error:&error]) {
            NSLog(@"WeatherExtensionListener successfully registered for Rules Engine Response Content events");
        } else {
            NSLog(@"There was an error registering WeatherExtensionListener for Rules Engine Response Content events: %@", error.localizedDescription ?: @"unknown");
        }
        
        // register a listener for WeatherExtension request events
        error = nil;
        if ([self.api registerListener:[WeatherExtensionListener class]
                             eventType:@"com.acpExample.eventType.weatherExtension"
                           eventSource:@"com.acpExample.eventSource.requestContent"
                                 error:&error]) {
            NSLog(@"WeatherExtensionListener successfully registered for WeatherExtension Request Content events");
        } else {
            NSLog(@"There was an error registering WeatherExtensionListener for WeatherExtension Request Content events: %@", error.localizedDescription ?: @"unknown");
        }
        
        // create our WeatherExtensionApiHandler
        self.apiHandler = [[WeatherExtensionApiHandler alloc] init];
        
        // initialize the events queue
        self.eventQueue = [[Queue alloc] init];
    }

    return self;
}

- (void) onUnregister {
    [super onUnregister];
    
    // the extension was unregistered
    // if the shared states are not used in the next registration they can be cleared in this method
    [[self api] clearSharedEventStates:nil];
    
    self.apiHandler.apiKey = @"";
    self.mid = nil;
}

- (void) unexpectedError:(NSError *)error {
    [super unexpectedError:error];
}

#pragma mark - WeatherExtension Internal methods
- (void) handleGetWeatherEvent:(ACPExtensionEvent *)event {
    NSLog(@"%@ - Handling Get Weather event", [self name]);
    NSNumber *zip = event.eventData[WEATHER_ZIP_KEY];
    [self.apiHandler getWeatherForZip:[zip integerValue] callback:^(NSDictionary* _Nullable content) {
        // create the response event
        NSLog(@"%@ - Weather object returned: %@", [self name], content);
        
        NSError *eventError = nil;
        NSDictionary* eventData = @{WEATHER_KEY : content};
        ACPExtensionEvent *weatherLoadedEvent = [ACPExtensionEvent extensionEventWithName:@"Weather Loaded"
                                                                                     type:@"com.acpExample.eventType.weatherExtension"
                                                                                   source:@"com.acpExample.eventSource.responseContent"
                                                                                     data:eventData
                                                                                    error:&eventError];
        if (!weatherLoadedEvent) {
            NSLog(@"%@ - An error occurred constructing event '%@': %@", [self name], weatherLoadedEvent.eventName, eventError.localizedDescription ?: @"unknown");
        }
        
        // update weather extension's shared state
        NSError *setSharedStateError = nil;
        if (![[self api] setSharedEventState:content event:event error:&setSharedStateError] && setSharedStateError != nil) {
            NSLog(@"An error occurred while setting the shared state %@, error code %ld", content, [setSharedStateError code]);
        }
        
        // dispatch the response for the public API
        NSError *dispatchError = nil;
        if ([ACPCore dispatchResponseEvent:weatherLoadedEvent requestEvent:event error:&dispatchError]) {
            NSLog(@"WeatherExtension dispatched an event '%@'", weatherLoadedEvent.eventName);
        } else {
            NSLog(@"%@ - An error occurred dispatching event '%@': %@", [self name], weatherLoadedEvent.eventName, dispatchError.localizedDescription ?: @"unknown");
        }
    }];
}

- (void) handleRulesConsequence:(ACPExtensionEvent *)event {
    NSLog(@"%@ - Handling Triggered Consequence event", [self name]);
    NSDictionary *eventData = event.eventData;
    if (!eventData) {
        return;
    }
    
    NSDictionary *triggeredConsequence = eventData[ACP_RULES_TRIGGERED_CONSEQUENCE_KEY];
    if (!triggeredConsequence || [triggeredConsequence count] == 0) {
        return;
    }
    
    NSDictionary *detail = triggeredConsequence[ACP_RULES_DETAIL_KEY];
    if (!detail || [detail count] == 0) {
        return;
    }

    NSString *zip = detail[WEATHER_ZIP_KEY];
    if (!zip) {
        NSLog(@"%@ - Not a zip request consequence", [self name]);
        return;
    }
    
    [self.apiHandler getWeatherForZip:[zip integerValue] callback:^(NSDictionary* _Nullable content) {
        NSLog(@"%@ - The weather has been updated for this user: %@, %@", self.name, content[@"temp"], content[@"conditions"]);
        // update weather extension's shared state
        NSError *setSharedStateError = nil;
        if (![[self api] setSharedEventState:content event:event error:&setSharedStateError] && setSharedStateError != nil) {
            NSLog(@"An error occurred while setting the shared state %@, error code %ld", content, [setSharedStateError code]);
        }
    }];
}

- (void) queueEvent: (ACPExtensionEvent*) event {
    if (!event) {
        return;
    }
    
    [self.eventQueue add:event];
}

- (void) processEvents {
    while ([self.eventQueue hasNext]) {
        ACPExtensionEvent* eventToProcess = [self.eventQueue peek];
        
        NSError *error = nil;
        NSDictionary *configSharedState = [self.api getSharedEventState:ACP_CONFIGURATION_SHARED_STATE event:eventToProcess error:&error];
        
        // NOTE: configuration is mandatory processing the event, so if shared state is null stop processing events
        if (!configSharedState) {
            NSLog(@"%@ - Could not process event, configuration shared state is pending", [self name]);
            return;
        }
        
        if (error != nil) {
            NSLog(@"%@ - Could not process event, an error occured while retrieving configuration shared state %ld", [self name], [error code]);
            return;
        }
        
        self.apiHandler.apiKey = configSharedState.count ? configSharedState[WEATHER_API_KEY] : @"";
        
        // Identity is not a mandatory dependency for this event, just retrive mid
        [self extractMidFromIdentitySharedState:eventToProcess];
        
        if ([eventToProcess.eventType isEqualToString:@"com.acpExample.eventType.weatherExtension"]) {
            // handle the get weather event
            [self handleGetWeatherEvent:eventToProcess];
            NSLog(@"%@ - GetWeather event successfully processed", [self name]);
        } else if ([eventToProcess.eventType isEqualToString:@"com.adobe.eventType.rulesEngine"]) {
            // handle the rules consequence
            [self handleRulesConsequence:eventToProcess];
            NSLog(@"%@ - Rules consequence event successfully processed", [self name]);
        }
        [self.eventQueue poll];
    }
}

- (void) extractMidFromIdentitySharedState:(ACPExtensionEvent *) event {
    NSError *error = nil;
    NSDictionary *identitySharedState = [self.api getSharedEventState:ACP_IDENTITY_SHARED_STATE event:event error:&error];
    
    if (!identitySharedState) {
        NSLog(@"%@ - Identity shared state is pending, returning nil", [self name]);
        return;
    }
    
    if (error != nil) {
        NSLog(@"%@ - An error occured while retrieving identity shared state %ld", [self name], [error code]);
        return;
    }
    
    if (identitySharedState.count) {
        self.mid = identitySharedState[ACP_IDENTITY_MID_KEY];
    }
}

@end
