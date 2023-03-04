#include <stdio.h>
#define sint(x) scanf("%d", &x)

//  GFG method (modified partition)

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low;

    for (int j = low; j <= high; j++)
    {
        if (arr[j] < pivot)
        {
            swap(&arr[i], &arr[j]), i++;
        }
    }

    //  now i will be at an element that is greater than or equal to pivot
    swap(&arr[i], &arr[high]);
    return i;
}

void quick_sort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

int main()
{
    int n, arr[100];
    printf("enter number of elements\n"), sint(n);

    printf("enter the %d elements\n", n);
    for (int i = 0; i < n; i++)
        sint(arr[i]);

    quick_sort(arr, 0, n - 1);
    printf("the sorted array:");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}