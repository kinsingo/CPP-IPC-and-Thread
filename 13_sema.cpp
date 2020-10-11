#include <Windows.h>
#include <process.h>
#include <stdio.h>

HANDLE semaphore;
int count = 0;

int main() {

	// 두개 실행파일 작성
	// 한프로그램은 CreateSemaphore
	// 다른 한프로그램은 OpenSemaphore
	semaphore = CreateSemaphore(NULL, 2, 2, TEXT("MYSEMPHORE"));
	semaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, TEXT("MYSEMPHORE"));
	if (semaphore == NULL) {
		printf("세마포어 오류\n");
		return 0;
	}

	for (int i = 0; i < 10; i++) {
		printf("진입대기\n");
		WaitForSingleObject(semaphore, INFINITE);
		printf("진입\n");
		Sleep(5000);
		ReleaseSemaphore(semaphore, 1, 0);
		printf("반환\n");
	}

	CloseHandle(semaphore);
}
