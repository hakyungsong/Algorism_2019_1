// sorting_project.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	NUMOFNUMBERS	325000// 5만개, 7.5만개, 10만개, 12.5만개, ..., 50만개까지 증가시키며 시간 측정할 것

int randNumbers[NUMOFNUMBERS];

// selection sort를 위한 함수들
void mergeSort(int A[], int p,int r);
void merge(int *data, int start, int mid, int end);

int main(int argc, char* argv[])
{
	register long n, i;
	clock_t before;	//시간측정알고리즘
	double elapsed_time;

	std::cout << "알고리즘입문 2019년 1학기 소팅 프로젝트 시작합니다.\n\n";

	srand((unsigned)time(NULL));

	before = clock();
	for (i = NUMOFNUMBERS - 1; i >= 0; i--) {
		n = rand();
		n += ((i + 1) / RAND_MAX) * RAND_MAX;
		randNumbers[NUMOFNUMBERS - 1 - i] = n;
	}
	elapsed_time = (double)(clock() - before) / CLOCKS_PER_SEC;	// 초 단위의 경과 시간을 측정함.
	fprintf(stdout, "%d 개의 랜덤 넘버 생성에 걸린 시간(초): %10.2f\n\n", NUMOFNUMBERS, elapsed_time);

	//std::cout << "정렬전 숫자 입력 값들 출력:\n\n";
	//for (i = 0; i < NUMOFNUMBERS; i++)
	//	printf("%ld ", randNumbers[i]);
	//printf("\n\n");

	// 여기에 각종 정렬 알고리즘을 구현해서 실행시키고 그 실행 시간을 출력합니다.
	// 예: Selection Sort는 다음과 같습니다.
	before = clock();
	mergeSort(randNumbers, 0,NUMOFNUMBERS-1);

	elapsed_time = (double)(clock() - before) / CLOCKS_PER_SEC;	// 초 단위의 경과 시간을 측정함.
	fprintf(stdout, "%d 개의 랜덤 넘버를 merge sort 하는 데에 걸린 시간(초): %10.2f\n\n", NUMOFNUMBERS, elapsed_time);

	//std::cout << "정렬 결과 출력:\n\n";
	//for (i = 0; i < NUMOFNUMBERS; i++)
	//	printf("%ld ", randNumbers[i]);
	//printf("\n\n");

	return 0;
}

int sorted[NUMOFNUMBERS];
void merge(int *data, int start, int mid, int end) {
	int i = start;
	int j = mid + 1;
	int k = start;

	while (i <= mid && j <= end) {
		if (data[i] <= data[j]) {
			sorted[k] = data[i];
			i++;
		}
		else {
			sorted[k] = data[j];
			j++;
		}
		k++;
	}
	if (i > mid) {
		for (int t = j; t <= end; t++) {
			sorted[k] = data[t];
			k++;
		}
	}
	else {
		for (int t = i; t <= mid; t++) {
			sorted[k] = data[t];
			k++;
		}
	}
	// 정렬된 배열을 삽입
	for (int t = start; t <= end; t++) {
		data[t] = sorted[t];
	}
}


void mergeSort(int A[], int p,int r)
{
	int q;
	if (p < r) {
		q = (p + r) / 2;
		mergeSort(A, p, q);
		mergeSort(A, q + 1, r);
		merge(A, p, q, r);
	}
}



