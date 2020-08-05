
function(create_resources dir is_internal)
    string(TIMESTAMP start_time "%s" UTC)

    MESSAGE(STATUS "-->\tCompiling resource binaries:")
    if(${is_internal})
        set(output_src "${dir}/res_watty.cpp")
        set(include_name "res_watty.h")
        set(res_class_name "RawWattyResources")
    else()
        set(output_src "${dir}/res.cpp")
        set(include_name "res.h")
        set(res_class_name "RawResources")

    endif()
    
    include_directories(${dir})
    set(output_header "${dir}/${include_name}")

    set(cache_file ${CMAKE_CACHEFILE_DIR}/${res_class_name}_resource_cache.txt)

    file(TOUCH ${cache_file})
    file(STRINGS ${cache_file} LINES_OLD_CHECKSUMS)
    set(NEW_CHECKSUMS "")

    # Create empty output files
    file(TOUCH ${output_src})
    file(TOUCH ${output_header})

  

    set(res_var "")
    set(init_var "")
    set(src_var "")
    

    message(STATUS "Reading existing resource files...")
    file(READ ${output_header} header_in)
    if("${header_in}" STREQUAL "")
        #copy empty data to header
        configure_file(${CMAKE_CURRENT_FUNCTION_LIST_DIR}/res.h.in ${output_header})
        MESSAGE(STATUS "header file <${output_header}> was empty, filling with template")
    else()
        string(REGEX MATCH "AUTO-BEGIN-RES(.*)AUTO-END-RES" header_in ${header_in})
        string(REGEX REPLACE "(//)" "" header_in ${header_in})
        string(REGEX REPLACE "(AUTO-BEGIN-RES\n)" "" header_in ${header_in})
        string(REGEX REPLACE "(AUTO-END-RES)" "" header_in ${header_in})
        string(REGEX REPLACE "(\n)" ";" header_in ${header_in})
        string(REGEX REPLACE ";;" ";" header_in "${header_in}")
    endif()

    file(READ ${output_src} source_in)
    if("${source_in}" STREQUAL "")
        configure_file(${CMAKE_CURRENT_FUNCTION_LIST_DIR}/res.cpp.in ${output_src})
        MESSAGE(STATUS "source file <${output_src}> was empty, filling with template")
    else()
        file(STRINGS ${output_src} source_list)
        string(REGEX MATCH "AUTO-BEGIN-RES(.*)AUTO-END-RES" source_in ${source_in})
        string(REGEX REPLACE "(//)" "" source_in "${source_in}")
        string(REGEX REPLACE "(AUTO-BEGIN-RES\n)" "" source_in "${source_in}")
        string(REGEX REPLACE "(AUTO-END-RES)" "" source_in "${source_in}")
        string(REGEX REPLACE "(\n)" ";" source_in "${source_in}")
        string(REGEX REPLACE ";;" ";" source_in "${source_in}")
    endif()

    message(STATUS "..done")



    # Collect input files
    file(GLOB_RECURSE bins ${dir}/*)
    # Iterate through input files
    set(uncached_bins "")
    set(cached_bins "")
    foreach(bin ${bins})
        file(SHA256 ${bin} CHECKSUM)
        list(APPEND NEW_CHECKSUMS "${CHECKSUM}\n")
        if (NOT ";${LINES_OLD_CHECKSUMS};" MATCHES ";${CHECKSUM};") # not cached, new addition
            list(APPEND uncached_bins ${bin})
        else()
            list(APPEND cached_bins ${bin})
        endif()
        
    endforeach()
    
    foreach(bin ${uncached_bins})
        # Get short filename
        string(REGEX MATCH "([^/]+)$" filename ${bin})
        string(REGEX REPLACE "([][+.*()^])" "\\\\\\1" regex ${dir})
        string(REGEX REPLACE "(${regex}\/)" "" relative_name ${bin})
        set(original_filename ${relative_name})
        if(${output_src} MATCHES ${filename} OR ${output_header}  MATCHES ${filename} OR EMSCRIPTEN)
            # Don't add to file
        else()
            message(${relative_name})
            # Replace filename spaces & extension separator for C compatibility
            string(REGEX REPLACE "\\.| |-|\/|:" "_" relative_name ${relative_name})
            # Read hex data from file
            file(READ ${bin} filedata HEX)
            # Convert hex data for C compatibility
            string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," filedata ${filedata})

            # Append data to output file
            list(APPEND src_var "\nconst unsigned char ${res_class_name}::${relative_name}[] = {${filedata}};\nconst unsigned ${res_class_name}::${relative_name}_size = sizeof(${relative_name})*8;\n")
            list(APPEND res_var "\nstatic const unsigned char ${relative_name}[];\nstatic const unsigned ${relative_name}_size;\n")
            list(APPEND init_var "\nResources::all.push_back(new Resource(\"${original_filename}\", ${relative_name}, ${relative_name}_size));\n")
        endif()

    endforeach()

      string(LENGTH "${source_in}" total_src_length)
      message(STATUS "....Total file size: ${total_src_length}")
    foreach(bin ${cached_bins})
      string(REGEX MATCH "([^/]+)$" filename ${bin})
      string(REGEX REPLACE "([][+.*()^])" "\\\\\\1" regex ${dir})
      string(REGEX REPLACE "(${regex}\/)" "" relative_name ${bin})
      set(original_filename ${relative_name})
      string(REGEX REPLACE "\\.| |-|\/|:" "_" relative_name ${relative_name})


      string(FIND "${header_in}" "static const unsigned char ${relative_name}[]" found_index_begin_array)
      if(${found_index_begin_array} GREATER -1)
          string(LENGTH "static const unsigned char ${relative_name}[]" found_index_len)
          math(EXPR found_index_len ${found_index_len}+1)
          string(SUBSTRING "${header_in}" ${found_index_begin_array} ${found_index_len} this_var_array)
          list(APPEND res_var "\nstatic const unsigned char ${relative_name}[];")
          list(APPEND res_var "\nstatic const unsigned ${relative_name}_size;\n")
          list(APPEND init_var "\nResources::all.push_back(new Resource(\"${original_filename}\", ${relative_name}, ${relative_name}_size));\n")

      endif()

      
      string(FIND "${source_in}" "const unsigned char ${res_class_name}::${relative_name}[] =" found_index_begin_array_source)
      if(${found_index_begin_array_source} GREATER -1)
          math(EXPR length_after_var ${total_src_length}-${found_index_begin_array_source})
          string(SUBSTRING "${source_in}" ${found_index_begin_array_source} ${length_after_var} string_after_var)
          string(FIND "${string_after_var}" "unsigned ${res_class_name}" next_var_index) #find next variable (to know length of array)
          math(EXPR next_var_index ${next_var_index}+${found_index_begin_array_source})
          if(${next_var_index} GREATER -1)
            math(EXPR found_index_len ${next_var_index}-${found_index_begin_array_source}-7) # -7 for ";const "
          else()
            SET(found_index_len ${length_after_var})
          endif()
          string(SUBSTRING "${source_in}" ${found_index_begin_array_source} "${found_index_len}" this_var_array_source)
          list(APPEND src_var "\n${this_var_array_source}")
          list(APPEND src_var "\nconst unsigned ${res_class_name}::${relative_name}_size = sizeof(${relative_name})*8;")
      endif()
      
    endforeach()


    
    #copy data to header
    configure_file(${CMAKE_CURRENT_FUNCTION_LIST_DIR}/res.h.in ${output_header})
    #copy data to src
    configure_file(${CMAKE_CURRENT_FUNCTION_LIST_DIR}/res.cpp.in ${output_src})
    #cache results
    file(WRITE ${cache_file} ${NEW_CHECKSUMS})

    string(TIMESTAMP end_time "%s" UTC)

    math(EXPR total_time ${end_time}-${start_time})
    message(STATUS "Done making resources, took: ${total_time}s")

endfunction()
