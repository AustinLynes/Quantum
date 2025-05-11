project "QApplication"
    kind          "StaticLib"
    language      "C++"
    cppdialect    "C++17"
    staticruntime "on"
    systemversion "latest"
    warnings      "extra"

    targetdir     (BIN_DIR)
    objdir        (OBJ_DIR)

    files {
        "src/**.cpp",
    }
    includedirs {
        "include/QApplication/include/",
        "include/QWindow/include/",
        "src/"
    }
    links {
        
    }
    defines {

    }
