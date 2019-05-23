#include <stdio.h>
#include<string.h>
#include<math.h>


int main(void){
	
	char password[100];
	char storepassword[100];
	int i, j, k; 
	int length; 
	int countdup;

	
	printf("Enter a string >\n");
	scanf("%s", password);
	
	length = strlen(password);
	strcpy(storepassword, password);
	
	
	
	
	
	
	for( i= 0; i < length ; i++)
	{		

		for(j = i + 1; j < length + 1; j++ )
		{
			if(  (password[j] >= '0') && (password[j] <= '9' ))
			{
				
				int x = password[j] - '0';
				
				if ( x > 1)
				{
					for( k = 0 ; k < x  ; k ++ )
					{
						printf("%c", password[i]);
					}
				
				}
				
			}
			else if (  (password[i] <= '0' || password[i] >= '9') || ( (password[j] <= '0' || password[j] >= '9') && ( password [j] != 0) &&( password [i] == 0) ) )
			{
					printf("%c", password[i]);
			}
			
			i = i + 1;
				
			
		}
	}
	


	

	

	
	
	return 0;
	
	
	
	
	
	
	
	
	
	
}
