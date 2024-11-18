/* $Id: hbbic.c,v 1.3 2012/07/12 14:04:45 ferber Exp $ */

#include <hbapi.h>
#include "bic.h"

HB_FUNC( BIC_COLLAPSE ) {
  const char *in= hb_parcx(1);
  HB_ISIZ in_len= hb_parclen(1);
  char *out= (char *)hb_xgrab(in_len+1);
  hb_retc_buffer(bic_collapse(out, in));
}

HB_FUNC( BIC_VERIFY ) {
  hb_retni(bic_verify(hb_parcx(1)));
}

HB_FUNC( BIC_ERROR ) {
  hb_retc(bic_error(hb_parni(1)));
}

HB_FUNC( BIC_SPLIT ) {
  bic_t bic;
  bic_split(&bic, hb_parcx(1));
  hb_reta(4);
  hb_storvc(bic.bank, -1, 1);
  hb_storvc(bic.country, -1, 2);
  hb_storvc(bic.location, -1, 3);
  hb_storvc(bic.branch[0] ? bic.branch : "XXX", -1, 4);
}

HB_FUNC( BIC_JOIN ) {
  PHB_ITEM a= hb_param(1, HB_IT_ANY);
  if(a && !HB_IS_NIL(a) && HB_IS_ARRAY(a) && hb_arrayLen(a) == 4) {
    char *out= (char *)hb_xgrab(4+2+2+3+1);
    strncpy(&out[0], hb_arrayGetC(a, 1), 4);
    strncpy(&out[4], hb_arrayGetC(a, 2), 2);
    strncpy(&out[4+2], hb_arrayGetC(a, 3), 2);
    strncpy(&out[4+2+2], hb_arrayGetC(a, 4), 3);
    out[4+2+2+3]= '\000';
    hb_retc_buffer(out);
  }
  else hb_ret();
}

