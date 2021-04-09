/*
 * server.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */
#include <cstdio> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <cstring> // contains string functions
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> //contains various functions for manipulating date and time

#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses

#include "SIMPLESOCKET.H"
#include "TASK1.H"
#include <iostream>
#include "SHA256.H"



class pwdServer : public TCPserver{
public:
	pwdServer(int port, int maxDataSize) : TCPserver(port, maxDataSize){;};

protected:
	string myResponse(string input);
	TASK1::BlackBoxSafe *blackbox;
};




int main(){

	srand(time(nullptr));

	pwdServer srv(2022,25);
	srv.run();


}


string pwdServer::myResponse(string input){
	int a,b,c;

	if(sscanf(input.c_str(), "makepwd[%i,%i]", &a,&b)){

		blackbox = new TASK1::BlackBoxSafe(a, b);
		blackbox->makePwd(a);

		return string("Password created");
	}else if(blackbox != NULL){


			return blackbox->input(input);;
	}else {
		return string("Couldn't read parameter");
	}
}
