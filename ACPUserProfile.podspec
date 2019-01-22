Pod::Spec.new do |s|
  s.name         = "ACPUserProfile"
  s.version      = "2.0.0"
  s.summary      = "User Profile library for Adobe Cloud Platform SDK. Written and Supported by Adobe."
  s.description  = <<-DESC
                   The User Profile library provides APIs that allow use of the custom client-side User Profile in the Adobe Cloud Platform SDK.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :file => "LICENSE.md"}
  s.author       = "Adobe Cloud Platform SDK Team"
  s.source       = {
    :git => "https://github.com/Adobe-Marketing-Cloud/acp-sdks.git",
    :tag => "v2.0.0-ACPUserProfile"
  }
  s.platform     = :ios, "10.0"
  s.requires_arc = true
  s.default_subspec = "iOS"

  # dependency on the core framework
  s.dependency "ACPCore", "~> 2.0"

  s.subspec "iOS" do |ios|
    ios.vendored_libraries = "libACPUserProfile_iOS.a"
    ios.source_files = "include/*.h"    
  end
end
