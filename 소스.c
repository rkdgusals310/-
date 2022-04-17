#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <string.h>

void swap(int arr[], int a, int b);
void ex_sort(int arr[], int size);
void mg_sort(int arr[], int L, int R, int* sortArr);
void mgTwoArea(int arr[], int L, int M, int R, int* sortArr);
//void swap1(int arr[], int a, int b);
int partition(int arr[], int L, int R);
void q_sort(int arr[], int L, int R);
//void swap(int arr[], int i, int j);
void heapify(int arr[], int size, int i);
void hp_sort(int arr[], int size);
void rd_sort(int* a, int n, int result[]);



int main()
{
	int n ;
	clock_t start, finish;
	double sum0 = 0;
	double sum1 = 0;
	double sum2 = 0;
	double sum3 = 0;
	double sum4 = 0;
	
	printf("몇개의 랜덤데이터를 생성할까요?");
	scanf_s("%d", &n);
	for (int i = 0; i < 5; i++)
	{

		int* arr = (int*)malloc(sizeof(int) * n);
		int* arr1 = (int*)malloc(sizeof(int) * n);
		int* arr2 = (int*)malloc(sizeof(int) * n);
		int* arr3 = (int*)malloc(sizeof(int) * n);
		int* arr4 = (int*)malloc(sizeof(int) * n);
		int* arr5 = (int*)malloc(sizeof(int) * n);
		int* sortArr = (int*)malloc(sizeof(int) * (n));
		int* result = (int*)malloc(sizeof(int) * (n));
		

		for (int j = 0; j < n; j++)
		{
			int random= rand()%n;
			arr[j] = random;
			arr1[j] = arr[j];
			arr2[j] = arr[j];
			arr3[j] = arr[j];
			arr4[j] = arr[j];
			arr5[j] = arr[j];
		}
			
		start = clock();
		ex_sort(arr1, n);
		finish = clock();

		sum0 += (double)(finish - start) / CLOCKS_PER_SEC;

		start = clock();
		mg_sort(arr2, 0, n - 1, sortArr);
		finish = clock();
		sum1 += (double)(finish - start) / CLOCKS_PER_SEC;

		start = clock();
		q_sort(arr3, 0, n - 1);
		finish = clock();
		sum2 += (double)(finish - start) / CLOCKS_PER_SEC;

		start = clock();
		hp_sort(arr4, n);
		finish = clock();
		sum3 += (double)(finish - start) / CLOCKS_PER_SEC;

		start = clock();
		rd_sort(arr5,n, result);
		finish = clock();
		finish = clock();
		//printf("%f\n", (double)(finish - start) / CLOCKS_PER_SEC);
		sum4 = (double)(finish - start) / CLOCKS_PER_SEC;

		free(arr);
		free(arr1);
		free(arr2);
		free(arr3);
		free(arr4);
		free(arr5);
		free(sortArr);
		free(result);

	}

	printf("Exchange sort 실행 평균:%f\n", sum0 / 5);
	printf("Mergesort 실행 평균:%f\n", sum1 / 5);
	printf("Quicksort 실행 평균:%f\n", sum2 / 5);
	printf("Heapsort 실행 평균:%f\n", sum3 / 5);
	printf("Radix sort 실행 평균:%f", sum4 / 5);
}

void swap(int arr[], int a, int b) 
{
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}
//Exchange sort
void ex_sort(int arr[], int size)
{
	int temp;
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (arr[i] > arr[j]) {
				/*temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;*/
				swap(arr, i, j);
			}
		}
	}
}
//Mergesort
void mgTwoArea(int arr[], int L, int M, int R,int sortArr[])
{
	int l_idx = L;   
	int r_idx = M + 1;  
	int i;
	int s_idx = L;      

	while (l_idx <= M && r_idx <= R)
	{  
		if (arr[l_idx] <= arr[r_idx])
		{   
			sortArr[s_idx] = arr[l_idx];
			l_idx++;
		}
		else 
		{                        
			sortArr[s_idx] = arr[r_idx];
			r_idx++;
		}
		s_idx++; 

	}

	if (l_idx > M)
	{
		for (i = r_idx; i <= R; i++)
		{
			sortArr[s_idx++] = arr[i];
		}
	}
	else
	{
		for (i = l_idx; i <= M; i++)
		{
			sortArr[s_idx++] = arr[i];
		}
	}
	for (i = L; i <= R; i++)
	{
		arr[i] = sortArr[i];
	}
}
void mg_sort(int arr[], int L, int R, int* sortArr)
{
	int M;
	if (L < R)
	{
		M = (L + R) / 2;
		mg_sort(arr, L, M, sortArr);
		mg_sort(arr, M + 1, R, sortArr);
		mgTwoArea(arr, L, M, R, sortArr);
	}
}

// Quicksort
/*void swap1(int arr[], int a, int b) {
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}*/
int partition(int arr[], int L, int R) 
{
	int pivot = arr[L], low = L + 1, high = R, temp;
	while (low <= high) {
		while (low <= R && pivot >= arr[low]) low++;
		while (high >= (L + 1) && pivot <= arr[high]) high--;
		if (low <= high) swap(arr, low, high);
	}
	swap(arr, L, high);
	return high;
}
void q_sort(int arr[], int L, int R) 
{
	if (L <= R) {
		int pivot = partition(arr, L, R);
		q_sort(arr, L, pivot - 1);
		q_sort(arr, pivot + 1, R);
	}
}

//Heapsort
/*void swap(int arr[], int i, int j) 
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}*/
void heapify(int arr[], int size, int i)
{

	int c = 2 * i + 1;

	if (c < size - 1 && arr[c] < arr[c + 1])
		c++;

	if (c < size && arr[i] < arr[c])
		swap(arr, i, c);
	
	if (c < size / 2)
		heapify(arr, size, c);
}
void hp_sort(int arr[], int size) 
{
	for (int i = size / 2; i >= 0; i--) 
	{
		heapify(arr, size, i);
	}

	for (int i = size - 1; i >= 0; i--)
	{
		swap(arr, i, 0);
		heapify(arr, i, 0);
	}

}
//Radix sort
void rd_sort(int* a, int n,int result[]) 
{
	int  maxValue = 0;
	int exp = 1;
	for (int i = 0; i < n; i++) 
	{
		if (a[i] > maxValue) 
			maxValue = a[i];
	}
	while (maxValue / exp > 0) 
	{
		int bucket[10] = { 0 };
		for (int i = 0; i < n; i++)
		{
			bucket[a[i] / exp % 10]++;
		}
			
		for (int i = 1; i < 10; i++)
		{
			bucket[i] += bucket[i - 1];
		}
			
		for (int i = n - 1; i >= 0; i--) 
		{
			result[--bucket[a[i] / exp % 10]] = a[i];
		}
		for (int i = 0; i < n; i++)
		{
			a[i] = result[i];
		}
			 
		exp *= 10;
	}
}
