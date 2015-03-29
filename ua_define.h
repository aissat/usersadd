/*
 * ua_define.h
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
 
 
#ifndef UA_DEFINE_H
#define UA_DEFINE_H

#define _XOPEN_SOURCE

#define DEFAULT_FILE_PATH		"/etc/usersadd/users.lst"
#define MAX_LOGIN_LENGTH		256
#define DEFAULT_PASSWORD		"qwerty"
#define DEFAULT_PASSWORD_LENGTH	16
#define DEFAULT_START_UID		1500
#define DEFAULT_START_GID		1500
#define MAX_FIELD_LENGTH		1024

/*
 * If you want change path to passgen script, make sure what function
 * "passgen" (ua_crypt.c) is correct.
 */
#define PASSGEN_PATH ".scripts/passgen.sh"

#endif
