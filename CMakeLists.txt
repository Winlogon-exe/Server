cmake_minimum_required(VERSION 3.26) 

project (Client-Server LANGUAGES CXX)

#включить .h из папки Headers
include_directories(inc)

file(GLOB SOURCES "src/*.cpp")

set(CMAKE_CXX_STANDARD 20) # стандарт C++, который вы хотите использовать

set(BOOST_ROOT "D:/LIBS C++/boost_1_82_0") # путь к вашему Boost

#находим boost
find_package(Boost 1.82.0 REQUIRED) 


if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(Client-Server ${SOURCES}) # имя исполняемого файла и  название папки с исходными файлами

if(Boost_FOUND)
    target_link_libraries(Client-Server ${Boost_LIBRARIES})
endif()
