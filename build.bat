@echo off

IF "%~1"=="" GOTO PrintHelp
IF "%~1"=="-h" GOTO PrintHelp
IF "%~1"=="-help"  GOTO PrintHelp

IF "%~1"=="-build"  GOTO Build
IF "%~1"=="-generate"  GOTO GenerateProjects
IF "%~1"=="-clean"  GOTO Clean
IF "%~1"=="-build-clean"  GOTO CleanBuild
IF "%~1"=="-fullbuild" GOTO FULLBUILD

echo ERROR: Unknown command "%~1"
echo Use -h or -help to see available commands.
GOTO Done

:CleanBuild
    echo Performing clean build...
    echo Cleaning Visual Studio generated files...
    del /S /Q *.sln *.vcxproj *.vcxproj.filters *.vcxproj.user *.ncb *.suo *.user *.opensdf *.sdf *.ipch *.tlog
    echo Cleaning complete.
    GOTO Build

:PrintHelp
    echo.
    echo ==============================
    echo Quantum Build System - Help
    echo ==============================
    echo Available commands:
    echo -------------------
    echo -build        Compile the project.
    echo -clean        Remove all binaries and generated files.
    echo -build-clean  Clean and then build the project.
    echo -fullbuild    Generate project files and build.
    echo -generate     Generate Visual Studio project files.
    echo.
    echo Supported Visual Studio versions:
    echo ---------------------------------
    echo vs2005        Generate Visual Studio 2005 project files.
    echo vs2008        Generate Visual Studio 2008 project files.
    echo vs2010        Generate Visual Studio 2010 project files.
    echo vs2012        Generate Visual Studio 2012 project files.
    echo vs2013        Generate Visual Studio 2013 project files.
    echo vs2015        Generate Visual Studio 2015 project files.
    echo vs2017        Generate Visual Studio 2017 project files.
    echo vs2019        Generate Visual Studio 2019 project files.
    echo vs2022        Generate Visual Studio 2022 project files.
    echo xcode4        Generate Apple Xcode 4 project files.
    echo.
    echo Example usage:
    echo --------------
    echo To build the project, run: build.bat -build
    echo To clean the project, run: build.bat -clean
    echo To generate project files, run: build.bat -generate
    echo.
    echo ==============================
    GOTO Done

:GenerateProjects
    echo Generating Visual Studio 2022 project files...
    build\premake\premake5.exe vs2022 
    echo Project files generated successfully.
    GOTO Done

:Build
    echo Starting build process...
    if not defined DevEnvDir (
        echo Setting up Visual Studio environment...
        call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
    )

    set solutionFile="Quantum.sln"
    echo Building solution: %solutionFile%
    msbuild /t:Build /p:Configuration=Debug /p:Platform=x64 %solutionFile%
    echo Build completed successfully.
    
    GOTO Done

:FULLBUILD
    echo Performing full build (generate + compile)...
    build\premake\premake5.exe vs2022 
    echo Project files generated successfully.

    if not defined DevEnvDir (
        echo Setting up Visual Studio environment...
        call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
    )

    set solutionFile="Quantum.sln"
    echo Building solution: %solutionFile%
    msbuild /t:Build /p:Configuration=Debug /p:Platform=x64 %solutionFile%
    echo Full build completed successfully.

    GOTO Done

:Clean
    echo Cleaning Visual Studio generated files...
    del /S /Q *.sln *.vcxproj *.vcxproj.filters *.vcxproj.user *.ncb *.suo *.user *.opensdf *.sdf *.ipch *.tlog
    echo Cleaning complete.

:Done
    echo.
    echo ==============================
    echo Done.
    echo ==============================
    echo.
    exit /b 0
