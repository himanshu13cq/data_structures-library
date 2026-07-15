cmake_minimum_required(VERSION 3.15)

project(DataStructuresLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

#-------------------------------------
add_executable(main main.cpp src/redis_lite.cpp)

target_include_directories(main PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)
#-------------------------------------

#-----------------------------------------
enable_testing()
find_package(GTest REQUIRED)

    add_executable(unit_tests
     test/DynamicArray/DAinsert_test.cpp
     test/DynamicArray/DAappend_test.cpp
     test/DynamicArray/DAremove_test.cpp
     test/DynamicArray/DAget_test.cpp
     test/DynamicArray/DA[]_test.cpp
     test/DynamicArray/DAisempt_test.cpp
     test/DynamicArray/DAsize_test.cpp
     test/DynamicArray/DAcap_test.cpp
     test/DynamicArray/DAcopy_test.cpp
     test/DynamicArray/DA=_test.cpp

     test/LinkedList/LLinsertfront_test.cpp
     test/LinkedList/LLinsertback_test.cpp
     test/LinkedList/LLinsert_test.cpp
     test/LinkedList/LLdeletefront_test.cpp
     test/LinkedList/LLdeleteval_test.cpp
     test/LinkedList/LLdeleteat_test.cpp
     test/LinkedList/LLfind_test.cpp
     test/LinkedList/LLsize_test.cpp
     test/LinkedList/LLiterator_test.cpp
     test/LinkedList/LLcopy_test.cpp
     test/LinkedList/LLassignop_test.cpp
     test/LinkedList/LLclear_test.cpp


     test/HashMap/HMinsert_test.cpp
     test/HashMap/HMget_test.cpp
     test/HashMap/HMcontain_test.cpp
     test/HashMap/HMremove_test.cpp
     test/HashMap/HMsize_test.cpp
     test/HashMap/HMempty_test.cpp
     test/HashMap/HMrehash_test.cpp
     test/HashMap/HMcopy_test.cpp
     test/HashMap/HMassignop_test.cpp
     test/HashMap/HMclear_test.cpp

      test/RedisLite/RLset_test.cpp
      test/RedisLite/RLget_test.cpp
      test/RedisLite/RLdel_test.cpp
      test/RedisLite/RLexist_test.cpp
      test/RedisLite/RLcount_test.cpp
      test/RedisLite/RLclear_test.cpp


      src/redis_lite.cpp
    )

target_include_directories(unit_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
     ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(unit_tests PRIVATE
     GTest::gtest
     GTest::gtest_main
 )

include(GoogleTest)
gtest_discover_tests(unit_tests)
#------------------------------------

#----------------------------------------

find_program(VALGRIND_PROGRAM valgrind)
if(VALGRIND_PROGRAM)
    message(STATUS "Valgrind found: ${VALGRIND_PROGRAM}")

    add_custom_target(valgrind
        COMMAND ${VALGRIND_PROGRAM} 
                --leak-check=full 
                --show-leak-kinds=all 
                --track-origins=yes 
                $<TARGET_FILE:main>  
        DEPENDS main                 
        COMMENT "Running Valgrind memory check on main..."
    )
else()
    message(WARNING "Valgrind not found! The 'valgrind' target will not be available.")
endif()

