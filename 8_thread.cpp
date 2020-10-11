#include <iostream>
#include <thread>
using std::thread;

// detach를 사용 시 thread 자원 오류 발생 X
void func1() {
	for (int i = 0; i < 100; i++) {
		std::cout << "쓰레드 1 작동중! \n";
	}
	std::cout << "쓰레드 1 종료\n";
}

void func2() {
	for (int i = 0; i < 100; i++) {
		std::cout << "쓰레드 2 작동중! \n";
	}
	std::cout << "쓰레드 2 종료\n";
}

void func3() {
	for (int i = 0; i < 100; i++) {
		std::cout << "쓰레드 3 작동중! \n";
	}
	std::cout << "쓰레드 3 종료\n";
}

int main() {
	thread t1(func1);
	thread t2(func2);
	thread t3(func3);

	//t1.join();
	//t2.join();
	//t3.join();
	//std::cout << "쓰레드 전부 종료 확인\n";

	t1.detach();
	t2.detach();
	t3.detach();

	std::cout << "메인 프로세스 종료\n";
}
