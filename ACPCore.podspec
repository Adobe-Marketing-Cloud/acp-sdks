Pod::Spec.new do |s|
  s.name         = "ACPCore"
  s.version      = "2.0.1"
  s.summary      = "Core library for Adobe Experience Platform SDK. Written and Supported by Adobe."
  s.description  = <<-DESC
                   The core library provides the foundation for the Adobe Experience Platform SDK.  Having the core library installed is a pre-requisite for any other Adobe Experience Platform SDK extension to work.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :file => "LICENSE.md"}
  s.author       = "Adobe Experience Platform SDK Team"
  s.source       = { :git => 'https://github.com/Adobe-Marketing-Cloud/acp-sdks.git', :tag => "v#{s.version}-#{s.name}" }
  s.platform     = :ios, '10.0'

  s.default_subspec = 'iOS'

  s.subspec 'iOS' do |ios|
    ios.vendored_libraries = "libACPCore_iOS.a","libACPIdentity_iOS.a","libACPSignal_iOS.a","libACPLifecycle_iOS.a"
    ios.source_files = "include/*.h", "include/*.m"
    ios.frameworks = "UIKit", "SystemConfiguration", "WebKit", "UserNotifications"
    ios.libraries = "sqlite3.0", "c++", "z"
  end
end
