/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * Members:
 *  	Bailey Gravina		  	|13253137
 *  	Bernie Tolentino Jr.	|
 *		Jove Garcia				|
 *		Khanh Truong			|12879654
 *		Shaheen Reza			|12794780
 *
 * Date of submission:
 *
 * Description of Program: This database program stores and processes patient
 * and hospital for both nurse and public use. Nurses will be able to make three
 * types of searches and are: medicine, patient or location.
 *
 * 	Medicine - A nurse will be able to display all medicines used in hospital or
 * 	search a particular medicine used within the hospital. If the search is
 * 	valid, the database will load a brief profile on the medicine, including
 * 	recommended dosage and availability within the hospital. The database will
 * 	also load information for all patients that require that particular medicine
 * 	and why.
 *
 * 	Patient - A nurse will be able to search a particular patient within the
 * 	database or display all current patients in alphabetical order by surname.
 * 	Once a search has been completed, the nurse will be able to update or view
 * 	a patients profile. This profile includes many personal details such as:
 * 	age, weight, emergency contact and their location within the hospital.
 *  An example of a situation where a patients info needs to be updated is for
 *  initial admission to thge hospital, or if they have been relocated within
 *  the hospital. That way, nurses and other relevant staff can keep track of
 *  where their patients are located. A patient will also be able to view their
 *  own information via a login.
 *
 *  Location - A nurse will be able to search a particular patient within the
 *  database or display all major locations stored within the database. When a
 *  a valid location search is made, a list of patients and staff within that
 *  location will be displayed.
*******************************************************************************/

/*******************************************************************************
	Header files
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*******************************************************************************
	Macros
*******************************************************************************/
#define MAX_NUM_PATIENTS 100
#define MAX_NUM_ID 200
#define MAX_DEPARTMENT_LEN 20
#define MAX_LEVEL_LEN 2
#define MAX_ROOM_LEN 3
#define	MAX_MED_LEN 20
#define MAX_NAME_LEN 20
#define MAX_ID_LEN 6
#define MAX_PASS_LEN 16
#define LEVEL_MIN 0         /* Min level of hospital, can be changed according
                               to hospital */
#define LEVEL_MAX 5         /* Max level of hospital, can be changed according
                               to hospital */
/*******************************************************************************
	Structures
	Patient (array library)
		-> medicine (struct within struct + library)
		-> location (struct within struct + library)
	2. medicine info (array library)
		-> medicine description (struct within a struct)
		-> patients using medication (linked array list)
	3. location info
		-> Location description (struct within a struct)
		-> patient or staff in location (linked array list)
*******************************************************************************/

/*==============================================================================
	date_time_t struct: used for informaton regarding patients admission and
	relief from hospital. Will be a struct within patient struct.
==============================================================================*/
	struct date_time
	{
		int month, day, year, hour, min;
	};
	typedef struct date_time date_time_t;
/*==============================================================================
	location_t struct: used for information regarding patients location within
	hospital. Will be a struct within patient_t struct.
==============================================================================*/
	struct location
	{
		char department[MAX_DEPARTMENT_LEN + 1];
		int level;
		int room;
	};
	typedef struct location location_t;
/*==============================================================================
	medicine_t struct: used for information regarding medicine required by
	patients. Will be a struct within patient_t struct.
==============================================================================*/
	struct diagnosis
	{
		char category[20];
		char description[400];
		char med[MAX_MED_LEN + 1];
		int dose, times;
	};
	typedef struct diagnosis diagnosis_t;
/*==============================================================================
	patient_t struct: used for storing all relevant patient information
	including: date_time_t, location_t and medicine_t. It will also store
	personal information.
==============================================================================*/
	struct patient
	{
		char surname[MAX_NAME_LEN + 1];
		char firstname[MAX_NAME_LEN + 1];
		int age, weight, height;
		date_time_t arrival_dt;
		location_t location_dt;
		date_time_t departure_dt;
		diagnosis_t diagnosis;
	};
	typedef struct patient patient_t;
/*==============================================================================
	location struct:
==============================================================================*/
/*******************************************************************************
	Function Prototypes
*******************************************************************************/
/*==============================================================================
	Database prototypes: Main prototypes used for managing database.
==============================================================================*/
	int logon(); 					/* returns 1 if valid, else 0 for invalid */
	void print_login_menu();
	void print_menu(void); 				  /* displays menu for user selection */
	void print_location();
	void add_patient(patient_t patient_lib[], int count);
	void display_patient(); 		     		  /* displays patient profile */
	void encrypt(); 								/* encrypts database data */
	void decrypt(); 								/* decrypts database data */
	void compress(); 							  /* compresses database data */
	void save_patient(patient_t patient_lib[], int count);/* saves database to text file */
	int load_patient();						 /* loads database from text file */
