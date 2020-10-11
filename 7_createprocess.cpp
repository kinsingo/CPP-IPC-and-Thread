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
    _In_opt_ LPCSTR lpApplicationName,  // �������ϸ�
    _Inout_opt_ LPSTR lpCommandLine, // ����� �μ�
    _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,  // Ŀ�� ������Ʈ(���μ���) ���ȼ���
    _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,  // Ŀ�� ������Ʈ(������) ���ȼ���
    _In_ BOOL bInheritHandles, ��ӿ���
    _In_ DWORD dwCreationFlags, ���μ����� �÷��� ����
    _In_opt_ LPVOID lpEnvironment, ȯ�溯�� �޸� ������
    _In_opt_ LPCSTR lpCurrentDirectory, ���� ����̺�� ���丮 
    _In_ LPSTARTUPINFOA lpStartupInfo, startupinfo ����ü ������ ����
    _Out_ LPPROCESS_INFORMATION lpProcessInformation, ���μ��� ���� �޾ƿ� ����ü �ּҰ�
	*/

	WaitForSingleObject(pi.hProcess, INFINITE); //parent will wait for the child to complete
	printf("Child Complete");
	//close handles
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
