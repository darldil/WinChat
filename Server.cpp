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


#include "Server.h"

bool loadServer(tServer &data) {

	bool loaded = false;

	initializeUserList(data);

	if (loadUserList(data)) {
		loaded = true;
	}

	return loaded;
}


void sendMessage(tServer &data, tMessage newMessage) {

	int userPos = findUsers(data, newMessage.idUserReceiver);
	tUser usuarioActual;

	obtainUser(data, usuarioActual, userPos);

	if (userPos != -1) {
		addMessageToEnd(usuarioActual.unread, newMessage);
		*data.users[userPos] = usuarioActual;
	}
}


void obtainNewMessages(tServer &server, tMessageList &newMessages, string id) {

	int userPos = findUsers(server, id);
	tUser usuario;

	obtainUser(server, usuario, userPos);
	
	int tamMax = nextTen(usuario.unread.counter);
	initializeVariableMessageList(newMessages, tamMax);

	for (int n = 0; n < usuario.unread.counter; n++) {
		newMessages.msgList[n] = usuario.unread.msgList[n];
		newMessages.counter++;
	}

	usuario.unread.counter = 0;

	*server.users[userPos] = usuario;
}