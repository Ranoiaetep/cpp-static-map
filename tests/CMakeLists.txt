add_executable(static_map static_map.cpp)
add_test(NAME static_map COMMAND static_map)

add_executable(make_static_map make_static_map.cpp)
add_test(NAME make_static_map COMMAND make_static_map)