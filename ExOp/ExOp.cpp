// ExOp.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
//#include "functions.h"
#include "def.h"
#include "ExOp.h"

// Register memory pointer
uint32_t *registerMemory = (uint32_t*)REGISTER_PTR;

void getVersionNumber(uint32_t reg) {
    if (*registerMemory != NULL) {
        *(uint32_t*)(*registerMemory + 4 * reg) = DLL_VERSION;
    }
}

uint32_t Init() {
    opcodeInsert opcodeTable[] = {
        { // ExOp_get_dll_version_number R
            0xF9, 0xFF,
            ARGUMENTS_R,
            (uint32_t)getVersionNumber
        },
        // TAIL INSERT TO STOP US
        {
            NULL,
            NULL,
            NULL,
            NULL
        }
    };

    // Write in our code
    int i = 0;
    uint32_t code;
    while (opcodeTable[i].table != NULL) {
        code = opcodeTable[i].code;
        switch (opcodeTable[i].table) {
            case 0xF8:
            code = code + 0x0100; break;
            case 0xF9:
            code = code + 0x0200; break;
            default:
            return READ_TABLE_OFFSET_ERROR;
        }

        *(uint32_t*)(OPCODE_TLB_CALLBACK_ADDR + 8 * code) = opcodeTable[i].functionPtr;
        *(uint32_t*)(OPCODE_TLB_BASE_ADDR + 8 * code) = opcodeTable[i].argumentSetup;

        i++;
    }
    return 0;
}
