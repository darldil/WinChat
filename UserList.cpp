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


#include <fstream>
#include "UserList.h"

void initializeUserList(tUserList &list) {

	list.counter = 0;
}


bool loadUserList(tUserList &list) {

	ifstream input;
	tUser userAux;
	bool sentinel, loaded = false;

	input.open("WCTMP\\users.dat");

	if (input.is_open()) {

		initializeUser(userAux);
		sentinel = loadUser(input, userAux);

		while (list.counter < MAX_USERS && !sentinel) {
			insertUser(list, userAux);
			initializeUser(userAux);
			sentinel = loadUser(input, userAux);
		}

		input.close();
		loaded = true;
	}

	return loaded;
}


void saveUserList(const tUserList &list) {

	ofstream output;

	output.open("WCTMP\\users.dat");

	for (int n = 0; n < list.counter; n++) {
		saveUser(output, *list.users[n]);
	}

	output << "End";

	output.close();
}


void obtainUser(const tUserList &list, tUser &usuario, int pos) {
	usuario = *list.users[pos];
}


//Binary Search.
int findUsers(const tUserList &list, string seBusca) {

	int pos = -1, ini = 0, end = list.counter - 1, middle;
	bool found = false;

	while ((ini <= end) && !found) {
		middle = (ini + end) / 2;

		if (seBusca == list.users[middle]->id) {
			found = true;
		}
		else if (seBusca < list.users[middle]->id) {
			end = middle - 1;
		}
		else {
			ini = middle + 1;
		}
	}

	if (found) {
		pos = middle;
	}
	return pos;
}


void insertUser(tUserList &list, tUser usuario) {

	int i = 0;
	while ((i < list.counter) && (list.users[i]->id < usuario.id)) {
		i++;
	}

	for (int j = list.counter; j > i; j--) {
		list.users[j] = list.users[j - 1];
	}

	list.users[i] = new tUser(usuario);
	list.counter++;
}


void destroyUserList(tUserList &list) {

	for (int n = 0; n < list.counter; n++) {
		destroyMessageList(list.users[n]->unread);
		delete list.users[n];
	}

	list.counter = 0;
}