#pragma warning(disable:4996) // 4996 ������ �Ⱥ��̵��� ��

#include <stdio.h>
#include <string.h> // strlen �Լ��� ����ϱ� ����

void basic_file_save() { // ���� �����ϴ� �ҽ��ڵ�
	FILE* wfp;
	int hap = 0;
	int in, i;

	wfp = fopen("data7.txt", "r+");
	//FILE* fopen(const char* fileName, const char* fileMode)
	//fileMode:
	// "r", "w", "a" = �б�, ����, �߰�
	// "r+" = �б⾲�� �Ѵ� �����ϰ�
	// "w+" = �б⾲�� �Ѵ� �����ϰ�, ������ �������� ������ ���� ����
	// "a+" = ���� �б�/���� �Ѵ� �����ϰ� �� ������ �������� ������ ���� ����

	// b�� ���̸� binary ������� �а� ����
	// t�� ���� ����

	for (i = 0; i < 5; i++)
	{
		printf(" ���� %d : ", i + 1);
		scanf("%d", &in);
		hap = hap + in;
	}

	fprintf(wfp, "�հ� = = > : %d\n", hap);

	fclose(wfp);
}


void basic_file_reverse() { // ���� ���� �� �յ� ��ȯ
	FILE* rfp, * wfp;
	char str1[200], str2[200];
	int size, i;

	rfp = fopen("in.txt", "r");
	if (rfp == NULL) {
		printf("���� ���� \n");
		return;
	}
	wfp = fopen("out.txt", "w");

	while (1)
	{
		fgets(str1, 200, rfp);

		if (feof(rfp))
			break;

		size = strlen(str1);
		for (i = size - 1; i >= 0; i--)
			str2[size - 1 - i] = str1[i - 1];

		str2[size - 1] = '\0';
		fputs(str2, wfp);
		fputs("\n", wfp);
	}

	fclose(rfp);
	fclose(wfp);
}


void main()
{
	basic_file_save();

	basic_file_reverse();
}
