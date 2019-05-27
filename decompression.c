#include <stdio.h>
#include<string.h>
#include<math.h>


int main(void){
	
	char password[100];
	char storepassword[100];
	int i, j, k; 
	int length; 
	int countdup;
/* enter the string needed for decompress */	
	printf("Enter a string >\n");
	scanf("%s", password);
/* get the length of the string */	
	length = strlen(password);

	
	
/* as the string is a combination of characters and '\0' at the end */

/* the program will compare the first digit 
with the one next to it, including '\0' */
	
	
	
	
	for( i= 0; i < length ; i++)
	{		

		for(j = i + 1; j < length + 1; j++ )
		{
			/* if the digit needed to compare is a number after a word */ 
			if(  (password[j] >= '0') && (password[j] <= '9' ))
			{
				/* change the number in the string into a single number */
				int x = password[j] - '0';
				/* when that number is greater than 1 */
				if ( x > 1)
				{
					
				 /* printing the digit corresponding to the number after it */
				 
					for( k = 0 ; k < x  ; k ++ )
					{
						printf("%c", password[i]);
					}
				
				}
				
			}
			
			/* when their is a word after a digit, 
    the program will look at that and the end to determine to print the word */
	 
			else if ( (password[i] <= '0' || password[i] >= '9') || 
					( (password[j] <= '0' || password[j] >= '9') && 
					( password [j] != 0) &&( password [i] == 0) ) )
			{
					printf("%c", password[i]);
			}
			
			/* increment the comparasion digit as it should be 
			comparing between every single one */
			
			i = i + 1;
				
			
		}
	}
	


	

	

	
	
	return 0;
	
	
	
	
	
	
	
	
	
	
}
