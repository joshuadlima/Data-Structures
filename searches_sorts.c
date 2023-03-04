#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define sint(x) scanf("%d", &x)

// searches
int linear_search(int arr[], int n, int v);
int binary_search_recursive(int arr[], int low, int up, int v);
int binary_search_non_recursive(int arr[], int n, int v);

// sorts
void selection_sort(int ARR[], int n);
void bubble_sort(int ARR[], int n);
void insertion_sort(int ARR[], int n);

void merge(int arr[], int temp[], int l1, int h1, int l2, int h2);
void cpy(int arr[], int temp[], int l, int h);
void merge_sort_recursive(int arr[], int low, int high);

void merge_pass(int arr[], int temp[], int size, int n);
void merge_sort_iterative(int arr[], int n);

void shell_sort();

void heap_sort(int arr[], int n);

// print
void print(int arr[], int n);

int main()
{
    int arr[100], ARR[100], n, sc, v;
    printf("enter the number of elements in the array\t"), sint(n);
    printf("enter the content of the array\t");
    for (int i = 0; i < n; i++)
        sint(arr[i]);

    while (1)
    {
        printf("0 -> merge sort\n1 -> linear search\n2 -> binary search rec\n3 -> binary search nrec\n4 -> selection sort\n5 -> bubble sort\n6 -> insertion sort\n7 -> exit\n"), sint(sc);

        switch (sc)
        {
        case 0:
            print(arr, n), merge_sort_iterative(arr, n);
            print(arr, n);
            break;

        case 1:
            sint(v), linear_search(arr, n, v);
            break;

        case 2:
            sint(v), binary_search_recursive(arr, 0, n - 1, v);
            break;

        case 3:
            sint(v), binary_search_non_recursive(arr, n, v);
            break;

        case 4:
            print(arr, n), selection_sort(arr, n);
            break;

        case 5:
            print(arr, n), bubble_sort(arr, n);
            break;

        case 6:
            print(arr, n), insertion_sort(arr, n);
            break;

        case 7:
            exit(0);

        default:
            exit(1);
        }
    }
    return 0;
}

// searches
int linear_search(int arr[], int n, int v)
{
    for (int i = 0; i < n; i++)
        if (arr[i] == v)
        {
            printf("found at %d\n", i);
            return i;
        }

    printf("not found\n");
    return -1;
}

int binary_search_recursive(int arr[], int low, int up, int v)
{

    if (low > up)
    {
        printf("not found\n");
        return -1;
    }

    int mid = (low + up) / 2;

    if (arr[mid] == v)
    {
        printf("found at %d\n", mid);
        return mid;
    }
    else if (arr[mid] > v)
        return binary_search_recursive(arr, low, mid - 1, v);
    else
        return binary_search_recursive(arr, mid + 1, up, v);
}

int binary_search_non_recursive(int arr[], int n, int v)
{
    int low, up, mid;
    low = 0, up = n - 1, mid = -1;

    while (low <= up)
    {
        mid = (low + up) / 2;

        if (arr[mid] == v)
        {
            printf("found at %d\n", mid);
            return mid;
        }
        else if (arr[mid] > v)
            up = mid - 1;
        else
            low = mid + 1;
    }

    printf("not found\n");
    return -1;
}

// sorts
void selection_sort(int ARR[], int n)
{
    int arr[100];
    for (int i = 0; i < n; i++)
        arr[i] = ARR[i];

    for (int i = 0; i < n - 1; i++)
    {
        int si = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] > arr[j])
                si = j;
            if (si != i)
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;

                si = i;
            }
        }
    }

    print(arr, n);
}

void bubble_sort(int ARR[], int n)
{
    int arr[100];
    for (int i = 0; i < n; i++)
        arr[i] = ARR[i];

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    print(arr, n);
}

void insertion_sort(int ARR[], int n)
{
    int arr[100];
    for (int i = 0; i < n; i++)
        arr[i] = ARR[i];

    for (int i = 1; i < n; i++)
    {
        int curr = arr[i], j;
        for (j = i - 1; j >= 0 && curr < arr[j]; j--)
        {
            arr[j + 1] = arr[j];
            arr[j] = curr;
        }
    }

    print(arr, n);
}

void merge(int arr[], int temp[], int l1, int h1, int l2, int h2)
{
    int i = l1, j = l2, k = l1;

    while (i <= h1 && j <= h2)
    {
        if (arr[i] < arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= h1)
        temp[k++] = arr[i++];
    while (j <= h2)
        temp[k++] = arr[j++];
}

void cpy(int arr[], int temp[], int l, int h)
{
    for (int i = l; i < h + 1; i++)
        arr[i] = temp[i];
}

void merge_sort_recursive(int arr[], int low, int high)
{
    if (low >= high)
        return;

    int mid = (low + high) / 2, temp[100];
    merge_sort_recursive(arr, low, mid);
    merge_sort_recursive(arr, mid + 1, high);
    merge(arr, temp, low, mid, mid + 1, high);
    cpy(arr, temp, low, high);
}

void merge_pass(int arr[], int temp[], int size, int n)
{
    int l1 = 0;
    while (l1 + size < n)
    {
        int h1 = l1 + size - 1;
        int l2 = h1 + 1;
        int h2 = (l2 + size - 1 < n) ? l2 + size - 1 : n - 1; // overflow

        merge(arr, temp, l1, h1, l2, h2);
        l1 = h2 + 1;
    }

    // to put the elements which couldnt be made into a merge
    for (int i = l1; i <= n - 1; i++)
        temp[i] = arr[i];

    cpy(arr, temp, 0, n - 1);
}

void merge_sort_iterative(int arr[], int n)
{
    int size = 1, temp[100];

    while (size < n)
    {
        merge_pass(arr, temp, size, n);
        size *= 2;
    }
}

// print
void print(int arr[], int n)
{
    printf("the array content is : ");
    for (int i = 0; i < n; i++)
        printf("%d\t", arr[i]);
    printf("\n");
}
