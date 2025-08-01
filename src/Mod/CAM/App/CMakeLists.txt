if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_definitions(-fext-numeric-literals) #fix for gcc and qt5
endif()

include_directories(
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
)

include_directories(
    SYSTEM
    ${OCC_INCLUDE_DIR}
    ${EIGEN3_INCLUDE_DIR}
)

set(Path_LIBS
    Part
    area-native
    FreeCADApp
)

generate_from_xml(CommandPy)
generate_from_xml(PathPy)
generate_from_xml(FeaturePathCompoundPy)
generate_from_xml(AreaPy)
generate_from_xml(FeatureAreaPy)
generate_from_xml(VoronoiPy)
generate_from_xml(VoronoiCellPy)
generate_from_xml(VoronoiEdgePy)
generate_from_xml(VoronoiVertexPy)

generate_from_py_(CommandPy)
generate_from_py_(PathPy)
generate_from_py_(FeaturePathCompoundPy)
generate_from_py_(AreaPy)
generate_from_py_(FeatureAreaPy)
generate_from_py_(VoronoiPy)
generate_from_py_(VoronoiCellPy)
generate_from_py_(VoronoiEdgePy)
generate_from_py_(VoronoiVertexPy)

SET(Python_SRCS
    CommandPy.xml
    CommandPyImp.cpp
    PathPy.xml
    PathPyImp.cpp
    FeaturePathCompoundPy.xml
    FeaturePathCompoundPyImp.cpp
    AreaPy.xml
    AreaPyImp.cpp
    FeatureAreaPy.xml
    FeatureAreaPyImp.cpp
    VoronoiPy.xml
    VoronoiPyImp.cpp
    VoronoiCellPy.xml
    VoronoiCellPyImp.cpp
    VoronoiEdgePy.xml
    VoronoiEdgePyImp.cpp
    VoronoiVertexPy.xml
    VoronoiVertexPyImp.cpp
)

SET(Mod_SRCS
    AppPath.cpp
    AppPathPy.cpp
    PreCompiled.cpp
    PreCompiled.h
)

SET(Path_SRCS
    Command.cpp
    Command.h
    Path.cpp
    Path.h
    PropertyPath.cpp
    PropertyPath.h
    FeaturePath.cpp
    FeaturePath.h
    FeaturePathCompound.cpp
    FeaturePathCompound.h
    FeaturePathShape.cpp
    FeaturePathShape.h
    Area.cpp
    Area.h
    AreaParams.h
    ParamsHelper.h
    FeatureArea.cpp
    FeatureArea.h
    PathSegmentWalker.h
    PathSegmentWalker.cpp
    Voronoi.cpp
    Voronoi.h
    VoronoiCell.cpp
    VoronoiCell.h
    VoronoiEdge.cpp
    VoronoiEdge.h
    VoronoiVertex.cpp
    VoronoiVertex.h
    ${Mod_SRCS}
    ${Python_SRCS}
)

SOURCE_GROUP("Python" FILES ${Python_SRCS})
SOURCE_GROUP("Module" FILES ${Mod_SRCS})

#if (WIN32) uncomment to use KDL
#    FILE( GLOB KDL_SRCS ${CMAKE_SOURCE_DIR}/src/Mod/Robot/App/kdl_cp/[^.]*.cpp )
#    FILE( GLOB KDL_HPPS ${CMAKE_SOURCE_DIR}/src/Mod/Robot/App/kdl_cp/[^.]*.hpp
#                        ${CMAKE_SOURCE_DIR}/src/Mod/Robot/App/kdl_cp/[^.]*.inl)
#
#    FILE( GLOB UTIL_SRCS ${CMAKE_SOURCE_DIR}/src/Mod/Robot/App/kdl_cp/utilities/[^.]*.cpp
#                         ${CMAKE_SOURCE_DIR}/src/Mod/Robot/App/kdl_cp/utilities/[^.]*.cxx)
#    FILE( GLOB UTIL_HPPS ${CMAKE_SOURCE_DIR}/src/Mod/Robot/App/kdl_cp/utilities/[^.]*.h
#                         ${CMAKE_SOURCE_DIR}/src/Mod/Robot/App/kdl_cp/utilities/[^.]*.hpp)
#
#    SET(Path_SRCS
#        ${Path_SRCS}
#        ${KDL_SRCS}
#        ${KDL_HPPS}
#        ${UTIL_SRCS}
#        ${UTIL_HPPS}
#    )
#
#    SOURCE_GROUP("KDL" FILES ${KDL_SRCS} ${KDL_HPPS} ${UTIL_SRCS} ${UTIL_HPPS} )
#endif(WIN32)

add_library(Path SHARED ${Path_SRCS})
target_link_libraries(Path ${Path_LIBS})
if (FREECAD_WARN_ERROR)
    target_compile_warn_error(Path)
endif()


if(FREECAD_USE_PCH)
    add_definitions(-D_PreComp_)
    GET_MSVC_PRECOMPILED_SOURCE("PreCompiled.cpp" Path_CPP_SRCS ${Path_SRCS})
    ADD_MSVC_PRECOMPILED_HEADER(Path PreCompiled.h PreCompiled.cpp Path_CPP_SRCS)
endif(FREECAD_USE_PCH)

SET_BIN_DIR(Path PathApp /Mod/CAM)
SET_PYTHON_PREFIX_SUFFIX(Path)

INSTALL(TARGETS Path DESTINATION ${CMAKE_INSTALL_LIBDIR})
