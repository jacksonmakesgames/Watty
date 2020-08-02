
function(create_resources dir is_internal)
MESSAGE(STATUS "____Compiling resource binaries:")
if(${is_internal})
    set(output_src "${dir}/res_watty.cpp")
    set(output_header "${dir}/res_watty.h")
else()
    set(output_src "${dir}/res.cpp")
    set(output_header "${dir}/res.h")
endif()


# Create empty output files
file(TOUCH ${output_src})
file(TOUCH ${output_header})
file(WRITE ${output_header} "//AUTO-GENERATED FILE, EDIT AT YOUR OWN RISK\n#pragma once\n#include <Resource.h>\n")
file(WRITE ${output_src} "//AUTO-GENERATED FILE, EDIT AT YOUR OWN RISK\n")

    if(${is_internal})
    file(APPEND ${output_src} "#include \"res_watty.h\"\n//std::vector<Resource*> Resources::all = std::vector<Resource*>();\n")
    file(APPEND ${output_header} "struct RawWattyResources {")
    else()
        file(APPEND ${output_src} "#include \"res.h\"\n//std::vector<Resource*> Resources::all = std::vector<Resource*>();\n")
        file(APPEND ${output_header} "struct RawResources {")
    endif()
    include_directories(${dir})

# string(REGEX MATCH "[^/]+(?=/$|$)" dir_name ${dir})
# Collect input files
file(GLOB_RECURSE bins ${dir}/*)
# Iterate through input files
foreach(bin ${bins})
    # Get short filename
    string(REGEX REPLACE "([][+.*()^])" "\\\\\\1" regex "${dir}")
    string(REGEX REPLACE "(${regex}\/)" "" relative_name ${bin})
    # string(REGEX MATCH "([^\/]+$)" relative_name ${relative_name})
    string(REGEX MATCH "([^/]+)$" filename ${bin})
    set(original_filename ${relative_name})
    if(${output_src} MATCHES ${filename} OR ${output_header}  MATCHES ${filename} OR EMSCRIPTEN)
    # Don't add to file
    else()
        message(${relative_name})
        # Replace filename spaces & extension separator for C compatibility
        string(REGEX REPLACE "\\.| |-|\/" "_" relative_name ${relative_name})
        # Read hex data from file
        file(READ ${bin} filedata HEX)
        # Convert hex data for C compatibility
        string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," filedata ${filedata})
        # Append data to output file
            if(${is_internal})
                file(APPEND ${output_src} "const unsigned char RawWattyResources::${relative_name}[] = {${filedata}};\nconst unsigned RawWattyResources::${relative_name}_size = sizeof(${relative_name})*8;\n")
            else()
                file(APPEND ${output_src} "const unsigned char RawResources::${relative_name}[] = {${filedata}};\nconst unsigned RawResources::${relative_name}_size = sizeof(${relative_name})*8;\n")
            endif()

            file(APPEND ${output_header} "static const unsigned char ${relative_name}[];\nstatic const unsigned ${relative_name}_size;\n")
    endif()
endforeach()
file(APPEND ${output_header} "static void Init() {\n")
foreach(bin ${bins})
    # Get short filename
    string(REGEX REPLACE "([][+.*()^])" "\\\\\\1" regex "${dir}")
    string(REGEX REPLACE "(${regex}\/)" "" relative_name ${bin})

    # string(REGEX MATCH "([^\/]+$)" relative_name ${relative_name})
    string(REGEX MATCH "([^/]+)$" filename ${bin})
    set(original_filename ${relative_name})
    if(${output_src} MATCHES ${filename} OR ${output_header}  MATCHES ${filename} OR EMSCRIPTEN)
    # Don't add to file
    else()
        string(REGEX REPLACE "\\.| |-|\/" "_" relative_name ${relative_name})
        file(APPEND ${output_header} "Resources::all.push_back(new Resource(\"${original_filename}\", ${relative_name}, ${relative_name}_size));\n")
    endif()
endforeach()
file(APPEND ${output_header} "}\n};\n")
endfunction()
