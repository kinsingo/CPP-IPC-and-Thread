#include <cstdio>
#include <fstream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>

using namespace std;

// std::this_thread::sleep_for(std::chrono::milliseconds(1));

void TH1(mutex& arg_m, ofstream& arg_ofs) {
	int sum = 0;
	int startnum = 1;
	arg_m.lock();
	for (int i = startnum; i < startnum + 10; i++) {
		sum += i;
		arg_ofs << "TH1:" << sum << endl;		
	}
	arg_m.unlock();
}

void TH2(mutex& arg_m, ofstream& arg_ofs) {
	int sum = 0;
	int startnum = 11;
	arg_m.lock();
	for (int i = startnum; i < startnum + 10; i++) {
		sum += i;
		arg_ofs << "TH2:" << sum << endl;		
	}
	arg_m.unlock();
}

void TH3(mutex& arg_m, ofstream& arg_ofs) {
	int sum = 0;
	int startnum = 21;
	arg_m.lock();
	for (int i = startnum; i < startnum + 10; i++) {
		sum += i;
		arg_ofs << "TH3:" << sum << endl;
	}
	arg_m.unlock();
}

int main() {
	ofstream ofs;
	mutex m;  // mutex 객체

	ofs.open("solution1.txt", ios::out | ios::trunc); // 파일 새로 쓰기

	thread* solTH[3];
	solTH[0] = new thread(TH1, std::ref(m), std::ref(ofs));
	solTH[1] = new thread(TH2, std::ref(m), std::ref(ofs));
	solTH[2] = new thread(TH3, std::ref(m), std::ref(ofs));

	for (int i = 0; i < 3; i++) {
		solTH[i]->join();
	}

	ofs.close();
}


