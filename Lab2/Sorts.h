#pragma once
#include "ISequence.h"
#include <functional>
#include <iostream>

template <class T>
std::pair<int, int> Partition(ISequence<T>& a, int l, int r, std::function<int(T, T)> comparator) {
	auto m1 = rand() % (r - l + 1) + l;
	std::swap(a[l], a[m1]);
	m1 = l;
	auto m2 = m1;
	for (auto i = l + 1; i <= r; ++i) {
		if (comparator(a[m1], a[i]) == 0) {
			++m2;
			std::swap(a[i], a[m2]);
		}
		else if (comparator(a[m1], a[i]) > 0) {
			std::swap(a[i], a[m1]);
			++m1;
			++m2;
			std::swap(a[i], a[m2]);
		}
	}
	return { m1, m2 };
}

template <class T>
void QuickSortSegment(ISequence<T>& a, std::function<int(T, T)> comparator, int l, int r) {
	while (l < r) {
		std::pair<int, int> p = Partition(a, l, r, comparator);
		auto m1 = p.first, m2 = p.second;
		if (m1 - l < r - m2) {
			QuickSortSegment(a, comparator, l, m1 - 1);
			l = m2 + 1;
		}
		else {
			QuickSortSegment(a, comparator, m2 + 1, r);
			r = m1 - 1;
		}
	}
}

template <class T>
void QuickSort(ISequence<T>& a, std::function<int(T, T)> comparator) {
	QuickSortSegment(a, comparator, 0, a.get_length() - 1);
}

template <class T>
void Merge(ISequence<T>& sequence, int l, int r, std::function<int(T, T)> comparator) {
	int i = l;
	int m = l + (r - l) / 2;
	int j = m;
	ISequence<T>& tmp = sequence.get_sub_sequence(0, r - l);
	int current_index = 0;

	while (i < m && j < r) {
		if (comparator(sequence[i], sequence[j]) <= 0) {
			tmp[current_index] = sequence[i];
			++i;
		}
		else {
			tmp[current_index] = sequence[j];
			++j;
		}
		++current_index;
	}

	while (i < m) {
		tmp[current_index] = sequence[i];
		++i;
		++current_index;
	}
	while (j < r) {
		tmp[current_index] = sequence[j];
		++j;
		++current_index;
	}

	for (int i = l; i < r; ++i) {
		sequence[i] = tmp[i - l];
	}
}

template <class T>
void MergeSortSegment(ISequence<T>& a, std::function<int(T, T)> comparator, int l, int r) {
	if (l >= r - 1) {
		return;
	}
	int m = (r - l) / 2 + l;
	int i = l, j = m;
	MergeSortSegment(a, comparator, l, m);
	MergeSortSegment(a, comparator, m, r);
	Merge(a, l, r, comparator);
}

template <class T>
void MergeSort(ISequence<T>& a, std::function<int(T, T)> comparator) {
	MergeSortSegment(a, comparator, 0, a.get_length());
}

template <class T>
void InsertionSort(ISequence<T>& sequence, std::function<int(T, T)> comparator) {
	int n = sequence.get_length();
	for (int i = 1; i < n; ++i) {
		int key = sequence[i];
		int j = i - 1;

		while (j >= 0 && comparator(sequence[j], key) > 0) {
			sequence[j + 1] = sequence[j];
			--j;
		}
		sequence[j + 1] = key;
	}
}

template <class T>
void Bubble(ISequence<T>& sequence, std::function<int(T, T)> comparator) {
	int n = sequence.get_length();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n - i - 1; ++j) {
			if (comparator(sequence[j], sequence[j + 1]) > 0) {
				std::swap(sequence[j], sequence[j + 1]);
			}
		}
	}
}
