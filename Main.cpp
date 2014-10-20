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


#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
#include <iomanip>
#include "Client.h"
#pragma comment (lib, "winmm.lib")

/*
	Displays an error if the user's file it's not available.
	OUTPUT: message on screen.
*/
void userError();
/*
	Allows the user to log in with your id and password.
	INPUT: server and identifier.
	OUTPUT: VALID ID.
*/
void logIn(const tServer &server, string &id);

//----------------------------------------------> START OF WINCHAT <-------------------------------------------------//

int main() {

	system("color 70");
	tServer server;
	string  id;

	if (loadServer(server)) {

		while (id != "0") {
			logIn(server, id);

			if (id != "0") {
				system("cls");
				runClient(server, id);
			}
		}
		saveUserList(server);
	}

	else {
		userError();
	}

	PlaySound("C:\\WINDOWS\\Media\\Windows Shutdown.wav", NULL, SND_NODEFAULT);

	return 0;
}


void userError() {

	cout << setw(45) << VERSION << endl;
	PlaySound("C:\\WINDOWS\\Media\\chord.wav", NULL, SND_ASYNC | SND_NODEFAULT);
	cout << "CATASTROPHIC ERROR!! Couldn't find the file users!!" << endl;
	cout << "The application can not continue and will shut" << endl;
	Sleep(3000);
}


void logIn(const tServer &server, string &id) {

	int pos = findUsers(server, id);
	string correctPass, pass;

	do {
		system("cls");
		cout << setw(45) << VERSION << endl;
		cout << "Welcome" << endl;

		cout << "Enter your ID (0 out): ";
		cin >> id;
		cin.sync();

		if (id != "0" && id != "") {
			cout << "Type your password: ";
			cin >> pass;
			cin.sync();
		}

		pos = findUsers(server, id);
		if (pos != -1) {
			correctPass = server.users[pos]->password;
		}

		if (pass != correctPass && id != "0"){
			PlaySound("C:\\WINDOWS\\Media\\chord.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		}
	} while ((id == "" || pos == -1 || pass != correctPass) && id != "0");
}