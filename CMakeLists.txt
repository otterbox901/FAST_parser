cmake_minimum_required(VERSION 3.20)
project(ExchangeParser VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
add_library(exchange_parser_lib ${SRC_FILES}
        "src/delete later/data_types.h"
        "src/delete later/operator_tags.h"
        "src/delete later/reads_bits.cpp"
        include/xml_parsing_coms/parse_child.h
        include/xml_parsing_coms/Node.h
        include/xml_parsing_coms/add_child.h
        include/xml_parsing_coms/print_tree.h
        include/xml_parsing_coms/parser_func.h
        include/Bit-processing-comms/decode_tree.h
        "include/Bit-processing-comms/decoding data types/decode_uint.h"
        "include/Bit-processing-comms/decoding data types/decode_string.h"
        "include/Bit-processing-comms/decoding data types/decode_int.h"
        "include/Bit-processing-comms/decoding data types/decode_decimal.h"
        "include/Bit-processing-comms/decoding data types/decode_byte_vector.h"
        "include/Bit-processing-comms/operator functions/delta.h"
        "include/Bit-processing-comms/operator functions/copy.h"
        "include/Bit-processing-comms/operator functions/increment.h"
        "include/Bit-processing-comms/operator functions/tail.h"
        "include/Bit-processing-comms/operator output.h"
        include/Bit-processing-comms/FastDecodeClass.h
        include/FastValue+StateDic.h
)

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/generated_headers/MarketDataRefresh.hpp
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/xml/templates.xml
        COMMENT "Generating C++ FAST parser headers from XML..."
)

add_executable(parser_app
        src/main.cpp
)
file(COPY "tests/xml parse test/test1.xml" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY "tests/xml parse test/test2.xml" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


include(FetchContent)

FetchContent_Declare(
        pugixml
        GIT_REPOSITORY https://github.com/zeux/pugixml.git
        GIT_TAG        v1.14
)
FetchContent_MakeAvailable(pugixml)

# Link it to your executable
target_link_libraries(exchange_parser_lib PRIVATE pugixml::pugixml)
target_link_libraries(parser_app PRIVATE exchange_parser_lib pugixml::pugixml)