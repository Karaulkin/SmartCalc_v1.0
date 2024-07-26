cmake_minimum_required(VERSION   3.5)

project(cpp VERSION   0.1 LANGUAGES C CXX) # Добавлено C в список языков

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD   11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавлено указание стандарта C, если это необходимо
set(CMAKE_C_STANDARD   99) # Например, стандарт C99
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets PrintSupport REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets PrintSupport REQUIRED)

##############################
file(GLOB C_SOURCES "../SmartCalc/*.c")
file(GLOB H_SOURCES "../SmartCalc/*.h")
file(GLOB DEPOSIT_C_SOURCES "../deposit/*.c")
file(GLOB DEPOSIT_H_SOURCES "../deposit/*.h")
file(GLOB CREDIT_C_SOURCES "../credit/*.c")
file(GLOB CREDIT_H_SOURCES "../credit/*.h")
##############################
file(GLOB QPLOT_C_SOURCES "qcustomplot.cpp")
file(GLOB QPLOT_H_SOURCES "qcustomplot.h")

set(PROJECT_SOURCES
        main.cpp

        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        credit.cpp
        credit.h
        credit.ui

        deposit.cpp
        deposit.h
        deposit.ui

        graph.cpp
        graph.h
        graph.ui

        # Добавьте здесь файлы на C, если они есть
        ${C_SOURCES}
        ${H_SOURCES}
        ${DEPOSIT_C_SOURCES}
        ${DEPOSIT_H_SOURCES}
        ${CREDIT_C_SOURCES}
        ${CREDIT_H_SOURCES}

        # QPLOT
        ${QPLOT_C_SOURCES}
        ${QPLOT_H_SOURCES}

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL   6)
    qt_add_executable(cpp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(cpp SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(cpp
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(cpp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport)

set_target_properties(cpp PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL   6)
    qt_finalize_executable(cpp)
endif()
