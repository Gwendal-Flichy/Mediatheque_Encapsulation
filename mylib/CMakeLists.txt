project(mylib)

set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)


set(HEADERS
    ${HEADER_DIR}/Book.h
    ${HEADER_DIR}/Client.h
    ${HEADER_DIR}/Commands.h
    ${HEADER_DIR}/IMedia.h
    ${HEADER_DIR}/Mediatheque.h
    ${HEADER_DIR}/Movie.h
    ${HEADER_DIR}/VideoGame.h
)

set(SOURCES
    ${SOURCE_DIR}/Commands.cpp
    ${SOURCE_DIR}/Mediatheque.cpp
)

add_library(${PROJECT_NAME}
STATIC
    ${SOURCES}
    ${HEADERS}

)

target_include_directories(${PROJECT_NAME}
PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${HEADER_DIR}>

)


set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Libraries")