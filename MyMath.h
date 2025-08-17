#ifndef MYMATH_H
#define MYMATH_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 
#include <stdbool.h>
#include <wingdi.h>  
#include <math.h> 
#include "resource.h"

#define SIZE_VETOR 1000
#define OBSULET_FUNCTION -1
#define NELTRO_FUNCTION 0

#define EXITING_WINDOWS 1 
#define BUTTON_CALCULATOR 2
#define BUTTON_CLEAR 3
#define DARK_COLOR 4
#define LIGHT_COLOR 5
#define GRAY_COLOR 6

#define BOTAO_QUAD 7
#define BOTAO_PONT 8
#define BOTAO_REST 9
#define BOTAO_CLEAN 10
#define BOTAO_DELET 11
#define BOTAO_PONTO 12
#define BOTAO_RAIZQ 13

#define BOTAO_9 14
#define BOTAO_8 15
#define BOTAO_7 16
#define BOTAO_6 17
#define BOTAO_5 18
#define BOTAO_4 20
#define BOTAO_3 21
#define BOTAO_2 22
#define BOTAO_1 23
#define BOTAO_0 24

#define BOTAO_PLUS 25
#define BOTAO_SUBT 26
#define BOTAO_VESES 27
#define BOTAO_DIVIS 28
#define BOTAO_ABRE_PAREN 29
#define BOTAO_FECHA_PAREN 30

#define ID_BTN_COR 31
#define string char *
#define VOIDNUM (0x0l) 

#ifndef BASES 
    #define BASE_DECIMAL 10
    #define BASE_HEXADECIMAL 16
    #define BASE_BINARIA 2
    #define BASE_OCTAL 8
#endif // BASES

static inline double quadrado(double num) {
    return num * num;
}

static inline double potencia(double num1, double num2) {
    double inicio = 1;
    for (int i = 0; i < num2; i++) {
        inicio *= num1;
    }
    return inicio;
}

static inline double somador(double num1, double num2) {
    return num1 + num2;
}

static inline double subtract(double num1, double num2) {
    return num1 - num2;
}

static inline double divis(double num1, double num2) {
    return num1 / num2;
}
  
static inline double mult(double num1, double num2) {
    return num1 * num2;
}

static inline int restFor2(int num){
    num %= 2;
    return num;
}
 
static inline double raizQuadrada(double numero) {
    if (numero < 0)
        return -1.0; // Valor inválido para raiz quadrada real
    return sqrt(numero);
}

static inline char *aredondar(double num, char expressao[SIZE_VETOR], HWND hWnd) {
    int size = strlen(expressao), num1;
    char avisoDeArendondamento[SIZE_VETOR] = "O numero ";
    strcat(avisoDeArendondamento, expressao);
    if (expressao[size-2] >= 53) {
        num1 = (int)ceil(num);
        sprintf(expressao, "%d", num1);
        strcat(avisoDeArendondamento, " foi arendondado por efeito para ");
        strcat(avisoDeArendondamento, expressao);
    } 
    else {
        num1 = (int)floor(num);
        sprintf(expressao, "%d", num1);
        strcat(avisoDeArendondamento, " foi arendondado por defeito para ");
        strcat(avisoDeArendondamento, expressao);
    }
    MessageBox(hWnd, avisoDeArendondamento, "Warning", MB_ICONWARNING | WS_CHILD);
    return (char *)expressao;
}
#endif