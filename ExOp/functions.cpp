#include "def.h"
#include "stdafx.h"
#include "ExOp.h"

node* head;

/////////////////////////////////  Helper Functions ///////////////////////////////////

BOOL unallocatedRegisterTable()
{
	registerMemory = (uint32_t*) REGISTER_PTR;
	return (registerMemory == NULL);
}

void setRegister(uint32_t reg, uint32_t value)
{
	if (unallocatedRegisterTable()) return;
	*(uint32_t*)(*registerMemory + 4 * reg) = value;
}

uint32_t getRegister(uint32_t reg)
{
	if (unallocatedRegisterTable()) return -1;
	return *(uint32_t*)(*registerMemory + 4 * reg);
}

// returns a pointer to the node that has the key value key
// or NULL if it doesn't exist
// uses sequencial search, O(n) with best case being recently stored data
node* getNode(uint32_t key)
{
	node* current = head;
	while (current != NULL && head->key != key) current = current->next;
	return current;
}

// inserts a node into the list at the beginning with a given key and value
void insertNode(uint32_t key, uint32_t value)
{
	node* n = new node;
	n->key = key;
	n->value = value;
	n->next = head;
	head = n;
}

////////////////////////////////// Opcode Functions ////////////////////////////////////

// sets return register to the dll's version 
// number (0x000000000 - 0xFFFFFFFF)
void getVersionNumber(uint32_t returnRegister)
{
	setRegister(returnRegister, DLL_VERSION);
}

// saves value in the list at location key
// if a node already exists there it overwrites it
void saveDataAt(uint32_t keyRegister, uint32_t valueRegister)
{
	uint32_t key = getRegister(keyRegister);
	uint32_t value = getRegister(valueRegister);
	node* n;
	if ((n = getNode(key)) == NULL)
	{
		insertNode(key, value);
	}
	n->value = value;
}

// gets data at a given key or returns -1 (0xFFFFFFFF) if
// there is no data for the given key
void readDataAt(uint32_t keyRegister, uint32_t returnRegister)
{
	uint32_t key = getRegister(keyRegister);
	node* n = getNode(key);
	if (n == NULL) setRegister(returnRegister, -1);
	setRegister(returnRegister, n->value);
}

void clearData()
{
	node* tmp;
	while (head != NULL)
	{
		tmp = head->next;
		delete head;
		head = tmp;
	}
}