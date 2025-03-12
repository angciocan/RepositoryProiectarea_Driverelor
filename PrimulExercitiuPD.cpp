#include <windows.h>
#include <windows.h>
#include <iostream>
#include <tchar.h>

using namespace std;

void afisareVariabileImagePath()
{
    HKEY hKey = 0;
    TCHAR pathOfsubKey[100] = TEXT("SYSTEM\\CurrentControlSet\\Services");

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, pathOfsubKey, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
    {
        cerr << "Eroare la deschidere!" << endl;
    }

    TCHAR serviceName[256]; 
    DWORD serviceIndex = 0;
    DWORD nameSize = 0;

    while (true)
    {
        nameSize = sizeof(serviceName) / sizeof(TCHAR);

        LONG enumeratedKeys = RegEnumKeyEx(hKey, serviceIndex, serviceName, &nameSize, NULL, NULL, NULL, NULL);

        if (enumeratedKeys != ERROR_SUCCESS)
            break;
        
        TCHAR servicePath[1024] = TEXT("");
        wcscpy_s(servicePath, pathOfsubKey);
        wcscat_s(servicePath, TEXT("\\"));
        wcscat_s(servicePath, serviceName);

        HKEY hServiceKey = NULL;
        if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, servicePath, 0, KEY_READ, &hServiceKey) == ERROR_SUCCESS)
        {
            TCHAR imagePath[512]; 
            DWORD pathSize = sizeof(imagePath);
            DWORD type;

            if (RegQueryValueEx(hServiceKey, L"ImagePath", NULL, &type, (LPBYTE)imagePath, &pathSize) == ERROR_SUCCESS)
            {
                wcout << "Serviciul: " << serviceName << "\n";
                wcout << "ImagePath: " << imagePath << "\n\n";
            }

            RegCloseKey(hServiceKey);
        }

        serviceIndex++;
    }

    RegCloseKey(hKey);
}

int main()
{
    afisareVariabileImagePath();
    return 0;
}