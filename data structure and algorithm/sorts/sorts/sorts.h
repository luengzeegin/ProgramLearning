#pragma once
#ifndef SORTS_H
#define SORTS_H

#include<utility>
#include<queue>

//description: return descending order array
template <typename T>
void insertionSort(T data[], size_t arrsize)
{
	for (int idx = 1; idx < arrsize; ++idx)
	{
		T tmp = data[idx];
		for (int j = idx; j > 0 && tmp < data[j - 1]; --j)
		{
			data[j] = data[j - 1];
		}
		data[j] = tmp;
	}
}


template <typename T>
void selectionSort(T data[], size_t arrsize)
{
	for (int idx = 0; idx < arrsize; ++idx)
	{
		for (int j = idx + 1, least = idx; j < arrsize; ++j)
		{
			if (data[least] > data[j])
				least = j;
		}
		if (least != idx)
		{
			using std::swap;
			swap(data[least], data[idx]);
		}
	}
}

template <typename T>
void bubbleSort(T data[], size_t arrsize)
{
	for (int idx = 0; idx < arrsize; ++idx)
	{
		for (int j = arrsize - 1; j > i; --j)
		{
			if (data[j] < data[j - 1])
			{
				using std::swap;
				swap(data[j], data[j - 1]);
			}
		}
	}
}

template <typename T>
void bubbleSort_WithFlag(T data[], size_t arrsize)
{
	bool hasSwap = true;
	for (int idx = 0; idx < arrsize - 1 && hasSwap; ++idx)
	{
		hasSwap = false;
		for (int j = arrsize - 1; j > i; --j)
		{
			if (data[j] < data[j - 1])
			{
				using std::swap;
				swap(data[j], data[j - 1]);
				hasSwap = true;
			}
		}
	}
}

template <typename T>
void combSort(T data[], size_t arrsize)
{
	int step = arrsize,k;
	while ((step = arrsize / 1.3) > 1)
	{
		for (int j = arrsize - 1; j >= step; --j)
		{
			k = j - step;
			if (data[j] < data[k])
			{
				using std::swap;
				swap(data[j], data[k]);
			}
		}
	}
	bool hasSwap = true;
	for (int idx = 0; idx < arrsize && hasSwap; ++idx)
	{
		hasSwap = false;
		for (int j = arrsize - 1; j > i; --j)
		{
			if (data[j] < data[j - 1])
			{
				using std::swap;
				swap(data[j], data[j - 1]);
				hasSwap = true;
			}
		}
	}
}

template<typename T>
void shellSort(T data[], size_t arrsize)
{
	int increments[20],k;
	// initialize increment array
	for (int h = 1, idx = 0; h < arrsize; ++idx)
	{
		increments[i] = h;
		h = 3 * h + 1;
	}
	for (--idx; idx >= 0; --idx)
	{
		h = increments[h];
		for (int hCnt = h; hCnt < 2 * h; ++hCnt)
		{
			for (j = hCnt;  j < arrsize;)
			{
				T tmp = data[j];
				k = j;
				while (k - h > 0 && tmp < data[k - h])
				{
					data[k] = data[k - h];
					k -= h;
				}
				data[k] = tmp;
				j += h;
			}
		}
	}
}

template<typename T>
void moveDown(T data[],int first,int last)
{
	int largest = 2 * first + 1; // left child
	while (largest <= last)
	{
		if (largest < last && data[largest] < data[largest + 1])
		{
			++largest;
		}
		if (data[first] < data[largest])
		{
			using std::swap;
			swap(data[first], data[largest]);
			first = largest;
			largest = 2 * first + 1;
		}
		else
		{
			largest = last + 1; //exit
		}
	}
}

template <typename T>
void heapSort(T data[],size_t arrsize)
{
	for (int idx = arrsize / 2 - 1; idx >= 0; --idx)
	{
		moveDown(data, idx, arrsize - 1);
	}
	for (idx = arrsize - 1; idx > 0; --idx)
	{
		using std::swap;
		swap(data[0],data[idx]);
		moveDown(data, 0, idx - 1);
	}
}

