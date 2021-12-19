# Trainer


```c
typedef struct {
	uintptr_t * array;
	size_t size;
} TOffsets;


typedef struct {
	DWORD id;
	HANDLE handle;
} TProcess;


TProcess trainer_process_connect(const char * name);
DWORD trainer_process_id(const char * name);
HANDLE trainer_process_open(DWORD pid);


// External trainer

uintptr_t trainer_address_module_base(DWORD pid, const char * name);
uintptr_t trainer_address_get(HANDLE process_handle, uintptr_t base, TOffsets * offsets);

void trainer_memory_write_protect(uint8_t * dst, uint8_t * src, size_t size, HANDLE p_handle);
void trainer_memory_nop_protect(uint8_t * dst, size_t size, HANDLE p_handle);
bool trainer_memory_read(TProcess process, void * src, void * value, size_t size);
bool trainer_memory_write(TProcess process, void * dst, void * value, size_t size);


// Internal trainer

uintptr_t trainer_internal_address_module_base();
uintptr_t trainer_internal_address_get(uintptr_t base, TOffsets * offsets);

void trainer_internal_memory_write_protect(uint8_t * dst, uint8_t * src, size_t size);
void trainer_internal_memory_nop_protect(uint8_t * dst, size_t size);
void trainer_internal_memory_read(void * address, void * value, size_t size);
void trainer_internal_memory_write(void * address, void * value, size_t size);
```
