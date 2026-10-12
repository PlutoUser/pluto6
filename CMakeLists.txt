# CMakeLists.txt for event package. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(Pluto
    VERSION 6.2.2
    LANGUAGES CXX
)

include(GNUInstallDirs)
include(CTest)

option(MULTISLOT "Allow to install several Pluto versions ito same DESTDIR" OFF)
if (MULTISLOT)
    set(PLUTO_SLOT Pluto-${PROJECT_VERSION})
endif()

###########################################################
SET(SOURCES src/PAdaptiveMesh.cc src/PAdaptiveMeshN.cc src/PAngularDistribution.cc src/PAnyDistribution.cc src/PArray.cc
    src/PBatch.cc src/PBeamSmearing.cc src/PBreitWigner.cc src/PBulkInterface.cc src/PChannel.cc src/PChannelModel.cc
    src/PCommandList.cc src/PComplexBreitWigner.cc src/PCross.cc src/PDalitzDecay.cc src/PDalitzDistribution.cc
    src/PDataBase.cc src/PData.cc src/PDebugFileOutput.cc src/PDecayChannel.cc src/PDecayManager.cc
    src/PDeltaAngularDistribution.cc src/PDensityMatrix.cc src/PDiLepton.cc src/PDistribution.cc
    src/PDistributionCollection.cc src/PDistributionManager.cc src/PDistributionManagerUtil.cc src/PDynamicData.cc
    src/PEEDirectDecay.cc src/PEmbeddedParticles.cc src/PF1.cc src/PF2.cc src/PF3.cc src/PFermiMomentum.cc
    src/PFermiMomentumDD.cc src/PFileInput.cc src/PFileOutput.cc src/PFilter.cc src/PFireball.cc src/PFixedDecay.cc
    src/PFixedProduction.cc src/PFormula.cc src/PFunction.cc src/PGenBod.cc src/PHadronDecay.cc src/PHadronDecayM1.cc
    src/PHadronDecayM1N.cc src/PHadronDecayM2.cc src/PHadronDecayM2Mesh.cc src/PHadronDecayM3.cc src/PHadronModel.cc src/PInclusiveModel.cc
    src/PMassSampling.cc src/PMesh.cc src/PParticle.cc src/PPiOmegaAngularDistribution.cc src/PPlutoBulkDecay.cc
    src/PProjector.cc src/PPropagator.cc src/PReaction.cc src/PSaid.cc src/PScatterDistribution.cc src/PSimpleVMDFF.cc
    src/PStaticData.cc src/PStdData.cc src/PStdModels.cc src/PTCrossWeight.cc src/PTGenPhaseSpace.cc src/PThermal.cc
    src/PUtils.cc src/PValues.cc src/PVertexFile.cc
)

set(HEADERS PAdaptiveMesh.h PAdaptiveMeshN.h PAngularDistribution.h PAnyDistribution.h PArray.h PBatch.h PBeamSmearing.h
    PBreitWigner.h PBulkInterface.h PChannel.h PChannelModel.h PCommandList.h PComplexBreitWigner.h PCross.h
    PDalitzDecay.h PDalitzDistribution.h PDataBase.h PData.h PDebugFileOutput.h PDecayChannel.h PDecayManager.h
    PDefines.h PDeltaAngularDistribution.h PDensityMatrix.h PDiLepton.h PDistributionCollection.h PDistribution.h
    PDistributionManager.h PDistributionManagerUtil.h PDynamicData.h PEEDirectDecay.h PEmbeddedParticles.h PF1.h PF2.h
    PF3.h PFermiMomentumDD.h PFermiMomentum.h PFileInput.h PFileOutput.h PFilter.h PFireball.h PFixedDecay.h
    PFixedProduction.h PFormula.h PFunction.h PGenBod.h PHadronDecay.h PHadronDecayM1.h PHadronDecayM1N.h
    PHadronDecayM2.h PHadronDecayM3.h PHadronModel.h PInclusiveModel.h PKinematics.h PMassSampling.h PMesh.h PParticle.h
    PPiOmegaAngularDistribution.h PPlutoBulkDecay.h PProjector.h PPropagator.h PReaction.h PSaid.h
    PScatterDistribution.h PSimpleVMDFF.h PStaticData.h PStdData.h PStdModels.h PTCrossWeight.h PTGenPhaseSpace.h
    PThermal.h PUtils.h PValues.h PVertexFile.h
)

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
#list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} $ENV{ROOTSYS}/etc/cmake)

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT "6.00" REQUIRED COMPONENTS RIO Net)
if(ROOT_VERSION LESS 6.00)
    message(FATAL_ERROR "The required ROOT version has to be at least 6.00, found " ${ROOT_VERSION})
endif()
message(STATUS "Found ROOT version: " ${ROOT_VERSION})

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

SET(ROOT_VERSION_LEGACY 6.22.00)

#---Create a shared library with geneated dictionary
add_library(Pluto SHARED ${SOURCES} ${CMAKE_BINARY_DIR}/Compiled.h ${CMAKE_BINARY_DIR}/Version.h)
add_library(Pluto::Pluto ALIAS Pluto)

