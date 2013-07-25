cmake_minimum_required(VERSION 2.8)

PROJECT(WebView)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5WebKitWidgets)
# Tell CMake to create the helloworld executable
add_executable(WebView main.cpp)

# Use the Widgets module from Qt 5.
qt5_use_modules(WebView Widgets WebKitWidgets)
