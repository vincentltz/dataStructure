/* CS261- Assignment 5
* Name: Li, Tingzhi & Zhang, Chunyang
* Date: 5/16/2015
* Development Environment: Xcode & MSVC
* Solution description: To-do list application. This main function controls the interactions between the user and the program.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"


int main (int argc, const char * argv[])
{
  char cmd = ' ';
  DynArr* mainList = createDynArr(10);
  /*two pointers that most of the options could be using*/
  TaskP temp = malloc(sizeof(struct Task));
  FILE *toDoFile;

  printf("\n\n** TO-DO LIST APPLICATION **\n\n");

  do
    {
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
	  /* Note: We have provided functions called printList(), saveList() and loadList() for you
	  to use.  They can be found in toDoList.c */

	  TaskP newTask = temp;

	  if (cmd == 'l')
	  {
		  printf("Please enter the filename: ");
		  //setbuf(stdin, NULL);
		  scanf("%[^\n]", newTask->description);
		  toDoFile = fopen(newTask->description, "r");
		  if (toDoFile == NULL)
			  printf("Can't open the file! Please double check!\n\n");
		  else
		  {
			  loadList(mainList, toDoFile);
			  fclose(toDoFile);
			  printf("The list has been loaded from file successfully.\n\n");
		  }
		  }
	  else if (cmd == 's')
	  {
		  printf("Please enter the filename: ");
		  //setbuf(stdin, NULL);
		  scanf("%[^\n]", newTask->description);
		  toDoFile = fopen(newTask->description, "w");
		  saveList(mainList, toDoFile);
		  fclose(toDoFile);
		  printf("The list has been saved into the file successfully.\n\n");
		  //}
	  }
	  else if (cmd == 'a')
	  {
		  printf("Please enter the task description: ");
		  //setbuf(stdin, NULL);
		  scanf("%[^\n]", newTask->description);
		  printf("Please enter the task priority (0-999): ");
		  setbuf(stdin, NULL);
		  scanf("%d", &newTask->priority);
		  addHeap(mainList, createTask(newTask->priority, newTask->description), compare);
		  printf("The task '%s' has been added to your to-do list.\n\n", newTask->description);
	  }
	  else if (cmd == 'g')
	  {
		  if (isEmptyDynArr(mainList)) 
			  printf("Your to-do list is empty.\n\n");
		  else
		  {
			  newTask = (TaskP)getMinHeap(mainList);
			  printf("Your first task is '%s'.\n\n", newTask->description);
		  }
	  }
	  else if (cmd == 'r')
	  {
		  if (isEmptyDynArr(mainList))
			  printf("Your to-do list is empty.\n\n");
		  else
		  {
			  newTask = (TaskP)getMinHeap(mainList);
			  printf("Your first task '%s' has been removed from the list.\n\n", newTask->description);
			  free(newTask);
			  removeMinHeap(mainList, compare);
		  }
	  }
	  else if (cmd == 'p')
	  {
		  if (isEmptyDynArr(mainList))
			  printf("Your to-do list is empty! There is nothing to print!\n\n");
		  else
			  printList(mainList);
	  }
	  else if (cmd != 'e')
		  printf("Wrong command, please choose again!\n\n");
	  setbuf(stdin, NULL);
  } while (cmd != 'e');
	printf("Bye!\n\n");
  /* delete the list */
	for (int i = 0; i < sizeDynArr(mainList); i++)
	{
		free((TaskP)getDynArr(mainList, i));
	}
	deleteDynArr(mainList);
	free(temp);

	return 0;
}
