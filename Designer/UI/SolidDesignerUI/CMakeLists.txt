##########################################################################################################
#--Date:    2023.01.24
#--Project: SolidDesignerUI
#--Author:  hananiah
##########################################################################################################
message("*--*--*--*--*--*--*--*--*--*--*--*--*--Start SolidDesigner UI--*--*--*--*--*--*--*--*--*--*--**--*--*--*")

add_definitions(-DSOLID_DESIGNER_UI_HOME)
add_definitions(-DALICE_BASIC_SERVICE_HOME)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH "C:/Qt/Qt5.15.14/5.15.14/msvc2019_64")
find_package(Qt5Core       5.13 REQUIRED)
find_package(Qt5Gui        5.13 REQUIRED)
find_package(Qt5Widgets    5.13 REQUIRED)


message("${PROJECT_SOURCE_DIR}")


FILE(GLOB SOURCE_FILES "${PROJECT_SOURCE_DIR}/Designer/UI/SolidDesignerUI/*.cpp")
FILE(GLOB HEADER_FILES "${PROJECT_SOURCE_DIR}/Designer/UI/SolidDesignerUI/*.h")

#source_group("" FILES ${SOURCE_FILES})
#source_group("" FILES ${HEADER_FILES})


set(RESOURCES ${PROJECT_SOURCE_DIR}/Designer/UI/SolidDesignerUI/StyleTemplate.qrc)
source_group("resources" FILES ${RESOURCES})


#-----------------------------------------------------------------------------
# 库文件链接路径(ALICE_LibDir 在上级定义了)
#-----------------------------------------------------------------------------
link_directories(${ALICE_LibDir})

#-----------------------------------------------------------------------------
# 头文件搜索路径
#-----------------------------------------------------------------------------
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Alice/Core/Foundation/AliceBasicService/Public)

#=============================================================================
#指定工程为动态库程序
add_library(SolidDesignerUI SHARED ${SOURCE_FILES} ${HEADER_FILES})
#设定工程的过滤器
set_target_properties(SolidDesignerUI PROPERTIES FOLDER "Designer/UI")
#=============================================================================


#-----------------------------------------------------------------------------
# 根据系统及机器位数设置链接的位数
# 必须放在link之后,否则设置无效
#-----------------------------------------------------------------------------
set(CMAKE_SHARED_LINKER_FLAGS "/machine:x64")


if(WIN32)
    # include the major version number in Windows shared library names (but not import library names)
    set_target_properties(SolidDesignerUI PROPERTIES DEBUG_POSTFIX "")
    set_target_properties(SolidDesignerUI PROPERTIES SUFFIX "${CMAKE_SHARED_LIBRARY_SUFFIX}")
else()
    set_target_properties(SolidDesignerUI PROPERTIES DEBUG_POSTFIX "d")
endif()
if (WIN32 AND MINGW)
    # on Windows/gcc get rid of "lib" prefix for shared libraries,
    # and transform the ".dll.a" suffix into ".a" for import libraries
    set_target_properties(SolidDesignerUI PROPERTIES PREFIX "")
    set_target_properties(SolidDesignerUI PROPERTIES IMPORT_SUFFIX ".a")
endif()

#-----------------------------------------------------------------------------
# 定义项目构建中间文件的生成目录
#-----------------------------------------------------------------------------
message("${CMAKE_BINARY_DIR}")
set(CMAKE_GENERATOR_PLATFORM x64)
if(SOLIDRENDER_WIN)
    if("${CMAKE_GENERATOR_PLATFORM}" STREQUAL "x64")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/x64/Debug)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/x64/Debug)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/x64/Debug)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/x64/Release)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/x64/Release)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/x64/Release)
    endif()

    if("${CMAKE_GENERATOR_PLATFORM}" STREQUAL "Win32")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/x86/Debug)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/x86/Debug)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/x86/Debug)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/x86/Release)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/x86/Release)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/x86/Release)
    endif()

elseif(SOLIDRENDER_LINUX)  
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
endif()



#-----------------------------------------------------------------------------
# 链接第三方的库
# @1、链接的动作需要放到add_library之后
#-----------------------------------------------------------------------------
target_link_libraries(SolidDesignerUI
    AliceBasicService
)



message("*--*--*--*--*--*--*--*--*--*--*--**--*--*--End SolidDesigner UI*--*--*--*--*--*--*--*--*--*--*--*--*--*")