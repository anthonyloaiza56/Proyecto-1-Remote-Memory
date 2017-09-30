/*!
 * Servidor Activo-Pasivo
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
int puerto_SP =4589;
int client_sa; // socket file descriptor
char ip[] = "127.0.0.1"; // Server IP
string echo;

/*********LISTA ENLAZADA*******/
struct nodo{

    string llave;
    string valor;
    int tam;
    int referencias;        // en este caso es un numero entero
    struct nodo *sgte;
};
typedef struct nodo *Tlista;
Tlista inicio, fin;
Tlista memoria = NULL;
int min_reff;
int long_lista=2;
/*
Define la estructura del nodo de la lista que usare
*/
void insertarFinal(Tlista &lista, int refer,string val,string key)
{
    long_lista+=1;
    Tlista t, q = new(struct nodo);

    q->referencias  = refer;
    q->valor=val;
    q->llave=key;
    q->sgte = NULL;

    if(lista==NULL)
    {
        lista = q;
    }
    else
    {
        t = lista;
        while(t->sgte!=NULL)
        {
            t = t->sgte;
        }
        t->sgte = q;
    }

}
/*
Metodo donde se inserta un valor de memoria, en el final para evitar mas complejidad
*/
Tlista buscarElemento_llave(Tlista lista, string key,string modo)
{
    if(modo=="ref"){
        Tlista q = lista;
        int i = 1, band = 0;

        while(q!=NULL)
        {
            if(q->llave == key)
            {
                cout<<endl<<"El valor de la llave indicada esta en la posicion "<< i <<endl;
                cout<<q->valor;
                band = 1;
                q->referencias+=1;
                return q;
            }
            q = q->sgte;
            i++;
        }

        if(band==0){

        }

    }
    else if(modo=="cmp"){


    }


    //cout<<"\n\n Numero no encontrado..!"<< endl;

}
/*
Metodo donde se inserta una llave y se busca en la lista de memoria
*/
int buscarElemento_ref(Tlista lista, int refer)
{


    Tlista q = lista;
    int i = 1, band = 0;

    while(q!=NULL)
    {
        if(q->referencias==refer)
        {

            cout<<endl<<" Encontrada en posicion "<< i <<endl;
            band = 1;
        }
        q = q->sgte;
        i++;
    }

    if(band==0){
        return 1;
    }

    //cout<<"\n\n Numero no encontrado..!"<< endl;

}
int min_ref(Tlista lista){
    bool encontrado=false;
    int min_n=0;
    while(encontrado!=true){
        if(buscarElemento_ref(lista,min_n)==1){
            min_n+=1;
        }
        else if(buscarElemento_ref(lista,min_n)!=1){
            encontrado=true;
        }
    }
    return min_n;
}

string reportarLista(Tlista inicio)
{
    string listaa;
    int l=0;
    while(inicio != NULL)
    {
        //cout <<"  " << inicio->valor ;
        listaa+= inicio->llave +" ,"+ inicio->valor+ " ,"+to_string(inicio->referencias)+ " ,"+to_string(sizeof(inicio->valor));
        listaa+="\n";
        l+=1;
        inicio = inicio->sgte;
    }
    cout<<"largo";
    cout<<"\n";
    cout<<l;
    cout<<listaa;
    long_lista=l;
    return listaa;
    
}

string reportarCache(Tlista inicio)
{
    string cache;
    int recorredor=0;


    while(recorredor != long_lista)
    {

            if(recorredor > (long_lista-6)){
                cache+= inicio->llave +" ,"+ inicio->valor+ " ,"+to_string(inicio->referencias)+ " ,"+to_string(sizeof(inicio->valor))+"\n";
            }
            recorredor+=1;
            inicio = inicio->sgte;
    }
    cout<<cache;
    return cache;
}


void eliminarElemento(Tlista &lista, int refer)
{
    long_lista-=1;
    Tlista p, ant;
    p = lista;

    if(lista!=NULL)
    {
        while(p!=NULL)
        {
            if(p->referencias==refer)
            {
                if(p==lista)
                    lista = lista->sgte;
                else
                    ant->sgte = p->sgte;

                delete(p);
                return;
            }
            ant = p;
            p = p->sgte;
        }
    }
    else
        cout<<" Lista vacia..!";
}

