#include "pch.h"
#include "..//Lab2/Sorts.h"
#include <iostream>
#include "..//Lab2//ArraySequence.h"

void test(int max_n, int step, std::initializer_list<void (*)(ISequence<int>&, std::function<int(int, int)>)> sort_functions) {
	ISequence<int>& sequence = *(new ArraySequence<int>());
	sequence.reserve(max_n);
	auto cmp = [](int a, int b) { return a - b; };
	for (int n = 0; n < max_n; n += step) {
		sequence.resize(n);
		for (auto sort_function : sort_functions) {
			for (int i = 0; i < n; ++i) {
				sequence[i] = rand();
			}
			sort_function(sequence, cmp);
			for (int i = 0; i < n - 1; ++i) {
				EXPECT_TRUE(cmp(sequence[i], sequence[i + 1]) <= 0);
			}
		}
	}
}

TEST(N2, N2) {
	test(1e4, 1000, { Bubble<int>, InsertionSort<int> });
}

TEST(NLogN, NLogN) {
	test(1e5, 1000, { MergeSort<int>, QuickSort<int> });
}