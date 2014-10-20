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


#ifndef Client_h
#define Client_h

#include <string>
using namespace std;
#include <Windows.h>
#include "ChatsList.h"
#include "Server.h"

const int ALIGNMENT = 38; /*Used to logically align the name of the application
						  provided that it is shown on screen.*/

const string VERSION = "WinChat 3.1.2";

typedef struct {
	string id;
	tChatsList chats;
}tClientsData;


/*
	Manages the stay of a user during use of WinChat.
	INPUT: list of server identifier of the current user.
	OUTPUT: list of modified server (if it was modified).
*/
void runClient(tServer &server, string id);
/*
	It is responsible for executing all operations to hone lists and chat server.
	INPUT: data of the current user, list the server, user, identifier, number of new messages.
	OUTPUT: data of the current user updated the server list updated, user date and amount of
	new updated posts.
*/
void loadClient(tClientsData &data, tServer &server, tUser &user, string id, int &fresh);
/*
	Initialize the user data.
	INPUT: data of the user ID and password.
	OUTPUT: data from user initialized.
*/
void initializeData(tClientsData &user, string id);
/*
	It is responsible for placing on the mailboxes the messages obtained from the server.
	INPUT: the server list, list of chats and identifier.
	OUTPUT: list of current and updated list of chat server.
*/
void placeInMailbox(tServer &server, tChatsList &chats, string id);
/*
	Create a new empty chat (no message inside).
	INPUT: the server list, list of chats, and identifier list of new messages.
	OUTPUT: list of modified and modified chat server list.
*/
void createEmptyChat(tServer &server, tChatsList &chats, string id, string idChat);
/*
	Prints out the header of new messages displayed before the main menu.
	INPUT: list of data from the user, the server list and identifier.
	OUTPUT: Text on screen.
*/
void showHeaderMenu(const tClientsData &data, const tServer &server, string id);
/*
	WinChat Main Menu.
	OUTPUT: char with the option selected by the user.
*/
char menu();
/*
	Gestiona la option N del menu principal.
	INPUT: list del server, list de data del user, identificador y la posición.
	OUTPUT: list del server modificada y data del user modificados.
*/
void optionN(tServer &server, tClientsData &data, string id, int pos);
/*
	Manages N Main menu option.
	INPUT: list of server, the list of user data, and position identifier.
	OUTPUT: list of modified server and the user data modified.
*/
void optionC(tServer &server, tClientsData &data, string id);
/*
	Manages E Main menu option.
	INPUT: list of the user data.
	OUTPUT: data the user modified.
*/
void optionE(tClientsData &data);
/*
	Manages S Main menu option.
	INPUT: list of the user data.
	OUTPUT: data the user modified.
*/
void optionS(tClientsData &data);
/*
	Prints out an error related to the talks.
	INPUT: integer indicating if exist a conversation (1), if there exist (0) or if there are no
	more spaces (-1).
	OUTPUT: Error on screen.
*/
void errorConversation(int exist);
/*
	Crea una nueva conversación (nuevo chat).
	INPUT: list del server, list de chats, nombre del creador y del receiver.
	OUTPUT: list del server modificada y list de chats modificada.
*/
void createChat(tServer &server, tChatsList &chatsLists, string creator, string idReceiver);
/*
	Create a new message. 
	INPUT: the server list, list of chats, creator name and receiver. 
	OUTPUT: list of modified and modified chat server list.
*/
bool composeMessage(tServer &server, tChatsList &listaChat, string id, string receiver);
/*
	Displays the user message shower.
	INPUT: user identifier.
	OUTPUT: message on screen.
*/
void showWelcome(string id);
/*
	Displays the name of the talks in the "Conversations" interface.
	INPUT: chat identifier.
	OUTPUT: message on screen.
*/
void showNameConversation(string idChat);
#endif