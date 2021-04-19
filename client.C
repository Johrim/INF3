/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <unistd.h> //contains various constants

#include <fstream>
#include "SIMPLESOCKET.H"
#include "TASK1.H"

using namespace std;


class pwdClient : public TCPclient{
public:

	void run();
	void makeBlackbox();


private:
	pwdClient *client = this;
	char pwdLength[99];
	char symbSetSize[99];
	int tries = 0;
	int repetition;
	fstream result;

};

class guessPwd{
public:
	string random(int pwdLength);
	void charSymbArray(int symbSetSize);
	~guessPwd();

private:
	char * charSymbArray_;
	int    lengthSymbArray_;

};

int main() {
	srand(time(NULL));

	//connect to host
	pwdClient c;
	c.run();


}



void pwdClient::run(){
	bool run=1;
	string msg;
	string host = "localhost";
	string response ="ACCESS ACCEPTED";

	conn(host , 2022);
	makeBlackbox();

	msg = receive(32);
	cout << "got response: " << msg << endl;

	guessPwd g;

	while(run){
		g.charSymbArray(atoi(symbSetSize));
		while(repetition > 0){
			if(tries == 0){
				tries = 1;
			}

			sendData(g.random(atoi(pwdLength)));
			msg =receive(32);
			cout << "got response: " << msg << endl;
			if(msg.compare(response) == 0){
				std::cout <<tries << " tries needed! " << endl;
				result.open("result.dat", ios::app);
				result << tries << " Versuche" << endl;
				result.close();

				repetition --;
				tries = 0;

				if(repetition > 1 ){

					msg = "newpwd[]";
					msg.insert(7,pwdLength);
					sendData(msg);
				}
				/*if(repetition = 1){
					result.open("result.dat", ios::app);
					result << "\n";
					result.close();
				}*/

			}
			tries++;
		}
		tries = 0;
		cin >> msg;
		if(msg.compare(0,5,"close") == 0){
			msg = "BYEBYE";
			sendData(msg);
			break;
				}
		if(msg.compare(0,6,"newbox") == 0){
			makeBlackbox();
		}

	}

}


void pwdClient::makeBlackbox(){
	string msg("makepwd[,]");
	char numbers[] = ("1234567890");
	int i,n;



	std::cout << "Passwordlength: ";
	std::cin >> pwdLength;
	i = strspn(pwdLength,numbers);

	while(i == 0){
		std::cout << "False Input!" << std::endl;
		std::cout << "Passwordlength: ";
		std::cin >> pwdLength;
		i = strspn(pwdLength,numbers);
	}


	i = atoi(pwdLength);

	while(i < TASK1::MINIMAL_PWD_LENGTH){
		std::cout <<"Minimum Passwordlength = 4" << std::endl;
		std::cout << "Passwordlength: ";
		std::cin >> pwdLength;
		i = atoi(pwdLength);
	}
	//pwdLength = i;
	msg.insert(8,pwdLength);

	std::cout << "Number of possible symbols: ";
	std::cin >> symbSetSize;
	i = strspn(symbSetSize,numbers);
	while(i == 0){
			std::cout << "False Input!" << std::endl;
			std::cout << "Number of possible symbols: ";
			std::cin >> symbSetSize;
			i = strspn(symbSetSize,numbers);
		}

	i = atoi(symbSetSize);

	while(i > TASK1::SYMBOLS.length() || i < 4){
		if(i > TASK1::SYMBOLS.length()){
			std::cout << "Maximum Number of possible symbols = " << TASK1::SYMBOLS.length() << std::endl;
		}
		if(i < 4){
			std::cout <<"Minimum Number of possible symbols = 4" << std::endl;
		}

		std::cout << "Number of possible symbols: ";
		std::cin >> symbSetSize;
		i = atoi(symbSetSize);

		}

	msg.insert(10,symbSetSize);
	cout << "Number of repetition: ";
	cin >> repetition;
	result.open("result.dat", ios::app);
	result << "Passwordlaenge: "<< pwdLength << ", Anzahl von unterschiedlichen Symbole: "<< symbSetSize << ", Anzahl der Wiederholungen: "<< repetition << endl;
	result.close();
	sendData(msg);
}


void guessPwd::charSymbArray(int symbSetSize){
	lengthSymbArray_ = symbSetSize;
	charSymbArray_ = new char [lengthSymbArray_ + 1];
	strncpy(charSymbArray_, TASK1::SYMBOLS.c_str(), lengthSymbArray_);
	return;
}

string guessPwd::random(int pwdLength){
	int symbolIdx;
		string pwd;
		for(int i=0; i < pwdLength; i++){
			symbolIdx = rand() % lengthSymbArray_;
			pwd += charSymbArray_[symbolIdx];
		}
	return pwd;
}

guessPwd::~guessPwd(){
	delete [] charSymbArray_;
}

