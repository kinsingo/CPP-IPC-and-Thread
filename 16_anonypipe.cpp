#pragma warning(disable:4996)

#include<stdio.h>
#include<windows.h>
#include<iostream>
#include <tchar.h>

using namespace std;
// 받는쪽, 서버, PIPE 생성
int recv() {
	HANDLE readPipe, writePipe;
	char messageBox[BUFSIZ];
	DWORD bytesRead;

	TCHAR exename[256] = { 0 };

	CreatePipe(&readPipe, &writePipe, NULL, 0);
	SetHandleInformation(writePipe, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);

	wsprintf(exename, TEXT("project1.exe %d"), (int)writePipe);
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);
	CreateProcess(
			NULL, exename,
			NULL, NULL,
			TRUE,
			CREATE_NEW_CONSOLE,
			NULL, NULL,
			&si, &pi);

	while (1) {
		memset(messageBox, 0x00, sizeof(messageBox));
		if (!ReadFile(readPipe, messageBox, BUFSIZ, &bytesRead, NULL)) {
			cout << "읽기 실패\n" << endl;
			CloseHandle(readPipe);
			return 1;
		}
		cout << messageBox << "," << bytesRead << endl;
		if (strcmp(messageBox, "EXIT") == 0) {
			break;
		}
	}

	CloseHandle(readPipe);

	return 1;
}

// 보내는쪽
int send(HANDLE& pipe) {
	char message[BUFSIZ];
	DWORD bytesWritten;

	while (1) {
		memset(message, 0x00, sizeof(message));
		cout << "Send Msg)";
		cin >> message;

		if (!WriteFile(pipe, message,
			strlen(message), &bytesWritten, NULL)) {
			cout << "전송오류 anonypipe ! \n" << endl;
			CloseHandle(pipe);
			return 1;
		}

		cout << endl << "전송]" << message << endl;
		if (strcmp(message, "EXIT") == 0) {
			break;
		}
	}
	CloseHandle(pipe);
	return 0;
}

int main(int argc, char* argv[]) {

	printf("%s\n", argv[0]);
	if (argc == 1) {
		recv();
	}
	else {
		HANDLE readPipe = (HANDLE)(atoi(argv[1]));
		send(readPipe);
	}
	return 0;
}