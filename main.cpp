#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <omp.h>
#include <locale.h>
#include <iostream>
#include <windows.h>


using std::cout;

float solution(float A, float den, int N) {
	A = 2 / den;
	den = sqrt(2 + den);
	return A;
}

int main()
{
	int N, rank, k, i;
	float den = sqrt(2);
	float A = 2;
	scanf("%d", &N);
	if (N != 1) {
		for (int i = 0; i < N-1; i++) {
			A *= 2 / den;
			den = sqrt(2 + den);
		}
	}
	cout << A;
	
}