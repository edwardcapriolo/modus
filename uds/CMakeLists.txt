#add_library (uds uds.cpp)
include_directories (${PROJECT_SOURCE_DIR}/../etcdcpp)
include_directories (${PROJECT_SOURCE_DIR}/guild)


add_executable (uds uds.cpp modus_context.h uds.h)

target_link_libraries (uds guild curl caf_core caf_io)
