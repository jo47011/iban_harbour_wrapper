/* $Id: iban.ch,v 1.4 2012/07/17 07:06:00 ferber Exp $ */

#ifndef __IBAN_CH__
#define __IBAN_CH__

#define IBAN_MAXLEN (2+2+30)

/* Maximum length including cosmetic spaces and trailing NUL. */
#define IBAN_BUFSIZE (IBAN_MAXLEN+10+1)

/* de.c */
#define IBAN_BLZ_MAXLEN 8
#define IBAN_KTO_MAXLEN 10

/* Error codes returned by iban_verify() */
#define IBAN_ERR_OK          0
#define IBAN_ERR_BADARGS   110
#define IBAN_ERR_NOMEM     120
#define IBAN_ERR_COUNTRY   130
#define IBAN_ERR_LENGTH    200
#define IBAN_ERR_CHECKSUM  300
#define IBAN_ERR_DIGIT     500
#define IBAN_ERR_ALPHA     600
#define IBAN_ERR_ALNUM     700

/* Max. number of characters returned by iban_error() */
#define IBAN_ETX_MAXLEN    128

#endif /*!__IBAN_CH__*/
