Pod::Spec.new do |s|
  s.name         = "ACPPlacesMonitor"
  s.version      = "0.0.1"
  s.summary      = "Places monitor for Adobe Experience Cloud SDK. Written and maintained by Adobe."
  s.description  = <<-DESC
                   The Places monitor provides native geolocation functionality, enabling use of the Places product in the V5 Adobe Experience Cloud SDK.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :file => "LICENSE.md"}
  s.author       = "Adobe Experience Platform SDK Team"
  s.source       = {
  	:git => 'https://github.com/Adobe-Marketing-Cloud/acp-sdks.git',
  	:tag => "v#{s.version}-#{s.name}"
  }

  s.platform = :ios, "10.0"
  s.requires_arc = true
  s.static_framework = true
  s.default_subspec = "iOS"

  # dependency on the core library
  s.dependency "ACPCore", ">= 2.0.3"
  s.dependency "ACPPlaces"

  s.subspec "iOS" do |ios|
    ios.vendored_libraries = "libACPPlacesMonitor_iOS.a"
    ios.source_files = "include/*.h", "include/*.m"
    ios.frameworks = "CoreLocation"
  end

end
