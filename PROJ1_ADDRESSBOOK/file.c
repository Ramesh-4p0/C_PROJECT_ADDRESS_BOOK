#include <stdio.h>
#include "file.h"
#include <string.h>

void saveContactsToFile(AddressBook *addressBook, char *fileName)
{
    FILE *fptr = fopen(fileName, "w");
    if (fptr == NULL)
    {
        printf("Failed to open file\n");
        return;
    }

    // Write the contact count as a header
    fprintf(fptr, "#%d#\n", addressBook->contactCount);

    // Loop through contacts and write them
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        // Write contact details without extra newlines
        fprintf(fptr, "%s,%s,%s", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        
        // Add a newline after each contact if it's not the last one
        if (i < addressBook->contactCount - 1)
        {
            fprintf(fptr, "\n");
        }
    }

    fclose(fptr);
    printf("Contacts saved to file.\n");
}


void loadContactsFromFile(AddressBook *addressBook, char *fileName)
{
    FILE *fptr = fopen(fileName, "r");
    if (fptr == NULL)
    {
        printf("Error: Could not open the file '%s'.\n", fileName);
        return;
    }

    char content[100], name[50], phone[20], email[50];

    // Skip the first line that contains the contact count header
    fgets(content, sizeof(content), fptr); 

    // Read contact details, making sure to ignore empty lines and avoid blank entries
    while (fscanf(fptr, " %49[^,],%19[^,],%49[^\n]", name, phone, email) == 3)
    {
        if (strlen(name) > 0 && strlen(phone) > 0 && strlen(email) > 0)
        {
            // Store the contact if it's valid
            strcpy(addressBook->contacts[addressBook->contactCount].name, name);
            strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
            strcpy(addressBook->contacts[addressBook->contactCount].email, email);
            addressBook->contactCount++;
        }

        // Skip the newline character after the contact information
        fgetc(fptr);
    }

    fclose(fptr);
    printf("Contacts loaded from file.\n");
}
