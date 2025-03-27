#include "hw09.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

// suggested testing function declaration
static void check_string_to_long(const char *string);

int main(int argc, char **argv) {
  errno = 0;

  fprintf(stderr, "Welcome to ECE264, we are working on HW09!\n\n");

    check_string_to_long("42", 10);      // 42 in base 10
    check_string_to_long("101", 2);      // 5 in base 2
    check_string_to_long("2A", 16);      // 42 in base 16

    check_string_to_long("042", 0);      // 34 in base 8
    check_string_to_long("0x2A", 0);     // 42 in base 16
    check_string_to_long("123", 0);      // 123 in base 10

    check_string_to_long("   99", 10);   // 99
    check_string_to_long("\t\n  0xF", 0);// 15 in base 16

    check_string_to_long("+123", 10);    // 123
    check_string_to_long("-123", 10);    // -123
    check_string_to_long("-0xA", 0);     // -10 in base 16

    check_string_to_long("100", 1);      // Invalid base -> errno = EINVAL
    check_string_to_long("100", 37);     // Invalid base -> errno = EINVAL

    check_string_to_long("abc", 10);     // No conversion -> endptr at "abc"
    check_string_to_long("10abc", 10);   // Partial conversion -> endptr at "abc"
    check_string_to_long("!!123", 10);   // No conversion -> endptr at "!!123"

    char buf[50];
    sprintf(buf, "%ld", LONG_MAX);       // Convert LONG_MAX to string
    check_string_to_long(buf, 10);       // Should return LONG_MAX

    sprintf(buf, "%ld", LONG_MIN);       // Convert LONG_MIN to string
    check_string_to_long(buf, 10);       // Should return LONG_MIN

    sprintf(buf, "%ld1", LONG_MAX / 10);
    check_string_to_long(buf, 10);       // Should set errno = ERANGE

  return EXIT_SUCCESS;
}
