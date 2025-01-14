#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Struct for linked list
typedef struct Node {
	char * name;
	float grade;
	struct Node * next;
} Node;

// Create node. Return its memory address
Node* createNode (float grade, char * name) {
	Node * new = malloc(sizeof(Node)); // Free'd in freeNodes
	new -> grade = grade;	
	new -> name = NULL;
	new -> next = NULL;
	
	// Copy string to heap
	if (name) {
		new -> name = malloc(sizeof(name) + 1); // Free'd in freeNodes
		strcpy(new -> name, name);
	}
	
	return new;
}


// Get the memory address of a node at a certain index (starting at 1)
Node* getNode(Node * current, int index) {
	if (!current)
		return NULL;

	if (index == 1)
		return current;

	return getNode(current -> next, index-1);

}


void printGrades (Node * node, bool names) {
	printf("\n");
	if (names) {
		while (node) {
			printf("%s: %f\t", node->name, node->grade);
			node = node -> next;
		}
	} else {
		while (node) {
			printf("%f  ", node->grade);
			node = node -> next;
		}
	}
	printf("\n\n");
}

// Free allocated memory recursively
void freeNodes(Node * current) {
	if (current) {
		Node * next = current -> next;
		free(current -> name); // Free the copy of the name
		free(current); // Free the whole node
		freeNodes(next);
	}
}

float getDouble() {
	float num;
	float previous = 0;

	while (true) {
		if (scanf("%f", &num) != 1) { // 1 is the number of succesfully scanned items
			printf("Please enter a valid number (exclude the percent symbol).\n");
			previous = 0;
			while (getchar() != '\n');
		} else if (num != 0 && num <= 2) {
			if (num == previous) {
				return num;
			} else {
				previous = num;
				printf("Enter the grade as a positive percent. Retype the number if the percent is less than or equal to 2.\n");
			}
		} else {
			return num;
		}
	}

}


// Main function
void main() {
	printf("Welcome to LemonCode!\n\nLemonCode was built by Simer Singh and Justin Friedlander in computer science. The purpose of this algorithm is to help teachers curve the grades of their students. You will enter your data and what you want the maximum / minimum score to be . LemonCode will automatically crunch the data to fit the new maximum and minimum.\n\nWhen prompted with a question, type the answer and hit enter.\n");

	// Get number of students
	int numStudents;
	printf("How many students' grades would you like to enter?\n");
	while (true) {
		if (scanf("%d", &numStudents) == 1) break;
		
		printf("Please enter an integer\n");
		
		while (getchar() != '\n');
	}
			
	// Include student names question and ensure output is "y" or "n"
	bool names = false;
	char y_n;
	printf("Would you like to include the students' name with their grade? (y/n)\n");
	
	scanf("%s", &y_n);
	while (tolower(y_n) != 'y' && tolower(y_n) != 'n') {
		printf("Please input 'y' or 'n'\n");
		scanf("%s", &y_n);
	}
	
	if (tolower(y_n) == 'y')
		names = true;

		

	// Gather student names and/or corresponding grades through linked list and structs
	Node * firstNode;
	bool first = true;

	if (names) {
				
		for (int i=0; i < numStudents; i++) {
			char name[30]; // Make a new memory address for each new name
			printf("Enter Student %d\'s name\n", (i+1));
			while (getchar() != '\n'); // Wait for new line buffer
			fgets(name, sizeof(name), stdin);

			// Remove \n from input
			while (strchr(name, '\n') != NULL)
				*strchr(name, '\n') = '\0';

			printf("Enter %s's grade (as a percent)\n", name);
			float grade = getDouble();
			if (first) {
				firstNode = createNode(grade, name);
				first = !first;
			} else {
				Node * newNode = createNode(grade, name);
				getNode(firstNode, i) -> next = newNode;
			}
			//printf("%p", *name);
			//if (i!=0)
			//printf("%p\n", *(getNode(firstNode, i) -> name));
		}
		
		printGrades(firstNode, true);
	} else {
		for (int i=0; i < numStudents; i++) {
			printf("Enter Student %d's grade (as a percent)\n", (i+1));
			float grade = getDouble();
				
			if (first) {
				firstNode = createNode(grade, NULL);
				first = !first;
			} else {
				Node * newNode = createNode(grade, NULL);
				getNode(firstNode, i) -> next = newNode;
		
			}
	
		}
		printGrades(firstNode, false);
	}
	

	// Grade curving calculation
	
	float minOld = getNode(firstNode, 1) -> grade;
	float maxOld = minOld;
	float minNew;
	float maxNew;

	// Get current spread of data
	int index = 1;
	while(true) {
		float currentGrade = (getNode(firstNode, index) -> grade);
		if (currentGrade < minOld) minOld = currentGrade;
		if (currentGrade > maxOld) maxOld = currentGrade;
		
		// End loop while including the last element
		if (!getNode(firstNode, index) -> next) break;
		index++;
	}

	// Get desired spread of data
	printf("What would you like the new minimum to be? (as a percent)\n");
	minNew = getDouble();

	printf("What would you like the new maximum to be? (as a percent)\n");
       	maxNew = getDouble();


	// Update current grades with curved grades
	index = 1;
	while (true) {
		float * currentGrade = &(getNode(firstNode, index) -> grade);
		// My linear interpolation formula
		*currentGrade = ((*currentGrade - minOld) / (maxOld - minOld)) * (maxNew - minNew) + minNew;

		if (!getNode(firstNode, index) -> next) break;
		index++;
	}
	printGrades(firstNode, names);
	
	// End of program
	freeNodes(firstNode);
}
