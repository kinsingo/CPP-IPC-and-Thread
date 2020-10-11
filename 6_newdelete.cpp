#include <iostream> // cout 사용을 위해 추가
using namespace std;
class CTest
{
public:
	CTest() : m_value(0)
	{
		cout << "constructor!" << endl;
	}
	CTest(int m_value) : m_value(0)
	{
		cout << "param constructor!" << endl;
	}
	~CTest()
	{
		cout << "destructor!" << endl;
	}

	int m_value;
};

void main()
{
	int* p1 = (int*)malloc(sizeof(int));
	*p1 = 3;
	cout << *p1 << endl;
	free(p1);

	int* p2 = new int;
	*p2 = 3;
	cout << *p2 << endl;
	delete p2;

	// malloc new 와 동일함
	int* p3 = (int*)malloc(2 * sizeof(int));
	p3[0] = 0;
	p3[1] = 1;
	free(p3);

	int* p4 = new int[2];
	p4[0] = 0;
	p4[1] = 1;
	delete[] p4;

	cout << endl << endl << endl << endl;

	////////////
	// 클래스 관련
	cout << "<malloc>" << endl;
	CTest* pT1 = (CTest*)malloc(sizeof(CTest));
	cout << "<free>" << endl;
	free(pT1);

	cout << "<new>" << endl;
	CTest* pT2 = new CTest(90);
	cout << "<delete>" << endl;
	delete pT2;

	cout << endl << endl;

	cout << "<new[], delete []>" << endl;
	//CTest* pT3 = new CTest(50)[2]; // 동적으로는 불가
	CTest* pT3 = new CTest[2]; // 동적으로는 불가
	delete[] pT3;

	cout << "<new*>" << endl;	
	CTest* pT4 = new CTest;
	cout << "<delete void*>" << endl;
	delete (void*)pT4;
	
	cout << endl << endl;

	// 클래스 메모리 복사
	cout << "<malloc>" << endl;
	CTest* pT5 = (CTest*)malloc(sizeof(CTest));
	pT5->m_value = 999;
	cout << "<m_value:" << pT5->m_value << ">" << endl;

	CTest* pT6 = (CTest*)malloc(sizeof(CTest));
	memcpy(pT6, pT5, sizeof(pT5));
	cout << "<m_value:" << pT6->m_value << ">" << endl;
	
	CTest* pT7 = (CTest*)malloc(sizeof(CTest));
	cout << "기존 주소 - pT7:" << pT7 << " pT6:" << pT6 << endl;
	pT7 = pT6; // 주소 포인터가 변경됨
	cout << "변경 주소 - pT7:" << pT7 << " pT6:" << pT6 << endl;;

	cout << "<free>" << endl;
	free(pT5);
}
