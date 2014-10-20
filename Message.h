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


#ifndef Message_h
#define Message_h

#include <string>
#include <ctime>
using namespace std;

const int SEED = 198236436; //seed predefined code to calculate the coding.
const string NAMEFILE = "_chat.dat";

typedef time_t tDate;

typedef struct {
	string idUserSender;
	string idUserReceiver;
	tDate date;
	string sms;
}tMessage;


/*
	Loads a message in the system.
	INPUT: Variable empty message, the sender of the messages and ifstream already open.
	OUTPUT: message loaded.
*/
void loadMessage(ifstream &input, tMessage &msg, string sender);
/*
	From the data transferred by the user generates a message in a variable
	message.
	INPUT: The sender, the recever, the message to enter and the variable message.
	OUTPUT: Variable message loaded.
*/
void createMessage(tMessage &msg, string sms, string sender, string recever);
/*
	From a message generates a line of text to be shown on screen.
	INPUT: message.
	OUTPUT: String ready to be shown on screen.
*/
string showMessage(tMessage msg);
/*
	From a date generates a line of text to be shown on screen.
	INPUT: date.
	OUTPUT: String ready to be shown on screen.
*/
string showDate(tDate date);
/*
	Saves a message to a file.
	INPUT: Variable message and opened ofstream.
*/
void saveMessage(ofstream &output, tMessage msg);

#endif