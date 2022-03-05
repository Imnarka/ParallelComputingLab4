#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <omp.h>
#include <locale.h>
#include <iostream>
#include <windows.h>


using std::cout;

float solution(float A, float den, int N) {
	for (int i = 0; i < N - 1; i++) {
		A *= 2 / den;
		den = sqrt(2 + den);
	}
	return A;
}

int main()
{
	int N, M, k, i;
	float den = sqrt(2);
	float A = 2;
	float B;
	scanf("%d", &N);
	scanf("%d", &M);

	if (N != 1) {
		A = solution(A, den, N);
	}
	
	B = 6 / A;

	for (int i = 1; i <= M; i++) {
		B *= pow((2 * i + 3) / (2 * i + 1), 2 * i + 1) * pow((i / (i + 1)), 2 * i);
	}
	
}