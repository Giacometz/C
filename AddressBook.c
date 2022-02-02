#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*address book struct*/
struct AddressBook {
	char surname[50];
	char firstname[50];
	char city[50];
	char phone[50];
	char maritalStatus[10];
};

/*function to add the contact into binary file*/
void addContact()
{
	struct AddressBook *book = (struct AddresssBook *)malloc(sizeof(struct AddressBook) * 1);
	printf("Enter surname: ");
	scanf("%s", book->surname);
	printf("Enter first name: ");
	scanf("%s", book->firstname);
	printf("Enter city: ");
	scanf("%s", book->city);
	printf("Enter phone: ");
	scanf("%s", book->phone);
	printf("Enter marital status(single/married): ");
	scanf("%s", book->maritalStatus);

	FILE* f1 = fopen("contacts.dat", "r");
	FILE *temp = fopen("temp.dat", "w");
	struct AddressBook *book1 = (struct AddresssBook *)malloc(sizeof(struct AddressBook) * 1);
	fread(book1, sizeof(struct AddressBook), 1, f1);
	while (!feof(f1))
	{
		fwrite(book1, sizeof(struct AddressBook), 1, temp);
		fread(book1, sizeof(struct AddressBook), 1, f1);
	}
	fwrite(book, sizeof(struct AddressBook), 1, temp);
	fclose(f1);
	fclose(temp);

	f1 = fopen("temp.dat", "r");
	temp = fopen("contacts.dat", "w");
	fread(book1, sizeof(struct AddressBook), 1, f1);
	while (!feof(f1))
	{
		fwrite(book1, sizeof(struct AddressBook), 1, temp);
		fread(book1, sizeof(struct AddressBook), 1, f1);
	}
	fclose(f1);
	fclose(temp);
}

//function to delete contact from binary file
void deleteContact()
{
	char firstname[50], lastname[50];
	printf("Enter first name: ");
	scanf("%s", firstname);
	printf("Enter last name: ");
	scanf("%s", lastname);

	struct AddressBook *book1 = (struct AddresssBook *)malloc(sizeof(struct AddressBook) * 1);
	FILE *f1 = fopen("contacts.dat", "r");
	FILE *temp = fopen("temp.dat", "w");
	fread(book1, sizeof(struct AddressBook), 1, f1);
	while (!feof(f1))
	{
		if (!(strcmp(firstname, book1->firstname) == 0 &&
			strcmp(lastname, book1->surname) == 0)) {
			fwrite(book1, sizeof(struct AddressBook), 1, temp);
		}
		fread(book1, sizeof(struct AddressBook), 1, f1);
	}
	fclose(f1);
	fclose(temp);
	f1 = fopen("temp.dat", "r");
	temp = fopen("contacts.dat", "w");
	fread(book1, sizeof(struct AddressBook), 1, f1);
	while (!feof(f1))
	{
		fwrite(book1, sizeof(struct AddressBook), 1, temp);
		fread(book1, sizeof(struct AddressBook), 1, f1);
	}
	fclose(f1);
	fclose(temp);
}

//function to search a contact from binary file
void searchContact()
{
	char firstname[50], lastname[50];
	printf("Enter first name: ");
	scanf("%s", firstname);
	printf("Enter last name: ");
	scanf("%s", lastname);

	struct AddressBook *book1 = (struct AddresssBook *)malloc(sizeof(struct AddressBook) * 1);
	FILE *f1 = fopen("contacts.dat", "r");
	fread(book1, sizeof(struct AddressBook), 1, f1);
	while (!feof(f1))
	{
		if (strcmp(firstname, book1->firstname) == 0 &&
			strcmp(lastname, book1->surname) == 0) {
			printf("First Name: %s\n", book1->firstname);
			printf("Surname: %s\n", book1->surname);
			printf("City: %s\n", book1->city);
			printf("Phone: %s\n", book1->phone);
			printf("Marital Status: %s\n", book1->maritalStatus);
		}
		fread(book1, sizeof(struct AddressBook), 1, f1);
	}
	fclose(f1);
}

