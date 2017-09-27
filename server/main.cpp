/*!
 * Simple socket program server.cpp
 * Version - 1.0.0
 * Based on: Simple chat program (server side).cpp - http://github.com/hassanyf
 *
 * Copyleft (c) 2017 Rodrigo Tufino <rtufino@ups.edu.ec, r.tufino@alumnos.upm.es>
 */

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <thread>

using namespace std;

int mode;//1=Activo,2=Pasivo
bool establecido=false;
int puerto_SP =3832;
int client_sa; // socket file descriptors
// port number (same that server)

char ip[] = "127.0.0.1"; // Server IP

string& bufferToString(char* buffer, int bufflen, string& str)
{
    char temp[bufflen];

    memset(temp, '\0', bufflen + 1);
    strncpy(temp, buffer, bufflen);

    return(str.assign(temp));
}

void client_SA()
{

    struct sockaddr_in server_addr;
    client_sa = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sa < 0)
    {
        exit(-1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(puerto_SP);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);
    if (connect(client_sa, (struct sockaddr *) &server_addr, sizeof(server_addr))
        < 0);
    send(client_sa,"mensaje del servidor activo",1024,0);
}

void server_SP()
{
    /* -------------- INITIALIZING VARIABLES -------------- */
    int server, client_sp; // socket file descriptors
    int portNum = 8534; // port number
    int bufSize = 1024; // buffer size
    char buffer[bufSize]; // buffer to transmit
    bool isExit = false; // var fo continue infinitly

    /* Structure describing an Internet socket address. */
    struct sockaddr_in server_addr;
    socklen_t size;

    cout << "\n- Starting server Pasivo..." << endl;

    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/

    server = socket(AF_INET, SOCK_STREAM, 0);

    /*
    * The socket() function creates a new socket.
    * It takes 3 arguments:
    * 1) AF_INET: address domain of the socket.
    * 2) SOCK_STREAM: Type of socket. a stream socket in
    * which characters are read in a continuous stream (TCP)
    * 3) Third is a protocol argument: should always be 0.
    * If the socket call fails, it returns -1.
    */

    if (server < 0) {
        cout << "Error establishing socket ..." << endl;
        exit(-1);
    }

    cout << "- Socket server has been created..." << endl;

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
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);

    /*
    * This function is used to set the socket level for socket.
    * It is used to avoid blind error when reuse the socket.
    * For more info, see the url.
    * http://stackoverflow.com/questions/5592747/bind-error-while-recreating-socket
    */

    int yes = 1;
    if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    /* ---------------- BINDING THE SOCKET --------------- */

    /*
    * The bind() system call binds a socket to an address,
    * in this case the address of the current host and port number
    * on which the server will run. It takes three arguments,
    * the socket file descriptor. The second argument is a pointer
    * to a structure of type sockaddr, this must be cast to
    * the correct type.
    */

    if ((bind(server, (struct sockaddr*) &server_addr, sizeof(server_addr)))
        < 0) {
        cout
                << "- Error binding connection, the socket has already been established..."
                << endl;
        exit(-1);
    }

    /* ------------------ LISTENING CALL ----------------- */

    size = sizeof(server_addr);
    cout << "- Looking for server activo" << endl;

    /*
    * The listen system call allows the process to listen
    * on the socket for connections.
    * The program will be stay idle here if there are no
    * incomming connections.
    * The first argument is the socket file descriptor,
    * and the second is the size for the number of clients
    * i.e the number of connections that the server can
    * handle while the process is handling a particular
    * connection. The maximum size permitted by most
    * systems is 5.
    */

    listen(server, 1);

    /* ------------------- ACCEPT CALL ------------------ */

    client_sp = accept(server, (struct sockaddr *) &server_addr, &size);

    /*
    * The accept() system call causes the process to block
    * until a client connects to the server. Thus, it wakes
    * up the process when a connection from a client has been
    * successfully established. It returns a new file descriptor,
    * and all communication on this connection should be done
    * using the new file descriptor. The second argument is a
    * reference pointer to the address of the client on the other
    * end of the connection, and the third argument is the size
    * of this structure.
    */

    if (client_sp < 0)
        cout << "- Error on accepting..." << endl;

    string echo;
    while (client_sp > 0) {
        // Welcome message to client
        //strcpy(buffer, "\n-> Welcome to echo server...\n");
        //send(client, buffer, bufSize, 0);
        cout << "- Connected with the servidor activo, waiting for data..." << endl;
        // loop to recive messages from client
        int rep=0;
        string dato;
        string dato2;
        do {
            if(dato==dato2)
            {
                rep+=1;
            }
            dato2=dato;
            cout << "\nSA: ";
            echo = "";
            bufferToString(buffer, sizeof(buffer), dato); // pasa de buffer a dato
            recv(client_sp, buffer, bufSize, 0);
            cout << buffer << "\n ";
            if(rep==20){

                cout<<"SERVIDOR ACTIVO DESCONECTADO";
                isExit=true;
                rep=0;
            }
                /*echo = "Goodbye!";
                sprintf(buffer, "%s", echo.c_str());
                send(client, buffer, bufSize, 0);*/
                //cout << buffer << "\n ";
        } while (!isExit);

        /* ---------------- CLOSE CALL ------------- */
        cout << "\n\n=> Connection terminated with IP "
             << inet_ntoa(server_addr.sin_addr);
        close(client_sp);
        cout << "\nGoodbye..." << endl;
        //exit(1);

    }

    /* ---------------- CLOSE CALL ------------- */
    close(server);
}
void server_to_rm()
{
    /* -------------- INITIALIZING VARIABLES -------------- */
    int server, client; // socket file descriptors
    int portNum = 1987; // port number
    int bufSize = 1024; // buffer size
    char buffer[bufSize]; // buffer to transmit
    bool isExit = false; // var fo continue infinitly

    /* Structure describing an Internet socket address. */
    struct sockaddr_in server_addr;
    socklen_t size;

    cout << "\n- Starting server..." << endl;

    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/

    server = socket(AF_INET, SOCK_STREAM, 0);

    /*
    * The socket() function creates a new socket.
    * It takes 3 arguments:
    * 1) AF_INET: address domain of the socket.
    * 2) SOCK_STREAM: Type of socket. a stream socket in
    * which characters are read in a continuous stream (TCP)
    * 3) Third is a protocol argument: should always be 0.
    * If the socket call fails, it returns -1.
    */

    if (server < 0) {
        cout << "Error establishing socket ..." << endl;
        exit(-1);
    }

    cout << "- Socket server has been created..." << endl;

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
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);

    /*
    * This function is used to set the socket level for socket.
    * It is used to avoid blind error when reuse the socket.
    * For more info, see the url.
    * http://stackoverflow.com/questions/5592747/bind-error-while-recreating-socket
    */

    int yes = 1;
    if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    /* ---------------- BINDING THE SOCKET --------------- */

    /*
    * The bind() system call binds a socket to an address,
    * in this case the address of the current host and port number
    * on which the server will run. It takes three arguments,
    * the socket file descriptor. The second argument is a pointer
    * to a structure of type sockaddr, this must be cast to
    * the correct type.
    */

    if ((bind(server, (struct sockaddr*) &server_addr, sizeof(server_addr)))
        < 0) {
        cout
                << "- Error binding connection, the socket has already been established..."
                << endl;
        exit(-1);
    }

    /* ------------------ LISTENING CALL ----------------- */

    size = sizeof(server_addr);
    cout << "- Looking for clients..." << endl;

    /*
    * The listen system call allows the process to listen
    * on the socket for connections.
    * The program will be stay idle here if there are no
    * incomming connections.
    * The first argument is the socket file descriptor,
    * and the second is the size for the number of clients
    * i.e the number of connections that the server can
    * handle while the process is handling a particular
    * connection. The maximum size permitted by most
    * systems is 5.
    */

    listen(server, 1);

    /* ------------------- ACCEPT CALL ------------------ */

    client = accept(server, (struct sockaddr *) &server_addr, &size);

    /*
    * The accept() system call causes the process to block
    * until a client connects to the server. Thus, it wakes
    * up the process when a connection from a client has been
    * successfully established. It returns a new file descriptor,
    * and all communication on this connection should be done
    * using the new file descriptor. The second argument is a
    * reference pointer to the address of the client on the other
    * end of the connection, and the third argument is the size
    * of this structure.
    */

    if (client < 0)
        cout << "- Error on accepting..." << endl;

    string echo;
    while (client > 0) {
        // Welcome message to client
        //strcpy(buffer, "\n-> Welcome to echo server...\n");
        //send(client, buffer, bufSize, 0);
        cout << "- Connected with the client, waiting for data..." << endl;
        // loop to recive messages from client
        do {
            cout << "\nClient: ";
            echo = "";
            /*
            * A send operation from client is done for each word
            * has written on it's terminal line. We need a special
            * character to stop transmission and this loop works
            * until this char ('*') arrives.
            */
            do {
                recv(client, buffer, bufSize, 0);
                string dato;
                bufferToString(buffer, sizeof(buffer), dato);
                if(dato == "SP")
                {
                    if(establecido==false)
                    {
                        mode=2;
                        establecido==true;
                        cout<<"servidor pasivo";
                    }
                }
                if(dato == "SA" )
                {
                    if(establecido==false)
                    {
                        mode=1;
                        establecido==true;
                        cout<<"servidor activo";
                        thread t3(client_SA);

                        t3.join();
                    }

                }
                cout<<"dato\n";
                string tmp;
                tmp=dato[0];
                if(mode==1){//como SA revisara lo que reciba del cliente
                    cout<<"Soy server activo";
                    if(tmp=="1") //ingresar nuevo valor a la lista
                    {
                        cout<<"Ingresando nuevo valor\n";
                        int ref=0;
                        string valor;
                        string llave;
                        int size_t;
                        int iterador=1;
                        int conteo=0;
                        string tmp;
                        tmp=dato[iterador];
                        while(tmp!="*")
                        {
                            tmp=dato[iterador];
                            if(conteo==0){
                                if(tmp=="_")
                                {
                                    conteo+=1;
                                    continue;
                                }
                                iterador+=1;
                                llave+=tmp;
                            }
                            if(conteo==1){
                                if(tmp=="*")
                                {
                                    conteo+=1;
                                    continue;
                                }
                                iterador+=1;
                                valor+=tmp;
                            }

                        }
                        size_t=sizeof(valor);
                        cout<<valor;
                        cout<<"\n";
                        cout<<llave;
                        cout<<"\n";
                        cout<<"proceso listo\n";
                    }
                }
                cout << buffer << "\n ";
                echo = "Goodbye!";
                 sprintf(buffer, "%s", echo.c_str());
                //send the message to the client
                send(client, buffer, bufSize, 0);
                // wait the request from client
                //cout << buffer << "\n ";
                // verify if client does not close the connection
               /* if (*buffer == '#') {
                     // exit loop and say goodbye (It's a polite server :D)
                     isExit = true;
                     *buffer = '*';
                     echo = "Goodbye!";
                 } else if ((*buffer != '#') && (*buffer != '*')) {
                     // concatenate the echo string to response to the client
                     echo += buffer;
                     echo += " ";
                 }*/
            } while (*buffer != '*');
            // copy the echo string to the buffer
            sprintf(buffer, "%s", echo.c_str());
            // send the message to the client
            send(client, buffer, bufSize, 0);
        } while (!isExit);

        /* ---------------- CLOSE CALL ------------- */
        cout << "\n\n=> Connection terminated with IP "
             << inet_ntoa(server_addr.sin_addr);
        close(client);
        cout << "\nGoodbye..." << endl;
        exit(1);

    }

    /* ---------------- CLOSE CALL ------------- */
    close(server);

}
int main() {
    thread t1(server_to_rm);
    thread t2(server_SP);
    t1.join();
    t2.join();

    return 0;
}
