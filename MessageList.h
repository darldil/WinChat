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


#ifndef MessageList_h
#define MessageList_h

#include "Message.h"

const int MAX_MESSAGES = 50; //Maximum supported messages.

typedef tMessage *tMessagePtr;

typedef struct {
	tMessagePtr msgList;
	int counter;
	int max;
}tMessageList;


/*
	Initializes a list of messages.
	INPUT: list of messages.
	OUTPUT: list of messages initialized.
*/
void initializeMessageList(tMessageList &list);
/*
    Initializes a list of messages with a size greater than the predetermined maximum.
    INPUT: list of messages and maximum size changed.
    OUTPUT: list of messages initialized.
*/
void initializeVariableMessageList(tMessageList &list, int sizeList);
/*
	It is responsible for adding a message at the end of the list.
	INPUT: list of messages and message inserted.
	OUTPUT: list of modified messages.
*/
void addMessageToEnd(tMessageList &list, tMessage message);
/*
	Inserts the last message in the message list in a separate variable.
	INPUT: list of messages and message empty variable.
	OUTPUT: Variable message filled.
*/
void obtainLastMessage(const tMessageList &list, tMessage &msg);
/*
    Insert a message in the message list in a separate variable.
    INPUT: message list, message variable and the position empty.
    OUTPUT: Variable message filled.
*/
void obtainMessage(const tMessageList &list, tMessage &msg, int pos);
/*
	Given a position inserts a message from the message list in a separate variable. 
	INPUT: list of messages, empty variable message and position. 
	OUTPUT: Variable message filled.
*/
string obtainSender(const tMessageList &list, int pos);
/*
	Given a position indicating the date of a message in the list. 
	INPUT: list of messages, date variable empty and position. 
	OUTPUT: date of the message.
*/
void obtainDate(const tMessageList &list, tDate &date, int pos);
/*
	Given a number calculated by the following decade this.
	INPUT: number.
	OUTPUT: Next decade of the number provided.
*/
int nextTen(int number);
/*
	Adapt space available message to the given conditions with sizelist variable.
    INPUT: list of current and maximum allowed message size.
    OUTPUT: list posts, you can zoom in far greater extent than indicated in the
    variable sizelist.
*/
void resizeMessageSpace(tMessageList &list, int tam);
/*
	Loads the list of messages from an already open file.
	INPUT: list of messages, the creator of the message and the ifstream open.
	OUTPUT: list of loaded messages.
*/
void loadMessageList(tMessageList &list, ifstream &input, string sender);
/*
	Save the list of messages in an already open file.
	INPUT: list of messages and open ofstrean.
*/
void saveMessageList(ofstream &output, const tMessageList &list);
/*
	Delete a list of Messages.
	INPUT: Full list of messages.
	OUTPUT: Empty list of messages.
*/
void destroyMessageList(tMessageList &list);

#endif