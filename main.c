#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>


typedef struct array
{
    char c;
    struct array *sig;
}string;

void addc(string**list,char x)
{
    string* nodo = (string*)malloc(sizeof(string));
    nodo->c = x;
    nodo->sig = NULL;
    if(*list == NULL)
    {
        *list = nodo;
    }
    else
    {
        string* aux = *list;
        while (aux->sig != NULL)
        {
            aux = aux->sig;
        }
        aux->sig = nodo;
    }
}

int sizestr(string*list){
    int i = 0;
    while (list != NULL)
    {
        list = list->sig;
        i++;
    }
    return i;
}

char* lts(string*list){
    char *str = (char*)malloc(sizeof(char)*(sizestr(list)+1));
    int i = 0;
    for(; list != NULL; i++)
    {
        str[i] = list->c;
        list = list->sig; 
    }
    str[i] = '\0';
    return str;
}

void addstr(string**list, char* str, int mode) 
{
    int i = 0, size = strlen(str);
    string *aux = (string*)malloc(sizeof(string)), *aux1 = aux;
    for(;;)
    {
        aux->c = str[i++];
        if(i < size)
        {
            aux->sig = (string*)malloc(sizeof(string));
            aux = aux->sig;
        }
        else
        {
            aux->sig = NULL;
            break;
        }
    }

    if(*list == NULL)
    {
        *list = aux1;
    }
    else
    {
        if(mode)
        {
            aux = *list;
            while (aux->sig != NULL)
            {
                aux = aux->sig;
            }
            aux->sig = aux1;
        }
        else
        {
            aux->sig = *list;
            *list = aux1;
        }
    }
}

void delstr(string**str, int pos){
    if (*str == NULL)
    {
        return;
    }

    string *aux;
    
    if(pos == 0)
    {
        aux = (*str)->sig;
        free(*str);
        *str = aux;
    }
    else
    {
        aux = *str;
        string *aux1;
        while (aux->sig != NULL && pos != 0)
        {
            pos -= 1;
            aux1 = aux;
            aux = aux->sig;
        }
        aux1->sig = aux->sig;
        free(aux);
    }
    
}

void Delstr(string**str, int until){
    string *aux = *str, *aux1;
    for(;aux != NULL; aux = aux1)
    {
        if(until == aux->c)
        {
            *str = aux;
            return;
        }
        aux1 = aux->sig;
        free(aux);
    }
    *str = NULL;
}

string* copystr(string*str2,int until){
    string *str1, *aux;
    if(until == str2->c)
    {
        return NULL;
    }
    str1 = (string*)malloc(sizeof(string));
    (str1)->c = str2->c;
    (str1)->sig = NULL;
    str2 = str2->sig;
    
    aux = str1;

    while (str2 != NULL)
    {
        if(str2->c == until)
        {
            break;
        }
        aux->sig = (string*)malloc(sizeof(string));
        aux = aux->sig;
        aux->c = str2->c;
        str2 = str2->sig;
    }
    aux->sig = NULL;
    return str1;
}

void catstr(string**str1,string*str2,int until){
    if(*str1 == NULL)
    {
        if(until == str2->c)
        {
            return;
        }
        *str1 = (string*)malloc(sizeof(string));
        (*str1)->c = str2->c;
        (*str1)->sig = NULL;
        str2 = str2->sig;
    }
    string *aux = *str1;
    while (aux->sig != NULL)
    {
        aux = aux->sig;
    }
    while (str2 != NULL)
    {
        if(str2->c == until)
        {
            break;
        }
        aux->sig = (string*)malloc(sizeof(string));
        aux = aux->sig;
        aux->c = str2->c;
        str2 = str2->sig;
    }
    aux->sig = NULL;
}

typedef struct array_of_str
{
    string* str;
    struct array_of_str *sig;
}astr;

int sizea(astr*array){
    int i = 0;
    while (array != NULL)
    {
        array = array->sig;
        i++;
    }
    return i;
}

void showastr(astr*array)
{
    char*r;
    while (array != NULL)
    {
        r = lts(array->str);
        printf("%s;",r);
        free(r);
        array = array->sig;
    }
    
}

void adda(astr **array, string*str, int pos){
    astr *nodo = (astr*)malloc(sizeof(astr));
    nodo->str = str;
    nodo->sig = NULL;
    if(*array == NULL)
    {
        *array = nodo;
    }
    else
    {
        astr *aux = *array;
        if(pos == 0)
        {
            *array = nodo;
            nodo->sig = aux;
        }
        else
        {
            while (aux->sig != NULL)
            {
                aux = aux->sig;
            }
            aux->sig = nodo;
        }
    }
    
}

