#include "trainer.h"
#include <TlHelp32.h>
#include <stdio.h>


DWORD
trainer_process_id(const char * name)
{
    size_t size = strlen(name) + 1; // + '\0'
    wchar_t * name_wchar = (wchar_t *) malloc(sizeof(wchar_t) * size);
    size_t num_converted;
    mbstowcs_s(&num_converted, name_wchar, size, name, _TRUNCATE);

    DWORD proc_id = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 proc_entry;
        proc_entry.dwSize = sizeof(proc_entry);
        if (Process32First(hSnap, &proc_entry)) {
            do {
                if (!_wcsicmp(proc_entry.szExeFile, name_wchar)) {
                    proc_id = proc_entry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &proc_entry));
        }
    }
    CloseHandle(hSnap);

    free(name_wchar);
    
    return proc_id;
}


HANDLE
trainer_process_open(DWORD pid)
{
    return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
}


TProcess
trainer_process_connect(const char * name)
{
    TProcess process = {
        .id = 0,
        .handle = NULL
    };

    DWORD pid = trainer_process_id(name);

    if (pid == 0) {
        printf("Process could not be found.\n");
        return process;
    }

    HANDLE handle = trainer_process_open(pid);

    if (handle == NULL) {
        printf("Process could not be opened.\n");
        return process;
    }

    process.id = pid;
    process.handle = handle;
    return process;
}
