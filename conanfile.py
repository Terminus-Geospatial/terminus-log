#    File:    conanfile.py
#    Author:  Marvin Smith
#    Date:    7/8/2023
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps
from conan.tools.files import copy

class ConanProject(ConanFile):

    name = "terminus_log"
    version = "0.0.4"

    license = "Terminus Proprietary"
    author  = "Marvin Smith <marvin_smith1@me.com>"
    url     = "https://bitbucket.org/msmith81886/terminus-log/src"
    description = "Standardized, extensible, and customizable logging"
    topics = ("terminus","log")

    options = { "shared": [True, False],
                "with_tests": [True, False],
                "with_docs": [True, False],
                "with_coverage": [True, False],
                "use_source_location": [True, False],
                "use_source_location_hack": [True, False],
                "use_external_boost": [True,False]
    }

    default_options = { "shared": True,
                        "with_tests": True,
                        "with_docs": True,
                        "with_coverage": False,
                        "use_source_location": False,
                        "use_source_location_hack": False,
                        "use_external_boost": False,
                        "boost/*:shared": True
    }

    settings = "os", "compiler", "build_type", "arch"

    def build_requirements(self):
        self.test_requires("gtest/1.14.0")
        self.tool_requires("terminus_cmake/1.0.1")

    def requirements(self):
        if not self.options.use_external_boost:
            self.requires("boost/1.85.0")

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.configure()
        return cmake

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CONAN_PKG_NAME"]        = self.name
        tc.variables["CONAN_PKG_VERSION"]     = self.version
        tc.variables["CONAN_PKG_DESCRIPTION"] = self.description
        tc.variables["CONAN_PKG_URL"]         = self.url

        tc.variables["TERMINUS_LOG_ENABLE_TESTS"]    = self.options.with_tests
        tc.variables["TERMINUS_LOG_ENABLE_DOCS"]     = self.options.with_docs
        tc.variables["TERMINUS_LOG_ENABLE_COVERAGE"] = self.options.with_coverage

        if self.options.use_source_location:
            tc.variables["TERMINUS_LOG_SOURCE_LOCATION_METHOD"] = "0"
        elif not self.options.use_source_location and not self.options.use_source_location_hack:
            tc.variables["TERMINUS_LOG_SOURCE_LOCATION_METHOD"] = "2"
        elif not self.options.use_source_location and self.options.use_source_location_hack:
            tc.variables["TERMINUS_LOG_SOURCE_LOCATION_METHOD"] = "1"
        else:
            raise Exception("Unknown state")
        print("TERMINUS_LOG_SOURCE_LOCATION_METHOD: ", tc.variables["TERMINUS_LOG_SOURCE_LOCATION_METHOD"])

        tc.generate()

        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

    def package_info(self):
        # For header-only packages, libdirs and bindirs are not used
         # so it's necessary to set those as empty.
         self.cpp_info.bindirs = []
         self.cpp_info.libdirs = []

    def package_id(self):
        self.info.clear()

    def export_sources(self):

        for p in [ "CMakeLists.txt", "include/*", "src/*", "test/*", "README.md" ]:
            copy( self,
                  p,
                  self.recipe_folder,
                  self.export_sources_folder )
