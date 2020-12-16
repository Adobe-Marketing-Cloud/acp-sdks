Pod::Spec.new do |s|
  s.name         = "ACPPlaces"
  s.version      = "1.4.0"
  s.summary      = "Places extension for Adobe Experience Platform SDK. Written and maintained by Adobe."
  s.description  = <<-DESC
                   The Places extension provides APIs that allow use of the Places service in the Adobe Experience Platform SDK.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :file => "LICENSE.md"}
  s.author       = "Adobe Experience Platform SDK Team"
  s.source       = {
  	:git => 'https://github.com/Adobe-Marketing-Cloud/acp-sdks.git',
  	:tag => "v#{s.version}-#{s.name}"
  }

  s.ios.deployment_target = "10.0"
  s.default_subspec = "xcframeworks"
  s.requires_arc = true
  s.static_framework = true
  s.cocoapods_version = ">= 1.10"
  s.xcconfig = { "HEADER_SEARCH_PATHS" => "${PROJECT_DIR}/**" }

  # dependency on the core library
  s.dependency "ACPCore", ">= 2.9.0"

  s.subspec "xcframeworks" do |f|
    f.ios.vendored_frameworks = "#{s.name}.xcframework"
    f.ios.source_files = "include/*.h", "include/*.m"
    f.ios.frameworks = "UIKit", "SystemConfiguration", "CoreLocation"
    f.ios.libraries = "sqlite3.0", "z", "c++"
  end
end
