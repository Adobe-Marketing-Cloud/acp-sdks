Pod::Spec.new do |s|
  s.name         = "ACPCoreBeta"
  s.version      = "0.0.2beta"
  s.summary      = "BETA - Core framework for Adobe Experience Cloud SDK. Written and Supported by Adobe, the official Pod for the Adobe Experience Cloud."
  s.description  = <<-DESC
                   By using the Adobe Cloud Platform SDKs (“Beta”), you hereby acknowledge that the Beta is provided “as is” without warranty of any kind. Adobe shall have no obligation to maintain, correct, update, change, modify or otherwise support the Beta. You are advised to use caution and not to rely in any way on the correct functioning or performance of such Beta and/or accompanying materials.

                   The core framework provides the foundation for the V5 Adobe Experience Cloud SDK.  Having the core framework installed is a pre-requisite for any other V5 extension to work.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :text => "Adobe Systems, Incorporated.  All Rights Reserved."}
  s.author       = "Adobe Cloud Platform SDK Team"
  s.source       = { :git => 'https://github.com/Adobe-Marketing-Cloud/acp-sdks.git', :tag => "v0.0.2beta-ACPCore" }
  s.platform     = :ios, '10.0'

  s.default_subspec = 'iOS'

  s.subspec 'iOS' do |ios|
    ios.frameworks = "UIKit"
    ios.vendored_frameworks = "ACPCore_iOS.framework"
  end
end
