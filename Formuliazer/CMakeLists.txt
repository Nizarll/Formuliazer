# CMakeList.txt : projet CMake pour Formuliazer, incluez la source et définissez
# la logique spécifique au projet ici.
#

# Ajoutez une source à l'exécutable de ce projet.
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(raylib)

add_executable (Formuliazer "libs/Renderer.h" "src/Renderer.cpp" "Formuliazer.cpp" "Formuliazer.h")
target_link_libraries(Formuliazer PRIVATE raylib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Formuliazer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
