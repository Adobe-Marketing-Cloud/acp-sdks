Pod::Spec.new do |s|
  s.name         = "ACPAcquisition"
  s.version      = "2.0.0"
  s.summary      = "Acquisition library for Adobe Experience Cloud SDK. Written and maintained by Adobe."
  s.description  = <<-DESC
                   The Acquisition library provides APIs that allow use of the Acquisition product in the V5 Adobe Experience Cloud SDK.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :file => "LICENSE.md"}
  s.author       = "Adobe Experience Platform SDK Team"
  s.source       = { :git => 'https://github.com/Adobe-Marketing-Cloud/acp-sdks.git', :tag => "v2.0.0-ACPAcquisition" }
  s.platform     = :ios, '10.0'
  s.requires_arc = true

  s.default_subspec = 'iOS'

  s.dependency "ACPCore", "~> 2.0"

  s.subspec "iOS" do |ios|
    ios.vendored_libraries = "libACPAcquisition_iOS.a"
    ios.source_files = "include/*.h"
  end

end
