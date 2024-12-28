from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.build import check_max_cppstd, check_min_cppstd
from conan.tools.scm import Git


class resource_utilsRecipe(ConanFile):
    name = "resource_utils"
    version = "1.0"
    package_type = "library"

    # Optional metadata
    license = "MIT"
    author = "Zhivko Petrov"
    url = "https://github.com/zhivkopetrov/resource_utils"
    description = "A static C++ library, which provides auto-generated description for assets"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False], "disable_ros_tooling": [True, False]}
    default_options = {"shared": False, "fPIC": False, "disable_ros_tooling": True}
    
    def validate(self):
        check_min_cppstd(self, "20")
        check_max_cppstd(self, "20")
        
    def requirements(self):
        self.requires("utils/1.0")
    
    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")
            
    def source(self):
        branch_name = "conan_test"
        git = Git(self)
        git.clone(url=self.url + ".git", target=".")
        git.checkout(branch_name) # TODO: pin a version
        
        target_dir = "cmake_helpers"
        git.clone("https://github.com/zhivkopetrov/cmake_helpers.git", target=target_dir)
        self.run(f"git checkout {branch_name}", cwd=target_dir) # TODO: pin a version

    def layout(self):
        cmake_layout(self)
    
    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        
        tc = CMakeToolchain(self)
        tc.variables["DISABLE_ROS_TOOLING"] = "ON" if self.options.disable_ros_tooling else "OFF"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["resource_utils"]