/*==============================================================================
	Valid user input prototypes: Secondary prototypes for ensuring proper user
	input.
==============================================================================*/
	int valid_logon();				/* checks if staff/patient logon is valid */
	int valid_patient(); 	  	   /* checks if patient info entered is valid */
	int valid_time();	   /* check if arrival and departure entered is valid */
	int valid_location();         /* checks if location info entered is valid */
	int valid_medicine(); 		  /* checks if medicine info entered is valid */
/*==============================================================================
	Request patients location within hospital. This allows nurses to be aware
	of where patients are located. This location will also be updatable.
==============================================================================*/
/*******************************************************************************
	Main
*******************************************************************************/
int main(void)
{
	int choice = 0, count = 0;
	patient_t patient_lib[MAX_NUM_PATIENTS];

    while(choice != 6)
    {
        print_menu();
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                printf("Adding patient...\n");
				if(count < MAX_NUM_PATIENTS)
				{	
	                add_patient(patient_lib, count);
					count++;
				}
				else
				{
					printf("Hospital is full.\n");
				}
                
                break;
            case 2:
                printf("Displaying patient...\n");
                break;
            case 3:
                printf("Updating patient info...\n");
                break;
            case 4:
                printf("Saving patient info...\n");
                save_patient(patient_lib, count);
                break;
            case 5:
                printf("Loading patient info...\n");
                break;
            case 6:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    }
    return 0;
}
/*******************************************************************************
	End Main
*******************************************************************************/

/*******************************************************************************
	Function Definitions
*******************************************************************************/
void print_login()
{
  	printf("\n"
    "1. Login\n"
    "2. Exit\n"
    "Enter choice (number between 1-2)>\n");
}

void print_menu()
{
	  printf("\n"
    "1. add a patient\n"
    "2. display patient\n"
	"3. update patient information\n"
    "4. save the patients to the database file\n"
    "5. load the patients from the database file\n"
    "6. exit the program\n"
    "Enter choice (number between 1-6)>\n");
}

