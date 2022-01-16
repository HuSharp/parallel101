project(hello)

add_executable(hello.out helloword.cpp)

target_link_libraries(hello.out PUBLIC slib)
target_link_libraries(hello.out PUBLIC dynlib)

# target_include_directories(hello.out PUBLIC ../slib)  #需要添加 ../ 因为是从当前目录搜索
