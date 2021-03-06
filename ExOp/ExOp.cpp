// ExOp.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "functions.h"
#include "def.h"
#include "ExOp.h"

// Register memory pointer
uint32_t* registerMemory;



uint32_t init() {
	registerMemory = (uint32_t*) REGISTER_PTR;
	opcodeInsert opcodeTable[] = {
		{ // ExOp_clear_memory
			0xF9, 0xFC,
			ARGUMENTS_,
			(uint32_t )clearData
		},
		{ // ExOp_store_memory RR
			0xF9,0xFD,
			ARGUMENTS_RR,
			(uint32_t) saveDataAt
		},
		{ // ExOp_load_memory RR
			0xF9,0xFE,
			ARGUMENTS_RR,
			(uint32_t) readDataAt
		},
        { // ExOp_get_version R
            0xF9, 0xFF,
            ARGUMENTS_R,
            (uint32_t) getVersionNumber
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

        *(uint32_t*) (OPCODE_TLB_CALLBACK_ADDR + 8 * code) = opcodeTable[i].functionPtr;
        *(uint32_t*) (OPCODE_TLB_BASE_ADDR + 8 * code) = opcodeTable[i].argumentSetup;

        i++;
    }
    return 0;
}
