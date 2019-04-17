
Pod::Spec.new do |s|
  s.name         = "ACPGriffonBeta"
  s.version      = "0.0.9"
  s.summary      = "BETA - Project Griffon framework for Adobe Experience Cloud SDK. Official Pod for Project Griffon Beta."
  s.description  = <<-DESC
                   By using the Adobe Cloud Platform SDKs (“Beta”), you hereby acknowledge that the Beta is provided “as is” without warranty of any kind. Adobe shall have no obligation to maintain, correct, update, change, modify or otherwise support the Beta. You are advised to use caution and not to rely in any way on the correct functioning or performance of such Beta and/or accompanying materials.
                   The Project Griffon frameworks provide APIs that allow use of Project Griffon in the V5 Adobe Experience Cloud SDK.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :text => "Adobe Systems, Incorporated.  All Rights Reserved."}
  s.author       = "Adobe Cloud Platform SDK Team"
  s.source       = { :git => 'https://github.com/Adobe-Marketing-Cloud/acp-sdks.git', :tag => "v0.0.9-ACPGriffonBeta" }
  s.platform     = :ios, '10.0'

  s.default_subspec = 'iOS'

  s.dependency "ACPCore", "~> 2.1.1"

  s.subspec 'iOS' do |ios|
    ios.vendored_libraries = "libProjectGriffon.a", "libACPGriffonBridge_iOS.a"
    ios.source_files = "include/*.h"
  end
end