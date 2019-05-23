#include <stdio.h>
#include <string.h>

int enter_choice();
int enter_choice2();
int enter_choice3();



int main(void)
{

enter_choice();
    
return 0;
 
}
void print_menu (void)
{
	printf("***************************************\n");
    printf(" WELLCOME TO THE HOSPITAL DATABASE \n");
    printf("***************************************\n");
    printf(" Please select the an option below \n");
    printf("\n"
     "--------------------------------\n"
    "1. Login \n"
    "2. Exit the program \n"
	 "--------------------------------\n");
}

void print_menu2 (void) /* menu in login */
{
    printf("\n"
    "--------------------------------\n"
    "1. Add new patient \n"
    "2. Display patients \n"
    "3. Load patients \n"
    "4. Save patients \n"
    "5. Update info \n"   /* update location and current medication */
    "6. Back to login menu \n"
	"--------------------------------\n");
}

void print_menu3 (void)
{
    printf("\n"
    "--------------------------------\n"
    "1. Update patient location \n"
    "2. Update patient medication \n" 
    "3. Back to options menu \n"
	"--------------------------------\n");
}





/* login menu */
int enter_choice()
{
	
 	int number;
    while(number<1 || number >2)
    {
     print_menu();
     scanf("%d",&number);
     switch(number)
     {
       case 1:
       	enter_choice2();
        
		break;
       
	   case 2:  
        
		break;     
		
		default: 
			printf("Invalid choice\n");	
			printf("Please enter number 1 or 2 \n");	
    }
   }
   return 0;
}

/* inside the first choice */

int enter_choice2()
{
	
 	int number2;
    while(number2<1 || number2 >6)
    {
     print_menu2();
     scanf("%d",&number2);
     switch(number2)
     {
       case 1:
       	
        
		break;
       
	   case 2:  
        
		break;
		
	   case 3:
       	
        break;
       
	   case 4:  
        
		break;	
	   case 5:  
        enter_choice3();
		break;		  
	   
	   case 6: 
		enter_choice(); /* return back to the menu */
		break;
		
		default: 
			printf("Invalid choice\n");	
			printf("Please enter number between 1 and 6\n");
    
	}
   }
   return 0;
}


int enter_choice3() /* update patients info */
{
	
 	int number3;
    while(number3<1 || number3>3)
    {
     print_menu3();
     scanf("%d",&number3);
     switch(number3)
     {
       case 1:
        
		break;
       
	   case 2:  
        
		break;
		
		case 3: 
		enter_choice2(); /*back to the options menu */
        
		break;      
		
		default: 
			printf("Invalid choice\n");	
			printf("Please enter number between 1 and 3 \n");	
    }
   }
   return 0;
}

