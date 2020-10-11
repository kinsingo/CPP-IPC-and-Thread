#include<stdio.h>
#include<windows.h>
#include<iostream>

using namespace std;
// �޴���, ����, PIPE Q ����
int recv() {
	HANDLE hNamePipe;
	char messageBox[BUFSIZ];
	DWORD bytesRead;

	hNamePipe = CreateNamedPipe(
					TEXT("\\\\.\\pipe\\Mail"),
					PIPE_ACCESS_DUPLEX,
					PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
					PIPE_UNLIMITED_INSTANCES,
					0,
					0,
					20000,       // ��� Timeout �ð�
					NULL
				);

	if (hNamePipe == INVALID_HANDLE_VALUE) {
		cout << "�������� ���� hNamePipe ! \n" << endl;
		return 1;
	}

	if (!(ConnectNamedPipe(hNamePipe, NULL)))
	{
		cout << "������� hNamePipe ! \n" << endl;
		CloseHandle(hNamePipe);
		return -1;
	}

	cout << "==========NamePipe IPC START==========\n" << endl;

	while (1) {
		memset(messageBox, 0x00, sizeof(messageBox));
		if (!ReadFile(hNamePipe, messageBox, BUFSIZ, &bytesRead, NULL)) {
			cout << "�б� ����\n" << endl;
			DisconnectNamedPipe(hNamePipe);
			CloseHandle(hNamePipe);
			return 1;
		}
		cout << messageBox << "," << bytesRead << endl;
		if (strcmp(messageBox, "EXIT") == 0) {
			break;
		}
	}
	DisconnectNamedPipe(hNamePipe);
	CloseHandle(hNamePipe);
}

// ��������
int send() {
	HANDLE hNamePipe;
	char message[BUFSIZ];
	DWORD bytesWritten;

	hNamePipe = CreateFile(
		TEXT("\\\\.\\pipe\\Mail"), GENERIC_READ | GENERIC_WRITE,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (hNamePipe == INVALID_HANDLE_VALUE) {
		cout << "�������� NamePipe ! \n" << endl;
		return 1;
	}

	DWORD pipeMode = PIPE_READMODE_MESSAGE | PIPE_WAIT;

	if (!(SetNamedPipeHandleState(hNamePipe, &pipeMode, NULL, NULL)))
	{
		cout << "������� hNamePipe ! \n" << endl;
		CloseHandle(hNamePipe);
		return -1;
	}

	while (1) {
		memset(message, 0x00, sizeof(message));
		cout << "Send Msg)";
		cin >> message;

		if (!WriteFile(hNamePipe, message,
			strlen(message), &bytesWritten, NULL)) {
			cout << "���ۿ��� named ! \n" << endl;
			CloseHandle(hNamePipe);
			return 1;
		}

		cout << endl << "����]" << message << endl;
		if (strcmp(message, "EXIT") == 0) {
			break;
		}
	}
	CloseHandle(hNamePipe);
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