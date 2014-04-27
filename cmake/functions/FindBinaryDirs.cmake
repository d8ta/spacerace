function(find_binary_dirs Libname)
	message(STATUS "looking for binary dir of library ${Libname}")
	if(${Libname}_BIN_DIRS)
		set(bin_dirs ${${Libname}_BIN_DIRS})
	endif()
	if(${Libname}_INCLUDE_DIRS)
		foreach(lib_dir ${${Libname}_INCLUDE_DIRS})
			if(PROJECT_BUILD_TYPE_64 AND IS_DIRECTORY "${lib_dir}/../bin64")
				get_filename_component(bin_dir "${lib_dir}/../bin64" ABSOLUTE)
				set(bin_dirs ${bin_dirs} "${bin_dir}")
			elseif(IS_DIRECTORY "${lib_dir}/../bin")
				get_filename_component(bin_dir "${lib_dir}/../bin" ABSOLUTE)
				set(bin_dirs ${bin_dirs} "${bin_dir}")
			endif()
		endforeach()
	endif()
	if(NOT ${Libname}_LIBRARY_DIRS AND ${Libname}_LIBRARIES)
		#try to find library_dirs from the libraries
		foreach(lib ${${Libname}_LIBRARIES})
			get_filename_component(lib_dir "${lib}" PATH)
			if(IS_DIRECTORY "${lib_dir}")
				set(lib_dirs ${lib_dirs} "${lib_dir}")
			endif()
			if(lib_dirs)
				message(STATUS "found lib directories of library ${Libname} at ${lib_dirs}")
				list(REMOVE_DUPLICATES lib_dirs)
				set(${Libname}_LIBRARY_DIRS ${lib_dirs} CACHE PATH " ${Libname} library dirs" FORCE)
				mark_as_advanced(${Libname}_LIBRARY_DIRS)
			endif()
		endforeach()
	endif()

	if(${Libname}_LIBRARY_DIRS)
		foreach(lib_dir ${${Libname}_LIBRARY_DIRS})
			if(PROJECT_BUILD_TYPE_64 AND IS_DIRECTORY "${lib_dir}/../bin64")
				get_filename_component(bin_dir "${lib_dir}/../bin64" ABSOLUTE)
				set(bin_dirs ${bin_dirs} "${bin_dir}")
			elseif(IS_DIRECTORY "${lib_dir}/../bin")
				get_filename_component(bin_dir "${lib_dir}/../bin" ABSOLUTE)
				set(bin_dirs ${bin_dirs} "${bin_dir}")
			endif()
		endforeach()
	endif()

	if(bin_dirs)
		message(STATUS "found binary directories of library ${Libname} at ${bin_dirs}")
		list(REMOVE_DUPLICATES bin_dirs)
		set(${Libname}_BIN_DIRS ${bin_dirs} CACHE PATH " ${Libname} binary dirs" FORCE)
		set(${Libname}_BIN_DIRS ${bin_dirs})
		mark_as_advanced(${Libname}_BIN_DIRS)
	else()
		message(WARNING "can't find bin dir of library ${Libname} at ${${Libname}_LIBRARY_DIRS} or ${${Libname}_INCLUDE_DIRS}")
	endif()
endfunction(find_binary_dirs)