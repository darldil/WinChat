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


#ifndef Chat_h
#define Chat_h

#include <string>
using namespace std;
#include "MessageList.h"

const int ALI_RECEPTION = 75; //It is used to align text messages received.

typedef struct {
	string idChat;
	string idSender;
	tMessageList chatMessages;
}tChat;


/*
	Initialize a chat.
	INPUT: Chat.
	OUTPUT: Chat initialized.
*/
void initializeChat(tChat &chat, string id);
/*
	Loads the list of chats from a file
	INPUT: list empty chats and open ifstream.
	OUTPUT: list of chats and charged boolean check.
*/
void loadChat(tChat &chat, ifstream &input);
/*
	Save the list of chats in a separate file.
	INPUT: full list chats and open ofstream.
*/
void saveChat(ofstream &output, const tChat &chat);
/*
	Displays a horizontal line on the interface.
	INPUT: Chat.
	OUTPUT: Line on screen.
*/
void showHorizontalLine();
/*
	Displays the last message in a conversation on the menu.
	INPUT: list of chats, chat the number of the connected user ID
	and the last connection.
	OUTPUT: Conversations on screen.
*/
void showHeaderChat(const tChat &chat, int cuentaChat, string id, tDate connection);
/*
	Show all message of a conversation.
	INPUT: list of chats, the user ID connected.
	OUTPUT: Screen Messages.
*/
void showMessages(const tChat &chat, string id);

#endif