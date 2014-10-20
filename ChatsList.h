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


#ifndef ChatsList_h
#define ChatsList_h

#include "Chat.h"

const int MAX_CHATS = 50; //Max chats admitted.

typedef tChat *tChatPtr;

typedef struct {
	tChatPtr chat;
	int counter;
	int max;
}tChatsList;


/*
	Initializes a list of chats.
	INPUT: list of chats and identifier.
	OUTPUT: list of chats initialized.
*/
void initializeChatsList(tChatsList &list, string id);
/*
	Initializes a list of chats with a maximum size greater than the default.
    INPUT: list of chats and modified maximum size.
 O  UTPUT: list of chats initialized.
*/
void initializeVariableChatsList(tChatsList &list, int sizeList);
/*
	Adapt space of chats available with the given conditions sizelist variable.
    INPUT: list of current chats and maximum allowed size.
    OUTPUT: list of extended or reduced function as indicated in chats
    vatiable sizelist.
*/
void resizeChatsSpace(tChatsList &list, int sizeList);
/*
	Load from a file the list of chats.
	INPUT: identifier list empty and chats.
	OUTPUT: list of chats and charged boolean check.
*/
bool loadChatsList(tChatsList &list, string id);
/*
	Save a file in the list of chats.
	INPUT: list of chats and identifier.
*/
void saveChatsList(const tChatsList &list, string id);
/*
	Given a position carries a chat in an independent variable
	from the list of chats.
	INPUT: list of chats, empty variable position and looking chat.
	OUTPUT: Variable chat loaded.
*/
void accesToChat(const tChatsList &list, tChat &chat, int pos);
/*
	It is responsible for adding a chat at the end of the list.
	INPUT: list of chats and chat inserted.
	OUTPUT: list of modified chats.
*/
void addChatToEnd(tChatsList &list, tChat chat);
/*
	Move a conversation at the end of the list.
	INPUT: list of chats and to move position.
	OUTPUT: list of modified chats.
*/
void moveChatToEnd(tChatsList &list, int pos);
/*
	Given a position identifier of a chat is sought.
	INPUT: list of chats and identifier for.
	OUTPUT: chat position (-1 if not located).
*/
int findChats(const tChatsList &list, string seBusca);
/*
	Removes a chat.
	INPUT: list of chats and position.
	OUTPUT: list of modified chats.
*/
void deleteChat(tChatsList &list, int position);
/*
	Sort the list of chats by date Ascending (taking
	reference to the date of the last message sent).
	INPUT: list of chats.
	OUTPUT: list of modified chats.
*/
void sortByDate(tChatsList &list);
/*
	Sort chat list by name Ascending (taking
	reference the id of the chat).
	INPUT: list of chats.
	OUTPUT: list of modified chats.
*/
void sortByName(tChatsList &list);
/*
	Deletes a list of chats in the dynamic memory.
    INPUT: list of chats busy.
    OUTPUT: empty pages listed in chats.
*/
void destroyChatsList(tChatsList &list);

#endif