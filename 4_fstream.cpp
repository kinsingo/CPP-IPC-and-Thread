#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main()
{
	ifstream ifs;
	ofstream ofs;
	fstream fs;
	string str;

	// 모드
	// ios::in = 읽기
	// ios::out = 쓰기
	// ios::ate = 읽으면서 파일 끝
	// ios::app = append
	// ios::trunc = 파일 존재 시 삭제
	// ios::binary = 이진 모드
	// ios::nocreate = 파일이 없으면 에러 발생
	// ios::noreplace = 파일이 있는 경우 에러를 발생
	// |(or) 를 이용하여 결합 가능

	// ofstream 기본 모드 : ios::out | ios::trunc
	// ifstream 기본 모드 : ios:in
	// fstream ios::in | ios::out

	ofs.open("example.txt", ios::out | ios::trunc); // 파일 새로 쓰기

	str = "testfile\n";
	ofs << str;
	ofs << "abc";
	ofs.write(str.c_str(), str.length());

	cout << "현재 파일포인터 위치는 " << ofs.tellp() << "입니다." << endl;
	
	ofs.seekp(-5, ios::cur); // ios::end, ios::beg
	
	cout << "현재 파일포인터 위치는 " << ofs.tellp() << "입니다." << endl;
	str = "[add message]\n";
	ofs << str;

	ofs.close();

	cout << endl << endl << endl;


	// 파일 읽기	
	ifs.open("example.txt", ios::in);
	if (!ifs.is_open()) {
		cout << "파일을 열 수가 없습니다!" << endl;
		exit(1);
	}
	else {
		cout << "파일을 성공적으로 열었습니다!" << endl;

		while (!ifs.eof()) {
			getline(ifs, str);
			cout << str << endl;
		}

		cout << "(ifs eof/good 값:" << ifs.eof() << ", " << ifs.good() << ")" << endl;
		ifs.seekg(-5, ios::cur);
		ifs >> str;
		cout << str << endl;
		cout << "이동을 하였으나 값을 가져오지 못 함 (ifs eof/good 값:" << ifs.eof() << ", " << ifs.good() << ")" << endl;
		ifs.clear(); // 상태가 변경되어 clear작업을 수행해야함
		cout << "상태값 (ifs eof/good 값:" << ifs.eof() << ", " << ifs.good() << ")" << endl;

		// 정상적으로 가져옴
		ifs.seekg(-5, ios::cur);
		ifs >> str;
		cout << str << endl;

		ifs.close();
	}

	cout << endl << endl << endl;

	// 파일 읽고 쓰기	
	fs.open("example_read_write.txt", ios::in | ios::out | ios::trunc);
	if (!fs.is_open()) {
		cout << "파일을 열 수가 없습니다!" << endl;
		exit(1);
	}
	else {
		cout << "파일을 성공적으로 열었습니다!" << endl;

		str = "testfile\n";
		fs << str;
		fs << "abc";
		 
		cout << "파일 위치값 :" << fs.tellg() << "," << fs.tellp() << endl;

		fs.seekg(ios::beg);

		while (!fs.eof()) {
			getline(fs, str);
			cout << str << endl;
		}

		str.clear();
		str.resize(10);

		fs.clear();
		fs.seekp(ios::beg);

		fs.read(&str[0], 10);	       // 파일 에서 10size만큼 읽어온다.		

		cout << str << endl;

		fs.close();
	}
}
