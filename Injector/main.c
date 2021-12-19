#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "trainer/trainer.h"


static void
print_usage(char * path)
{
	printf("Usage:\n"
			"%s <process_name> <full_path_to_dll>\n",
			path);
}


static bool
inject(const char * name_process, const char * path_dll)
{
    // Verify that the dll file exists
    DWORD fattr = GetFileAttributesA(path_dll);
    if (!(fattr != INVALID_FILE_ATTRIBUTES && !(fattr & FILE_ATTRIBUTE_DIRECTORY))) {
        return false;
    }

    // Open a handle to the process
    TProcess process = trainer_process_connect(name_process);
    if (process.id == 0 || process.handle == NULL) {
        return false;
    }

    // Allocate memory for path_dll in the target process
    LPVOID p_dll_path = VirtualAllocEx(process.handle, 0, strlen(path_dll) + 1, MEM_COMMIT, PAGE_READWRITE);
    if (p_dll_path == NULL) {
        return false;
    }

    // Write path_dll to the allocated memory in the target process
    WriteProcessMemory(process.handle, p_dll_path, (LPVOID)path_dll, strlen(path_dll) + 1, 0);

    // Create a remote thread in the target process that runs LoadLibraryA with
    HANDLE hThread = CreateRemoteThread(process.handle, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, p_dll_path, 0, 0);

    bool thread_ok = false;
    if (hThread) {
        thread_ok = WaitForSingleObject(hThread, INFINITE) == 0;
    }

    VirtualFreeEx(process.handle, p_dll_path, 0, MEM_RELEASE);

    return thread_ok;
}


int
main(int argc, char * argv[])
{
	if (argc != 3) {
		print_usage(argv[0]);
		return 0;
	}

    if (inject(argv[1], argv[2])) {
        puts("Injection succeeded.\n");
    } else {
        puts("Injection failed.\n");
    }

	return 0;
}
