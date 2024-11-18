/* $Id: error.c,v 1.2 2012/07/03 17:35:44 ferber Exp $ */

#include "iban.h"
#include <string.h>
#include <stdio.h>

char *iban_error(char *etx, int ecd) {
  int subcode= ecd % 100;
  if(ecd == IBAN_ERR_OK) {
    strcpy(etx, "No error");
  }
  else if(ecd == IBAN_ERR_BADARGS) {
    strcpy(etx, "Bad arguments / null pointer");
  }
  else if(ecd == IBAN_ERR_NOMEM) {
    strcpy(etx, "Not enough memory");
  }
  else if(ecd == IBAN_ERR_COUNTRY) {
    strcpy(etx, "Unknown country code");
  }
  else if(ecd-subcode == IBAN_ERR_LENGTH) {
    sprintf(etx, "Expected number of characters: %d", subcode);
  }
  else if(ecd-subcode == IBAN_ERR_CHECKSUM) {
    sprintf(etx, "Checksum error; calculated: %02d", subcode);
  }
  else if(ecd-subcode == IBAN_ERR_DIGIT) {
    sprintf(etx, "Expected a digit [0-9] at position %d", subcode);
  }
  else if(ecd-subcode == IBAN_ERR_ALPHA) {
    sprintf(etx, "Expected a letter [A-Z] at position %d", subcode);
  }
  else if(ecd-subcode == IBAN_ERR_ALNUM) {
    sprintf(etx, "Expected a letter [A-Z] or a digit [0-9]"
            " at position %d", subcode);
  }
  else strcpy(etx, "Unknown error");
  return etx;
}
