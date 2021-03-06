INCLUDE_DIRECTORIES(${DEPENDENCIES_PATH}/zlib)
INCLUDE_DIRECTORIES(${DEPENDENCIES_PATH}/freetype/include)
INCLUDE_DIRECTORIES(${DEPENDENCIES_PATH}/angelscript/include)
INCLUDE_DIRECTORIES(${DEPENDENCIES_PATH}/asJIT)
INCLUDE_DIRECTORIES(${DEPENDENCIES_PATH}/libiconv/include)
INCLUDE_DIRECTORIES(${DEPENDENCIES_PATH}/glfw/include)
INCLUDE_DIRECTORIES(${DEPENDENCIES_PATH}/android_native_app_glue)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH})

OPTION(BUILD_INPUT "on for use off for ignore" ON)
OPTION(BUILD_BASEGAME "on for use off for ignore" ON)
OPTION(BUILD_PHYSIC "on for use off for ignore" ON)
OPTION(BUILD_RENDERER "on for use off for ignore" ON)
OPTION(BUILD_SOUND "on for use off for ignore" ON)

SET(BUILD_GUI 1 CACHE STRING
"Specify the GUI. Possible values:
  0 - None
  1 - IMGUI
  2 - MYGUI
  3 - IMGUI & MYGUI"
)

ADD_DEFINITIONS(-D_BUILD_DLL_EXPORT)
ADD_DEFINITIONS(-D_ALLOW_KEYWORD_MACROS)

ADD_SUBDIRECTORY(libplatform)
ADD_SUBDIRECTORY(libimage)
ADD_SUBDIRECTORY(libmodel)

IF(CMAKE_GENERATOR MATCHES "Visual Studio")
    IF(${CMAKE_VS_PLATFORM_TOOLSET} STREQUAL "v140_clang_3_7")
        SET(BUILD_PHYSIC FALSE)
        SET(BUILD_SOUND FALSE)
    ENDIF()
ENDIF()

IF(BUILD_INPUT)
    ADD_DEFINITIONS(-D_BUILD_INPUT)
    ADD_SUBDIRECTORY(libinput)
ENDIF()

IF(BUILD_PHYSIC)
    ADD_DEFINITIONS(-D_BUILD_PHYSIC)
    ADD_SUBDIRECTORY(libphysic)
ENDIF()

IF(BUILD_SOUND)
    ADD_DEFINITIONS(-D_BUILD_SOUND)
    ADD_SUBDIRECTORY(libsound)
ENDIF()

IF(BUILD_GUI)
    ADD_DEFINITIONS(-D_BUILD_GUI)
    ADD_SUBDIRECTORY(libgui)
ENDIF()

IF(BUILD_BASEGAME)
    ADD_DEFINITIONS(-D_BUILD_BASEGAME)
ENDIF()

IF(BUILD_SCRIPT)
    ADD_DEFINITIONS(-D_BUILD_SCRIPT)
ENDIF()

IF(BUILD_RENDERER)
    ADD_DEFINITIONS(-D_BUILD_RENDERER)
    ADD_SUBDIRECTORY(lib3d)
    ADD_SUBDIRECTORY(librenderer)
ENDIF()

ADD_SUBDIRECTORY(engine)