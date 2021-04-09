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

#include "SIMPLESOCKET.H"
#include "TASK1.H"

using namespace std;


class pwdClient : public TCPclient{
public:

	void run();
	void makeBlackbox();


private:
	pwdClient *client = this;
	int pwdLength;
	int symbSetSize;
	int tries = 1;
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
	bool goOn=1;
	bool run=1;
	int i = 1;
	string msg;
	string host = "localhost";
	string response ="ACCESS ACCEPTED";
	conn(host , 2022);
	makeBlackbox();
	msg = receive(32);
	cout << "got response: " << msg << endl;


	guessPwd g;

	while(run){
		g.charSymbArray(symbSetSize);
		while(goOn){
			sendData(g.random(pwdLength));
			msg =receive(32);
			cout << "got response: " << msg << endl;
			if(msg.compare(response) == 0){
				goOn = 0;
				std::cout <<tries << " tries needed! " << std::endl;
			}
			tries++;
		}
	}

}


void pwdClient::makeBlackbox(){
	string msg("makepwd[,]");
	char numbers[] = ("1234567890");
	char a[99];
	char b[99];
	int i,j;



	std::cout << "Passwordlength: ";
	std::cin >> a;
	i = strspn (a,numbers);

	while(i == 0){
		std::cout << "False Input!" << std::endl;
		std::cout << "Passwordlength: ";
		std::cin >> a;
		i = strspn (a,numbers);
	}


	j = atoi(a);

	while(j < TASK1::MINIMAL_PWD_LENGTH){
		std::cout <<"Minimum Passwordlength = 4" << std::endl;
		std::cout << "Passwordlength: ";
		std::cin >> a;
		j = atoi(a);
	}
	pwdLength = j;

	std::cout << "Number of possible symbols: ";
	std::cin >> b;
	i = strspn (b,numbers);
	while(i == 0){
			std::cout << "False Input!" << std::endl;
			std::cout << "Number of possible symbols: ";
			std::cin >> b;
			i = strspn (b,numbers);
		}

	j = atoi(b);

	while(j > TASK1::SYMBOLS.length()){
			std::cout <<"Minimum Number of possible symbols = 4" << std::endl;
			std::cout << "Number of possible symbols: ";
			std::cin >> b;
			j = atoi(b);

		}
	symbSetSize = j;
	msg.insert(8,a);
	msg.insert(10,b);

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

