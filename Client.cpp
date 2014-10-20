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
#include <cctype>
using namespace std;
#include <iomanip>
#include "Client.h"
#pragma comment (lib, "winmm.lib")

void runClient(tServer &server, string id) {

	tClientsData data;
	char option;
	int userPosition = findUsers(server, id), newMessages = 0;
	tUser connectedUser;

	showWelcome(id);

	loadClient(data, server, connectedUser, id, newMessages);

	showHeaderMenu(data, server, id);

	if (newMessages > 0) { //If new messages inform the user with a sound and a message on screen.
		PlaySound("WCTMP\\receive_message.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		cout << setw(35) << "You have " << newMessages;
		cout << " new message(s)." << endl;
	}

	option = menu();

	while (option != '0') {
		switch (option) {
		case 'n': optionN(server, data, id, userPosition); break; //New conversation.
		case 'c': optionC(server, data, id); break; //Access to existing conversation.
		case 'e': optionE(data); break; //Delete conversation.
		case 's': optionS(data); break; //Sort conversations.
		default: cout << "Error! Incorrect option." << endl; Sleep(2000); break;
		}
		system("cls"); //Clean the screen.
		showWelcome(id);
		showHeaderMenu(data, server, id);
		option = menu();
	}
	
	cout << setw(45) << "See you soon " << id << "!" << endl;

	connectedUser.lastConnection = time(0); //Updates the last logon time of the user connected.
	*server.users[userPosition] = connectedUser;
	saveChatsList(data.chats, id);

	Sleep(1000);
	PlaySound("C:\\WINDOWS\\Media\\Windows Logoff Sound.wav", NULL, SND_NODEFAULT);
	system("cls");
}


void loadClient(tClientsData &data, tServer &server, tUser &user, string id, int &fresh) {

	int pos = findUsers(server, id);

	initializeData(data, id);
	if (loadChatsList(data.chats, id)) {
		initializeChatsList(data.chats, id);
	}
	
	obtainUser(server, user, pos);
	if (user.unread.counter > 0) {
		fresh = user.unread.counter;
		placeInMailbox(server, data.chats, id);
		user.unread.counter = 0;
	}
}


void initializeData(tClientsData &user, string id) {

	user.id = id;

	user.chats.chat = NULL;
}


void placeInMailbox(tServer &server, tChatsList &chats, string id) {

	tMessageList newMess;
	tChat currentChat;
	int counter = 0;

	obtainNewMessages(server, newMess, id);

	while (counter <  newMess.counter) {
		int chatPos = findChats(chats, newMess.msgList[counter].idUserSender);
		if (chatPos == -1) { // ---------> If no open conversation with the user generates a new.
			string idChat = obtainSender(newMess, counter);
			createEmptyChat(server, chats, id, idChat);
			chatPos = findChats(chats, idChat);
		}
		accesToChat(chats, currentChat, chatPos);
		while (newMess.msgList[counter].idUserSender == currentChat.idChat) {
			int cont = currentChat.chatMessages.counter;
			currentChat.chatMessages.msgList[cont] = newMess.msgList[counter];
			currentChat.chatMessages.counter++;
			counter++;
			chats.chat[chatPos] = currentChat;
		}
	}
	destroyMessageList(newMess);
}


void createEmptyChat(tServer &server, tChatsList &chats, string id, string idChat) {

	tUser serverAux;
	tChat currentChat;
	int userPos = findUsers(server, idChat);
	int chatPos;

	createChat(server, chats, id, idChat); //Creates a conversation.
	obtainUser(server, serverAux, userPos);
	serverAux.unread.counter--; //The message "New conversation Initiated by ..." is deleted to avoid duplication.
	*server.users[userPos] = serverAux;
	chatPos = findChats(chats, idChat);
	accesToChat(chats, currentChat, chatPos);
	currentChat.chatMessages.counter--;
	chats.chat[chatPos] = currentChat;
}


void showHeaderMenu(const tClientsData &data, const tServer &server, string id) {

	for (int n = 0; n < data.chats.counter; n++) {
		string usuario = data.chats.chat[n].idChat;
		int position = findUsers(server, usuario);
		tDate connection = server.users[position]->lastConnection;
		showHeaderChat(data.chats.chat[n], n, id, connection);
	}
}


char menu() {

	char option;

	showHorizontalLine();

	cout << "Main Menu" << endl << endl;
	cout << setw(36) << "Enter to chat N: c N (Enter)" << setw(39) << "Create new chat: n" << endl;
	cout << setw(38) << "Delete chat N: e N (Enter)" << setw(37) << "Sort chats by name: s n" << endl;
	cout << setw(35) << "Sort chats by date: s d" << setw(40) << "Exit: 0" << endl;

	showHorizontalLine();
	cout << endl;

	cin >> option;
	option = tolower(option);

	return option;
}


void optionN(tServer &server, tClientsData &data, string id, int pos) {

	string receiver;
	bool error = false;
	int exist = 1;

	if (data.chats.counter < MAX_CHATS) {

		do {
			error = false;
			cout << endl << "New chat." << endl;
			cout << "Specify the id of receiver (0 cancel): ";
			cin >> receiver;
			cin.sync();
			int position = findUsers(server, receiver);
			if ((position == -1 || pos == position) && receiver != "0") {
				cout << endl << "Incorrecto user" << endl; //Checks if the receiver corresponds to a user and does not match with the id.
				PlaySound("C:\\WINDOWS\\Media\\chord.wav", NULL, SND_ASYNC | SND_NODEFAULT);
				error = true;
			}
			if (findChats(data.chats, receiver) != -1) { //Checks if the conversation already exists
				errorConversation(exist);
				error = true;
			}
		} while (error);

		if (receiver != "0") {
			createChat(server, data.chats, id, receiver);
			PlaySound("C:\\WINDOWS\\Media\\chimes.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		}
	}

	else {
		exist = -1;
		errorConversation(exist);
	}
}


void optionC(tServer &server, tClientsData &data, string id) {

	int position, exist = 0; //exist it's used for the message error
	bool continueWriting = true, moveConversation = false;
	tChat currentChat;

	cin >> position;
	cin.sync();

	if (position < data.chats.counter && position >= 0) {
		do {
			system("cls");
			accesToChat(data.chats, currentChat, position);
			string receiver = currentChat.idChat;
			showNameConversation(currentChat.idChat);
			showMessages(currentChat, id);
			continueWriting = composeMessage(server, data.chats, id, receiver);
			if (continueWriting) {
				PlaySound("WCTMP\\send_message.wav", NULL, SND_ASYNC | SND_NODEFAULT);
				moveConversation = true;
			}
		} while (continueWriting);
		if (moveConversation) {
			moveChatToEnd(data.chats, position);
		}
	}
	else {
		errorConversation(exist);
	}
}


void optionE(tClientsData &data) {

	int position;

	cin >> position;
	cin.sync();

	if (position < data.chats.counter && position >= 0) {
		PlaySound("C:\\WINDOWS\\Media\\recycle.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		deleteChat(data.chats, position);
	}
							
	else {
		int exist = 0;
		errorConversation(exist);
	}
}


void optionS(tClientsData &data) {

	char selection;

	cin >> selection;
	cin.sync();
	selection = tolower(selection);

	if (selection == 'd') {
		sortByDate(data.chats);
	}

	else if (selection == 'n') {
		sortByName(data.chats);
	}

	else {
		PlaySound("C:\\WINDOWS\\Media\\chord.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		cout << "Error! Incorrect option." << endl;
		Sleep(1000);
	}

}


void errorConversation(int exist) {

	PlaySound("C:\\WINDOWS\\Media\\chord.wav", NULL, SND_ASYNC | SND_NODEFAULT);

	if (exist == 0) {
		cout << "Error! The conversation does not exist." << endl;
	}

	else if (exist == 1) {
		cout << "Error! The conversation already exists." << endl;
	}

	else {
		cout << "Error! You can not create more conversations." << endl;
		cout << "Delete a conversation before creating a new" << endl;
	}

	Sleep(2000);
}


void createChat(tServer &server, tChatsList &chatsLists, string creator, string idReceiver) {

	tMessage auxMessage;
	tChat auxChat;
	string creationMessage = "New conversation initiated by " + creator;
	int counter = chatsLists.counter;
	int countMess;

	initializeMessageList(auxChat.chatMessages);

	auxChat.idChat = idReceiver;
	auxChat.idSender = creator;
	createMessage(auxMessage, creationMessage, creator, idReceiver);
	countMess = auxChat.chatMessages.counter;
	auxChat.chatMessages.msgList[countMess] = auxMessage;
	auxChat.chatMessages.counter++;
	addChatToEnd(chatsLists, auxChat);
	sendMessage(server, auxMessage);
	
}


bool composeMessage(tServer &server, tChatsList &listaChat, string id, string receiver) {

	bool keep = false;
	string message;
	int chatPos = findChats(listaChat, receiver);
	tChat currentChat;
	tMessage newMessage;

	accesToChat(listaChat, currentChat, chatPos);

	do {
		cout << "Write your message (type ESC to exit): ";
		getline(cin, message);
	} while (message == "");

	if (message != "ESC") {
		createMessage(newMessage, message, id, receiver);
		sendMessage(server, newMessage);
		int counter = currentChat.chatMessages.counter;
		currentChat.chatMessages.msgList[counter] = newMessage;
		currentChat.chatMessages.counter++;
		listaChat.chat[chatPos].chatMessages = currentChat.chatMessages;
	}

	return keep;
}


void showWelcome(string id) {

	showHorizontalLine();

	cout << setw(ALIGNMENT) << VERSION << ": Welcome " << id << endl;

	showHorizontalLine();

}


void showNameConversation(string idChat) {

	showHorizontalLine();

	cout << setw(ALIGNMENT + 4) << "Chat with: " << idChat << endl;

	showHorizontalLine();
}