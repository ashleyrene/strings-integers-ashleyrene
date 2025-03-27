#include "hw09.h"
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>

#define INV_SYMBOL 36

// useful static helper functions
static int char_to_int(char c);
const char *skip_whitespace(const char *ptr);

long string_to_long(const char *string, const char **endptr, int base) {
  // checking that the first argument is not null, as specified in hw09.h
  assert(string != NULL);

  // setting errno to zero before function body starts
  errno = 0;

  long ret_value = 0;

  int sign = 1;

  // Check if the base provided is invalid, i.e. it is less than 2 or more than
  // 36. Remember that base 0 is valid, and you need to check the string to see
  // if it is octal or hexadecimal.
  //
  // If the base is invalid, set errno to EINVAL and return
  if (base < 0 || base == 1 || base > 36) {
    errno = EINVAL;
    if (endptr) *endptr = string;
    return 0;
  }

  // Skip over any whitespace present
  string = skip_whitespace(string);

  // Find the sign before the start of the number, if any
  if (*string == '-') {
    sign = -1;
    string++;
  } else if (*string == '+') {
    string++;
  }

  // Handle the case where base == 0
  if (base == 0) {
    if (*string == '0') {
      if (*(string + 1) == 'x' || *(string + 1) == 'X') {
        base = 16;  // Hexadecimal
        string += 2;
      } else {
        base = 8;   // Octal
        string++;
      }
    } else {
      base = 10;  // Default to decimal
    }
  }

  // Continue conversion while
  // 1) the string has not ended
  // 2) the current symbol is valid
  // 3) the current symbol is not a numeric value more than the base
  // Remember to deal with overflow! If overflow occurs, set errno to ERANGE
  const char *start = string;
  while (*string) {
    int digit = char_to_int(*string);

    if (digit >= base) break; 

    if (ret_value > (LONG_MAX - digit) / base) {
      errno = ERANGE;
      ret_value = (sign == 1) ? LONG_MAX : LONG_MIN;
      while (char_to_int(*string) < base) string++;
      break;
    }

    ret_value = ret_value * base + digit;
    string++;
  }

  // Deal with signs
  ret_value *= sign;

  // If there is no digit conversion, what should endptr be?
  if (endptr) *endptr = (*string != '\0') ? string : start;

  return ret_value;
}


  return ret_value;
}

static int char_to_int(char c) {
  // what if c is '0' -- '9'
  if (isdigit(c)) {
    return c - '0';
  }

  // what if c is 'a' -- 'z'
  if (islower(c)) {
    // only deal with one alphabetic case
    c = toupper(c);
  }

  if (isupper(c)) {
    // 'A' becomes 65 - 65 + 10 = 10, 'B' becomes 11 and so on
    return c - 'A' + 10;
  }

  return INV_SYMBOL;
}

const char *skip_whitespace(const char *ptr) {
  while (isspace(*ptr)) {
    ptr++;
  }

  return ptr;
}
