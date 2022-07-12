cmake_minimum_required(VERSION 3.10)

add_executable(Thermostat 
../networking/socket/Socket.cc
../networking/socket/Socket.h
../networking/router/Router.cc
../networking/router/Router.h
../networking/http/HTTP.cc
../networking/http/HTTP.h
../networking/http/Payload.cc
../networking/http/Payload.h 
src/Thermostat.cc
src/Thermostat.h
src/main.cc)

