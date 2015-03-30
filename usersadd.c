/*
 * usersadd.c
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
#include <strings.h>
#include <getopt.h>
#include <unistd.h>
#include <sys/types.h>

#include "ua_crypt.h"
#include "ua_struct.h"
#include "ua_define.h"

static const struct option long_opts[] = {
	{"file", required_argument, 0, 'f'},
	{"help", no_argument, 0, 'h'},
	{NULL, no_argument, NULL, 0}
};

void
usage (char **argv) {
	fprintf (stdout, "Usage: %s [-f file] [-h]\n", argv[0]);
	fprintf (stdout, "  --help (-h) - print this message\n");
	fprintf (stdout, "  --file (-f file) - file with users login. "
						"By default used /etc/usersadd/users.lst\n");
}

int add_users (char *pfile_path) {
	FILE *pusers_list = NULL;
	if ((pusers_list = fopen (pfile_path, "r")) == NULL) {
		fprintf (stderr, "Can't open file \"%s\": ", pfile_path);
		perror ("");
		return (-1);
	}
	FILE *ppasswd = NULL;
	if ((ppasswd = fopen ("/etc/passwd", "a")) == NULL) {
		perror ("Can't open file \"/etc/passwd\"");
		fclose (pusers_list);
		return (-1);
	}
	FILE *pshadow = NULL;
	if ((pshadow = fopen ("/etc/shadow", "a")) == NULL) {
		perror ("Can't open file \"/etc/shadow\"");
		fclose (pusers_list);
		fclose (ppasswd);
		return -1;
	}
	FILE *pgroup = NULL;
	if ((pgroup = fopen ("/etc/group", "a")) == NULL) {
		perror ("Can't open file \"/etc/group\"");
		fclose (pusers_list);
		fclose (ppasswd);
		fclose (pshadow);
		return (-1);
	}
	
	char *plogin  = (char *) calloc (MAX_LOGIN_LENGTH, sizeof (char));
	unsigned int num = 0;
	
	while (fscanf (pusers_list, "%s", plogin) != EOF) {
		account *pacc = account_init (plogin, num);
		
		char *ppasswd_line = format_to_passwd (pacc);
		char *pshadow_line = format_to_shadow (pacc);
		char *pgroup_line  = format_to_group  (pacc);
		fprintf (ppasswd, "%s", ppasswd_line);
		fprintf (pshadow, "%s", pshadow_line);
		fprintf (pgroup,  "%s", pgroup_line );
		num++;
		
		free (ppasswd_line);
		free (pshadow_line);
		free (pgroup_line);
		free (pacc->puser);
		free (pacc);
	}
	free (plogin);
	
	fclose (ppasswd);
	fclose (pshadow);
	fclose (pgroup);
	fclose (pusers_list);
	
	return num; //added users count
}

int 
main(int argc, char **argv) {
	
	char *pfile_path = DEFAULT_FILE_PATH;
	
	char opt = 0;
	while ((opt = getopt_long (argc, argv, "hf:", long_opts, NULL)) != -1) {
		switch (opt) {
			case 'f':
				pfile_path = optarg;
				break;
			case 'h':
				usage (argv);
				return 0;
			default:
				usage (argv);
				return -1;
		}
	} 
	
	if (geteuid ()) 
		fprintf (stderr, "Effective user id is not 0.\n" 
							"You may not have required permissions\n");
	
	int ret = add_users (pfile_path);
	if (ret < 0)
		fprintf (stderr, "Can't add users\n");
	else
		fprintf (stdout, "%d users added\n", ret);
					
	return 0;
}

