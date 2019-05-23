#include <iostream>
using namespace std;


//Ai배열부터 Aj배열까지 곱할 때 최저 비용이 나온 순서를 출력하는 함수
void print_min_Matrix(int **s, int i, int j)
{
	/*예를 들어 A2부터 A4배열까지 곱할 떄 최저비용이 나온 순서가 (A2A3)A4라면
	s[2][4]에는 3이 저장되어있다. 즉, 곱하는 괄호가 끝나는 지점의 Ai행렬의 i가 저장되어있는 것*/
	if (i == j)
	{
		//Ai배열부터 Ai배열까지로 i,j값이 같아지면 행렬을 출력
		cout << "A" << i;
	}
	else
	{
		cout << "(";
		print_min_Matrix(s, i, s[i][j]);
		//s[i][j]+1부분(괄호가 끊기는 부분)부터 j배열까지 재귀함수
		print_min_Matrix(s, s[i][j] + 1, j);
		cout << ")";
	}
}

//행렬 곱을 구하는 최소 비용 구하는 함수
int ChainedMatrix(int arr[], int n) {
	int** DP;
	int** S;
	int i, j, k, L;
	int tmp;
	int count = 0;

	//DP 배열은 j번째 행렬부터 k번째 행렬까지의 곱셈 가중치 값 중 최소값
	DP = new int*[n];
	//S 배열은 최소 행렬순서가 정해질때 괄호(행렬곱셈의 일부)가 끝나는 인덱스가 저장된다.
	S = new int*[n];
	for (i = 0; i < n; i++) {
		DP[i] = new int[n];
		S[i] = new int[n];
	}
	for (i = 1; i < n; i++) {
		DP[i][i] = 0;
	}
	for (i = 1; i < n; i++) {
		for (j = 1; j < n - i; j++) {
			k = i + j;
			DP[j][k] = INT32_MAX;   //최댓값을 넣어둔다.(초기화)
			for (L = j; L <= k - 1; L++) {
				/*
				tmp값은 Aj부터 Ak배열까지 곱할 때 경우의 수에 따른 모든 비용을 계산한다.
				예를 들어, i가 2,j가 3, k가 5 이면 DP가 j부터 k까지, 즉 A3부터 A5까지 곱하는 경우이다.
				(A3)(A4A5)과 (A3A4)(A5) 이렇게 두 가지가 가능하다. 이 둘 중 최소 비용만 저장해야한다.
				L은 3부터 4까지 증가하므로
				L이 3일때를 살펴보면
				tmp 값은 DP[3][3]+DP[4][5]+arr[2]*arr[3]*arr[5] 가 되는데 이 값은,
				A3부터 A3까지 곱하는 값, A4부터 A5까지 곱하는 값을 각각 더하고 A3*(A3A4)를 곱하는 비용을 더한다.
				L이 4일 때를 살펴보면
				tmp 값은 DP[3][4]+DP[5][5]+arr[2]*arr[5]*arr[5]가 되는데 이는 (A3A4)(A5) 을 구하는 비용이다.
				*/
				tmp = DP[j][L] + DP[L + 1][k] + arr[j - 1] * arr[L] * arr[k];


				if (tmp < DP[j][k])
				{
					/*Aj배열부터 Ak배열까지 곱하는 가중치 중 가장 작은 값을 DP[j][k]에 넣어야하기 때문에
					기존에 저장되어있는 값보다 작은 값이 생기면 값을 update한다.
					위의 예시 중 더 작은 값을 최소비용으로 DP[j][k]에 저장시켜야 한다.*/
					DP[j][k] = tmp;

					//Aj부터 Ak까지 곱해가는 과정 중 최솟값이 나왔을 때의 index값을 저장해둔다.
					//이는 print_min_Matrix 에서 출력할 때 사용된다.
					S[j][k] = L;
				}
			}
		}
	}
	printf("-----최적 행렬 곱셈 순서-----\n");
	//S배열에서 1부터 p배열 갯수-1까지 곱했을 때 순서를 출력해야하므로 인덱스를 매개변수를 1,n-1을 주었다.
	print_min_Matrix(S, 1, n - 1);
	cout << "\n" << endl;

	//행렬의 갯수는 p배열 갯수(n값)의 -1이므로 DP의 A1번째 행렬부터 A(n-1)까지 합 중 최소값을 저장한 값을 출력한다.
	return DP[1][n - 1];
}


//모든 가능한 곱셈 순서의 갯수를 구하는 함수
int Count_DP(int n, int* C) {

	//C 배열 내의 값들을 초기화
	for (int i = 0; i <= n; i++) {
		C[i] = 0;
	}

	//행렬 1개를 곱하는 횟수는 1개, 2개를 곱하는 횟수는 1개밖에 없으므로 미리 저장해둠
	C[1] = 1;
	C[2] = 1;

	//C 배열에 값을 저장해두면서 필요시 그 값을 꺼내쓴다
	/*예를 들어 C[4]일 경우
	1-(A1)*(A2A3A4)
	2-(A1A2)*(A3A4)
	3-(A1A2A3)*(A4)
	이렇게 경우가 나뉘는데,
	1번의 경우에는 A2A3A4를 곱하는 경우의 수는 행렬 3개를 곱하는 것이므로 C[3]에 저장되어있다
	2번의 경우에는 C[2]*C[2]
	3번의 경우에는 C[3]*C[1]의 방식으로 이미 전단계에서 저장시켜놓은 값을 사용하면 된다.
	*/
	for (int j = 3; j <= n; j++) {
		for (int i = 1; i <= j - 1; i++) {
			C[j] += C[i] * C[j - i];
		}
	}

	//행렬 n개를 곱했을때의 결과를 반환한다.
	return C[n];
}

int main(void) {
	//1번 문제에 제시되어있던 행렬 <p0,p1,p2,p3,p4,p5>값 입력
	int p[] = { 10,5,20,7,15,3};
	int length = sizeof(p) / sizeof(int);

	//p배열로 인해 만들어지는 행렬갯수는 p배열 갯수-1이다.
	//(A1=p0xp1, A2=p1xp2, A3=p2xp3, A4=p3xp4, A5=p4xp5 이기 때문)
	int matrix_num = length - 1;

	//곱셈 최소비용을 구하는 함수
	ChainedMatrix(p, length);

	/*Count_DP에서 사용할 것
	C행렬은 각 인덱스 값만큼 행렬갯수을 곱할 때 곱셈 횟수이다.
	예를 들어 C[3]은 행렬 3개를 곱할때 나올 수 있는 가짓수이다.*/
	int *C = new int(matrix_num);

	/*모든 가능한 곱셈 순서의 갯수를 출력하는 함수.
	행렬의 갯수와, C 행렬을 매개변수로 입력한다.*/
	printf("-----모든 가능한 곱셈 순서의 갯수-----\n");
	cout << Count_DP(matrix_num, C) << endl;

	return 0;
}