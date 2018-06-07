/*
 * state.c - Tohil: Engine state/window
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

#include "internals.h"
#include "state.h"

#include <stdlib.h>


TH_state *th_Open(const char *title, int x, int y, int w, int h,
		unsigned flags)
{
	TH_state *st;

	if(x < 0)
	{
		switch(x)
		{
		  case TH_CENTER:
			x = SDL_WINDOWPOS_CENTERED;
			break;
		  case TH_UNDEFINED:
			x = SDL_WINDOWPOS_UNDEFINED;
			break;
		  default:
			th_last_error = TH_BADVALUE;
			return NULL;
		}
	}

	if(y < 0)
	{
		switch(y)
		{
		  case TH_CENTER:
			y = SDL_WINDOWPOS_CENTERED;
			break;
		  case TH_UNDEFINED:
			y = SDL_WINDOWPOS_UNDEFINED;
			break;
		  default:
			th_last_error = TH_BADVALUE;
			return NULL;
		}
	}

	if(w < 0)
	{
		switch(w)
		{
		  case TH_UNDEFINED:
			if(!(flags & TH_FULLSCREEN) || (h != TH_UNDEFINED))
			{
				th_last_error = TH_BADVALUE;
				return NULL;
			}
			break;
		  default:
			th_last_error = TH_BADVALUE;
			return NULL;
		}
	}

	if(h < 0)
	{
		switch(h)
		{
		  case TH_UNDEFINED:
			/* (Checked above, for 'w'.)*/
			break;
		  default:
			th_last_error = TH_BADVALUE;
			return NULL;
		}
	}

	if(!(st = (TH_state *)calloc(1, sizeof(TH_state))))
	{
		th_last_error = TH_OOMEMORY;
		return NULL;
	}

	if(flags & TH_FULLSCREEN)
	{
		if(w == TH_UNDEFINED)
			st->wflags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		else
			st->wflags |= SDL_WINDOW_FULLSCREEN;
	}

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK) != 0)
	{
		free(st);
		th_last_error = TH_INITFAIL;
		return NULL;
	}

	if(!(st->window = SDL_CreateWindow(title, x, y, w, h, st->wflags)))
	{
		free(st);
		th_last_error = TH_OPENFAIL;
		return NULL;
	}

	if(flags & TH_VSYNC)
		st->rflags |= SDL_RENDERER_PRESENTVSYNC;
	if(!(st->renderer = SDL_CreateRenderer(st->window, -1, st->rflags)))
	{
		SDL_DestroyWindow(st->window);
		free(st);
		th_last_error = TH_OPENFAIL;
		return NULL;
	}

	/* Workaround for LogicalSize issues width certain display setups */
#if 1
	SDL_GetRendererOutputSize(st->renderer, &w, &h);
#else
	if(SDL_GetRendererOutputSize(st->renderer, &w, &h) < 0)
		th_log_printf(WLOG, "SDL_GetRendererOutputSize() failed! "
				"(%s)\n", SDL_GetError());
	else
		th_log_printf(WLOG, "SDL_GetRendererOutputSize(): %d x %d\n",
				w, h);
#endif
	SDL_RenderSetLogicalSize(st->renderer, w, h);

	return st;
}


void th_Close(TH_state *state)
{
	SDL_DestroyRenderer(state->renderer);
	SDL_DestroyWindow(state->window);
#if 0
	SDL_Quit();
#endif
	free(state);
}


TH_errors th_Run(TH_state *state, int timeout)
{
	if(timeout < 0)
	{
		switch(timeout)
		{
		  case TH_FRAME:
			break;
		  case TH_FOREVER:
			break;
		  case TH_POLL:
			break;
		  default:
			return TH_BADVALUE;
		}
	}
	else if(timeout == 0)
		return TH_OK;

	state->is_running = 1;
	int t0 = (int)SDL_GetTicks();
	while(state->is_running)
	{
		int t = (int)SDL_GetTicks();

		/* Handle input */
		//TODO

		/* Advance game logic to current time */
		//TODO

		/* Check for TH_POLL */
		if(timeout < 0)
		{
			switch(timeout)
			{
			  case TH_FRAME:
			  case TH_FOREVER:
				break;
			  case TH_POLL:
				return TH_OK;
			  default:
				return TH_BADVALUE;
			}
		}

		/* Calculate tweening/extrapolation */
		//TODO

		/* Render scene */
		//TODO

		/* Sync and present */
		SDL_RenderPresent(state->renderer);

		/* Check time limit */
		if(timeout < 0)
		{
			switch(timeout)
			{
			  case TH_FRAME:
				return TH_OK;
			  case TH_FOREVER:
				break;
			  case TH_POLL:
				break;
			  default:
				return TH_BADVALUE;
			}
		}
		else if(SDL_TICKS_PASSED(t, t0 + timeout))
			return TH_OK;
	}

	return TH_OK;
}
