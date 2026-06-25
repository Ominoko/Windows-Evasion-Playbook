#include <windows.h>
#include <iostream>
#include <vector>

int main()
{
    // Get the handle and base address of the already loaded ntdll.dll
    HMODULE dirtyNtdll = GetModuleHandleA("ntdll.dll");
    if (!dirtyNtdll) {
        std::cerr << "Failed to get ntdll.dll handle.\n";
        return 1;
    }

    // Read the clean ntdll.dll from disk
    HANDLE cleanNtdll = CreateFileA("C:\\Windows\\System32\\ntdll.dll", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (cleanNtdll == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open ntdll.dll from disk.\n";
        return 1;
    }

    DWORD fileSize = GetFileSize(cleanNtdll, NULL);
    std::vector<BYTE> fileBuffer(fileSize);
    DWORD bytesRead;
    ReadFile(cleanNtdll, fileBuffer.data(), fileSize, &bytesRead, NULL);
    CloseHandle(cleanNtdll);

    // Parse PE headers and find the .text section
    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)fileBuffer.data();
    PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)((BYTE*)fileBuffer.data() + pDosHeader->e_lfanew);

    PIMAGE_SECTION_HEADER pSectionHeader = IMAGE_FIRST_SECTION(pNtHeaders);
    for (int i = 0; i < pNtHeaders->FileHeader.NumberOfSections; i++) {
        // Looking for .text
        if (strcmp((char*)pSectionHeader->Name, ".text") == 0) {

            BYTE* pMemAddress = (BYTE*)dirtyNtdll + pSectionHeader->VirtualAddress;
            BYTE* pDiskAddress = fileBuffer.data() + pSectionHeader->PointerToRawData;
            SIZE_T sizeOfSection = pSectionHeader->Misc.VirtualSize;

            // Overwrite hooked .text section with clean bytes
            DWORD oldProtect = 0;
            if (VirtualProtect(pMemAddress, sizeOfSection, PAGE_EXECUTE_READWRITE, &oldProtect)) {

                memcpy(pMemAddress, pDiskAddress, sizeOfSection);

                // Restore memory permissions
                VirtualProtect(pMemAddress, sizeOfSection, oldProtect, &oldProtect);
                std::cout << "Success\n";
            }
            break;
        }
        pSectionHeader++;
    }

	return 0;
}