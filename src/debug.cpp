#include "debug.h"
#include <windows.h>
#include <fstream>
#include <string>

namespace debug {

    inline void Log(const std::string& message) {
        std::ofstream logFile("d3d11_proxy.log", std::ios_base::app);
        if (logFile.is_open()) {
            logFile << message << std::endl;
            logFile.close();
        }
    }

    inline void trace(const char* msg) {
        OutputDebugStringA(msg);
    }
}