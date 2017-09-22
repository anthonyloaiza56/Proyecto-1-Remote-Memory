#ifndef RMLIB_H_INCLUDED
#define RMLIB_H_INCLUDED
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <thread>
using namespace std;

int portNum = 33111;
int portNum2 = 33111;
int disponible_server_HA=0; //ASI VERIFICO SI ESTA CONECTADO O DESCONECTADO
int disponible_server_PA=0;
    int client; // socket file descriptors
     // port number (same that server)
int bufsize = 1024; // buffer size
char buffer[1024]; // buffer to transmit

char ip[] = "127.0.0.1"; // Server IP
bool isExit = false; // var fo continue infinitly



   /* -------------- INITIALIZING VARIABLES -------------- */
    int client2; // socket file descriptors
     // port number (same that server)

    char buffer2[1024]; // buffer to transmit

    bool isExit2 = false; // var fo continue infinitly

void enviar(int cliente_S,char B[],int size_B){
    char msj[1024]="hola1*";
    char msj2[1024]="hola2*";
    if (cliente_S==1)
    {
        send(client,msj,size_B,0);
    }
    if (cliente_S==2)
    {
        send(client2,msj2,size_B,0);
    }



}
void cliente(){
/* -------------- INITIALIZING VARIABLES -------------- */


    /* Structure describing an Internet socket address. */
struct sockaddr_in server_addr;
    cout << "\n- Starting client..." << endl;

    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/

    client = socket(AF_INET, SOCK_STREAM, 0);

    /*
    * The socket() function creates a new socket.
    * It takes 3 arguments:
    * 1) AF_INET: address domain of the socket.
    * 2) SOCK_STREAM: Type of socket. a stream socket in
    * which characters are read in a continuous stream (TCP)
    * 3) Third is a protocol argument: should always be 0.
    * If the socket call fails, it returns -1.
    */

    if (client < 0)
            {
        cout << "\n-Error establishing socket..." << endl;
        exit(-1);
            }

    cout << "\n- Socket client has been created..." << endl;

    /*
    * The variable serv_addr is a structure of sockaddr_in.
    * sin_family contains a code for the address family.
    * It should always be set to AF_INET.
    * INADDR_ANY contains the IP address of the host. For
    * server code, this will always be the IP address of
    * the machine on which the server is running.
    * htons() converts the port number from host byte order
    * to a port number in network byte order.
    */

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);

    /*
    * This function converts an Internet address (either IPv4 or IPv6)
    * from presentation (textual) to network (binary) format.
    * If the comunication is on the same machine, you can comment this line.
    */
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    /* ---------- CONNECTING THE SOCKET ---------- */

    if (connect(client, (struct sockaddr *) &server_addr, sizeof(server_addr))
        < 0)
        cout << "- Connection to the server port number: " << portNum << endl;

    /*
    * The connect function is called by the client to
    * establish a connection to the server. It takes
    * three arguments, the socket file descriptor, the
    * address of the host to which it wants to connect
    * (including the port number), and the size of this
    * address.
    * This function returns 0 on success and -1
    * if it fails.
    * Note that the client needs to know the port number of
    * the server but not its own port number.
    */
    cout << "- Awaiting confirmation from the server..." << endl; //line 40

    // recive the welcome message from server
    recv(client, buffer, bufsize, 0);
    cout << buffer << endl;

    cout << "- Connection confirmed, you are good to go!" << endl;
    cout << "- Enter * to end the message" << endl;
    cout << "- Enter # to end the connection\n" << endl;

    // loop to send messages to server
    disponible_server_HA=1;
    do {
        cout << "Message: ";
        /*
        * The function 'cin' get an word at time and send it
        * to the server. The send operation is call until
        * the user write '*'.
        */
        //do {
            // read from terminal
            int server;
            cin >> server;
            enviar(server, buffer, bufsize);
            if(buffer=="*"){
                enviar(client, buffer, bufsize);
            }
            else if(buffer=="#"){
                *buffer = '*';
                isExit = true;
                cout<<"finalizado server 2"<<endl;
            }
            // send to the server
            /*send(client, buffer, bufsize, 0);
            if (*buffer == '#') {
                // exit from the loop
                *buffer = '*';
                isExit = true;
            }
        } while (*buffer != '*');
        // wait the response from the server
        cout << "Server says: ";
        recv(client, buffer, bufsize, 0);
        // print the server message
        cout << buffer << endl;*/
    } while (!isExit);

    /* ---------------- CLOSE CALL ------------- */

    cout << "\nConnection terminated.\n";

    /*
    * Once the server presses # to end the connection,
    * the loop will break and it will close the server
    * socket connection and the client connection.
    */
    close(client);
    disponible_server_HA=0;


}


