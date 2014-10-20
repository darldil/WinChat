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


#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <sstream>
using namespace std;
#include <fstream>
#include "Message.h"

/*
	It is responsible for encoding messages before they are saved to a file.
	INPUT: Message and key coding.
	OUTPUT: Encoded message.
*/
string encodeMessage(int code, string message);
/*
	Decode a message loaded from a file.
	INPUT: Key code and encoded message.
	OUTPUT: Decoded message.
*/
string decodeMessage(int code, string message);
/*
	Responsible for coding a lowercase letter.
	INPUT: Message, key code and coded position.
	OUTPUT: Coded letter.
*/
void encodeLowerCase(string &message, int code, int pos);
/*
	It is responsible for encoding an uppercase letter.
	INPUT: Message, key code and coded position.
	OUTPUT: Coded letter.
*/
void encodeMayusCase(string &message, int code, int pos);
/*
	It is responsible for encoding a number.
	INPUT: Message, key code and coded position.
	OUTPUT: Coded Number.
*/
void encodeNumber(string &message, int code, int pos);



void loadMessage(ifstream &input, tMessage &msg, string sender) {

	tMessage auxMessage;
	string decode;
	char aux;

	input >> auxMessage.idUserSender;
	auxMessage.idUserReceiver = sender;
	input.get(aux);
	input >> auxMessage.date;
	input.get(aux);
	getline(input, decode);

	int kernel = int(auxMessage.date) / SEED; /*Generates key coding from date and
											  a division of a predefined number.*/
	decode = decodeMessage(kernel, decode);
	auxMessage.sms = decode;

	msg = auxMessage;
}


void createMessage(tMessage &msg, string sms, string sender, string recever) {

	msg.date = time(0);
	msg.idUserSender = sender;
	msg.idUserReceiver = recever;
	msg.sms = sms;
}


string showMessage(tMessage msg) {

	return msg.idUserSender + "  (" + showDate(msg.date) + "): " + msg.sms;
}


string showDate(tDate date){
	stringstream result;
	tm* ltm = localtime(&date);
	result << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year;
	result << ", " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec;
	return result.str();
}


void saveMessage(ofstream &output, tMessage msg) {

	string encode;
	int kernel = int(msg.date) / SEED; /*Generates key coding from date and
									   a division of a predefined number.*/
	output << msg.idUserSender << " ";
	output << msg.date << " ";
	encode = encodeMessage(kernel, msg.sms);
	output << encode << endl;
}


string encodeMessage(int code, string message) {

	string encodeMess = message;

	for (int n = 0; n < encodeMess.length(); n++) {
		if (encodeMess[n] >= 'a' && encodeMess[n] <= 'z') {
			encodeLowerCase(encodeMess, code, n);
		}

		else if (encodeMess[n] >= 'A' && encodeMess[n] <= 'Z') {
			encodeMayusCase(encodeMess, code, n);
		}

		else if (encodeMess[n] >= '0' && encodeMess[n] <= '9') {
			encodeNumber(encodeMess, code, n);
		}
	}

	return encodeMess;
}


string decodeMessage(int code, string message) {

	string decodeMess;

	decodeMess = encodeMessage(-code, message); /*Encode function is reused but
												the encryption key by passing negative.*/

	return decodeMess;
}


void encodeLowerCase(string &message, int code, int pos) {

	if (message[pos] + code > 'z') {
		message[pos] = 'a' - 'z' + message[pos] + code - 1;
	}

	else if (message[pos] + code < 'a') {
		message[pos] = 'z' - 'a' + message[pos] + code + 1;
	}

	else {
		message[pos] += code;
	}
}


void encodeMayusCase(string &message, int code, int pos) {

	if (message[pos] + code > 'Z') {
		message[pos] = 'A' - 'Z' + message[pos] + code - 1;
	}

	else if (message[pos] + code < 'A') {
		message[pos] = 'Z' - 'A' + message[pos] + code + 1;
	}

	else {
		message[pos] += code;
	}
}


void encodeNumber(string &message, int code, int pos) {

	if (message[pos] + code > '9') {
		message[pos] = '0' - '9' + message[pos] + code - 1;
	}

	else if (message[pos] + code < '0') {
		message[pos] = '9' - '0' + message[pos] + code + 1;
	}

	else {
		message[pos] += code;
	}
}