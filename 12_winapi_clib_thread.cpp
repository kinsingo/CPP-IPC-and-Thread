#include <Windows.h>
#include <process.h>
#include <stdio.h>

HANDLE semaphore;
int count = 0;

unsigned int __stdcall mythread(void* arg) 
{
	int n_my_num = (int)arg;
	for ( int i = 0; i < 50; i++) {
		WaitForSingleObject(semaphore, INFINITE);
		count += 1;
		printf("mynum %d\n", n_my_num);
		ReleaseSemaphore(semaphore, 1, 0);
	}
	return 0;
}

DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{
	DWORD n_my_num = *(DWORD*)lpParam;
	for (int i = 0; i < 50; i++) {
		WaitForSingleObject(semaphore, INFINITE);
		count += 1;
		printf("mynum %d\n", n_my_num);
		ReleaseSemaphore(semaphore, 1, 0);
	}

	return 0;
}

int main(int argc, char* argv[])
{
	HANDLE myhandleA, myhandleB;

	// 두번째 초기값
	// 세번째 최대값
	semaphore = CreateSemaphore(NULL, 1, 1, TEXT("MYSEMPHORE"));
	//semaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, TEXT("MYSEMPHORE"));
	
	myhandleA = (HANDLE)_beginthreadex(0, 0, &mythread, (void*)0, 0, 0);
	myhandleB = (HANDLE)_beginthreadex(0, 0, &mythread, (void*)1, 0, 0);

	WaitForSingleObject(myhandleA, INFINITE);
	WaitForSingleObject(myhandleB, INFINITE);

	CloseHandle(myhandleA);
	CloseHandle(myhandleB);
	
	printf("count = %d\n", count);


	// WINAPI
	DWORD dwThreadId1 = 1;
	DWORD dwThrdParam1 = 1;
	HANDLE hThread1 = CreateThread(NULL, 0, MyThreadFunction, &dwThrdParam1, 0, &dwThreadId1);
	DWORD dwThreadId2 = 2;
	DWORD dwThrdParam2 = 2;
	HANDLE hThread2 = CreateThread(NULL, 0, MyThreadFunction, &dwThrdParam2, 0, &dwThreadId2);
	
	if (hThread1 == NULL)
		printf("CreateThread() failed, error : %d\n", GetLastError());
	else
		printf("CreateThread() is OK!\n");
	if (hThread2 == NULL)
		printf("CreateThread() failed, error : %d\n", GetLastError());
	else
		printf("CreateThread() is OK!\n");

	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);

	if (CloseHandle(hThread1) != 0)
		printf("Handle to thread closed successfully.\n");
	if (CloseHandle(hThread2) != 0)
		printf("Handle to thread closed successfully.\n");

	getchar();

	CloseHandle(semaphore);

	return 0;
}