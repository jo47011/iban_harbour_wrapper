/* $Id: hbiban.c,v 1.4 2012/07/07 07:41:01 ferber Exp $ */

#include <hbapi.h>
#include "iban.h"

HB_FUNC( IBAN_COLLAPSE ) {
  const char *in= hb_parcx(1);
  HB_ISIZ in_len= hb_parclen(1);
  char *out= (char *)hb_xgrab(in_len+1);
  hb_retc_buffer(iban_collapse(out, in));
}

HB_FUNC( IBAN_EXPAND ) {
  const char *in= hb_parcx(1);
  HB_ISIZ in_len= hb_parclen(1);
  char *out= (char *)hb_xgrab(2*in_len+1);
  hb_retc_buffer(iban_expand(out, in));
}

#if 0
HB_FUNC( IBAN_MOD97 ) {
  hb_retni(iban_mod97(hb_parcx(1)));
}
#endif

HB_FUNC( IBAN_FROM_BBAN ) {
  const char *bban= hb_parcx(1);
  HB_ISIZ bban_len= hb_parclen(1);
  const char *country= hb_parcx(2);
  char *iban= (char *)hb_xgrab(4+bban_len+1);
  hb_retc_buffer(iban_from_bban(iban, country, bban));
}

HB_FUNC( IBAN_VERIFY ) {
  hb_retni(iban_verify(hb_parcx(1)));
}

HB_FUNC( IBAN_ERROR ) {
  int ecd= hb_parni(1);
  char *etx= (char *)hb_xgrab(IBAN_ETX_MAXLEN+1);
  hb_retc_buffer(iban_error(etx, ecd));
}

/* Caution: requires length of blz <= 8, kto <= 10 */
HB_FUNC( IBAN_FROM_BLZ_KTO ) {
  const char *blz= hb_parcx(1);
  const char *kto= hb_parcx(2);
  char *iban= (char *)hb_xgrab(4+8+10+1);
  hb_retc_buffer(iban_from_blz_kto(iban, blz, kto));
}

