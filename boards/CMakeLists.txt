# SPDX-License-Identifier: Apache-2.0

# To avoid a lot of empty CMakeLists.txt files we assume it is not an
# error if it is missing

if(EXISTS ${BOARD_DIR}/CMakeLists.txt)
  if(USING_OUT_OF_TREE_BOARD)
	set(build_dir boards/${ARCH}/${BOARD})
  else()
	unset(build_dir)

	# FIXME: SHADOW_VARS: Remove this once we have enabled -Wshadow globally.
	#
	# For now, only enable warning for shadow variables for in-tree boards.
	add_compile_options($<TARGET_PROPERTY:compiler,warning_shadow_variables>)
  endif()

  add_subdirectory(${BOARD_DIR} ${build_dir})
endif()

if(DEFINED SHIELD)
  foreach(s ${SHIELD_AS_LIST})
    # search for shield/shield.conf file
    if(EXISTS ${SHIELD_DIR_${s}}/CMakeLists.txt)
      if(${SHIELD_${s}_OUT_OF_TREE})
        set(build_dir shields/${s}/)
      else()
        unset(build_dir)
      endif()
      add_subdirectory(${SHIELD_DIR_${s}} ${build_dir})
    endif()
  endforeach()
endif()
