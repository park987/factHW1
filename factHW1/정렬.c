#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 3
#define MAX_LEN 256  //최대 버퍼 크기

typedef struct _Group {
	int len; //문자열 길이
	int count; //그룹에 속하는 단어 개수
	char** word; //그룹에 속하는 단어들의 배열
} Group;

int main() {
	Group group[NUM];
	for (int i = 0; i < NUM; i++) {
		group[i].len = i + 1;
		group[i].count = 2;
		group[i].word = (char**)malloc(sizeof(char*) * 2);
		group[i].word[0] = (char*)malloc(sizeof(char) * group[i].len);
		group[i].word[1] = (char*)malloc(sizeof(char) * group[i].len);
	}

	group[0].word[0] = "a";
	group[0].word[1] = "B";

	group[1].word[0] = "BV";
	group[1].word[1] = "AA";

	group[2].word[0] = "SSS";
	group[2].word[1] = "AAA";


	for (int i = 0; i < NUM; i++) {
		char* tempStr = (char*)malloc(sizeof(char) * (group[i].len + 1));

		for (int j = 0; j < group[i].count - 1; j++) {
			for (int k = j+1; k < group[i].count; k++) {
				if (strcmp(group[i].word[j], group[i].word[k]) > 0) {
					strcpy(tempStr, group[i].word[j]);	// 바꿀 때 임시로 temp에 저장한다.
					strcpy(group[i].word[j], group[i].word[k]);
					strcpy(group[i].word[k], tempStr);
				}
			}
		}
	}

	Group** group_address_sort = (Group**)malloc(sizeof(Group*)*NUM);
	for (int i = 0; i < NUM; i++)
		*group_address_sort = (Group*)malloc(sizeof(Group));

	for (int i = 0; i < NUM; i++) {
		group_address_sort[i] = group + i;
	}

	Group** temp;
	for (int i = 0; i < NUM; i++) {
		for (int j = 0; j < 2; j++) {
			if (group_address_sort[i][0].len > group_address_sort[j][0].len) {
				temp = group_address_sort[i];
				group_address_sort[i] = group_address_sort[j];
				group_address_sort[j] = temp;
			}
		}
	}

	for (int i = 0; i < NUM; i++) {
		printf("%d - letter: ", group[i].len);

		for (int j = 0; j < group[i].count; j++) {

			printf("%d ", group[i].word[j]);
		}
		printf("\n");
	}
}