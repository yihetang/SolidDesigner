#pragma once
// 此头文件包含DLL导出的宏
#include "AliceMacroDefinitions.h"
#include <iostream>

#if defined(_WIN32)
#ifdef SOLID_DESIGNER_INTERACTION_HOME
#define SOLID_DESIGNER_INTERACTION_EXPORT DLL_EXPORT
#else
#define SOLID_DESIGNER_INTERACTION_EXPORT DLL_IMPORT
#endif
#else
#define SOLID_DESIGNER_INTERACTION_EXPORT __attribute__((visibility("default")))
#endif

namespace
{
    void InitTest()
    {
        int i = 0;
        std::cout << "Here is init test..." << std::endl;
    }

    void UnInitTest()
    {
        int i = 0;
        std::cout << "Here is uninit test..." << std::endl;
    }
}


extern "C" void InitializePlugin()
{
    InitTest();
}


extern "C" void UnInitializePlugin()
{
    UnInitTest();
}



