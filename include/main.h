#pragma once
#include <windows.h>
#define IMPORT __declspec(dllimport)

IMPORT int createTexture(const char *texFileName);
IMPORT void drawTexture(int id, int index, int level, int time, float sizeX, float sizeY, float centerX, float centerY, float posX, float posY, float rotation, float screenHeightScaleFactor, float r, float g, float b, float a);
typedef void (*PresentCallback)(void *);
IMPORT void presentCallbackRegister(PresentCallback cb);
IMPORT void presentCallbackUnregister(PresentCallback cb);
typedef void (*KeyboardHandler)(DWORD, WORD, BYTE, BOOL, BOOL, BOOL, BOOL);
IMPORT void keyboardHandlerRegister(KeyboardHandler handler);
IMPORT void keyboardHandlerUnregister(KeyboardHandler handler);
IMPORT void scriptWait(DWORD time);
IMPORT void scriptRegister(HMODULE module, void (*LP_SCRIPT_MAIN)());
IMPORT void scriptRegisterAdditionalThread(HMODULE module, void (*LP_SCRIPT_MAIN)());
IMPORT void scriptUnregister(HMODULE module);
IMPORT void scriptUnregister(void (*LP_SCRIPT_MAIN)());
IMPORT void nativeInit(UINT64 hash);
IMPORT void nativePush64(UINT64 val);
IMPORT PUINT64 nativeCall();
static void WAIT(DWORD time) { scriptWait(time); }
static void TERMINATE() { WAIT(MAXDWORD); }
IMPORT UINT64 *getGlobalPtr(int globalId);
IMPORT int worldGetAllVehicles(int *arr, int arrSize);
IMPORT int worldGetAllPeds(int *arr, int arrSize);
IMPORT int worldGetAllObjects(int *arr, int arrSize);
IMPORT int worldGetAllPickups(int *arr, int arrSize);
IMPORT BYTE *getScriptHandleBaseAddress(int handle);
enum eGameVersion : int
{
	VER_1_0_335_2_STEAM,
	VER_1_0_335_2_NOSTEAM,
	VER_1_0_350_1_STEAM,
	VER_1_0_350_2_NOSTEAM,
	VER_SIZE,
	VER_UNK = -1
};