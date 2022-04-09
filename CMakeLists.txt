cmake_minimum_required(VERSION 3.10)

project(my_stepper VERSION 1.0 DESCRIPTION "stepper support")


IF(WIN32)
	set(PATH winMockup)
	add_library(mystepper SHARED
				${PATH}/my_stepper.cpp)
	message("!!!HEY!!! This may not work correctly on windows")
	message("!!!HEY!!! Use my_stepper.py from winMockup dir")
ELSE()
	set(PATH src)
	add_library(mystepper-objs
				OBJECT
				${PATH}/my_stepper.cpp
				${PATH}/my_stepper.hpp)

	target_compile_options(mystepper-objs
				PRIVATE
				-Wall -fPIC -O1 -pthread)

	add_library(mystepper
				SHARED
				$<TARGET_OBJECTS:mystepper-objs>)

	target_compile_options(mystepper
				PRIVATE
				-pthread)
	target_link_libraries(mystepper
				stdc++ crypt m rt wiringPi)
ENDIF()




