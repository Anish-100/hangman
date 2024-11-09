#include <iostream>
#include <windows.h>

typedef void (*HelloFunc)();

int main() {
    // Load DLL
    HMODULE dll = LoadLibrary(TEXT("sfml-graphics-2.dll"));
    if (dll == NULL) {
        std::cerr << "Could not load the DLL" << std::endl;
        return 1;
    }

    // Get function from DLL
    HelloFunc hello = (HelloFunc)GetProcAddress(dll, "main");
    if (hello == NULL) {
        std::cerr << "Could not find the function" << std::endl;
        return 1;
    }

    // Call function
    hello();

    // Free DLL
    FreeLibrary(dll);
    return 0;
}
