#define _WIN32_WINNT 0x501

#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <conio.h>
using namespace std;

HANDLE GetProcessHandle(const char *process_name, DWORD dwAccess);

int main()
{
	PROCESS_INFORMATION pi;
    STARTUPINFO si;
    HANDLE  hThreadArray;
    ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );
	char temp[512];
	
	string a = "                        _     _          _                  \n"; cout << a;
	string b = " ___ _   _ ___ _ __ ___| |_  | |__   ___| |_ __   ___ _ __  \n"; cout << b;
	string c = "/ __| | | / __| '__/ _ \\ __| | '_ \\ / _ \\ | '_ \\ / _ \\ '__| \n"; cout << c;
	string d = "\\__ \\ |_| \\__ \\ | |  __/ |_  | | | |  __/ | |_) |  __/ |    \n"; cout << d;
	string e = "|___/\\__, |___/_|  \\___|\\__| |_| |_|\\___|_| .__/ \\___|_|    \n"; cout << e;
	string f = "     |___/                                |_|               \n"; cout << f;
	cout<<"\n";
	
	cout<<"==========================MENU=============================\n";
	
	cout<<"Wprowad\253 cyfr\251 z menu\n\n";
	
	char process_name[13]={"explorer.exe"};

    HANDLE hProcess=GetProcessHandle(process_name,PROCESS_QUERY_INFORMATION);
    DWORD pid=GetProcessId(hProcess);
	
	cout<<"1. Odpal\n2. Wyj\230cie\n\n";
	
	int menu_int;
	
	cout<<"Podaj cyfr\251: ";
	
	menu_int=getch();
	
	cout<<endl;
	
	switch (menu_int)
	{
		case '1':
    
    sprintf(temp, "sysret -pid %d", pid);
	CreateProcess(NULL, temp, NULL, NULL, FALSE, 0 , NULL, NULL, &si, &pi);

    CloseHandle(hProcess);
	
	return 0;
	
	case '2': return 0;
		default: cout<<"Podaj cyfr\251 z menu!\n"; system("pause"); break;
	}
	return 0;
}

HANDLE GetProcessHandle(const char *process_name, DWORD dwAccess)
{
HANDLE hProcessSnap;
HANDLE hProcess;
PROCESSENTRY32 pe32;


hProcessSnap=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

if(hProcessSnap==INVALID_HANDLE_VALUE)
  {
    cerr <<"Failed to create process snapshot!";
    return INVALID_HANDLE_VALUE;
  }

pe32.dwSize=sizeof(PROCESSENTRY32);

if(!Process32First(hProcessSnap,&pe32))
  {
      cerr <<"Process32First() failed\n";
      return INVALID_HANDLE_VALUE;
  }

do
  {
    if(strcmp(pe32.szExeFile,process_name)==0)
        return OpenProcess(dwAccess,0,pe32.th32ProcessID);

  }while(Process32Next(hProcessSnap,&pe32));

}
