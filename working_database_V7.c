/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * Members:
 *  	Bailey Gravina		  	|13253137
 *		Joven Garcia			|13197189
 *		Khanh Truong			|12879654
 *		Shaheen Reza			|12794780
 *
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
#define KEY 'K'				/* Key for encrypting and decrypting data */
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
		int month, day, year, hour, minute;
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


/*******************************************************************************
	Function Prototypes
*******************************************************************************/

/*==============================================================================
	Database prototypes: Main prototypes used for managing database.
==============================================================================*/
	/* Lets the user log into the program */
	int logon(); 				
	
	/* Prints title of the program at the start */
	void print_title(void);
	
	/* Prints login menu for user */
	void print_login(void);
	
	/* Prints menu for selecting a specfic function of the program */
	void print_menu(void);
	
	/* Adds a new patient */
	void add_patient(patient_t patient_lib[], int count);

	/* Updates information of patient */
	void update_patient (patient_t patient_lib[], int count);
	
	/* Displays patient(s) profile */
	void display_patient(patient_t patient_lib[], int count);
	
	/* Encrypts or decrypts database data */
	void encrypt_decrypt (patient_t patient_lib[], int count);
	
	/* compresses database data */
	void compress(); 							  
	
	/* Saves database to text file */
	void save_patient(patient_t patient_lib[], int count);
	
	/* Loads database from text file */
	int load_patient(patient_t patient_lib[], int count);

	/* Sorts patient's in alphabetical order */
	void bubble_sort(patient_t patient_lib[], int count);


/*==============================================================================
	Patient's information prototypes: Secondary prototypes for adding and
	updating patient's information
==============================================================================*/
	void patient_name(patient_t patient_lib[], int count);
	void patient_measurements(patient_t patient_lib[], int count);
	void patient_arrival_time(patient_t patient_lib[], int count);
	void patient_location(patient_t patient_lib[], int count);
	void patient_medication(patient_t patient_lib[], int count);
	void patient_depature_time(patient_t patient_lib[], int count);
	void print_debug(int count, valid);


/*==============================================================================
	Valid user input prototypes: Secondary prototypes for ensuring proper user
	input.
==============================================================================*/
	int valid_fullname(patient_t patient_lib[], int count);
	int valid_time_info(date_time_t date_time_dt);
	int valid_measurement(patient_t patient_lib[], int count);
	int valid_location(location_t location_dt);
	int valid_department(location_t location);
	int valid_level(location_t location);
	int valid_room(location_t location);
	int valid_med(diagnosis_t diagnosis);
	int valid_med_time(diagnosis_t diagnosis);
	int valid_med_dosage(diagnosis_t diagnosis);

/*==============================================================================
	Request patients location within hospital. This allows nurses to be aware
	of where patients are located. This location will also be updatable.
==============================================================================*/
/*******************************************************************************
	Main
*******************************************************************************/
int main(void)
{
	/* Initialise variable for menu selection */
	int choice = 0;
	
	/* Initialise variable for storing number of patients */
	int count = 0;
	
	/* Declare variable for patient structure data type */
	patient_t patient_lib[MAX_NUM_PATIENTS];

	/* Prints title of the program */
	print_title();

	/* Stays within while loop when user hasn't selected login 
	or exit program */
	while(choice != 1)
	{
		/* Prints login menu for user */
		print_login();

		/* Gets user's input and stores it in 'choice' */
		scanf("%d", &choice);

		/* Switch case for determining to login or exit the program */
		switch(choice)
       	{	
       		/* This case lets the user login */
       		case 1:
				break;
       
       		/* This case lets the user log out of the program */
	    	case 2:
	    		/* Informs the user that they're exiting the program */
	    		printf("Exiting program...\n");
	    		return 0;  
		
			/* The default case for when the user inputs an invalid input */
			default:
				/* Informs the user that their selection is an invalid choice
				and request them to input either a 1 or 2 */ 
				printf("Invalid choice\n");	
				printf("Please enter number 1 or 2 \n");	
		}
	}


	/* Stays within while loop while the user hasn't inputed a valid input
	for selecting the feature to run or exit program feature*/
    while(choice != 6)
    {
    	/* Prints selection menu for user */
        print_menu();

        /* Gets user's input and stores it in 'choice' */
        scanf("%d", &choice);

        /* Switch case for determining which feature to run */
        switch(choice)
        {
        	/* This case lets the user add a patient */
            case 1:
            	/* Informs the user the function is running */
                printf("Adding patient...\n");

                /* Checks to see if maximum amount of patients has
                been reached */
				if(count < MAX_NUM_PATIENTS)
				{	
					/* User defined function to add a patient and thier
					information */
	                add_patient(patient_lib, count);

	                /* Increments the count variable to keep track of
	                the number of patients have been recorded */
					count++;
				}

				else
				{
					/* Informs the user that the max capactiy has
					been reached */
					printf("Hospital is full.\n");
				}

                break;

            /* This case lets the user display patient(s) information */    
            case 2:
            	/* Informs the user the function is running */
                printf("Displaying patient info...\n");

                /* User defined function to display patient(s) information */
                display_patient(patient_lib, count);

                break;

            /* This case allows the user to update a particular patient's
            information */    
            case 3:
            	/* Informs the user the function is running */
                printf("Updating patient info...\n");

                /* User defined function to update patient's information */
                update_patient(patient_lib, count);

                break;

            /* This case allows the user to save the patients' information
            to a text file database */    
            case 4:
            	/* Informs the user the function is running */
                printf("Saving patient info...\n");

                /* Encrypts the data before saving it to the database */
                encrypt_decrypt(patient_lib, count);

                /* Saves the encrypted data to the database text file */
                save_patient(patient_lib, count);

                /* Decrypts the data so it can be displayed correctly if
                display patients is selected afterwards */
                encrypt_decrypt(patient_lib, count);

                break;
            
            /* This case allows the user to load the patients' information
            from a text file database */
            case 5:
            	/* Informs the user the function is running */
                printf("Loading patient info...\n");

                /* Loads the encrypted data from the database text file
                and the number of patients in the database */
                count = load_patient(patient_lib, count);

                /* Decrpts the data that was loaded */
                encrypt_decrypt(patient_lib, count);

                break;

            /* This case allows the user to exi the program */    
            case 6:
            	/* Informs the user they're exiting the program */
                printf("Exiting program...\n");

                break;

            /* This case is for debugging purposes */    
            case 7:
            	printf("Sorting...\n");
            	bubble_sort(patient_lib, count);
            	break;

            /* The default case for when the user inputs an invalid input */
            default:
                /* Informs the user that their selection is an invalid
                choice */
                printf("Invalid choice\n");

                break;
        }
		print_debug();
    }
    return 0;
}


