add_library(rational rational.h rational.cpp)
set_property(TARGET rational PROPERTY CXX_STANDARD 14)

add_executable(rational_test rational_test.cpp)
target_link_libraries(rational_test rational)