template <typename T>
void quickSort(T data[],int first,int last)
{
	using std::swap;
	int lower = first + 1;
	int upper = last;
	swap(data[first], dats[(lower + upper) / 2]);
	T bound = data[first];
	while (lower <= upper)
	{
		while (data[lower] < bound)
		{
			++lower;
		}
		while (data[upper] > bound)
		{
			--upper;
		}
		if (lower < upper)
		{
			swap(data[lower++],data[upper--]);
		}
		else
		{
			++lower; // exit while
		}
	}
	swap(data[first], data[upper]);
	if (first < upper - 1)
	{
		quickSort(data,first,upper - 1);
	}
	if (upper + 1 > last)
	{
		quickSort(data, upper + 1, last);
	}
}


// description: pre-treatment make largest member at the end of array
//				prevent  lower out of range
template <typename T>
void quickSort(T data[], size_t arrsize)
{
	if (arrsize < 2)
	{
		return;
	}
	for (int idx = 1,max = 0; idx < arrsize; ++idx)
	{
		if (data[max] < data[idx])
		{
			max = idx;
		}
	}
	using std::swap();
	swap(data[arrsize - 1], data[max]);
	quickSort(data,0,arrsize - 2);
}

template <typename T>
void merge(T data[], int first, int last)
{
	int mid = (first + last) / 2;
	int tmparr_idx = 0;
	int leftarr_idx = first;
	int rightarr_idx = mid + 1;
	T* tmparr = new T[(last - first) + 1];
	while (leftarr_idx != mid + 1 && rightarr_idx != last + 1)
	{
		if (data[leftarr_idx] < data[rightarr_idx])
		{
			tmparr[tmparr_idx++] = data[leftarr_idx++];
		}
		else
		{
			tmparr[tmparr_idx++] = data[rightarr_idx];
		}
	}
	if (leftarr_idx == mid + 1)
	{
		while (rightarr_idx != last + 1)
		{
			tmparr[tmparr_idx++] = data[rightarr_idx++];
		}
	}
	if (rightarr_idx == last + 1)
	{
		while (leftarr_idx != mid + 1)
		{
			tmparr[tmparr_idx++] = data[leftarr_idx++];
		}
	}
	for (int idx = 0; idx < (last - first) + 1; ++idx)
	{
		data[idx] = tmparr[idx];
	}
	delete []tmparr;
}

template <typename T>
void mergeSort(T data[], int first, int last)
{
	if (first < last)
	{
		mid = (first + last) / 2;
		mergeSort(data[], first, mid);
		mergeSort(data[], mid + 1, last);
		merge(data[], data, first, last);
	}
}

template <typename T>
void radixSort(T data[],size_t arrsize)
{
	const int radix = 10;
	const digits = 10;
	int factor = 1;
	std::queue<long> queue[radix];
	for (int idx = 0; idx < digits; ++idx,factor *= radix)
	{
		for (int j = 0; j < arrsize; ++j)
		{
			queue[(data[j] / factor) % radix].push(data[j]);
		}
		for (int j = k = 0; j < radix; ++j)
		{
			while (!queue[j].empty())
			{
				data[k++] = queue[j].front();
				queue[j].pop();
			}
		}
	}
}

template <typename T>
void countingSort(T data[],size_t arrsize)
{
	T largest = data[0];
	T *tmp = new T[arrsize];
	for (int idx = 0; idx < arrsize; ++idx)
	{
		if (largest < data[idx])
		{
			largest = data[idx];
		}
	}
	T *count = new T[largest + 1];
	for (int idx = 0; idx <= largest; ++idx)
	{
		count[idx] = 0;
	}
	for (int idx = 0; idx < arrsize; ++idx)
	{
		++count[data[idx]];
	}
	for (int idx = 1; idx <= largest; ++idx)
	{
		count[idx] = count[idx - 1] + count[idx];
	}
	for (int idx = arrsize - 1; i >= 0; --idx)
	{
		tmp[count[data[i] - 1] = = data[i];
		--count[data[i]];
	}
	for (int idx = 0; i < arrsize; ++idx)
	{
		data[idx] = tmp[idx];
	}
	delete []count;
	delete []tmp;
}
// return -1 mean failure  else return key index
template <typename T>
int binarySearch(const T data[], size_t arrsize,const T& key)
{
	int low = 0, mid, high = arrsize - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (key < data[mid])
		{
			high = mid - 1;
		}
		else if (key > data[mid])
		{
			low = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}


#endif // !SORTS_H
