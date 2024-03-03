#include <stdio.h>

void insertionSort(int arr[], int n);

void binaryinsertionSort(int arr[], int n);

void mergeSort(int arr[], int l, int r);

void selectionSort(int arr[], int n); 

void bubbleSort(int arr[], int n);

void radixsort(int arr[], int n);

void heapSort(int* array, int size);

void quickSort(int arr[], int low, int high);

void countingSort(int array[], int size);

int main(void)
{
	int dizi[] = { 8, 8, 9, 4, 5, 2, 6, 1 };
	//int dizi[] = { 2, 3, 9, 7, 2, 0, 6, 1 };
	int array_size = sizeof(dizi) / sizeof(dizi[0]);
	{
		//selectionSort(dizi, array_size);
		//insertionSort(dizi, array_size); 
		//binaryinsertionSort(dizi, array_size);
		//bubbleSort(dizi, array_size);
		//mergeSort(dizi, 0, array_size -1);
		//countingSort(dizi, array_size); 	
		//radixsort(dizi, array_size);
		//heapSort(dizi, array_size);
		quickSort(dizi, 0, array_size - 1);

		for (int i = 0; i < array_size; i++)
		{
			printf("%d ", dizi[i]);
		}
	}
    return 0;
}

void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

// A utility function to get maximum value in arr[]
int getMax(int arr[], int n)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > mx)
			mx = arr[i];
	return mx;
}

void countSort(int arr[], int n, int exp)
{
	int output[10];
	int i, count[10] = { 0 };

	// Store the count of each element
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	// Store the cummulative count of each array
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Find the index of each element of the original array in count array, and
	// place the elements in output array
	for (i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	// Copy the sorted elements into original array
	for (i = 0; i < n; i++)
		arr[i] = output[i];
}

void radixsort(int arr[], int n)
{
	int m = getMax(arr, n);

	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(arr, n, exp);
}

void selectionSort(int arr[], int n)
{
	int i, j, min_idx;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++)
	{
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;

		// Swap the found minimum element with the first element
		swap(&arr[min_idx], &arr[i]);
	}
}

void countingSort(int array[], int size) {
	int output[10];

	// Find the largest element of the array
	int max = array[0];
	for (int i = 1; i < size; i++) {
		if (array[i] > max)
			max = array[i];
	}

	// The size of count must be at least (max+1) but
	// we cannot declare it as int count(max+1) in C as
	// it does not support dynamic memory allocation.
	// So, its size is provided statically.
	int count[10];

	// Initialize count array with all zeros.
	for (int i = 0; i <= max; ++i) {
		count[i] = 0;
	}

	// Store the count of each element
	for (int i = 0; i < size; i++) {
		count[array[i]]++;
	}

	// Store the cummulative count of each array
	for (int i = 1; i <= max; i++) {
		count[i] += count[i - 1];
 	}

	// Find the index of each element of the original array in count array, and
	// place the elements in output array
	for (int i = size - 1; i >= 0; i--) {
		output[count[array[i]] - 1] = array[i];
		count[array[i]]--;
	}

	// Copy the sorted elements into original array
	for (int i = 0; i < size; i++) {
		array[i] = output[i];
	}
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(int arr[], int low, int high)
{
	int pivot = arr[high]; // pivot
	int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot
		if (arr[j] < pivot)
		{
			i++; // increment index of smaller element
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int L[4], R[4];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
	if (l < r) {
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int m = l + (r - l) / 2;

		// Sort first and second halves
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

void insertionSort(int arr[], int n)
{
	int i, deger, j;
	for (i = 1; i < n; i++) //ilk secilen/bakılan dizideki [1].dizi degeridir.
	{
		deger = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > deger) //bakılan degerin solunda bir dizi degeri var mı? ve o dizi sırasındaki deger bakılan degerden büyük mü? evet ise, bakılan deger sola kaydırılır
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = deger;
	}
}

// A function to implement bubble sort
void bubbleSort(int arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)

		// Last i elements are already in place  
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
}

int binarySearch(int a[], int item, int low, int high)
{
	if (high <= low)
		return (item > a[low]) ?
		(low + 1) : low;

	int mid = (low + high) / 2;

	if (item == a[mid])
		return mid + 1;

	if (item > a[mid])
		return binarySearch(a, item,
			mid + 1, high);
	return binarySearch(a, item, low,
		mid - 1);
}

// Function to sort an array a[] of size 'n'
void binaryinsertionSort(int arr[], int n)
{
	int i, loc, j, selected;

	for (i = 1; i < n; ++i)
	{
		j = i - 1;
		selected = arr[i];

		// find location where selected should be inseretd
		loc = binarySearch(arr, selected, 0, j);

		// Move all elements after location to create space
		while (j >= loc)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = selected;
	}
}

