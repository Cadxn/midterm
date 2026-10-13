#include <stdio.h>
#include <stdlib.h>
#include "complex.h"

typedef struct ComplexType {
    double real;
    double imag;
} ComplexType;

complex CreatComplex(double real, double imag){
    ComplexType *c = (ComplexType *)malloc(sizeof(ComplexType));
    c->real = real;
    c->imag = imag;
    return c;
}
void DestroyComplex(complex c){
    free(c);
}
double GetReal(const complex c){
    return c->real;
}
double GetImaginary(const complex c){
    return c->imag;
}
double ComplexMagnitude(const complex c){
    return sqrt(c->real * c->real + c->imag * c->imag);
}
complex AddComplex(const complex c1, const complex c2){
    return CreatComplex(c1->real + c2->real, c1->imag + c2->imag);
}
complex SubtractComplex(const complex c1, const complex c2){
    return CreatComplex(c1->real - c2->real, c1->imag - c2->imag);
}
complex MultiplyComplex(const complex c1, const complex c2){
    return CreatComplex(c1->real * c2->real - c1->imag * c2->imag, c1->imag * c2->real + c1->real * c2->imag);
}
complex DivideComplex(const complex c1, const complex c2){
    double denominator = c2->real * c2->real + c2->imag * c2->imag;
    return CreatComplex((c1->real * c2->real + c1->imag * c2->imag) / denominator, (c1->imag * c2->real - c1->real * c2->imag) / denominator);
}
complex ConjugateComplex(const complex c){
    return CreatComplex(c->real, -(c->imag));
}
complex SquareComplex(const complex c){
    return MultiplyComplex(c, c);
}
void DisplayComplex(const complex c1){
    printf("(%.2f + %.2fi)", c1->real, c1->imag);
}