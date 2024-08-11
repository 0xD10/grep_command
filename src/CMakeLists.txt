project(grep)

add_library(first_head func_grep.c)

target_include_directories(
    first_head
    PUBLIC
    ${PROJECT_CURRENT_SOURCE_DIR}/../include/func_grep.h
)

