#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    static char count[128][128][128] = { 0 };
    int i, j, k;
    int fob = 0, sob = 0, tob = 0;
    long int size, size_2;
    const char* p;
    char* str, * str2;

    getchar();
    str = (char*)malloc(sizeof(char) * 100);
    scanf("%s", str);
    size = strlen(str);
    *(str + size) = '\0';
    printf("%s", str);
    getchar();

    for (p = str; *(p + 2); p++) {
        count[(int)*p][(int)*(p + 1)][(int)*(p + 2)]++;
    }

    for (i = 0; i != 128; i++) {
        for (j = 0; j != 128; j++) {
            for (k = 0; k != 128; k++) {
                if (count[i][j][k] > count[fob][sob][tob]) {
                        fob = i;
                        sob = j;
                        tob = k;
                }
            }
        }
    }

    if (str[0] == '\0')
        return 1;

    for (i = 2; str[i] != '\0'; i++) {
        if (str[i - 2] == fob && str[i - 1] == sob && str[i] == tob) { 
            str[i - 2] = '#';
            for (j = i-1; (str[j] != '\0'); j++) {
                    str[j] = str[j + 2];
                    if(str[j]!='\0')
                        str[j + 1] = str[j + 3];
            }
        }
    }

    printf("\nThe new string is %s.", str);
    size_2 = strlen(str);
    str2 = (char*)malloc(sizeof(char) * (size_2 + 3));
    *str2 = fob;
    *(str2 + 1) = sob;
    *(str2 + 2) = tob;
    strcpy(str2+3, str);

    printf("\nThe final string is %s.", str2);
    getchar();

    return 0;
}