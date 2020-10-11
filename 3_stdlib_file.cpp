#pragma warning(disable:4996) // 4996 에러를 안보이도록 함

#include <stdio.h>
#include <string.h> // strlen 함수를 사용하기 위함

void basic_file_save() { // 파일 저장하는 소스코드
	FILE* wfp;
	int hap = 0;
	int in, i;

	wfp = fopen("data7.txt", "r+");
	//FILE* fopen(const char* fileName, const char* fileMode)
	//fileMode:
	// "r", "w", "a" = 읽기, 쓰기, 추가
	// "r+" = 읽기쓰기 둘다 가능하게
	// "w+" = 읽기쓰기 둘다 가능하게, 파일이 존재하지 않으면 새로 생성
	// "a+" = 끝에 읽기/쓰기 둘다 가능하게 단 파일이 존재하지 않으면 새로 생성

	// b를 붙이면 binary 방식으로 읽고 쓰기
	// t는 생략 가능

	for (i = 0; i < 5; i++)
	{
		printf(" 숫자 %d : ", i + 1);
		scanf("%d", &in);
		hap = hap + in;
	}

	fprintf(wfp, "합계 = = > : %d\n", hap);

	fclose(wfp);
}


void basic_file_reverse() { // 파일 저장 및 앞뒤 전환
	FILE* rfp, * wfp;
	char str1[200], str2[200];
	int size, i;

	rfp = fopen("in.txt", "r");
	if (rfp == NULL) {
		printf("파일 없음 \n");
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
