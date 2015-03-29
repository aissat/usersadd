/*
 * ua_struct.c
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

#include "ua_struct.h"
#include "ua_crypt.h"
#include "ua_define.h"

/*
 *
 *	typedef struct {
 *	 	char *plogin;
 *		char *pcrypted_password;
 *		unsigned int uid;
 *		unsigned int gid;
 *		char *pGECOS;
 *		char *phome_dir;
 *		char *pshell;
 *	} user_info; 
 *
 *	typedef stuct {
 *		user_info *puser;
 *		unsigned int date;
 *		unsigned int min_time_pass_change;
 *		unsigned int max_time_pass_change;
 *		unsigned int days_to_notify;
 *		unsigned int days_to_null;
 *		unsigned int expiration;
 *	} account;
 *
 */

user_info *
user_info_init (char *plogin, unsigned int num) {
	user_info *puser = (user_info *) calloc (1, sizeof (user_info));
	puser->plogin = plogin;
	char *ppass = passgen (PASSGEN_PATH, DEFAULT_PASSWORD_LENGTH);
	fprintf (stdout, "Login: %s\nPassword: %s\n\n", 
				puser->plogin, ppass);
	
	char *psalt = saltgen (2);
	puser->pcrypted_password = crypt (ppass, psalt);
	free (ppass);
	free (psalt);
	//TODO: search for unused uids and gids
	puser->uid = num + DEFAULT_START_UID;
	puser->gid = num + DEFAULT_START_UID;
	
	//by default:
	puser->pGECOS = "";
	puser->phome_dir = "/";
	puser->pshell = "/bin/bash";
	
	return puser;
}
			
account *
account_init (char *plogin, unsigned int num) {
	account *pacc = (account *) calloc (1, sizeof (account));
	pacc->puser = user_info_init(plogin, num);
	pacc->date = 1; //TODO: Add date calculation
	//All anower fields of "pacc" is NULL (calloc)
	
	return pacc;
}
	
char *
format_to_passwd (account *pacc) {
	char *pret = (char *) calloc (MAX_FIELD_LENGTH, sizeof (char));
	
	sprintf (pret, "%s:%s:%d:%d:%s:%s:%s\n", 
						pacc->puser->plogin,
						"x",	/*
								 * pacc->puser->pcrypted_password
								 * Crypted password will saved 
								 * in shadow file
								 */
						pacc->puser->uid,
						pacc->puser->gid,
						pacc->puser->pGECOS,
						pacc->puser->phome_dir,
						pacc->puser->pshell);
	
	return pret;
}

char *
format_to_shadow (account *pacc) {
	char *pret = (char *) calloc (MAX_FIELD_LENGTH, sizeof (char));
	
	/*
	 * Minimal info to /etc/shadow.
	 * TODO: more info
	 */
	sprintf (pret, "%s:%s:%d:%d:::::\n", 	
						pacc->puser->plogin,
						pacc->puser->pcrypted_password,
						pacc->date,
						pacc->min_time_pass_change);
					
	return pret;
}

char *
format_to_group (account *pacc) {
	char *pret = (char *) calloc (MAX_FIELD_LENGTH, sizeof (char));
	
	/*
	 * Default user group names as user login.
	 * Without password
	 */
	sprintf (pret, "%s:x:%d:\n", pacc->puser->plogin, pacc->puser->gid);
					
	return pret;
}
