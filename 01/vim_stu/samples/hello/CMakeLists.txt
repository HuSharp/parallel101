project(hello)

add_executable(hello.out helloword.cpp)

target_link_libraries(hello.out PUBLIC slib)
target_link_libraries(hello.out PUBLIC dynlib)
