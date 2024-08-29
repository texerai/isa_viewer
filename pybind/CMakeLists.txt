cmake_minimum_required(VERSION 3.12)
project(isa_decoder)

set(pybind11_DIR /home/kabylkas/miniforge3/lib/python3.10/site-packages/pybind11/share/cmake/pybind11/)
find_package(pybind11 REQUIRED)

# Setting project directories.
set (SRC_DIR ./isa_spec_manager/source/)
set (INC_DIR ./isa_spec_manager/include)
set (THIRD_PARTY_DIR ./isa_spec_manager/source/third_party)

# Local target: IsaDecoder.
# Setting all header files for this project.
set (ALL_H
    # Top interface header.
    ${INC_DIR}/amdisa/isa_decoder.h
    ${INC_DIR}/amdisa/api_version.h

    # Local library headers.
    ${SRC_DIR}/common/amdisa_expression_tree_consts.h
    ${SRC_DIR}/common/amdisa_structures.h
    ${SRC_DIR}/common/amdisa_xml_element_consts.h
    ${SRC_DIR}/common/amdisa_utility.h
    ${SRC_DIR}/common/isa_xml_reader.h

    # Third party library headers.
    ${THIRD_PARTY_DIR}/tinyxml2/tinyxml2.h
)

# Setting all source files for this project.
set (ALL_CPP
    # Top interface source file.
    ${SRC_DIR}/isa_decoder/isa_decoder.cpp
    ${SRC_DIR}/isa_decoder/encoding_condition_handler.hpp

    # Local library source files.
    ${SRC_DIR}/common/amdisa_utility.cpp
    ${SRC_DIR}/common/amdisa_structures.cpp
    ${SRC_DIR}/common/isa_xml_reader.cpp

    # Third party source files.
    ${THIRD_PARTY_DIR}/tinyxml2/tinyxml2.cpp
)

add_library(amdisa MODULE ${ALL_CPP} ${ALL_H} ./isa_decoder/isa_decoder_pybind.cpp)
set_target_properties(amdisa PROPERTIES PREFIX "")
target_link_libraries(amdisa PRIVATE pybind11::module)
target_include_directories(amdisa PRIVATE
    ${SRC_DIR}/common
    ${THIRD_PARTY_DIR}/tinyxml2
    PUBLIC
    ${INC_DIR}
)
