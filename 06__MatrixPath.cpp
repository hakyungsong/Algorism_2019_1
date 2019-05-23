#include <stdio.h>
#include <string>
#include <iostream>

//���ڸ� 3���� �־��� ��, ���� ū ���� return�ϴ� �Լ�
int max(int x, int y, int z)
{
	if (x > y) {
		if (x > z) {
			return x;
		}
		else {
			if (y > z)
				return y;
			else
				return z;
		}
	}
	else {
		if (y < z)
			return z;
		else
			return y;
	}
}


int matrixPath(int **arr, int n) {
	//���� ���� �����صδ� �迭 c
	int **c = new int*[n + 1];
	for (int i = 0; i <= n; i++) {
		c[i] = new int[n + 1];
	}

	//0��� 0������ 0���� ���� �ʱ�ȭ �صд�.
	for (int i = 0; i <= n; i++) {
		c[i][0] = 0;
	}
	for (int j = 0; j <= n; j++) {
		c[0][j] = 0;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			//�밢�� �� �ִ�
			int w_max = max(c[i - 1][j], c[i][j - 1], c[i - 1][j - 1]);
			c[i][j] = arr[i - 1][j - 1] + w_max;

		}
	}

	printf("-----������ ��� �� ���-----\n");
	//������ ��� �� ���
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%d ", c[i][j]);
		}
		printf("\n");
	}

	printf("\n(n,n)���� ���� ���� ���� ������ %d\n", c[n][n]);
	int count = 0;
	//x�� y�� �� ��ǥ�� �����ϴ� ���ε�, n*n����̸� (n,n)�������� �Ųٷ� ���� �����Ѵ�.
	int x = n, y = n;

	//����� ������ �ִ� ������ 2n-1(n*n����� ��)
	//(1,1)���� (n,n)���� ���µ� ��� ���� ������ �ִ� ������ 2n-1�̹Ƿ�
	int max_count = 2 * n - 1;

	//������ x��ǥ�� y��ǥ�� �����صδ� �迭�̴�.
	int *x_print = new int[max_count];
	int *y_print = new int[max_count];


	//(4,4)���� �Ųٷ� �� ��θ� ���󰣴�. ��ǥ���� x_print,y_print �迭�� �����صд�.
	for (int i = 1; i <= max_count; i++) {
		//x�� y�� (1,1)�� ���������� ���ǹ� 
		if (x != 1 || y != 1) {
			//���� ��ġ�� �����Ǿ ����� ��(c)���� ���� ����� ���� ���ش�
			int f_num = c[x][y] - arr[x - 1][y - 1];
			if (f_num == c[x][y - 1]) {//�������� �̵��ϴ� ���(��)
				x = x;
				y = y - 1;	//�� ��ǥ ����
				x_print[i] = x;
				y_print[i] = y;

			}
			else if (f_num == c[x - 1][y - 1]) {//���� �밢������ �̵��ϴ� ���(��)
				x = x - 1;	//�� ��ǥ ����	
				y = y - 1;	//�� ��ǥ ����
				x_print[i] = x;
				y_print[i] = y;

			}
			else if (f_num == c[x - 1][y]) {//���� �̵��ϴ� ���(��) 
				x = x - 1;		//�� ��ǥ ����
				y = y;
				x_print[i] = x;
				y_print[i] = y;

			}
			//count�� (1,1)���� (4,4) ��ġ���� �̵��ϴµ� ���� ���� ������ �ǵ��� �ϴ�
			//��η� ���� �������� ������ ������ �����̴�.
			count++;
		}
	}

	//�������� x,y��ǥ
	x_print[0] = n;
	y_print[0] = n;

	printf("\n--���� ���� ������ ã�� ����� ��ǥ�� ���--");
	//����� x,y��ǥ�� �����. ������ �Ųٷ� �Ǿ��ֱ� ������ �ε����� ���ҽ�Ű�� ����Ѵ�.
	for (int i = count; i >= 0; i--) {
		printf("\n(%d %d)", x_print[i], y_print[i]);
	}

	return c[n][n];
}

int main(void) {
	//6�� ������ �ԷµǾ��ִ� ��� ��
	int matrix[][4] = { {6,7,12,5},{5,3,11,18},{7,17,3,3},{8,10,14,9} };
	//������ ���õǾ��ִ� n*n ����� n���� 4�̹Ƿ� 
	int n = 4;
	//�������� nũ��� �迭 ����
	int **arr = new int*[n];
	for (int i = 0; i < n; i++) {
		arr[i] = new int[n];
	}

	//������ ���õǾ��ִ� ��� ���� �������� ���� arr�迭�� �ִ´�.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arr[i][j] = matrix[i][j];
		}
	}
	//arr�迭�� �� ������ ����ϴ� ����
	printf("\n-----��� ��� �� ���-----\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	matrixPath(arr, n);
	return 0;
}