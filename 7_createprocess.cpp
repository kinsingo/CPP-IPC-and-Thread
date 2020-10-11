#include <stdio.h>
#include <windows.h>

int main() {
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si)); //allocate memory
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
	si.dwX = 100;
	si.dwY = 0;
	si.dwXSize = 300;
	si.dwYSize = 300;
	ZeroMemory(&pi, sizeof(pi));

	//create child process
	if (!CreateProcessA((LPSTR)"C:\\WINDOWS\\system32\\notepad.exe", NULL,
		NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		fprintf(stderr, "Create Process Failed");
		return -1;
	}
	if (!CreateProcessA(NULL,(LPSTR)"C:\\WINDOWS\\system32\\mspaint",
		NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		fprintf(stderr, "Create Process Failed");
		return -1;
	}

	/*	
    _In_opt_ LPCSTR lpApplicationName,  // 실행파일명
    _Inout_opt_ LPSTR lpCommandLine, // 명령행 인수
    _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,  // 커널 오브젝트(프로세스) 보안설정
    _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,  // 커널 오브젝트(쓰레드) 보안설정
    _In_ BOOL bInheritHandles, 상속여부
    _In_ DWORD dwCreationFlags, 프로세스의 플래그 설정
    _In_opt_ LPVOID lpEnvironment, 환경변수 메모리 포인터
    _In_opt_ LPCSTR lpCurrentDirectory, 현재 드라이브와 디렉토리 
    _In_ LPSTARTUPINFOA lpStartupInfo, startupinfo 구조체 포인터 전달
    _Out_ LPPROCESS_INFORMATION lpProcessInformation, 프로세스 정보 받아올 구조체 주소값
	*/

	WaitForSingleObject(pi.hProcess, INFINITE); //parent will wait for the child to complete
	printf("Child Complete");
	//close handles
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
