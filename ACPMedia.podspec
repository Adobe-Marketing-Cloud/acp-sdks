Pod::Spec.new do |s|
  s.name         = "ACPMedia"
  s.version      = "1.0.0"
  s.summary      = "Media library for Adobe Experience Cloud SDK. Written and maintained by Adobe."
  s.description  = <<-DESC
                   The Media library provides APIs that allow analytics tracking for audio and video in the V5 Adobe Experience Cloud SDK.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :file => "LICENSE.md"}
  s.author       = "Adobe Experience Platform SDK Team"
  s.source       = {
    :git => "https://github.com/Adobe-Marketing-Cloud/acp-sdks.git",
    :tag => "v1.0.0-ACPMedia"
  }
  s.platform     = :ios, '10.0'
  s.requires_arc = true
  s.default_subspec = "iOS"

  # dependency on the core framework
  s.dependency "ACPCore", "~> 2.0"

  s.subspec "iOS" do |ios|
    ios.vendored_libraries = "iOS/libACPMedia_iOS.a"
    ios.source_files = "iOS/include/*.h"
  end


end
