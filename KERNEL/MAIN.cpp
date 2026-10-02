extern "C" {
#include <gnu-efi/inc/efi.h>
#include <gnu-efi/inc/efilib.h>
#include <gnu-efi/inc/efiapi.h>
#include <BOOT_DATA_INTERFACE.h>
}
BOOT_DATA_INTERFACE* interface;


extern "C" EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable) {
	InitializeLib(ImageHandle, SystemTable);
	Print(L"Transferred control to kernel");
	UINTN size = sizeof(BOOT_DATA_INTERFACE*);
	SystemTable->RuntimeServices->GetVariable((wchar_t*)L"BootInterface", (EFI_GUID*) & gBootInterfaceGuid, NULL, &size, &interface);
	Print(L"BootInterface Version: %d\n", interface->Version); 
	Print(L"BootInterface Size: %d\n", interface->Size);
	Print(L"BootInterface SystemTable: %p\n", interface->SystemInterface.SystemTable);
	while(true){}
	return EFI_SUCCESS;
}      