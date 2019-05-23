#include <stdio.h>
#include<string.h>
#include<math.h>


int main(void){
	
	char password[100];
	char storepassword[100];
	int i, j; 
	int length; 
	int countdup;

	
	printf("Enter a password>\n");
	scanf("%s", password);
	
	length = strlen(password);
	strcpy(storepassword, password);


	
	for( i= 0; i < length ; i++)
	{		
		countdup = 1;
	
		for(j = i + 1; j < length + 1; j++ )
		{
			if(password[i] == password[j])
			{
				countdup++;
				password[j] = '0';
			
			}				
				
			else if ( password[i]!='0' && password[i] != password[j])
			{					
				printf("%c", password[i]);
			
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