/*******************************************************************************
	Function Definitions
*******************************************************************************/

/*******************************************************************************
 * Displays the title at the start of the program for the user.
*******************************************************************************/
void print_title(void)
{
	printf("***************************************\n");
    printf(" WELLCOME TO THE HOSPITAL DATABASE \n");
    printf("***************************************\n");
}


/*******************************************************************************
 * Displays the login menu for the user.
*******************************************************************************/
void print_login(void)
{
  	printf("\n"
    "1. Login\n"
    "2. Exit\n"
    "Enter choice (number between 1-2)>\n");
}


/*******************************************************************************
 * Displays the menu to select which feature/function to run.
*******************************************************************************/
void print_menu(void)
{
	printf("\n"
    "1. Add a patient\n"
    "2. Display patient\n"
	"3. Update patient information\n"
    "4. Save the patients to the database file\n"
    "5. Load the patients from the database file\n"
    "6. Exit the program\n"
    "7. Sort data (wip)\n"
    "Enter choice (number between 1-7)>\n");
}


/*******************************************************************************
 * Displays the menu to select which feature/function to run.
*******************************************************************************/
void print_update_menu(void)
{
	printf("\n"
    "1. Update patient's age, weight and height\n"
    "2. Update patient's location\n"
	"3. Update patient's medication\n"
    "4. Update patient's depature information\n"
    "5. Return to main menu\n"
    "Enter choice (number between 1-5)>\n");
}

/*******************************************************************************
 * Request patients surname and first name. Can be used later on to search
 * for patients in database.
*******************************************************************************/
void patient_name(patient_t patient_lib[], int count)   
{    
    printf("Enter their surname in all captials, then their first name,"
            "in seperated by a space> \n");
    
    /* Loops scanf function till a valid input is entered by the user */
    do
    {
        /* Stores the patient's surname and first name */
        scanf("%s %s", patient_lib[count].surname, 
                    patient_lib[count].firstname);
    } while(valid_fullname(patient_lib, count) == 0);
}


/*******************************************************************************
 * Request patients age, weight and height.
*******************************************************************************/
void patient_measurements(patient_t patient_lib[], int count)
{
   printf("Enter their age, weight and height, seperated by a space> \n");
   
    /* Loops scanf function till a valid input is entered by the user */
    do
    {
        /* Stores the patient's age, weight and height */
        scanf("%d %d %d", &patient_lib[count].age,
                      &patient_lib[count].weight,
                      &patient_lib[count].height);
    } while(valid_measurement(patient_lib, count) == 0); 
}


/*******************************************************************************
 * Request patients location within hospital. This allows nurses to be aware
 * of where patients are located. This location will also be updatable.
*******************************************************************************/
void patient_arrival_time(patient_t patient_lib[], int count)
{    
    printf("Enter their time of admission into the hospital.\n");

    /* Prompts the user to enter the patient's arrivial time in the following
    order */
    printf("Enter day, month, year, hour and minute seperated by spaces> \n");
    
    /* Loops scanf function till a valid input is entered by the user */
    do
    {
        /* Stores the patient's arrival day, month, year, hour and
        minute */
        scanf("%d %d %d %d %d", &patient_lib[count].arrival_dt.day,
                            &patient_lib[count].arrival_dt.month,
                            &patient_lib[count].arrival_dt.year,
                            &patient_lib[count].arrival_dt.hour,
                            &patient_lib[count].arrival_dt.minute);
    } while(valid_time_info(patient_lib[count].arrival_dt) == 0);
}


/*******************************************************************************
 * Request patients location within hospital. This allows nurses to be aware
 * of where patients are located. This location will also be updatable.
*******************************************************************************/
void patient_location(patient_t patient_lib[], int count)
{    
    printf("Enter the patients admission location.\n");

    /* Prompts the user to enter the patient's location */
    printf("Enter the department they are being sent to, using all caps> \n");
    
    /* Loops scanf function till a valid input is entered by the user */
    do
    {
        /* Stores which department the patient is in */
        scanf("%s", patient_lib[count].location_dt.department);
    } while(valid_department(patient_lib[count].location_dt) == 0);

    
    /* Prompts the user to enter which level they're in */
    printf("Enter the floor level they are being sent to, between %d - %d> \n",
            LEVEL_MIN, LEVEL_MAX);
    
    /* Loops scanf function till a valid input is entered by the user */
    do
    {
        /* Stores which level the patient is in */
        scanf("%d", &patient_lib[count].location_dt.level);
    } while(valid_level(patient_lib[count].location_dt) == 0);

    /* Prompts the user to enter which room they're in */
    printf("Enter the room number they are being sent to> \n");
    
    /* Loops scanf function till a valid input is entered by the user */
    do
    {
        /* Stores the room number the patient is in */
        scanf("%d", &patient_lib[count].location_dt.room);
    } while(valid_room(patient_lib[count].location_dt) == 0);
}


