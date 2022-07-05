# cmake_minimum_required(VERSION 3.1)
# PROJECT(dip)                      

# FIND_PACKAGE( OpenCV REQUIRED )                
# INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )

# set( NAME_SRC
#     src/main.cpp    
# )
# # set( NAME_HEADERS       
# #      include/dip.h
# # )

# add_executable( main ${NAME_SRC} ${NAME_HEADERS})
# set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out")
# TARGET_LINK_LIBRARIES (main ${OpenCV_LIBS})

cmake_minimum_required(VERSION 3.1) 
PROJECT (name)
find_package(OpenCV REQUIRED )
set( NAME_SRC
    src/main.cpp    
)

set( NAME_HEADERS       
     include/dip.h
)

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include )
link_directories( ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_executable( name ${NAME_SRC} ${NAME_HEADERS} )

target_link_libraries( name ${OpenCV_LIBS} )
