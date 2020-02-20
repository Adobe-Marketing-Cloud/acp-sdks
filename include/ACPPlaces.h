//
//  ACPPlaces.h
//  Adobe Cloud Platform -- iOS Framework
//
//  Copyright 1996-2018. Adobe. All Rights Reserved
//
//  Places Version: 1.3.1

#import <CoreLocation/CoreLocation.h>
#import <Foundation/Foundation.h>

@class ACPPlacesPoi;

/**
 * @brief An enum type representing different error codes when getting nearby POIs.
 *
 * @see getNearbyPointsOfInterest
 */
typedef NS_ENUM(NSUInteger, ACPPlacesRequestError) {
    ACPPlacesRequestErrorNone,
    ACPPlacesRequestErrorConnectivityError,
    ACPPlacesRequestErrorServerResponseError,
    ACPPlacesRequestErrorInvalidLatLongError,
    ACPPlacesRequestErrorConfigurationError,
    ACPPlacesRequestErrorQueryServiceUnavailable,
    ACPPlacesRequestErrorUnknownError
};

/**
 * @brief An enum type representing different types of region events
 *
 * @see processRegionEvent:forRegionEventType:
 */
typedef NS_ENUM(NSUInteger, ACPRegionEventType) {
    ACPRegionEventTypeNone,     /*!< Enum value ACPRegionEventTypeNone */
    ACPRegionEventTypeEntry,    /*!< Enum value ACPRegionEventTypeEntry */
    ACPRegionEventTypeExit      /*!< Enum value ACPRegionEventTypeExit */
};

@interface ACPPlaces : NSObject {}

/**
 * @brief Clears out the client-side data for Places in shared state, local storage, and in-memory.
 */
+ (void) clear;

/**
 * @brief Returns the current version of the ACPPlaces Extension.
 */
+ (nonnull NSString*) extensionVersion;

/**
 * @brief Returns the last latitude and longitude provided to the ACPPlaces Extension.
 *
 * @discussion If the ACPPlaces Extension does not have a valid last known location for the user, the CLLocation
 * object returned in the callback will have lat/lon values of 999.999. The CLLocation object returned by this
 * method will only ever contain valid data for latitude and longitude, and is not meant to be used for plotting
 * course, speed, altitude, etc.
 *
 * @param callback called with a CLLocation object representing the last known lat/lon provided to the extension
 */
+ (void) getLastKnownLocation: (nullable void (^) (CLLocation* _Nullable lastLocation)) callback;

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
 * @brief Requests a list of nearby Points of Interest (POI) and returns them in a callback.
 *
 * @param currentLocation a CLLocation object represent the current location of the device
 * @param limit a non-negative number representing the number of nearby POI to return from the request
 * @param callback called with an array of ACPPlacesPoi objects that represent the nearest POI to the device
 * @param errorCallback called if there was an error encountered while getting POIs.
 */
+ (void) getNearbyPointsOfInterest: (nonnull CLLocation*) currentLocation
                             limit: (NSUInteger) limit
                          callback: (nullable void (^) (NSArray<ACPPlacesPoi*>* _Nullable nearbyPoi)) callback
                     errorCallback: (nullable void (^) (ACPPlacesRequestError result)) errorCallback;

/**
 * @brief Returns all Points of Interest (POI) in which the device is currently known to be within.
 *
 * @param callback called with an array of ACPPlacesPoi objects that represent the user-within POIs
 */
+ (void) getCurrentPointsOfInterest: (nullable void (^) (NSArray<ACPPlacesPoi*>* _Nullable userWithinPoi)) callback;

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

/**
 * @brief Sets the authorization status in the Places extension.
 *
 * The status provided is stored in the Places shared state, and is for reference only.
 * Calling this method does not impact the actual location authorization status for this device.
 *
 * @param status the CLAuthorizationStatus to be set for this device
 */
+ (void) setAuthorizationStatus: (CLAuthorizationStatus) status;

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
@property(nonatomic, strong, nullable) NSDictionary<NSString*, NSString*>*
metaData;  ///< Dictionary containing meta data for the POI
@property(nonatomic) Boolean userIsWithin;  ///< Indicates if the device is currently inside of this POI

@end
