//
//  WeatherExtensionDataObject.h
//  Adobe Cloud Platform -- ACP SDK Extension for iOS
//
//  Copyright 1996-2018 Adobe. All Rights Reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface WeatherExtensionDataObject : NSObject

@property (nonatomic) double temperature;
@property (nonatomic) UIColor *tempColor;
@property (nonatomic, strong) NSString *conditions;
@property (nonatomic, strong) UIImage *picture;

+ (WeatherExtensionDataObject *) weatherWithTemp:(double)temp conditions:(NSString *)conditions;

@end

NS_ASSUME_NONNULL_END
