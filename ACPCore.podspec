Pod::Spec.new do |s|
  s.name         = "ACPCore"
  s.version      = "2.8.2"
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
  s.subspec 'main' do |th|

  th.ios.vendored_libraries = "libACPCore_iOS.a","libACPIdentity_iOS.a","libACPSignal_iOS.a","libACPLifecycle_iOS.a"
  th.ios.frameworks = "UIKit", "SystemConfiguration", "WebKit", "UserNotifications"
  th.ios.libraries = "sqlite3.0", "z", "c++"
  th.ios.source_files = "include/*.h", "include/Empty.m"

  th.tvos.vendored_libraries = "libACPCore_tvOS.a", "libACPIdentity_tvOS.a", "libACPSignal_tvOS.a", "libACPLifecycle_tvOS.a"
  th.tvos.frameworks = "SystemConfiguration"
  th.tvos.libraries = "sqlite3.0", "z", "c++"
  th.tvos.source_files = "include/*.h", "include/Empty.m"
  end
end
