//
//  ACPPlaces.h
//  Adobe Cloud Platform -- iOS Framework
//
//  Copyright 1996-2018. Adobe. All Rights Reserved
//
//  Places Version: 0.0.1

#import <Foundation/Foundation.h>

@class ACPPlacesPoi, CLLocation, CLRegion;

/**
 * @brief An enum type representing different types of region events
 *
 * @see processRegionEvent:forRegionEventType:
 */
typedef NS_ENUM(NSUInteger, ACPRegionEventType) {
    ACPRegionEventTypeEntry   = 1, /*!< Enum value ACPRegionEventTypeEntry */
    ACPRegionEventTypeExit    = 2, /*!< Enum value ACPRegionEventTypeExit */
    ACPRegionEventTypeNone    = 3  /*!< Enum value ACPRegionEventTypeNone */
};

@interface ACPPlaces : NSObject {}

/**
 * @brief Returns the current version of the ACPPlaces Extension.
 */
+ (nonnull NSString*) extensionVersion;

/**
 * @brief Requests a list of nearby Points of Interest (POI) and returns them in a callback.
 *
 * @param currentLocation a CLLocation object represent the current location of the device
 * @param limit a non-negative number representing the number of nearby POI to return from the request
 * @param callback called with an array of ACPPlacesPoi objects that represent the nearest POI to the device
 */
+ (void) getNearbyPointsOfInterest: (nonnull CLLocation*) currentLocation
                             limit: (NSUInteger) limit
                          callback: (nullable void (^) (NSArray<ACPPlacesPoi*>* _Nullable nearbyPoi)) callback;

/**
 * @brief Passes a region and event type to be processed by the SDK
 *
 * Calling this method will result in an Event being dispatched in the SDK, allowing for rules to be processed
 * as a result of the triggering event.
 *
 * @param region the CLRegion object that triggered the event
 * @param eventType value indicating whether the device entered or exited the provided region
 */
+ (void) processRegionEvent: (nonnull CLRegion*) region forRegionEventType: (ACPRegionEventType) eventType;

/**
 * @brief Registers the ACPPlaces extension with the Core Event Hub.
 */
+ (void) registerExtension;

@end

#pragma mark - Custom Places Objects
/**
 *  @class ACPPlacesPoi
 *
 *  This class contains data that is directly correlated to the properties maintained by the Adobe Places Database.
 */
@interface ACPPlacesPoi : NSObject

@property(nonatomic, strong, nullable) NSString* identifier;  ///< The identifier for the POI
@property(nonatomic, strong, nullable) NSString* name;  ///< The name of the POI
@property(nonatomic) double latitude;  ///< The latitude of the POI's center
@property(nonatomic) double longitude;  ///< The longitude of the POI's center
@property(nonatomic) NSUInteger radius;  ///< The radius of the POI
@property(nonatomic, strong, nullable) NSDictionary<NSString*, NSString*>* metaData;  ///< Dictionary containing meta data for the POI
@property(nonatomic) Boolean userIsWithin;  ///< Indicates if the device is currently inside of this POI

@end