/*******************************************************************************
 * Request patient information regarding what medicine they are required to
 * take.
*******************************************************************************/
void patient_medication(patient_t patient_lib[], int count)
{
    printf("Enter patients medicine information.\n");

    /* Prompts the user to enter the medication they're taking */
    printf("Enter the name of the medicine, using all caps> ");
    
    /* Loops scanf function till a valid input is entered by the user */
    do
    {
        /* Stores the medicine the patient has been prescribed */
        scanf("%s", patient_lib[count].diagnosis.med);
    } while(valid_med(patient_lib[count].diagnosis) == 0);

    /* Prompts the user to enter how frequently they have to take their
    prescribed medicine */
    printf("\nEnter how many times the medicine is to be taken daily> \n");
    
    /* Loops scanf function till a valid input is entered by the user */
    do
    {
        /* Stores the amount of the times per day the patient has to
        take the prescribed medicine */
        scanf("%d", &patient_lib[count].diagnosis.times);
    } while(valid_med_time(patient_lib[count].diagnosis) == 0);

    /* Prompts the user to enter the dosage of their medication */
    printf("\nEnter the dosage amount in milligrams> \n");
    
    /* Loops scanf function till a valid input is entered by the user */
    do
    {
        /* Stores the dosage of the prescribed medicine */
        scanf("%d", &patient_lib[count].diagnosis.dose);
    } while(valid_med_dosage(patient_lib[count].diagnosis) == 0);
}


/*******************************************************************************
 * Request patient's departure time.
*******************************************************************************/
void patient_depature_time(patient_t patient_lib[], int count)
{
    /* Declare Variable */
    char temp_YN[5];

    /* Asks the user if the patient has been discharged yet */
    printf("Has the patient been released from the hospital?\n");
    
    /* Asks the user to enter either yes or no in all capital letters */
    printf("Enter 'YES' or 'NO' in all caps.\n");
    
    /* Stores the choice that the user has entered */
    scanf("%s", temp_YN);

    /* Checks to see if the user has inputed 'YES' */
    if(strcmp(temp_YN, "YES") == 0)
    {
        /* Request the user to enter the patient's depature time if
        they inputed yes to the previous question */
        printf("Enter the patients time of departure from the hospital.\n");
        
        /* Asks the user to enter the day, month, year, hour and minute
        that they were discharged from the hospital */
        printf("Enter day, month, year, hour and minute seperated by spaces> ");
        
        /* Loops scanf function till a valid input is entered by the user */
        do
        {
            /* Stores the time that the patietn was discharged */
            scanf("%d %d %d %d %d", &patient_lib[count].departure_dt.day,
                            &patient_lib[count].departure_dt.month,
                            &patient_lib[count].departure_dt.year,
                            &patient_lib[count].departure_dt.hour,
                            &patient_lib[count].departure_dt.minute);
        } while(valid_time_info(patient_lib[count].departure_dt) == 0); 
    }

    /* Checks to see if the use user has inputed 'NO' */
    else if (strcmp(temp_YN, "NO") == 0)
    {
        /* Informs the user that the add paitent feature has been completed */
        printf("End of Input.\n");
    }

    /* The default case if neither YES or NO has not been entered */
    else
    {
        /* Informs the user that the input that they entered is invalid */
        printf("Invalid input.\n");
    }
}


/*******************************************************************************
 * Adds a new patient to the patient_lib structure and increments the number
 * of patients (count) by 1
*******************************************************************************/
void add_patient(patient_t patient_lib[], int count)
{
  /*==============================================================================
	Request patients surname and first name. Can be used later on to search
	for patients in database.
  ==============================================================================*/
	patient_name(patient_lib, count);


  /*============================================================================
	Request patients age, weight and height.
  ============================================================================*/
    patient_measurements(patient_lib, count);


  /*============================================================================
	Request patients arrival time. This allows nurses to keep track of when
	patients arrive, and how long they have been in the hospital for.
  ============================================================================*/
    patient_arrival_time(patient_lib, count);


  /*============================================================================
	Request patients location within hospital. This allows nurses to be aware
	of where patients are located. This location will also be updatable.
  ============================================================================*/
    patient_location(patient_lib, count);
       

  /*============================================================================
	Request patient information regarding what medicine they are required to
	take.
  ============================================================================*/
    patient_medication(patient_lib, count);


  /*============================================================================
	Request patients departure time.
  ============================================================================*/
   	patient_depature_time(patient_lib, count);
}


