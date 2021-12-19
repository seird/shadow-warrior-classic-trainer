#include "trainer.h"
#include <TlHelp32.h>


uintptr_t
trainer_address_get(HANDLE process_handle, uintptr_t base, TOffsets * offsets)
{
    uintptr_t address = base;
    uintptr_t * p;

    for (p = offsets->array; p < offsets->array + offsets->size - 1; p++) {
        if (ReadProcessMemory(process_handle, (void *)(address + *p), &address, sizeof(address), NULL) == 0) {
            return 0;
        }
    }

    return address + *p; // add the final offset
}


uintptr_t
trainer_internal_address_get(uintptr_t base, TOffsets * offsets)
{
    uintptr_t address = base;
    uintptr_t * p;

    for (p = offsets->array; p < offsets->array + offsets->size - 1; p++) {
        if (address < base) return 0;
        address = *(uintptr_t *)(address + *p);
    }

    return address + *p; // add the final offset
}


uintptr_t
trainer_address_module_base(DWORD pid, const char * name)
{
    size_t size = strlen(name) + 1; // + '\0'
    wchar_t * name_wchar = (wchar_t *) malloc(sizeof(wchar_t) * size);
    size_t num_converted;
    mbstowcs_s(&num_converted, name_wchar, size, name, _TRUNCATE);

    uintptr_t base_address = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 mod_entry;
        mod_entry.dwSize = sizeof(mod_entry);
        if (Module32First(hSnap, &mod_entry)) {


            do {
                if (!_wcsicmp(mod_entry.szModule, name_wchar)) {
                    base_address = (uintptr_t)mod_entry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &mod_entry));
        }

    }
    CloseHandle(hSnap);

    free(name_wchar);
    
    return base_address;
}


uintptr_t
trainer_internal_address_module_base()
{
    return (uintptr_t)GetModuleHandle(NULL);
}
