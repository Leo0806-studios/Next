extern "C" {
#include <efi.h>
#include <efilib.h>
#include <efiapi.h>
#include <BOOT_DATA_INTERFACE.h>
}
//BOOT_DATA_INTERFACE* interface;


extern "C" EFI_STATUS _KERNEL_MAIN(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable) {
	InitializeLib(ImageHandle, SystemTable);
	Print((CHAR16*)L"Transferred control to kernel");
	BOOT_DATA_INTERFACE* interface = nullptr;
	UINTN size = sizeof(interface);

	EFI_STATUS status = SystemTable->RuntimeServices->GetVariable(
		(CHAR16*)L"BootInterface",
		(EFI_GUID*)&gBootInterfaceGuid,
		nullptr,
		&size,
		&interface
	);

	if (EFI_ERROR(status) || interface == nullptr) {
		Print((CHAR16*)L"GetVariable failed: %r\n", status);
		return status;
	}

	Print((CHAR16*)L"BootInterface Version: %d\n", interface->Version);
	Print((CHAR16*)L"BootInterface Size: %d\n", interface->Size);
	Print((CHAR16*)L"BootInterface SystemTable: %p\n", interface->SystemInterface.SystemTable);
	while(true){}
	return EFI_SUCCESS;
}      