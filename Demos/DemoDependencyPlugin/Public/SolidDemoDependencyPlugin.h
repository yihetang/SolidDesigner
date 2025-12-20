#pragma once
#include "AliceMacroDefinitions.h"
#if defined(_WIN32)
#ifdef ALICE_DEMO_DEPEND_PLUGIN_HOME
#define ALICE_DEMO_DEPEND_PLUGIN_EXPORT DLL_EXPORT
#else
#define ALICE_DEMO_DEPEND_PLUGIN_EXPORT DLL_IMPORT
#endif
#else
#define ALICE_DEMO_DEPEND_PLUGIN_EXPORT __attribute__((visibility("default")))
#endif

