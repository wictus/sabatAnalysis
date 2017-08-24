project(sabatanalysis)


add_definitions(-std=gnu++0x)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

find_package(ROOT REQUIRED COMPONENTS Hist Gpad Graf MathCore) 
include(${ROOT_USE_FILE})
add_library(dataFile dataFile.cpp)
add_library(elementSpectrum elementSpectrum.cpp)
add_library(spectrumFitter spectrumFitter.cpp)

target_link_libraries(elementSpectrum dataFile ${ROOT_LIBRARIES})
target_link_libraries(spectrumFitter elementSpectrum dataFile ${ROOT_LIBRARIES})

add_executable(sabatanalysis main.cpp)

target_link_libraries(sabatanalysis dataFile elementSpectrum spectrumFitter)

