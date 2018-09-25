Pod::Spec.new do |s|
  s.name         = "ACPAcquisition"
  s.version      = "0.0.1"
  s.summary      = "Acquisition framework for Adobe Cloud Platform SDK. Written and Supported by Adobe."
  s.description  = <<-DESC
                   The Acquisition framework provides APIs that allow use of acquisition and Adobe link features in the Adobe Cloud Platform SDK.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :file => "LICENSE.md"}
  s.author       = "Adobe Cloud Platform SDK Team"
  s.source       = { :git => 'https://github.com/Adobe-Marketing-Cloud/acp-sdks.git', :tag => "v0.0.1-ACPAcquisition" }
  s.platform     = :ios, '10.0'

  s.default_subspec = 'iOS'

  # dependency on the core framework
  # release day dependency
  #s.dependency "ACPCore", "~> 1.0"
  # testing dependency
  s.dependency "ACPCore", "~> 0.0.1"

  s.subspec 'iOS' do |ios|
    # ios.vendored_frameworks = 'ACPAcquisition_iOS.framework'
    # ios.xcconfig = {
    #   "FRAMEWORK_SEARCH_PATHS" => "'${PODS_ROOT}/ACPAcquisition'",
    #   "LD_RUNPATH_SEARCH_PATHS" => "@loader_path/../Frameworks"
    # }
    ios.requires_arc = true
  end
end
