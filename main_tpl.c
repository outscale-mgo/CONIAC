/**
 * BSD 3-Clause License
 *
 * Copyright (c) 2022, Outscale SAS
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **/

 /*
  * This code is autogenerated, don't edit it directely
  */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "json.h"
#include "osc_sdk.h"
#include "main-helper.h"

#ifndef JSON_C_TO_STRING_COLOR
#define JSON_C_TO_STRING_COLOR 0
#endif

#define OAPI_RAW_OUTPUT 1

#define TRY(f, args...)						\
	do {							\
		if (f) {fprintf(stderr, args);  return 1;}	\
	} while(0)

static int argcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1 && *s2) {
		s1++;
		s2++;
	}
	if ((*s2 == '.' && *s1 == '\0') ||
	    (*s1 == '.' && *s2 == '\0'))
		return 0;
	return *s1 != *s2;
}

static void *cascade_struct;
static int (*cascade_parser)(void *, char *, char *, struct ptr_array *);

____complex_struct_func_parser____

int main(int ac, char **av)
{
	struct osc_env e;
	struct osc_str r;
	int color_flag = 0;
	int i;
	char *help_appent = getenv("COGNAC_HELP_APPEND");
	unsigned int flag = 0;
	unsigned int program_flag = 0;

	for (i = 1; i < ac; ++i) {
		if (!strcmp("--verbose", av[i])) {
		  flag |= OSC_VERBOSE_MODE;
		} else if (!strcmp("--insecure", av[i])) {
		  flag |= OSC_INSECURE_MODE;
		}
	}
	TRY(osc_init_sdk(&e, NULL, flag), "fail to init C sdk\n");
	osc_init_str(&r);

	if (ac < 2) {
	show_help:
		printf("Usage: %s CallName [options] [--Params ParamArgument]\n"
		       "options:\n"
		       "\t--insecure	\tdoesn't verify SSL certificats\n"
		       "\t--raw-print	\tdoesn't format the output\n"
		       "\t--verbose	\tcurl backend is now verbose\n"
		       "\t--help	\t\tthis\n"
		       "\t--color	\t\ttry to colorize json if json-c support it\n%s%s",
		       av[0], help_appent ? help_appent : "",
		       help_appent ? "\n" : "");
		return 0;
	}

	for (i = 1; i < ac; ++i) {
		if (!strcmp("--verbose", av[i]) || !strcmp("--insecure", av[i])) {
			/* Avoid Unknow Calls */
		} else if (!strcmp("--help", av[i])) {
			if (av[i+1]) {
				const char *cd = osc_find_description(av[i+1]);
				if (cd) {
					puts(cd);
					return 0;
				} else {
					printf("Unknow Call %s\n", av[i+1]);
					return 1;
				}
			}
			goto show_help;
		} else if (!strcmp("--raw-print", av[i])) {
			program_flag |= OAPI_RAW_OUTPUT;
		} else if (!strcmp("--color", av[i])) {
			color_flag |= JSON_C_TO_STRING_COLOR;
		} else
		____cli_parser____
		{
			printf("Unknow Call %s\n", av[i]);
		}
	}

	osc_deinit_str(&r);
	osc_deinit_sdk(&e);
	return 0;
}
