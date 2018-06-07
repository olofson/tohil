/*
 * th_types.h - Tohil basic data types
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

#ifndef TH_TYPES_H
#define TH_TYPES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/*---------------------------------------------------------
	Various widely used Audiality 2 types
---------------------------------------------------------*/

typedef	int TH_handle;
typedef struct TH_state TH_state;
typedef struct TH_view TH_view;


/* Object types (Also used for RCHM handle type tagging!) */
typedef enum TH_otypes
{
	TH_TWINDOW = 1,	/* Rendering target; on-screen or off-screen */
	TH_TCAMERA,	/*  */
	TH_TGROUP,	/* Group container (applies transforms to children) */
	TH_TTILEMAP,	/* Tiled background layer */
	TH_TSTREAM,	/* Stream layer (procedural texture) */
	TH_TSPRITE,	/* Sprite */
	TH_TPSYSTEM,	/* Particle system */
	TH_TLENSFX,	/* "Lens effect" (fake rotating sphere) */
	TH_TFADEFILTER,	/* Fade/blur filter */
} TH_otypes;

/* Log levels */
typedef enum {
	/* Log levels */
	TH_LOG_INTERNAL =	0x00000001,
	TH_LOG_CRITICAL =	0x00000002,
	TH_LOG_ERROR =		0x00000010,
	TH_LOG_WARNING =	0x00000020,
	TH_LOG_INFO =		0x00000040,
	TH_LOG_MESSAGE =	0x00000080,
	TH_LOG_DEBUG =		0x00001000,
	TH_LOG_DEVELOPER =	0x01000000,

	/* Log level group masks */
	TH_LOGM_CRITICAL =	0x0000000f,
	TH_LOGM_NORMAL =	0x00000ff0,
	TH_LOGM_DEBUG =		0x00fff000,
	TH_LOGM_DEVELOPER =	0xff000000,

	/* Default log level mask */
	TH_LOGM_DEFAULT =	TH_LOGM_CRITICAL | TH_LOGM_NORMAL,

	TH_LOGM_ALL =		0xffffffff
} TH_loglevels;


/*---------------------------------------------------------
	NULL (stolen from the GNU C Library)
---------------------------------------------------------*/
#ifndef NULL
#	if defined __GNUG__ &&					\
			(__GNUC__ > 2 ||			\
			(__GNUC__ == 2 && __GNUC_MINOR__ >= 8))
#		define NULL (__null)
#	else
#		if !defined(__cplusplus)
#			define NULL ((void*)0)
#		else
#			define NULL (0)
#		endif
#	endif
#endif


/*---------------------------------------------------------
	Error handling
---------------------------------------------------------*/

#define TH_ALLERRORS	\
/* === NOTE: These first codes should match RCHM_errors! === */\
  TH_DEFERR(REFUSE,		"Destruction refused")\
  TH_DEFERR(OOMEMORY,		"Out of memory")\
  TH_DEFERR(OOHANDLES,		"Out of handles")\
  TH_DEFERR(INVALIDHANDLE,	"Invalid handle")\
  TH_DEFERR(FREEHANDLE,		"Handle already returned to the free pool")\
/* ========================================================= */\
  TH_DEFERR(BADCONFIG,		"Bad engine configuration")\
  TH_DEFERR(BADRESOLUTION,	"Unsupported display resolution")\
  TH_DEFERR(BADVALUE,		"Bad or unrecognized argument value")\
  TH_DEFERR(OORANGE,		"Argument out of range")\
  TH_DEFERR(INITFAIL,		"Subsystem initialization failed")\
  TH_DEFERR(OPENFAIL,		"Device open failed")\
  \
  TH_DEFERR(INTERNAL,		"INTERNAL ERROR")	/* Must be last! */

#define	TH_DEFERR(x, y)	TH_##x,
typedef enum TH_errors
{
	TH_OK = 0,
	TH_ALLERRORS
} TH_errors;
#undef	TH_DEFERR

#ifdef __cplusplus
};
#endif

#endif /* TH_TYPES_H */
