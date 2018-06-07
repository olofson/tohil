/*
 * tohil.h - Tohil 2D Game Engine
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

#ifndef TOHIL_H
#define TOHIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "th_state.h"
#include "th_view.h"

/* Versioning */
#define	TH_MAKE_VERSION(major, minor, micro, build)	\
		(((major) << 24) | ((minor) << 16) | ((micro) << 8) | (build))
#define	TH_MAJOR(ver)	(((ver) >> 24) & 0xff)
#define	TH_MINOR(ver)	(((ver) >> 16) & 0xff)
#define	TH_MICRO(ver)	(((ver) >> 8) & 0xff)
#define	TH_BUILD(ver)	((ver) & 0xff)

/* Current version */
#define	TH_VERSION	TH_MAKE_VERSION(@VERSION_MAJOR@, @VERSION_MINOR@, @VERSION_PATCH@, @VERSION_BUILD@)


/*---------------------------------------------------------
	Error handling
---------------------------------------------------------*/

/* Return last error code set by a Tohil call, and reset the error status. */
TH_errors th_LastError(void);

/*
 * Return textual explanation of a Tohil error code. This will construct an
 * INTERNAL WARNING message for errors that should not occur unless there are
 * bugs in Tohil itself.
 */
const char *th_ErrorString(TH_errors errorcode);

/*
 * Return the name or description of the specified error code. These calls
 * return NULL for internal or unknown errors.
 */
const char *th_ErrorName(TH_errors errorcode);
const char *th_ErrorDescription(TH_errors errorcode);


/*---------------------------------------------------------
	Versioning
---------------------------------------------------------*/

/* Return version of the Tohil headers the application was built with. */
static inline unsigned th_HeaderVersion(void)
{
	return TH_VERSION;
}

/* Return version of the linked Tohil library. */
unsigned th_LinkedVersion(void);

#ifdef __cplusplus
};
#endif

#endif /* TOHIL_H */
