Pod::Spec.new do |s|
  s.name         = "ACPAnalytics"
  s.version      = "2.0.0"
  s.summary      = "Analytics library for Adobe Experience Cloud SDK. Written and maintained by Adobe."
  s.description  = <<-DESC
                   The Analytics library provides APIs that allow use of the Analytics product in the V5 Adobe Experience Cloud SDK.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :text => "Adobe.  All Rights Reserved."}
  s.author       = "Adobe Mobile SDK Team"
  s.source       = {
  	:git => 'https://github.com/Adobe-Marketing-Cloud/acp-sdks.git',
  	:tag => "v#{s.version}-#{s.name}"
  }

  s.platform = :ios, "10.0"
  s.requires_arc = true
  s.default_subspec = "iOS"

  # dependency on the core framework
  s.dependency "ACPCore", "~> 2.0"

  s.subspec "iOS" do |ios|
    ios.vendored_libraries = "iOS/libACPAnalytics_iOS.a"
    ios.source_files = "iOS/include/*.h"
  end

end