void addarray(astr **array, astr *array1){
    if(*array == NULL)
    {
        *array = array1;
    }
    else
    {
        astr *aux = *array;
        while(aux->sig != NULL)
        {
            aux = aux->sig;
        }
        aux->sig = array1;
    }
}

void astrf(astr**array){
    astr *aux;
    Delstr(&(*array)->str,0);
    aux = (*array)->sig;
    free(*array);
    *array = aux;
}

void dela(astr **array, int pos){
    if (*array == NULL)
    {
        return;
    }
    
    if(pos == 0)
    {
        astrf(array);
    }
    else
    {
        astr *aux = *array, *aux1;
        while (pos != 0 && aux->sig != NULL)
        {
            aux1 = aux;
            aux = aux->sig;
            pos -= 1;
        }
        astrf(&aux);
        aux1->sig = aux;
    }
    
}

void Dela(astr**array){
    astr *aux;
    while (*array != NULL)
    {
        Delstr(&(*array)->str,0);
        aux = (*array)->sig;
        free(*array);
        *array = aux;
    }
    
}

int getfile(FILE *f, astr **words){
    int i = 0;
    char buffer[128];
    string* aux = NULL;
    astr* word;
    while (fgets(buffer,128,f) != NULL){
        addstr(&aux,buffer,1);
        if(buffer[strlen(buffer)-1] == '\n')
        {
            delstr(&aux,-1);
        }
        if(i == 0)
        {
            adda(words,aux,0);
            word = *words;
        }
        else
        {
            word->sig = (astr*)malloc(sizeof(astr));
            word = word->sig;
            word->str = aux;
        }
        aux = NULL;
        i++;
    }
    word->sig = NULL;
    return i;
}

int nm(int m, int M){
    srand(time(NULL));
    return m + rand()%(M + 1 - m);
}

char *getword(astr**word, int num){
    if(*word == NULL)
    {
        return NULL;
    }
    char *r;
    if(num == 0)
    {
        r = lts((*word)->str);
        astrf(word);
    }
    else
    {
        astr *aux = *word, *aux1;
        while (aux->sig != NULL && num != 0)
        {
            num -= 1;
            aux1 = aux;
            aux = aux->sig;
        }
        if(num <= 0)
        {
            r = lts(aux->str);
            astrf(&aux);
            aux1->sig = aux;
        }
    }
    return r;
}

void end(char* file, astr*words){
    FILE *f = fopen(file,"w");
    char *r;
    while(words != NULL)
    {
        r = lts(words->str);
        fprintf(f,"%s\n",r);
        free(r);
        words = words->sig;
    }
    fclose(f);
}

char* inputstr(){
    string *str = NULL;
    int k = 0;
    while (1)
    {
        k = getch();
        if(k == 13)
        {
            char* r = lts(str);
            Delstr(&str,0);
            return r;
        }
        else
        {
            if((65 <= k && k <= 90) || (97 <= k && k <= 122) || k == VK_SPACE)
            {
                putchar(k);
                addc(&str,k);
            }
            else
            {
                
                if(k == 8) 
                {
                    putchar(8);
                    putchar(' ');
                    putchar(8);
                    delstr(&str,sizestr(str)-1);
                }
            }

        }
    }
    
}

int inputp(char*word,int size){
    char *input = inputstr();
    int r = strcmp(word,input);
    free(input);
    return r;
}

void game(astr**words, char* file){
    astr *aux = NULL;
    string *str = NULL;
    int rn, i = sizea(*words), size;
    char*r;
    while ((*words) != NULL)
    {
        rn = nm(0,sizea(*words)-1);
        r = getword(words,rn);
        addstr(&str,r,1);
        adda(&aux,str,1);
        str = NULL;
        printf("%d\n%s",i,r);
        i -= 1;
        size = strlen(r);
        for(int j = size; j < 60; j++)
        {
            putchar(' ');
        }
        rn = inputp(r,size);
        free(r);
        system("cls");
        if(rn)
        {
            break;
        }
    }

    addarray(&aux,*words);

    end(file,aux);
    if(rn == 0)
    {
        printf("YOU WIN");
        system("pause>nul");
    }
}

int main(){
    char file[MAX_PATH], *r;
    FILE *f;
    do
    {
        system("echo FILE: ");
        r = inputstr();
        strcpy(file,r);
        free(r);
        strcat(file,".txt");
        system("cls");
        f = fopen(file,"r");
    } while (f == NULL);
    
    astr *word = NULL;
    getfile(f,&word);
    fclose(f);
    game(&word,file);
    Dela(&word);
    system("cls");
    main();
    return 0;
}