# CMakeLists.txt for event package. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(pluto)

include_directories(include)

file(GLOB SOURCES "src/*.cc")
set (INCL_FILES PAdaptiveMesh.h PAdaptiveMeshN.h PAngularDistribution.h PAnyDistribution.h PArray.h PBatch.h PBeamSmearing.h PBreitWigner.h PBulkInterface.h PChannel.h PChannelModel.h PCommandList.h PComplexBreitWigner.h PCross.h PDalitzDecay.h PDalitzDistribution.h PData.h PDataBase.h PDebugFileOutput.h PDecayChannel.h PDecayManager.h PDeltaAngularDistribution.h PDensityMatrix.h PDiLepton.h PDistribution.h PDistributionCollection.h PDistributionManager.h PDistributionManagerUtil.h PDynamicData.h PEEDirectDecay.h PEmbeddedParticles.h PF1.h PF2.h PF3.h PFermiMomentumDD.h PFermiMomentum.h PFileInput.h PFileOutput.h PFireball.h PFixedDecay.h PFixedProduction.h PFormula.h PFunction.h PGenBod.h PHadronDecay.h PHadronDecayM1.h PHadronDecayM1N.h PHadronDecayM2.h PHadronDecayM3.h PHadronModel.h PInclusiveModel.h PMassSampling.h PMesh.h PParticle.h PPiOmegaAngularDistribution.h PPlutoBulkDecay.h PProjector.h PPropagator.h PReaction.h PSaid.h PScatterDistribution.h PSimpleVMDFF.h PStaticData.h PStdData.h PStdModels.h PTCrossWeight.h PThermal.h PUtils.h PValues.h PVertexFile.h)

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
#list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} $ENV{ROOTSYS}/etc/cmake)

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO Net)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
ROOT_GENERATE_DICTIONARY(G__Pluto ${INCL_FILES} LINKDEF PlutoLinkDef.h)

#---Create a shared library with geneated dictionary
add_library(Pluto SHARED ${SOURCES} G__Pluto.cxx)
target_link_libraries(Pluto ${ROOT_LIBRARIES})

#---Create  a main program using the library
#add_executable(Main MainEvent.cxx)
#target_link_libraries(Main Event)
