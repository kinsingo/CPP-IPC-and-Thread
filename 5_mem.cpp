#include <iostream> // cout을 쓰기 위함
#include <stdlib.h>
using namespace std;
void main()
{
	// 메모리 할당
	int a = 1;
	int* p = (int*)malloc(sizeof(int));
	cout << *p << endl;
	*p = 2;

	cout << a << endl;
	cout << *p << endl;

	// 메모리 해제
	free(p);

	// 2 메모리 할당 후 초기화
	int* p2 = (int*)calloc(1, sizeof(int));
	cout << *p2 << endl;
	free(p2);

	// 3 malloc 후 realloc
	int* p3 = (int*)malloc(sizeof(int));
	*p3 = 3;
	int* p4 = (int*)realloc(p3, 1024 * sizeof(int));
	cout << p3 << endl;
	cout << p4 << endl;

	// 메모리 오류 발생함 free(p3), p3은 권한을 잃어버린 메모리
	//free(p3);		// Error?
	free(p4);		// OK

	// 메모리 처리
	char str[32] = "Do you like C Programming?";
	char *ptr, *p5;
	puts(str);
	ptr = (char *)malloc(32);
	memset(ptr, 0x00, 32);  // 메모리 초기화
	memcpy(ptr, str, strlen(str)); //메모리 카피
	puts(ptr); // 화면에 글자 표시, cout << 과 같음
	
	memset(ptr + 12, 'l', 1); // 12번째 위치글자를 l로 변경
	puts(ptr);

	p5 = (char *)memchr(ptr, 'l', 18); // 최대 18바이트 사이에 'l'글자 위치 찾기
	puts(p5);
	memmove(str + 12, str + 7, 5); // 7째 위치에 12번째 위치 이후 바이트 5개 복사
	puts(str);
}
