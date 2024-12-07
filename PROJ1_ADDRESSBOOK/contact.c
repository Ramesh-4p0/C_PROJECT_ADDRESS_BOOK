#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <stdio_ext.h>
int i = 0;
void listContacts(AddressBook *addressBook)
{ printf("******************************************************************\n");
  printf("Sl_NO\t\t NAME\t\t PHONE_NO\t MAIL_ID\t\t \n");
  int i;
  for (i = 0; i < (addressBook->contactCount); i++)
  {
    printf("%-15d %-15s %-15s %-15s \n",i+1,addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
  }
  printf("******************************************************************\n");
}

void initialize(AddressBook *addressBook, char *argv[], int argc) {
    if (argc > 1) { // If a file name is passed as a command-line argument
        char *fileName = argv[1];

        // Check if the file ends with .csv
        if (strstr(fileName, ".csv") == fileName + strlen(fileName) - 4) {
            FILE *checkPtr = fopen(fileName, "r"); // Try opening the file in read mode

            if (checkPtr != NULL) {
                // If the file exists, load contacts from the file
                addressBook->contactCount = 0;
                loadContactsFromFile(addressBook, fileName);
                fclose(checkPtr); // Close the file after loading
            } else {
                // If the file doesn't exist, create a new file and use default population
                printf("Error: Unable to open file '%s'. Using default population.\n", fileName);
                addressBook->contactCount = 0;
                populateAddressBook(addressBook);
            }
        } else {
            printf("Not a valid CSV file.\n");
            return;  // Exit if the file name is not valid
        }
    } else { // If no command-line argument is provided
        // Use the predefined 'back.csv' file
        
        addressBook->contactCount = 0;
        populateAddressBook(addressBook);
        // saveContactsToFile(addressBook, fileName);
        // printf("Data saved to default file '%s'.\n", fileName);
    }
}


void saveAndExit(AddressBook *addressBook,char * argv[],int argc)
{     if (argc > 1)
            {   char *filename=argv[1];
                saveContactsToFile(addressBook, filename);
            }
            else{
                char *fileName = "back.csv";
                saveContactsToFile(addressBook, fileName);
            }
}

void createContact(AddressBook *addressBook)
{
  char name[50], phone[20], email[50];
  __fpurge(stdin);
  printf("Enter the Name: ");
  scanf("%49[^\n]", name);
  __fpurge(stdin);
  strcpy(addressBook->contacts[addressBook->contactCount].name, name);
 
  phone: printf("Enter the Phone no: ");
  scanf("%19[^\n]", phone);
  __fpurge(stdin);
  printf(" Entered Phone no is %s\n", phone);
  int i = 0, flag = 0;
  int flag2 = 0;
  int num = strlen(phone);
  if (num < 10 || num > 10)
  {
    printf("phone no is not valid\n");
    goto phone;
  }
  while (phone[i] != '\0')
  {
    if (!(phone[i] >= '0' && phone[i] <= '9'))
    {
      printf("enter nos\n");
      flag2 = 1;
      break;
    }
    i++;
  }
  if (flag2 == 1)
  {
    goto phone;
  }

  // Check if phone number already exists
  for (i = 0; i < addressBook->contactCount; i++)
  {
    if (strcmp(addressBook->contacts[i].phone, phone) == 0)
    {
      printf("Error: Phone number already exists.\n");
      flag = 1;
      break;
    }
  }

  if (flag == 1)
  {
    goto phone; // Stop the function if the phone number already exists
  }
  strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
  printf("Phone no is successfully added\n");

  Email:printf("Enter the email\n");
  scanf("%49[^\n]", email);
  __fpurge(stdin);

  int flag3 = 0;              // To check if '@' was found
  int length = strlen(email); // Get the length of the email
  i = 0;                      // Initialize i for email traversal

  while (email[i] != '\0')
  {
    if (email[i] == '@')
    {
      // Check that there's a character after '@'
      if (email[i + 1] == '\0' || email[i + 1] == '.')
      {
        printf("Invalid: There should be a lowercase character after '@'.\n");
        goto Email;
      }
      flag3 = 1;         // '@' found
      int start = i + 1; // Start checking after '@'

      // Loop to validate the characters after '@'
      while (start < length - 4)
      { // Stop before the last 4 characters
        if (!(email[start] >= 'a' && email[start] <= 'z' || email[start] >= '0' && email[start] <= '9' || email[start] == '.'))
        {
          printf("Invalid: There should be lowercase characters in the domain.\n");
          goto Email;
        }
        start++;
      }
      i++;
    }
    else
    {
      i++;
    }
  }

  if (flag3 == 0)
  {
    printf("Invalid: Email must contain '@'.\n");
    goto Email;
  }

  // Check if the email ends with ".com"
  if (length < 4 || strcmp(&email[length - 4], ".com") != 0)
  {
    printf("Invalid: Email must end with '.com'.\n");
   goto Email;
  }
   for (i = 0; i < addressBook->contactCount; i++)
  { flag=0;
    if (strcmp(addressBook->contacts[i].email, email) == 0)
    {
      printf("Error: Email already exists.\n");
      flag = 1;
      break;
    }
  }

  if (flag == 1)
  {
    goto Email; // Stop the function if the Email id already exists
  }

  // If all checks pass, save the email
  strcpy(addressBook->contacts[addressBook->contactCount].email, email);
  addressBook->contactCount++;
  printf("Contact created successfully!\n");
}

void searchContact(AddressBook *addressBook)
{
  int option, j;
  char name[50], phone[50], email[50];
 search: printf("Enter the searchby option\n");
  printf("1: NAME\n");
  printf("2: Phone_no\n");
  printf("3: MAIL_ID\n");
  scanf("%d", &option);
  printf("The Entered option is %d \n", option);
  if (option == 1)
  {
    __fpurge(stdin);
    printf("Enter the Name: ");
    scanf("%49[^\n]", name);
    __fpurge(stdin);
    int exist_flag = 0;
   printf("******************************************************************\n");
  printf("Sl_NO\t\t NAME\t\t PHONE_NO\t MAIL_ID\t\t \n");
    for (j = 0; j < addressBook->contactCount; j++)
    {
      if (!(strcmp(addressBook->contacts[j].name, name)))
      {
        exist_flag = 1;
        printf("%-15d %-15s %-15s %-15s\n",j+1, addressBook->contacts[j].name, addressBook->contacts[j].phone, addressBook->contacts[j].email);
      }
    }
    if (exist_flag == 0)
    {
      printf("The Searched Name is not available\n");
      goto search;
    }
  }
  else if (option == 2)
  {
    __fpurge(stdin);
    printf("Enter the phone: ");
    scanf("%49[^\n]", phone);
    __fpurge(stdin);
    int exist_flag1 = 0;
     printf("******************************************************************\n");
  printf("Sl_NO\t\t NAME\t\t PHONE_NO\t MAIL_ID\t\t \n");
    for (j = 0; j < addressBook->contactCount; j++)
    {
      if (!(strcmp(addressBook->contacts[j].phone, phone)))
      {
        exist_flag1 = 1;
        printf("%-15d %-15s %-15s %-15s\n",j+1, addressBook->contacts[j].name, addressBook->contacts[j].phone, addressBook->contacts[j].email);
      }
    }
    if (exist_flag1 == 0)
    {
      printf("The Searched Phone_no is not available\n");
       goto search;
    }
  }
  else if (option == 3)
  {
    __fpurge(stdin);
    printf("Enter the Email Id: ");
    scanf("%49[^\n]", email);
    __fpurge(stdin);
    int exist_flag2 = 0;
        printf("******************************************************************\n");
  printf("Sl_NO\t\t NAME\t\t PHONE_NO\t MAIL_ID\t\t \n");
    for (j = 0; j < addressBook->contactCount; j++)
    {
      if (!(strcmp(addressBook->contacts[j].email, email)))
      {
        exist_flag2 = 1;
        printf("%-15d %-15s %-15s %-15s\n",j+1, addressBook->contacts[j].name, addressBook->contacts[j].phone, addressBook->contacts[j].email);
      }
    }
    if (exist_flag2 == 0)
    {
      printf("The Searched Email_id is not available\n");
       goto search;
    }
  }
  else
  {
    printf("Invalid option choose among the given options\n");
     goto search;
  }
}

void editContact(AddressBook *addressBook)
{
  int edit_option, i, index;
  char name[50], new_name[50], phone[50], new_phone[50], email[50], new_email[50];
  printf("Enter the edit by option\n");
  printf("1.NAME\n");
  printf("2.PHONE_NO\n");
  printf("3.MAIL_ID\n");
  scanf("%d", &edit_option);
  if (edit_option == 1)
  {
    int flag = 0;
    __fpurge(stdin);
    printf("Enter the name to be edited:\n");
    scanf("%49[^\n]", name);
    __fpurge(stdin);
    printf("Index\t\t NAME\t\t PHONE_NO\t MAIL_ID\t\t \n");
    for (i = 0; i < addressBook->contactCount; i++)
    {
      flag = 1;
      if ((!(strcmp(addressBook->contacts[i].name, name))))
      {
        printf("%-15d %-15s %-15s %-15s\n", i, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
      }
    }
    if (flag == 0)
    {
      printf("The entered number doesnt exist\n");
    }

    printf("Enter the index to be edited\n");
    scanf("%d", &index);
    __fpurge(stdin);
    printf("Enter the new name to be edited insted of the existing name\n");
    scanf("%49[^\n]", new_name);
    __fpurge(stdin);
    strcpy(addressBook->contacts[index].name, new_name);
  }
  else if (edit_option == 2)
  {
    __fpurge(stdin);
   phoneno: printf("Enter the Phone no to be edited: \n");
    scanf("%19[^\n]", phone);
    __fpurge(stdin);
    int j, edit_index1, flag1 = 0;
    for (j = 0; j < addressBook->contactCount; j++)
    {
      if ((!(strcmp(addressBook->contacts[j].phone, phone))))
      {
        flag1 = 1;
        edit_index1 = j;
        printf("%-15d %-15s %-15s %-15s\n", j+1, addressBook->contacts[j].name, addressBook->contacts[j].phone, addressBook->contacts[j].email);
      }
    }
    if (flag1 == 0)
    {
      printf("The entered phone no doesnt exist\n");
      goto  phoneno;
    }
    __fpurge(stdin);
    printf("Enter the new Phone no to be edited instead of the existing phone no: \n");
    scanf("%19[^\n]", new_phone);
    __fpurge(stdin);
    int i = 0, flag = 0;
    int flag2 = 0;
    int num = strlen(new_phone);
    if (num < 10 || num > 10)
    {
      printf("phone no is not valid\n");
      return;
    }
    while (new_phone[i] != '\0')
    {
      if (!(new_phone[i] >= '0' && new_phone[i] <= '9'))
      {
        printf("enter nos\n");
        flag2 = 1;
        break;
      }
      i++;
    }
    if (flag2 == 1)
    {
      return;
    }

    // Check if phone number already exists
    for (i = 0; i < addressBook->contactCount; i++)
    {
      if (strcmp(addressBook->contacts[i].phone, new_phone) == 0)
      {
        printf("Error: Phone number already exists. Enter the a valid no \n");
        flag = 1;
        break;
      }
    }

    if (flag == 1)
    {
      return; // Stop the function if the phone number already exists
    }
    strcpy(addressBook->contacts[edit_index1].phone, new_phone);
  }
  else if (edit_option == 3)
  {
    int flagg = 0;
    __fpurge(stdin);
    printf("Enter the email\n");
    scanf("%49[^\n]", email);
    __fpurge(stdin);
    int j, edit_index3;
    for (j = 0; j < addressBook->contactCount; j++)
    {
      if ((!(strcmp(addressBook->contacts[j].email, email))))
      {
        flagg = 1;
        edit_index3 = j;
        printf("%-15d %-15s %-15s %-15s\n", i, addressBook->contacts[j].name, addressBook->contacts[j].phone, addressBook->contacts[j].email);
      }
    }
    if (flagg == 0)
    {
      printf("The entered gmail doesnt exist\n");
    }

    __fpurge(stdin);
    printf("Enter the email\n");
    scanf("%49[^\n]", new_email);
    __fpurge(stdin);
    int flag3 = 0;                  // To check if '@' was found
    int length = strlen(new_email); // Get the length of the email
    i = 0;                          // Initialize i for email traversal

    while (new_email[i] != '\0')
    {
      if (new_email[i] == '@')
      {
        // Check that there's a character after '@'
        if (new_email[i + 1] == '\0' || new_email[i + 1] == '.')
        {
          printf("Invalid: There should be a lowercase character after '@'.\n");
          return;
        }
        flag3 = 1;         // '@' found
        int start = i + 1; // Start checking after '@'

        // Loop to validate the characters after '@'
        while (start < length - 4)
        { // Stop before the last 4 characters
          if (!(new_email[start] >= 'a' && new_email[start] <= 'z' || new_email[start] >= '0' && new_email[start] <= '9' || new_email[start] == '.'))
          {
            printf("Invalid: There should be lowercase characters in the domain.\n");
            return;
          }
          start++;
        }
        i++;
      }
      else
      {
        i++;
      }
    }

    if (flag3 == 0)
    {
      printf("Invalid: Email must contain '@'.\n");
      return;
    }

    // Check if the email ends with ".com"
    if (length < 4 || strcmp(&new_email[length - 4], ".com") != 0)
    {
      printf("Invalid: Email must end with '.com'.\n");
      return;
    }

    // If all checks pass, save the email
    strcpy(addressBook->contacts[edit_index3].email, new_email);
    // // addressBook->contactCount++;
    // printf("Contact created successfully!\n");
  }
  else
  {
    printf("enter a valid option\n");
  }
}

void deleteContact(AddressBook *addressBook)
{
  int contact_removed;
  listContacts(addressBook);
  printf("Enter which contact to be deleted\n");
  scanf("%d", &contact_removed);
  int k, delete_flag = 0;
  for (k = 0; k < addressBook->contactCount; k++)
  {
    if (k == contact_removed - 1)
    {
      delete_flag = 1;
      while (k < addressBook->contactCount)
      {
        addressBook->contacts[k] = addressBook->contacts[k + 1];
        k++;
      }
      if (delete_flag == 1)
      {
        addressBook->contactCount = addressBook->contactCount - 1;
        break;
      }
    }
  }
}
