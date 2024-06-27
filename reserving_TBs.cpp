#include <windows.h>
#include <iostream>

// Reserving Terabytes of virtual address space and committing a tiny piece.
int main() {
    
    SIZE_T reserveSize = 127ULL << 40; // 1 terabyte = 2^40 bytes

    // Reserve the memory
    LPVOID lpvBase = VirtualAlloc(
        NULL,                 // Next page to commit
        reserveSize,          // Page size, in bytes
        MEM_RESERVE,          // Allocate reserved pages
        PAGE_NOACCESS);       // Protection = no access

    if (lpvBase == NULL) {
        std::cerr << "VirtualAlloc (reserve) failed. Error: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Memory reserved at address: " << lpvBase << std::endl;

    // Define the size to commit: 4 KB (one page)
    SIZE_T commitSize = 4 * 1024; // 4 kilobytes

    // Commit the memory
    LPVOID lpvCommit = VirtualAlloc(
        lpvBase,              // Address of reserved memory
        commitSize,           // Size of the committed memory
        MEM_COMMIT,           // Allocate committed pages
        PAGE_READWRITE);      // Read/write access

    if (lpvCommit == NULL) {
        std::cerr << "VirtualAlloc (commit) failed. Error: " << GetLastError() << std::endl;
        VirtualFree(lpvBase, 0, MEM_RELEASE); // Release reserved memory
        return 1;
    }

    std::cout << "Memory committed at address: " << lpvCommit << std::endl;

    // You can release the committed and reserved memory when it's no longer needed
    VirtualFree(lpvBase, 0, MEM_RELEASE);

    return 0;
}
