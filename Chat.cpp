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
using namespace std;
#include <iomanip>
#include <fstream>
#include "Chat.h"


void initializeChat(tChat &chat, string id) {

	chat.idSender = id;
}


void loadChat(tChat &chat, ifstream &input) {

	input >> chat.idChat;

	loadMessageList(chat.chatMessages, input, chat.idChat);

}


void saveChat(ofstream &output, const tChat &chat) {

	output << chat.idChat << endl;

	saveMessageList(output, chat.chatMessages);
}


void showHorizontalLine() {

	for (int n = 0; n < 80; n++) { //80 corresponds to the number of characters you enter a line in Command Prompt.
		cout << char(196);
	}
}


void showHeaderChat(const tChat &chat, int cuentaChat, string id, tDate connection) {

	int counter = chat.chatMessages.counter - 1;
	tMessage aux;
	string sender = obtainSender(chat.chatMessages, counter);

	cout << " " << cuentaChat << "- " << chat.idChat << ". Last connection: ";
	cout << showDate(connection) << endl << endl;
	obtainLastMessage(chat.chatMessages, aux);

	if (sender != id) {
		cout << "      " << showMessage(aux) << endl;
	}

	else {
		cout << setw(ALI_RECEPTION) << showMessage(aux) << endl;
	}

	showHorizontalLine();
}


void showMessages(const tChat &chat, string id) {

	tMessage aux;

	for (int n = 0; n < chat.chatMessages.counter; n++) {

		string sender = obtainSender(chat.chatMessages, n);

		obtainMessage(chat.chatMessages, aux, n);

		if (sender != id) {
			cout << "   " << showMessage(aux) << endl;
		}

		else {
			cout << setw(ALI_RECEPTION) << showMessage(aux) << endl;
		}

		showHorizontalLine();
	}
}