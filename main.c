#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "complex.c"

#define EPSILON 1e-6

// Track test statistics globally
int tests_run = 0;
int tests_passed = 0;

// Assertion helper function
void assert_true(int condition, const char* test_name) {
    tests_run++;
    if (condition) {
        tests_passed++;
    } else {
        printf("  ❌ [FAIL] %s\n", test_name);
    }
}

// Float precision helper
int close_enough(double a, double b) {
    if (isnan(a) && isnan(b)) return 1; // Count matching NaNs as equal for tests
    if (isinf(a) && isinf(b)) return ((a > 0) == (b > 0)); 
    return fabs(a - b) < EPSILON;
}

int main() {
    printf("==================================================\n");
    printf("     EXPANDED TEST SUITE FOR COMPLEX ADT          \n");
    printf("==================================================\n\n");

    // ---------------------------------------------------------
    // BATCH 1: Standard Values & Basic Verification
    // ---------------------------------------------------------
    printf("--- Batch 1: Standard Valuations ---\n");
    {
        complex c1 = CreatComplex(3.0, -4.0);
        assert_true(c1 != NULL, "CreatComplex allocation check");
        assert_true(close_enough(GetReal(c1), 3.0), "GetReal basic check");
        assert_true(close_enough(GetImaginary(c1), -4.0), "GetImaginary basic check");
        assert_true(close_enough(ComplexMagnitude(c1), 5.0), "ComplexMagnitude check");
        
        complex conj = ConjugateComplex(c1);
        assert_true(close_enough(GetReal(conj), 3.0), "Conjugate Real matching");
        assert_true(close_enough(GetImaginary(conj), 4.0), "Conjugate Imaginary inverted");
        
        DestroyComplex(c1);
        DestroyComplex(conj);
    }

    // ---------------------------------------------------------
    // BATCH 2: Edge Cases (Zeroes and Signs)
    // ---------------------------------------------------------
    printf("\n--- Batch 2: Absolute Zero & Signed Zeroes ---\n");
    {
        complex zero = CreatComplex(0.0, 0.0);
        assert_true(close_enough(ComplexMagnitude(zero), 0.0), "Magnitude of absolute zero");
        
        complex sq_zero = SquareComplex(zero);
        assert_true(close_enough(GetReal(sq_zero), 0.0) && close_enough(GetImaginary(sq_zero), 0.0), "Square of absolute zero");
        
        complex neg_zero = CreatComplex(-0.0, -0.0);
        assert_true(close_enough(ComplexMagnitude(neg_zero), 0.0), "Magnitude of negative zeroes");

        DestroyComplex(zero);
        DestroyComplex(sq_zero);
        DestroyComplex(neg_zero);
    }

    // ---------------------------------------------------------
    // BATCH 3: Identities (Mathematical Proof Verification)
    // ---------------------------------------------------------
    printf("\n--- Batch 3: Algebraic & Mathematical Identities ---\n");
    {
        complex c = CreatComplex(2.5, 7.1);
        complex zero = CreatComplex(0.0, 0.0);
        complex one = CreatComplex(1.0, 0.0);

        // Additive Identity: c + 0 = c
        complex add_id = AddComplex(c, zero);
        assert_true(close_enough(GetReal(add_id), GetReal(c)), "Additive identity (Real)");
        assert_true(close_enough(GetImaginary(add_id), GetImaginary(c)), "Additive identity (Imag)");

        // Multiplicative Identity: c * 1 = c
        complex mul_id = MultiplyComplex(c, one);
        assert_true(close_enough(GetReal(mul_id), GetReal(c)), "Multiplicative identity (Real)");
        assert_true(close_enough(GetImaginary(mul_id), GetImaginary(c)), "Multiplicative identity (Imag)");

        // Conjugate of Conjugate identity: conj(conj(c)) == c
        complex conj1 = ConjugateComplex(c);
        complex conj2 = ConjugateComplex(conj1);
        assert_true(close_enough(GetReal(conj2), GetReal(c)) && close_enough(GetImaginary(conj2), GetImaginary(c)), "Double conjugate loops back");

        DestroyComplex(c); DestroyComplex(zero); DestroyComplex(one);
        DestroyComplex(add_id); DestroyComplex(mul_id);
        DestroyComplex(conj1); DestroyComplex(conj2);
    }

    // ---------------------------------------------------------
    // BATCH 4: Extreme Valuations & Stress Testing
    // ---------------------------------------------------------
    printf("\n--- Batch 4: Division-by-Zero and Extreme Values ---\n");
    {
        complex dividend = CreatComplex(5.0, 5.0);
        complex absolute_zero = CreatComplex(0.0, 0.0);
        
        // Division by Zero handling 
        // Mathematically undefined. Your implementation will likely produce infinity or NaN.
        complex bad_div = DivideComplex(dividend, absolute_zero);
        double r = GetReal(bad_div);
        double i = GetImaginary(bad_div);
        assert_true(isnan(r) || isinf(r) || isnan(i) || isinf(i), "Division by absolute zero yields Inf or NaN handles gracefully");

        // Extreme structural stress bounds test
        complex huge_real = CreatComplex(1e154, 0.0); 
        complex h_sq = SquareComplex(huge_real);
        assert_true(isinf(GetReal(h_sq)), "Overflow successfully handled resulting in standard positive infinity");

        DestroyComplex(dividend);
        DestroyComplex(absolute_zero);
        DestroyComplex(bad_div);
        DestroyComplex(huge_real);
        DestroyComplex(h_sq);
    }

    // ---------------------------------------------------------
    // BATCH 5: Display Format Visual Validation
    // ---------------------------------------------------------
    printf("\n--- Batch 5: Component Visual Output Formats ---\n");
    {
        complex visual1 = CreatComplex(0.0, -1.5);
        complex visual2 = CreatComplex(-4.2, 0.0);
        
        printf("  [Visual Verify] Pure Imaginary (0.0, -1.5): ");
        DisplayComplex(visual1);
        printf("\n  [Visual Verify] Pure Real (-4.2, 0.0):     ");
        DisplayComplex(visual2);
        printf("\n");

        DestroyComplex(visual1);
        DestroyComplex(visual2);
    }

    // Final Report Execution Status Output Summary Block
    printf("\n==================================================\n");
    printf(" FINAL RESULTS: Passed %d / %d checks.\n", tests_passed, tests_run);
    printf("==================================================\n");

    return (tests_passed == tests_run) ? 0 : 1;
}
