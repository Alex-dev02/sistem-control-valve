cmake_minimum_required(VERSION 3.10)

add_executable(Thermostat 
../../networking/router/Router.cc
../../networking/router/Router.h
../../networking/http/HTTP.cc
../../networking/http/HTTP.h
../../networking/http/Payload.cc
../../networking/http/Payload.h 
src/main.cc)

