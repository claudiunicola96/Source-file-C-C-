/*
 * repository.c
 *
 *  Created on: Mar 7, 2016
 *      Author: claudiu
 */

#include <src/repository/repository.h>
#include <src/util/constants.h>
#include <src/util/dynamicVector.h>
#include <stdlib.h>
#include <string.h>

/**
 * Constructor
 * fileName - char
 */
Repository* initRepository(char* fileName) {
	Repository* repo = (Repository*) malloc(sizeof(Repository));
	repo->fileName = (char*) malloc(sizeof(char) * strlen(fileName) + 1);
	strcpy(repo->fileName, fileName);
	repo->vector = initDynamicVector(50);
	repo->vector = loadFile(repo);
	return repo;
}

/**
 * Add an expense to vector.
 * repo - Repository
 * item - Expense
 */
void addItem(Repository* repo, Expense* item) {
	add(repo->vector, item);
}

/**
 * Get the last id from vector.
 * repo - Repository
 */
int getLastId(Repository* repo) {
	int id = 0;
	int i = 0;
	Expense* item;
	for (i = 0; i < getSize(repo->vector); i++) {
		item = findByPosition(repo->vector, i);
		if (item->id > id)
			id = item->id;
	}
	return id + 1;
}

/**
 * Read a line from a file and split after Expense fields (id, day, money, type)
 * file - FILE
 */
Expense* readLine(FILE* file) {
	Expense* item;
	char* line, *token;
	int id;
	int day;
	float money;
	line = (char*) malloc(sizeof(char) * LINE_LENGTH);
	if (fgets(line, LINE_LENGTH, file) == NULL) {
		item = NULL;
		return item;
	}
	token = strtok(line, "#");
	id = atoi(token);
	token = strtok(NULL, "#");
	day = atoi(token);
	token = strtok(NULL, "#");
	money = atof(token);
	token = strtok(NULL, "\n");
	item = initExpense(id, day, money, token);
	return item;
}

/**
 * Read the vector from file
 * repo - Repository
 */
DynamicVector* loadFile(Repository* repo) {
	Expense* item;
	FILE* file;
	file = fopen(repo->fileName, "r");
	while (1) {
		item = readLine(file);
		if (item)
			add(repo->vector, (Item*) item);
		else
			break;
	}
	fclose(file);
	return repo->vector;
}

/**
 * Write a line in file
 * file - FILE
 * item - Expense
 */
void writeLine(FILE* file, Expense* item) {
	fprintf(file, "%d#%d#%f#%s\n", item->id, item->day, item->money,
			item->type);
}

/**
 * Write the vector in file
 * repo - Repository
 */
void writeFile(Repository* repo) {
	FILE* file;
	file = fopen(repo->fileName, "w");
	int i = 0;
	for (i = 0; i < getSize(repo->vector); i++) {
		writeLine(file, findByPosition(repo->vector, i));
	}
	fclose(file);
}

/**
 * Delete an expense from vector
 * repo - Repository
 * item - Expense
 */
void deleteItem(Repository* repo, Expense* item) {
	delete(repo->vector, item);
}

/**
 * Deallocate the repository
 * repo - Repository
 */
void freeRepository(Repository* repo) {
	free(repo->fileName);
	destroyDynamicVector(repo->vector);
	free(repo);
}
