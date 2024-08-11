project(grep)

add_executable(grep main.c)

target_link_libraries(
    grep
    PRIVATE
    first_head
)
