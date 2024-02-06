#ifndef QUICKSORT_H_
#define QUICKSORT_H_
#include <iostream>

namespace GEEKS_FOR_GEEKS_CODE{

/*This code is not owned by me, it is copied from the website:
https://www.geeksforgeeks.org/cpp-program-for-quicksort/
as of the date:
06.02.2024

However this code is free for (commercial) use,
it is just made apparent, that no guarantee for safety or any warranty whatsoever is given 
with consideration of this snippet. 

*/

int partition(float arr[], int start, int end)
{
 
    int pivot = arr[start];
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    std::swap(arr[pivotIndex], arr[start]);
 
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (arr[i] <= pivot) {
            i++;
        }
 
        while (arr[j] > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            std::swap(arr[i++], arr[j--]);
        }
    }
 
    return pivotIndex;
}
 
void quickSort(float arr[], int start, int end)
{
 
    // base case
    if (start >= end)
        return;
 
    // partitioning the array
    int p = partition(arr, start, end);
 
    // Sorting the left part
    quickSort(arr, start, p - 1);
 
    // Sorting the right part
    quickSort(arr, p + 1, end);
}

}


#define QM_SORT(x)  GEEKS_FOR_GEEKS_CODE::quickSort((x),0,((sizeof (x))/(sizeof(*(x)))-1))




#endif