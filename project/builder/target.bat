@echo off
rem This file is the script to set path for ARM eabi tool chain.
set CURDIR=%~dp0
set path=%CURDIR%..\..\tools\cygwin\bin;%CURDIR%..\..\tools\cygwin\g++_arm_none_eabi\bin;%path%
@echo makefile option:
@echo 	make all\make:	build all project
@echo 	make clean:	clean output file
@echo 	make rebuild:	rebuild project
@echo 	debug_flash:	debug mode
@echo 	objfiles:	compile to object file
cd %CD%\make
cmd make