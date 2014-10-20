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


#ifndef User_h
#define User_h

#include "MessageList.h"

typedef struct {
	string id;
	string password;
	tDate lastConnection;
	tMessageList unread;
}tUser;

typedef tUser *tUserPtr;


/*
	Initialize a user.
	INPUT: user.
	OUTPUT: user initialized.
*/
void initializeUser(tUser &user);
/*
	Loads a user from a file.
	INPUT: user and open ifstream.
	OUTPUT: boolean user loaded and verification.
*/
bool loadUser(ifstream &input, tUser &user);
/*
	Saves a user to a file.
	INPUT: user and ofstream open.
*/
void saveUser(ofstream &output, tUser user);

#endif