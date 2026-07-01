#include "lib_gerador.h"
#include <stdio.h>

void cria(int vetor[], char txt[])
{
    /* * Preenche uma variavel com idices == tabela ascii.
       * Foi criado um unsigned char para obter o valor do byte
       e para lidar com o setlocale, o indice 195 é marcado. */
    
    unsigned char ch;
    int a;

    for(a = 0; txt[a] != '\0'; a++)
    {
        ch = txt[a];
        if(ch > 127)
            vetor[195] = 1;
        vetor[ch] = 1;
    }
}


void gera(char entrada[], char saida[], int base[])
{
    /* * Reproduz entrada[] em saida[] usando a tabela ascii (base[]) e
       produz um efeito de processamento.

       * Para um char padrão, o char da entrada é transformado em
       unsigned char para ser comparado com a base e salvo na saida.
       * Para um char mult-byte, imprime apenas o segundo byte com utf[].
       * Para o efeito  a busca precisa ser entrada >> ascii. */

    unsigned char ch;
    char utf[3];
    int conta = 0;
    int a, b, c = 0;


    utf[2] = '\0';
    for(a = 0; entrada[a] != '\n'; a++) for(b = 32; b < 256; b++)
    {
        if(base[b])
        {
            if(!conta || (conta > 35))
             { printf("\n  "); conta = 0; }

            utf[0] = b; utf[1] = '\0';
            if(b > 127)
                { utf[0] = 195; utf[1] = b; }
       
            ch = entrada[a];
            if(ch == b)
            { 
                saida[c++] = (char)b;
                printf("\n\n  %s \n", saida);
                conta = 0;
                break;
            }
            else { printf("%s  ", utf); conta++; }
        }
    }
    saida[c] = '\0';
}



void caracteres(int i, char entrada[], char txt[])
{
    /* * Analisa a frequencia de cada caractere em entrada[].
       * Para resetar a variavel static usei o proprio parametro.
       * Para poder burlar o case sensitive, usei o indice i  que
       é igual a tabela ascii para comparar maiuscula e minusculas,
       também usei a tabela ascii para evitar repetições, junto com
       uma variavel int para contabilizar. */

    unsigned char ch;
    static int pula = 0; 
    int a, conta = 0;

    if(i == -1)
        { pula = 0; return; }

    if((pula == 0) || (pula == 3))
        { pula = 0; printf("\n\n  "); }
    else
        printf("\t\t");


    for(a = 0; entrada[a] != '\0'; a++)
    {
        ch = entrada[a];
        if(ch == 195)
            { a++; ch = entrada[a]; }
        
        if(i == ch) conta++;
        else if((i + 32 == ch) && (ch > 96) && (ch < 123)) conta++;
        else if((i + 32 == ch) && (ch > 127)) conta++;
    }


    if(conta == 1)
    { 
        printf("1 vez o %s", txt);
        pula++;
    }
    else if(conta)
    {
        printf("%d vezes os %ss", conta, txt);
        pula++;
    }
}



int escolha(char entrada[])
{
    /* * Verifica se foi digitado sim ou não.
       * Como preciso comparar apenas com duas strings, se
       for digitado Ã ou ã, eu apenas contabilizo e pulo para
       a terceira letra.
       * Comparo apenas caracteres minusculos e uso da ausencia
       de letras para conferir se foi digitado s ou n. */

    char ch, sim[] = "sim", nao[] = "nao";
    int a, outro, conta;
    unsigned char b;
    
    outro = 0; conta = 0;
    for(a = 0; a < 3; a++)
    {
        b = entrada[a+1];
        if((b == 131) || (b == 227))
            { conta++; a += 2; }

        ch = entrada[a];
        if((ch >= 'A') && (ch <= 'Z'))
            ch += 32;
        
        if(ch == sim[a]) conta++;
        else if(ch == nao[a]) conta--;
        else outro++;
    }
    
    if(((conta == 1) && (outro == 2)) || (conta == 3)) return 1;
    else if(((conta == -1) && (outro == 2)) || (conta == -3)) return 2;
    else return 0;
}
