#include <Windows.h>
#include <iostream>
#include <string>

int main() {
    HKEY hKey;
    LONG lRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Services", 0, KEY_READ, &hKey);
    int max = 100;
    int nrafis = 0;

    if (lRes == ERROR_SUCCESS) {
        wchar_t szSubkey[256];
        DWORD dwIndex = 0;
        DWORD cbName = sizeof(szSubkey);

        while (RegEnumKeyEx(hKey, dwIndex, szSubkey, &cbName, NULL, NULL, NULL, NULL) != ERROR_NO_MORE_ITEMS) {
            HKEY hSubkey;

            if (RegOpenKeyEx(hKey, szSubkey, 0, KEY_READ, &hSubkey) == ERROR_SUCCESS) {
                wchar_t szImagePath[1024];
                DWORD cbData = sizeof(szImagePath);
                DWORD cbType = sizeof(szImagePath);

                if (RegQueryValueEx(hSubkey, L"ImagePath", NULL, &cbType, (LPBYTE)szImagePath, &cbData) == ERROR_SUCCESS) {
                    if (nrafis == max) return 0;
                    if (cbType == 0x01 || cbType == 0x02) {
                        nrafis++;
                        std::wcout << L"Subkey: " << szSubkey << std::endl;
                        std::wcout << L"ImagePath: " << szImagePath << std::endl;
                        std::wcout << L"Type: " << cbType << std::endl;

                    }
                }
                RegCloseKey(hSubkey);
            }
            dwIndex++;
            cbName = sizeof(szSubkey);
        }
        RegCloseKey(hKey);
    }
    else {
        std::cerr << "Error opening registry key!" << std::endl;
        return 1;
    }
    return 0;
}