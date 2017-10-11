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
int reconexion=1;
int size_memoria=0;
int puerto_client ;
int portNum2 ;
int disponible_server_HA=0; //ASI VERIFICO SI ESTA CONECTADO O DESCONECTADO
int disponible_server_PA=0;
int client; //socket cliente 1, osea el del servidor activo
int bufsize = 10240; // buffer size
 char buffer[10240];
    char buffer2[10240];
char ip[] = "127.0.0.1"; // Server IP
bool isExit = false; // var fo continue infinitly
string echo="";
string echo2="";
int client2; //socket cliente 2, osea el del servidor pasivo

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

rmRef_h operator ==(rmRef_h A,rmRef_h B){
    if(A.valor==B.valor){
        wxMessageBox("Correcto");
        return A;
    }
    else{
        wxMessageBox("Incorrecto");
        return A;
    }
}
rmRef_h operator !=(rmRef_h A,rmRef_h B){
    if(A.valor!=B.valor){
        wxMessageBox("Correcto");
        return A;
    }
    else{
        wxMessageBox("Incorrecto");
        return A;
    }
}


void peticion(string data2,string llave)
{
    if(data2=="3"){ //consulta de memoria
        char msj[10240]="3k_ll*";
        send(client,msj,10240,0);
        send(client2,msj,10240,0);
        recv(client, buffer, bufsize, 0);
        recv(client2, buffer2, bufsize, 0);
    }
    else if(data2=="4"){ //consulta de cache
         char msj[10240]="4k_ll*";
         send(client,msj,10240,0);
         send(client2,msj,10240,0);
         recv(client, buffer, bufsize, 0);
         recv(client2, buffer2, bufsize, 0);

    }
    else if(data2=="5")
        { //consulta de llave para aumentar en 1 la referencia
        data2="5"+llave+"_ll*";
        char string_array[10240];
        strcpy(string_array, data2.c_str());
        send(client,string_array,10240,0);
        send(client2,string_array,10240,0);
        recv(client, buffer, bufsize, 0);
        recv(client2, buffer2, bufsize, 0);
         strcpy(buffer, "");

    }
    else if(data2=="2"){ //elimina la llave

        data2="2"+llave+"_ll*";
        char string_array[10240];
        strcpy(string_array, data2.c_str());
        send(client,string_array,10240,0);
        send(client2,string_array,10240,0);
        recv(client, buffer, bufsize, 0);
        recv(client2, buffer2, bufsize, 0);
        strcpy(buffer, "");
    }
    else if(data2=="9"){ //comparar llaves
        data2="9"+llave+"_ll*";
        char string_array[10240];
        strcpy(string_array, data2.c_str());
        send(client,string_array,10240,0);
        send(client2,string_array,10240,0);
        recv(client, buffer, bufsize, 0);
        recv(client2, buffer2, bufsize, 0);
        strcpy(buffer, "");
    }
    else if(data2=="7"){ // envia un dato vacio en espera de ir recorriendo el buffer
         char msj[10240]="7k_ll*";
         send(client,msj,10240,0);
         send(client2,msj,10240,0);
         recv(client, buffer, bufsize, 0);
         recv(client2, buffer2, bufsize, 0);
    }

}
/*
envia un mensaje a un servidor y espera su respuesta
*/

void enviar(string data,int size_B)
{

    char string_array[10240];
    strcpy(string_array, data.c_str());
    send(client,string_array,size_B,0);
    send(client2,string_array,size_B,0);
    wxMessageBox(string_array);
}
/*
envia un mensaje a un servidor
*/
void cliente(){

    /* Structure describing an Internet socket address. */
    struct sockaddr_in server_addr;

    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/
    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0)
            {

        exit(-1);
            }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(puerto_client);

    inet_pton(AF_INET, ip, &server_addr.sin_addr);
    if (connect(client, (struct sockaddr *) &server_addr, sizeof(server_addr))
        < 0)
    // recive the welcome message from server
   // recv(client, buffer, bufsize, 0);
    // loop to send messages to server
    disponible_server_HA=1;
    if(reconexion==1){
    send(client,"SA",1024,0);
    }


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

    if (client2 < 0) {

        exit(-1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum2);

    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    /* ---------- CONNECTING THE SOCKET ---------- */

    if (connect(client2, (struct sockaddr *) &server_addr, sizeof(server_addr))
        < 0)
        disponible_server_PA=0;
        send(client2,"SP",1024,0);
}

void iniciar_cliente_SA(){
    size_memoria+=1;
    strcpy(buffer, "");
    reconexion=0;
    close(client);
    thread t3(cliente); // para conectarse con el server activo
    t3.join();




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

void rm_new(string key,string value,int value_size)
{
    string dato_enviar="1"+key+"_"+value+"*";
    enviar(dato_enviar,10240);
}

void rm_delete(string llave)
{
    peticion("5",llave);

}
rmRef_h rm_get(string key){
    rmRef_h resultado;
    return resultado;

}


#endif // RMLIB_H_INCLUDED
