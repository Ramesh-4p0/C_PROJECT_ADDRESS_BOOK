#include <stdio.h>
#include "contact.h"
#include <string.h>
#include "file.h"
extern int i;

int main(int argc, char *argv[])
{
    int choice;
    AddressBook addressBook;

    // // Initialize the address book
    initialize(&addressBook,argv,argc); // Set dummy data initially
     if(i==1){
        return 1;
     }
     
    do
    {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createContact(&addressBook);
            break;
        case 2:
            searchContact(&addressBook);
            break;
        case 3:
            editContact(&addressBook);
            break;
        case 4:
            deleteContact(&addressBook);
            break;
        case 5:
            listContacts(&addressBook); // Print contacts that were loaded from the file
            break;
        case 6:
            // Save the contacts back to file before exiting
            saveAndExit(&addressBook,argv,argc);
            printf("Saving and Exiting...\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
