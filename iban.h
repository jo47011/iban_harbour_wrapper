/* $Id: iban.h,v 1.7 2012/07/07 11:18:30 ferber Exp $ */

#ifndef __IBAN_H__
#define __IBAN_H__

#include "iban.ch"

#ifdef __cplusplus
extern "C" {
#endif /* C++ */

/* iban.c */
extern int iban_isdigit(int c);
extern int iban_isalpha(int c);
extern int iban_isalnum(int c);
extern int iban_isspace(int c);

extern char *iban_collapse(char *iban_out, const char *iban_in);
extern char *iban_expand(char *iban_out, const char *iban_in);
extern int iban_mod97(const char *iban);
extern char *iban_from_bban(char *iban, const char *country, const char *bban);

/* verify.c */
extern int iban_verify(const char *iban);

/* de.c */
extern char *iban_from_blz_kto(char *iban, const char *blz, const char *kto);

/* error.c */
extern char *iban_error(char *etx, int ecd);

#ifdef __cplusplus
}
#endif /* C++ */

#endif /*!__IBAN_H__*/
