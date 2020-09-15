# Purpose
Expanding knowledge of OpenMP library usage.

# Set Up
<b>IDE: CLion 2020.2.1</b>
Include this onto your <b>CMakeLists.txt</b> in order to use OpenMP:
```
...
find_package(OpenMP)
if (OPENMP_FOUND)
    find_package(OpenMP REQUIRED)
    target_link_libraries(${PROJECT_NAME} ${OpenMP_CXX_LIBRARIES})
    #set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    #set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    #set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
...
```



