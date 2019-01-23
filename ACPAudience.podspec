Pod::Spec.new do |s|
  s.name         = "ACPAudience"
  s.version      = "2.0.0"
  s.summary      = "Audience Manager library for Adobe Experience Platform SDK. Written and maintained by Adobe."
  s.description  = <<-DESC
                   The Audience Manager library provides APIs that allow use of the Audience Manager product in the Adobe Experience Platform SDK.
                   DESC

  s.homepage     = "https://github.com/Adobe-Marketing-Cloud/acp-sdks/releases"

  s.license      = {:type => "Commercial", :file => "LICENSE.md"}
  s.author       = "Adobe Experience Platform SDK Team"
  s.source       = {
    :git => 'https://github.com/Adobe-Marketing-Cloud/acp-sdks.git',
    :tag => "v#{s.version}-#{s.name}"
  }
  s.platform     = :ios, '10.0'
  s.requires_arc = true
  s.static_framework = true
  s.default_subspec = 'iOS'

  # dependency on the core library
  s.dependency "ACPCore", "~> 2.0"

  s.subspec 'iOS' do |ios|
    ios.vendored_libraries = "libACPAudience_iOS.a"
    ios.source_files = "include/*.h", "include/*.m"
  end
end
