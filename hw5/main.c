/* CS261- Assignment 5
 * Name: Li, Tingzhi & Zhang, Chunyang
 * Date: 5/22/2015
 * Development Environment: Xcode & MSVC
 * Solution description: To-do list application. This main function controls the interactions between the user and the program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"


int main(int argc, const char * argv[])
{
	char cmd = ' ';
	DynArr* mainList = createDynArr(10);
    FILE *inputFile;
    FILE *outputFile;

	printf("\n\n** TO-DO LIST APPLICATION **\n\n");
	do{
		printf("Press:\n"
			"'l' to load to-do list from a file\n"
			"'s' to save to-do list to a file\n"
			"'a' to add a new task\n"
			"'g' to get the first task\n"
			"'r' to remove the first task\n"
			"'p' to print the list\n"
			"'e' to exit the program\n"
			);
		/* get input command (from the keyboard) */
		cmd = getchar();
		/* clear the trailing newline character */
		while (getchar() != '\n');

		/* Fixme:  Your logic goes here! */
		if (cmd == 'l') {
			char load[30];
			printf("Please enter the filename: ");
			fgets(load, 30, stdin);
			char *nlptr;
			/* remove trailing newline character */
			nlptr = strchr(load, '\n');
			if (nlptr)
				*nlptr = '\0';
			inputFile = fopen(load, "r");
			if (inputFile == NULL)
				printf("Can't open the file! Please double check!\n\n");
			if (inputFile != NULL) {
				loadList(mainList, inputFile);
                fclose(inputFile);
				printf("The list has been loaded from file successfully.\n\n");
			}
		}
		else if (cmd == 's') {
            char save[30];
            printf("Please enter the file name: ");
            fgets(save, 30, stdin);
            char *nlptr;
            /* remove trailing newline character */
            nlptr = strchr(save, '\n');
            if (nlptr)
                *nlptr = '\0';

            outputFile = fopen(save, "w");
            if (outputFile != NULL){
                saveList(mainList, outputFile);
                fclose(outputFile);
                printf("The list has been saved into the file successfully.\n\n");
            }
            if (outputFile == NULL)
                printf("This file could not be saved!\n\n");
		}
		else if (cmd == 'a') {
            char desc[TASK_DESC_SIZE];
            int prio;
            
			printf("Please enter the task description: ");
			fgets(desc, TASK_DESC_SIZE, stdin);
			char *nlptr;
			/* remove trailing newline character */
			nlptr = strchr(desc, '\n');
			if (nlptr)
				*nlptr = '\0';
			printf("Please enter the task priority (0-999): ");
			setbuf(stdin, NULL);
			scanf("%d", &prio);
			setbuf(stdin, NULL);
			addHeap(mainList, createTask(prio, desc), compare);
			printf("The task '%s' has been added to your to-do list.\n\n", desc);
		}
		else if (cmd == 'g') {
			if (isEmptyDynArr(mainList)) {
				printf("Your to-do list is empty.\n\n");
			}
			else {
				TaskP temp = (TaskP)getMinHeap(mainList);
				printf("Your first task is '%s'.\n\n", temp->description);
			}
		}
		else if (cmd == 'r') {
			if (isEmptyDynArr(mainList)) {
				printf("Your to-do list is empty!\n\n");
			}
			else {
				TaskP temp = (TaskP)getMinHeap(mainList);
				printf("Your first task '%s' has been removed from the list.\n\n", temp->description);
				free(temp);
				removeMinHeap(mainList, compare);
			}
		}
		else if (cmd == 'p') {
			if (isEmptyDynArr(mainList)) {
				printf("Your to-do list is empty! There is nothing to print!\n\n");
			}
			else
				printList(mainList);
		}
		else if (cmd != 'e')
			printf("Wrong command, please choose again!\n\n");
		/* Note: We have provided functions called printList(), saveList() and loadList() for you
		to use.  They can be found in toDoList.c */
	} while (cmd != 'e');
	printf("Bye!\n\n");
    /* free tasks */
    TaskP task;
    for (int i = 0; i < sizeDynArr(mainList); i++) {
		task = (TaskP)getDynArr(mainList, i);
        free(task);
    }
    
	/* delete the list */
	deleteDynArr(mainList);

	return 0;
}