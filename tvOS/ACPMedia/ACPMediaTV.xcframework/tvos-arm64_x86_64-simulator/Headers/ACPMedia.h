//
//  ACPMedia.h
//  Adobe Digital Marketing Suite -- iOS Application Measurement Library
//
//  Copyright 1996-2020. Adobe, Inc. All Rights Reserved
//
//  Media Version: 2.3.1

#import <Foundation/Foundation.h>

/**
 * @brief These enumeration values define the type of a tracking event
 *
 * @see ACPMediaTracker::trackEvent:info:data:
 */
typedef NS_ENUM(NSInteger, ACPMediaEvent) {
    ACPMediaEventAdBreakStart,
    ACPMediaEventAdBreakComplete,
    ACPMediaEventAdStart,
    ACPMediaEventAdComplete,
    ACPMediaEventAdSkip,
    ACPMediaEventChapterStart,
    ACPMediaEventChapterComplete,
    ACPMediaEventChapterSkip,
    ACPMediaEventSeekStart,
    ACPMediaEventSeekComplete,
    ACPMediaEventBufferStart,
    ACPMediaEventBufferComplete,
    ACPMediaEventBitrateChange,
    ACPMediaEventStateStart,
    ACPMediaEventStateEnd
};

/**
 * @brief These enumeration values define the type of a media
 *
 * @see ACPMedia::createMediaObjectWithName:mediaId:length:streamType:mediaType:
 */
typedef NS_ENUM(NSInteger, ACPMediaType) {
    ACPMediaTypeVideo,
    ACPMediaTypeAudio
};

@interface ACPMediaTracker : NSObject

+ (instancetype _Nonnull) new NS_UNAVAILABLE;
- (instancetype _Nonnull) init NS_UNAVAILABLE;

/**
 * @brief Method to track the start of a viewing session.
 *
 * @param mediaInfo NSDictionary instance created using createMediaObjectWithName method
 * @param contextData NSDictionary instance containing the context data associated with the media
 */
- (void) trackSessionStart: (NSDictionary* _Nonnull) mediaInfo data: (NSDictionary* _Nullable) contextData;

/**
 * @brief Method to track media play or resume after a previous pause.
 */
- (void) trackPlay;

/**
 * @brief Method to track media pause.
 */
- (void) trackPause;

/**
 * @brief Method to track media complete.
 *
 */
- (void) trackComplete;

/**
 * @brief Method to track the end of a viewing session.
 *
 * This method must be called even if the user does not view the media to completion.
 */
- (void) trackSessionEnd;

/**
 * @brief Method to track an error in media playback.
 *
 * @param errorId Error Id
 */
- (void) trackError: (NSString* _Nonnull) errorId;

/**
 * @brief Method to track media event.
 *
 * @param event Media event
 * @param info Info object for AdBreakStart, AdStart and ChapterStart events. Pass nil for other events.
 * @param data NSDictionary instance containing context data for AdStart and ChapterStart events. Pass nil for other events.
 */
- (void) trackEvent: (ACPMediaEvent) event info: (NSDictionary* _Nullable) info data:
    (NSDictionary* _Nullable) data;

/**
 * @brief This method should be called when media playhead changes for accurate tracking.
 *
 * @param time Current position of the playhead. For VOD, value is specified in seconds from the beginning of the media item.
 * For live streaming, return playhead position if available or the current UTC time in seconds otherwise.
 */

- (void) updateCurrentPlayhead: (double) time;

/**
 * @brief This method should be called during a playback session with recently available QoE data.
 *
 * @param qoeObject NSDictionary instance containing current QoE information
 */

- (void) updateQoEObject: (NSDictionary* _Nonnull) qoeObject;

@end

@interface ACPMedia : NSObject {}
/**
 * @brief Registers the ACPMedia extension with the Core Event Hub.
 */
+ (void) registerExtension;

/**
 * @brief Returns the current version of the ACPMedia Extension.
 */
+ (NSString* _Nonnull) extensionVersion;

/**
 * @brief Creates an instance of ACPMediaTracker.
 */
+ (ACPMediaTracker* _Nullable) createTracker;

/**
 * @brief Creates an instance of ACPMediaTracker.
 *
 * @param config Config to override default config passed through V5 config.
 */
+ (ACPMediaTracker* _Nullable) createTrackerWithConfig: (NSDictionary* _Nullable) config;

/**
 * @deprecated
 * @brief Creates an instance of ACPMediaTracker.
 *
 * @param callback Callback which returns the created ACPMediaTracker instance.
 */
+ (void) createTracker: (void (^ _Nonnull) (
    ACPMediaTracker* _Nullable)) callback __attribute__ ( (deprecated)) ;

/**
 * @deprecated
 * @brief Creates an instance of ACPMediaTracker.
 *
 * @param config Config to override default config passed through V5 config.
 * @param callback Callback which returns the created ACPMediaTracker instance.
 */
+ (void) createTrackerWithConfig: (NSDictionary* _Nullable) config
                        callback: (void (^ _Nonnull) (ACPMediaTracker* _Nullable)) callback __attribute__ ( (deprecated)) ;

/**
 * @brief Creates an instance of the Media info object.
 *
 * @param name The name of the media
 * @param mediaId The unqiue identifier for the media
 * @param length The length of the media in seconds
 * @param streamType The stream type as a string. Use the pre-defined constants for vod, live, and linear content
 * @param mediaType The media type of the stream
 */
+ (NSDictionary* _Nonnull) createMediaObjectWithName: (NSString* _Nonnull) name
                                             mediaId: (NSString* _Nonnull) mediaId
                                              length: (double) length
                                          streamType: (NSString* _Nonnull) streamType
                                           mediaType: (ACPMediaType) mediaType;

/**
 * @brief Creates an instance of the AdBreak info object.
 *
 * @param name The name of the ad break
 * @param position The position of the ad break in the content starting with 1
 * @param startTime The start time of the ad break relative to the main media
 */
+ (NSDictionary* _Nonnull) createAdBreakObjectWithName: (NSString* _Nonnull) name
                                              position: (double) position
                                             startTime: (double) startTime;

/**
 * @brief Creates an instance of the Ad info object.
 *
 * @param name The name of the ad
 * @param adId The unique id for the ad
 * @param position The start position of the ad
 * @param length The length of the ad in seconds
 */
+ (NSDictionary* _Nonnull) createAdObjectWithName: (NSString* _Nonnull) name
                                             adId: (NSString* _Nonnull) adId
                                         position: (double) position
                                           length: (double) length;

/**
 * @brief Creates an instance of the Chapter info object.
 *
 * @param name The name of the chapter
 * @param position The position of the chapter
 * @param length The length of the chapter in seconds
 * @param startTime The start time of the chapter relative to the main media
 */
+ (NSDictionary* _Nonnull) createChapterObjectWithName: (NSString* _Nonnull) name
                                              position: (double) position
                                                length: (double) length
                                             startTime: (double) startTime;

/**
 * @brief Creates an instance of the QoE info object.
 *
 * @param bitrate The bitrate of media in bits per second
 * @param startupTime The start up time of media in seconds
 * @param fps The current frames per second information
 * @param droppedFrames The number of dropped frames so far
 */
+ (NSDictionary* _Nonnull) createQoEObjectWithBitrate: (double) bitrate
                                          startupTime: (double) startupTime
                                                  fps: (double) fps
                                        droppedFrames: (double) droppedFrames;

/**
* @brief Creates an instance of the state info object.
*
* @param stateName The media state with a state name
*/
+ (NSDictionary* _Nonnull) createStateObjectWithName: (NSString* _Nonnull) stateName;

@end
