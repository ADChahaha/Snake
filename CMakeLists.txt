cmake_minimum_required(VERSION 3.5)
project(snake)

add_executable(snake src/main.cpp src/snake_game.cpp)

target_include_directories(snake PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(snake ncurses)