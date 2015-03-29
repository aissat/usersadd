/*
 * ua_struct.h
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


#ifndef UA_STRUCT_H
#define UA_STRUCT_H

#define _XOPEN_SOURCE

typedef struct {
	char *plogin;
	char *pcrypted_password;
	unsigned int uid;
	unsigned int gid;
	char *pGECOS;
	char *phome_dir;
	char *pshell;
} user_info;

//typedef struct user_info user_info;

typedef struct {
	user_info *puser;
	unsigned int date;
	unsigned int min_time_pass_change;
	unsigned int max_time_pass_change;
	unsigned int days_to_notify;
	unsigned int days_to_null;
	unsigned int expiration;
} account;

char *
format_to_passwd (account *pacc);

char *
format_to_shadow (account *pacc);

char *
format_to_group  (account *pacc);

account *
account_init (char *plogin, unsigned int num);

user_info *
user_info_init (char *plogin, unsigned int num);
#endif
