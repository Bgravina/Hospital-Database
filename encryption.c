/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * Members:
 *		Bailey Gravina			|13253137
 *		Bernie Tolentino Jr.	|13...
 *		Joven Garcia			|13197189
 *		Shaheen Reza			|12794780
 *		Khanh Truong			|12879654
 * 
 * Aurthor:
 *		Joven Garcia
 *
 * Description of Program:
 * 
 * XOR cipher
 * 
 * Generate a key ASCII between Decimal 33 to 126
 * 
 *  
*******************************************************************************/


/*******************************************************************************
 * List header files
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


/*******************************************************************************
 * List preprocessing directives
*******************************************************************************/
#define MAX_STRING_LEN 99
#define MAX_PASS_LEN 16


/*******************************************************************************
 * List structs
*******************************************************************************/



/*******************************************************************************
 * Function prototypes
*******************************************************************************/
void print_menu ();
void read_database (char text[]);
void write_database (char text[]);
void encrypt_decrypt (char text[], char key);
char create_key (char text[], char key);
void display_string (char text[]);


/*******************************************************************************
 * Main
*******************************************************************************/
int main (void)
{

	char text[MAX_STRING_LEN+1];
	char pass[MAX_PASS_LEN+1];
	char key;
	char output[MAX_STRING_LEN+1];
	char decrypt[MAX_STRING_LEN+1];
	int text_len, pass_len;
	int i;
	int temp;


    /* determines which function is ran based on the user's input */
    int choice;

    /* Loops till valid input is entered or exit program is chosen */
    do
    {   
        /* Prints menu for user */
        print_menu();

        /* Reads user input and determines which function to run */
        scanf("%d", &choice);
        switch(choice)
        {
            /* Run function to read database */
            case 1:

                read_database();
                break;

            /* Run function to write to database */
            case 2:
                write_database();
                break;

            /* Run function to encrypt contents of database */
            case 3:
                encrypt_decrypt();
                break;

            /* Run function to decrypt contents of database */
            case 4:
                key = create_key();
                break;

            /* Run function to display string */
            case 5:
            	display_string();    

            /* Choice that allows user to exit the program */
            case 6:
                break;

            /* Prints invalid choice if the user inputs anything besides
            1 to 6 */
            default:
                printf("Invalid choice\n");
                break;
        }

    } while(choice != 6);

    return 0;
}


/*******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void print_menu ()
{
        printf("\n"
        "1. Read string from text file\n"
        "2. Write string to text file\n"
        "3. Encrypt/Decrypt string\n"
        "4. Create a key from a password to encrypt and decrypt string\n"
        "5. Display string\n"
        "6. Exit the program\n"
        "Enter choice (number between 1-5)>\n");
}


/*******************************************************************************
 * This function reads the database file
 * 
 * inputs:
 * - text[] 
 * outputs:
 * - none
*******************************************************************************/
void read_database (char text[])
{
    /* Variable used to control loop */
    int i = 0;

    FILE* fp = NULL;

    /* Opens textfile called database in read mode */
    fp = fopen("database.txt", "r");

    /* Exits the function if error occurs */
    if (fp == NULL)
    {
        printf("Read error\n");
        return;
    }

    /* Reads string in database textfile */
    fscanf(fp, "%[^'\n']s", text);

    /* Closes text file */
    fclose(fp);

}


/*******************************************************************************
 * This function writes to the database file
 * 
 * inputs:
 * - text[]
 * outputs:
 * - none
*******************************************************************************/
void write_database (char text[])
{
    /* Variable used to control loop */
    int i = 0;

    FILE* fp = NULL;

    /* Opens textfile called database in write mode */
    fp = fopen("database.txt", "w");

    /* Exits the function if error occurs */
    if (fp == NULL)
    {
        printf("Read error\n");
        return;
    }

    /* Writes string to database textfile */
    fprintf(fp, "%[^'\n']s", text);

    /* Closes text file */
    fclose(fp);
}


/*******************************************************************************
 * This function encrypts contents of database
 * 
 * inputs:
 * - text[]
 * outputs:
 * - none
*******************************************************************************/
void encrypt_decrypt (text[])
{
	/* Gets password length */
	pass_len = strlen(pass);

	/* Gets string length */
	text_len = strlen(text);

	if (text_len == 0)
	{
		printf("No string read\n");
	}

	if (pass_len == 0)
	{
		printf("No key generated\n");
	}

	/* XORs each of the bits of each character in the string with the key. 
	A single character in ASCII can be represented in binary as 8 bits. 
	this encryptions the string*/
	for (i = 0; i < text_len; i++)
	{
		output[i] = text[i] ^ key;
	}
}


/*******************************************************************************
 * This function decrypts contents of database
 * 
 * inputs:
 * - text[]
 * outputs:
 * - key
*******************************************************************************/
char create_key (text[], key)
{
	/* Gets password from user and stores it */
	printf("\nEnter password for string> \n");
	scanf(" %[^'\n']s", pass);

	/* Gets password length */
	pass_len = strlen(pass);

	/* Generates a key based on password. This is based on the average on 
	the value of the ASCII characters*/
	for (i = 0; i < pass_len; i++)
	{
		temp = temp + pass[i];
	}
	return temp / pass_len; 
}