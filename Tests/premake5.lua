project "QTests"
    kind          "ConsoleApp"
    language      "C++"
    cppdialect    "C++17"
    staticruntime "on"
    systemversion "latest"
    warnings      "extra"
    targetdir     (BIN_DIR)
    objdir        (OBJ_DIR)
    files {
        "src/**.h",
        "src/**.hpp",
        "src/**.cpp",
    }
    includedirs {
        "src",
        ROOT_PATH "projects/QGraph/include",
        ROOT_PATH "projects/QML/include",
        ROOT_PATH "projects/QWindow/include",
    }
    links {
        "QGraph",
        "QML",
        "QWindow",
    }
    defines {

    }
