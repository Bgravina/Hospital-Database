#include <stdio.h>
#include<string.h>
#include<math.h>


int main(void){
	
	char password[100];
	char storepassword[100];
	int i, j; 
	int length; 
	int countdup;

/* enter the string needed to compress */
	printf("Enter a password>\n");
	scanf("%s", password);
/* get the length of the string */	
	length = strlen(password);
	
/* as the string is a combination of characters and '\0' at the end *
/* the program will compare the first digit with the one next to it, including '\0' */

	
	for( i= 0; i < length ; i++)
	{		
		/* the duplicate is set to 1 */
		/* it will start counting if the next one is the same as the previous one and set coundup to 2 */
		countdup = 1;
	
		for(j = i + 1; j < length + 1; j++ )
		{
			/* when the digit is the same as the digit next to it */
			if(password[i] == password[j])
			{
				/* increase the countdup if there is a duplicate digit */
				countdup++;
				/* make the comprared digit '\0' */
				password[j] = '0';
			
			}				
			/* when two digit is different */	
			else if ( password[i]!='0' && password[i] != password[j])
			{	
				/* print out the digit */				
				printf("%c", password[i]);
				/* if the digit is more than one, the program will print the number after it*/
				/* otherwise, it will just print the digit it self if there is no duplicate */
				if(countdup > 1)
				{
					printf("%d", countdup);
				}
				password[i] = '0';				
			}
				
		}
		
	}
	

	
	
	return 0;
	
	
	
	
	
	
	
	
	
	
}
