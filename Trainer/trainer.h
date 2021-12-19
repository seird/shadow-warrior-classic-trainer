#ifndef __TRAINER_H__
#define __TRAINER_H__


#include <stdint.h>
#include <stdbool.h>
#include <windows.h>


typedef struct {
	uintptr_t * array;
	size_t size;
} TOffsets;


typedef struct {
	DWORD id;
	HANDLE handle;
} TProcess;


/**
 * @brief Open a process by name
 * 
 * @param name 
 * @return TProcess 
 */
TProcess trainer_process_connect(const char * name);

/**
 * @brief Get a process id
 * 
 * @param name 
 * @return DWORD 
 */
DWORD trainer_process_id(const char * name);

/**
 * @brief Open a process by process id
 * 
 * @param pid 
 * @return HANDLE 
 */
HANDLE trainer_process_open(DWORD pid);


// External trainer

/**
 * @brief Get the base address of a module
 * 
 * @param pid 
 * @param name 
 * @return uintptr_t 
 */
uintptr_t trainer_address_module_base(DWORD pid, const char * name);

/**
 * @brief Dereference a multilevel pointer
 * 
 * @param process_handle 
 * @param base 
 * @param offsets 
 * @return uintptr_t 
 */
uintptr_t trainer_address_get(HANDLE process_handle, uintptr_t base, TOffsets * offsets);

/**
 * @brief Write bytes from src to dst
 * 
 * @param dst 
 * @param src 
 * @param size 
 * @param p_handle 
 */
void trainer_memory_write_protect(uint8_t * dst, uint8_t * src, size_t size, HANDLE p_handle);

/**
 * @brief Overwrite a memory area with 0x90 bytes
 * 
 * @param dst 
 * @param size 
 * @param p_handle 
 */
void trainer_memory_nop_protect(uint8_t * dst, size_t size, HANDLE p_handle);

/**
 * @brief Read memory from src to value
 * 
 * @param process 
 * @param src 
 * @param value 
 * @param size 
 * @return true 
 * @return false 
 */
bool trainer_memory_read(TProcess process, void * src, void * value, size_t size);

/**
 * @brief Write a value into memory
 * 
 * @param process 
 * @param dst 
 * @param value 
 * @param size 
 * @return true 
 * @return false 
 */
bool trainer_memory_write(TProcess process, void * dst, void * value, size_t size);


// Internal trainer

/**
 * @brief Get the base address of a module
 * 
 * @return uintptr_t 
 */
uintptr_t trainer_internal_address_module_base();

/**
 * @brief Dereference a multilevel pointer
 * 
 * @param base 
 * @param offsets 
 * @return uintptr_t 
 */
uintptr_t trainer_internal_address_get(uintptr_t base, TOffsets * offsets);

/**
 * @brief Write bytes from src to dst
 * 
 * @param dst 
 * @param src 
 * @param size 
 */
void trainer_internal_memory_write_protect(uint8_t * dst, uint8_t * src, size_t size);

/**
 * @brief Overwrite a memory area with 0x90 bytes
 * 
 * @param dst 
 * @param size 
 */
void trainer_internal_memory_nop_protect(uint8_t * dst, size_t size);

/**
 * @brief Read memory from src to value
 * 
 * @param address 
 * @param value 
 * @param size 
 */
void trainer_internal_memory_read(void * address, void * value, size_t size);

/**
 * @brief Write a value into memory
 * 
 * @param address 
 * @param value 
 * @param size 
 */
void trainer_internal_memory_write(void * address, void * value, size_t size);


#endif // __TRAINER_H__
