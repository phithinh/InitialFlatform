@echo off
set Cr_PATH=%~dp0
mkdir %Cr_PATH%..\includes
set path=%path%;%Cr_PATH%..\..\tools\perl\perl\bin
set ROOT=../../../..
set PREFIX=./
cd ..\..\tools\builder\FileList\bin

Perl GenerateTxtFileList.pl ..\..\..\..\project\builder\Project.flist -prefix=$(ROOT) -root=%ROOT% -o=..\..\..\..\project\builder\filelist.txt
echo Pasing file list is done.
Perl GenerateFileMakef.pl ..\..\..\..\project\builder\Project.flist -compiler=DCOM_GNU -root=%ROOT% -o=..\..\..\..\project\builder\filelist.mk
echo Initialization is done.

REM Creating header file
set CYGWIN_PATH=%Cr_PATH%..\..\tools\cygwin\bin
set PATH=%CYGWIN_PATH%;%PATH%
cd %Cr_PATH%\make
echo Creating header file
make header
pause