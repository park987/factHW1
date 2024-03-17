#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256  //�ִ� ���� ũ��

typedef struct _Group {
	int len; //���ڿ� ����
	int count; //�׷쿡 ���ϴ� �ܾ� ����
	char** word; //�׷쿡 ���ϴ� �ܾ���� �迭
} Group;

void makeGroup(Group* group, int length);  //�׷� ����
void addWord(int length, char* inputStr, int i, int* group_count, Group* groupArr);  //�׷쿡 �ܾ� �߰�

int main() {
	printf("�ܾ���� �������� �����Ͽ� �Է��ϼ���: ");
	
	char inputStr[MAX_LEN];
	char* tempStr = NULL;
	scanf("%[^\n]s", inputStr);

	int length = 0; //�ܾ� ����
	int i;  //�ݺ���
	Group* groupArr = NULL;  //�ܾ� �׷���� �迭
	int group_count = 0;  //�׷� ����

	for(i = 0; inputStr[i] != 0; i++) {  //NULL���� ������ ������ ���ڿ��� ���� ����
		if (inputStr[i] != ' ') {  //���� ���� �ƴ� ��
			length++;
		}
		else {  //���� ���� ������ ��

			//�׷쿡 �ܾ� �߰�
			addWord(length,inputStr, i, &group_count, groupArr);

			length = 0;  //�ܾ� ���� �ʱ�ȭ
		}

	}

	if (length > 0) {  //������ �ܾ�
		//�׷쿡 �ܾ� �߰�
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

void makeGroup(Group* group, int length) {  //�׷� ����
	group->count = 1;
	group->len = length;
		
	/*group->word = (char**)malloc(sizeof(char*) * 1);
	group->word[0] = (char*)malloc(sizeof(char) * (length + 1));*/

	group->word = (char**)malloc(sizeof(char*) * group->count);
	if (group->word == NULL) {  //�޸� �Ҵ� ����
		perror("Mem err");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < group->count; ++i) {
		group->word[i] = (char*)malloc(sizeof(char) * (length + 1));
		if (group->word[i] == NULL) {   //�޸� �Ҵ� ����2
			perror("Mem err2");
			exit(EXIT_FAILURE);
		}
	}
}

void addWord(int length, char* inputStr, int i, int* group_count, Group* groupArr) {  //�׷쿡 �ܾ� �߰�
	char* tempStr = (char*)malloc(sizeof(char) * (length + 1));  //�ܾ� ���̸�ŭ �޸� �Ҵ�
	strncpy(tempStr, inputStr + (i - length), length);
	tempStr[length] = '\0';

	int flag = 0;  //�ܾ� �߰� �ƴ��� flag��
	int k;
	for (k = 0; k < *group_count; k++) {
		if (length == groupArr[k].len) {  //���� �׷�� �߿� �ܾ���̰� ���� �׷� ���� �ܾ���
			groupArr[k].count++;  //�׷� �� �ܾ� ���� ����
			groupArr[k].word = realloc(groupArr[k].word, sizeof(char) * groupArr[k].count * (length + 1));  //�׷쿡 ���ϴ� �ܾ� �迭 ���� �ø���
			strcpy(groupArr[k].word[groupArr[k].count] + (length + 1), tempStr);

			printf("�߰���: %s\n", groupArr[k].word[groupArr[k].count] + (length + 1));
			flag = 1;
			break;
		}
	}
	if (flag == 0 && length > 0) {    //�ܾ� �߰� �ȵ�. ���׷� ������ ��.
		(*group_count)++;

		if (groupArr == NULL)       //������ �׷� 0��(malloc) 
			groupArr = malloc(groupArr, sizeof(Group) * (*group_count));
		else					   //������ �׷� 0�� �ƴ�(realloc)
			groupArr = realloc(groupArr, sizeof(Group) * (*group_count));

		makeGroup(groupArr + k, length);    //���� �׷� ����

		strcpy((groupArr + k)->word[0], tempStr);

		printf("�߰���: %s\n", (groupArr + k)->word[0]);
	}
	
	free(tempStr);
}