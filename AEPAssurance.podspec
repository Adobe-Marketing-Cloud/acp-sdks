Pod::Spec.new do |s|
  s.name         = "AEPAssurance"
  s.version      = "1.1.2"
  s.summary      = "AEPAssurance SDK for Adobe Experience Platform SDK. Written and maintained by Adobe."
  s.description  = <<-DESC
                   AEPAssurance SDK provides APIs that allow use of the AEPAssurance product in the Adobe Experience Platform SDK.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :file => "LICENSE.md"}
  s.author       = "Adobe Experience Platform SDK Team"
  s.source       = { :git => 'https://github.com/Adobe-Marketing-Cloud/acp-sdks.git', :tag => "v#{s.version}-#{s.name}" }

  s.platform = :ios, "10.0"
  s.requires_arc = true
  s.static_framework = true
  s.cocoapods_version = ">= 1.10"
  s.ios.deployment_target = "10.0"
  s.default_subspec = "xcframeworks"
  s.dependency "ACPCore", ">= 2.9.0"

  s.subspec "xcframeworks" do |f|
      f.ios.vendored_frameworks = "#{s.name}.xcframework"
      f.ios.source_files = "#{s.name}.xcframework/ios-arm64_armv7_armv7s/Headers/*.h", "include/*.m"
      f.ios.libraries = "sqlite3.0", "z", "c++"
    end
end
