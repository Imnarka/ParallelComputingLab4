#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <omp.h>
#include <locale.h>
#include <iostream>
#include <windows.h>
#include <ctime>
#include <time.h>


using std::cout;
using std::endl;

float task_A(float A, float den, int N) {
	for (int i = 0; i < N - 1; i++) {
		A *= 2 / den;
		den = sqrt(2 + den);
	}
	return A;
}

float task_B() {
	return 0;
}

int main()
{
	int N, M, k, i;
	float den = sqrt(2);
	float A = 2;
	float B;
	scanf("%d", &N);
	scanf("%d", &M);
	clock_t start, end;
	start = clock();
	if (N != 1) {
		A = task_A(A, den, N);
	}
	cout << A << endl;
	B = 6.0 / A;

	for (int i = 1; i <= M; i++) {
		B *= pow((2.0 * i + 3.0) / (2.0 * i + 1.0), 2.0 * i + 1.0) * pow((i / (i + 1.0)), 2.0 * i);
	}
	//Sleep(100);
	end = clock();
	double time1 = ((double)end - start) / ((double)CLOCKS_PER_SEC);
	cout << B << endl;
	// parallel calculation
	A = 2;
	B = 1;
	clock_t start_time, end_time;
	start_time = clock();
#pragma omp parallel
	{
#pragma omp for schedule(static, 1) reduction(*:A)
		for (int i = 0; i < N - 1; i++) {
			A *= 2 / den;
			den = sqrt(2 + den);
		}
#pragma omp master
		printf("A = %f\n", A);
#pragma omp for schedule(static, 1) reduction(*:B)
		for (int i = 1; i <= M; i++) {
			B *= pow((2.0 * i + 3.0) / (2.0 * i + 1.0), 2.0 * i + 1.0) * pow((i / (i + 1.0)), 2.0 * i);
		}
	}
	B *= 6.0 / A;
	//Sleep(100);
	end_time = clock();
	double time2 = ((double)end_time - start_time) / ((double)CLOCKS_PER_SEC);
	printf("B = %f\n", B);
	printf("Time_1 = %f\n", time1);
	printf("Time_2 = %f\n", time2);
	printf("Boost: %f\n", time1 / time2);
}