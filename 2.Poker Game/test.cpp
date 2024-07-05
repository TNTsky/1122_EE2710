#include<iostream>
#include<vector>
using namespace std;

void SelectionSort(vector<int> &arr, int size)
{
	int p;
	int tmd;
	for (int i = 0; i < size; i++)
	{
		p = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[p]) { p = j; }
		}
		tmd = arr[i];
		arr[i] = arr[p];
		arr[p] = tmd;
	}

	return;
}


/*
int main()
{
	vector<int> arr = { 5, 4, 3, 2, 1 };

	SelectionSort(arr, arr.size());

	for (int i = 0, n = arr.size(); i < n; i++)
	{
		cout << arr[i] << ' ';
	}
}
*/