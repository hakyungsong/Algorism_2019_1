#include <stdio.h>
#include <string>
#include <malloc.h>
#include <math.h>
#include<algorithm>
#include <stdlib.h>	//malloc,free�Լ��� ����� ��� ����
#include <iostream>
#define MAX(X,Y) (X > Y ? X : Y)  
using namespace std;

int main() {
	printf("======���� ���� �κ� ���� LCS=====\n");
	//�Է� �޴� ���ڿ��� input1,input2�� ������
	string input1, input2;
	int length1, length2;

	//input1,input2�� 3�� ������ ������ �Է��ص�
	input1 = "10111010100";
	input2 = "00111010110";

	//�� ���ڿ��� ���̸� length1,length2�� ���� �����Ѵ�.
	length1 = input1.size();
	length2 = input2.size();

	//string���� ���� input1,input2�� char������ ��ȯ��Ű�� ���� ���� i1,i2
	char *i1 = new char[length1 + 1];
	char *i2 = new char[length2 + 1];

	//string���� ���� input1�� char���� i1�� �����Ѵ�.
	std::copy(input1.begin(), input1.end(), i1);
	std::copy(input2.begin(), input2.end(), i2);

	//�迭 �ʱ�ȭ
	i1[input1.size() + 1] = '\0';
	i2[input2.size() + 1] = '\0';

	//C[i][j]�� �� ���ڿ� input1�� 1���� i����,input2�� 1���� j���� LCS�����̴�.
	int **C = new int*[length1 + 1];
	for (int i = 0; i <= length1; i++) {
		C[i] = new int[length2 + 1];
	}

	//answer�� ����� ���ڰ� ����� �迭
	char *answer = new char[length1*length2];

	//0��� 0���� 0���� �ʱ�ȭ�Ѵ�.
	for (int i = 0; i <= length1; i++) {
		C[i][0] = 0;
	}
	for (int j = 0; j <= length2; j++) {
		C[0][j] = 0;
	}


	for (int i = 1; i <= length1; i++) {
		for (int j = 1; j <= length2; j++) {

			//���� �κ��� ã�� ��� ���� �ε��� ���� +1
			if (input1[i - 1] == input2[j - 1]) {
				C[i][j] = C[i - 1][j - 1] + 1;
			}
			//���� �κ��� ���� ��쿡�� C[i],[j] ���忡�� ����, ���� �� �� ū ���� �����´�
			else {
				C[i][j] = MAX(C[i - 1][j], C[i][j - 1]);
			}
		}
	}
	/*
	���� ��� input1�� 1101�̰�, input2�� 1010�̶�� C�迭�� �̿Ͱ��� �ϼ��ȴ�.
	���� ���������� ����ִ� ���ڿ��� ���̴� C[length1][length2] �迭 ���� ����.
				 [1] [0] [1] [0]
			  0   0    0    0    0
		[1]  0   1   1    1    1
		[1]  0   1   1    2    2
		[0]  0   1   2    2    3
		[1]  0   1   2    3    3

	*/


	printf("\n���� ���ڿ��� ����:  %d\n", C[length1][length2]);

	int x = length1;
	int y = length2;
	int idx = 0;

	/*���� ���ڿ��� ����ϴ� �������� C[length1][length2]���� �Ųٷ� ���س������Ѵ�.
	���� �κ��� ������ ������ ���� ���� ���������Ƿ� ���� ��ġ�� ��������
	����, ���� ���ڿ� ������ ����κ��� ��µ� index���� �ƴϰ�,
	���� �밢��(��)�� ���ڰ� ���ٸ� �� �κ��� index�� �ش��ϴ� ���ڰ� ����� ���̴�.
	*/
	while (x > 0 && y > 0) {
		if (C[x][y] == C[x][y - 1])	//���ʰ� ������ ����(��)
			y--;
		else if (C[x][y] == C[x - 1][y])	//���ʰ� ������ ����(��)
			x--;
		else {										//���� �����ʰ� �� �ٸ��� �밢�� �̵�(��)
			answer[idx++] = i1[x - 1];	//���ڿ��� ���
			x--;
			y--;
		}
	}

	/*answer�迭�� ��Ƶξ��� ����� ���ڿ��� ����ϴ� �����̴�.
	�ٷ� �� C[length1][length2]���� �Ųٷ� ã�ƿ��� ������ �������Ƿ� answer����
	����� ���ڿ��� ������ �������� ����Ǿ������Ƿ� ����� �� ���� ������� ��µǵ���
	index�� ���ҽ�Ű�鼭 ����Ѵ�.*/
	printf("���� ���ڿ�: ");
	for (int j = idx - 1; j >= 0; j--) {
		printf("%c", answer[j]);
	}

	return 0;
}