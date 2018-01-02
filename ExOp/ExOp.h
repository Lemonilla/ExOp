#pragma once
#include "def.h"

#ifdef EXOP_EXPORTS
#define EXOP_API __declspec(dllexport)
#else
#define EXOP_API __declspec(dllimport)
#endif

extern "C" EXOP_API uint32_t Init();
extern "C" EXOP_API void getVersionNumber(uint32_t reg);
