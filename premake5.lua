-- Makes a path relative to the folder containing this script file.
ROOT_PATH = function(path)
    return string.format("%s/%s", _MAIN_SCRIPT_DIR, path)
end

LIB_DIR = ROOT_PATH "Lib"
DEP_DIR  = ROOT_PATH "Dependencies"
TESTS_DIR = ROOT_PATH "QTests"

BIN_DIR  = ROOT_PATH "build/_/%{prj.name}"
OBJ_DIR  = ROOT_PATH "build/_/%{prj.name}"

WORKSPACE_NAME = "Quantum"
TESTS_NAME = "QTests"
START_PROJECT  = "Quantum"

include "workspace.lua"
include "projects.lua"

for _, path in ipairs(PROJECTS) do
    include(path .. "/premake5.lua")
end
