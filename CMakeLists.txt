set(PACKAGE felix-monitoring)
set(PACKAGE_VERSION 0.0.1)

include(FELIX)

include_directories(src web)

find_package(TBB ${tbb_version} EXACT REQUIRED)
include_directories(${TBB_INCLUDE_DIRS})
link_directories(${TBB_DIR}/lib)
find_package(Boost ${boost_version} EXACT REQUIRED COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
#felix_add_external for external usage

# from externals
felix_add_external(docopt ${docopt_version} ${BINARY_TAG})
felix_add_external(simdjson ${simdjson_version} ${BINARY_TAG})
felix_add_external(json ${json_version})
felix_add_external(jwrite ${jwrite_version} ${BINARY_TAG})
felix_add_external(libfabric ${libfabric_version} ${BINARY_TAG})
felix_add_external(logrxi ${logrxi_version} ${BINARY_TAG})
felix_add_external(pybind11 ${pybind11_version})
felix_add_external(simplewebserver ${simplewebserver_version})


set(APP_SOURCES
        src/elink-subscribe.cpp 
        src/web_server.hpp
        src/web_server.cpp
        web/index.html
        src/main_fmclient.cpp
        src/functions.hpp
        src/functions.cpp

        )

# others
felix_add_external(catch ${catch_version})

tdaq_add_executable(felm-client ${APP_SOURCES} src/main_fmclient.cpp)
target_link_libraries(felm-client netio rt pthread felix-client-lib felix-client-thread ${Boost_LIBRARIES})


# web server resources
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/share/felix-monitoring/web
#          DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_custom_target(felix-monitoring-web ALL
          COMMAND cmake -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/web ${CMAKE_CURRENT_BINARY_DIR}/share/felix-monitoring/web)
file(COPY ${FELIX_EXTERNAL_DIR}/bootstrap/${bootstrap_version}/
          DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/share/felix-monitoring/web
          PATTERN ".*" EXCLUDE)
file(COPY ${FELIX_EXTERNAL_DIR}/jquery/${jquery_version}/
          DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/share/felix-monitoring/web/js
          PATTERN ".*" EXCLUDE)
file(COPY ${FELIX_EXTERNAL_DIR}/datatables/${datatables_version}/media/
          DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/share/felix-monitoring/web
          PATTERN ".*" EXCLUDE)
file(COPY ${FELIX_EXTERNAL_DIR}/highcharts/${highcharts_version}/code/
          DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/share/felix-monitoring/web/js
          PATTERN ".*" EXCLUDE)
file(COPY ${FELIX_EXTERNAL_DIR}/mathjs/${mathjs_version}/
          DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/share/felix-monitoring/web/js
          PATTERN ".*" EXCLUDE)

