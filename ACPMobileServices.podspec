Pod::Spec.new do |s|
  s.name         = "ACPMobileServices"
  s.version      = "1.0.0"
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

  s.default_subspec = 'iOS'
  s.static_framework = true

  s.dependency "ACPCore", "~> 2.1.1"
  s.dependency "ACPAnalytics", "~> 2.0.3"

  s.subspec "iOS" do |ios|
    ios.vendored_libraries = "libACPMobileServices_iOS.a"
    ios.source_files = "include/*.h", "include/Empty.m"
  end

end