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


#ifndef Server_h
#define Server_h

#include "UserList.h"
#include "ChatsList.h"

typedef tUserList tServer;

/*
	It is responsible for loading the server with data stored in a file.
	INPUT: empty server list.
	OUTPUT: Boolean verification of load and list refilled.
*/
bool loadServer(tServer &data);
/*
	Manages sending messages to the list of unread messages the user
	corresponding.
	INPUT: list of server and message entered.
	OUTPUT: list of current and Boolean verification server.
*/
void sendMessage(tServer &data, tMessage newMessage);
/*
	Manages the list of unread messages of a corresponding user.
	INPUT: list of server, and identifier list empty messages.
	OUTPUT: list of modified server (counter set to 0) and list of posts filled.
*/
void obtainNewMessages(tServer &server, tMessageList &newMessages, string id);

#endif