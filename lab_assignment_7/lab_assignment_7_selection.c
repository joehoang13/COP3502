
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int selectionSort(int arr[], int n, int swap_count[]);
void swap(int* x, int* y);

int main() {
    const int array1_base[9] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
    const int array2_base[9] = {90, 80, 70, 60, 50, 40, 30, 20, 10};

    int array[9] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
    int array2[9] = {90, 80, 70, 60, 50, 40, 30, 20, 10};
    int array_swap_count[9] = {0,0,0,0,0,0,0,0,0};
    int array2_swap_count[9] = {0,0,0,0,0,0,0,0,0};
    
    printf("Array 1:\n");
    int total_swap_arr_1 = selectionSort(array, 9, array_swap_count);

    for(int i = 0; i < 9; i++) {
        printf("%d: %d\n", array1_base[i], array_swap_count[i]);
    } 
    printf("Total Swaps: %d\n\n", total_swap_arr_1);

    printf("Array 2:\n");
    int total_swap_arr_2 = selectionSort(array2, 9, array2_swap_count);

    for(int i = 0; i < 9; i++) {
        printf("%d: %d\n", array2_base[i], array2_swap_count[i]);
    } 
    printf("Total Swaps: %d\n", total_swap_arr_2);
}

void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int selectionSort(int arr[], int n, int swap_count[]) 
{ 
    int min = 0; 
    int total_swap = 0;
    for (int i = 0; i < n-1; i++) 
    { 
        min = i; 
        for (int j = i+1; j < n; j++) 
          if (arr[j] < arr[min]) 
            min = j; 
  
           if(min != i) 
            swap(&arr[min], &arr[i]);
            total_swap++;
            swap_count[min]++;
            swap_count[i]++;
    }
    return total_swap;
} 