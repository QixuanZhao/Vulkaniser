cmake_minimum_required(VERSION 3.16)

project(Vulkaniser VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Vulkan REQUIRED)
find_package(slang CONFIG HINTS "$ENV{VULKAN_SDK}/lib/cmake")

qt_standard_project_setup()

qt_add_executable(Vulkaniser
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.ui
    src/UI/TrialVulkanWindow/TrialVulkanWindow.cpp
)

target_precompile_headers(Vulkaniser PRIVATE src/pch.h)

target_include_directories(Vulkaniser 
    PRIVATE src
)

target_link_libraries(Vulkaniser 
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    Vulkan::Vulkan
)

set_target_properties(Vulkaniser PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Vulkaniser
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
