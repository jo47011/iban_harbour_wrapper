/* $Id: test.prg,v 1.10 2012/07/12 14:06:48 ferber Exp $ */

#include "iban.ch"
#include "bic.ch"

PROCEDURE MAIN()
LOCAL iban, bic
LOCAL a, i
  iban := iban_from_blz_kto("477239024342", "2223234234")
  ? iban_expand(iban)
  ? iban_verify(iban), iban_error(iban_verify(iban))

  bic := bic_join(bic_split(bic_collapse("INGFOO DE 6A")))
  ? bic
  ? bic_verify(bic), bic_error(bic_verify(bic))

  a := bic_split(bic)
  FOR i:=1 to LEN(a)
    ? a[i]
  NEXT

  RETURN
