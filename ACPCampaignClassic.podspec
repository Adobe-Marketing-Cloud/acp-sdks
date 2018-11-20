Pod::Spec.new do |s|
  s.name         = "ACPCampaignClassic"
  s.version      = "1.0.0"
  s.summary      = "Campaign Classic framework for Adobe Experience Cloud SDK. Written and maintained by Adobe."
  s.description  = <<-DESC
                   The campaign classic framework provides APIs that allow use of the Campaign Classic product in the V5 Adobe Experience Cloud SDK.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :text => "Adobe Systems, Incorporated.  All Rights Reserved."}
  s.author       = "Adobe Mobile SDK Team"
  s.source       = { :git => 'https://github.com/Adobe-Marketing-Cloud/acp-sdks.git', :tag => "v1.0.0-ACPCampaignClassic" }
  s.platform     = :ios, '10.0'

  # dependency on the core framework
  s.dependency "ACPCore", "~> 1.0"

  s.subspec 'iOS' do |ios|
    ios.vendored_frameworks = 'ACPCampaignClassic_iOS.framework'
    ios.xcconfig = {
      "FRAMEWORK_SEARCH_PATHS" => "'${PODS_ROOT}/ACPCampaignClassic'",
      "LD_RUNPATH_SEARCH_PATHS" => "@loader_path/../Frameworks"
    }
    ios.requires_arc = true
  end
end
