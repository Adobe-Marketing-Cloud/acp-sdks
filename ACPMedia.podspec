Pod::Spec.new do |s|
  s.name         = "ACPMedia"
  s.version      = "2.1.1"
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
  s.default_subspec = "main"

  # dependency on the core framework
  s.dependency "ACPCore", ">= 2.7.0"

  s.subspec "main" do |th|
    th.ios.vendored_libraries = "libACPMedia_iOS.a"
    th.ios.source_files = "include/*.h", "include/*.m"

    th.tvos.vendored_libraries = "libACPMedia_tvOS.a"
    th.tvos.source_files = "include/*.h", "include/*.m"
  end

end
