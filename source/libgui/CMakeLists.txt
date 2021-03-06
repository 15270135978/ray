PROJECT("libgui")

SET(HEADER_PATH ${CMAKE_SOURCE_DIR}/include/ray)
SET(SOURCE_PATH ${CMAKE_SOURCE_DIR}/source/libgui)

IF(BUILD_GUI EQUAL 1 OR BUILD_GUI EQUAL 3)
	INCLUDE_DIRECTORIES(${DEPENDENCIES_PATH}/imgui)
	ADD_DEFINITIONS(-D_BUILD_IMGUI)
ENDIF()

IF(BUILD_GUI EQUAL 2 OR BUILD_GUI EQUAL 3)
    ADD_DEFINITIONS(-DMYGUI_STATIC)
    ADD_DEFINITIONS(-D_BUILD_MYGUI)
    FILE(GLOB MYGUI_LIST "MYGUI/*.*")
    SOURCE_GROUP("MyGUI" FILES ${MYGUI_LIST})

    INCLUDE_DIRECTORIES(${DEPENDENCIES_PATH}/MyGUIEngine/include)
ENDIF()

SET(GUI_LIST
    ${HEADER_PATH}/gui_imageloader.h
    ${SOURCE_PATH}/gui_imageloader.cpp
    ${HEADER_PATH}/gui_input_button.h
    ${HEADER_PATH}/gui_input_key.h
    ${SOURCE_PATH}/gui_system.cpp
    ${HEADER_PATH}/gui_system.h
    ${HEADER_PATH}/gui_types.h
    ${HEADER_PATH}/gui.h
)
SOURCE_GROUP("gui\\common" FILES ${GUI_LIST})

IF(BUILD_GUI EQUAL 1 OR BUILD_GUI EQUAL 3)
	SET(IMGUI_LIST
    ${HEADER_PATH}/imgui.h
    ${SOURCE_PATH}/imgui.cpp
    ${HEADER_PATH}/imgui_system.h
    ${SOURCE_PATH}/imgui_system.cpp
    )
	SOURCE_GROUP("gui\\IMGUI" FILES ${IMGUI_LIST})
ENDIF()

IF(BUILD_GUI EQUAL 2 OR BUILD_GUI EQUAL 3)
	SET(MYGUI_LIST
	    ${HEADER_PATH}/gui_align.h
	    ${HEADER_PATH}/gui_widget.h
	    ${SOURCE_PATH}/gui_widget.cpp
	    ${HEADER_PATH}/gui_button.h
	    ${SOURCE_PATH}/gui_button.cpp
	    ${HEADER_PATH}/gui_menu.h
	    ${SOURCE_PATH}/gui_menu.cpp
	    ${HEADER_PATH}/gui_menuitem.h
	    ${SOURCE_PATH}/gui_menuitem.cpp
	    ${HEADER_PATH}/gui_textbox.h
	    ${SOURCE_PATH}/gui_textbox.cpp
	    ${HEADER_PATH}/gui_window.h
	    ${SOURCE_PATH}/gui_window.cpp
	    ${HEADER_PATH}/gui_listbox.h
	    ${SOURCE_PATH}/gui_listbox.cpp
	    ${HEADER_PATH}/gui_editbox.h
	    ${SOURCE_PATH}/gui_editbox.cpp
	    ${HEADER_PATH}/gui_combobox.h
	    ${SOURCE_PATH}/gui_combobox.cpp
	    ${HEADER_PATH}/gui_imagebox.h
	    ${SOURCE_PATH}/gui_imagebox.cpp
	    ${HEADER_PATH}/gui_scrollbar.h
	    ${SOURCE_PATH}/gui_scrollbar.cpp
	    ${HEADER_PATH}/gui_scrollview.h
	    ${SOURCE_PATH}/gui_scrollview.cpp
	)
	SOURCE_GROUP("gui\\MYGUI" FILES ${MYGUI_LIST})
ENDIF()

ADD_LIBRARY(libgui SHARED ${GUI_LIST} ${IMGUI_LIST} ${MYGUI_LIST})

TARGET_LINK_LIBRARIES(libgui PUBLIC libplatform)
TARGET_LINK_LIBRARIES(libgui PRIVATE librenderer)

IF(BUILD_GUI EQUAL 1 OR BUILD_GUI EQUAL 3)
	TARGET_LINK_LIBRARIES(libgui PRIVATE imgui)
ENDIF()

IF(BUILD_GUI EQUAL 2 OR BUILD_GUI EQUAL 3)
	TARGET_LINK_LIBRARIES(libgui PRIVATE MyGUIEngine)
	IF(BUILD_PLATFORM_WINDOWS)
	    TARGET_LINK_LIBRARIES(libgui PRIVATE Imm32)
	ENDIF()
ENDIF()

SET_TARGET_ATTRIBUTE(libgui "core")