# Compiler
$compiler = "cl.exe"
$flags = "/Od /favor:blend /std:c++17"
$includes = "/I ..\include"
$libraries = "/link opengl32.lib, gdi32.lib, user32.lib, shell32.lib, ..\lib\glfw3_mt.lib, ..\lib\glfw3.lib"

# Files
$sources = "..\src\main.cpp ..\src\window.cpp ..\src\graphic.cpp ..\src\shader.cpp ..\src\shader_program.cpp ..\src\vertex_array.cpp ..\src\input.cpp ..\src\object.cpp ..\src\camera.cpp ..\src\display.cpp ..\src\glad.c"
$program = "KawaiEngine"

Invoke-Expression "$compiler /Fe:$program.exe $sources $flags $includes $libraries"
Copy-Item ..\shaders . -Recurse -Force
Remove-Item *.obj -Force
