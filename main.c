#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void save(char ** words, int size)
{
    FILE *f;
    f = fopen("corrections.txt", "w");
    for(int i = 0; i < size; i++)
    {
        fprintf(f, "%s", words[i]);
        fprintf(f, "\n");
    }
    fclose(f);

}

void random_50(char ** words, int size)
{
    srand(time(NULL));

    char ** r_words = malloc( 50 * sizeof(char*));
    for(int i = 0; i < 50; i++)
    {
        r_words[i] = malloc(65 * sizeof(char));
    }

    printf("\nZAD 2 = = = = = = = = = = = = = = = = =\n");
    for(int i = 0 ; i < 50; i++)
    {
        usleep(1000);
        char * str = words[rand()%size-1];
        if(strlen(str)>2){

            char c1, c2;
            c1 = str[0];
            c2 = str[strlen(str)-1];
            str[0] = c2;
            str[strlen(str)-1] = c1;
            strcpy(r_words[i], str);

            printf("[%d]%s\n",i, r_words[i]);

        }
        else
        {
            i--;
        }
    }

    save(r_words, 50);


}
char ** remove_stop_list(char ** words, int size)
{
    int list_n = 10;
    char ** stop_list = malloc( list_n * sizeof(char*));
    for(int i = 0; i < list_n; i++)
    {
        stop_list[i] = malloc(65 * sizeof(char));
    }

    strcpy(stop_list[0], "i");
    strcpy(stop_list[1], "a");
    strcpy(stop_list[2], "lub");
    strcpy(stop_list[3], "tez");
    strcpy(stop_list[4], "się");
    strcpy(stop_list[5], "I");
    strcpy(stop_list[6], "z");
    strcpy(stop_list[7], "po");
    strcpy(stop_list[8], "w");
    strcpy(stop_list[9], "ile");

    printf("\nSTOP LIST:\n");
    for(int i = 0 ; i < list_n; i++)
    {
        printf("%s\n", stop_list[i] );
    }



    int deleted_n = 0;
    for(int i = 0 ; i < size; i ++)
    {
        int boolean = 0;

        for(int j = 0; j < list_n; j++){

            if(strcmp(words[i], stop_list[j]) == 0)
            {
                boolean = 1;
            }

        }
        if(boolean == 1)
        {
            strcpy(words[i],"");  //TEST X->NULL
            deleted_n ++;
        }
    }

    printf("\n\n\n ************************************** \n\n\n");

    for(int i = 0; i < size; i++)
    {
        printf("%s ", words[i]);
    }

    return words;
}

char ** read_words()
{
    int n = 0;

    //check size
    FILE * f;
    f = fopen("pan_tadeusz.txt", "r");
    if(f==NULL)
    {
        printf("Read error\n");
    }
    else
    {
        char buff[64];
        while(fscanf(f, "%s", buff) != EOF)
        {
            n++;
        }
    }

    //read words
    fclose(f);
    f = fopen("pan_tadeusz.txt", "r");

    char ** words = malloc( n * sizeof(char*));
    for(int i = 0; i < n; i++)
    {
        words[i] = malloc(65 * sizeof(char));
    }

    if(f==NULL)
    {
        printf("Read error\n");
    }
    else
    {
        char buff[64];
        int index = 0;
        while(fscanf(f, "%s", buff) != EOF)
        {

            strcpy(words[index], buff);
            index++;
        }
    }
    fclose(f);


    //print
    for(int i = 0; i < n; i++)
    {
        //printf("%s ", words[i]);
    }

    //ZAD1
    remove_stop_list(words, n);

    //ZAD2
    random_50(words, n);

    return words;
}

void remove_spaces(char* s) {
    const char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while ((*s++ = *d++));
}


int main(int argc, const char * argv[]) {
    read_words();
    return 0;
}

