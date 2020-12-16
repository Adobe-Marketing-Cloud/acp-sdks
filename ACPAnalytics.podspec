Pod::Spec.new do |s|
  s.name         = "ACPAnalytics"
  s.version      = "2.5.0"
  s.summary      = "Analytics library for Adobe Experience Platform SDK. Written and maintained by Adobe."
  s.description  = <<-DESC
                   The Analytics library provides APIs that allow use of the Analytics product in the Adobe Experience Platform SDK.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :file => "LICENSE.md"}
  s.author       = "Adobe Experience Platform SDK Team"
  s.source       = {
  	:git => 'https://github.com/Adobe-Marketing-Cloud/acp-sdks.git',
  	:tag => "v#{s.version}-#{s.name}"
  }

  s.ios.deployment_target = "10.0"
  s.tvos.deployment_target = "10.0"
  s.requires_arc = true
  s.static_framework = true
  s.default_subspec = "main"

  # dependency on the core library
  s.dependency "ACPCore", ">= 2.5.0"

  s.subspec "main" do |th|
    th.ios.vendored_libraries = "libACPAnalytics_iOS.a"
    th.ios.source_files = "include/*.h", "include/*.m"

    th.tvos.vendored_libraries = "libACPAnalytics_tvOS.a"
    th.tvos.source_files = "include/*.h", "include/*.m"
  end

end
