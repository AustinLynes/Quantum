project "Quantum"
    kind          "ConsoleApp"
    language      "C++"
    cppdialect    "C++17"
    staticruntime "on"
    systemversion "latest"
    
    warnings      "extra"

    targetdir     (BIN_DIR)
    objdir        (OBJ_DIR)
    files {
        "src/**.cpp",
        "src/**.c",
    }
    includedirs {
        "include/",
        "src/",

        "../Dependencies/glad/include/",
        
        "../Lib/QWindow/include/",
        "../Lib/QApplication/include/",
    }
    links {
        "QApplication",
        "QWindow",
    }
    defines {

    }
