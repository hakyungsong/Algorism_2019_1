#include <stdio.h>
#include <string>
#include <iostream>

//인자를 3개를 넣었을 때, 제일 큰 값을 return하는 함수
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
	//누적 합을 저장해두는 배열 c
	int **c = new int*[n + 1];
	for (int i = 0; i <= n; i++) {
		c[i] = new int[n + 1];
	}

	//0행과 0열에는 0으로 값을 초기화 해둔다.
	for (int i = 0; i <= n; i++) {
		c[i][0] = 0;
	}
	for (int j = 0; j <= n; j++) {
		c[0][j] = 0;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			//대각선 중 최대
			int w_max = max(c[i - 1][j], c[i][j - 1], c[i - 1][j - 1]);
			c[i][j] = arr[i - 1][j - 1] + w_max;

		}
	}

	printf("-----누적된 경로 값 출력-----\n");
	//누적된 경로 값 출력
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%d ", c[i][j]);
		}
		printf("\n");
	}

	printf("\n(n,n)까지 가는 가장 높은 점수는 %d\n", c[n][n]);
	int count = 0;
	//x와 y는 각 좌표를 저장하는 곳인데, n*n행렬이면 (n,n)에서부터 거꾸로 값을 저장한다.
	int x = n, y = n;

	//행렬을 지나는 최대 갯수가 2n-1(n*n행렬일 때)
	//(1,1)에서 (n,n)까지 가는데 행렬 값을 지나는 최대 갯수가 2n-1이므로
	int max_count = 2 * n - 1;

	//지나온 x좌표와 y좌표를 저장해두는 배열이다.
	int *x_print = new int[max_count];
	int *y_print = new int[max_count];


	//(4,4)에서 거꾸로 온 경로를 따라간다. 좌표값을 x_print,y_print 배열에 저장해둔다.
	for (int i = 1; i <= max_count; i++) {
		//x와 y가 (1,1)에 갈때까지의 조건문 
		if (x != 1 || y != 1) {
			//현재 위치에 누적되어서 저장된 값(c)에서 원래 행렬의 값을 빼준다
			int f_num = c[x][y] - arr[x - 1][y - 1];
			if (f_num == c[x][y - 1]) {//왼쪽으로 이동하는 경우(←)
				x = x;
				y = y - 1;	//열 좌표 감소
				x_print[i] = x;
				y_print[i] = y;

			}
			else if (f_num == c[x - 1][y - 1]) {//왼쪽 대각선으로 이동하는 경우(↖)
				x = x - 1;	//행 좌표 감소	
				y = y - 1;	//열 좌표 감소
				x_print[i] = x;
				y_print[i] = y;

			}
			else if (f_num == c[x - 1][y]) {//위로 이동하는 경우(↑) 
				x = x - 1;		//행 좌표 감소
				y = y;
				x_print[i] = x;
				y_print[i] = y;

			}
			//count는 (1,1)에서 (4,4) 위치까지 이동하는데 가장 높은 점수가 되도록 하는
			//경로로 가는 과정에서 지나온 점수의 갯수이다.
			count++;
		}
	}

	//도착점의 x,y좌표
	x_print[0] = n;
	y_print[0] = n;

	printf("\n--가장 높은 점수를 찾는 경로의 좌표를 출력--");
	//경로의 x,y좌표를 출력함. 순서가 거꾸로 되어있기 때문에 인덱스를 감소시키며 출력한다.
	for (int i = count; i >= 0; i--) {
		printf("\n(%d %d)", x_print[i], y_print[i]);
	}

	return c[n][n];
}

int main(void) {
	//6번 문제에 입력되어있는 행렬 값
	int matrix[][4] = { {6,7,12,5},{5,3,11,18},{7,17,3,3},{8,10,14,9} };
	//문제에 제시되어있는 n*n 행렬의 n값이 4이므로 
	int n = 4;
	//동적으로 n크기로 배열 생성
	int **arr = new int*[n];
	for (int i = 0; i < n; i++) {
		arr[i] = new int[n];
	}

	//문제에 제시되어있는 행렬 값을 동적으로 만든 arr배열에 넣는다.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arr[i][j] = matrix[i][j];
		}
	}
	//arr배열에 잘 들어갔는지 출력하는 과정
	printf("\n-----행렬 경로 값 출력-----\n");
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