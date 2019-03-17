#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct WordInfo
{
	char word[50];
	char class[10];
	char meaning[1000];
}WordInfo;
int size = 0;
WordInfo wInfo[200000];

int readLine(FILE *fp, char str[], int limit)
{
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n' && ch != EOF)
	{
		if (i<limit - 1)
			str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

void read()
{
	char filename[50];
	printf("사전이름 : ");
	scanf("%s", filename);
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("로드실패\n");
	}
	else {
		printf("로드성공\n");
	}

	while (!feof(fp))
	{
		char buffer[1500] = { 0, };
		fflush(stdin);
		readLine(fp, buffer, sizeof(buffer));
		if (strcmp(buffer, "\0") != 0)
		{
			int len = strlen(buffer);
			int s = 0, e = 0;
			int isClassEnded = 0;

			for (int i = 0; i < len; i++)
			{
				if (!isClassEnded)
				{
					if (buffer[i] == '(')
					{
						strncpy(wInfo[size].word, buffer, e - 1);
						s = e;
					}
					else if (buffer[i] == ')')
					{
						strncpy(wInfo[size].class, buffer + s, e - s + 1);
						s = e;
						isClassEnded = 1;
					}
					e++;
				}
			}
			strcpy(wInfo[size].meaning, buffer + s + 2);
			size++;
		}
	}
	fclose(fp);
}

int find(int start, int end, char *target)
{
	if (start >= end) return start;

	int mid = (start + end) / 2;
	int cmp = strcmp(wInfo[mid].word, target);


	if (cmp >= 0)
	{
		return find(start, mid, target);
	}
	else
	{
		return find(mid + 1, end, target);
	}
}

void findWord()
{
	char toFind[50] = { 0, };
	getchar();
	gets(toFind);
	_strlwr(toFind);
	toFind[0] -= 32;

	int tidx = find(0, size - 1, toFind);
	if (strcmp(wInfo[tidx].word, toFind) != 0)
	{
		printf("Not Found\n");
		if (tidx != 0)
			printf("%s %s %s\n", wInfo[tidx - 1].word, wInfo[tidx - 1].class, wInfo[tidx - 1].meaning);
		printf("- - -\n");
		if (tidx != size - 1)
			printf("%s %s %s\n", wInfo[tidx].word, wInfo[tidx].class, wInfo[tidx].meaning);
	}
	else
	{
		while (strcmp(wInfo[tidx].word, toFind) == 0) 
		{
			printf("%s %s %s\n", wInfo[tidx].word, wInfo[tidx].class, wInfo[tidx].meaning);
			tidx++;
		}
	}
}

int main()
{
	char command[10];
	int isread = 0;


	while (1)
	{
		printf("read : 사전파일로드 size : 단어갯수출력 find : 단어찾기\n");
		printf("$ ");
		scanf("%s", command);
		getchar();
		
		if (strcmp(command, "read") == 0)
		{
			isread = 1;
			read();
		}
		else
		{
			if (!isread)
			{
				printf("먼저 파일을 로드 해주십시오.\n");
				continue;
			}

			if (strcmp(command, "size") == 0) 
			{
				printf("%d\n", size);
			}
			else if (strcmp(command, "find") == 0)
			{
				findWord();
			}
		}
	}
	return 0;
}