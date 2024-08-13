cmake_minimum_required(VERSION 3.28)
project(authentication_app_cpp)

set(CMAKE_CXX_STANDARD 23)

add_executable(authentication_app_cpp src/main.cpp
        src/Auth.cpp
        include/authentication-app/Auth.h
        include/authentication-app/User.h
        src/Application.cpp
        include/authentication-app/Application.h
        include/authentication-app/Request.h
        src/Request.cpp
        include/authentication-app/JSONParseable.h
        include/authentication-app/RequestException.h
        include/authentication-app/network/request/SignupRequest.hpp
        include/authentication-app/network/response/SignupResponse.hpp
        include/authentication-app/network/request/LoginRequest.hpp
        include/authentication-app/network/response/LoginResponse.hpp
        src/Cryptor.cpp
        include/authentication-app/Cryptor.hpp
        include/authentication-app/network/response/GetUserResponse.hpp
        include/authentication-app/exceptions/FileNotFound.hpp
        include/authentication-app/UserDetails.hpp
        src/DetailsManager.cpp
        include/authentication-app/DetailsManager.hpp
        include/authentication-app/network/request/CreateDetailsRequest.hpp
        include/authentication-app/network/response/CreateDetailsResponse.hpp
)

find_package(unofficial-curlpp CONFIG REQUIRED)
target_link_libraries(authentication_app_cpp PRIVATE unofficial::curlpp::curlpp)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(authentication_app_cpp PRIVATE nlohmann_json::nlohmann_json)

find_package(botan CONFIG REQUIRED)
target_link_libraries(authentication_app_cpp PRIVATE Botan::Botan-static)