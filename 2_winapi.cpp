#include <stdio.h>
#include <Windows.h>


// ������Ʈ �Ӽ� -> ����� -> �۾����丮 -> $(SolutionDir)$(Configuration)\
// �۾����丮�� ��µ��丮 ������ �޶� �߻��� ����

int main()
{
	HANDLE hSrcFile, hDstFile;
	char buf[512];
	DWORD nread, nwrite;
	// �����ڵ� : hSrcFile = CreateFile(TEXT("test.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	// �������� : read/write �Ѵ� �����ϵ��� open
	hSrcFile = CreateFile(TEXT("test.txt"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	// GENERIC_READ �� GENERIC_WRITE�� ���ÿ� �����ϵ��� ȣ��

	hDstFile = CreateFile(TEXT("CopiedFile"), GENERIC_WRITE, 0, NULL, TRUNCATE_EXISTING, 0, NULL);

	if (hDstFile == INVALID_HANDLE_VALUE) { // ������ ������ ����
		hDstFile = CreateFile(TEXT("CopiedFile"), GENERIC_WRITE, 0, NULL, CREATE_NEW, 0, NULL);
	}
	/* 
	CreateFile �Լ� ���� ����
		LPCTSTR lpFileName, // ������ �̸��� ���� ������
		DWORD dwDesiredAccess, // ����(read-write) ���, 
								  GENERIC_READ, GENERIC_WRITE
		DWORD dwShareMode, // ���� ���
								FILE_SHARE_READ : �б⸸ ����, FILE_SHARE_WRITE : ���⸸ ����
								0: ���� ����
		LPSECURITY_ATTRIBUTES lpSecurityAttributes, // ���� �Ӽ��� ����������
		DWORD dwCreationDisposition, // ������ ������ ���� �������� ���� �� ��� �ؾ������� �����Ѵ�
		DWORD dwFlagsAndAttributes, // ���� �Ӽ��� ������ ����, �б����� ��
		HANDLE hTemplateFile // �����ϱ� ���� �Ӽ��� ���� ������ �ڵ�

		// dwCreationDisposition �ɼ� ����
		#define CREATE_NEW          1  // ���ο� ������ �����Ѵ�. ������ ������ ����
		#define CREATE_ALWAYS       2  // ���ο� ������ �����Ѵ�. ������ �����ϸ�, �Լ��� ������ �����, ���� �Ӽ� �ʱ�ȭ
		#define OPEN_EXISTING       3  // ������ ����, ������ ������ ����
		#define OPEN_ALWAYS         4  // ������ ������ CREATE_NEWó�� ����, ������ ����
		#define TRUNCATE_EXISTING   5  // ������ ����, �ʱ�ȭ��. ������ ������ ����
	*/
	
	if ((hSrcFile == INVALID_HANDLE_VALUE) || (hDstFile == INVALID_HANDLE_VALUE)) {
		printf("File Open Failed\n");
		return -1;
	}

	while (1)
	{
		ReadFile(hSrcFile, buf, sizeof(buf), &nread, NULL);
		if (nread <= 0)
			break;
		printf("%d byte read\n", nread);
		WriteFile(hDstFile, buf, nread, &nwrite, NULL);
		printf("%d byte write\n", nwrite);

		CloseHandle(hSrcFile);
		CloseHandle(hDstFile);
	}
}
