#include "records.h"
#define SWAP(a,b) {RECORD tmp; tmp = a; a = b; b = tmp;}

void min_adjust(RECORD records[], int i, int j) {
	int child, rootkey;
	RECORD tmp;
	tmp = records[i];
	rootkey = records[i].key;
	child = 2 * i + 1;

	while (child <= j) {
		if (child < j && (records[child].key > records[child + 1].key))
			child++;
		if (rootkey < records[child].key)
			break;
		else {
			records[(child - 1) / 2] = records[child];
			child = 2 * child + 1;
		}
	}
	records[(child - 1) / 2] = tmp;
}

void max_adjust(RECORD records[], int i, int j) {
	int child, rootkey;
	RECORD tmp;
	tmp = records[i];
	rootkey = records[i].key;
	child = 2 * i + 1;

	while (child <= j) {
		if (child < j && (records[child].key < records[child + 1].key))
			child++;
		if (rootkey > records[child].key)
			break;
		else {
			records[(child - 1) / 2] = records[child];
			child = 2 * child + 1;
		}
	}
	records[(child - 1) / 2] = tmp;
}

void RECORDS::sort_records_insertion(int start_index, int end_index) {
	// Insertion sort
	for (int i = start_index + 1; i <= end_index; i++) {
		RECORD tmp = records[i];
		int j = i;
		while ((j > start_index) && (compare_keys((const void*)&tmp, (const void*)(&records[j - 1])) < 0)) {
			records[j] = records[j - 1];
			j--;
		}
		records[j] = tmp;
	}
}

void RECORDS::sort_records_heap(int start_index, int end_index) {
	// Classic heap sort
	for (int i = (end_index-1) / 2; i >= 0; i--)
		max_adjust(records, i, end_index);
	for (int i = end_index; i >= 0; i--) {
		SWAP(records[0], records[i]);
		max_adjust(records,0, i-1);
	}
}

void RECORDS::sort_records_weird(int start_index, int end_index) {
	// A weird sort with a make-heap operation followed by insertion sort
	for (int i = (end_index-1) / 2; i >= start_index; i--)
		min_adjust(records, i, end_index-1);

	sort_records_insertion(start_index, end_index);
}

void RECORDS::sort_records_quick_classic(int start_index, int end_index) {
	// Classic quick sort without any optimization techniques applied
	int pivot;

	if (start_index < end_index) {
		pivot = start_index;
		for (int i = start_index; i < end_index; i++) {
			if (compare_keys((const void*)(&records[i]), (const void*)(&records[end_index])) < 0) {
				SWAP(records[i], records[pivot]);
				pivot++;
			}
		}
		SWAP(records[end_index],records[pivot]);

		sort_records_quick_classic(start_index, pivot - 1);
		sort_records_quick_classic(pivot + 1,end_index);
	}
}


void RECORDS::sort_records_intro(int start_index, int end_index) {
	// Introsort described in https://en.wikipedia.org/wiki/Introsort
	int maxDepth = 2 * (log2(get_size()));

	auto introsort = [&](int n, int depth, int left, int right, auto& intro_sort_ref) -> void {
		if (n < 16) {
			sort_records_insertion(left, right);
		}
		else if(!depth){
			sort_records_heap(left, right);
		}
		else {
			int pivot = left;
			for (int i = left; i < right; i++) {
				if (compare_keys((const void*)(&records[i]), (const void*)(&records[right])) < 0) {
					SWAP(records[i], records[pivot]);
					pivot++;
				}
			}
			SWAP(records[right], records[pivot]);

			intro_sort_ref(pivot - left, depth - 1, left, pivot - 1, intro_sort_ref);
			intro_sort_ref(right - pivot, depth - 1, pivot + 1, right, intro_sort_ref);
		}
	};

	introsort(get_size(),maxDepth,start_index,end_index,introsort);
}


void merge(RECORD records[], int left, int right) {
	RECORD* list = new RECORD[right - left + 1];

	int mid = (left + right) / 2;
	int i = left;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= right) {
		if (records[i].key < records[j].key) {
			list[k++] = records[i++];
		}
		else {
			list[k++] = records[j++];
		}
	}

	while (i <= mid) {
		list[k++] = records[i++];
	}
	while (j <= right) {
		list[k++] = records[j++];
	}

	for (int l = left; l <= right; l++) {
		records[l] = list[l - left];
	}

	delete[] list;
}

void RECORDS::sort_records_merge_with_insertion(int start_index, int end_index) {
	// Merge sort optimized by insertion sort only
	if (end_index - start_index < 16) {
		sort_records_insertion(start_index, end_index);
		return;
	}

	if (start_index < end_index) {
		int mid = (start_index + end_index) / 2;
		sort_records_merge_with_insertion(start_index, mid);
		sort_records_merge_with_insertion(mid + 1, end_index);

		merge(records, start_index, end_index);
	}
}
