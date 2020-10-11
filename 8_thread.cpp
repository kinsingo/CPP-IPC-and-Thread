#include <iostream>
#include <thread>
using std::thread;

// detach�� ��� �� thread �ڿ� ���� �߻� X
void func1() {
	for (int i = 0; i < 100; i++) {
		std::cout << "������ 1 �۵���! \n";
	}
	std::cout << "������ 1 ����\n";
}

void func2() {
	for (int i = 0; i < 100; i++) {
		std::cout << "������ 2 �۵���! \n";
	}
	std::cout << "������ 2 ����\n";
}

void func3() {
	for (int i = 0; i < 100; i++) {
		std::cout << "������ 3 �۵���! \n";
	}
	std::cout << "������ 3 ����\n";
}

int main() {
	thread t1(func1);
	thread t2(func2);
	thread t3(func3);

	//t1.join();
	//t2.join();
	//t3.join();
	//std::cout << "������ ���� ���� Ȯ��\n";

	t1.detach();
	t2.detach();
	t3.detach();

	std::cout << "���� ���μ��� ����\n";
}
