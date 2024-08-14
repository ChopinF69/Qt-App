cmake_minimum_required(VERSION 3.28)
project(lab10)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(Qt6Widgets_DIR "/home/lazar/Qt/6.7.0/gcc_64/lib/cmake/Qt6Widgets")
set(Qt6CoreTools_DIR "/home/lazar/Qt/6.7.0/gcc_64/lib/cmake/Qt6CoreTools")
set(Qt6GuiTools_DIR "/home/lazar/Qt/6.7.0/gcc_64/lib/cmake/Qt6GuiTools")
find_package(Qt6Widgets REQUIRED)

# Set the path to Wayland libraries
# set(WAYLAND_CLIENT_LIBRARIES "/usr/lib/x86_64-linux-gnu")
set(WAYLAND_CLIENT_LIBRARIES "/home/lazar/Downloads//usr/lib/i386-linux-gnu")
# Set the path to Wayland include files
set(WAYLAND_INCLUDE_DIRS "home/lazar/Downloads//usr/lib/i386-linux-gnu")

# Add the Wayland library directory to the linker search paths
link_directories(${WAYLAND_CLIENT_LIBRARIES})

# Add the Wayland include directory to the include search paths
include_directories(${WAYLAND_INCLUDE_DIRS})

add_executable(lab13
        app.cpp
        domain.cpp
        domain.h
        repo.cpp
        repo.h
        service.cpp
        service.h
        ui.cpp
        ui.h
        validator/validator.h
        validator/validator.cpp
        undo.h
        newGui.h
        newGui.cpp
        observer.h
        CosCRUDGui.h
        CosReadOnlyGUI.h
        TableModel.h
        storeGUImodele.cpp
        storeGUImodele.h
)

target_link_libraries(lab13 Qt6::Widgets)
