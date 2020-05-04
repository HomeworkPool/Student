#ifndef __IncludeGuard_ArrayUtils
#define __IncludeGuard_ArrayUtils
#include <stddef.h>
#include "../structures.h"

void StudentArraySort_ShellSort(student** array, int length) {
    student* temp = NULL;

    for (int d = length / 2; d >= 1; d = d / 2) {
        for (int i = d - 1; i < length; i += d) {
            if (array[i]->order < array[i - d]->order) {
                temp = array[i];

                for (int j = i - d; j >= 0 && array[j] > array[j + d]; j -= d) {
                    student* temp2 = array[j + d];
                    array[j + d] = array[j];
                    array[j] = temp;
                }
            }
        }
    }
}

void _StudentArrayUtil_ArrangeHeap(student** array, int beginPosition, int endPosition) {
    student* temp = NULL;
    int root = beginPosition;
    
    while (root <= endPosition / 2) {
        if (root == 0) break;
        int leftChild = 2 * root;
        
        //Left child key is $leftChild - 1
        if (array[leftChild - 1] > array[root - 1]) {
            temp = array[root - 1];
            array[root - 1] = array[leftChild - 1];
            array[leftChild - 1] = temp;
        }

        //Right child key is $leftChild
        if (array[leftChild] > array[root - 1]) {
            temp = array[root - 1];
            array[root - 1] = array[leftChild];
            array[leftChild] = temp;
        }

        root *= 2;
    }
}

void StudentArrayUtil_ConvertToHeap(student** array, int beginPosition, int endPosition) {
    beginPosition++;

    for (int i = endPosition / 2; i >= beginPosition; i--) {
        _StudentArrayUtil_ArrangeHeap(array, i, endPosition);
    }
}

void StudentArraySort_HeapSort(student** array, int length) {
    student* temp = NULL;
    StudentArrayUtil_ConvertToHeap(array, 0, length);
    
    for (int i = length - 1; i > 0; i--) {
        temp = array[0];
        array[0] = array[i];
        array[i] = temp;

        _StudentArrayUtil_ArrangeHeap(array, 1, i - 1);
    }
    
}
#endif