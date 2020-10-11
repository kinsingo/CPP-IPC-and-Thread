#include <cstdio>
#include <fstream>
#include <thread>
#include <iostream>

using namespace std;

// std::this_thread::sleep_for(std::chrono::milliseconds(1));

void TH1(int* shared, ofstream& arg_ofs) {
	int startnum = 1;
	int num = 0;
	for (int i = startnum; i < startnum + 1000; i++) {
		*shared = *shared + 1;
		num = *shared;
		printf("TH1:%d\n", num);
		arg_ofs << "TH1:" << num << endl;
	}
}

void TH2(int* shared, ofstream& arg_ofs) {
	int startnum = 1;
	int num = 0;
	for (int i = startnum; i < startnum + 1000; i++) {
		*shared = *shared + 1;
		num = *shared;
		printf("TH2:%d\n", num);
		arg_ofs << "TH2:" << num << endl;
	}
}

int main() {
	ofstream ofs;

	ofs.open("solution2.txt", ios::out | ios::trunc); // 파일 새로 쓰기

	int myShared = 0;
	thread* solTH[2];
	solTH[0] = new thread(TH1, &myShared, std::ref(ofs));
	solTH[1] = new thread(TH2, &myShared, std::ref(ofs));

	for (int i = 0; i < 2; i++) {
		solTH[i]->join();
	}
	ofs.close();
}


