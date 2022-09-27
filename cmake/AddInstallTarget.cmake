include(GNUInstallDirs)

function(add_install_target)
  set(oneValueArgs NAME)
  cmake_parse_arguments(TARGET "" "${oneValueArgs}" "" ${ARGN})

  install(
    TARGETS ${TARGET_NAME}
    EXPORT ${TARGET_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES
    DESTINATION include
    PUBLIC_HEADER DESTINATION include)

endfunction()
