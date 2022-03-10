#include <omp.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <chrono>
#include <functional>
#include <locale.h>
#include <iostream>

using namespace std;


void task_1(int N, int M) {
	float A = 2;
	for (int i = 1; i < N; i++)
	{
		float znam = 0;
		for (int j = 0; j < i; j++)
		{
			znam = sqrt(2 + znam);
		}
		A = A * 2 / znam;
	}
	printf("A = %f\n", A);

	float B = 1;
	for (int i = 1; i <= M; i++)
	{
		B *= pow((float)(2 * i + 3) / (2 * i + 1), 2 * i + 1) * pow((float)i / (i +
			1), 2 * i);
	}
	B = B * 6 / A;
	printf("B = %f\n", B);
}


void task_2(int N, int M, int C1, int C2) {
	float A = 2;
	float B = 1;
#pragma omp parallel
	{
#pragma omp for schedule(static, C1) reduction(*:A)
		for (int i = 1; i < N; i++)
		{
			float znam = 0;
			for (int j = 0; j < i; j++)
			{
				znam = sqrt(2 + znam);
			}
			A = A * 2 / znam;
		}
#pragma omp master
		printf("A = %f\n", A);
#pragma omp for schedule(static, C2) reduction(*:B)
		for (int i = 1; i <= M; i++)
		{
			B *= pow((float)(2 * i + 3) / (2 * i + 1), 2 * i + 1) * pow((float)i / (i +
				1), 2 * i);
		}
	}
	B = B * 6 / A;
	printf("B = %f\n", B);
}

int main()
{
	int N, M, C1, C2;
	printf("N: ");
	scanf_s("%d", &N);
	printf("M: ");
	scanf_s("%d", &M);

	auto start_time = chrono::high_resolution_clock::now();

	task_1(N, M);

	auto end_time = chrono::high_resolution_clock::now();
	int64_t t_posled = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
	printf("Time_1: %" PRId64 "\n", t_posled);

	printf("C1: ");
	scanf_s("%d", &C1);
	printf("C2: ");
	scanf_s("%d", &C2);

	auto start = chrono::high_resolution_clock::now();

	task_2(N, M, C1, C2);

	auto end = chrono::high_resolution_clock::now();
	int64_t t_paral = chrono::duration_cast<chrono::microseconds>(end - start).count();
	printf("Time_1: %" PRId64 "\n", t_paral);

	float boost = (float)t_posled / t_paral;
	printf("Speedup: %f\n", boost);
	return 0;
}