#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "complex.h"

#define EPSILON 1e-6

// Helper function to compare floating-point values safely
int assert_close(double actual, double expected, const char* test_name) {
    if (fabs(actual - expected) > EPSILON) {
        printf("  ❌ [FAIL] %s: Expected %.4f, but got %.4f\n", test_name, expected, actual);
        return 0;
    }
    return 1;
}

int main() {
    int passed_tests = 0;
    int total_tests = 0;

    printf("=========================================\n");
    printf(" RUNNING COMPLEX NUMBER ADT TEST SUITE   \n");
    printf("=========================================\n\n");

    // ---------------------------------------------------------
    // Test 1: Creation, Getters, and Destruction
    // ---------------------------------------------------------
    printf("Test 1: Creation & Getters...\n");
    complex c1 = CreatComplex(3.0, 4.0); // Spelling matches complex.h
    
    total_tests += 2;
    if (c1 != NULL) {
        if (assert_close(GetReal(c1), 3.0, "GetReal")) passed_tests++;
        if (assert_close(GetImaginary(c1), 4.0, "GetImaginary")) passed_tests++;
    } else {
        printf("  ❌ [FAIL] CreatComplex returned NULL\n");
    }

    // ---------------------------------------------------------
    // Test 2: Magnitude
    // ---------------------------------------------------------
    printf("Test 2: Magnitude...\n");
    total_tests++;
    if (assert_close(ComplexMagnitude(c1), 5.0, "ComplexMagnitude (3 + 4i)")) passed_tests++;

    // ---------------------------------------------------------
    // Test 3: Conjugate
    // ---------------------------------------------------------
    printf("Test 3: Conjugate...\n");
    complex c1_conj = ConjugateComplex(c1);
    total_tests += 2;
    if (assert_close(GetReal(c1_conj), 3.0, "Conjugate Real Part")) passed_tests++;
    if (assert_close(GetImaginary(c1_conj), -4.0, "Conjugate Imaginary Part")) passed_tests++;

    // ---------------------------------------------------------
    // Test 4: Basic Arithmetic Operations (Add & Subtract)
    // ---------------------------------------------------------
    printf("Test 4: Arithmetic (Add & Subtract)...\n");
    complex c2 = CreatComplex(1.5, -2.5);
    
    // Add: (3 + 4i) + (1.5 - 2.5i) = (4.5 + 1.5i)
    complex c_add = AddComplex(c1, c2);
    total_tests += 2;
    if (assert_close(GetReal(c_add), 4.5, "Add Real Part")) passed_tests++;
    if (assert_close(GetImaginary(c_add), 1.5, "Add Imaginary Part")) passed_tests++;

    // Subtract: (3 + 4i) - (1.5 - 2.5i) = (1.5 + 6.5i)
    complex c_sub = SubtractComplex(c1, c2);
    total_tests += 2;
    if (assert_close(GetReal(c_sub), 1.5, "Subtract Real Part")) passed_tests++;
    if (assert_close(GetImaginary(c_sub), 6.5, "Subtract Imaginary Part")) passed_tests++;

    // ---------------------------------------------------------
    // Test 5: Advanced Arithmetic Operations (Multiply & Divide)
    // ---------------------------------------------------------
    printf("Test 5: Arithmetic (Multiply & Divide)...\n");
    
    // Multiply: (3 + 4i) * (1.5 - 2.5i) = (4.5 - 7.5i + 6i - 10i^2) = (14.5 - 1.5i)
    complex c_mul = MultiplyComplex(c1, c2);
    total_tests += 2;
    if (assert_close(GetReal(c_mul), 14.5, "Multiply Real Part")) passed_tests++;
    if (assert_close(GetImaginary(c_mul), -1.5, "Multiply Imaginary Part")) passed_tests++;

    // Divide: (3 + 4i) / (1.5 - 2.5i)
    // Denominator = 1.5^2 + (-2.5)^2 = 2.25 + 6.25 = 8.5
    // Numerator = (3 + 4i) * (1.5 + 2.5i) = (4.5 + 7.5i + 6i - 10) = (-5.5 + 13.5i)
    // Expected Real = -5.5 / 8.5 = -0.6470588
    // Expected Imag = 13.5 / 8.5 = 1.5882353
    complex c_div = DivideComplex(c1, c2);
    total_tests += 2;
    if (assert_close(GetReal(c_div), -5.5 / 8.5, "Divide Real Part")) passed_tests++;
    if (assert_close(GetImaginary(c_div), 13.5 / 8.5, "Divide Imaginary Part")) passed_tests++;

    // ---------------------------------------------------------
    // Test 6: Square
    // ---------------------------------------------------------
    printf("Test 6: Square Complex...\n");
    // Square: (3 + 4i)^2 = 9 + 24i - 16 = (-7 + 24i)
    complex c_sq = SquareComplex(c1);
    total_tests += 2;
    if (assert_close(GetReal(c_sq), -7.0, "Square Real Part")) passed_tests++;
    if (assert_close(GetImaginary(c_sq), 24.0, "Square Imaginary Part")) passed_tests++;

    // ---------------------------------------------------------
    // Test 7: Display Verification (Visual Check)
    // ---------------------------------------------------------
    printf("Test 7: Visual Display Verification...\n");
    printf("  Expected format output for c1 (3.00 + 4.00i):\n  [OUTPUT] ");
    DisplayComplex(c1);
    printf("\n");

    // ---------------------------------------------------------
    // Clean up all allocated memory blocks
    // ---------------------------------------------------------
    DestroyComplex(c1);
    DestroyComplex(c2);
    DestroyComplex(c1_conj);
    DestroyComplex(c_add);
    DestroyComplex(c_sub);
    DestroyComplex(c_mul);
    DestroyComplex(c_div);
    DestroyComplex(c_sq);

    // Final Report Summary
    printf("=========================================\n");
    printf(" SUMMARY: Passed %d/%d assertion checks.\n", passed_tests, total_tests);
    printf("=========================================\n");

    if (passed_tests == total_tests) {
        printf("🎉 ALL TESTS PASSED SUCCESSFULLY! 🎉\n");
        return 0;
    } else {
        printf("⚠️ SOME TESTS FAILED. Check implementations above. ⚠️\n");
        return 1;
    }
}
