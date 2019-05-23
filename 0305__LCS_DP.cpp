#include <stdio.h>
#include <string>
#include <malloc.h>
#include <math.h>
#include<algorithm>
#include <stdlib.h>	//malloc,free함수가 선언된 헤더 파일
#include <iostream>
#define MAX(X,Y) (X > Y ? X : Y)  
using namespace std;

int main() {
	printf("======최장 공통 부분 순서 LCS=====\n");
	//입력 받는 문자열을 input1,input2로 지정함
	string input1, input2;
	int length1, length2;

	//input1,input2를 3번 문제의 값으로 입력해둠
	input1 = "10111010100";
	input2 = "00111010110";

	//각 문자열의 길이를 length1,length2에 각각 저장한다.
	length1 = input1.size();
	length2 = input2.size();

	//string으로 받은 input1,input2를 char형으로 변환시키기 위한 변수 i1,i2
	char *i1 = new char[length1 + 1];
	char *i2 = new char[length2 + 1];

	//string으로 받은 input1을 char형인 i1에 복사한다.
	std::copy(input1.begin(), input1.end(), i1);
	std::copy(input2.begin(), input2.end(), i2);

	//배열 초기화
	i1[input1.size() + 1] = '\0';
	i2[input2.size() + 1] = '\0';

	//C[i][j]는 두 문자열 input1의 1부터 i까지,input2의 1부터 j까지 LCS길이이다.
	int **C = new int*[length1 + 1];
	for (int i = 0; i <= length1; i++) {
		C[i] = new int[length2 + 1];
	}

	//answer는 공통된 문자가 저장될 배열
	char *answer = new char[length1*length2];

	//0행과 0열은 0으로 초기화한다.
	for (int i = 0; i <= length1; i++) {
		C[i][0] = 0;
	}
	for (int j = 0; j <= length2; j++) {
		C[0][j] = 0;
	}


	for (int i = 1; i <= length1; i++) {
		for (int j = 1; j <= length2; j++) {

			//공통 부분을 찾을 경우 이전 인덱스 값에 +1
			if (input1[i - 1] == input2[j - 1]) {
				C[i][j] = C[i - 1][j - 1] + 1;
			}
			//공통 부분이 없는 경우에는 C[i],[j] 입장에서 왼쪽, 위쪽 값 중 큰 값을 가져온다
			else {
				C[i][j] = MAX(C[i - 1][j], C[i][j - 1]);
			}
		}
	}
	/*
	예를 들어 input1이 1101이고, input2가 1010이라면 C배열은 이와같이 완성된다.
	따라서 공통적으로 들어있는 문자열의 길이는 C[length1][length2] 배열 값과 같다.
				 [1] [0] [1] [0]
			  0   0    0    0    0
		[1]  0   1   1    1    1
		[1]  0   1   1    2    2
		[0]  0   1   2    2    3
		[1]  0   1   2    3    3

	*/


	printf("\n공통 문자열의 길이:  %d\n", C[length1][length2]);

	int x = length1;
	int y = length2;
	int idx = 0;

	/*공통 문자열을 출력하는 과정에는 C[length1][length2]에서 거꾸로 구해나가야한다.
	공통 부분이 생겼을 때마다 값이 새로 더해졌으므로 현재 위치를 기준으로
	왼쪽, 위쪽 숫자와 같으면 공통부분이 출력된 index값이 아니고,
	왼쪽 대각선(↖)과 숫자가 같다면 그 부분의 index에 해당하는 문자가 공통된 것이다.
	*/
	while (x > 0 && y > 0) {
		if (C[x][y] == C[x][y - 1])	//왼쪽과 같은지 본다(←)
			y--;
		else if (C[x][y] == C[x - 1][y])	//위쪽과 같은지 본다(↑)
			x--;
		else {										//왼쪽 오른쪽과 다 다르면 대각선 이동(↖)
			answer[idx++] = i1[x - 1];	//문자열에 담기
			x--;
			y--;
		}
	}

	/*answer배열에 담아두었던 공통된 문자열을 출력하는 과정이다.
	바로 전 C[length1][length2]에서 거꾸로 찾아오는 과정을 거쳤으므로 answer에는
	공통된 문자열이 순서가 뒤집혀서 저장되어있으므로 출력할 때 원래 순서대로 출력되도록
	index를 감소시키면서 출력한다.*/
	printf("공통 문자열: ");
	for (int j = idx - 1; j >= 0; j--) {
		printf("%c", answer[j]);
	}

	return 0;
}