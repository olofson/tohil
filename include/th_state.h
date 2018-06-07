/*
 * th_state.h - Tohil: Engine state/window
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

#ifndef TH_STATE_H
#define TH_STATE_H

#include "th_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum TH_stateflags
{
	/* Flags for TH_state */
	TH_FULLSCREEN =	0x00000200,	/* Open in fullscreen mode */
	TH_VSYNC =	0x00000400,	/* Vsync'ed display refresh */

	TH_STATEFLAGS =	0x000fff00,	/* Mask for the flags above */
} TH_stateflags;

typedef enum TH_specialvalues
{
	/* Special values for state and view coordinates and sizes */
	TH_CENTER = -1,
	TH_UNDEFINED = -2,
	TH_DESKTOP = -3,

	/* Special values for th_Run() 'timeout' */
	TH_FRAME = -1,		/* Run for one rendered frame */
	TH_FOREVER = -2,	/* Run until interrupted */
	TH_POLL = -3,		/* Advance to input, and/or poll input only */
} TH_specialvalues;

/* Create a Tohil state and output window. */
TH_state *th_Open(const char *title, int x, int y, int w, int h,
		unsigned flags);

/* Close and destroy a state with window. */
void th_Close(TH_state *state);

/* Run state for the specified amount of time. */
TH_errors th_Run(TH_state *state, int timeout);

#ifdef __cplusplus
};
#endif

#endif /* TH_STATE_H */
