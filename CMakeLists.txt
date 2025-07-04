cmake_minimum_required(VERSION 3.15)
project(exe C CXX)

if (MSVC)
  # In Debug usiamo la DLL di debug (/MDd), altrimenti la release (/MD)
  set(CMAKE_MSVC_RUNTIME_LIBRARY
    "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
    CACHE STRING "" FORCE
  )
endif()

# Enable C and C++ languages
enable_language(C)
enable_language(CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Libreria GLAD ---
find_package(OpenGL REQUIRED)
add_library(glad STATIC
    third_party/glad/src/glad.c
)
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/include
)
target_link_libraries(glad PUBLIC OpenGL::GL)

# --- Libreria ImGui ---
# Creiamo un target "imgui" che compila tutti i suoi file sorgente.
add_library(imgui STATIC
    third_party/imgui/imgui.cpp
    third_party/imgui/imgui_draw.cpp
    third_party/imgui/imgui_tables.cpp
    third_party/imgui/imgui_widgets.cpp
    third_party/imgui/backends/imgui_impl_glfw.cpp
    third_party/imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui
)
target_link_libraries(imgui PUBLIC glad glfw)

# Platform-specific settings
if(APPLE)
    # macOS specific configurations

    # Vulkan Setup for macOS
    find_package(Vulkan REQUIRED)
    if(Vulkan_FOUND)
        message(STATUS "Vulkan found at ${Vulkan_INCLUDE_DIR}")
    else()
        message(FATAL_ERROR "Vulkan not found!")
    endif()

    # GLFW and GLM Setup for macOS
    find_package(glfw3 REQUIRED)
    find_package(glm REQUIRED)
    find_package(Threads REQUIRED)

    # Define the project source and header files
    file(GLOB_RECURSE SOURCES src/camera/*.cpp src/objects/*.cpp src/scene/*.cpp src/utilities/*.cpp)
    file(GLOB_RECURSE HEADERS include/*.h include/*.hpp)
    file(GLOB_RECURSE HEADERS third_party/*.h third_party/*.hpp)
    
    add_subdirectory(third_party/bullet3)

    # Define the project executable
    add_executable(exe src/main.cpp ${SOURCES} ${HEADERS})
    add_executable(compute_shadows src/compute_shadows.cpp ${SOURCES} ${HEADERS})

    target_include_directories(exe PRIVATE 
        ${CMAKE_SOURCE_DIR}/third_party/bullet3/src
    )
    add_dependencies(exe Bullet3Common BulletDynamics BulletCollision LinearMath)
    target_link_libraries(exe PRIVATE Bullet3Common BulletDynamics BulletCollision LinearMath)


    target_include_directories(compute_shadows PRIVATE 
        ${CMAKE_SOURCE_DIR}/third_party/bullet3/src
    )
    add_dependencies(compute_shadows Bullet3Common BulletDynamics BulletCollision LinearMath)
    target_link_libraries(compute_shadows PRIVATE Bullet3Common BulletDynamics BulletCollision LinearMath)


    # Include directories
    target_include_directories(exe PRIVATE ${GLM_INCLUDE_DIRS})
    target_include_directories(exe PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_include_directories(exe PRIVATE ${CMAKE_SOURCE_DIR}/third_party)
    target_include_directories(exe PUBLIC ${Vulkan_INCLUDE_DIR})

    target_include_directories(compute_shadows PRIVATE ${GLM_INCLUDE_DIRS})
    target_include_directories(compute_shadows PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_include_directories(compute_shadows PRIVATE ${CMAKE_SOURCE_DIR}/third_party)
    target_include_directories(compute_shadows PUBLIC ${Vulkan_INCLUDE_DIR})

    # Link libraries
    target_link_libraries(exe PRIVATE Vulkan::Vulkan glfw Threads::Threads imgui)
    target_link_libraries(compute_shadows PRIVATE Vulkan::Vulkan glfw Threads::Threads imgui)
    
    file(GLOB GLSL_SOURCE_FILES "${CMAKE_SOURCE_DIR}/assets/shaders/*.vert" "${CMAKE_SOURCE_DIR}/assets/shaders/*.frag")

    # Create the 'shaders' directory in the build directory
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/shaders)

    # Compile GLSL shaders into SPIR-V
    set(SPIRV_BINARY_FILES "")
    foreach(GLSL_FILE ${GLSL_SOURCE_FILES})
        get_filename_component(FILENAME_WE ${GLSL_FILE} NAME_WE)
        get_filename_component(FILE_EXT ${GLSL_FILE} EXT)

        # Convert the extension to the desired suffix
        if(FILE_EXT STREQUAL ".frag")
            set(SUFFIX "Frag")
        elseif(FILE_EXT STREQUAL ".vert")
            set(SUFFIX "Vert")
        else()
            set(SUFFIX "")
        endif()

        # Construct the new SPIR-V file name
        set(SPIRV_FILE "${CMAKE_BINARY_DIR}/shaders/${FILENAME_WE}${SUFFIX}.spv")

        add_custom_command(
            OUTPUT ${SPIRV_FILE}
            COMMAND ${Vulkan_GLSLC_EXECUTABLE} ${GLSL_FILE} -o ${SPIRV_FILE}
            DEPENDS ${GLSL_FILE}
            COMMENT "Compiling shader: ${GLSL_FILE} -> ${SPIRV_FILE}"
        )

        list(APPEND SPIRV_BINARY_FILES ${SPIRV_FILE})
    endforeach()


    # Add custom target for shaders
    add_custom_target(Shaders DEPENDS ${SPIRV_BINARY_FILES})

    # Ensure that exe depends on the SPIR-V files
    add_dependencies(exe Shaders)
    add_dependencies(compute_shadows Shaders)

    # Copy resources (textures, models, etc.) to the build directory
    file(COPY ${CMAKE_SOURCE_DIR}/assets/textures DESTINATION ${CMAKE_BINARY_DIR}/assets)
    file(COPY ${CMAKE_SOURCE_DIR}/assets/models DESTINATION ${CMAKE_BINARY_DIR}/assets)
    file(COPY ${CMAKE_SOURCE_DIR}/assets/background.bmp DESTINATION ${CMAKE_BINARY_DIR})

    # Use GLOB to find files and only copy if any exist
    file(GLOB SHADER_FILES "${CMAKE_SOURCE_DIR}/assets/shaders/*.spv")
    if(SHADER_FILES)
        file(COPY ${SHADER_FILES} DESTINATION ${CMAKE_BINARY_DIR}/shaders)
    else()
        message(WARNING "No SPIR-V shader files found in ${CMAKE_SOURCE_DIR}/assets/shaders/")
    endif()

elseif(WIN32)

    # Windows specific configurations

    # Set paths to libraries (modify these based on your SDK and library installation)
    set(GLFW "C:/VulkanSDK/libs/glfw-3.4.bin.WIN64")
    set(GLM "C:/VulkanSDK/libs/glm")
    
    add_library(glfw STATIC IMPORTED)
    set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION "${GLFW}/lib-vc2022/glfw3.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${GLFW}/include"
    )

    # List of directories to add to the include path
    list(APPEND INCLUDE_DIRS "${GLFW}/include" ${GLM} headers)

    # List of libraries to link to the executable
    # list(APPEND LINK_LIBS "${GLFW}/lib-mingw-w64/libglfw3.a")
    list(APPEND LINK_LIBS "${GLFW}/lib-vc2022/glfw3.lib")
    file(GLOB_RECURSE SOURCES src/camera/*.cpp src/objects/*.cpp src/scene/*.cpp src/utilities/*.cpp)
    file(GLOB_RECURSE HEADERS include/*.h include/*.hpp)
    file(GLOB_RECURSE HEADERS third_party/*.h third_party/*.hpp)

    add_subdirectory(third_party/bullet3)

    add_executable(exe src/main.cpp ${SOURCES} ${HEADERS})
    add_executable(compute_shadows src/compute_shadows.cpp ${SOURCES} ${HEADERS})

    target_include_directories(exe PRIVATE 
        ${CMAKE_SOURCE_DIR}/third_party/bullet3/src
    )
    target_include_directories(compute_shadows PRIVATE 
        ${CMAKE_SOURCE_DIR}/third_party/bullet3/src
    )
    add_dependencies(exe Bullet3Common BulletDynamics BulletCollision LinearMath)
    target_link_libraries(exe PRIVATE Bullet3Common BulletDynamics BulletCollision LinearMath imgui)
    add_dependencies(compute_shadows Bullet3Common BulletDynamics BulletCollision LinearMath)
    target_link_libraries(compute_shadows PRIVATE Bullet3Common BulletDynamics BulletCollision LinearMath imgui)

    find_package(Vulkan REQUIRED)

    foreach(dir IN LISTS Vulkan_INCLUDE_DIR INCLUDE_DIRS)
        target_include_directories(exe PUBLIC ${dir})
        target_include_directories(compute_shadows PUBLIC ${dir})
    endforeach()

    foreach(lib IN LISTS Vulkan_LIBRARIES LINK_LIBS)
        target_link_libraries(exe PRIVATE ${lib})
        target_link_libraries(compute_shadows PRIVATE ${lib})
    endforeach()

    target_include_directories(exe PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_include_directories(exe PRIVATE ${CMAKE_SOURCE_DIR}/third_party)
    target_include_directories(compute_shadows PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_include_directories(compute_shadows PRIVATE ${CMAKE_SOURCE_DIR}/third_party)


    file(GLOB GLSL_SOURCE_FILES "${CMAKE_SOURCE_DIR}/assets/shaders/*.vert" "${CMAKE_SOURCE_DIR}/assets/shaders/*.frag")

    # Create the 'shaders' directory in the build directory
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/shaders)

    # Compile GLSL shaders into SPIR-V
    set(SPIRV_BINARY_FILES "")
    foreach(GLSL_FILE ${GLSL_SOURCE_FILES})
        get_filename_component(FILENAME_WE ${GLSL_FILE} NAME_WE)
        get_filename_component(FILE_EXT ${GLSL_FILE} EXT)

        # Convert the extension to the desired suffix
        if(FILE_EXT STREQUAL ".frag")
            set(SUFFIX "Frag")
        elseif(FILE_EXT STREQUAL ".vert")
            set(SUFFIX "Vert")
        else()
            set(SUFFIX "")
        endif()

        # Construct the new SPIR-V file name
        set(SPIRV_FILE "${CMAKE_BINARY_DIR}/shaders/${FILENAME_WE}${SUFFIX}.spv")

        add_custom_command(
            OUTPUT ${SPIRV_FILE}
            COMMAND ${Vulkan_GLSLC_EXECUTABLE} ${GLSL_FILE} -o ${SPIRV_FILE}
            DEPENDS ${GLSL_FILE}
            COMMENT "Compiling shader: ${GLSL_FILE} -> ${SPIRV_FILE}"
        )

        list(APPEND SPIRV_BINARY_FILES ${SPIRV_FILE})
    endforeach()


    # Add custom target for shaders
    add_custom_target(Shaders DEPENDS ${SPIRV_BINARY_FILES})

    # Ensure that exe depends on the SPIR-V files
    add_dependencies(exe Shaders)
    add_dependencies(compute_shadows Shaders)

    file(COPY ${CMAKE_SOURCE_DIR}/assets/textures DESTINATION ${CMAKE_BINARY_DIR}/assets)
    file(COPY ${CMAKE_SOURCE_DIR}/assets/models DESTINATION ${CMAKE_BINARY_DIR}/assets)
    file(COPY ${CMAKE_SOURCE_DIR}/assets/background.bmp DESTINATION ${CMAKE_BINARY_DIR})

    # Use GLOB to find files and only copy if any exist
    file(GLOB SHADER_FILES "${CMAKE_SOURCE_DIR}/assets/shaders/*.spv")
    if(SHADER_FILES)
        file(COPY ${SHADER_FILES} DESTINATION ${CMAKE_BINARY_DIR}/shaders)
    else()
        message(WARNING "No SPIR-V shader files found in ${CMAKE_SOURCE_DIR}/assets/shaders/")
    endif()
elseif(UNIX AND NOT APPLE)
    file(GLOB_RECURSE SOURCES src/camera/*.cpp src/objects/*.cpp src/scene/*.cpp src/utilities/*.cpp)
    file(GLOB_RECURSE HEADERS include/*.h include/*.hpp)
    
    add_subdirectory(third_party/bullet3)

    add_executable(exe src/main.cpp ${SOURCES} ${HEADERS})
    add_executable(compute_shadows src/compute_shadows.cpp ${SOURCES} ${HEADERS})

    target_include_directories(exe PRIVATE 
        ${CMAKE_SOURCE_DIR}/third_party/bullet3/src
    )
    target_include_directories(compute_shadows PRIVATE 
        ${CMAKE_SOURCE_DIR}/third_party/bullet3/src
    )
    add_dependencies(exe Bullet3Common BulletDynamics BulletCollision LinearMath)
    add_dependencies(compute_shadows Bullet3Common BulletDynamics BulletCollision LinearMath)
    target_link_libraries(exe PRIVATE Bullet3Common BulletDynamics BulletCollision LinearMath)
    target_link_libraries(compute_shadows PRIVATE Bullet3Common BulletDynamics BulletCollision LinearMath)

    find_package(Vulkan REQUIRED)
    find_package(glfw3 REQUIRED)


    find_package(glm REQUIRED)
    target_include_directories(exe PRIVATE ${GLM_INCLUDE_DIRS})
    target_include_directories(compute_shadows PRIVATE ${GLM_INCLUDE_DIRS})

    target_include_directories(exe PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_include_directories(exe PRIVATE ${CMAKE_SOURCE_DIR}/third_party)
    target_include_directories(compute_shadows PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_include_directories(compute_shadows PRIVATE ${CMAKE_SOURCE_DIR}/third_party)

    target_link_libraries(exe PRIVATE Vulkan::Vulkan glfw imgui)
    target_link_libraries(compute_shadows PRIVATE Vulkan::Vulkan glfw imgui)

    foreach(dir IN LISTS Vulkan_INCLUDE_DIR INCLUDE_DIRS)
        target_include_directories(exe PUBLIC ${dir})
        target_include_directories(compute_shadows PUBLIC ${dir})
    endforeach()

    foreach(lib IN LISTS Vulkan_LIBRARIES LINK_LIBS)
        target_link_libraries(exe PRIVATE ${lib})
        target_link_libraries(compute_shadows PRIVATE ${lib})
    endforeach()

    target_include_directories(exe PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_include_directories(compute_shadows PRIVATE ${CMAKE_SOURCE_DIR}/include)

    file(GLOB GLSL_SOURCE_FILES "${CMAKE_SOURCE_DIR}/assets/shaders/*.vert" "${CMAKE_SOURCE_DIR}/assets/shaders/*.frag")

    # Create the 'shaders' directory in the build directory
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/shaders)

    # Compile GLSL shaders into SPIR-V
    set(SPIRV_BINARY_FILES "")
    foreach(GLSL_FILE ${GLSL_SOURCE_FILES})
        get_filename_component(FILENAME_WE ${GLSL_FILE} NAME_WE)
        get_filename_component(FILE_EXT ${GLSL_FILE} EXT)

        # Convert the extension to the desired suffix
        if(FILE_EXT STREQUAL ".frag")
            set(SUFFIX "Frag")
        elseif(FILE_EXT STREQUAL ".vert")
            set(SUFFIX "Vert")
        else()
            set(SUFFIX "")
        endif()

        # Construct the new SPIR-V file name
        set(SPIRV_FILE "${CMAKE_BINARY_DIR}/shaders/${FILENAME_WE}${SUFFIX}.spv")

        add_custom_command(
            OUTPUT ${SPIRV_FILE}
            COMMAND ${Vulkan_GLSLC_EXECUTABLE} ${GLSL_FILE} -o ${SPIRV_FILE}
            DEPENDS ${GLSL_FILE}
            COMMENT "Compiling shader: ${GLSL_FILE} -> ${SPIRV_FILE}"
        )

        list(APPEND SPIRV_BINARY_FILES ${SPIRV_FILE})
    endforeach()


    # Add custom target for shaders
    add_custom_target(Shaders DEPENDS ${SPIRV_BINARY_FILES})

    # Ensure that exe depends on the SPIR-V files
    add_dependencies(exe Shaders)
    add_dependencies(compute_shadows Shaders)

    file(COPY ${CMAKE_SOURCE_DIR}/assets/textures DESTINATION ${CMAKE_BINARY_DIR}/assets)
    file(COPY ${CMAKE_SOURCE_DIR}/assets/models DESTINATION ${CMAKE_BINARY_DIR}/assets)
    file(COPY ${CMAKE_SOURCE_DIR}/assets/background.bmp DESTINATION ${CMAKE_BINARY_DIR})


    # Use GLOB to find files and only copy if any exist
    file(GLOB SHADER_FILES "${CMAKE_SOURCE_DIR}/assets/shaders/*.spv")
    if(SHADER_FILES)
        file(COPY ${SHADER_FILES} DESTINATION ${CMAKE_BINARY_DIR}/shaders)
    else()
        message(WARNING "No SPIR-V shader files found in ${CMAKE_SOURCE_DIR}/assets/shaders/")
    endif()
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

