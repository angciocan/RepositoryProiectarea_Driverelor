#include <windows.h>
#include <setupapi.h>
#include <iostream>
#include <devguid.h>

using namespace std;

#pragma comment(lib, "setupapi.lib")

int main() {

    HDEVINFO hDeviceInformation = SetupDiGetClassDevs(
        &GUID_DEVCLASS_USB, NULL, NULL, DIGCF_PRESENT);

    if (hDeviceInformation == INVALID_HANDLE_VALUE) {
        cerr << "Eroare: Nu s-a gasit lista dispozitivelor";
        return 1;
    }

    SP_DEVINFO_DATA devInfoData;
    memset(&devInfoData, 0, sizeof(SP_DEVINFO_DATA));
    devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    wcout << "Dispozitive USB care au fost gasite:\n";

    for (DWORD i = 0; SetupDiEnumDeviceInfo(hDeviceInformation, i, &devInfoData) ; i++) {
        CHAR deviceName[256];
        DWORD size = 0;
        
        BOOL foundDevice = FALSE;
        BOOL frendlyName = FALSE;

        frendlyName = SetupDiGetDeviceRegistryPropertyA(hDeviceInformation, &devInfoData, SPDRP_FRIENDLYNAME, NULL, (PBYTE)deviceName, sizeof(deviceName), &size);

        if (frendlyName)
        {
            wcout << L" - " << deviceName << std::endl;
            foundDevice = TRUE;
        }
        
        if (!foundDevice && SetupDiGetDeviceRegistryPropertyA(hDeviceInformation, &devInfoData, SPDRP_DEVICEDESC, NULL, (PBYTE)deviceName, sizeof(deviceName), &size))
        {
            wcout << L" - " << deviceName << std::endl;
            foundDevice = TRUE;
        }

        if (!foundDevice) 
        {
           wcout << L" - Dispozitiv necunoscut" << std::endl;
        }
    }
    
    SetupDiDestroyDeviceInfoList(hDeviceInformation);

    return 0;
}