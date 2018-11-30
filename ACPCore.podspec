Pod::Spec.new do |s|
  s.name         = "ACPCore"
  s.version      = "1.0.2"
  s.summary      = "Core framework for Adobe Experience Platform SDK. Written and Supported by Adobe."
  s.description  = <<-DESC
                   The core framework provides the foundation for the Adobe Experience Platform SDK.  Having the core framework installed is a pre-requisite for any other Adobe Experience Platform SDK extension to work.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :file => "LICENSE.md"}
  s.author       = "Adobe Cloud Platform SDK Team"
  s.source       = { :git => 'https://github.com/Adobe-Marketing-Cloud/acp-sdks.git', :tag => "v1.0.2-ACPCore" }
  s.platform     = :ios, '10.0'

  s.default_subspec = 'iOS'

  s.subspec 'iOS' do |ios|    
    ios.frameworks = "UIKit"
    ios.vendored_frameworks = "ACPCore_iOS.framework",
                              "AdobeMarketingMobileCore.framework",
                              "ACPIdentity_iOS.framework",
                              "ACPLifecycle_iOS.framework",
                              "ACPSignal_iOS.framework"
  end
end
