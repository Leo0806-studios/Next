/*
 * UEFI:SIMPLE - UEFI development made easy
 * Copyright ©️ 2014-2023 Pete Batard <pete@akeo.ie> - Public Domain
 * See COPYING for the full licensing terms.
 */
#pragma warning(push,0)
#include <efi.h>
#include <efilib.h>
#include <libsmbios.h>
#include <string.h>
#pragma warning(pop)

#include <intrin.h>


#include "GLOBALS.h"
#include "HEAP.h"
#include "STARTUP.h"

typedef  _Bool BOOL;
#if defined(_M_X64) || defined(__x86_64__)
static CHAR16* ArchName = L"x86 64-bit";
#elif defined(_M_IX86) || defined(__i386__)
static CHAR16* ArchName = L"x86 32-bit";
#elif defined (_M_ARM64) || defined(__aarch64__)
static CHAR16* ArchName = L"ARM 64-bit";
#elif defined (_M_ARM) || defined(__arm__)
static CHAR16* ArchName = L"ARM 32-bit";
#elif defined (_M_RISCV64) || (defined(__riscv) && (__riscv_xlen == 64))
static CHAR16* ArchName = L"RISC-V 64-bit";
#else
#  error Unsupported architecture
#endif
#define MiB(x) ((UINT64)(x) << 20)
#define GiB(x) ((UINT64)(x) << 30)





BOOL WasKeyPressed() {
	EFI_INPUT_KEY key;
	EFI_STATUS status;

	// Try to read a key without waiting
	status = ST->ConIn->ReadKeyStroke(ST->ConIn, &key);
	if (status == EFI_SUCCESS) {
		return TRUE; // A key was pressed
	}
	else if (status == EFI_NOT_READY) {
		return FALSE; // No key pressed, still waiting
	}
	else {
		Print(L"Error reading key: %r\n", status);
		return FALSE; // An error occurred
	}

}


// Application entrypoint (must be set to 'efi_main' for gnu-efi crt0 compatibility)
EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable)
{

	GlobalST = SystemTable;
	UINTN Event;

	EFI_STATUS InitStaus =InitBootloader(ImageHandle, SystemTable);
	if (EFI_ERROR(InitStaus)) {

	}


	
	// The platform logo may still be displayed → remove it
	//SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
	EFI_STATUS Status = { 0 };











	EFI_LOADED_IMAGE_PROTOCOL* LoadedImage =NULL;

	EFI_STATUS status = uefi_call_wrapper(BS->HandleProtocol, 3,
		ImageHandle,
		&gEfiLoadedImageProtocolGuid,
		(void**)&LoadedImage);

	if (EFI_ERROR(status)) {
		Print(L"Failed to get LoadedImageProtocol\n");
		SystemTable->ConIn->Reset(SystemTable->ConIn, FALSE);
		SystemTable->BootServices->WaitForEvent(1, &SystemTable->ConIn->WaitForKey, &Event);
	}
	Print(L"Loaded Image Protocol: %p\n", LoadedImage);

	EFI_FILE_IO_INTERFACE* FileSystem=NULL;

	status = uefi_call_wrapper(BS->HandleProtocol, 3,
		LoadedImage->DeviceHandle,
		&gEfiSimpleFileSystemProtocolGuid,
		(void**)&FileSystem);

	if (EFI_ERROR(status)) {
		Print(L"Failed to get FileSystem from boot device\n");
		SystemTable->ConIn->Reset(SystemTable->ConIn, FALSE);
		SystemTable->BootServices->WaitForEvent(1, &SystemTable->ConIn->WaitForKey, &Event);
	}
	Print(L"FileSystem Protocol: %p\n", FileSystem);
	
	EFI_FILE_HANDLE Root, CurrentDir;

	// Open volume
	status = uefi_call_wrapper(FileSystem->OpenVolume, 2, FileSystem, &Root);
	if (EFI_ERROR(status)) {
		Print(L"Failed to open volume\n");
		SystemTable->ConIn->Reset(SystemTable->ConIn, FALSE);
		SystemTable->BootServices->WaitForEvent(1, &SystemTable->ConIn->WaitForKey, &Event);
	}
	Print(L"Root Directory: %p\n", Root);
	EFI_FILE_HANDLE KernelFile;

	status = uefi_call_wrapper(Root->Open, 5, Root, &CurrentDir,
		L"efi\\boot", EFI_FILE_MODE_READ, 0);
	if (EFI_ERROR(status)) {
		Print(L"Failed to open EFI\\BOOT\n");
		SystemTable->ConIn->Reset(SystemTable->ConIn, FALSE);
		SystemTable->BootServices->WaitForEvent(1, &SystemTable->ConIn->WaitForKey, &Event);
	}
	Print(L"Current Directory: %p\n", CurrentDir);
	status = uefi_call_wrapper(CurrentDir->Open, 5, CurrentDir, &KernelFile,
		L"KERNEL.exe", EFI_FILE_MODE_READ, 0);
	if (EFI_ERROR(status)) {
		Print(L"KERNEL.exe not found\n");
		SystemTable->ConIn->Reset(SystemTable->ConIn, FALSE);
		SystemTable->BootServices->WaitForEvent(1, &SystemTable->ConIn->WaitForKey, &Event);
	}
	Print(L"Kernel File: %p\n", KernelFile);
	
	EFI_DEVICE_PATH* KernelPath;
	KernelPath = FileDevicePath(LoadedImage->DeviceHandle, L"EFI\\BOOT\\KERNEL.exe");

	EFI_HANDLE KernelImage;
	status = uefi_call_wrapper(BS->LoadImage, 6, FALSE, ImageHandle,
		KernelPath, NULL, 0, &KernelImage);

	if (EFI_ERROR(status)) {
		Print(L"Failed to load KERNEL.exe\n");
		SystemTable->ConIn->Reset(SystemTable->ConIn, FALSE);
		SystemTable->BootServices->WaitForEvent(1, &SystemTable->ConIn->WaitForKey, &Event);
	}
	Print(L"Kernel Image Handle: %p\n", KernelImage);
	GlobalST->BootServices->Stall(1000000);
	//SystemTable->ConOut->ClearScreen(SystemTable->ConOut);

	SystemTable->BootServices->Stall(1000000);
	SystemTable->RuntimeServices->SetVariable(L"BootInterface", &gBootInterfaceGuid, EFI_VARIABLE_NON_VOLATILE, sizeof(BOOT_DATA_INTERFACE*), &BootInterface);
		status = uefi_call_wrapper(BS->StartImage, 3, KernelImage, NULL, NULL);

}
// Global variables
EFI_SYSTEM_TABLE* GlobalST = NULL;