/***************************************************************************************/
/***************************************************************************************/

void cliente2(){


    /* Structure describing an Internet socket address. */
    struct sockaddr_in server_addr;

    cout << "\n- Starting client..." << endl;

    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/

    client2 = socket(AF_INET, SOCK_STREAM, 0);

    /*
    * The socket() function creates a new socket.
    * It takes 3 arguments:
    * 1) AF_INET: address domain of the socket.
    * 2) SOCK_STREAM: Type of socket. a stream socket in
    * which characters are read in a continuous stream (TCP)
    * 3) Third is a protocol argument: should always be 0.
    * If the socket call fails, it returns -1.
    */

    if (client2 < 0) {
        cout << "\n-Error establishing socket..." << endl;
        exit(-1);
    }

    cout << "\n- Socket client has been created..." << endl;

    /*
    * The variable serv_addr is a structure of sockaddr_in.
    * sin_family contains a code for the address family.
    * It should always be set to AF_INET.
    * INADDR_ANY contains the IP address of the host. For
    * server code, this will always be the IP address of
    * the machine on which the server is running.
    * htons() converts the port number from host byte order
    * to a port number in network byte order.
    */

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum2);

    /*
    * This function converts an Internet address (either IPv4 or IPv6)
    * from presentation (textual) to network (binary) format.
    * If the comunication is on the same machine, you can comment this line.
    */
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    /* ---------- CONNECTING THE SOCKET ---------- */

    if (connect(client2, (struct sockaddr *) &server_addr, sizeof(server_addr))
        < 0)
        cout << "- Connection to the server port number: " << portNum2 << endl;

    /*
    * The connect function is called by the client to
    * establish a connection to the server. It takes
    * three arguments, the socket file descriptor, the
    * address of the host to which it wants to connect
    * (including the port number), and the size of this
    * address.
    * This function returns 0 on success and -1
    * if it fails.
    * Note that the client needs to know the port number of
    * the server but not its own port number.
    */
    cout << "- Awaiting confirmation from the server..." << endl; //line 40

    // recive the welcome message from server
    recv(client2, buffer2, bufsize, 0);
    cout << buffer2 << endl;

    cout << "- Connection confirmed, you are good to go!" << endl;
    cout << "- Enter * to end the message" << endl;
    cout << "- Enter # to end the connection\n" << endl;
    // loop to send messages to server
    disponible_server_PA=1;
    do {
        cout << "Message: ";
        /*
        * The function 'cin' get an word at time and send it
        * to the server. The send operation is call until
        * the user write '*'.
        */


            int server;
            cin >> server;
            enviar(server, buffer, bufsize);
            if(buffer2=="*"){
                enviar(client2, buffer2, bufsize);
            }
            else if(buffer2=="#"){
                *buffer2 = '*';
                isExit2 = true;
                cout<<"finalizado server 2"<<endl;
            }
            // read from terminal
           /* cin >> buffer2;
            // send to the server
            send(client2, buffer2, bufsize, 0);
            if (*buffer2 == '#') {
                // exit from the loop
                *buffer2 = '*';
                isExit = true;
            }
        } while (*buffer2 != '*');
        // wait the response from the server
        cout << "Server says: ";
        recv(client2, buffer2, bufsize, 0);
        // print the server message
        cout << buffer2 << endl;*/
    } while (!isExit2);

    /* ---------------- CLOSE CALL ------------- */

    cout << "\nConnection terminated.\n";

    /*
    * Once the server presses # to end the connection,
    * the loop will break and it will close the server
    * socket connection and the client connection.
    */
    close(client2);
    disponible_server_PA=0;

}
void rm_init(char* ip,int port,char* ipHA,int portHA){
    portNum=port;
    portNum2=portHA;
    thread t1(cliente); // para conectarse con el server activo
    thread t2(cliente2); //para conectarse al server pasivo
    t1.join();
    t2.join();


}

void rm_new(char* key,void* value,int value_size){

}
void rm_delete(char* msj){

}


#endif // RMLIB_H_INCLUDED
