/* $Id: verify.c,v 1.9 2012/07/12 09:44:43 ferber Exp $ */

#include "iban.h"

#include <string.h>
#include <stdlib.h>

/* Generated from the list of valid IBANs by country at
   http://en.wikipedia.org/wiki/International_Bank_Account_Number */

/* format: n=[0-9], a=[A-Z], c= (n|a) */
typedef struct { const char *country, *format; } bban_info_t;

/* sorted by country (asc) */
static const bban_info_t bban_info[] = {
  { "AD", "8n,12c" },
  { "AE", "3n,16n" },
  { "AL", "8n,16c" },
  { "AT", "16n" },
  { "AZ", "4c,20n" },
  { "BA", "16n" },
  { "BE", "12n" },
  { "BG", "4a,6n,8c" },
  { "BH", "4a,14c" },
  { "CH", "5n,12c" },
  { "CR", "17n" },
  { "CY", "8n,16c" },
  { "CZ", "20n" },
  { "DE", "18n" }, /* Germany: 8n,10n */
  { "DK", "14n" },
  { "DO", "4a,20n" },
  { "EE", "16n" },
  { "ES", "20n" },
  { "FI", "14n" },
  { "FO", "14n" },
  { "FR", "10n,11c,2n" },
  { "GB", "4a,14n" },
  { "GE", "2c,16n" },
  { "GI", "4a,15c" },
  { "GL", "14n" },
  { "GR", "7n,16c" },
  { "GT", "4c,20c" },
  { "HR", "17n" },
  { "HU", "24n" },
  { "IE", "4c,14n" },
  { "IL", "19n" },
  { "IS", "22n" },
  { "IT", "1a,10n,12c" },
  { "KW", "4a,22n" },
  { "KZ", "3n,13c" },
  { "LB", "4n,20c" },
  { "LI", "5n,12c" },
  { "LT", "16n" },
  { "LU", "3n,13c" },
  { "LV", "4a,13c" },
  { "MC", "10n,11c,2n" },
  { "MD", "2c,18n" },
  { "ME", "18n" },
  { "MK", "3n,10c,2n" },
  { "MR", "23n" },
  { "MT", "4a,5n,18c" },
  { "MU", "4a,19n,3a" },
  { "NL", "4a,10n" },
  { "NO", "11n" },
  { "PK", "4c,16n" },
  { "PL", "24n" },
  { "PT", "21n" },
  { "RO", "4a,16c" },
  { "RS", "18n" },
  { "SA", "2n,18c" },
  { "SE", "20n" },
  { "SI", "15n" },
  { "SK", "20n" },
  { "SM", "1a,10n,12c" },
  { "TN", "20n" },
  { "TR", "5n,17c" },
  { "VG", "4c,16n" },
  { (const char *)0, (const char *)0 }
};

static int find_bban_info(const char *country) {
  int result= -1;
  register int i;
  for(i=0; bban_info[i].country; i++) {
    register const char *s= bban_info[i].country;
    if(s[0] < country[0] || s[1] < country[1]) { continue; }
    else if(s[0] == country[0] && s[1] == country[1]) { result= i; }
    break;
  }
  return result;
}

static const char *parse_format(const char *fmt, int *nptr, char *cptr) {
  int n= 0;
  register const char *s= fmt;
  while(iban_isdigit(*s)) { n= n*10 + (*s++)-'0'; }
  *nptr= n; *cptr= s[0];
  return &s[1];
}

static int format_length(const char *fmt) {
  int result= 0;
  register const char *s= fmt;
  for(;;) {
    int n= 0; char c/*= '\000'*/;
    s= parse_format(s, &n, &c);
    result += n;
    if(!*s++) break; /* else: skip ',' */
  }
  return result;
}

static int iban_verify_numeric(const char *iban, int k, int n) {
  int err= 0;
  register int i;
  for(i=0; i<n; i++) {
    register int c= iban[k+i];
    if(!iban_isdigit(c)) { err= IBAN_ERR_DIGIT + k+i+1; break; }
  }
  return err;
}

static int iban_verify_alpha(const char *iban, int k, int n) {
  int err= 0;
  register int i;
  for(i=0; i<n; i++) {
    register int c= iban[k+i];
    if(!iban_isalpha(c)) { err= IBAN_ERR_ALPHA + k+i+1; break; }
  }
  return err;
}

static int iban_verify_alnum(const char *iban, int k, int n) {
  int err= 0;
  register int i;
  for(i=0; i<n; i++) {
    register int c= iban[k+i];
    if(!iban_isalnum(c)) { err= IBAN_ERR_ALNUM + k+i+1; break; }
  }
  return err;
}

static int iban_verify_format(const char *iban, const char *fmt) {
  int err= 0;
  register int k= 4; /* bban index */
  while(!err) {
    int n; char c;
    fmt= parse_format(fmt, &n, &c);
    switch(c) {
      case 'n': err= iban_verify_numeric (iban, k, n); break;
      case 'a': err= iban_verify_alpha   (iban, k, n); break;
      case 'c': err= iban_verify_alnum   (iban, k, n); break;
    }
    k+= n;
    if(!*fmt++) break; /* else: skip ',' */
  }
  return err;
}

int iban_verify(const char *iban) {
  int err= -1;
  if(iban) {
    char *clps= (char *)malloc(strlen(iban)+1);
    if(clps) {
      size_t clps_len= strlen(iban_collapse(clps, iban));
      int i= find_bban_info(iban);
      if(i >= 0) {
        size_t iban_len= 4+format_length(bban_info[i].format);
        if(clps_len == iban_len) {
          err= iban_verify_format(clps, bban_info[i].format);
          if(err == 0) {
            int one= iban_mod97(iban);
            if(one != 1) {
              err= IBAN_ERR_CHECKSUM + one;
            }
          }
        }
        else err= IBAN_ERR_LENGTH + iban_len;
      }
      else err= IBAN_ERR_COUNTRY;
    }
    else err= IBAN_ERR_NOMEM;
    free(clps); clps= (char *)0;
  }
  else err= IBAN_ERR_BADARGS;
  return err;
}
