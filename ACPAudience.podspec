Pod::Spec.new do |s|
  s.name         = "ACPAudience"
  s.version      = "1.1.0"
  s.summary      = "Audience Manager framework for Adobe Experience Platform SDK. Written and Supported by Adobe."
  s.description  = <<-DESC
                   The Audience Manager framework provides APIs that allow use of Adobe Audience Manager in the Adobe Cloud Platform SDK.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :file => "LICENSE.md"}
  s.author       = "Adobe Experience Platform SDK Team"
  s.source       = { :git => 'https://github.com/Adobe-Marketing-Cloud/acp-sdks.git', :tag => "v1.1.0-ACPAudience" }
  s.platform     = :ios, '10.0'

  s.default_subspec = 'iOS'

  # dependency on the core framework
  s.dependency "ACPCore", "~> 1.0"

  s.subspec 'iOS' do |ios|
    ios.vendored_frameworks = 'ACPAudience_iOS.framework'
    ios.xcconfig = {
      "FRAMEWORK_SEARCH_PATHS" => "'${PODS_ROOT}/ACPAudience'",
      "LD_RUNPATH_SEARCH_PATHS" => "@loader_path/../Frameworks"
    }
    ios.requires_arc = true
  end
end
