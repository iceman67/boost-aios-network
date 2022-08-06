cmake_minimum_required(VERSION 3.16)
project(smtech)

set(CMAKE_CXX_STANDARD 14)

#Boost 라이브러리 설치 확인
find_package(Boost)
find_package(Threads)
find_package(Boost REQUIRED COMPONENTS thread)
include_directories(${Boost_INCLUDE_DIR} /$ENV${HOME}  /Users/mac/boost_test/include)
add_definitions("-Wall -std=c++11 -I ${HOME}")

link_directories(/usr/local/lib)

if(Boost_FOUND)
    find_path (${HOME} "sha.h"  PATH_SUFFIXES "crypto++")
    # include 패스 설정
    include_directories(${Boost_INCLUDE_DIRS} /$ENV${HOME})
    # crypto++ 
    include_directories(/Users/mac) 
endif()


add_executable(test-sync-thread
	test_sync_thread.cpp 
)

add_executable(test-thread
	test_thread.cpp 
)

add_executable(timer-test
	timer_test.cpp 
)

add_executable(server
    server.cpp 
    hash.cpp
    storage.cpp
)

add_executable(merkle
    main.cpp 
    merkle_tree.cpp
    node.cpp
)

add_executable(client
	client.cpp
)

#[[
add_executable(demo demo.cpp)
]]

target_include_directories(server PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${workspace_root}>
)

target_link_libraries(test-sync-thread
	${Boost_LIBRARIES}
    Boost::thread
) 

target_link_libraries(test-thread
	${Boost_LIBRARIES}
    Boost::thread
) 


target_link_libraries(timer-test
	${Boost_LIBRARIES}
) 

target_link_libraries(merkle
	${Boost_LIBRARIES}
    "cryptopp"
) 

target_link_libraries(server
	${Boost_LIBRARIES}
        "cryptopp"
        "boost_serialization"
) 


target_link_libraries(client
	${Boost_LIBRARIES}
) 


#[[
target_link_libraries(demo
	${Boost_LIBRARIES}
    "boost_serialization"
) 
]]

