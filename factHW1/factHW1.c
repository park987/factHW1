#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256  //최대 버퍼 크기

typedef struct _Group {
	int len; //문자열 길이
	int count; //그룹에 속하는 단어 개수
	char** word; //그룹에 속하는 단어들의 배열
} Group;

void makeGroup(Group* group, int length);  //그룹 생성
void addWord(int length, char* inputStr, int i, int* group_count, Group* groupArr);  //그룹에 단어 추가

int main() {
	printf("단어들을 공백으로 구분하여 입력하세요: ");
	
	char inputStr[MAX_LEN];
	char* tempStr = NULL;
	scanf("%[^\n]s", inputStr);

	int length = 0; //단어 길이
	int i;  //반복문
	Group* groupArr = NULL;  //단어 그룹들의 배열
	int group_count = 0;  //그룹 개수

	for(i = 0; inputStr[i] != 0; i++) {  //NULL값이 나오기 전까지 문자열을 전부 보기
		if (inputStr[i] != ' ') {  //공백 문자 아닐 때
			length++;
		}
		else {  //공백 문자 만났을 때

			//그룹에 단어 추가
			addWord(length,inputStr, i, &group_count, groupArr);

			length = 0;  //단어 길이 초기화
		}

	}

	if (length > 0) {  //마지막 단어
		//그룹에 단어 추가
		addWord(length, inputStr, i, &group_count, groupArr);
	}

	for (i = 0; i < group_count; i++) {
		printf("%d-letter words: ", groupArr[i].len);
		for (int j = 0; j < groupArr[i].count; j++) {
			printf("%s ", groupArr[i].word + j);
		}
		printf("\n");
	}



}

void makeGroup(Group* group, int length) {  //그룹 생성
	group->count = 1;
	group->len = length;
		
	/*group->word = (char**)malloc(sizeof(char*) * 1);
	group->word[0] = (char*)malloc(sizeof(char) * (length + 1));*/

	group->word = (char**)malloc(sizeof(char*) * group->count);
	if (group->word == NULL) {  //메모리 할당 실패
		perror("Mem err");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < group->count; ++i) {
		group->word[i] = (char*)malloc(sizeof(char) * (length + 1));
		if (group->word[i] == NULL) {   //메모리 할당 실패2
			perror("Mem err2");
			exit(EXIT_FAILURE);
		}
	}
}

void addWord(int length, char* inputStr, int i, int* group_count, Group* groupArr) {  //그룹에 단어 추가
	char* tempStr = (char*)malloc(sizeof(char) * (length + 1));  //단어 길이만큼 메모리 할당
	strncpy(tempStr, inputStr + (i - length), length);
	tempStr[length] = '\0';

	int flag = 0;  //단어 추가 됐는지 flag값
	int k;
	for (k = 0; k < *group_count; k++) {
		if (length == groupArr[k].len) {  //기존 그룹들 중에 단어길이가 같은 그룹 존재 단어임
			groupArr[k].count++;  //그룹 내 단어 개수 증가
			groupArr[k].word = realloc(groupArr[k].word, sizeof(char) * groupArr[k].count * (length + 1));  //그룹에 속하는 단어 배열 개수 늘리기
			strcpy(groupArr[k].word[groupArr[k].count] + (length + 1), tempStr);

			printf("추가됨: %s\n", groupArr[k].word[groupArr[k].count] + (length + 1));
			flag = 1;
			break;
		}
	}
	if (flag == 0 && length > 0) {    //단어 추가 안됨. 새그룹 만들어야 함.
		(*group_count)++;

		if (groupArr == NULL)       //생성된 그룹 0개(malloc) 
			groupArr = malloc(groupArr, sizeof(Group) * (*group_count));
		else					   //생성된 그룹 0개 아님(realloc)
			groupArr = realloc(groupArr, sizeof(Group) * (*group_count));

		makeGroup(groupArr + k, length);    //새로 그룹 생성

		strcpy((groupArr + k)->word[0], tempStr);

		printf("추가됨: %s\n", (groupArr + k)->word[0]);
	}
	
	free(tempStr);
}