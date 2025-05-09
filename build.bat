@echo off

IF "%~1"=="-h" GOTO PrintHelp
IF "%~1"=="-help"  GOTO PrintHelp

IF "%~1"=="-build"  GOTO Build
IF "%~1"=="-generate"  GOTO GenerateProjects
IF "%~1"=="-clean"  GOTO Clean

IF "%~1"=="" GOTO FULLBUILD

GOTO Done

:PrintHelp
    echo.
    echo compile Compile the project.
    echo clean                Remove all binaries and generated files
    echo.
    echo vs2005            Generate Visual Studio 2005 project files
    echo vs2008            Generate Visual Studio 2008 project files
    echo vs2010            Generate Visual Studio 2010 project files
    echo vs2012            Generate Visual Studio 2012 project files
    echo vs2013            Generate Visual Studio 2013 project files
    echo vs2015            Generate Visual Studio 2015 project files
    echo vs2017            Generate Visual Studio 2017 project files
    echo vs2019            Generate Visual Studio 2019 project files
    echo vs2022            Generate Visual Studio 2022 project files
    echo xcode4            Generate Apple Xcode 4 project files

    GOTO Done

:GenerateProjects
    build\premake\premake5.exe vs2022 
    GOTO Done

:Build
    if not defined DevEnvDir (
        call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
    )

    set solutionFile="Quantum.sln"
        msbuild /t:Build /p:Configuration=Debug /p:Platform=x64 %solutionFile%
    
    GOTO Done

:FULLBUILD
    
    build\premake\premake5.exe vs2022 

    if not defined DevEnvDir (
        call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
    )

    set solutionFile="Quantum.sln"
        msbuild /t:Build /p:Configuration=Debug /p:Platform=x64 %solutionFile%

    GOTO Done

:Clean
    echo Cleaning Visual Studio generated files...
    del /S /Q *.sln *.vcxproj *.vcxproj.filters *.vcxproj.user *.ncb *.suo *.user *.opensdf *.sdf *.ipch *.tlog
    echo Cleaning complete.
    GOTO Done

:Done
    echo.
    echo Done.
    echo.
    exit /b 0