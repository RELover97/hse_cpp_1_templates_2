cmake_minimum_required(VERSION 3.20)
project(CppRankingSeminars LANGUAGES CXX)

# Generate the compilation database for clangd / VS Code.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(CTest)

# Every source has its own main(). Set the language standard per target.
function(add_seminar_example name source standard output_dir)
    add_executable(${name} "${source}")
    set_target_properties(${name} PROPERTIES
        CXX_STANDARD ${standard}
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        # Use the same executable path for single- and multi-config generators.
        RUNTIME_OUTPUT_DIRECTORY "$<1:${output_dir}>"
    )
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${name} PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endfunction()

# Short, independent programs in teaching order.
set(project_examples
    01a_ordinary_function
    01b_three_arguments
    01c_functor
    01d_bind
    01e_lambda
    01f_lambda_by_name
    02a_rank_by_value
    02b_reference_overloads
    02c_reference_deduction
    02d_bad_relay
    02e_forward_relay
    02f_rank_by_forward
    02g_simple_forward
    03a_fixed_row
    03b_pack_size
    03c_pack_expansion
    03d_recursive_print
    03e_comma_operator
    03f_comma_fold
    03g_report_row
    04_unconstrained
    05a_expression_sfinae
    05b_comparable_trait
    05c_printable_trait
    05d_enable_if
    05e_sfinae_ranking
    05f_sfinae_row
    05g_contract_check
    05h_ranking_output_check
    06a_concept_requirements
    06b_concepts_ranking
    06c_concepts_row
    06d_concept_overloads
    06e_contract_equivalence
    06f_nonmovable_result
    06g_vector_bool
    06h_output_equivalence
)
foreach(name IN LISTS project_examples)
    set(standard 17)
    if(name MATCHES "^06")
        set(standard 20)
    endif()
    add_seminar_example(${name} "examples/${name}.cpp" ${standard} "${CMAKE_BINARY_DIR}")
    target_include_directories(${name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
    add_custom_target(run-${name}
        COMMAND "$<TARGET_FILE:${name}>" DEPENDS ${name} USES_TERMINAL VERBATIM)
    list(APPEND project_run_commands COMMAND "${CMAKE_COMMAND}" -E echo "=== ${name} ==="
         COMMAND "$<TARGET_FILE:${name}>")
    if(BUILD_TESTING)
        add_test(NAME project.${name} COMMAND ${name})
        set_tests_properties(project.${name} PROPERTIES LABELS project)
    endif()
endforeach()
add_custom_target(run ${project_run_commands} DEPENDS ${project_examples} USES_TERMINAL VERBATIM)

# Independent programs from the theory guide.
set(theory_examples
    01_ordinary_sort 02_functor 03_bind 04_lambda
    05_reference_overloads 06_reference_collapsing 07_forwarding
    08_pack_size 09_recursive_print 10_comma_fold 11_sum_fold
    12_forwarding_factory 13_unconstrained_max 14_decltype 15_declval
    16_expression_sfinae 17_type_trait 18_partial_specialization
    19_void_t 20_has_less 21_enable_if 22_sfinae_write_max
    23_concepts_write_max 24_concept_overloads 25_empty_folds 26_unary_sum
)
foreach(name IN LISTS theory_examples)
    set(standard 17)
    if(name MATCHES "^2[34]_")
        set(standard 20)
    endif()
    # Prefix target names to separate the two groups of examples.
    set(target "theory_${name}")
    add_seminar_example(${target} "theory/examples/${name}.cpp" ${standard} "${CMAKE_BINARY_DIR}/theory")
    set_target_properties(${target} PROPERTIES OUTPUT_NAME "${name}")
    list(APPEND theory_targets ${target})
    list(APPEND theory_run_commands COMMAND "${CMAKE_COMMAND}" -E echo "=== ${name} ==="
         COMMAND "$<TARGET_FILE:${target}>")
    add_custom_target(run-theory-${name}
        COMMAND "$<TARGET_FILE:${target}>" DEPENDS ${target} USES_TERMINAL VERBATIM)
    if(BUILD_TESTING)
        add_test(NAME theory.${name} COMMAND ${target})
        set_tests_properties(theory.${name} PROPERTIES LABELS theory)
    endif()
endforeach()
add_custom_target(theory DEPENDS ${theory_targets})
add_custom_target(run-theory ${theory_run_commands} DEPENDS ${theory_targets} USES_TERMINAL VERBATIM)

# Intentionally invalid examples are excluded from the ordinary build.
# CTest succeeds only if the configured compiler rejects each source.
if(BUILD_TESTING AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(negative_examples
        01_unconstrained 02_sfinae 03_concepts 04_concepts_print 05_concepts_row)
    foreach(name IN LISTS negative_examples)
        set(standard 20)
        if(name MATCHES "^0[12]_")
            set(standard 17)
        endif()
        add_test(NAME negative.${name}
            COMMAND "${CMAKE_COMMAND}"
                "-DCOMPILER=${CMAKE_CXX_COMPILER}"
                "-DCOMPILER_ARG1=${CMAKE_CXX_COMPILER_ARG1}"
                "-DSTANDARD=${standard}"
                "-DSOURCE=${CMAKE_CURRENT_SOURCE_DIR}/negative/${name}.cpp"
                "-DINCLUDE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/include"
                "-DLOG_FILE=${CMAKE_BINARY_DIR}/${name}.log"
                "-DOSX_SYSROOT=${CMAKE_OSX_SYSROOT}"
                -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/CheckNegative.cmake")
        set_tests_properties(negative.${name} PROPERTIES LABELS negative)
    endforeach()
    add_custom_target(check-negative
        COMMAND "${CMAKE_CTEST_COMMAND}" --output-on-failure -C "$<CONFIG>" -L "^negative$"
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}" USES_TERMINAL VERBATIM)
endif()
