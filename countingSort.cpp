// sorting_project.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	NUMOFNUMBERS	325000// 5만개, 7.5만개, 10만개, 12.5만개, ..., 50만개까지 증가시키며 시간 측정할 것
#define RANDLIMIT 325000

long randNumbers[NUMOFNUMBERS];

// selection sort를 위한 함수들
void countingSort(long A[NUMOFNUMBERS + 1], long n);

int main(int argc, char* argv[])
{
	register long n, i;
	clock_t before;	//시간측정알고리즘
	double elapsed_time;

	std::cout << "알고리즘입문 2019년 1학기 소팅 프로젝트 시작합니다.\n\n";

	srand((unsigned)time(NULL));

	before = clock();
	for (i = NUMOFNUMBERS - 1; i >= 0; i--) {
		n = rand() % RANDLIMIT;
		//n += ((i + 1) / RAND_MAX) * RAND_MAX;
		n += ((i + 1) / RANDLIMIT) * RANDLIMIT;
		randNumbers[NUMOFNUMBERS - 1 - i] = n;
	}
	elapsed_time = (double)(clock() - before) / CLOCKS_PER_SEC;	// 초 단위의 경과 시간을 측정함.
	fprintf(stdout, "%d 개의 랜덤 넘버 생성에 걸린 시간(초): %10.2f\n\n", NUMOFNUMBERS, elapsed_time);

	//std::cout << "정렬전 숫자 입력 값들 출력:\n\n";
	//for (i = 0; i < NUMOFNUMBERS; i++)
	//	printf("%ld ", randNumbers[i]);
	//printf("\n\n");

	before = clock();
	countingSort(randNumbers, NUMOFNUMBERS);

	elapsed_time = (double)(clock() - before) / CLOCKS_PER_SEC;	// 초 단위의 경과 시간을 측정함.
	fprintf(stdout, "%d 개의 랜덤 넘버를 counting sort 하는 데에 걸린 시간(초): %10.2f\n\n", NUMOFNUMBERS, elapsed_time);

	//std::cout << "정렬 결과 출력:\n\n";
	//for (i = 1; i < NUMOFNUMBERS+1; i++)
//		printf("%ld ", randNumbers[i]);
	//printf("\n\n");

	return 0;
}


void countingSort(long A[NUMOFNUMBERS + 1], long n) {
	int count[RANDLIMIT + 1], countSum[RANDLIMIT + 2], B[NUMOFNUMBERS + 1];

	//count배열 초기화
	for (int i = 0; i <= RANDLIMIT; i++)
		count[i] = 0;

	//숫자 등장 횟수 세기
	for (int i = 1; i <= RANDLIMIT; i++) {
		count[A[i]]++;
	}

	//누적합 구성
	countSum[0] = count[0];
	for (int i = 1; i <= RANDLIMIT + 1; i++)
		countSum[i] = countSum[i - 1] + count[i];

	//뒤에서부터 수열 A를 순회하며 정렬된 숫자들은 B에 들어감
	for (int i = NUMOFNUMBERS; i >= 1; i--) {
		B[countSum[A[i]]] = A[i];
		countSum[A[i]]--;
	}

	//B배열의 내용을 A에도 넣는다.
	for (int i = 0; i <= NUMOFNUMBERS; i++)
		A[i] = B[i];
}