target_include_directories(Pluto
    PUBLIC
        $<INSTALL_INTERFACE:include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/inc>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        ${CMAKE_BINARY_DIR}
)

if (${ROOT_VERSION} VERSION_LESS ${ROOT_VERSION_LEGACY})
    include_directories(${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}/include)
endif()

file(WRITE ${CMAKE_BINARY_DIR}/Plugins.h)
file(WRITE ${CMAKE_BINARY_DIR}/Plugins.cc)
file(WRITE ${CMAKE_BINARY_DIR}/PluginLinkDef.h)

# This macro prepares whole Plugin logic:
# - if 'PDistributionManager.mod.cc' file exists adds it to `Plugins.cc'
# - for each of SOURCES adds it as source to `Pluto` target
# - for each of HEADERS adds it to headers collection (should be improved)
# - installs include and macros (if exists) directories
# - appends CLASSES to `PluginLinkDef.h`
macro(add_plugin plugin_target)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs SOURCES HEADERS CLASSES)
    cmake_parse_arguments(PLUGIN "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/PDistributionManager.mod.cc)
        file(APPEND ${CMAKE_BINARY_DIR}/Plugins.cc "\#include \"${CMAKE_CURRENT_SOURCE_DIR}/PDistributionManager.mod.cc\"\n")
    endif()

    foreach(f ${PLUGIN_SOURCES})
       target_sources(Pluto PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${f})
    endforeach()

    foreach(f ${PLUGIN_HEADERS})
        list(APPEND PLUGIN_HEADERS_COLLECTION ${f})
        get_filename_component(f_name "${f}" NAME)
        file(APPEND ${CMAKE_BINARY_DIR}/Plugins.h "\#include \"${f_name}\"\n")
    endforeach()

    install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PLUTO_SLOT}
    )

    target_include_directories(Pluto
        PUBLIC
            $<INSTALL_INTERFACE:include>
        PRIVATE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )
    if (${ROOT_VERSION} VERSION_LESS ${ROOT_VERSION_LEGACY})
        get_property(incdir DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
        set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include;${incdir}")
    endif()

    if (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/macros)
        install(DIRECTORY macros/
            DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PLUTO_SLOT}/macros/plugins/${plugin_target})
    endif()

    # dynamically generate source files and Plugins LinkDef
    foreach(f ${PLUGIN_CLASSES})
        file(APPEND ${CMAKE_BINARY_DIR}/PluginLinkDef.h "\#pragma link C++ class ${f};\n")
    endforeach()
endmacro()

add_subdirectory(plugins)

install(FILES ${CMAKE_BINARY_DIR}/Plugins.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PLUTO_SLOT})

ROOT_GENERATE_DICTIONARY(G__Pluto MODULE Pluto ${PLUGIN_HEADERS_COLLECTION} ${HEADERS} Plugins.h LINKDEF PlutoLinkDef.h)

#---Create a shared library with geneated dictionary

target_link_libraries(Pluto PRIVATE ROOT::Core ROOT::Tree ROOT::EG)

###########################################################

configure_file(Version.h.in Version.h)
#target_include_directories(Pluto PUBLIC
#    "${PROJECT_BINARY_DIR}")

add_custom_target(Compiled.h)
add_custom_command(OUTPUT Compiled.h COMMAND echo char *date_string = \\\(char*\\\) \\\"\$\$\(date +\"%e %B %Y\"\)\\\"  > ${CMAKE_CURRENT_BINARY_DIR}/Compiled.h DEPENDS G__Pluto.cxx ${SOURCES})

# Install logic
set(CMAKE_INSTALL_CMAKEDIR ${CMAKE_INSTALL_LIBDIR}/cmake/Pluto-${PROJECT_VERSION})

install(TARGETS Pluto
    EXPORT PlutoTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PLUTO_SLOT})

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/libPluto.rootmap
        ${CMAKE_CURRENT_BINARY_DIR}/libPluto_rdict.pcm
        DESTINATION ${CMAKE_INSTALL_LIBDIR})

INSTALL(DIRECTORY macros/
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/macros/${PLUTO_SLOT})
INSTALL(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PLUTO_SLOT})

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/libPluto.rootmap
        ${CMAKE_CURRENT_BINARY_DIR}/libPluto_rdict.pcm
        DESTINATION ${CMAKE_INSTALL_LIBDIR})

# Install Cionfig files
include(CMakePackageConfigHelpers)
configure_package_config_file(Config.cmake.in PlutoConfig.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_CMAKEDIR}
        PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_BINDIR)

write_basic_package_version_file(PlutoConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/PlutoConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/PlutoConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_CMAKEDIR})

# Create and install export/targets package
export(PACKAGE Pluto)

# Add all targets to the build-tree export set
export(TARGETS Pluto
        NAMESPACE Pluto
        FILE PlutoTargets.cmake)

install(EXPORT PlutoTargets
        FILE PlutoTargets.cmake
        NAMESPACE Pluto::
        DESTINATION ${CMAKE_INSTALL_CMAKEDIR})
