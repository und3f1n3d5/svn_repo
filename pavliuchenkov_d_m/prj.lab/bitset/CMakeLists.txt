add_library(bitset bitset.h bitset.cpp)
set_property(TARGET bitset PROPERTY CXX_STANDARD 20)

add_executable(bitset_test bitset_test.cpp)
target_link_libraries(bitset_test bitset)
