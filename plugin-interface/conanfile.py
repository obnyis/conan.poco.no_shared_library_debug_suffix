from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps


class plugininterfaceRecipe(ConanFile):
    name = "plugininterface"
    version = "1.0"
    package_type = "header-library"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "include/*"

    def layout(self):
        cmake_layout(self)

    # same package ID for any package
    def package_id(self):
        self.info.clear()

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        # header_only - no build

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def requirements(self):
        self.requires("poco/1.12.4", transitive_headers=True)