/*******************************************************************************
 * Display Patient information
*******************************************************************************/
void update_patient (patient_t patient_lib[], int count)
{
	/* Initialise variable for menu selection */
	int choice = 0;

	/* Declares variable used to control loops */
    int i;

    /* Declares variable for user input to display patients */
    char code[MAX_NAME_LEN+1];

    /* Request the user to input patient's last name or * to display all
    flights stored */
    printf("Enter their surname, then their first name,"
            "seperated by a space> \n");

    /* Stores user's input to determine whether to display all patients or
    a patient with a specfic name */
    scanf(" %s", code);

	for (i = 0; i < count; i++)
    {
        /* Prints patient's details if user input matches their 
        last name */
        if (strcmp(code, patient_lib[i].surname) == 0)
        {
        	/* Stays within while loop while the user hasn't inputed 
        	a valid input for selecting the feature to run or exit program 
        	feature*/
    		while(choice != 5)
    		{
    			/* Prints selection menu for user */
        		print_update_menu();

        		/* Gets user's input and stores it in 'choice' */
        		scanf("%d", &choice);

        		/* Switch case for determining which feature to run */
        		switch(choice)
        		{
        			/* This case lets the user update the patient's
        			measurements */
            		case 1:
            			/* Informs the user the function is running */
            			printf("Updating patient's measurements...\n\n");

            			/* User defined function to change patient's
            			measurements */
            			patient_measurements(patient_lib, i);
                		
                		break;


            		/* This case lets the user update the patient's location */    
            		case 2:
            			/* Informs the user the function is running */
            			printf("Updating patient's location\n");

            			/* User defined function to change patient's
            			location */
            			patient_location(patient_lib, i);

                		break;


            		/* This case lets the user update the patient's
            		medication information*/    
            		case 3:
            			/* Informs the user the function is running */
            			printf("Updating patient's medication\n");

            			/*User defined function to change patient's
            			medication information */
            			patient_medication(patient_lib, i);

                		break;


            		/* This case allows the user update the patient's
            		depature information */    
            		case 4:
            			/*Informs the user the function is running */
            			printf("Updating patient's depature information\n");

            			/* User defined function to change patient's depature
            			time */
            			patient_depature_time(patient_lib, i);

                		break;
            

            		/* This case allows the user to return to the main menu */    
            		case 5:
            			/* Informs the user they're returning to the main
            			menu */
                		printf("Returning to main menu...\n");
                		
                		break;


            		/* The default case for when the user inputs an invalid input */
            		default:
                		/* Informs the user that their selection is an invalid
                		choice */
                		printf("Invalid choice\n");

                		break;
        		}

    		}
    	}
	}
}



/*******************************************************************************
 * Display Patient information
*******************************************************************************/
void display_patient (patient_t patient_lib[], int count)
{
	/* Declares variable for user input to display patients */
    char code[MAX_NAME_LEN+1];

    /* Initalises variable to compare user input to display all patients */
    char all_patients = '*';

    /* Declares variable used to control loops */
    int i;

    /* Initalises variable that keeps track of the number of patients
    displayed */
    int display = 0;

    /* Request the user to input patient's last name or * to display all
    flights stored */
    printf("Enter patient's last name or enter * to show all patients>\n");
    
    /* Stores user's input to determine whether to display all patients or
    a patient with a specfic name */
    scanf("%s", code);

    /* Regardless of input, if there are no patients stored, it will print
    the statement shown below */
    if (count == 0)
    {
        printf("No patients\n");  
    }

	/* If '*' is entered, it will display all patients */
    else if (code[0] == all_patients)
    {
    	/* Loop that list each patient stored in order */
        for (i = 0; i < count; i++)
        {
        	/* Displays the patient's last and first name in one line */
        	printf("%s %s\n", patient_lib[i].surname, 
        						patient_lib[i].firstname);

        	/* Displays the patient's age, weight and height in one line */
        	printf("Age: %d, Weight: %dkg, Height: %dcm\n",
        										patient_lib[i].age,
                       							patient_lib[i].weight,
                       							patient_lib[i].height);

        	/* Displays the patient's arrival information in one line */
        	printf("Arrived on ");
        	printf("%02d/%02d/%d at %02d:%02d\n", 
        							patient_lib[i].arrival_dt.day,
        							patient_lib[i].arrival_dt.month,
        							patient_lib[i].arrival_dt.year,
        							patient_lib[i].arrival_dt.hour,
        							patient_lib[i].arrival_dt.minute);

        	/* Displays the patient's location when they arrived in the
        	hospital in one line */
        	printf("Location in ");
        	printf("%s at Level: %d  Room: %d\n", 
        						patient_lib[i].location_dt.department,
        						patient_lib[i].location_dt.level,
        						patient_lib[i].location_dt.room);

        	/* Displays the patient's prescribed medicine in one line */
        	printf("Prescribed Medicine: ");
        	printf("%s %dmg %d times per day\n\n", 
        						patient_lib[i].diagnosis.med,
        						patient_lib[i].diagnosis.dose,
        						patient_lib[i].diagnosis.times);
        }
    }

    /* Condition for displaying a patient with a specific name */
    else
    {
    	/* Compares input entered with all last names stored stored */
        for (i = 0; i < count; i++)
        {
            /* Prints patient's details if user input matches their 
            last name */
            if (strcmp(code, patient_lib[i].surname) == 0)
            {
            	/* Displays the patient's last and first name in one line */
            	printf("%s %s\n", patient_lib[i].surname, 
        						patient_lib[i].firstname);

            	/* Displays the patient's age, weight and height in one line */
        		printf("Age: %d, Weight: %dkg, Height: %dcm\n",
        										patient_lib[i].age,
                       							patient_lib[i].weight,
                       							patient_lib[i].height);
        		
        		/* Displays the patient's arrival information in one line */
        		printf("Arrival on: ");
        		printf("%02d/%02d/%d at %02d:%02d\n", 
        							patient_lib[i].arrival_dt.day,
        							patient_lib[i].arrival_dt.month,
        							patient_lib[i].arrival_dt.year,
        							patient_lib[i].arrival_dt.hour,
        							patient_lib[i].arrival_dt.minute);

        		/* Displays the patient's location when they arrived in the
        		hospital in one line */
        		printf("Location: ");
        		printf("%s Level: %d  Room: %d\n", 
        						patient_lib[i].location_dt.department,
        						patient_lib[i].location_dt.level,
        						patient_lib[i].location_dt.room);

        		/* Displays the patient's prescribed medicine in one line */
        		printf("Prescribed Medicine: ");
        		printf("%s %dmg %d times per day\n\n", 
        						patient_lib[i].diagnosis.med,
        						patient_lib[i].diagnosis.dose,
        						patient_lib[i].diagnosis.times);

        		/*Increments display variable by 1 */
        		display++;
        	}

        /* Condition if the user imput matched none of the names in the
        database text file */
        if (display == 0)
        {
        	printf("No patients\n");
        }

    	}
    }
}


