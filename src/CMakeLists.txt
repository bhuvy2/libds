set(SRC_FILES
  avl_tree.c
  common.c
  hash_funcs.c
  hash_table.c
  linked_list.c
  ring_buffer.c
  stack.c
  queue.c
  vector.c
)

function(configure_lib config_name)
  add_library("${config_name}" STATIC "${SRC_FILES}")

  set_target_properties("${config_name}" PROPERTIES VERSION 1)

  target_include_directories("${config_name}" PRIVATE ../includes/private)
  target_include_directories("${config_name}" PUBLIC ../includes/public)
  set_target_properties("${config_name}" PROPERTIES PUBLIC_HEADER 
	  "../includes/public/avl_tree.h;../includes/public/hash_funcs.h;../includes/public/hash_table.h;../includes/public/linked_list.h;../includes/public/queue.h;../includes/public/ring_buffer.h;../includes/public/stack.h;../includes/public/vector.h")
  INSTALL(TARGETS "${config_name}"
        ARCHIVE DESTINATION "libs"
        PUBLIC_HEADER DESTINATION "includes/libds"
  )
endfunction()

configure_lib(ds)
configure_lib(ds-pthread)
target_compile_definitions(ds-pthread PRIVATE LIBDS_PTHREAD_ENABLED)

