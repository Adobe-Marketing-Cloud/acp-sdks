Pod::Spec.new do |s|
  s.name         = "AEPMobileServices"
  s.version      = "3.0.1"
  s.summary      = "Mobile Services library for Adobe Experience Platform SDK. Written and maintained by Adobe."
  s.description  = <<-DESC
                   The Mobile Services library provides APIs that allow use of the Mobile Services product in the Adobe Experience Platform SDK.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :file => "LICENSE.md"}
  s.author       = "Adobe Experience Platform SDK Team"
  s.source       = { :git => 'https://github.com/Adobe-Marketing-Cloud/acp-sdks.git', :tag => "v#{s.version}-#{s.name}" }
  s.platform     = :ios, '10.0'
  s.requires_arc = true

  s.default_subspec = 'xcframeworks'
  s.cocoapods_version = ">= 1.10"
  s.static_framework = true
  s.swift_version = '5.1'

  s.dependency "AEPCore"

  s.subspec "xcframeworks" do |f|
    f.ios.vendored_frameworks = "#{s.name}.xcframework"
    f.ios.source_files = "#{s.name}.xcframework/ios-arm64_armv7_armv7s/Headers/*.h", "include/*.m"
  end

end

