Pod::Spec.new do |s|
  s.name         = "ACPCore"
  s.version      = "2.9.5"
  s.summary      = "Core library for Adobe Experience Platform SDK. Written and Supported by Adobe."
  s.description  = <<-DESC
                   The core library provides the foundation for the Adobe Experience Platform SDK.  Having the core library installed is a pre-requisite for any other Adobe Experience Platform SDK extension to work.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :file => "LICENSE.md"}
  s.author       = "Adobe Experience Platform SDK Team"
  s.source       = { :git => 'https://github.com/Adobe-Marketing-Cloud/acp-sdks.git', :tag => "v#{s.version}-#{s.name}" }

  s.ios.deployment_target = '10.0'
  s.tvos.deployment_target = '10.0'
  s.static_framework = true
  s.default_subspec = 'main'
  s.cocoapods_version = ">= 1.10"

  s.subspec 'main' do |th|
    th.ios.vendored_frameworks = "ACPCore.xcframework", "ACPIdentity.xcframework", "ACPLifecycle.xcframework", "ACPSignal.xcframework"
    th.ios.frameworks = "UIKit", "SystemConfiguration", "WebKit", "UserNotifications"
    th.ios.libraries = "sqlite3.0", "z", "c++"
    th.ios.source_files = "ACPCore.xcframework/ios-arm64_armv7_armv7s/Headers/*.h", "ACPIdentity.xcframework/ios-arm64_armv7_armv7s/Headers/*.h", "ACPLifecycle.xcframework/ios-arm64_armv7_armv7s/Headers/*.h", "ACPSignal.xcframework/ios-arm64_armv7_armv7s/Headers/*.h", "include/Empty.m"

    th.tvos.vendored_frameworks = "ACPCoreTV.xcframework", "ACPIdentityTV.xcframework", "ACPLifecycleTV.xcframework", "ACPSignalTV.xcframework"
    th.tvos.frameworks = "SystemConfiguration"
    th.tvos.libraries = "sqlite3.0", "z", "c++"
    th.tvos.source_files = "ACPCoreTV.xcframework/tvos-arm64/Headers/*.h", "ACPIdentityTV.xcframework/tvos-arm64/Headers/*.h", "ACPLifecycleTV.xcframework/tvos-arm64/Headers/*.h", "ACPSignalTV.xcframework/tvos-arm64/Headers/*.h", "include/Empty.m"
  end
end
