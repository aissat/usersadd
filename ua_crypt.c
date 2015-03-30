/*
 * ua_crypt.c
 * 
 * Copyright 2015 Ivin Artem <ivin.artem@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
 
#define _XOPEN_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ua_crypt.h"
#include "ua_define.h"

char * 
saltgen (unsigned int length) {
	char *psalt = (char *) calloc (length, sizeof (char));
	srand (rand ());
	
	int i = 0;
	for (; i < length; i++) {
		psalt [i] = rand () % 256;
	}
	return psalt;
}

char *
passgen (char *ppassgen_path, unsigned int length) {
	char *pcmd = (char *) calloc (MAX_FIELD_LENGTH, sizeof (char));
	
	//See here, if default passgen script was modified
	//TODO: as option
	sprintf (pcmd, "%s -c 1 -l %d", ppassgen_path, length);
	
	FILE *pfd = popen (pcmd, "r");
	char *ppass = (char *) calloc (length, sizeof(char));
	fscanf (pfd, "%s", ppass);
	pclose (pfd);
	free (pcmd);
	return ppass;
}

