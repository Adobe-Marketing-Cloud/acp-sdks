Pod::Spec.new do |s|
  s.name         = "ACPCampaign"
  s.version      = "1.0.1"
  s.summary      = "Campaign library for Adobe Experience Cloud SDK. Written and maintained by Adobe."
  s.description  = <<-DESC
                   The Campaign library provides APIs that allow use of the Campaign product in the Adobe Experience Cloud SDK.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :file => "LICENSE.md"}
  s.author       = "Adobe Experience Platform SDK Team"
  s.source       = { :git => 'https://github.com/Adobe-Marketing-Cloud/acp-sdks.git', :tag => "v#{s.version}-#{s.name}" }
  s.platform = :ios, "10.0"
  s.requires_arc = true

  s.default_subspec = "iOS"
  s.static_framework = true

  s.dependency "ACPCore", "~> 2.0"

  s.subspec "iOS" do |ios|
    ios.vendored_libraries = "libACPCampaign_iOS.a"
    ios.source_files = "include/*.h", "include/*.m"
  end
end
