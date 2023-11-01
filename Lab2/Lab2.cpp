#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "Sorts.h"

using namespace std;

template <class Function>
auto time_decorate_function(Function&& func) {
	return [&](auto && ...args) {
		auto start = std::chrono::steady_clock::now();
		std::invoke(std::forward<Function>(func), args...);
		auto end = std::chrono::steady_clock::now();
		return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	};
}

void do_records(int max_n, int step, std::initializer_list<void (*)(std::vector<int>&, std::function<int(int, int)>)> sort_functions, const string& path_to_file) {
	std::ofstream out(path_to_file, std::ios::app);
	if (!out.is_open()) {
		throw "failed to open file";
	}

	std::vector<int> sequence;
	sequence.reserve(max_n);
	auto cmp = [](int a, int b) { return a - b; };
	int time = 0;
	for (auto sort_function : sort_functions) {
		auto decorated = time_decorate_function(sort_function);
		if (sort_function == Bubble<int>) {
			out << "Bubble" << endl;
		}
		else if (sort_function == InsertionSort<int>) {
			out << "InsertionSort" << endl;
		}
		else if (sort_function == MergeSort<int>) {
			out << "MergeSort" << endl;
		}
		else if (sort_function == QuickSort<int>) {
			out << "QuickSort" << endl;
		}
		else {
			out << "Unknown function" << endl;
		}
		for (int n = 0; n < max_n; n += step) {
			sequence.resize(n);
			for (int i = 0; i < n; ++i) {
				sequence[i] = rand();
			}
			time = decorated(sequence, cmp);
			out << time << ' ';
		}
		out << endl;
	}
	out.close();
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	string path_to_file = "D:\\Junk\\records.txt";
	std::ofstream outputFile(path_to_file, std::ios::out | std::ios::trunc);
	if (!outputFile.is_open()) {
		throw "failed to open file";
	}
	outputFile.close();
	do_records(1e4, 1000, { Bubble<int>, InsertionSort<int> }, path_to_file);
	do_records(1e5, 1000, { MergeSort<int>, QuickSort<int> }, path_to_file);
}