/*******************************************************************************
 * This function stores the data to the database file
*******************************************************************************/
void save_patient (patient_t patient_lib[], int count)
{
	/* Initialisation of looping variable */
	int i = 0;

    FILE* fp = NULL;

    /* Opens textfile called database in write mode */
    fp = fopen("database.txt", "w");

    /* Exits the function if error occurs */
    if (fp == NULL)
    {
        /* Informs the user there is an error */
        printf("Read error\n");
        return;
    }

    /* Writes the number of patients and starts a new line in the databse
    text file */
    fprintf(fp, "%d\r\n", count);

	/* Loop for writing each patient to the database textfile. Each patient
	is saved to a new line */
    for (i = 0; i < count; i++)
    {	
    	/* Writes the patient's first and last name to the database
    	text file */
    	fprintf(fp, "%s\r\n", patient_lib[i].surname);
    	fprintf(fp, "%s\r\n", patient_lib[i].firstname);

    	/* Writes the patient's age, weight and height to the database
    	text file */
    	fprintf(fp, "%d %d %d ", patient_lib[i].age, 
    						patient_lib[i].weight, 
    						patient_lib[i].height);
    
    	/* Writes the patient's arrivial time and date to the database
    	text file */
    	fprintf(fp, "%d %d %d %d %d ", patient_lib[i].arrival_dt.day,
                            		patient_lib[i].arrival_dt.month,
                            		patient_lib[i].arrival_dt.year,
                            		patient_lib[i].arrival_dt.hour,
                           			patient_lib[i].arrival_dt.minute);
    	
    	/* Writes the patient's location in the hospital to the database
    	text file */
    	fprintf(fp, "%s ", patient_lib[i].location_dt.department);
    	fprintf(fp, "%d ", patient_lib[i].location_dt.level);
    	fprintf(fp, "%d ", patient_lib[i].location_dt.room);

    	/* Writes the patient's depature time and date if they have been
    	discharged from the hospital and starts a new line */
    	fprintf(fp, "%d %d %d %d %d\r\n", patient_lib[i].departure_dt.day,
                            			patient_lib[i].departure_dt.month,
                            			patient_lib[i].departure_dt.year,
                            			patient_lib[i].departure_dt.hour,
                            			patient_lib[i].departure_dt.minute);

	}

    /* Closes text file */
    fclose(fp);   
}


/*******************************************************************************
 * Reads the database file and puts the data into patient_lib.
*******************************************************************************/
int load_patient (patient_t patient_lib[], int count)
{
    /* Initialisation of looping variable */
    int i = 0;

    FILE* fp = NULL;

    /* Opens textfile called database in write mode */
    fp = fopen("database.txt", "r");

    /* Exits the function if error occurs */
    if (fp == NULL)
    {
        printf("Read error\n");
        return count;
    }

    /* Reads the number of patients and starts a new line in the databse
    text file */
    fscanf(fp, "%d\r\n", &count);

	/* Loop for reading each patient from the database textfile. A new line
	is started after reading a patient's information */
    for (i = 0; i < count; i++)
    {
    	/* Reads the patient's first and last name from the database
    	text file */
    	fscanf(fp, "%[^\n]\r\n", patient_lib[i].surname);
    	fscanf(fp, "%[^\n]\r\n", patient_lib[i].firstname);

    	/* Reads the patient's age, weight and height from the database
    	text file */
    	fscanf(fp, "%d %d %d ", &patient_lib[i].age, 
    							&patient_lib[i].weight, 
    							&patient_lib[i].height);
    
    	/* Reads the patient's arrivial time and date from the database
    	text file */
    	fscanf(fp, "%d %d %d %d %d ", &patient_lib[i].arrival_dt.day,
                            		&patient_lib[i].arrival_dt.month,
                            		&patient_lib[i].arrival_dt.year,
                            		&patient_lib[i].arrival_dt.hour,
                            		&patient_lib[i].arrival_dt.minute);
    
    	/* Reads the patient's location in the hospital from the database
    	text file */
    	fscanf(fp, "%s ", patient_lib[i].location_dt.department);
    	fscanf(fp, "%d ", &patient_lib[i].location_dt.level);
    	fscanf(fp, "%d ", &patient_lib[i].location_dt.room);

    	/* Reads the patient's depature time and date if they have been
    	discharged from the hospital and starts a new line */
    	fscanf(fp, "%d %d %d %d %d\r\n", &patient_lib[i].departure_dt.day,
                            		&patient_lib[i].departure_dt.month,
                            		&patient_lib[i].departure_dt.year,
                            		&patient_lib[i].departure_dt.hour,
                            		&patient_lib[i].departure_dt.minute);

	}

    /* Closes text file */
    fclose(fp);

    /* Returns the number of patients added to the patient_lib */
    return count;
}


