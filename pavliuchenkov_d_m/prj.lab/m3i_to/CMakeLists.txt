add_library(m3i_by_to m3i_by_t_o.h m3i_by_t_o.cpp)
set_property(TARGET m3i_by_to PROPERTY CXX_STANDARD 20)

add_executable(m3i_time_to time_measure_to.cpp)
target_link_libraries(m3i_time_to M3i_by_to)
