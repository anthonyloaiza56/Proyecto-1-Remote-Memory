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

int puerto_client ;
int portNum2 ;
int disponible_server_HA=0; //ASI VERIFICO SI ESTA CONECTADO O DESCONECTADO
int disponible_server_PA=0;
int client; //socket cliente 1, osea el del servidor activo
int bufsize = 1024; // buffer size
char buffer[1024]; // buffer to transmit
char ip[] = "127.0.0.1"; // Server IP
bool isExit = false; // var fo continue infinitly
string echo="";
string echo2="";
int client2; //socket cliente 2, osea el del servidor pasivo
char buffer2[1024]; // buffer to transmit
bool isExit2 = false; // var fo continue infinitly


string& bufferToString(char* buffer, int bufflen, string& str)
{
    char temp[bufflen];
    memset(temp, '\0', bufflen + 1);
    strncpy(temp, buffer, bufflen);
    return(str.assign(temp));
}
/*
Convierte un buffer en string
*/
struct rmRef_h{
    string llave;
    int Size;
    string valor;

};
void peticion(int cliente_S,char B[],int size_B)
{
    char msj[1024]="pt*";
    char msj2[1024]="pt*";
    if (cliente_S==1)
    {
         send(client,msj,size_B,0);
         recv(client, buffer, bufsize, 0);
    }
    if (cliente_S==2)
    {
        send(client2,msj,size_B,0);
        recv(client2, buffer2, bufsize, 0);
    }


}
/*
envia un mensaje a un servidor y espera su respuesta
*/

void enviar(string data,int size_B)
{

    char string_array[1024];
    strcpy(string_array, data.c_str());
    send(client,string_array,size_B,0);

}
/*
envia un mensaje a un servidor
*/
void cliente(){

    /* Structure describing an Internet socket address. */
    struct sockaddr_in server_addr;

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

        exit(-1);
            }
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
    server_addr.sin_port = htons(puerto_client);
    /*
    * This function converts an Internet address (either IPv4 or IPv6)
    * from presentation (textual) to network (binary) format.
    * If the comunication is on the same machine, you can comment this line.
    */
    inet_pton(AF_INET, ip, &server_addr.sin_addr);
    if (connect(client, (struct sockaddr *) &server_addr, sizeof(server_addr))
        < 0)
    // recive the welcome message from server
   // recv(client, buffer, bufsize, 0);
    // loop to send messages to server
    disponible_server_HA=1;
    send(client,"SA",1024,0);

}
/*
Permite conectarme con el servidor activo
*/

/***************************************************************************************/
/***************************************************************************************/

void cliente2(){


    /* Structure describing an Internet socket address. */
    struct sockaddr_in server_addr;



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

        exit(-1);
    }



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


    // recive the welcome message from server
    //recv(client2, buffer2, bufsize, 0);



        disponible_server_PA=0;
        send(client2,"SP",1024,0);
}
/*
permite conectarme con el servidor pasivo
*/
void rm_init(char* ip,int port,char* ipHA,int portHA)
{

    puerto_client=port;
    portNum2=portHA;
    thread t1(cliente); // para conectarse con el server activo
    thread t2(cliente2);
    t1.join();
    t2.join();

}

void rm_new(char* key,void* value,int value_size)
{

}

void rm_delete(char* msj)
{

}
rmRef_h rm_get(char* key){
    rmRef_h resultado;
    return resultado;

}


#endif // RMLIB_H_INCLUDED