/*******************************************************************************
 * This function encrypts and decrypts the string from the text file
*******************************************************************************/
void encrypt_decrypt (patient_t patient_lib[], int count)
{
	/* Declaring variables used for the loops in this function */
	int i, j;

	/* Declaring variable for string length */
	int string_len;

	/* Loop for encrypting/decrypting each patient's information */ 
	for (i = 0; i < count; i++)
	{
		/* Stores the length of the patient's last name */
		string_len = strlen(patient_lib[i].surname);
		
		/* Loop for encrypting/decrypting the patient's last name */
		for (j = 0; j < string_len; j++)
		{
			/* XORs each bit in the character with the bits of
			the key */
			patient_lib[i].surname[j] = patient_lib[i].surname[j] ^ KEY;
		}


		/* Stores the length of the patient's first name */
		string_len = strlen(patient_lib[i].firstname);
		
		/* Loop for encrypting/decrypting the patient's first name */
		for (j = 0; j < string_len; j++)
		{
			/* XORs each bit in the character with the bits of the key */
			patient_lib[i].firstname[j] = patient_lib[i].firstname[j] ^ KEY;
		}


		/* Encrypts/decrypts the patient's age, weight and height. This is 
		archeived by XORing each bit in the int data type with the bits of
		the key */
		patient_lib[i].age = patient_lib[i].age ^ KEY;
		patient_lib[i].weight = patient_lib[i].weight ^ KEY;
		patient_lib[i].height = patient_lib[i].height ^ KEY;


		/* Encrypts/decrypts the patient's arrival date and time. This is 
		archeived by XORing each bit in the int data type with the bits of
		the key */
		patient_lib[i].arrival_dt.day = 
		patient_lib[i].arrival_dt.day ^ KEY;
		
		patient_lib[i].arrival_dt.month = 
		patient_lib[i].arrival_dt.month ^ KEY;
		
		patient_lib[i].arrival_dt.year = 
		
		patient_lib[i].arrival_dt.year ^ KEY;
		patient_lib[i].arrival_dt.hour = 
		
		patient_lib[i].arrival_dt.hour ^ KEY;
		
		patient_lib[i].arrival_dt.minute =  
		patient_lib[i].arrival_dt.minute ^ KEY;


		/* Stores the length of the department for  */
		string_len = strlen(patient_lib[i].location_dt.department);
		for (j = 0; j < string_len; j++)
		{
			/* XORs each bit in the character with the bits of the key */
			patient_lib[i].location_dt.department[j] = 
			patient_lib[i].location_dt.department[j] ^ KEY;
		}

		/* Encrypts/decrypts the level and the room the patient is in. This is 
		archeived by XORing each bit in the int data type with the bits of
		the key */
		patient_lib[i].location_dt.level = 
		patient_lib[i].location_dt.level ^ KEY;

		patient_lib[i].location_dt.room =
		patient_lib[i].location_dt.room ^ KEY;


		/* Encrypts/decrypts patient's depature date and time. This is 
		archeived by XORing each bit in the int data type with the bits of
		the key */
		patient_lib[i].departure_dt.day = 
		patient_lib[i].departure_dt.day ^ KEY;

		patient_lib[i].departure_dt.month =
		patient_lib[i].departure_dt.month ^ KEY;

		patient_lib[i].departure_dt.year =
		patient_lib[i].departure_dt.year ^ KEY;

		patient_lib[i].departure_dt.hour =
		patient_lib[i].departure_dt.hour ^ KEY;

		patient_lib[i].departure_dt.minute = 
		patient_lib[i].departure_dt.minute ^ KEY;
	}
}


/*******************************************************************************
 * This function checks if the patient's full name is valid
*******************************************************************************/
int valid_fullname(patient_t patient_lib[],int count, valid_fullname_count)
{
    /* Delcares variable for the loops in this function */
    int i;
    	
    /* Declares variable for the length of the patient's surname and
    first name */
    int lenS, lenF;

    /* Delcares variable that determines if the user's input is valid
    or not */
    int valid_fullname;

    /* Stores the length of the patient's surname and first name */
  	lenS = strlen(patient_lib[count].surname);
 	lenF = strlen(patient_lib[count].firstname);

 	/* Loop for checking each character of lastname the user has entered */
  	for (i=0; i < lenS; i++)
  	{
  		/* Condition if one of the characters is not a capital letter */
      	if((patient_lib[count].surname[i] < 'A')
         ||(patient_lib[count].surname[i] > 'Z'))
      	{
      		/* Informs the user that the input is invalid */
        	printf("Invalid input.\n");
        	
        	/* Stores a 0 in the validation check which indicates the input
        	is invalid */
        	valid_fullname = 0;
			valid_fullname_count++;

        	/* Returns the value of the invalid input indicator */
        	return valid_fullname;
      	}
	}

	/* Condition for checking if the first character is not a capital letter
	for the first name */
	if((patient_lib[count].firstname[0] < 'A')
         ||(patient_lib[count].firstname[0] > 'Z'))
    {
      	/*Informs the user that the input is invalid */
        printf("Invalid input.\n");
        	
        /* Stores a 0 in the validation check which indicates the input
        is invalid */
        valid_fullname = 0;
        
       /* Returns a 0 value, indicating the input is invalid */
        return valid_fullname;
    }

    /* Loop for checking each character in the patients first name */
    for (i=1; i < lenF; i++)
  	{
  		/* Condition for checking if any of the characters are not
  		lower case letters */
      	if((patient_lib[count].firstname[i] < 'a')
         ||(patient_lib[count].firstname[i] > 'z'))
      	{
      		/* Informs the user that the input is invalid */
        	printf("Invalid input.\n");

        	/* Stores a 0 in the validation check which indicates the input
        	is invalid */
        	valid_fullname = 0;

        	/* Returns a 0 value, indicating the input is invalid */
        	return valid_fullname;
      	}
	}

	/* Stores a 1 in the validation check, which indicates the input is
	valid */
	valid_fullname = 1;

	/* Returns a value of 1, indicating the input is valid */
	return valid_fullname;  	
}