//function to sort the contacts in the file by the city
void sortByCity()
{
	struct AddressBook *book1 = (struct AddresssBook *)malloc(sizeof(struct AddressBook) * 1);
	FILE *f1 = fopen("contacts.dat", "r");
	fread(book1, sizeof(struct AddressBook), 1, f1);
	int count = 0;
	while (!feof(f1))
	{
		count++;
		fread(book1, sizeof(struct AddressBook), 1, f1);
	}
	fclose(f1);

	struct AddressBook *books = (struct AddresssBook *)malloc(sizeof(struct AddressBook) * count+1);
	f1 = fopen("contacts.dat", "r");
	int i = 0;
	fread(&(books[i]), sizeof(struct AddressBook), 1, f1);
	while (!feof(f1))
	{
		i++;
		fread(&(books[i]), sizeof(struct AddressBook), 1, f1);
	}
	fclose(f1);

	for (int i = 1; i < count; i++)
		for (int j = 0; j < count - i; j++) {
			if (strcmp(books[j].city, books[j + 1].city) > 0) {
				struct AddressBook *temp = (struct AddresssBook *)malloc(sizeof(struct AddressBook) * 1);
				*temp = books[j];
				books[j] = books[j + 1];
				books[j + 1] = *temp;
			}
		}

	FILE *fw = fopen("contacts.dat", "w");
	for (int i = 0; i < count; i++)
	{
		fwrite(&(books[i]), sizeof(struct AddressBook), 1, fw);
		printf("%s\n", books[i].firstname);
	}
	fclose(fw);
}

//function to print the all contact details
void printContactDetails()
{
	char firstname[50], lastname[50];
	printf("Enter first name: ");
	scanf("%s", firstname);
	printf("Enter last name: ");
	scanf("%s", lastname);
	struct AddressBook *book1 = (struct AddresssBook *)malloc(sizeof(struct AddressBook) * 1);
	FILE *f1 = fopen("contacts.dat", "r");
	fread(book1, sizeof(struct AddressBook), 1, f1);
	while (!feof(f1))
	{
		if(strcmp(firstname,book1->firstname)==0 &&
			strcmp(lastname, book1->surname)==0) {
			printf("First Name: %s\n", book1->firstname);
			printf("Surname: %s\n", book1->surname);
			printf("City: %s\n", book1->city);
			printf("Phone: %s\n", book1->phone);
			printf("Marital Status: %s\n", book1->maritalStatus);
			printf("-----------------------\n");
		}
		fread(book1, sizeof(struct AddressBook), 1, f1);
	}
	fclose(f1);
}

//function to print only surnames and names of the contacts
void printSurnameAndNames()
{
	FILE* f = fopen("contacts.dat", "r");
	struct AddressBook *book = (struct AddresssBook *)malloc(sizeof(struct AddressBook) * 1);
	fread(book, sizeof(struct AddressBook), 1, f);
	while (!feof(f))
	{
		printf("First Name: %s\n", book->firstname);
		printf("Surname: %s\n", book->surname);
		printf("-----------------------\n");
		fread(book, sizeof(struct AddressBook), 1, f);
	}
	fclose(f);
}

//main driver function
int menu()
{
	int choice;
	printf("1. Add a contact \n");
	printf("2. Delete a contact \n");
	printf("3. Search a contact \n");
	printf("4. Sort by city \n");
	printf("5. Print contact details \n");
	printf("6. Print surname and name of all contacts \n");
	printf("7. Exit \n");
	printf("Enter option (1-7): ");
	scanf("%d", &choice);
	while (choice < 1 || choice>7)
	{
		printf("Wrong Input, Enter again (1-7): ");
		scanf("%d", &choice);
	}
	return choice;
}

int main()
{
	int choice;
	do 
	{
		choice = menu();
		switch (choice)
		{
		case 1:
			printf("-------------------------------------------\n");
			addContact();
			printf("-------------------------------------------\n");
			break;
		case 2:
			printf("-------------------------------------------\n");
			deleteContact();
			printf("-------------------------------------------\n");
			break;
		case 3:
			printf("-------------------------------------------\n");
			searchContact();
			printf("-------------------------------------------\n");
			break;
		case 4:
			printf("-------------------------------------------\n");
			sortByCity();
			printf("-------------------------------------------\n");
			break;
		case 5:
			printf("-------------------------------------------\n");
			printContactDetails();
			printf("-------------------------------------------\n");
			break;
		case 6:
			printf("-------------------------------------------\n");
			printSurnameAndNames();
			printf("-------------------------------------------\n");
			break;
		case 7:
			printf("----------- GOOD BYE ------------\n");
			break;
		default:
			printf("Wrong Input, Enter again (1-7): \n");
		}
	} while (choice != 7);

	return 0;
}