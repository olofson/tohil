/*
 * hello.c - Minimal Tohil example
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


static void print_version(const char *exename)
{
	unsigned v = th_LinkedVersion();
	fprintf(stderr, "%s\n"
			"Linked against Tohil v%d.%d.%d.%d\n",
			exename,
			TH_MAJOR(v),
			TH_MINOR(v),
			TH_MICRO(v),
			TH_BUILD(v));
	v = th_HeaderVersion();
	fprintf(stderr, "Compiled against Tohil v%d.%d.%d.%d\n",
			TH_MAJOR(v),
			TH_MINOR(v),
			TH_MICRO(v),
			TH_BUILD(v));
}


static void fail(unsigned where, TH_errors err)
{
	fprintf(stderr, "ERROR at %d: %s\n", where, th_ErrorString(err));
	exit(100);
}


int main(int argc, char *argv[])
{
	TH_state *st;
	TH_view *v;

	print_version(argv[0]);

	if(!(st = th_Open("Tohil: Hello", TH_CENTER, TH_CENTER, 640, 480, 0)))
		fail(1, th_LastError());

	th_Run(st, 2000);

	th_Close(st);

	return 0;
}
