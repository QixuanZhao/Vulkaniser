cmake_minimum_required(VERSION 3.16)

project(Vulkaniser VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core)
find_package(Vulkan REQUIRED)
find_package(slang CONFIG HINTS "$ENV{VULKAN_SDK}/lib/cmake")

qt_standard_project_setup()

qt_add_executable(Vulkaniser
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.ui
    src/UI/TrialVulkanWindow/TrialVulkanWindow.cpp
    src/UI/TrialVulkanWidget/TrialVulkanWidget.cpp
    src/Utilities/VulkanUtility.cpp
    src/Global/VulkanManager.cpp
    src/Renderer/Renderer.cpp
    src/UI/VulkanExtensionList/VulkanExtensionListView.cpp
    src/UI/VulkanExtensionList/VulkanExtensionListModel.cpp
    src/UI/About/AboutWindow.cpp
    src/UI/About/AboutWindow.ui
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
