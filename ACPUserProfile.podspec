Pod::Spec.new do |s|
  s.name         = "ACPUserProfile"
  s.version      = "2.0.1"
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

  # dependency on the core library
  s.dependency "ACPCore", "~> 2.0"

  s.subspec "iOS" do |ios|
    ios.vendored_libraries = "libACPUserProfile_iOS.a"
    ios.source_files = "include/*.h", "include/Empty.m"
  end
end
