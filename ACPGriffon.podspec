Pod::Spec.new do |s|
  s.name         = "ACPGriffon"
  s.version      = "1.0.1"
  s.summary      = "Project Griffon SDK for Adobe Experience Cloud. Written and maintained by Adobe."
  s.description  = <<-DESC
                   The Project Griffon SDK provides APIs that allow use of the Project Griffon product in conjunction with the Adobe Experience Cloud solutions.
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
  s.dependency "ACPCore"

  s.subspec "iOS" do |ios|
    ios.vendored_libraries = "libACPGriffon_iOS.a"
    ios.source_files = "include/*.h"
    ios.frameworks = "UIKit", "SystemConfiguration"
    ios.libraries = "c++", "z"
  end


end
