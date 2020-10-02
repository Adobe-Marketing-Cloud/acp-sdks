Pod::Spec.new do |s|
  s.name         = "AEPAssurance"
  s.version      = "1.0.0"
  s.summary      = "AEPAssurance SDK for Adobe Experience Cloud. Written and maintained by Adobe."
  s.description  = <<-DESC
                   AEPAssurance SDK provides APIs that allow use of the AEPAssurance product in conjunction with the Adobe Experience platform solutions.
                   DESC

  s.homepage     = "https://git.corp.adobe.com/dms-mobile/v5-podspecs"

  s.license      = {:type => "Commercial", :text => "Adobe.  All Rights Reserved."}
  s.author       = "Adobe Mobile SDK Team"
  s.source       = { :git => 'git@git.corp.adobe.com:dms-mobile/v5-ios-builds.git', :tag => "v#{s.version}-#{s.name}" }

  s.platform = :ios, "10.0"
  s.requires_arc = true
  s.static_framework = true
  s.default_subspec = "iOS"
  s.dependency "ACPCore"

  s.subspec "iOS" do |ios|
    ios.vendored_libraries = "iOS/libAEPAssurance_iOS.a"
    ios.source_files = "iOS/include/*.h"
    ios.frameworks = "UIKit", "SystemConfiguration"
    ios.libraries = "c++", "z"
  end
end
