#include <stdio.h>
#include <stdlib.h>
#include "ucos_ii.h"

min_heap* createHeap(INT32U max_size) {

	if (max_size <= 0) {
		printf("size of heap must above 0\n");
		exit(1);
	}

	min_heap* heap = (min_heap*)malloc(sizeof(min_heap));
	heap->data = (heap_element*)malloc(max_size * sizeof(heap_element));

	if (!heap->data) {
		printf("no more space can malloc\n");
		exit(1);
	}

	heap->len = 0;
	heap->max_size = max_size;

	return heap;

}

void clearHeap(min_heap* heap) {

	if (heap->data != NULL) {
		free(heap->data);
		heap->len = 0;
		heap->max_size = 0;
	}

}

int isHeapEmpty(min_heap* heap) {

	if (heap->len == 0)
		return 1;
	else
		return 0;

}

void insertHeapElement(min_heap* heap, heap_element element) {
	
	if (heap->len == heap->max_size) {
		heap_element* tmp_p = realloc(heap->data, 2 * heap->max_size * sizeof(heap_element));
		if (!tmp_p) {
			printf("no more space to extend\n");
			exit(1);
		}
		else {
			heap->data = tmp_p;
			heap->max_size = 2 * heap->max_size;
		}
	}

	heap->data[heap->len] = element;
	heap->len++;
	int i = heap->len - 1;
	while (i != 0) {
		int j = (i - 1) / 2;
		if (element.value >= heap->data[j].value)
			break;
		heap->data[i] = heap->data[j];
		i = j;
	}
	heap->data[i] = element;

}

heap_element deleteMinElement(min_heap* heap) {

	if (heap->len == 0) {
		printf("heap is empty\n");
		exit(1);
	}

	heap_element root = heap->data[0];
	heap->len--;
	if (heap->len == 0)
		return root;

	heap_element tmp = heap->data[heap->len];
	int i = 0;
	int j = 2 * i + 1;
	while (j <= heap->len - 1) {
		if (j < heap->len - 1 && (heap->data[j].value > heap->data[j + 1].value))
			j++;
		if (tmp.value <= heap->data[j].value)
			break;
		else {
			heap->data[i] = heap->data[j];
			i = j;
			j = 2 * i + 1;
		}
	}
	heap->data[i] = tmp;

	return root;

}
