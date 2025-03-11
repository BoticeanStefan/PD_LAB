#include <Windows.h>
#include <stdio.h>
#include <winreg.h>


int main() {
    HKEY hKey;
    LONG lRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Services", 0, KEY_READ, &hKey);
    if (lRes == ERROR_SUCCESS) {
        wchar_t szSubkey[256];
        DWORD dwIndex = 0;
        DWORD cbName = sizeof(szSubkey);
        while (RegEnumKeyEx(hKey, dwIndex, szSubkey, &cbName, NULL, NULL, NULL, NULL) != ERROR_NO_MORE_ITEMS) {
            HKEY hSubkey;
            if (RegOpenKeyEx(hKey, szSubkey, 0, KEY_READ, &hSubkey) == ERROR_SUCCESS) {
                wchar_t szImagePath[1024];
                DWORD cbData = sizeof(szImagePath);

                if (RegQueryValueEx(hSubkey, L"ImagePath", NULL, NULL, (LPBYTE)szImagePath, &cbData) == ERROR_SUCCESS) {
                    wprintf(L"Subkey: %s \n", szSubkey);
                    wprintf(L"ImagePath: %s\n", szImagePath);
                }
                RegCloseKey(hSubkey);
            }
            dwIndex++;
            cbName = sizeof(szSubkey);
        }
        RegCloseKey(hKey);
    }
    else {
        wprintf("Error opening registry key!\n");
        return 1;
    }
    return 0;
}


