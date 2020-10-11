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

	// ���
	// ios::in = �б�
	// ios::out = ����
	// ios::ate = �����鼭 ���� ��
	// ios::app = append
	// ios::trunc = ���� ���� �� ����
	// ios::binary = ���� ���
	// ios::nocreate = ������ ������ ���� �߻�
	// ios::noreplace = ������ �ִ� ��� ������ �߻�
	// |(or) �� �̿��Ͽ� ���� ����

	// ofstream �⺻ ��� : ios::out | ios::trunc
	// ifstream �⺻ ��� : ios:in
	// fstream ios::in | ios::out

	ofs.open("example.txt", ios::out | ios::trunc); // ���� ���� ����

	str = "testfile\n";
	ofs << str;
	ofs << "abc";
	ofs.write(str.c_str(), str.length());

	cout << "���� ���������� ��ġ�� " << ofs.tellp() << "�Դϴ�." << endl;
	
	ofs.seekp(-5, ios::cur); // ios::end, ios::beg
	
	cout << "���� ���������� ��ġ�� " << ofs.tellp() << "�Դϴ�." << endl;
	str = "[add message]\n";
	ofs << str;

	ofs.close();

	cout << endl << endl << endl;


	// ���� �б�	
	ifs.open("example.txt", ios::in);
	if (!ifs.is_open()) {
		cout << "������ �� ���� �����ϴ�!" << endl;
		exit(1);
	}
	else {
		cout << "������ ���������� �������ϴ�!" << endl;

		while (!ifs.eof()) {
			getline(ifs, str);
			cout << str << endl;
		}

		cout << "(ifs eof/good ��:" << ifs.eof() << ", " << ifs.good() << ")" << endl;
		ifs.seekg(-5, ios::cur);
		ifs >> str;
		cout << str << endl;
		cout << "�̵��� �Ͽ����� ���� �������� �� �� (ifs eof/good ��:" << ifs.eof() << ", " << ifs.good() << ")" << endl;
		ifs.clear(); // ���°� ����Ǿ� clear�۾��� �����ؾ���
		cout << "���°� (ifs eof/good ��:" << ifs.eof() << ", " << ifs.good() << ")" << endl;

		// ���������� ������
		ifs.seekg(-5, ios::cur);
		ifs >> str;
		cout << str << endl;

		ifs.close();
	}

	cout << endl << endl << endl;

	// ���� �а� ����	
	fs.open("example_read_write.txt", ios::in | ios::out | ios::trunc);
	if (!fs.is_open()) {
		cout << "������ �� ���� �����ϴ�!" << endl;
		exit(1);
	}
	else {
		cout << "������ ���������� �������ϴ�!" << endl;

		str = "testfile\n";
		fs << str;
		fs << "abc";
		 
		cout << "���� ��ġ�� :" << fs.tellg() << "," << fs.tellp() << endl;

		fs.seekg(ios::beg);

		while (!fs.eof()) {
			getline(fs, str);
			cout << str << endl;
		}

		str.clear();
		str.resize(10);

		fs.clear();
		fs.seekp(ios::beg);

		fs.read(&str[0], 10);	       // ���� ���� 10size��ŭ �о�´�.		

		cout << str << endl;

		fs.close();
	}
}
