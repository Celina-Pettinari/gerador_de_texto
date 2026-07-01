#include <stdio.h>
#include <locale.h>
#include "lib_gerador.h"


int main(void)
{
    setlocale(LC_ALL, "");

    int a, b, t = 100002;
    int letras, numeros, simbolos;
    char entrada[t], saida[t], utf[3];
    int ascii[256] = {0}, asc_e[256] = {0};

    char abc[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char abc_lib[] = "àáâãéêíóõôúçÀÁÂÃÉÊÍÓÕÔÚÇ";
    char num[] = "1234567890";
    char especiais[] = " /;¨:\'\"\\-_=+*^%$#@!.,?()`[]";
    
    cria(ascii, abc); cria(ascii, abc_lib);
    cria(ascii, num); cria(ascii, especiais);
   
    
    do
    {
        a = 0; letras = 0; numeros = 0; simbolos = 0;
        do
        {
            printf("\033[2J\033[H");
            
            if(a == -1)
                printf("\n  Caractere invalido \n");
            
            for(a = 0; a < t; a++) entrada[a] = '\0'; 
            for(a = 0; a < t; a++) saida[a] = '\0';


            printf("\n  Digite quaquer coisa ");
            printf("- limite de %d mil caracteres: \n  ", (t - 2) / 1000);
            fgets(entrada, t, stdin);
            

            for(a = 0; entrada[a] != '\n'; a++)
            {
                b = (unsigned char)entrada[a];
                if(!ascii[b])
                    { a = -1; break; }
            }
        } while(a == -1);

                
        printf("\n");
        gera(entrada, saida, ascii);

        
        printf("\n\n\n  -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_");
        printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- \n  ");
        printf("********************************************************");
        printf("*************************************************** \n\n\n");
        printf("  O Texto: \n  %s \n  de %d caracteres possuí:", saida, a - 1);
        

        cria(asc_e, saida);
        asc_e[195] = 0;
        
        for(a = 33; a < 256; a++)
            if(asc_e[a])
            {
                if((a > 47) && (a < 58)) numeros = 1;
                else if((a > 64) && (a < 91)) letras = 1;
                else if((a > 96) && (a < 123)) letras = 1;
                else if(a > 127) letras = 1;
                else simbolos = 1;
            }


        if(letras)
        {
            for(a = 65; a < 91; a++)
                if(asc_e[a] || asc_e[a+32])
                { 
                    caracteres(a, saida, "caractere");
                        printf(" %c", a);
                }

            utf[0] = 195; utf[2] = '\0';
            for(a = 128; a < 256; a++)
                if(asc_e[a])
                {
                    utf[1] = a;
                    caracteres(a, saida, "caractere");
                    printf(" %s", utf);
                }
            
            printf("\n\n  -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_");
            printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-"); 
            caracteres(-1, saida, "");
        }

        if(numeros)
        {
                for(a = 48; a < 58; a++)
                if(asc_e[a])
                {
                    caracteres(a, saida, "numero");
                    printf(" %c", a);
                }
            printf("\n\n  -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_");
            printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-"); 
            caracteres(-1, saida, "");
        }


        if(simbolos)
        {
            for(a = 33; a < 48; a++)
                if(asc_e[a])
                    { caracteres(a, saida, "simbolo"); printf(" %c", a); }
            
            for(a = 58; a < 64; a++)
                if(asc_e[a])
                    { caracteres(a, saida, "simbolo"); printf(" %c", a); }
            
            for(a = 91; a < 97; a++)
                if(asc_e[a])
                    { caracteres(a, saida, "simbolo"); printf(" %c", a); }
            
            for(a = 123; a < 127; a++)
                if(asc_e[a])
                    { caracteres(a, saida, "simbolo"); printf(" %c", a); }
            
            printf("\n\n  -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_");
            printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-");
            caracteres(-1, saida, "");
        }
        
        for(a = 32; a < 256; a++) asc_e[a] = 0;

        do
        {
            for(a = 0; entrada[a] != '\0'; a++) entrada[a] = '\0';

            printf("\n\n\n  Deseja reiniciar o programa? \n  ");
            fgets(entrada, 5, stdin);
            a = escolha(entrada);
        }
        while(!a);

        printf("\033[2J\033[H");
    }
    while(a == 1);
    return 0;
}
