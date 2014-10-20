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
#include "ChatsList.h"

void initializeChatsList(tChatsList &list, string id) {

	list.counter = 0;
	list.chat = new tChat[MAX_CHATS];
	list.max = MAX_CHATS;
}


void initializeVariableChatsList(tChatsList &list, int sizeList) {

	list.counter = 0;
	list.chat = new tChat[sizeList];
	list.max = sizeList;
}


void resizeChatsSpace(tChatsList &list, int sizeList) {

	tChatPtr tmp = new tChat[sizeList];

	for (int n = 0; n < list.counter; n++) {
		tmp[n] = list.chat[n];
	}

	delete[] list.chat;
	list.chat = tmp;
	list.max = sizeList;
}


bool loadChatsList(tChatsList &list, string id) {

	ifstream input;
	int counter;
	bool loaded = false;

	input.open("WCTMP\\" + id + "_chat.dat");

	if (input.is_open()) {

		input >> counter;
		int sizeList = nextTen(counter);
		initializeVariableChatsList(list, sizeList);
		int countAux = list.counter;

		while (counter > 0) {
			initializeChat(list.chat[countAux], id);
			loadChat(list.chat[countAux], input);
			countAux++;
			counter--;
		} 
		list.counter = countAux;

		input.close();
		loaded = true;
	}

	return loaded;
}


void saveChatsList(const tChatsList &list, string id) {

	ofstream output;

	output.open("WCTMP\\" + id + "_chat.dat");

	output << list.counter << endl;

	for (int n = 0; n < list.counter; n++) {
		saveChat(output, list.chat[n]);
	}

	output.close();
}


void accesToChat(const tChatsList &list, tChat &chat, int pos) {
	chat = list.chat[pos];
}


void addChatToEnd(tChatsList &list, tChat chat) {

	if (list.counter >= list.max) {
		int maxSize = (list.max * 3) / 2 + 1;
		resizeChatsSpace(list, maxSize);
	}

	list.chat[list.counter] = chat;
	list.counter++;
}


void moveChatToEnd(tChatsList &list, int pos) {

	tChat aux = list.chat[pos];

	for (int n = pos; n < list.counter - 1; n++) {
		list.chat[n] = list.chat[n + 1];
	}

	list.chat[list.counter - 1] = aux;
}


// Linear search.
int findChats(const tChatsList &list, string seBusca) {

	int position = -1, counter = 0;
	bool found = false;

	while (counter < list.counter && !found) {
		if (list.chat[counter].idChat == seBusca) {
			found = true;
			position = counter;
		}
		else {
			counter++;
		}
	}

	return position;
}


void deleteChat(tChatsList &list, int position) {

	destroyMessageList(list.chat[position].chatMessages);

	for (int n = position; n < list.counter - 1; n++) {
		list.chat[n] = list.chat[n + 1];
	}
	list.counter--;

	if (list.counter < (list.max / 2)) {
		int sizeMax = (list.max * 2) / 3;
		resizeChatsSpace(list, sizeMax);
	}
}


void sortByDate(tChatsList &list) {

	tChat currentChat, lastChat;
	tDate actualDate, lastDate;
	bool inter = true;
	int i = 0;

	while ((i < list.counter - 1) && inter) {
		inter = false;
		for (int j = list.counter - 1; j > i; j--) {

			accesToChat(list, currentChat, j);
			accesToChat(list, lastChat, j - 1);

			int k = currentChat.chatMessages.counter - 1;
			int m = lastChat.chatMessages.counter - 1;

			obtainDate(currentChat.chatMessages, actualDate, k);
			obtainDate(lastChat.chatMessages, lastDate, m);

			if (actualDate < lastDate) {
				tChat tmp;
				tmp = list.chat[j];
				list.chat[j] = list.chat[j - 1];
				list.chat[j - 1] = tmp;
				inter = true;
			}
		}
		if (inter) {
			i++;
		}
	}
}


// Bubble Sorting by improved method.
void sortByName(tChatsList &list) {

	bool inter = true;
	int i = 0;

	while ((i < list.counter - 1) && inter) {
		inter = false;
		for (int j = list.counter - 1; j > i; j--) {
			if (list.chat[j].idChat < list.chat[j - 1].idChat) {
				tChat tmp;
				tmp = list.chat[j];
				list.chat[j] = list.chat[j - 1];
				list.chat[j - 1] = tmp;
				inter = true;
			}
		}
		if (inter) {
			i++;
		}
	}
}


void destroyChatsList(tChatsList &list) {

	for (int n = 0; n < list.counter; n++) {
		destroyMessageList(list.chat[n].chatMessages);
	}

	delete[] list.chat;
	list.counter = 0;
	list.max = 0;
}