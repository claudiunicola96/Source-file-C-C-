/*
 * expense.h
 *
 *  Created on: Mar 7, 2016
 *      Author: claudiu
 */

#ifndef DOMAIN_EXPENSE_H_
#define DOMAIN_EXPENSE_H_

typedef struct {
	int id;
	int day;
	float money;
	char* type;
} Expense;

/**
 * Construct
 * id - int
 * day - int
 * money - float
 * type - char*
 */
Expense* initExpense(int id, int day, float money, char* type);

/**
 * Get the money
 * item - Expense
 */
float getMoney(Expense* item);

/**
 * Get the type
 * item - Expense
 */
char* getType(Expense* item);

/**
 * Destructor
 * item - Expense
 */
void destroyExpense(Expense* item);
#endif /* DOMAIN_EXPENSE_H_ */
