set_source_files_properties (kodidevkit2.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties (kodidevkit2.i PROPERTIES SWIG_FLAGS "-I${CMAKE_BINARY_DIR}/src")

message ("PYTHON2 attempting to build!")

if (CMAKE_VERSION VERSION_LESS "3.8")
  swig_add_module (python2-kodidevkit python kodidevkit2.i)
else ()
  swig_add_library (python2-kodidevkit LANGUAGE python SOURCES kodidevkit2.i)
endif ()
swig_link_libraries (python2-kodidevkit ${PYTHON2_LIBRARIES} kodidevkit)

target_include_directories(${SWIG_MODULE_python2-kodidevkit_REAL_NAME}
  PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/../.."
  "${PYTHON2_INCLUDE_DIR}"
)

if (DOXYGEN_FOUND AND PYTHON2_EXECUTABLE)
  foreach (_file ${DOCCLASSES})
    add_dependencies (${SWIG_MODULE_python2-kodidevkit_REAL_NAME} ${_file}class_doc_i)
  endforeach ()
  add_dependencies (${SWIG_MODULE_python2-kodidevkit_REAL_NAME} common_hpp_doc_i)
endif ()

set_target_properties (${SWIG_MODULE_python2-kodidevkit_REAL_NAME} PROPERTIES
  OUTPUT_NAME _kodi
  COMPILE_FLAGS "${CMAKE_C_FLAGS} -DSWIGPYTHON=${SWIG_FOUND} -DSWIGPYTHON2=${SWIG_FOUND}"
)

install (TARGETS ${SWIG_MODULE_python2-kodidevkit_REAL_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${PYTHON2_PACKAGES_PATH}
)

install (FILES ${CMAKE_CURRENT_BINARY_DIR}/kodidevkit.py
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${PYTHON2_PACKAGES_PATH}
)
