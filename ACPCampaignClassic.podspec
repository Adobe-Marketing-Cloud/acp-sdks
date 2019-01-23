Pod::Spec.new do |s|
  s.name         = "ACPCampaignClassic"
  s.version      = "2.0.0"
  s.summary      = "Campaign Classic framework for Adobe Experience Cloud SDK. Written and maintained by Adobe."
  s.description  = <<-DESC
                   The campaign classic framework provides APIs that allow use of the Campaign Classic product in the V5 Adobe Experience Cloud SDK.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :text => "Adobe.  All Rights Reserved."}
  s.author       = "Adobe Mobile SDK Team"
  s.source       = { :git => 'git@git.corp.adobe.com:dms-mobile/v5-ios-builds.git', :tag => "v#{s.version}-#{s.name}" }
  s.platform = :ios, "10.0"
  s.requires_arc = true

  s.default_subspec = "iOS"
  s.static_framework = true

  s.dependency "ACPCore", "~> 2.0"

  s.subspec "iOS" do |ios|
    ios.vendored_libraries = "iOS/libACPCampaignClassic_iOS.a"
    ios.source_files = "iOS/include/*.h", "iOS/include/*.m"
    ios.frameworks = "UIKit", "SystemConfiguration"
    ios.libraries = "sqlite3.0", "c++", "z"
  end

  # s.default_subspec = 'iOS'
  #
  # s.subspec 'iOS' do |ios|
  #   ios.frameworks = "UIKit"
  #   ios.vendored_frameworks = "ADBCore"
  # end

  # s.subspec 'Extension' do |extension|
  #   extension.platform     = :ios, '5.0'
  #   extension.source_files  = "AdobeMobileLibrary/*.h", "AdobeMobileLibrary/Empty.m"
  #   extension.frameworks = "UIKit", "SystemConfiguration"
  #   extension.libraries = "sqlite3.0"
  #   extension.vendored_libraries = "AdobeMobileLibrary/libAdobeMobile_extension.a"
  # end
  #
  # s.subspec 'WatchOS2' do |watchos2|
  #   watchos2.platform  = :watchos, '2.0'
  #   watchos2.source_files  = "AdobeMobileLibrary/*.h", "AdobeMobileLibrary/Empty.m"
  #   watchos2.libraries = "sqlite3.0"
  #   watchos2.vendored_libraries = "AdobeMobileLibrary/libAdobeMobile_watch.a"
  # end
  #
  # s.subspec 'TVOS' do |tvos|
  #   tvos.platform  = :tvos, '9.0'
  #   tvos.tvos.deployment_target = '9.0'
  #   tvos.source_files  = "AdobeMobileLibrary/*.h", "AdobeMobileLibrary/Empty.m"
  #   tvos.frameworks = "UIKit", "SystemConfiguration"
  #   tvos.libraries = "sqlite3.0"
  #   tvos.vendored_libraries = "AdobeMobileLibrary/libAdobeMobile_TV.a"
  # end

end
