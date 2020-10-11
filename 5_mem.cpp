#include <iostream> // cout�� ���� ����
#include <stdlib.h>
using namespace std;
void main()
{
	// �޸� �Ҵ�
	int a = 1;
	int* p = (int*)malloc(sizeof(int));
	cout << *p << endl;
	*p = 2;

	cout << a << endl;
	cout << *p << endl;

	// �޸� ����
	free(p);

	// 2 �޸� �Ҵ� �� �ʱ�ȭ
	int* p2 = (int*)calloc(1, sizeof(int));
	cout << *p2 << endl;
	free(p2);

	// 3 malloc �� realloc
	int* p3 = (int*)malloc(sizeof(int));
	*p3 = 3;
	int* p4 = (int*)realloc(p3, 1024 * sizeof(int));
	cout << p3 << endl;
	cout << p4 << endl;

	// �޸� ���� �߻��� free(p3), p3�� ������ �Ҿ���� �޸�
	//free(p3);		// Error?
	free(p4);		// OK

	// �޸� ó��
	char str[32] = "Do you like C Programming?";
	char *ptr, *p5;
	puts(str);
	ptr = (char *)malloc(32);
	memset(ptr, 0x00, 32);  // �޸� �ʱ�ȭ
	memcpy(ptr, str, strlen(str)); //�޸� ī��
	puts(ptr); // ȭ�鿡 ���� ǥ��, cout << �� ����
	
	memset(ptr + 12, 'l', 1); // 12��° ��ġ���ڸ� l�� ����
	puts(ptr);

	p5 = (char *)memchr(ptr, 'l', 18); // �ִ� 18����Ʈ ���̿� 'l'���� ��ġ ã��
	puts(p5);
	memmove(str + 12, str + 7, 5); // 7° ��ġ�� 12��° ��ġ ���� ����Ʈ 5�� ����
	puts(str);
}
