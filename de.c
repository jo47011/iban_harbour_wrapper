/* $Id: de.c,v 1.6 2012/07/07 11:18:30 ferber Exp $ */

#include "iban.h"

static int count_digits(const char *num) {
  int result= 0;
  register const char *s= num;
  while(*s) {
    register int c= *s++;
    if(iban_isdigit(c)) ++result;
  }
  return result;
}

static char *copy_digits(char *buf, const char *num) {
  register const char *s= num;
  register char *t= buf;
  while(*s) {
    register int c= *s++;
    if(iban_isdigit(c)) *t++= c;
  }
  *t= '\000';
  return buf;
}

/* Caution: Account numbers in BBANs can require two trailing
   sub-account (Unterkonto) digits.  ISO 13616 states that only banks
   can issue valid IBANs & BBANs. */

static char *bban_from_blz_kto(char *bban, const char *blz, const char *kto) {
  { /* BLZ: 8 digits, left padded with '0' */
    register int i, n= count_digits(blz);
    for(i=0; i<(8-n); i++) { bban[i]= '0'; }
    if(n <= 8) copy_digits(&bban[8-n], blz);
  }
  { /* account #: 10 digits, left padded with '0' */
    register int i, n= count_digits(kto);
    for(i=0; i<(10-n); i++) { bban[8+i]= '0'; }
    if(n <= 10) copy_digits(&bban[8+10-n], kto);
  }
  return bban;
}

/* Caller must ensure that length of collapsed blz <= 8, kto <= 10 */
char *iban_from_blz_kto(char *iban, const char *blz, const char *kto) {
  char bban[8+10+1];
  return iban_from_bban(iban, "DE", bban_from_blz_kto(bban, blz, kto));
}
