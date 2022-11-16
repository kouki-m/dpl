#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


char *extend(char *message){
	int len, len_mod, i;
	char *tmp;

	len = strlen(message);
	len_mod = strlen(message) % 64;
	if (len < 56){
		tmp = (char *)malloc(sizeof(char) * (len + 64 - len_mod + 1));
	} else {
		tmp = (char *)malloc(sizeof(char) * (len + 128 - len_mod + 1));
	}
	strcpy(tmp, message);
	i = 0;
	while (i < len){
		i++;
	}
	tmp[i] = 0x80;
	printf("%d\n", 56 - len_mod - 1);
	printf("%d\n", len + 120 - len_mod + 1);
	if (len < 56){
		for (int j = 0; j < 56 - len_mod; j++){
			tmp[i++] = '\0';
		}
	} else {
		for (int j = 0; j < 120 - len_mod; j++){
			tmp[i++] = '\0';
		}
	}
	printf("%d\n", i);
	return tmp;
}

int main(int argc, char *argv[]){
	char *str;

	str = extend(argv[1]);
	printf("%s", str);
	return 0;
}