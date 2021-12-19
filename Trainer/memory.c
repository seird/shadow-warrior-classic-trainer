#include "trainer.h"


#define NOP 0x90


void
trainer_memory_write_protect(uint8_t * dst, uint8_t * src, size_t size, HANDLE process_handle)
{
    DWORD oldprotect;
    VirtualProtectEx(process_handle, dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
    WriteProcessMemory(process_handle, dst, src, size, NULL);
    VirtualProtectEx(process_handle, dst, size, oldprotect, &oldprotect);
}


void
trainer_internal_memory_write_protect(uint8_t * dst, uint8_t * src, size_t size)
{
    DWORD oldprotect;
    VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
    memcpy(dst, src, size);
    VirtualProtect(dst, size, oldprotect, &oldprotect);
}


void
trainer_memory_nop_protect(uint8_t * dst, size_t size, HANDLE process_handle)
{
    uint8_t * array_nop = (uint8_t *)malloc(sizeof(uint8_t) * size);
    if (array_nop == NULL) return;
    memset(array_nop, NOP, size);

    trainer_memory_write_protect(dst, array_nop, size, process_handle);

    free(array_nop);
}


void
trainer_internal_memory_nop_protect(uint8_t * dst, size_t size)
{
    DWORD oldprotect;
    VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
    memset(dst, NOP, size);
    VirtualProtect(dst, size, oldprotect, &oldprotect);
}


bool
trainer_memory_read(TProcess process, void * src, void * value, size_t size)
{
    return ReadProcessMemory(process.handle, src, value, size, NULL);
}


bool
trainer_memory_write(TProcess process, void * dst, void * value, size_t size)
{
    return WriteProcessMemory(process.handle, dst, value, size, NULL);
}


void
trainer_internal_memory_read(void * src, void * value, size_t size)
{
    memcpy(value, src, size);
}


void
trainer_internal_memory_write(void * dst, void * value, size_t size)
{
    memcpy(dst, value, size);
}
