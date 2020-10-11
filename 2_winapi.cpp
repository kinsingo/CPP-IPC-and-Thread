#include <stdio.h>
#include <Windows.h>


// 프로젝트 속성 -> 디버그 -> 작업디렉토리 -> $(SolutionDir)$(Configuration)\
// 작업디렉토리와 출력디렉토리 설정이 달라서 발생한 문제

int main()
{
	HANDLE hSrcFile, hDstFile;
	char buf[512];
	DWORD nread, nwrite;
	// 교재코드 : hSrcFile = CreateFile(TEXT("test.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	// 개선예시 : read/write 둘다 가능하도록 open
	hSrcFile = CreateFile(TEXT("test.txt"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	// GENERIC_READ 에 GENERIC_WRITE를 동시에 가능하도록 호출

	hDstFile = CreateFile(TEXT("CopiedFile"), GENERIC_WRITE, 0, NULL, TRUNCATE_EXISTING, 0, NULL);

	if (hDstFile == INVALID_HANDLE_VALUE) { // 파일이 없으면 생성
		hDstFile = CreateFile(TEXT("CopiedFile"), GENERIC_WRITE, 0, NULL, CREATE_NEW, 0, NULL);
	}
	/* 
	CreateFile 함수 인자 설명
		LPCTSTR lpFileName, // 파일의 이름에 대한 포인터
		DWORD dwDesiredAccess, // 접근(read-write) 모드, 
								  GENERIC_READ, GENERIC_WRITE
		DWORD dwShareMode, // 공유 모드
								FILE_SHARE_READ : 읽기만 공유, FILE_SHARE_WRITE : 쓰기만 공유
								0: 공유 안함
		LPSECURITY_ATTRIBUTES lpSecurityAttributes, // 보안 속성에 대한포인터
		DWORD dwCreationDisposition, // 파일이 존재할 때와 존재하지 않을 때 어떻게 해야할지를 지정한다
		DWORD dwFlagsAndAttributes, // 파일 속성을 지정함 숨김, 읽기전용 등
		HANDLE hTemplateFile // 복사하기 위한 속성을 가진 파일의 핸들

		// dwCreationDisposition 옵션 관련
		#define CREATE_NEW          1  // 새로운 파일을 생성한다. 파일이 있으면 실패
		#define CREATE_ALWAYS       2  // 새로운 파일을 생성한다. 파일이 존재하면, 함수는 파일을 덮어쓰고, 파일 속성 초기화
		#define OPEN_EXISTING       3  // 파일을 열고, 파일이 없으면 실패
		#define OPEN_ALWAYS         4  // 파일이 없으면 CREATE_NEW처럼 동작, 있으면 열기
		#define TRUNCATE_EXISTING   5  // 파일을 열고, 초기화함. 파일이 없으면 실패
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
