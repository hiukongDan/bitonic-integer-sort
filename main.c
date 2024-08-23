#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "random.h"
#include "bitonic_integer.h"


int main() {
	// generate random number
	setSeed(123);
	int cap = 100000;
	int length = 62129;
	int arr[length];
	double startTime, endTime;
	
	// generate random number array
	for (int i = 0; i < length; i++) {
		arr[i] = randomInt() % cap;
		//printf("%d\t", arr[i]);
	}
	// printf("\n");
	
	startTime = omp_get_wtime();
	// feed in the random number array to bitonic sort function
	bitonicIntegerSort(arr, length, BT_INCREMENT);
	int passFlag = 1;
	for (int i = 0; i < length-1; i++) {
		// printf("%d\t", arr[i]);
		if (arr[i] > arr[i+1]) {
			//printf("FAIL pair: (%d, %d), at index (%d, %d).\n", arr[i], arr[i+1], i, i+1);
			passFlag = 0;
		}
	}
	// printf("%d.\n", arr[length-1]);
	endTime = omp_get_wtime();
	
	if (passFlag == 1) {
		puts("PASS");
	} else {
		puts("FAIL");
	}
	
	printf("Complete tasks using %fs wall clock time.\n", endTime-startTime);
	return 0;
}