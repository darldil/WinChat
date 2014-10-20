/*  WinChat 3.1.2
 *   Copyright 2014  Mauricio Abbati Loureiro.
 *
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *   Designed for Windows
 */


#ifndef UserList_h
#define User

#include "User.h"

const int MAX_USERS = 50; //Máximo de usuarios admitidos.

typedef tUserPtr tUsuarios[MAX_USERS];

typedef struct {
	tUsuarios users;
	int counter;
}tUserList;


/*
	It is responsible for initializing a list of users.
	INPUT: uninitialized list.
	OUTPUT: list initialized.
*/
void initializeUserList(tUserList &list);
/*
	It is responsible for loading users from a file. 
	INPUT: list of users. 
	OUTPUT: list of users updated and Boolean verification.
*/
bool loadUserList(tUserList &list);
/*
	It handles users save a file. 
	INPUT: list of users.
*/
void saveUserList(const tUserList &list);
/*
	Given a user loads a position in a single variable from 
	the list of users. 
	INPUT: list of users, varying the position empty user to find. 
	OUTPUT: Variable user charged.
*/
void obtainUser(const tUserList &list, tUser &user, int pos);
/*
	Given a user name in the list of searches users position 
	one user. 
	INPUT: list of users, name to search. 
	OUTPUT: Position in located (-1 if not found).
*/
int findUsers(const tUserList &list, string seBusca);
/*
	List users in orderly list. 
	INPUT: list of users and user entered. 
	OUTPUT: list of users ordered.
*/
void insertUser(tUserList &list, tUser user);
void destroyUserList(tUserList &list);

#endif