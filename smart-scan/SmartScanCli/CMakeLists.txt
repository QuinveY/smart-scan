add_executable(smartscan_main SmartScanCLI.cpp)
add_library(smartscan_config SmartScanConfig.cpp)
target_link_libraries(smartscan_main simpleble::simpleble smartscan_config AT CSV data exceptions point3 service controller trigger )
