/*
 * dynamicVector.c
 *
 *  Created on: Mar 7, 2016
 *      Author: claudiu
 */

#include <src/domain/expense.h>
#include <src/util/dynamicVector.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Initializes an empty array.
 * capacity - integer
 */
DynamicVector* initDynamicVector(int capacity) {
	DynamicVector* vector = (DynamicVector*) malloc(
			sizeof(DynamicVector) * capacity);
	vector->size = 0;
	vector->capacity = capacity;
	vector->items = (Item*) malloc(sizeof(Item) * vector->capacity);

	return vector;
}

/**
 * If necessary double the allocated memory.
 * Step1: Allocate new memory
 * Step2: Copy items in new memory
 * Step3: Deallocate the memory and pointing to the new location of items in heap
 * vector - DynamicVector
 */
void vectorDoubleCapacity(DynamicVector* vector) {
	vector->capacity *= 2;
	Item* newItems = (Item*) malloc(sizeof(Item) * vector->capacity);
	int i = 0;
	for (i = 0; i < vector->size; i++)
		newItems[i] = vector->items[i];
	free(vector->items);
	vector->items = newItems;
}

/**
 * Add an item in DynamicVector.
 * vector - DynamicVector
 * item - Item
 */
void add(DynamicVector* vector, Item item) {
	if (vector->capacity == vector->size) {
		vectorDoubleCapacity(vector);
	}
	vector->items[vector->size] = item;
	vector->size++;
}

/**
 * Delete an item from DynamicVector.
 * vector - DynamicVector
 * item - Item
 */
void delete(DynamicVector* vector, Item item) {
	int i = 0;
	for (i = 0; i < vector->size; i++) {
		if (vector->items[i] == item) {
			vector->items[i] = vector->items[vector->size - 1];
			vector->size--;
		}
	}
}

/**
 * Return the size of DynamicVector.
 * vector - DynamicVector
 */
int getSize(DynamicVector* vector) {
	return vector->size;
}

Item findByPosition(DynamicVector* vector, int position) {
	return vector->items[position];
}

/**
 * Print the items of vector
 * vector - DynamicVector
 */
void printDynamicVector(DynamicVector* vector) {
	Expense* item;
	int i = 0;
	for (i = 0; i < getSize(vector); i++) {
		item = findByPosition(vector, i);
		printf("%4d %4d %8f %8s\n", item->id, item->day, item->money,
				item->type);
	}
}

/**
 * Get the last item of vector
 */
Item getLastItem(DynamicVector* vector) {
	return vector->items[vector->size - 1];
}

/**
 * Copy the dynamic vector
 * sourceVector - DynamicVector
 */
DynamicVector* copyDynamicVector(DynamicVector* sourceVector) {
	DynamicVector* destinationVector = initDynamicVector(sourceVector->capacity);
	int i;
	for (i = 0; i < getSize(sourceVector); i++) {
		add(destinationVector, sourceVector->items[i]);
	}
	return destinationVector;
}

/**
 * Destroy an item
 * vector - DynamicVector
 * position - integer
 */
void destroyByPosition(DynamicVector* vector, int position) {
	free(vector->items[position]);
}

/**
 * Memory free.
 * vector - DynamicVector
 */
void destroyDynamicVector(DynamicVector* vector) {
	int i = 0;
	for (i = 0; i < getSize(vector); i++)
		free(vector->items[i]);
}
