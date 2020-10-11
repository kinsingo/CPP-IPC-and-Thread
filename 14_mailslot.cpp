#include<stdio.h>
#include<windows.h>
#include<iostream>

using namespace std;
// �޴���, ����, MAILSLOT Q ����
int recv() {
	HANDLE hMailSlot;
	char messageBox[BUFSIZ];
	DWORD bytesRead;

	hMailSlot = CreateMailslot(	TEXT("\\\\.\\mailslot\\Mail"), 0,
								MAILSLOT_WAIT_FOREVER, NULL);
	
	// ù��° 
	//   �����ϴ� ���Ͻ����� �̸��� �����ϴµ� ���˴ϴ�.
	//   \\computername\mailslot\[path]name
	// �ι�° ���Ͻ��� ������, 0�� ��� �ִ�
	// ����° ���ŷ �ð�, read ���ð�

	if (hMailSlot == INVALID_HANDLE_VALUE) {
		cout << "�������� MailSlot ! \n" << endl;
		return 1;
	}

	cout << "==========MAILSLOT IPC START==========\n" << endl;

	while (1) {
		memset(messageBox, 0x00, sizeof(messageBox));
		if (!ReadFile(hMailSlot, messageBox, BUFSIZ, &bytesRead, NULL)) {
			cout << "�б� ����\n" << endl;
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

// ��������
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
		cout << "�������� MailSlot ! \n" << endl;
		return 1;
	}

	while (1) {
		memset(message, 0x00, sizeof(message));
		cout << "Send Msg)";
		cin >> message;

		if (!WriteFile(hMailSlot, message,
			strlen(message), &bytesWritten, NULL)) {
			cout << "���ۿ��� MailSlot ! \n" << endl;
			CloseHandle(hMailSlot);
			return 1;
		}

		cout << endl << "����]" << message << endl;
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