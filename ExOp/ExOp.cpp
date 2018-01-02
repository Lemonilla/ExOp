// ExOp.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
//#include "functions.h"
#include "def.h"
#include "ExOp.h"

void getVersionNumber(uint32_t reg) {
    // open handle
    HANDLE psoHandle = GetCurrentProcess();
    uint32_t register_addr = NULL;

    // get our register location
    bool read = ReadProcessMemory(psoHandle, (LPVOID)REGISTER_PTR, (LPVOID)register_addr, PTR_SIZE, NULL);
    if (!read) return;// READ_REGISTER_LOCATION_ERROR;

    // write our new version number
    bool write = WriteProcessMemory(psoHandle, (LPVOID)(register_addr + 4 * reg), (LPVOID)DLL_VERSION, PTR_SIZE, NULL);
    if (!write) return;// WRITE_REGISTER_LOCATION_ERROR;

    // close handle
    CloseHandle(psoHandle);
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
