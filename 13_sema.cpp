#include <Windows.h>
#include <process.h>
#include <stdio.h>

HANDLE semaphore;
int count = 0;

int main() {

	// �ΰ� �������� �ۼ�
	// �����α׷��� CreateSemaphore
	// �ٸ� �����α׷��� OpenSemaphore
	semaphore = CreateSemaphore(NULL, 2, 2, TEXT("MYSEMPHORE"));
	semaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, TEXT("MYSEMPHORE"));
	if (semaphore == NULL) {
		printf("�������� ����\n");
		return 0;
	}

	for (int i = 0; i < 10; i++) {
		printf("���Դ��\n");
		WaitForSingleObject(semaphore, INFINITE);
		printf("����\n");
		Sleep(5000);
		ReleaseSemaphore(semaphore, 1, 0);
		printf("��ȯ\n");
	}

	CloseHandle(semaphore);
}
