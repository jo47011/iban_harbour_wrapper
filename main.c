/* $Id: main.c,v 1.7 2012/07/17 07:05:31 ferber Exp $ */

#include "iban.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  if(argc == 1+1) {
    char *iban= argv[1];
    char buf[IBAN_BUFSIZE], etx[IBAN_ETX_MAXLEN];
    printf("IBAN ......... : %s\n", iban);
    printf("Collapsed .... : %s\n", iban_collapse(buf, iban));
    printf("Expanded ..... : %s\n", iban_expand(buf, iban));
    printf("Verify ....... : %d: %s\n", iban_verify(iban),
           iban_error(etx, iban_verify(iban)));
  }
  else if(argc == 1+2) {
    char buf[IBAN_BUFSIZE], etx[IBAN_ETX_MAXLEN];
    printf("BLZ .......... : %s\n", iban_collapse(buf,argv[1]));
    printf("Kto .......... : %s\n", iban_collapse(buf,argv[2]));
    printf("IBAN ......... : %s\n", iban_from_blz_kto(buf, argv[1], argv[2]));
    printf("Verify ....... : %d: %s\n", iban_verify(buf),
           iban_error(etx, iban_verify(buf)));
  }
  return 0;
}
