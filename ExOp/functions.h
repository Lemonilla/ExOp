#pragma once
#include "stdafx.h"
#include "def.h"

extern void getVersionNumber(uint32_t reg);
extern void saveDataAt(uint32_t keyRegister, uint32_t valueRegister);
extern void readDataAt(uint32_t keyRegister, uint32_t returnRegister);