Pod::Spec.new do |s|
  s.name         = "ACPMedia"
  s.version      = "2.1.0"
  s.summary      = "Media library for Adobe Experience Platform SDK. Written and maintained by Adobe."
  s.description  = <<-DESC
                   The Media library provides APIs that allow analytics tracking for audio and video in the Adobe Experience Platform SDK.
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
  s.static_framework = true
  s.default_subspec = "iOS"

  # dependency on the core framework
  s.dependency "ACPCore", ">= 2.3.3"

  s.subspec "iOS" do |ios|
    ios.vendored_libraries = "libACPMedia_iOS.a"
    ios.source_files = "include/*.h", "include/*.m"
  end

end
