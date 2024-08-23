// bitonic sort functions
#include <stddef.h>
#include <stdio.h>
#include <omp.h>
#include "bitonic_integer.h"

size_t pow2lt(size_t n) {
	size_t x = 1;
	while(x<<1 < n) {x<<=1;}
	return x;
}

void bitonicIntegerSort(int* array, size_t length, int direction) {
	// base case
	if (length <= 1) return;
	#pragma omp parallel
	#pragma omp single
	{
		switch(direction) {
			case BT_INCREMENT:
			{
				if (length == 2) {
					if (*array > *(array+1)){
						// exchange 
						(*array) 	^= *(array+1);
						*(array+1) 	^= *array;
						(*array) 	^= *(array+1);					
					}
					break;
				}
				//printf("Bitonic sort incremently with array size=%d.\n", length);
				#pragma omp taskgroup
				{
					#pragma omp task
					{bitonicIntegerSort(array, length/2, BT_DECREMENT);}
					#pragma omp task
					{bitonicIntegerSort(array+(length/2), length-length/2, BT_INCREMENT);}
					
					#pragma omp taskwait
					
					#pragma omp task
					{mergeBitonicInteger(array, length, direction);}
				}
				
				break;
			}
			case BT_DECREMENT:
			{
				if (length == 2) {
					if (*array < *(array+1)){
						// exchange 
						(*array) 	^= *(array+1);
						*(array+1) 	^= *array;
						(*array) 	^= *(array+1);					
					}
					break;
				}
				//printf("Bitonic sort decremently with array size=%d.\n", length);
				#pragma omp taskgroup
				{
					#pragma omp task
					{bitonicIntegerSort(array, length/2, BT_INCREMENT);}
					#pragma omp task
					{bitonicIntegerSort(array+(length/2), length-length/2, BT_DECREMENT);}
					
					#pragma omp taskwait
					
					#pragma omp task
					{mergeBitonicInteger(array, length, direction);}					
				}
				
				break;			
			}
			default:
			{
				//printf("Undefined direction=%d.\n", direction);
				break;
			}
		}
	}
}

void mergeBitonicInteger(int* array, int length, int direction) {
	//printf("merging bitonic sequence with size=%d and size=%d.\n", length1, length2);
	if (length <= 1) return;
	#pragma omp parallel
	{
		switch(direction) {
			case BT_INCREMENT:
			{
				int x;
				int halfLength = pow2lt(length);
				for (int i = 0; i < length-halfLength; i++) {
					if (*(array+i) > *(array+i+halfLength)) {
						x = *(array+i+halfLength);
						*(array+i+halfLength) = *(array+i);
						*(array+i) = x;
					}
				}
				#pragma omp task
				{mergeBitonicInteger(array, halfLength, direction);}
				
				#pragma omp task
				{mergeBitonicInteger(array+halfLength, length-halfLength, direction);}
				break;
			}
			case BT_DECREMENT:
			{
				int x;
				int halfLength = pow2lt(length);
				for (int i = 0; i < length-halfLength; i++) {
					if (*(array+i) < *(array+i+halfLength)) {
						x = *(array+i+halfLength);
						*(array+i+halfLength) = *(array+i);
						*(array+i) = x;
					}
				}
				#pragma omp task
				{mergeBitonicInteger(array, halfLength, direction);}
				
				#pragma omp task
				{mergeBitonicInteger(array+halfLength, length-halfLength, direction);}
				break;
			}
			default:
			{
				break;
			}
		}
	}
}