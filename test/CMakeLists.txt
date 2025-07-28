add_executable(calc calc.c)

target_include_directories(calc PRIVATE ../include)
target_link_libraries(calc cmth)

add_test(NAME calc COMMAND calc)