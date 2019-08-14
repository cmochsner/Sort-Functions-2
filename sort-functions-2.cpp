#include <iostream>
#include <time.h>
#include <chrono>

using namespace std::chrono;
using namespace std;

//for testing
void print(int *arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}
int partition(int *arr, int low, int high)
{
	int pivot = arr[high];  
	int i = (low - 1); 

	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j] <= pivot)
		{
			i++;  
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	int temp = arr[i + 1];
	arr[i + 1] = arr[high];
	arr[high] = temp;

	return (i + 1);
}
void merge(int *arr, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	int *L = new int[n1]; 
	int *R= new int[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];
	i = 0; 
	j = 0; 
	k = l; 
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}

	delete[] R;
	delete[] L;
}
void mergeSort(int *arr, int l, int r)
{
	if (l < r)
	{
		int m = (l + r-1) / 2;

		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

void quick(int *arr, int l, int h)
{
		if (l < h)
		{
			int p = partition(arr, l, h);

			quick(arr, l, p - 1);
			quick(arr, p + 1, h);
		}
}
void heapify(int *arr, int n, int i)
{
	int largest = i; 
	int l = 2 * i + 1; 
	int r = 2 * i + 2; 

	if (l < n && arr[l] > arr[largest])
		largest = l;

	if (r < n && arr[r] > arr[largest])
		largest = r;

	if (largest != i)
	{
		int temp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = temp;

		heapify(arr, n, largest);
	}
}
void heap(int *arr, int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	for (int i = n - 1; i >= 0; i--)
	{
		int temp = arr[i];
		arr[i] = arr[0];
		arr[0] = temp;
		heapify(arr, i, 0);
	}
}

int main()
{
	int n=0;

	cout << "Welcome to the merge, quick, and heap sort timer program! Enter -1 to exit." << endl;

	while (n != -1)
	{
		cout << "\nEnter the size of the array you'd like to sort: ";
		cin >> n;
		cout << endl;

		if (n < 0)
		{
			while (n < -1)
			{
				cout << "Invalid array size. Try again." << endl;
				cin >> n;
				cout << endl;
			}
			if (n == -1)
			{
				cout << "Exiting..." << endl;
				return 0;
			}
		}

		int *arr = new int[n];
		int *arr2 = new int[n];
		int *arr3 = new int[n];

		for (int i = 0; i < n; i++)
		{
			arr[i] = rand() % 100;
			arr2[i] = arr[i];
			arr3[i] = arr[i];
		}

		high_resolution_clock::time_point start = high_resolution_clock::now();
		mergeSort(arr, 0, n - 1);
		cout << "Merge Sort...." << endl;
		high_resolution_clock::time_point stop = high_resolution_clock::now();
		duration<double> mergeTime = duration_cast<duration<double>>(stop - start);
		
		high_resolution_clock::time_point start2 = high_resolution_clock::now();
		quick(arr2, 0, n - 1);
		cout << "Quick Sort..." << endl;
		high_resolution_clock::time_point stop2 = high_resolution_clock::now();
		duration<double> quickTime = duration_cast<duration<double>>(stop2 - start2);

		high_resolution_clock::time_point start3 = high_resolution_clock::now();
		heap(arr3, n);
		cout << "Heap Sort..." << endl;
		high_resolution_clock::time_point stop3 = high_resolution_clock::now();
		duration<double> heapTime = duration_cast<duration<double>>(stop3 - start3);

		cout << "\nAll done! ";
		if (heapTime.count() < mergeTime.count() && heapTime.count() < quickTime.count())
		{
			cout << "Heap Sort was the fastest!" << endl;
		}
		else if (mergeTime.count() < heapTime.count() && mergeTime.count() < quickTime.count())
		{
			cout << "Merge Sort was the fastest!" << endl;
		}
		else
		{
			cout << "Quick Sort was the fastest!" << endl;
		}

		cout << "\nRuntime for Merge Sort was " << mergeTime.count() << " seconds." << endl;
		cout << "Runtime for Quick Sort was " << quickTime.count() << " seconds." << endl;
		cout << "Runtime for Heap Sort was " << heapTime.count() << " seconds." << endl;

		delete[] arr;
		delete[] arr2;
		delete[] arr3;
	}

	//system("pause");
	return 0;
}