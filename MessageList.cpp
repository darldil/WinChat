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
#include "MessageList.h"


void initializeMessageList(tMessageList &list) {

	list.counter = 0;
	list.msgList = new tMessage[MAX_MESSAGES];
	list.max = MAX_MESSAGES;
}


void initializeVariableMessageList(tMessageList &list, int sizeList) {

	list.counter = 0;
	list.msgList = new tMessage[sizeList];
	list.max = sizeList;

}


void addMessageToEnd(tMessageList &list, tMessage message) {

	if (list.counter >= list.max) {
		int maxSize = (list.max * 3) / 2 + 1;
		resizeMessageSpace(list, maxSize);
	}

	list.msgList[list.counter] = message;
	list.counter++;
}


void obtainLastMessage(const tMessageList &list, tMessage &msg) {
	msg = list.msgList[list.counter - 1];
}


void obtainMessage(const tMessageList &list, tMessage &msg, int pos) {
	msg = list.msgList[pos];
}


string obtainSender(const tMessageList &list, int pos) {
	return list.msgList[pos].idUserSender;
}


void obtainDate(const tMessageList &list, tDate &date, int pos) {
	date = list.msgList[pos].date;
}


int nextTen(int number) {

	int result = ((number / 10) + 1) * 10;

	return result;
}


void resizeMessageSpace(tMessageList &list, int tam) {
	
	tMessagePtr tmp = new tMessage[tam];

	for (int n = 0; n < list.counter; n++) {
		tmp[n] = list.msgList[n];
	}

	delete[] list.msgList;
	list.msgList = tmp;
	list.max = tam;
}


void loadMessageList(tMessageList &list, ifstream &input, string emisor) {

	int countAux;
	input >> countAux;

	int tamMax = nextTen(countAux);

	initializeVariableMessageList(list, tamMax);

	int counter = 0;
	while (counter < countAux) {
		
		loadMessage(input, list.msgList[counter], emisor);
		counter++;
	}
	list.counter = counter;
}


void saveMessageList(ofstream &output, const tMessageList &list) {

	output << list.counter << endl;

	for (int n = 0; n < list.counter; n++) {
		saveMessage(output, list.msgList[n]);
	}
}


void destroyMessageList(tMessageList &list) {

	delete[] list.msgList;
	list.counter = 0;
	list.max = 0;
}