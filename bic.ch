/* $Id: bic.ch,v 1.2 2012/07/17 07:06:20 ferber Exp $ */

#ifndef __BIC_CH__
#define __BIC_CH__

#define BIC_MAXLEN (4+2+2+3)

/* bic_validate */
#define BIC_ERR_OK        0
#define BIC_ERR_BADARGS   1
#define BIC_ERR_NOMEM     2
#define BIC_ERR_LENGTH    3
#define BIC_ERR_BANK      4
#define BIC_ERR_COUNTRY   5
#define BIC_ERR_LOCATION  6
#define BIC_ERR_BRANCH    7

#endif /*!__BIC_CH__*/
