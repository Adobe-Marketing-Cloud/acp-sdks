Pod::Spec.new do |s|
  s.name         = "ACPAudienceBeta"
  s.version      = "1.0.2beta"
  s.summary      = "BETA - Audience Manager framework for Adobe Experience Cloud SDK. Written and Supported by Adobe."
  s.description  = <<-DESC
                   By using the Adobe Cloud Platform SDKs (“Beta”), you hereby acknowledge that the Beta is provided “as is” without warranty of any kind. Adobe shall have no obligation to maintain, correct, update, change, modify or otherwise support the Beta. You are advised to use caution and not to rely in any way on the correct functioning or performance of such Beta and/or accompanying materials.

                   The Audience Manager framework provides APIs that allow use of Adobe Audience Manager in the V5 Adobe Experience Cloud SDK.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :text => "Adobe Systems, Incorporated.  All Rights Reserved."}
  s.author       = "Adobe Cloud Platform SDK Team"
  s.source       = { :git => 'https://github.com/Adobe-Marketing-Cloud/acp-sdks.git', :tag => "v1.0.2beta-ACPAudience" }
  s.platform     = :ios, '10.0'

  s.default_subspec = 'iOS'

  # dependency on the core framework
  s.dependency "ACPCoreBeta", ">= 1.0.2beta"

  s.subspec 'iOS' do |ios|
    ios.vendored_frameworks = 'ACPAudience_iOS.framework'
    ios.xcconfig = {
      "FRAMEWORK_SEARCH_PATHS" => "'${PODS_ROOT}/ACPAudienceBeta'",
      "LD_RUNPATH_SEARCH_PATHS" => "@loader_path/../Frameworks"
    }
    ios.requires_arc = true
  end
end