void add_patient(patient_t patient_lib[], int count)
{
/*==============================================================================
	Declare Variables
==============================================================================*/
	char temp_YN[5];
/*==============================================================================
	Request patients surname and first name. Can be used later on to search
	for patients in database.
==============================================================================*/
    printf("Enter their surname, then their first name, seperated by a space> ");
    scanf("%s %s", patient_lib[count].surname, patient_lib[count].firstname);

        printf("\nPatients name is %s %s\n", patient_lib[count].surname, 
                                             patient_lib[count].firstname);
/*==============================================================================
	Request patients age, weight and height.
==============================================================================*/
    printf("Enter their age, weight and height, seperated by a space> ");
    scanf("%d %d %d", &patient_lib[count].age,
                      &patient_lib[count].weight,
                      &patient_lib[count].height);

        printf("\nAge: %d, Weight: %d, Height: %d\n",
                       patient_lib[count].age,
                       patient_lib[count].weight,
                       patient_lib[count].height);
/*==============================================================================
	Request patients arrival time. This allows nurses to keep track of when
	patients arrive, and how long they have been in the hospital for.
==============================================================================*/
    printf("Enter their time of admission into the hospital.\n");
    printf("Enter day, month, year, hour and minute seperated by spaces> ");
    scanf("%d %d %d %d %d", &patient_lib[count].arrival_dt.day,
                            &patient_lib[count].arrival_dt.month,
                            &patient_lib[count].arrival_dt.year,
                            &patient_lib[count].arrival_dt.hour,
                            &patient_lib[count].arrival_dt.min);
        printf("\nArrival information:\n");
        printf("Day: %d\nMonth: %d\nYear: %d\nHour: %d\nMinute: %d\n", 
				patient_lib[count].arrival_dt.day,
                patient_lib[count].arrival_dt.month,
 				patient_lib[count].arrival_dt.year,
				patient_lib[count].arrival_dt.hour,
				patient_lib[count].arrival_dt.min);
/*==============================================================================
	Request patients location within hospital. This allows nurses to be aware
	of where patients are located. This location will also be updatable.
==============================================================================*/
    printf("Enter the patients admission location.\n");
    printf("Enter the department they are being sent to, using all caps> ");
    scanf("%s", patient_lib[count].location_dt.department);

        printf("\n%s\n", patient_lib[count].location_dt.department);

    printf("Enter the floor level they are being sent to, between %d - %d> \n",
            LEVEL_MIN, LEVEL_MAX);
    scanf("%d", &patient_lib[count].location_dt.level);

        printf("\n%d\n", patient_lib[count].location_dt.level);

    printf("Enter the room number they are being sent to> ");
    scanf("%d", &patient_lib[count].location_dt.room);

        printf("\n%d\n", patient_lib[count].location_dt.room);
/*==============================================================================
	Request patient information regarding what medicine they are required to
	take.
==============================================================================*/
    printf("Enter patients medicine information.\n");
    printf("Enter the name of the medicine, using all caps> ");
    scanf("%s", patient_lib[count].diagnosis.med);

        printf("\nMedicine name is %s\n", patient_lib[count].diagnosis.med);

    printf("Enter how many times the medicine is to be taken daily> ");
    scanf("%d", &patient_lib[count].diagnosis.times);

        printf("\nThe medicine is to be taken %d times per day.\n", 
		patient_lib[count].diagnosis.times);

    printf("Enter the dosage amount in milligrams> ");
    scanf("%d", &patient_lib[count].diagnosis.dose);

        printf("\nDosage amount is %d\n", patient_lib[count].diagnosis.dose);
/*==============================================================================
	Request patients departure time.
==============================================================================*/
   	printf("Has the patient been released from the hospital?\n");
	printf("Enter 'YES' or 'NO' in all caps.\n");
	scanf("%s", temp_YN);
	if(strcmp(temp_YN, "YES") == 0)
	{
		printf("Enter the patients time of departure from the hospital.\n");
   		printf("Enter day, month, year, hour and minute seperated by spaces> ");
    	scanf("%d %d %d %d %d", &patient_lib[count].departure_dt.day,
                            &patient_lib[count].departure_dt.month,
                            &patient_lib[count].departure_dt.year,
                            &patient_lib[count].departure_dt.hour,
                            &patient_lib[count].departure_dt.min);

        printf("\nDeparture information:\n");
        printf("Day: %d\nMonth: %d\nYear: %d\nHour: %d\nMinute: %d\n", 
							patient_lib[count].departure_dt.day,
                            patient_lib[count].departure_dt.month,
                            patient_lib[count].departure_dt.year,
                            patient_lib[count].departure_dt.hour,
                            patient_lib[count].departure_dt.min);
	}
	else if (strcmp(temp_YN, "NO") == 0)
	{
		printf("End of Input.\n");
	}
	else
	{
		printf("Invalid input.\n");
	}
}

/*******************************************************************************
 * This function stores the data to the database file
 * 
 * inputs:
 * - 
 * outputs:
 * - none
*******************************************************************************/
void save_patient (patient_t patient_lib[], int count)
{
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

    /* Saves number of patients */
    fprintf(fp, "%d\r\n", count);


/* Loop for saving each flight stored */
    for (i = 0; i < count; i++)
    {
    fprintf(fp, "%s ", patient_lib[i].surname);
    fprintf(fp, "%s ", patient_lib[i].firstname);

    fprintf(fp, "%d %d %d ", patient_lib[i].age, 
    						patient_lib[i].weight, 
    						patient_lib[i].height);
    
    fprintf(fp, "%d %d %d %d %d ", patient_lib[i].arrival_dt.day,
                            patient_lib[i].arrival_dt.month,
                            patient_lib[i].arrival_dt.year,
                            patient_lib[i].arrival_dt.hour,
                            patient_lib[i].arrival_dt.min);
    
    fprintf(fp, "%s ", patient_lib[i].location_dt.department);
    fprintf(fp, "%d ", patient_lib[i].location_dt.level);
    fprintf(fp, "%d ", patient_lib[i].location_dt.room);

    fprintf(fp, "%d %d %d %d %d\r\n", patient_lib[i].departure_dt.day,
                            		patient_lib[i].departure_dt.month,
                            		patient_lib[i].departure_dt.year,
                            		patient_lib[i].departure_dt.hour,
                            		patient_lib[i].departure_dt.min);

	}

    /* Closes text file */
    fclose(fp);
    
}

