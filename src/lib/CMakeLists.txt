#
# SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

set(CMAKE_AUTOMOC ON)

set(SOURCES
    tunedtypes/tunedtypes.cpp
    translationmanager/translationmanager.cpp
    tunedmanager/tunedmanager.cpp
)

set(HEADERS
    tunedtypes/tunedtypes.h
    translationmanager/translationmanager.h
    tunedmanager/tunedmanager.h
)

set(INTERNAL_LIBS
    ${SOURCES}
    ${HEADERS}
    ${MOC_HEADERS}
)

set(EXTERNAL_LIBS
    Qt5::Widgets
    Qt5::DBus
)

add_library(${LIB_NAME} STATIC
    ${INTERNAL_LIBS}
)

target_link_libraries(${LIB_NAME} PRIVATE ${EXTERNAL_LIBS})

target_compile_definitions(${LIB_NAME} PRIVATE
    TS_PROJECT_NAME=${CMAKE_PROJECT_NAME}
    TS_DATAROOT_PREFIX=${CMAKE_INSTALL_FULL_DATAROOTDIR}
)
