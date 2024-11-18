/* $Id: test.prg,v 1.10 2012/07/12 14:06:48 ferber Exp $ */

#include "iban.ch"
#include "bic.ch"

PROCEDURE MAIN()
LOCAL iban, bic
LOCAL a, i
  //iban := iban_from_bban("06619000073086000", "DE")
  iban := iban_from_blz_kto("54550010", "1589043")
  ? iban_expand(iban)
  ? iban_verify(iban), iban_error(iban_verify(iban))

  //bic := "LUHS DE 6A"
  bic := bic_join(bic_split(bic_collapse("LUHS DE 6A")))
  ? bic
  ? bic_verify(bic), bic_error(bic_verify(bic))

  a := bic_split(bic)
  FOR i:=1 to LEN(a)
    ? a[i]
  NEXT

  RETURN
