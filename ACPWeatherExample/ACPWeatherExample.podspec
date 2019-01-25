Pod::Spec.new do |s|
  s.name         = "ACPWeatherExample"
  s.version      = "1.0.0b"
  s.summary      = "Sample weather extension for Adobe ACP SDK."
  s.description  = <<-DESC
                   The ACPWeatherExample pod is a simple demonstration of how you can write your own custom extension to integrate with the ACP SDK.
                   DESC

  s.homepage     = "https://git.corp.adobe.com/sbenedic/v5-podspecs"

  s.license      = {:type => "Commercial", :text => "Adobe Inc.  All Rights Reserved."}
  s.author       = "Adobe Mobile SDK Team"
  s.source       = { :git => 'git@git.corp.adobe.com:sbenedic/v5-podspecs.git', :tag => "v1.0.0b-ACPWeatherExample" }
  s.platform     = :ios, '10.0'

  # dependency on the core framework
  s.dependency "ACPCore"

  s.source_files = "ACPWeatherExample/*.{h,m}"
  s.resources = "ACPWeatherExample/assets/*"

  s.requires_arc = true

end