/*******************************************************************************
 * This function checks if the patient's arrival information is valid
*******************************************************************************/
int valid_time_info(date_time_t date_time_dt, int valid_time_count)
{
	/* Delcares variable that determines if the user's input is valid
    or not */
    int valid_tinfo;

    /* Condition to check if the date and time entered is invalid */
  	if ((date_time_dt.year < 2016)||(date_time_dt.year > 2020)
	  ||(date_time_dt.month < 1)||(date_time_dt.month > 12)
	  ||(date_time_dt.day < 1)||(date_time_dt.day > 31)
	  ||(date_time_dt.hour < 0 )||(date_time_dt.hour > 23)
	  ||(date_time_dt.minute < 0)||(date_time_dt.minute > 59))
	{
	 	/* Informs the user that the input is invalid */
   		printf("invalid input.\n");

   		/* Stores a 0 in the validation check which indicates the input
        is invalid */
		valid_tinfo = 0;
		valid_time_count++;
	}

	/* If condition is not met, then date and time entered is valid */
	else
	{
		/*Stores a value of 1 in the validation check, which indicates the
		input is valid */
		valid_tinfo = 1;
	}
	
	/* Returns the value stored in the validation check */
	return valid_tinfo;
}


/*******************************************************************************
 * This function checks if the measurements of the patient is valid
*******************************************************************************/
int valid_measurement(patient_t patient_lib[], int count, valid_measure_count)
{
	/* Delcares variable that determines if the user's input is valid
    or not */
    int valid_measure;

    /* Condition to check if the patient's measurements are invalid */
  	if ((patient_lib[count].age < 0)||(patient_lib[count].age > 150)||
     	(patient_lib[count].weight < 0)||(patient_lib[count].weight > 250)||
     	(patient_lib[count].height < 0)||(patient_lib[count].height > 250))
	{
		/* Informs the user that the input is invalid */
    	printf("invalid input.\n");

    	/* Stores a 0 in the validation check which indicates the input
        is invalid */
		valid_measure = 0;
		valid_measure_count++;
	}

	/* If condition is not met, then the values entered for the patient's
	measurements is valid */
  	else
    {
    	/*Stores a value of 1 in the validation check, which indicates the
		input is valid */
		valid_measure = 1;
    }

    /* Returns the value stored in the validation check */
	return valid_measure;
}


/*******************************************************************************
 * This function checks if the prescribed medicine entered is valid 
*******************************************************************************/
int valid_med(diagnosis_t diagnosis, int valid_med_count)
{
	/* Delcares variable that determines if the user's input is valid
    or not */
    int valid;

    /* Declares variable for the length of the string */
    int lenM;

    /* Delcares variable for the loop in this function */
    int i;
    
    /* Stores the length of the medication */
    lenM = strlen(diagnosis.med);

    /* Loop for checking each character of the medicine variable */
 	for (i=0; i < lenM; i++)
  	{
  		/* Condition if character is not a capital letter */
      	if((diagnosis.med[i] < 'A')
         ||(diagnosis.med[i] > 'Z'))
      	{
      		/* Informs the user that the input is invalid */
        	printf("Invalid input.\n");
        	
        	/* Stores a 0 in the validation check which indicates the input
        	is invalid */
        	valid = 0;
			valid_med_count++;
        	
        	/* Returns the value stored in the validation check */
        	return valid;
      	}
	}

	/*Stores a value of 1 in the validation check, which indicates the
	input is valid */
	
	valid = 1;

	/* Returns the value stored in the validation check */
	return valid;
}


/*******************************************************************************
 * This function checks if the amount of times the prescribed medicine is taken
 * per a day is valid
*******************************************************************************/
int valid_med_time(diagnosis_t diagnosis, int valid_med_time_count)
{
	/* Delcares variable that determines if the user's input is valid
    or not */
	int valid;

	/* Condition to check if the value entered is invalid */
	if ((diagnosis.times < 1)||(diagnosis.times > 6))
    {
		/* Informs the user that the input is invalid */
		printf("invalid input.\n");
		
		/* Stores a 0 in the validation check which indicates the input
        is invalid */
		valid = 0;
		valid_med_time_count++;
	}
  	
	/* If condition is not met, then the value entered is valid */
  	else
    {
    	/*Stores a value of 1 in the validation check, which indicates the
		input is valid */
	 	valid = 1;
    }

	/* Returns the value stored in the validation check */
	return valid;
}

/*******************************************************************************
 * This function checks if the dosage of the prescribed medicine is valid
*******************************************************************************/
int valid_med_dosage(diagnosis_t diagnosis, int valid_med_dose_count)
{
	/* Delcares variable that determines if the user's input is valid
    or not */
	int valid;

	/* Condition to check if the value entered is invalid */
	if ((diagnosis.dose < 1)||(diagnosis.dose > 500))
    {
		/* Informs the user that the input is invalid */
		printf("invalid input.\n");
		
		/* Stores a 0 in the validation check which indicates the input
        is invalid */
		valid = 0;
		valid_med_dose_count++;
	}
  	
	/* If condition is not met, then the value entered is valid */
  	else
    {
	 	/*Stores a value of 1 in the validation check, which indicates the
		input is valid */
	 	valid = 1;
    }

	/* Returns the value stored in the validation check */
	return valid;
}

