# Dynamic makefile for Windows systems
#
# File:     makefile
# Version:  0.5
#
# Author:   Joeri Kok
# Date:     February 2021
#
# Description:
#   Generates makefile recipes for Windows systems by searching through file
#   header inclusions within source files.
#
# PATH_X86_CXX := d:\arduino\i686-7.3.0-release-posix-dwarf-rt_v5-rev0\mingw32\bin
# PATH_X86_MAKE := d:\arduino\avr-gcc-9.2.0-x86-mingw\avr-gcc-9.2.0-x86-mingw\bin
#
# PATH_X64_CXX := d:\arduino\i686-7.3.0-release-posix-dwarf-rt_v5-rev0\mingw64\bin
# PATH_X64_MAKE := c:\program files\avr-gcc-10.1.0-x64-windows\bin
#
OUT_FILE := tic-tac-toe.exe

SRC_DIR := .
HDR_DIR := .
VPATH = $(SRC_DIR):$(HDR_DIR)

SFML_PATH := d:/arduino/sfml-2.5.1
SFML_LIB := -L $(SFML_PATH)/lib/x64
SFML_INC := -I $(SFML_PATH)/include

# note: to hide the console window, add the following flag: -mwindows
CXXFLAGS := -std=c++17 -pedantic -Wall -Wextra -Werror -Ofast
CXX := g++

# extract file names from all CPP files within the SRC_DIR directory
# and replace the .cpp extensions with .o
targets := $(patsubst %.cpp,%.o,$(notdir $(wildcard $(SRC_DIR)/*.cpp)))

# search through the HPP and CPP file specified by the $1 (first) argument and
# only return the strings that start with '#include "' (note the double quote)
find_includes = findstr 2^>nul /b /i /c:"\#include "^" "$(HDR_DIR)\\$1.hpp" "$(SRC_DIR)\\$1.cpp"

# for every header file found, add the corresponding TPP file
# (template definition), if it exists
add_tpp_files = (echo %%~nxe & if exist "%%~ne.tpp" echo %%~ne.tpp)

# walk through the output of the find_includes command, returning the 2nd token
# delimited by double quotes while only keeping the file name and extension
find_dependencies = for /f tokens^=2^ delims^=^" %%e in ('$(find_includes)') do $(add_tpp_files)

# creates a recipe for a target based on the 1st argument it receives and runs
# the find_dependencies command to look for all corresponding header files
define create_target_recipe
    $1.o: $1.cpp $(shell $(find_dependencies))
		$(CXX) $(CXXFLAGS) $$(FLAGS) -c $$< $$(SFML_INC) -o $$@
endef

cli: FLAGS := -D CLI
cli: targets := $(filter-out graphical-interface.o, $(targets))
cli: build

gui: FLAGS     := -D SFML_STATIC -D GUI -mwindows
gui: SFML_STL  := -lsfml-main -lsfml-graphics-s -lsfml-window-s -lsfml-system-s
gui: WIN_STL   := -lgdi32 -lopengl32 -lws2_32 -lwinmm -lfreetype
gui: targets   := $(filter-out cmd-line-interface.o, $(targets))
gui: build

build: $(targets)
	$(CXX) $(CXXFLAGS) $(FLAGS) $(targets) -o $(OUT_FILE) $(SFML_LIB) $(SFML_STL) $(WIN_STL)

# iterate through all the targets found and create a recipe for each of them
$(foreach target, $(basename $(targets)), $(eval $(call create_target_recipe,$(target))))

clean:
	del $(targets) 2>nul

.PHONY: cli gui build clean
