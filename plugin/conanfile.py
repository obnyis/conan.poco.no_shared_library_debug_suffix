import os
from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.files import copy


class pluginRecipe(ConanFile):
    name = "plugin"
    version = "1.0"
    package_type = "shared-library"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": True, "fPIC": True}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*"

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def deploy(self):
        if self.package_folder:
            copy(self, "*", os.path.join(self.package_folder, "lib"), os.path.join(self.deploy_folder, "lib"))

    def package_info(self):
        self.cpp_info.libs = ["plugin"]

    def requirements(self):
        self.requires("poco/1.12.4")
        self.requires("plugininterface/1.0")
