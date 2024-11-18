/* $Id: bic.c,v 1.2 2012/07/12 14:04:45 ferber Exp $ */

#include "bic.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static int bic_isdigit(int c) { return ('0' <= c && c <= '9'); }
static int bic_isalpha(int c) { return ('A' <= c && c <= 'Z'); }
static int bic_isalnum(int c) { return bic_isdigit(c) || bic_isalpha(c); }
static int bic_isspace(int c) { return isspace(c); }

char *bic_collapse(char *out, const char *in) {
  register const char *s= in;
  register char *t= out;
  while(*s) {
    register int c= *s++;
    if(!bic_isspace(c)) { *t++= c; }
  }
  *t= '\000';
  return out;
}

bic_t *bic_split(bic_t *out, const char *in) {
  strncpy(out->bank, &in[0], 4);
  strncpy(out->country, &in[4], 2);
  strncpy(out->location, &in[4+2], 2);
  if(in[4+2+2]) strncpy(out->branch, &in[4+2+2], 3);
  else out->branch[0]= '\000'; /* primary office: XXX */
  out->bank[4]= out->country[2]= out->location[2]= out->branch[3]= '\000';
  return out;
}

char *bic_join(char out[11+1], const bic_t *in) {
  strncpy(&out[0], in->bank, 4);
  strncpy(&out[4], in->country, 2);
  strncpy(&out[4+2], in->location, 2);
  strncpy(&out[4+2+2], in->branch, 3);
  return out;
}

int bic_verify(const char *s) {
  int err= -1; /* unknown error */
  if(s) {
    char *clps= (char *)malloc(strlen(s)+1);
    if(clps) {
      size_t clps_len= strlen(bic_collapse(clps, s));
      if(clps_len == 8 || clps_len == 11) {
	bic_t bic;
	bic_split(&bic, clps);
	if(bic_isalpha(bic.bank[0]) &&
	   bic_isalpha(bic.bank[1]) &&
	   bic_isalpha(bic.bank[2]) &&
	   bic_isalpha(bic.bank[3]) &&
	   bic.bank[4] == '\000') {
	  if(bic_isalpha(bic.country[0]) &&
	     bic_isalpha(bic.country[1]) &&
	     bic.country[2] == '\000') {
	    if(bic_isalnum(bic.location[0]) &&
	       bic_isalnum(bic.location[1]) &&
	       bic.location[2] == '\000') {
	      if(bic.branch[0] == '\000' ||
		 (bic_isalnum(bic.branch[0]) &&
		  bic_isalnum(bic.branch[1]) &&
		  bic_isalnum(bic.branch[2]) &&
		  bic.branch[3] == '\000')) {
		err= BIC_ERR_OK;
	      }
	      else err= BIC_ERR_BRANCH;
	    }
	    else err= BIC_ERR_LOCATION;
	  }
	  else err= BIC_ERR_COUNTRY;
	}
	else err= BIC_ERR_BANK;
      }
      else err= BIC_ERR_LENGTH;
      free(clps); clps= (char *)0;
    }
    else err= BIC_ERR_NOMEM;
  }
  else err= BIC_ERR_BADARGS;
  return err;
}

char *bic_error(int ecd) {
  char *etx= (char *)0;
  switch(ecd) {
  case BIC_ERR_OK:
    etx= "No error"; break;
  case BIC_ERR_BADARGS:
    etx= "Bad arguments / null pointer"; break;
  case BIC_ERR_NOMEM:
    etx= "Not enough memory"; break;
  case BIC_ERR_LENGTH:
    etx= "Invalid length (must be 8 or 11)"; break;
  case BIC_ERR_BANK:
    etx= "Bank code contains invalid character(s)"; break;
  case BIC_ERR_COUNTRY:
    etx= "Country code contains invalid character(s)"; break;
  case BIC_ERR_LOCATION:
    etx= "Location code contains invalid character(s)"; break;
  case BIC_ERR_BRANCH:
    etx= "Branch code contains invalid character(s)"; break;
  default:
    etx= "Unknown error"; break;
  }
  return etx;
}
