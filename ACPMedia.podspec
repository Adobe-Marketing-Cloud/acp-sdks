Pod::Spec.new do |s|
  s.name         = "ACPMedia"
  s.version      = "2.3.1"
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
  s.ios.deployment_target = "10.0"
  s.tvos.deployment_target = "10.0"
  s.requires_arc = true
  s.static_framework = true
  s.cocoapods_version = ">= 1.10"

  # dependency on the core framework
  s.dependency "ACPCore", ">= 2.9.0"

  s.subspec "xcframeworks" do |f|
     f.ios.vendored_frameworks = "#{s.name}.xcframework"
     f.ios.source_files = "#{s.name}.xcframework/ios-arm64_armv7_armv7s/Headers/*.h", "include/*.m"
     f.ios.libraries = "sqlite3.0", "z", "c++"

     f.tvos.vendored_frameworks = "#{s.name}TV.xcframework"
     f.tvos.source_files = "#{s.name}TV.xcframework/tvos-arm64/Headers/*.h", "include/*.m"
     f.tvos.libraries = "sqlite3.0", "z", "c++"
  end

end
