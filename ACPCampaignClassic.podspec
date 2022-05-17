Pod::Spec.new do |s|
  s.name         = "ACPCampaignClassic"
  s.version      = "2.1.1"
  s.summary      = "Campaign Classic library for Adobe Experience Cloud SDK. Written and maintained by Adobe."
  s.description  = <<-DESC
                   The campaign classic library provides APIs that allow use of the Campaign Classic product in the Adobe Experience Cloud SDK.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :file => "LICENSE.md"}
  s.author       = "Adobe Experience Platform SDK Team"
  s.source       = { :git => 'https://github.com/Adobe-Marketing-Cloud/acp-sdks.git', :tag => "v#{s.version}-#{s.name}" }
  s.platform = :ios, "10.0"
  s.requires_arc = true

  s.default_subspec = "xcframeworks"
  s.static_framework = true
  s.cocoapods_version = ">= 1.10"

  # dependency on the core library
  s.dependency "ACPCore", '>= 2.9.0'

  s.subspec "xcframeworks" do |f|
    f.ios.vendored_frameworks = "#{s.name}.xcframework"
    f.ios.source_files = "#{s.name}.xcframework/ios-arm64_armv7_armv7s/Headers/*.h", "include/*.m"
    f.ios.libraries = "sqlite3.0", "z", "c++"
  end
end
