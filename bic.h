/* $Id: bic.h,v 1.3 2012/07/12 14:04:45 ferber Exp $ */

#ifndef __BIC_H__
#define __BIC_H__

#include "bic.ch"

/* Bank Identifier Code */
typedef struct {
  char bank[4+1]; /* bank code (alpha) */
  char country[2+1]; /* ISO 3166-1 alpha 2 (alpha) */
  char location[2+1]; /* (alnum) */
  char branch[3+1]; /* (alnum) */
} bic_t;

#ifdef __cplusplus
extern "C" {
#endif /* C++ */

extern char *bic_collapse(char *out, const char *in);
extern bic_t *bic_split(bic_t *out, const char *in);
extern char *bic_join(char out[11+1], const bic_t *in);
extern int bic_verify(const char *bic);
extern char *bic_error(int ecd);

#ifdef __cplusplus
}
#endif /* C++ */

#endif /*!__BIC_H__*/
