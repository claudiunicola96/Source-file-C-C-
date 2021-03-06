/*
 * ui.c
 *
 *  Created on: Mar 7, 2016
 *      Author: claudiu
 */

#include <src/controller/controller.h>
#include <src/domain/expense.h>
#include <src/domain/validator.h>
#include <src/repository/repository.h>
#include <src/util/constants.h>
#include <src/util/dynamicVector.h>
#include <stdio.h>
#include <string.h>

/**
 * Put the menu in console
 */
void printMenu() {
	puts("1.Adauga cheltuiala.");
	puts("2.Afisare cheltuieli.");
	puts("3.Sterge cheltuiala.");
	puts("4.Modifica cheltuiala.");
	puts("5.Filtrare");
	puts("6.Sortare");
	puts("7.Undo");
	puts("0.Iesire.\n");
	puts("Dati o comanda: ");
}

/**
 * Get the command from user.
 * Return an integer
 */
int getCommand() {
	int cmd = 0;
	scanf("%d", &cmd);
	return cmd;
}

/**
 * The add command get from console the properties
 * of expense
 * ctrl - Controller
 */
void addCommand(Controller* ctrl) {
	int day = 1;
	float money = 0;
	char type[20];
	puts("Adauga cheltuiala:");
	puts("Introdu ziua(1-31):");
	scanf("%d", &day);
	puts("Introdu suma:");
	scanf("%f", &money);
	puts("Introdu tipul*:");
	puts("*Tipul poate fi: mancare, transport, "
			"telefon&internet,imbracaminte,altele");
	scanf("%s", type);
	addAction(ctrl, day, money, type);
	if (getErrorsNumber(ctrl->valid) > 0) {
		int i = 0;
		for (i = 1; i <= getErrorsNumber(ctrl->valid); i++) {
			puts(ctrl->valid[i]);
		}
//		freeErrors(ctrl->valid);
	} else
		puts(SUCCES_MSG);
}

/**
 * Show the expenses
 * ctrl - Controller
 */
void showCommand(Controller* ctrl) {
	DynamicVector* vector = getAllAction(ctrl);
	printDynamicVector(vector);
}

/**
 * The delete command remove from container an expense
 * ctrl - Controller
 */
void deleteCommand(Controller* ctrl) {
	int id = 0;
	puts("Sterge cheltuiala");
	puts("Introdu id-ul cheltuieli: ");
	scanf("%d", &id);
	int ok = deleteAction(ctrl, id);
	if (ok > -1)
		puts(SUCCES_MSG);
	else
		puts("Id-ul nu exista.");
}

/**
 * The update command read an id, show the expense (if exist)
 * and leave user to change the expense fields
 * ctrl - Controller
 */
void updateCommand(Controller* ctrl) {
	int id = 0;
	puts("Modifica cheltuiala");
	puts("Introdu id-ul cheltuieli: ");
	scanf("%d", &id);
	int position = searchId(ctrl, id);
	if (position > -1) {
		int day = 1;
		float money = 0;
		char type[20];
		puts("Introdu ziua(1-31):");
		scanf("%d", &day);
		puts("Introdu suma:");
		scanf("%f", &money);
		puts("Introdu tipul*:");
		puts("*Tipul poate fi: mancare, transport, "
				"telefon&internet,imbracaminte,altele");
		scanf("%s", type);
		updateAction(ctrl, id, position, day, money, type);
		if (getErrorsNumber(ctrl->valid) > 0) {
			int i = 0;
			for (i = 1; i < getErrorsNumber(ctrl->valid); i++) {
				puts(ctrl->valid[i]);
			}
//			freeErrors(ctrl->valid);
		} else
			puts(SUCCES_MSG);
	} else
		puts("Id-ul nu exista.");

}

/**
 * Filter the vector by a property
 * ctrl - Controller
 */
void filterCommand(Controller* ctrl) {
	char property[4];
	puts("Cheluieliile pot fi filtrare dupa: suma, zi, tip");
	puts("Alege dupa ce doresti sa fie filtrate datele: ");
	scanf("%s", property);
	while (1) {
		if (strcmp(property, FILTER_BY_MONEY) == 0) {
			float money = 0;
			puts("Introdu suma: ");
			scanf("%f", &money);
			printDynamicVector(filterByMoney(ctrl, money));
			break;
		} else if (strcmp(property, FILTER_BY_DAY) == 0) {
			int day = 0;
			puts("Introdu ziua: ");
			scanf("%d", &day);
			printDynamicVector(filterByDay(ctrl, day));
			break;
		} else if (strcmp(property, FILTER_BY_TYPE) == 0) {
			char type[20];
			puts("Introdu tipul(mancare, transport, "
					"telefon&internet,imbracaminte,altele): ");
			scanf("%s", type);
			printDynamicVector(filterByType(ctrl, type));
			break;
		} else {
			puts("Acest criteriu nu este valid!");
			break;
		}
	}
}

/**
 * Sort the vector by property asc and desc
 * ctrl - Controller
 */
void sortCommand(Controller* ctrl) {
	char property[4];
	char order[4];
	//TODO: user-ul sa aleaga ordinea asc/desc
	puts("Cheltuieliile pot fi sortate dupa: suma, tip");
	puts("Alege dupa ce doresti sa fie sortate datele: ");
	scanf("%s", property);
	while (1) {
		if (strcmp(property, SORT_BY_MONEY) == 0) {
			puts("Alege ordinea in care doresti sa fie sortate "
					"datele: crescator(asc), descrescator(desc)");
			scanf("%s", order);
			printDynamicVector(sortByMoney(ctrl, order));
			break;
		} else if (strcmp(property, SORT_BY_TYPE) == 0) {
			puts("Alege ordinea in care doresti sa fie sortate "
					"datele: crescator(asc), descrescator(desc)");
			scanf("%s", order);
			printDynamicVector(sortByType(ctrl, order));
			break;
		} else {
			puts("Acest criteriu nu este valid!");
			break;
		}
	}
}

/**
 * Undo the last operation
 * ctrl - Controller
 */
void undoCommand(Controller* ctrl) {
	undo(ctrl);
}

/**
 * Deallocate the memory from controller struct.
 * ctrl - Controller
 */
void destroyAll(Controller* ctrl) {
	freeRepository(ctrl->repo);
	freeController(ctrl);
}

/**
 * The start of application
 * ctrl - Controller
 */
void runUi(Controller* ctrl) {
	puts("Bine ati venit!\n");
	int cmd = 0;
	while (1) {
		printMenu();
		cmd = getCommand();
		switch (cmd) {
		case 1:
			addCommand(ctrl);
			break;
		case 2:
			showCommand(ctrl);
			break;
		case 3:
			deleteCommand(ctrl);
			break;
		case 4:
			updateCommand(ctrl);
			break;
		case 5:
			filterCommand(ctrl);
			break;
		case 6:
			sortCommand(ctrl);
			break;
		case 7:
			undoCommand(ctrl);
			break;
		case 0:
			writeAll(ctrl);
			puts("\nLa revedere!!!");
			return;
		default:
			puts("Comanda nerecunoscuta.");
			break;
		}
	}
}