void eliminarElemento_llave(Tlista &lista, string key_delete )
{
    long_lista-=1;
    Tlista p, ant;
    p = lista;

    if(lista!=NULL)
    {
        while(p!=NULL)
        {
            if(p->llave==key_delete)
            {
                if(p==lista)
                    lista = lista->sgte;
                else
                    ant->sgte = p->sgte;

                delete(p);
                return;
            }
            ant = p;
            p = p->sgte;
        }
    }
    else
        cout<<" Lista vacia..!";
}
void ordenarLista(Tlista lista)
{
    Tlista actual , siguiente;
    int t;
    int tam_aux;
    string valor_aux;
    string llave_aux;
    actual = lista;
    while(actual->sgte != NULL)
    {
        siguiente = actual->sgte;

        while(siguiente!=NULL)
        {
            if(actual->referencias > siguiente->referencias)
            {
                t = siguiente->referencias; //hace respaldo
                tam_aux=siguiente->tam;
                valor_aux=siguiente->valor;
                llave_aux=siguiente->llave;

                siguiente->referencias = actual->referencias;//modifica
                siguiente->valor = actual->valor;
                siguiente->llave = actual->llave;
                siguiente->tam = actual->tam;

                actual->referencias = t;//reestablece
                actual->llave=llave_aux;
                actual->valor=valor_aux;
                actual->tam=tam_aux;
            }
            siguiente = siguiente->sgte;
        }
        actual = actual->sgte;
        siguiente = actual->sgte;

    }

    cout<<"\n\n\tLista ordenada..."<<endl;
}
int insertarAntesDespues()
{
    int _op, band;
    cout<<endl;
    cout<<"\t 1. Antes de la posicion           "<<endl;
    cout<<"\t 2. Despues de la posicion         "<<endl;

    cout<<"\n\t Opcion : "; cin>> _op;

    if(_op==1)
        band = -1;
    else
        band = 0;

    return band;
}
void insertarElemento(Tlista &lista, int valor, int pos)
{
    Tlista q, t;
    int i;
    q = new(struct nodo);
    q->referencias = valor;

    if(pos==1)
    {
        q->sgte = lista;
        lista = q;
    }
    else
    {
        int x = insertarAntesDespues();
        t = lista;

        for(i=1; t!=NULL; i++)
        {
            if(i==pos+x)
            {
                q->sgte = t->sgte;
                t->sgte = q;
                return;
            }
            t = t->sgte;
        }
    }
    cout<<"   Error...Posicion no encontrada..!"<<endl;
}


/*********FIN LISTA ENLAZADA*******/



string& bufferToString(char* buffer, int bufflen, string& str)
{
    char temp[bufflen];

    memset(temp, '\0', bufflen + 1);
    strncpy(temp, buffer, bufflen);

    return(str.assign(temp));
}
/*
 * Funcion para convertir un dato buffer en string
 */

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
    send(client_sa,"mensaje del servidor activo",10240,0);
}

