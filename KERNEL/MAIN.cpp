extern "C" {
#include <gnu-efi/inc/efi.h>
#include <gnu-efi/inc/efilib.h>
#include <gnu-efi/inc/efiapi.h>
#include <BOOT_DATA_INTERFACE.h>
}



extern "C" EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable) {
	InitializeLib(ImageHandle, SystemTable);
	Print(L"Hello, UEFI World!\n");
	return EFI_SUCCESS;
}      