set(SRC_FILES
  common.c
  hash_table/hash_table.c
  linked_list/linked_list.c
)

function(configure_lib config_name)
  add_library("${config_name}" STATIC "${SRC_FILES}")

  set_target_properties("${config_name}" PROPERTIES VERSION 1)

  target_include_directories("${config_name}" PRIVATE ../includes/private)
  target_include_directories("${config_name}" PUBLIC ../includes/public)
endfunction()

configure_lib(ds)
configure_lib(ds-pthread)
target_compile_definitions(ds-pthread PRIVATE LIBDS_PTHREAD_ENABLED)

