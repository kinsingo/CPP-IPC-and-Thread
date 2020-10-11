#include <cstdio>
#include <iostream>
#include <thread>
#include <vector>
#include <string>

using std::thread;
using std::vector;

void worker(vector<int>::iterator start, vector<int>::iterator end, int* result) {
	int sum = 0;
	for (auto itr = start; itr < end; ++itr) {
		sum += *itr;
	}

	*result = sum;

	// �������� id �� ������
	thread::id this_id = std::this_thread::get_id();
	printf("������ %x ���� %d ���� %d ���� ����� ��� : %d \n", this_id, *start, *(end - 1), sum);

}

void argTH(int* shared_var, int value1, std::string value2) {
	for (int i = 0; i < 10000; i++) {
		*shared_var = *shared_var + 1;
	}
	std::cout << *shared_var << "," << value1 << "," << value2 << ", my th id:" << std::this_thread::get_id() << std::endl;
}

int main() {
	vector<int> data(10000);
	for (int i = 0; i < 10000; i++) {
		data[i] = i;
	}

	// �� �����忡�� ���� �κ� �յ��� �����ϴ� ����
	vector<int> partial_sums(4);

	vector<thread> workers;
	for (int i = 0; i < 4; i++) {
		workers.push_back(thread(worker, data.begin() + i * 2500, data.begin() + (i + 1) * 2500, &partial_sums[i]));
	}

	for (int i = 0; i < 4; i++) {
		workers[i].join();
	}
	int total = 0;
	for (int i = 0; i < 4; i++) {
		total += partial_sums[i];
	}
	std::cout << "��ü �� : " << total << std::endl << std::endl << std::endl;



	int myShared = 999;
	thread* argTH1 = new thread(argTH, &myShared, 100, "test string");
	argTH1->join();
	std::cout << "������:" << myShared << std::endl;
	std::cout << "����" << std::endl;
}


