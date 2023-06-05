# CMakeLists.txt for event package. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(pluto
    VERSION 6.1.9
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
    src/PHadronDecayM1N.cc src/PHadronDecayM2.cc src/PHadronDecayM3.cc src/PHadronModel.cc src/PInclusiveModel.cc
    src/PMassSampling.cc src/PMesh.cc src/PParticle.cc src/PPiOmegaAngularDistribution.cc src/PPlutoBulkDecay.cc
    src/PProjector.cc src/PPropagator.cc src/PReaction.cc src/PSaid.cc src/PScatterDistribution.cc src/PSimpleVMDFF.cc
    src/PStaticData.cc src/PStdData.cc src/PStdModels.cc src/PTCrossWeight.cc src/PTGenPhaseSpace.cc src/PThermal.cc
    src/PUtils.cc src/PValues.cc src/PVertexFile.cc
)

set(HEADERS include/PAdaptiveMesh.h include/PAdaptiveMeshN.h include/PAngularDistribution.h include/PAnyDistribution.h
    include/PArray.h include/PBatch.h include/PBeamSmearing.h include/PBreitWigner.h include/PBulkInterface.h
    include/PChannel.h include/PChannelModel.h include/PCommandList.h include/PComplexBreitWigner.h include/PCross.h
    include/PDalitzDecay.h include/PDalitzDistribution.h include/PDataBase.h include/PData.h include/PDebugFileOutput.h
    include/PDecayChannel.h include/PDecayManager.h include/PDefines.h include/PDeltaAngularDistribution.h
    include/PDensityMatrix.h include/PDiLepton.h include/PDistributionCollection.h include/PDistribution.h
    include/PDistributionManager.h include/PDistributionManagerUtil.h include/PDynamicData.h include/PEEDirectDecay.h
    include/PEmbeddedParticles.h include/PF1.h include/PF2.h include/PF3.h include/PFermiMomentumDD.h
    include/PFermiMomentum.h include/PFileInput.h include/PFileOutput.h include/PFilter.h include/PFireball.h
    include/PFixedDecay.h include/PFixedProduction.h include/PFormula.h include/PFunction.h include/PGenBod.h
    include/PHadronDecay.h include/PHadronDecayM1.h include/PHadronDecayM1N.h include/PHadronDecayM2.h
    include/PHadronDecayM3.h include/PHadronModel.h include/PInclusiveModel.h include/PKinematics.h
    include/PMassSampling.h include/PMesh.h include/PParticle.h include/PPiOmegaAngularDistribution.h
    include/PPlutoBulkDecay.h include/PProjector.h include/PPropagator.h include/PReaction.h include/PSaid.h
    include/PScatterDistribution.h include/PSimpleVMDFF.h include/PStaticData.h include/PStdData.h include/PStdModels.h
    include/PTCrossWeight.h include/PTGenPhaseSpace.h include/PThermal.h include/PUtils.h include/PValues.h
    include/PVertexFile.h
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

#---Create a shared library with geneated dictionary
add_library(Pluto SHARED ${SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/Compiled.h)

target_include_directories(Pluto
    PUBLIC
        $<INSTALL_INTERFACE:include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/inc>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        ${CMAKE_CURRENT_BINARY_DIR}
)

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
        list(APPEND PLUGIN_HEADERS_COLLECTION ${CMAKE_CURRENT_SOURCE_DIR}/${f})
        file(APPEND ${CMAKE_BINARY_DIR}/Plugins.h "\#include \"${CMAKE_CURRENT_SOURCE_DIR}/${f}\"\n")
    endforeach()

    install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PLUTO_SLOT}/plugins
    )

    if (IS_DIRECTORY macros)
        install(DIRECTORY macros/
            DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PLUTO_SLOT}/plugins/${plugin_target})
    endif()

    target_include_directories(Pluto PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

    # dynamically generate source files and Plugins LinkDef
    foreach(f ${PLUGIN_CLASSES})
       file(APPEND ${CMAKE_BINARY_DIR}/PluginLinkDef.h "\#pragma link C++ class ${f};\n")
    endforeach()
endmacro()

add_subdirectory(plugins)

ROOT_GENERATE_DICTIONARY(G__Pluto MODULE Pluto ${PLUGIN_HEADERS_COLLECTION} ${HEADERS} Plugins.h LINKDEF PlutoLinkDef.h)

#---Create a shared library with geneated dictionary

target_link_libraries(Pluto PRIVATE ROOT::Core ROOT::Tree ROOT::EG)

###########################################################

#---Create a main program using the library
#add_executable(Main MainEvent.cxx)
#target_link_libraries(Main Event)

add_custom_target(Compiled.h)
add_custom_command(OUTPUT Compiled.h COMMAND echo char *date_string = \\\(char*\\\) \\\"\$\$\(date +\"%e %B %Y\"\)\\\"  > ${CMAKE_CURRENT_BINARY_DIR}/Compiled.h DEPENDS G__Pluto.cxx ${SOURCES})


# Install logic
set(CMAKE_INSTALL_CMAKEDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${CMAKE_PROJECT_NAME}-${PROJECT_VERSION})

install(TARGETS Pluto
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PLUTO_SLOT})

INSTALL(DIRECTORY macros/
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PLUTO_SLOT})
INSTALL(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PLUTO_SLOT})

include(CMakePackageConfigHelpers)
configure_package_config_file(Config.cmake.in ${CMAKE_PROJECT_NAME}Config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_CMAKEDIR}
        PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_BINDIR)

write_basic_package_version_file(${CMAKE_PROJECT_NAME}ConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_CMAKEDIR})

# Add all targets to the build-tree export set
export(TARGETS Pluto
        FILE ${CMAKE_PROJECT_NAME}Targets.cmake)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/libPluto.rootmap
        ${CMAKE_CURRENT_BINARY_DIR}/libPluto_rdict.pcm
        DESTINATION ${CMAKE_INSTALL_LIBDIR})

# Install the export set for use with the install-tree
install(TARGETS Pluto
        EXPORT ${CMAKE_PROJECT_NAME}Targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT shlib COMPONENT dev)
