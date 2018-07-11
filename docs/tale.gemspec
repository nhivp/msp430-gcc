# coding: utf-8

Gem::Specification.new do |spec|
  spec.name          = "msp430-gcc"
  spec.version       = "0.1"
  spec.authors       = ["Nhi Pham"]
  spec.email         = ["vannhibka@gmail.com"]

  spec.summary       = %q{Document for MSP430 programming with GCC}
  spec.homepage      = "https://nhivp.github.io/msp430-gcc/"
  spec.license       = "None"

  spec.files         = `git ls-files -z`.split("\x0").select { |f| f.match(%r{^(assets|_layouts|_includes|_sass|README)}i) }

  spec.add_runtime_dependency "jekyll", "~> 3.6"
  spec.add_runtime_dependency "jekyll-paginate", "~> 1.1"

  spec.add_development_dependency "bundler", "~> 1.12"
  spec.add_development_dependency "rake", "~> 10.0"
end
