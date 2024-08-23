// bitonic sort function header
#ifndef BITONIC_INTEGER_H
#define BITONIC_INTEGER_H

#define BT_INCREMENT 0
#define BT_DECREMENT 1


void bitonicIntegerSort(int* array, size_t length, int direction);

void mergeBitonicInteger(int* array, int length, int direction);

#endif