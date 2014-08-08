# Make sure the compiler can find include files from our Hello library.
include_directories (${PROJECT_SOURCE_DIR}/../etcd-plus-plus)
include_directories (${PROJECT_SOURCE_DIR}/guild)

# Make sure the linker can find the Hello library once it is built.
link_directories (${PROJECT_SOURCE_DIR}/guild )

# Add executable called "helloDemo" that is built from the source files
# "demo.cxx" and "demo_b.cxx". The extensions are automatically found.
add_executable (guilddemo guilddemo.cpp)

# Link the executable to the Hello library.
target_link_libraries (guilddemo guild cppa curl) 
