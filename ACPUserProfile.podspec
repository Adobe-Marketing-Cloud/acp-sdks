Pod::Spec.new do |s|
  s.name         = "ACPUserProfile"
  s.version      = "2.2.0"
  s.summary      = "User Profile library for Adobe Experience Platform SDK. Written and Supported by Adobe."
  s.description  = <<-DESC
                   The User Profile library provides APIs that allow use of the custom client-side User Profile in the Adobe Experience Platform SDK.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :file => "LICENSE.md"}
  s.author       = "Adobe Experience Platform SDK Team"
  s.source       = {
    :git => "https://github.com/Adobe-Marketing-Cloud/acp-sdks.git",
    :tag => "v#{s.version}-#{s.name}"
  }
  s.platform     = :ios, "10.0"
  s.requires_arc = true
  s.default_subspec = "iOS"
  s.static_framework = true
  s.cocoapods_version = ">= 1.10"
  s.default_subspec = "xcframeworks"

  # dependency on the core library
  s.dependency "ACPCore", ">= 2.9.0"

  s.subspec "xcframeworks" do |f|
    f.ios.vendored_frameworks = "#{s.name}.xcframework"
    f.ios.source_files = "#{s.name}.xcframework/ios-arm64_armv7_armv7s/Headers/*.h", "include/*.m"
    f.ios.libraries = "sqlite3.0", "z", "c++"
  end
end
