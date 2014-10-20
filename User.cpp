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
#include "User.h"


void initializeUser(tUser &user) {

	user.lastConnection = time(0);
}


bool loadUser(ifstream &input, tUser &user) {

	tUser userAux;
	bool stop = true;

	input >> userAux.id;
	input >> userAux.password;
	input >> userAux.lastConnection;

	if (userAux.id != "End") {
		loadMessageList(userAux.unread, input, userAux.id);
		user = userAux;

		stop = false;
	}
	return stop;
}


void saveUser(ofstream &output, tUser user) {

	output << user.id << endl;
	output << user.password << endl;
	output << user.lastConnection << endl;
	saveMessageList(output, user.unread);

}