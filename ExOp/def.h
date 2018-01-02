#ifndef DEFINITIONS
#define DEFINITIONS

// Game Addresses
#define OPCODE_TLB_BASE_ADDR 			0x009CCC00
#define OPCODE_TLB_CALLBACK_ADDR		0x009CCC04
#define REGISTER_PTR					0x00A954B0

// Misc
#define PTR_SIZE 						sizeof(uint32_t)
#define DLL_VERSION						1

// Error Codes
#define READ_TABLE_OFFSET_ERROR 		0x80000001
#define WRITE_TO_PROCESS_ERROR 			0x80000002
#define READ_REGISTER_LOCATION_ERROR	0x80000003
#define WRITE_REGISTER_LOCATION_ERROR	0x80000004

// Argument setup
#define ARGUMENTS_ 						0x006B101C
#define ARGUMENTS_R						0x006B1040
#define ARGUMENTS_RR					0x006B1058

// Types
typedef struct
{
	uint32_t table;
	uint32_t code;
	uint32_t argumentSetup;
	uint32_t functionPtr;
} opcodeInsert;

typedef struct
{
	node* next, prev;
	uint32_t key, value;
} node;
#endif
