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
