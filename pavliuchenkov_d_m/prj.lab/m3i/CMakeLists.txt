add_library(m3i m3i.h m3i.cpp)
set_property(TARGET M3i PROPERTY CXX_STANDARD 14)

add_executable(M3i_test M3i_test.cpp M3i_test.cpp)
target_link_libraries(M3i_test m3i)
