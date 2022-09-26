#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char **createTable() {
	char** table = malloc(26*sizeof(char*));
	for(int i = 0; i < 26; i++)
		table[i] = malloc(26*sizeof(char));

	for(int a = 0; a < 26; a++){
		for(int b = 0; b < 26; b++){
			int i = 65 + a + b;
			if(i > 90){
				i -= 26;
			}
			table[a][b] = i;
		}
		
	}
	return table;
}

void printTable(char **table) {
	for(int a = 0; a < 26; a++){
		for(int b = 0; b < 26; b++)
			printf("%c", table[a][b]);
		printf("\n");
	}
	printf("\n");
}

char *encrypt(char *str, char **table, char *key) {
	int len = strlen(str);
	char *out = malloc(len*(sizeof(char)));

	for(int i = 0; i < len; i++){
		out[i] = table[str[i]-65][key[i]-65];
	}
	return out;
}

char *decrypt(char *str, char **table, char *key) {
	int len = strlen(str);
	char *out = malloc(len*(sizeof(char)));

	for(int i = 0; i < len; i++){
		for(int b = 0; b < 26; b++){
			if( table[key[i]-65][b] == str[i]){
				out[i] = table[0][b];
			}
		}
	//out[-1] = 0;
	}
	return out;
}

int main() {
	char **table = createTable();
	printTable(table);
	
	char *str = "BCDC";
	char *key = "DACB";

	char *encrypted = encrypt(str, table, key);
	
	printf("Encrypted:\t%s\n", encrypted);

	printf("Decrypted:\t%s\n", decrypt(encrypted, table, key));
	
	return 0;
}




























