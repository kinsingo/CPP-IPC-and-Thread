#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#include <WinSock2.h>
#include <string>
#include <iostream>


class UDPSocket
{
public:
	WSAData wsdata;
	UDPSocket()
	{
		int ret = WSAStartup(MAKEWORD(2, 2), &wsdata);
		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (sock == INVALID_SOCKET) {
			std::cout << "INVALID_SOCKET";
		}
	}
	~UDPSocket()
	{
		closesocket(sock);
		WSACleanup();
	}

	void SendTo(const std::string& address, unsigned short port, const char* buffer, int len, int flags = 0)
	{
		sockaddr_in add;
		add.sin_family = AF_INET;
		add.sin_addr.s_addr = inet_addr(address.c_str());
		add.sin_port = htons(port);
		int ret = sendto(sock, buffer, len, flags, reinterpret_cast<SOCKADDR*>(&add), sizeof(add));
		if (ret < 0) {
			std::cout << "sendto failed" << std::endl;
		}
	}
	void SendTo(sockaddr_in& address, const char* buffer, int len, int flags = 0)
	{
		int ret = sendto(sock, buffer, len, flags, reinterpret_cast<SOCKADDR*>(&address), sizeof(address));
		if (ret < 0) {
			std::cout << "sendto failed" << std::endl;
		}
	}
	sockaddr_in RecvFrom(char* buffer, int len, int flags = 0)
	{
		sockaddr_in from;
		int size = sizeof(from);
		int ret = recvfrom(sock, buffer, len, flags, reinterpret_cast<SOCKADDR*>(&from), &size);
		if (ret < 0) {
			std::cout << "recvfrom failed" << std::endl;
		}

		// make the buffer zero terminated
		buffer[ret] = 0;
		return from;
	}
	void Bind(unsigned short port)
	{
		sockaddr_in add;
		add.sin_family = AF_INET;
		add.sin_addr.s_addr = htonl(INADDR_ANY);
		add.sin_port = htons(port);

		int ret = bind(sock, reinterpret_cast<SOCKADDR*>(&add), sizeof(add));
		if (ret < 0) {
			std::cout << "Bind failed" << std::endl;
		}
	}

private:
	SOCKET sock;
};


int main(int argc, char* argv[])
{
	printf("%s\n", argv[0]);
	if (argc > 1) {
		UDPSocket Socket;
		char buffer[BUFSIZ];

		Socket.Bind(55568);

		std::string strmessage;
		while (1) {
			sockaddr_in srcaddr = Socket.RecvFrom(buffer, sizeof(buffer));
			std::cout << buffer << std::endl;
			if (strcmp(buffer, "EXIT") == 0) {
				break;
			}
			std::cout << "Send Msg)";
			std::cin >> strmessage;
			Socket.SendTo(srcaddr, strmessage.c_str(), strmessage.size());

			if (strcmp(strmessage.c_str(), "EXIT") == 0) {
				break;
			}
		}
	}
	else {
		UDPSocket Socket;

		std::string strmessage;
		char buffer[BUFSIZ];

		while (1) {
			std::cout << "Send Msg)";
			std::cin >> strmessage;
			Socket.SendTo("192.168.0.5", 55568, strmessage.c_str(), strmessage.size());

			if (strcmp(strmessage.c_str(), "EXIT") == 0) {
				break;
			}

			sockaddr_in srcaddr = Socket.RecvFrom(buffer, sizeof(buffer));
			std::cout << buffer << std::endl;
			if (strcmp(buffer, "EXIT") == 0) {
				break;
			}
		}
	}
}