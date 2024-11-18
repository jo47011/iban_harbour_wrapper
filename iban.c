/* $Id: iban.c,v 1.9 2012/07/08 12:52:51 ferber Exp $ */

#include "iban.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int iban_isdigit(int c) { return ('0' <= c && c <= '9'); }
int iban_isalpha(int c) { return ('A' <= c && c <= 'Z'); }
int iban_isalnum(int c) { return iban_isdigit(c) || iban_isalpha(c); }
int iban_isspace(int c) { return isspace(c); }

/* Remove white space while copying iban_in to iban_out. */
char *iban_collapse(char *iban_out, const char *iban_in) {
  register const char *s= iban_in;
  register char *t= iban_out;
  while(*s) {
    register int c= *s++;
    if(!iban_isspace(c)) { *t++= c; }
  }
  *t= '\000';
  return iban_out;
}

/* Insert white space while copying iban_in to iban_out. */
char *iban_expand(char *iban_out, const char *iban_in) {
  register const char *s= iban_in;
  register char *t= iban_out;
  register int k= 0;
  while(*s) {
    register int c= *s++;
    if(iban_isspace(c)) continue;
    if(k++ == 4) { *t++= ' '; k= 1; }
    *t++= c;
  }
  *t= '\000';
  return iban_out;
}

/* Compile digits for the mod97 operation from a collapsed iban. */
static char *iban_digits(char *digits, const char *iban) {
  register const char *s= (char *)&iban[4];
  register char *t= digits;
  register size_t i, len= strlen(iban);
  for(i=4; i<len; i++) { /*while(*s) {*/
    register int c= *s++;
    if(iban_isdigit(c)) {
      *t++= c;
    }
    else if(iban_isalpha(c)) {
      c= 10 + c-'A';
      *t++ = '0' + c / 10;
      *t++ = '0' + c % 10;
    }
    /* else: skip/ignore */
  }
  for(i=0; i<2; i++) { /* country code */
    register int c= 10 + iban[i]-'A';
    *t++ = '0' + c / 10;
    *t++ = '0' + c % 10;
  }
  *t++= iban[2]; /* checksum */
  *t++= iban[3];
  *t= '\000';
  return digits;
}

/* Calculate (digits mod k) */
static int modulus(const char *digits, int k) {
  int result= 0, a= 1;
  size_t num_digits= strlen(digits);
  register size_t i= 0;
  for(i=0; i<num_digits; i++) {
    register int d= digits[num_digits-i-1]-'0';
    if(i > 0) a= (10*a) % k;
    result += d * a;
  }
  return result % k;
}

/* MOD-97-10 as per ISO/IEC 7064:2002 */
int iban_mod97(const char *iban) {
  int result= -1;
  register size_t len= strlen(iban);
  char *buf= (char *)malloc(2*len+1);
  if(buf) {
    result= modulus(iban_digits(buf, iban), 97);
    free(buf); buf= (char *)0;
  }
  return result;
}

/* Generate iban (incl. checksum) from country and bban. */
char *iban_from_bban(char *iban, const char *country, const char *bban) {
  iban[0]= country[0];
  iban[1]= country[1];
  iban[2]= iban[3]= '0';
  strcpy(&iban[4], bban);
  {
    int crc= 98 - iban_mod97(iban);
    iban[2]= '0' + crc / 10;
    iban[3]= '0' + crc % 10;
  }
  return iban;
}
