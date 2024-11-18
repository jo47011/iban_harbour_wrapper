# iban_harbour_wrapper
Simple IBAN helper library, including a Harbour wrapper.

== Files ==

iban.h: C function declarations.
iban.ch: Shared definitions for both C and Harbour.
iban.c: IBAN string operations.
verify.c: IBAN verification routines.
de.c: Guess IBAN from German BLZ and KTO (dangerous).
error.c: Generate error text from error codes.
hbiban.c: Harbour wrapper.
main.c: Test program (C).
test.prg: Test program (Harbour).
test.hbp, hbiban.hbc: build rules for test.prg with hbmk2.

bic.c, bic.h, bic.ch, hbbic.c: Bank identifier code support.

== General Notes ==

* IBANs and BICs consist only of digits and upper case letters (7 bit ASCII).
* Country codes in IBAN and BIC are not the same in all countries.
*

Resposibilities of the caller:

* iban_mod97: use a collapsed IBAN, ensure length > 4.
* iban_from_blz_kto: IBANs can be invalid for sub-accounts.
* iban_from_blz_kto: ensure collapsed length of BLZ <= 8 and KTO <= 10.
* iban_from_blz_kto: use iban_verify on the generated IBAN.

* bic_verify: returns zero (ok) even if the BIC is not collapsed
* bic_join: can return an invalid BIC for invalid args; use bic_verify.
* bic_split: always returns a BIC11; primary office (branch XXX) = default.
