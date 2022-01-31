cmake_minimum_required(VERSION 3.16)

project(eBiblis VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 6.2 COMPONENTS Widgets Core Quick Core5Compat REQUIRED)
find_package(Qt6 6.2 COMPONENTS WebView Sql)
find_package(ZLIB)
include_directories(quazip)

#target_include_directories(appBookManager PUBLIC
	#"${CMAKE_CURRENT_SOURCE_DIR}/quazip")

qt_add_executable(appBookManager
    main.cpp
    homemodel.cpp
		librarymodel.cpp
    homequeries.cpp
    libraryqueries.cpp
		bookparsers.cpp
		ioutil.cpp

    homemodel.h
		librarymodel.h
		bookparsers.h
		ioutil.h
    homequeries.h
    libraryqueries.h
		constants.h

    structs.h
    resources/web.qrc
    android/AndroidManifest.xml

		)
qt_add_qml_module(appBookManager
    URI BookManager
    VERSION 1.0
    QML_FILES
        main.qml
				EpubReader.qml
				HomeView.qml
				LibraryView.qml
				AddLibrary.qml
)
set(ANDROID_PACKAGE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/android CACHE INTERNAL "")

target_compile_definitions(appBookManager
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(appBookManager PUBLIC
    Qt6::Quick
		Qt6::Widgets
    Qt6::Sql
		Qt6::WebView
		Qt6::Core5Compat
		"${PROJECT_SOURCE_DIR}/lib/quazip/libquazip1-qt6.so"
		)

