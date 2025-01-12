#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>


void main() {
	printf("Welcome to LemonCode!\n\nLemonCode was built by Simer Singh and Justin Friedlander in computer science. The purpose of this algorithm is to help teachers curve the grades of their students. You will enter your data and what you want the maximum / minimum score to be . LemonCode will automatically crunch the data to fit the new maximum and minimum.\n\nWhen prompted with a question, type the answer and hit enter\n");

	// Get number of students
	int numStudents;
	printf("How many students' grades would you like to enter? (Ex: \"23\"\n");
	scanf("%d", &numStudents);

	// Include student names?
	bool names = "False";
	char y_n;
	printf("Would you like to include the students' name with their grade? (y/n)\n");
	
	scanf("%s", &y_n);
	
	if (tolower(y_n) == 'n')
		names = "True";

	if (names){
		printf("Working\n");
	} else
		printf("Not working...\n");
	
	

}
