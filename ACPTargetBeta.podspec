Pod::Spec.new do |s|
  s.name         = "ACPTargetBeta"
  s.version      = "0.0.2beta"
  s.summary      = "BETA - Target framework for Adobe Experience Cloud SDK. Written and Supported by Adobe, the official Pod for the Adobe Experience Cloud."
  s.description  = <<-DESC
                   By using the Adobe Cloud Platform SDKs (“Beta”), you hereby acknowledge that the Beta is provided “as is” without warranty of any kind. Adobe shall have no obligation to maintain, correct, update, change, modify or otherwise support the Beta. You are advised to use caution and not to rely in any way on the correct functioning or performance of such Beta and/or accompanying materials.

                   The target framework provides APIs that allow use of the Target product in the V5 Adobe Experience Cloud SDK.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :text => "Adobe Systems, Incorporated.  All Rights Reserved."}
  s.author       = "Adobe Cloud Platform SDK Team"
  s.source       = { :git => 'https://github.com/Adobe-Marketing-Cloud/acp-sdks.git', :tag => "v0.0.2beta-ACPTarget" }
  s.platform     = :ios, '10.0'

  s.default_subspec = 'iOS'

  # dependency on the core framework
  s.dependency "ACPCoreBeta", ">= 0.0.3beta"

  s.subspec 'iOS' do |ios|
    ios.preserve_paths = '*/Frameworks/*.framework'
    ios.source_files = 'Pod/Classes/**/*', 'ACPTarget_iOS.framework/Headers/*.h'
    ios.public_header_files = 'ACPTarget_iOS.framework/Headers/*.h'
    ios.vendored_frameworks = 'ACPTarget_iOS.framework', 'AdobeMarketingMobileTarget.framework'
    ios.xcconfig = {
      "FRAMEWORK_SEARCH_PATHS" => "'${PODS_ROOT}/ACPTarget'",
      "LD_RUNPATH_SEARCH_PATHS" => "@loader_path/../Frameworks"
    }
    ios.requires_arc = true
  end
end
