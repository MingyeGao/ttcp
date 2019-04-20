cmake_minimum_required(VERSION 3.5)

project(ttcp)

aux_source_directory(. ROOT_DIR)

add_executable(ttcp ${ROOT_DIR})