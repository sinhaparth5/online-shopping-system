set(CONFIG_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/config/database.cpp)

set(CONTROLLER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/controllers/ProductController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/controllers/UserController.cpp)

set(MODEL_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/models/User.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/models/UserDAO.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/models/ProductDAO.cpp)

set(UTILS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/DatabaseInitializer.cpp)

# Combine all sources
set(SOURCES
    ${CONFIG_SOURCES}
    ${CONTROLLER_SOURCES}
    ${MODEL_SOURCES}
    ${UTILS_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

# Create library target
add_library(shop_lib STATIC ${SOURCES})

target_include_directories(shop_lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(shop_lib
    PUBLIC
    PkgConfig::SQLite3
    OpenSSL::SSL
    OpenSSL::Crypto
)

# Create executable target
add_executable(shop_exe
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_link_libraries(shop_exe
    PRIVATE
    shop_lib
)