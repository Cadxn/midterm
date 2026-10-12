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
    
}
complex SubtractComplex(const complex c1, const complex c2){

}
complex MultiplyComplex(const complex c1, const complex c2){

}
complex DivideComplex(const complex c1, const complex c2){
    
}
complex ConjugateComplex(const complex c){
    
}
complex SquareComplex(const complex c){
    
}
void DisplayComplex(const complex c1){
    
}