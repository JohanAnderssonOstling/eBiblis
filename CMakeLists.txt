cmake_minimum_required(VERSION 3.16)

project(BookManager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 6.2 COMPONENTS Widgets Core Quick REQUIRED)
find_package(Qt6 6.2 COMPONENTS WebView Sql)


qt_add_executable(appBookManager
    main.cpp
    homemodel.cpp
		librarymodel.cpp
    homequeries.cpp
    libraryqueries.cpp
		bookparsers.cpp


    homemodel.h
		librarymodel.h
		bookparsers.h

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
		${CMAKE_SOURCE_DIR}/lib/libz.a
		${CMAKE_SOURCE_DIR}/lib/libarchive.a
		${CMAKE_SOURCE_DIR}/lib/libminizip.a)
