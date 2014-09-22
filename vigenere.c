#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	if(argc != 4)
	{
		printf("Usage: vigenere -d[ecrypt]|-e[ncrypt] <Key> <Message>\r\n");
		return -1;
	}
	
	int key_len = strlen(argv[2]);
	
	if(key_len <= 0)
	{
		printf("Please provide a valid key.\r\n");
		return -1;
	}
	
	char* key = malloc(sizeof(char)*key_len);
	if(!key)
	{
		printf("Malloc failed. Please make sure enough memory is available.\r\n");
		return -1;
	}
	
	memset(key, 0, key_len);
	strcpy(key, argv[2]);
	
	int len = strlen(argv[3]);
	
	if(len <= 0)
	{
		printf("Please provide a valid message.\r\n");
		return -1;
	}
	
	
	char* input = malloc(sizeof(char)*len);
	if(!input)
	{
		printf("Malloc failed. Please make sure enough memory is available.\r\n");
		return -1;
	}
	
	memset(input, 0, len);
	strcpy(input, argv[3]);
	
	int y;
	for(y = 0; y < len; y++)
	{
		if(input[y] < 65 || (input[y] > 90 && input[y] < 97) || (input[y] > 122))
		{
			printf("Message does not contain valid characters!\r\n");
			return -1;	
		}
		
		if(input[y] >= 97 && input[y] <= 122)
			input[y] = input[y]-32;
		
	}
	
	int x;
	int modifier = (argv[1][1] == 'd' ? -1 : 1);
	int val = 0;
	for(x = 0; x < len; x++)
	{
		val = (((input[x]-65)+(modifier*(key[x%key_len]-65)))%26);
		while(val < 0)
			val += 26;
		input[x] = val+65;
	}
	
	printf("Input: %s\r\nKey: %s\r\nOutput:%s\r\n", argv[3], argv[2], input);
	free(key);
	free(input);
}
