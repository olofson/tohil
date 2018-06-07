/*
 * tohil.c - Tohil main file - configuration, open/close etc
 *
 * Copyright 2018 David Olofson <david@olofson.net>
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the
 * use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include <stdio.h>
#include <stdlib.h>
#include "tohil.h"


/*---------------------------------------------------------
	Error handling
---------------------------------------------------------*/

#define	TH_DEFERR(x, y)	y,
static const char *th_errdescs[] = {
	"Ok - no error!",
	TH_ALLERRORS
};
#undef	TH_DEFERR


#define	TH_DEFERR(x, y)	#x,
static const char *th_errnames[] = {
	"OK",
	TH_ALLERRORS
};
#undef	TH_DEFERR


static char th_errbuf[128];


TH_errors th_last_error = TH_OK;


TH_errors th_LastError(void)
{
	return th_last_error;
}


const char *th_ErrorString(TH_errors errorcode)
{
	if((errorcode >= 0) && (errorcode < TH_INTERNAL))
		return th_errdescs[errorcode];
	else
	{
		th_errbuf[sizeof(th_errbuf) - 1] = 0;
		snprintf(th_errbuf, sizeof(th_errbuf) - 1,
				"INTERNAL ERROR #%d; please report to "
				"<david@olofson.net>",
				errorcode - TH_INTERNAL);
		return th_errbuf;
	}
}


const char *th_ErrorName(TH_errors errorcode)
{
	if((errorcode >= 0) && (errorcode < TH_INTERNAL))
		return th_errnames[errorcode];
	else
		return NULL;
}


const char *th_ErrorDescription(TH_errors errorcode)
{
	if((errorcode >= 0) && (errorcode < TH_INTERNAL))
		return th_errdescs[errorcode];
	else
		return NULL;
}


/*---------------------------------------------------------
	Versioning
---------------------------------------------------------*/

unsigned th_LinkedVersion(void)
{
	return TH_VERSION;
}
