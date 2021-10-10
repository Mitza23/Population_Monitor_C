cmake_minimum_required(VERSION 3.16)
project(a23_Mitza23 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(a23_Mitza23
        domain.c
        domain.h
        validator.c
        validator.h repository.c repository.h service.c service.h ui.c ui.h utils.c utils.h undo_service.c undo_service.h test_service.c test_domain.c test_repo.c)
