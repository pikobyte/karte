:: =============================================================================
:: Karte
:: -----------------------------------------------------------------------------
:: WinBuild.bat
:: A compilation and build script which generated an executable file.
:: =============================================================================

:: Enable the use of the Microsoft compiler.
SET VS="C:\Program Files (x86)\Microsoft Visual Studio\"
CALL %VS%"2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" amd64

:: Define the project path, source, include, build and output folders, as well
:: as external library names.
SET PROJ = %USERPROFILE%"\Documents\pikobyte\karte\"
SET SRC=%PROJ%"src\*.c"
SET INC=%PROJ%include\
SET LIBS=SDL2.lib SDL2main.lib SDL2_image.lib SDL2_mixer.lib SDL2_ttf.lib
SET BUILD=%PROJ%build\
SET OUT=%PROJ%bin\karte.exe

:: Define dependency include and library folders.
SET DEP_INC=%PROJ%deps\include\
SET DEP_LIB=%PROJ%deps\lib\x64\

:: Build flags listed as thus:
::  > /cgthreads8 - compile across 8 threads.
::  > /Fe - executable output.
::  > /Fo - object file output.
::  > /Fd - debug file output.
::  > /Od - disable optimisations.
::  > /W4 - enable level 4 warnings.
::  > /WX - treat warnings as errors.
::  > /Zi - generates complete debugginf information.
SET FLAGS=/cgthreads8 /Fe%OUT% /Fo%BUILD% /Fd%BUILD% /Od /W4 /WX /Zi

:: Link flags listed as thus:
::  > /LIBPATH - additional library folders to search.
::  > /SUBSYSTEM - sets the default entry point.
SET LINK_FLAGS=/LIBPATH:%DEP_LIB% %LIBS% /SUBSYSTEM:WINDOWS

:: Compile the program.
cl.exe %SRC% /I%INC% /I%DEP_INC% %FLAGS% /link %LINK_FLAGS%