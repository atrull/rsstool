::
::
:: // configure - create config.mak and config.h
::
:: // Copyright (c) 2005 NoisyB
::
::
@echo off
::if not exist cl.exe
echo IMPORTANT: The PATH enviroment variable must include the path to the Visual C++ compiler (CL.EXE)
cl configure.c -o config.status
config.status
