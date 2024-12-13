cmake_minimum_required(VERSION 3.16)

project(Projet-Prog_Con VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        View/mainwindow.cpp
        View/mainwindow.h
        View/mainwindow.ui
#        Controller/controlleurChefDeRang.cpp
#        Controller/controlleurChefDeRang.h
#        Controller/controlleurCuisinier.h
#        Controller/controlleurCuisinier.h
#        Controller/controlleurMaitreHotel.cpp
#        Controller/controlleurMaitreHotel.h
#        Controller/controlleurPlongeur.cpp
#        Controller/controlleurPlongeur.h
#        Controller/controlleurServeur.cpp
#        Controller/controlleurServeur.h
#        Controller/controlleurStock.cpp
#        Controller/controlleurStock.h
        Model/chefDeRang.cpp
        Model/chefDeRang.h
        Model/cuisinier.cpp
        Model/cuisinier.h
        Model/maitreHotel.cpp
        Model/maitreHotel.h
        Model/plongeur.cpp
        Model/plongeur.h
        Model/serveur.cpp
        Model/serveur.h
        Model/stockGestion.cpp
        Model/stockGestion.h
        View/vueChefDeRang.cpp
        View/vueChefDeRang.h
        View/vueCuisinier.cpp
        View/vueCuisinier.h
        View/vueMaitreHotel.cpp
        View/vueMaitreHotel.h
        View/vuePlongeur.cpp
        View/vuePlongeur.h
        View/vueServeur.cpp
        View/vueServeur.h
        View/vueStock.cpp
        View/vueStock.h
        Tests/Test.cpp
        Tests/testChefDeRang.cpp
        Tests/testCuisinier.cpp
        Tests/testMaitreHotel.cpp
        Tests/testPlongeur.cpp
        Tests/testServeur.cpp
        Tests/testStockGestion.cpp
        Model/EtapeRecette.h
        Model/Recette.h
        Model/commis.h
        Model/commis.cpp
        Model/client.h
        Model/client.cpp
        Model/ComptoirSocket.h
        Model/ComptoirSocket.cpp
        ipc/ipc_utils.h
        ipc/ipc_utils.cpp
        Model/ressourceGestion.h
        Model/ressourceGestion.cpp
        ../Pools_/resourcePool.h
        ../Pools_/resourcePool.cpp
        Model/assiette.h
        Model/table.h
        ../Pools_/threadPool.h
        ../Pools_/threadpool.cpp
        Model/table.cpp
        Model/assiette.cpp
        Model/utils.h
        Model/utils.cpp
        Model/serviceManager.h
        Model/serviceManager.cpp
        Model/chefDeCuisine.h
        Model/chefDeCuisine.cpp
        Model/EtapeRecette.cpp
        Model/dressage.h
        Model/carte_restaurant.h
        mysql.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Projet-Prog_Con
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Projet-Prog_Con APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Projet-Prog_Con SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Projet-Prog_Con
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Projet-Prog_Con PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        gtest
        gtest_main
)
enable_testing()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Projet-Prog_Con)
endif()
set_target_properties(Projet-Prog_Con PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Projet-Prog_Con
    BUNDLE DESTINATION ..
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Projet-Prog_Con)
endif()