/*******************************************************************************
 * This function checks if the department entered is valid
*******************************************************************************/
int valid_department(location_t location_dt, int valid_department_count)
{
    /* Declares variable for the department the patient has been sent to */
    int lenD;

    /* Delcares variable for the loop in this function */
    int i;

    /* Delcares variable that determines if the user's input is valid
    or not */
    int valid;
  	
    /* Stores the length of the string */
  	lenD = strlen(location_dt.department);

	/* Loop for checking each character of the string */
	for (i=0; i < lenD; i++)
  	{
   		/* Condition for checking if the character in the string is not
   		a capital letter */
   		if((location_dt.department[i] < 'A')
        	||(location_dt.department[i] > 'Z'))
		{
			/* Informs the user that the input is invalid */
			printf("invalid input.\n");
				
			/* Stores a 0 in the validation check which indicates the input
        	is invalid */
			valid = 0;
			valid_department_count++;
				
			/* Returns the value stored in the validation check */
			return valid;
		}
	}

	/*Stores a value of 1 in the validation check, which indicates the
	input is valid */
	valid = 1;

	/* Returns the value stored in the validation check */
	return valid;
}

/*******************************************************************************
 * This function checks if the level entered is valid
*******************************************************************************/
int valid_level(location_t location_dt, int valid_level_count)
{
	/* Delcares variable that determines if the user's input is valid
    or not */
	int valid;

	/* Condition to check if input is valid */
	if ((location_dt.level < LEVEL_MIN)||(location_dt.level > LEVEL_MAX))
	{
		/* Informs the user that the input is invalid */
		printf("invalid input.\n");
		
		/* Stores a 0 in the validation check which indicates the input
        is invalid */
		valid = 0;
		valid_level_count++;
	}

	/* If condition is not met, then the value entered is valid */
	else
	{
		/*Stores a value of 1 in the validation check, which indicates the
		input is valid */
		valid = 1;
	}
	
	/* Returns the value stored in the validation check */
	return valid;
}


/*******************************************************************************
 * This function checks if the room number entered is valid
*******************************************************************************/
int valid_room(location_t location_dt, int valid_room_count)
{
	/* Delcares variable that determines if the user's input is valid
    or not */
	int valid;

	/* Condition to check if input is valid */
	if ((location_dt.room < 0)||(location_dt.room > 200))
	{
		/* Informs the user that the input is invalid */
		printf("invalid input.\n");
		
		/* Stores a 0 in the validation check which indicates the input
        is invalid */
		valid = 0;
		valid_room_count++;
	}

	/* If condition is not met, then the value entered is valid */
	else
	{
		/*Stores a value of 1 in the validation check, which indicates the
		input is valid */
		valid = 1;
	}
	
	/* Returns the value stored in the validation check */
	return valid;
}
/*******************************************************************************
 * This function prints the debug menu
*******************************************************************************/
void print_debug(int valid_fullname_count, int valid_time_count
,int valid_measure_count, int valid_med_count, int valid_med_time_count
,int valid_med_dose_count,int valid_department_count,int valid_level_count
,int valid_room_count)
{
	printf("\n\n");
	printf("================================================================");
	printf("\nThis is the program run data\n");
	printf("================================================================");
	
	printf("\nThere was %d login attempts.\n", login_count);
/*******************************************************************************/
	printf("\nThe add patient function was used %d times.\n", add_patient_count);
	printf("\nWithin the add patient function, the following bugs occured:\n");
	printf("================================================================");
	printf("\nPatiens fullname was entered incorrectly %d times.\n", valid_fullname_count);
	printf("\nPatients arrival time was entered incorrectly %d times.\n", valid_time_count);
	printf("\nPatients age, weight or height was entered incorrectly %d times.\n", valid_measure_count);
	printf("\nPatients medicine information was entered incorrectly %d times.\n", valid_med_count);
	printf("\nPatients medicine times per day information was entered incorrectly %d times.\n", valid_med_time_count);
	printf("\nPatients medicine dosage was entered incorrectly %d times.\n", valid_med_dose_count);
	printf("\nPatients department location was entered incorrectly %d times.\n", valid_department_count);
	printf("\nPatients level location was entered incorrectly %d times.\n", valid_level_count);
	printf("\nPatients room location was entered incorrectly %d times.\n", valid_room_count);
	printf("================================================================");
/*****************************************************************************/
	printf("\nThe display patient function was used %d times.\n", display_patient_count);
	printf("\nWithin the display patient function, the following bugs occured:\n");
	printf("================================================================");
	printf("Invalid")

}
/*******************************************************************************
 * This function Sorts
*******************************************************************************/
void bubble_sort(patient_t patient_lib[], int count)
{
	int i, j;
	int comp;

	char temp[MAX_NAME_LEN+1];




/* comparing each string with the one next to it */ 
   for (i = 1; i < count; i++) 
   {
      for (j = 1; j < count; j++) 
	  {
	  	/* strcmp for comparing the ascii value of each characters to determine
	  	which one is greater */
	  	comp = strcmp(patient_lib[j-1].surname, patient_lib[j].surname);
	  	/* when the result is positive integrer */
        if ( comp > 0) {
        	/* copy the string into a temporary array */
            strcpy(temp, patient_lib[j-1].surname);
            /* replace the string with the one it was comprared with */
            strcpy(patient_lib[j-1].surname, patient_lib[j].surname);
            /* copy the value from the temporary to replace the other string */
            strcpy(patient_lib[j].surname, temp);

            /* copy the string into a temporary array */
            strcpy(temp, patient_lib[j-1].firstname);
            /* replace the string with the one it was comprared with */
            strcpy(patient_lib[j-1].firstname, patient_lib[j].firstname);
            /* copy the value from the temporary to replace the other string */
            strcpy(patient_lib[j].firstname, temp);

            
         }
      }
   }
}

