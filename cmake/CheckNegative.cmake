# Compile one deliberately invalid program and save its diagnostic for class.
set(compiler_args)
if(NOT "${COMPILER_ARG1}" STREQUAL "")
    separate_arguments(compiler_arg1 NATIVE_COMMAND "${COMPILER_ARG1}")
    list(APPEND compiler_args ${compiler_arg1})
endif()
if(NOT "${OSX_SYSROOT}" STREQUAL "")
    list(APPEND compiler_args -isysroot "${OSX_SYSROOT}")
endif()
execute_process(
    COMMAND "${COMPILER}" ${compiler_args} "-std=c++${STANDARD}"
        -Wall -Wextra -Wpedantic -Werror "-I${INCLUDE_DIR}" -fsyntax-only "${SOURCE}"
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE errors
)
file(WRITE "${LOG_FILE}" "${output}${errors}")
if(NOT result MATCHES "^[0-9]+$")
    message(FATAL_ERROR "Could not run compiler: ${result}")
elseif(result EQUAL 0)
    message(FATAL_ERROR "Unexpected success: ${SOURCE}")
else()
    message(STATUS "Expected rejection: ${SOURCE}. Diagnostic: ${LOG_FILE}")
endif()