void server_SP()
{
    /* -------------- INITIALIZING VARIABLES -------------- */
    int server, client_sp; // socket file descriptors
    int portNum = 2754; // port number
    int bufSize = 10240; // buffer size
    char buffer[bufSize]; // buffer to transmit
    bool isExit = false; // var fo continue infinitly

    /* Structure describing an Internet socket address. */
    struct sockaddr_in server_addr;
    socklen_t size;

    cout << "\n- Starting server Pasivo..." << endl;

    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/

    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        cout << "Error establishing socket ..." << endl;
        exit(-1);
    }

    cout << "- Socket server has been created..." << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);

    int yes = 1;
    if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        perror("setsockopt");
        exit(1);
    }

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


    listen(server, 1);

    /* ------------------- ACCEPT CALL ------------------ */

    client_sp = accept(server, (struct sockaddr *) &server_addr, &size);


    if (client_sp < 0)
        cout << "- Error on accepting..." << endl;

    string echo;
    while (client_sp > 0) {
        // Welcome message to client
        //strcpy(buffer, "\n-> Welcome to echo server...\n");
        //send(client, buffer, bufSize, 0);
        cout << "- Connectado con el servidor activo, esperando datos..." << endl;
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
            if(rep==200){

                cout<<"SERVIDOR ACTIVO DESCONECTADO";
                isExit=true;



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
        exit(1);

    }

    /* ---------------- CLOSE CALL ------------- */
    close(server);
}
void server_to_rm()
{
    /* -------------- INITIALIZING VARIABLES -------------- */
    int server, client; // socket file descriptors
    int portNum = 1987; // port number
    int bufSize = 10240; // buffer size
    char buffer[bufSize]; // buffer to transmit
    bool isExit = false; // var fo continue infinitly

    /* Structure describing an Internet socket address. */
    struct sockaddr_in server_addr;
    socklen_t size;

    cout << "\n- Starting server..." << endl;

    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/

    server = socket(AF_INET, SOCK_STREAM, 0);


    if (server < 0) {
        cout << "Error establishing socket ..." << endl;
        exit(-1);
    }

    cout << "- Socket server has been created..." << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);

    int yes = 1;
    if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    /* ---------------- BINDING THE SOCKET --------------- */

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

    listen(server, 1);

    /* ------------------- ACCEPT CALL ------------------ */

    client = accept(server, (struct sockaddr *) &server_addr, &size);


    if (client < 0)
        cout << "- Error on accepting..." << endl;

    
    while (client > 0) {
        // Welcome message to client
        //strcpy(buffer, "\n-> Welcome to echo server...\n");
        //send(client, buffer, bufSize, 0);
        cout << "- Connected with the client, waiting for data..." << endl;
        // loop to recive messages from client
        do {
            cout << "\nCliente RMLIB: ";
            echo = "";
            do {
                recv(client, buffer, bufSize, 0);
                string dato;
                bufferToString(buffer, sizeof(buffer), dato);

                send(client_sa,buffer,10240,0); //envia al servidor pasivo el dato
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

                string tmp;
                tmp=dato[0];
                if(mode==1){//como SA revisara lo que reciba del cliente
                    cout<<"\n Soy server activo\n ";
                    cout<<"\n Indicacion tipo :"+tmp+"\n";
                    if(tmp=="1") //ingresar nuevo valor a la lista
                    {
                        cout<<"\nIngresando nuevo valor\n";
                       
                        int ref=0;
                        string valor;
                        string llave;
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
                                if(tmp!="_"){
                                    valor+=tmp;
                                }
                                iterador+=1;

                            }

                        }
                        cout<<valor;
                        cout<<"\n";
                        cout<<llave;
                        cout<<"\n";
                        insertarFinal(memoria,0,valor,llave);
                        long_lista+=1;
                        cout<<"Se agrego una nueva llave\n";
                    }
                    else if(tmp=="2") //eliminar memoria
                    {
                        cout<<"eliminar llave";
                        int ref=0;
                        string valor;
                        string llave;
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
                                if(tmp!="_"){
                                    valor+=tmp;
                                }
                                iterador+=1;

                            }

                        }
                        cout<<"\nllave";
                        cout<<"\n";
                        cout<<llave;
                        cout<<"\n";

                        //buscarElemento_llave(memoria,llave);
                        eliminarElemento_llave(memoria,llave);
                    }
                    else if(tmp=="3") //consultar memoria
                    {
                        cout<<"\n Ver memoria: \n";
                        echo=reportarLista(memoria);
                    }
                    else if(tmp=="4") //ver cache
                    {
                        cout<<"\n Ver cache: \n";
                        ordenarLista(memoria);
                        echo=reportarCache(memoria);
                        //sprintf(buffer, "%s",mem.c_str());
                        //send(client,buffer,1024,0);

                    }
                    else if(tmp=="5") //consultar memoria
                    {

                        cout<<"\n Consultar Memoria: \n";

                        int ref=0;
                        string valor;
                        string llave;
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
                                if(tmp!="_"){
                                    valor+=tmp;
                                }
                                iterador+=1;

                            }

                        }
                        cout<<"\nllave";
                        cout<<"\n";
                        cout<<llave;
                        cout<<"\n";
                        buscarElemento_llave(memoria,llave,"ref");


                        //sprintf(buffer, "%s", cach.c_str());
                        //send(client,buffer,1024,0);
                    }
                    else if(tmp=="6") //compara valores de llave
                    {

                    }
                    else if(tmp=="7") //copia valores de llave
                    {

                    }
                    cout << buffer << "\n ";
                    //echo = "Goodbye, ha sidp un gusto,!\n mucho,mcuha skms \n gusto";

                    sprintf(buffer, "%s", echo.c_str());
                    //send the message to the client
                    send(client, buffer, bufSize, 0);

                }





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
