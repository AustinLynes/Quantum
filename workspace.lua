workspace (WORKSPACE_NAME)
    startproject (START_PROJECT)
    configurations {
        "Debug",
        "Release"
    }
    platforms {
        "x64"
    }
    filter "configurations:Debug"
        runtime  "Debug"
        symbols  "on"
        optimize "off"
    filter "configurations:Release"
        runtime  "release"
        symbols  "off"
        optimize "on"

    filter "platforms:x64"
        architecture "x64"
        