#include<stdio.h>
#include<windows.h>
#include<iostream>

using namespace std;
// 받는쪽, 서버, MAILSLOT Q 생성
int recv() {
	HANDLE hMailSlot;
	char messageBox[BUFSIZ];
	DWORD bytesRead;

	hMailSlot = CreateMailslot(	TEXT("\\\\.\\mailslot\\Mail"), 0,
								MAILSLOT_WAIT_FOREVER, NULL);
	
	// 첫번째 
	//   생성하는 메일슬롯의 이름을 결정하는데 사용됩니다.
	//   \\computername\mailslot\[path]name
	// 두번째 메일슬롯 사이즈, 0일 경우 최대
	// 세번째 블록킹 시간, read 대기시간

	if (hMailSlot == INVALID_HANDLE_VALUE) {
		cout << "생성오류 MailSlot ! \n" << endl;
		return 1;
	}

	cout << "==========MAILSLOT IPC START==========\n" << endl;

	while (1) {
		memset(messageBox, 0x00, sizeof(messageBox));
		if (!ReadFile(hMailSlot, messageBox, BUFSIZ, &bytesRead, NULL)) {
			cout << "읽기 실패\n" << endl;
			CloseHandle(hMailSlot);
			return 1;
		}
		cout << messageBox << "," << bytesRead << endl;
		if (strcmp(messageBox, "EXIT") == 0) {
			break;
		}
	}
	CloseHandle(hMailSlot);
}

// 보내는쪽
int send() {
	HANDLE hMailSlot;
	char message[BUFSIZ];
	DWORD bytesWritten;

	hMailSlot = CreateFile(
							TEXT("\\\\.\\mailslot\\Mail"), GENERIC_WRITE,
							NULL,
							NULL,
							OPEN_EXISTING,
							FILE_ATTRIBUTE_NORMAL,
							NULL
	);

	if (hMailSlot == INVALID_HANDLE_VALUE) {
		cout << "생성오류 MailSlot ! \n" << endl;
		return 1;
	}

	while (1) {
		memset(message, 0x00, sizeof(message));
		cout << "Send Msg)";
		cin >> message;

		if (!WriteFile(hMailSlot, message,
			strlen(message), &bytesWritten, NULL)) {
			cout << "전송오류 MailSlot ! \n" << endl;
			CloseHandle(hMailSlot);
			return 1;
		}

		cout << endl << "전송]" << message << endl;
		if (strcmp(message, "EXIT") == 0) {
			break;
		}
	}
	CloseHandle(hMailSlot);
	return 0;
}

int main(int argc, char* argv[]) {

	printf("%s\n", argv[0]);
	if (argc > 1) {
		recv();
	}
	else {
		send();
	}
	return 0;
}