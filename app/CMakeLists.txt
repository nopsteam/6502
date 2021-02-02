add_executable(
  main_app
  main_app.c
)

add_dependencies(main_app resources)

target_link_libraries(
  main_app
  ${SDL2_LIBRARIES}
)

target_link_libraries(
  main_app
  disassembler
)
