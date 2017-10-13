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
#include <unistd.h>

using namespace std;

int decicion;
int mode;//1=Activo,2=Pasivo
bool establecido=false;
int puerto_SA_SP ; //puerto para conectar el activo con el pasivo
int puerto_SP ; // puerto del servidor pasivo
int puerto_RM ; // puerto del cliente RM
int client_rm;
int client_sa; // socket del servidor activo
char ip[] = "127.0.0.1"; // IP para conectarse con el servidor pasivo
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
int long_lista;
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
int buscarElemento_llave(Tlista lista, string key,string modo)
{
    if(modo=="ref"){ //solo lo busca y aumenta una referencia
        Tlista q = lista;//temporal de la memoria, donde se recorre hasta encontrar la llave indicada
        int i = 1, band = 0;

        while(q!=NULL)
        {
            if(q->llave == key)
            {
                cout<<endl<<"El valor de la llave indicada esta en la posicion "<< i <<endl;
                cout<<q->valor;
                band = 1;
                q->referencias+=1;
                return 1;
            }
            q = q->sgte;
            i++;
        }

        if(band==0){
            return 0;
        }

    }
    else if(modo=="cmp"){ //busca,aumenta una referencia y retorna el nodo
        Tlista q = lista; //temporal de la memoria, donde se recorre hasta encontrar la llave indicada
        int i = 1, band = 0;

        while(q!=NULL)
        {
            if(q->llave == key)
            {
                cout<<endl<<"El valor de la llave indicada esta en la posicion "<< i <<endl;
                cout<<q->valor;
                band = 1;
                q->referencias+=1;
                echo=q->valor;
                return 1;
            }
            q = q->sgte;
            i++;
        }

        if(band==0){
            return 0;
        }
    }

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
    int largo=0;
    while(inicio != NULL)
    {
        //cout <<"  " << inicio->valor ;
        listaa+= inicio->llave +" ,"+ inicio->valor+ " ,"+to_string(inicio->referencias)+ " ,"+to_string(sizeof(inicio->valor));
        listaa+="\n";
        largo+=1;
        inicio = inicio->sgte;
    }
    cout<<"largo";
    cout<<"\n";
    cout<<largo;
    cout<<listaa;
    long_lista=largo;
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
void cronometro() {
    int x=0;
    while (true) {
        unsigned int microseconds = 5000000;
        usleep(microseconds);
        if(x==10){
            x=0;
            if(long_lista>2){
                if(mode==1){
                    int min=min_ref(memoria);
                    eliminarElemento(memoria,min);
                    cout<<"Se eliminó la llave menos referenciada";
                    long_lista-=1;
                    char mensaje[10240];
                    string msj="6"+std::to_string(min)+"*";
                    // bufferToString(mensaje, sizeof(mensaje), msj);
                    strcpy(mensaje, msj.c_str());
                    send(client_sa,mensaje,10240,0);
                }
            }
        }
        x+=1;
    }
}
/*
 * Funcion que recorre cada cierto tiempo y elimina el elemento menos referenciado
 */
void client_SA()
{
    char buff[10240];
    struct sockaddr_in server_addr;
    client_sa = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sa < 0)
    {
        exit(-1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(puerto_SA_SP);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);
    if (connect(client_sa, (struct sockaddr *) &server_addr, sizeof(server_addr))
        < 0);
    if(decicion==1){
        send(client_sa,"mensaje del servidor activo",10240,0);
    }
    else if(decicion=2) {
        string data;
        cout << "\nSincronizando...\n";
        string mensaje_s = "Sincronizar";
        char string_array[10240];
        strcpy(string_array, mensaje_s.c_str());
        cout << "\nEsperando\n";
        send(client_sa, string_array, 10240, 0);
        while (data != "END") {

            recv(client_sa, buff, 10240, 0);
            cout << "\nListo\n";
            cout << buff;
            cout<<data;
            bufferToString(buff, 10240, data);
        }
    }

}

void server_SP()
{
    while(true) {
        /* -------------- INITIALIZING VARIABLES -------------- */
        int server, client_sp; // socket file descriptors
        int bufSize = 10240; // buffer size
        char buffer[bufSize]; // buffer to transmit
        bool isExit = false; // var fo continue infinitly

        /* Structure describing an Internet socket address. */
        struct sockaddr_in server_addr;
        socklen_t size;

        cout << "\n- Iniciando servidor Pasivo..." << endl;

        /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/

        server = socket(AF_INET, SOCK_STREAM, 0);
        if (server < 0) {
            cout << "Error estableciendo el socket ..." << endl;
            exit(-1);
        }

        cout << "- Socket servidor creado..." << endl;

        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htons(INADDR_ANY);
        server_addr.sin_port = htons(puerto_SP);

        int yes = 1;
        if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if ((bind(server, (struct sockaddr *) &server_addr, sizeof(server_addr)))
            < 0) {
            cout
                    << "- Error:SOCKET EN USO..."
                    << endl;
            exit(-1);
        }

        /* ------------------ LISTENING CALL ----------------- */

        size = sizeof(server_addr);
        cout << "- Buscando servidor activo" << endl;


        listen(server, 1);

        /* ------------------- ACCEPT CALL ------------------ */

        client_sp = accept(server, (struct sockaddr *) &server_addr, &size);


        if (client_sp < 0)
            cout << "- Error al aceptar..." << endl;

        string echo;
        while (client_sp > 0) {
            // Welcome message to client
            //strcpy(buffer, "\n-> Welcome to echo server...\n");
            //send(client, buffer, bufSize, 0);
            cout << "- Connectado con el servidor activo, esperando datos..." << endl;
            // loop to recive messages from client
            char d[10240];
            echo="Recibido";
            sprintf(d, "%s", echo.c_str());
            //send the message to the client
            send(client_sp, d, bufSize, 0);
            int rep = 0;
            string dato;
            string dato2;
            do {
                if (dato == dato2) {
                    rep += 1;
                }
                dato2 = dato;

                echo = "";
                recv(client_sp, buffer, bufSize, 0);
                bufferToString(buffer, sizeof(buffer), dato); // pasa de buffer a dato
                cout << buffer << "\n ";
                if (rep == 300) {

                    cout << "\nSERVIDOR ACTIVO DESCONECTADO\n";
                    isExit = true;
                }

                string tmp;
                string tmp2;
                tmp=dato[0];
                tmp2=dato[1];

                if(tmp!="7"){
                    cout << "\nSA: ";
                    cout<<"\n Indicacion desde Activo tipo :"+tmp+"\n";
                }

                if(tmp=="1") //ingresar nuevo valor a la lista
                {
                    cout<<"\nIngresando nuevo valor como SP\n";

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
                    if(buscarElemento_llave(memoria,llave,"ref")==1){
                        echo="La llave ingresada esta en uso";

                    }
                    else if(buscarElemento_llave(memoria,llave,"ref")==0){
                        echo="Llave agregada";
                        insertarFinal(memoria,0,valor,llave);
                        long_lista+=1;
                        cout<<"Se agrego una nueva llave\n";
                    }
                }
                else if(tmp=="2") //eliminar memoria
                {
                    cout<<"eliminar llave como SP";
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
                    if(buscarElemento_llave(memoria,llave,"ref")==1){
                        echo="Eliminado";
                        eliminarElemento_llave(memoria,llave);

                    }
                    else if(buscarElemento_llave(memoria,llave,"ref")==0){
                        echo="Llave no encontrada";
                    }

                }
                else if(tmp=="5") //aumentar referencia
                {

                    cout<<"\n Aumentar referencia: \n";

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
                    if(buscarElemento_llave(memoria,llave,"ref")==1){
                        echo="Referencia aumentada";

                    }
                    else if(buscarElemento_llave(memoria,llave,"ref")==0){
                        echo="Llave no encontrada";
                    }

                }
                else if(tmp=="6"){
                    int min = atoi(tmp2.c_str());
                    eliminarElemento(memoria,min);
                    cout<<"Eliminando\n";

                }
                else if(tmp=="S") //compara valores de llave
                {
                    mode=2;
                    cout<<"SINCRONIZADO AL SERVIDOR ACTIVO";
                }
                else if(tmp=="7") //copia valores de llave
                {

                }
            } while (!isExit);

            /* ---------------- CLOSE CALL ------------- */
            cout << "\n\n=> Connection terminated with IP "
                 << inet_ntoa(server_addr.sin_addr);
            // close(client_sp);
            /* ---------------- CLOSE CALL ------------- */
            close(server);
            cout << "\nGoodbye..." << endl;
            //exit(1);
            client_sp = 0;
            mode=1;
            cout<<"MEMORIA REPORTADA";
            reportarLista(memoria);
        }

    }
}
void server_to_rm()
{
    /* -------------- INITIALIZING VARIABLES -------------- */
    int server_rm; // socket file descriptors
    int bufSize = 10240; // buffer size

    bool isExit = false; // var fo continue infinitly

    /* Structure describing an Internet socket address. */
    struct sockaddr_in server_addr;
    socklen_t size;

    cout << "\n- Iniciando servidor hacia cliente RM..." << endl;

    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/

    server_rm = socket(AF_INET, SOCK_STREAM, 0);


    if (server_rm < 0) {
        cout << "Error estableciendo el socket ..." << endl;
        exit(-1);
    }

    cout << "- Socket servidor creado..." << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(puerto_RM);

    int yes = 1;
    if (setsockopt(server_rm, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    /* ---------------- BINDING THE SOCKET --------------- */

    if ((bind(server_rm, (struct sockaddr*) &server_addr, sizeof(server_addr)))
        < 0) {
        cout
                << "- Error:Socket en uso"
                << endl;
        exit(-1);
    }

    /* ------------------ LISTENING CALL ----------------- */

    size = sizeof(server_addr);
    cout << "- Esperando al cliente..." << endl;

    listen(server_rm, 1);

    /* ------------------- ACCEPT CALL ------------------ */

    client_rm = accept(server_rm, (struct sockaddr *) &server_addr, &size);


    if (client_rm < 0)
        cout << "- Error al aceptarlo..." << endl;


    // Welcome message to client
    cout << "- Conectado con cliente RMLIB..." << endl;
    // loop to recive messages from client
    while (client_rm > 0) {


        echo = "";

        char buffer[bufSize]; // buffer to transmit
        recv(client_rm, buffer, bufSize, 0);
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
            if(tmp!="7"){
                cout << "\nCliente RMLIB: ";
                cout<<"\n Soy server activo\n ";
                cout<<"\n Indicacion tipo :"+tmp+"\n";
            }

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
                if(buscarElemento_llave(memoria,llave,"ref")==1){
                    echo="La llave ingresada esta en uso";

                }
                else if(buscarElemento_llave(memoria,llave,"ref")==0){
                    echo="Llave agregada";
                    insertarFinal(memoria,0,valor,llave);
                    long_lista+=1;
                    cout<<"Se agrego una nueva llave\n";
                }
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
                if(buscarElemento_llave(memoria,llave,"ref")==1){
                    echo="Eliminado";
                    eliminarElemento_llave(memoria,llave);

                }
                else if(buscarElemento_llave(memoria,llave,"ref")==0){
                    echo="Llave no encontrada";
                }
                //buscarElemento_llave(memoria,llave);

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

            }
            else if(tmp=="5") //aumentar referencia
            {

                cout<<"\n Aumentar referencia: \n";
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
                if(buscarElemento_llave(memoria,llave,"ref")==1){
                    echo="Referencia aumentada";

                }
                else if(buscarElemento_llave(memoria,llave,"ref")==0){
                    echo="Llave no encontrada";
                }

            }
            else if(tmp=="9"){ //compara valores de llave

                int ref=0;
                string llave_c;
                int iterador=1;
                string tmp;
                tmp=dato[iterador];
                while(tmp!="_"){
                    llave_c+=tmp;
                    iterador+=1;
                    tmp=dato[iterador];
                }
                cout<<"llave";
                cout<<"\n";
                cout<<llave_c;
                cout<<"\n";
                buscarElemento_llave(memoria,llave_c,"cmp");
                char myArray[10240];
                strcpy(myArray, echo.c_str());
                //send the message to the client
                send(client_rm, myArray, bufSize, 0);
                strcpy(buffer, "");
                continue;
            }
            else if(tmp=="7") //copia valores de llave
            {
                char myArray[10240];
                strcpy(myArray, echo.c_str());
                //send the message to the client
                send(client_rm, myArray, bufSize, 0);
                strcpy(buffer, "");
                continue;
            }
        }
        if(mode==2){
            echo="Hecho";

        }
        sprintf(buffer, "%s", echo.c_str());

        char myArray[10240];
        strcpy(myArray, echo.c_str());
        //send the message to the client
        send(client_rm, myArray, bufSize, 0);
        strcpy(buffer, "");
    }
    /* ---------------- CLOSE CALL ------------- */
    cout << "\n\n=> Connection terminated with IP "
         << inet_ntoa(server_addr.sin_addr);
    close(client_rm);
    cout << "\nGoodbye..." << endl;
    exit(1);
    /* ---------------- CLOSE CALL ------------- */
    close(server_rm);
}
int main() {
    cout<<"1:Conectar\n 2:Re-conectar SA\n";
    cin>>decicion;
    if(decicion==1){

        cout<<"Ingrese puerto del cliente RM\n";
        cin>>puerto_RM;
        cout<<"Ingrese puerto del servidor Pasivo\n";
        cin>>puerto_SP;
        cout<<"Ingrese puerto para conectar server Activo con pasivo\n";
        cin>>puerto_SA_SP;
        thread t1(server_to_rm);
        thread t2(server_SP);
        thread t3(cronometro);
        t1.join();
        t2.join();
        t3.join();
    }
    else if(decicion==2)
    {
        mode=1;
        cout<<"Ingrese puerto del cliente RM\n";
        cin>>puerto_RM;
        cout<<"Ingrese puerto para conectar server Activo con pasivo\n";
        cin>>puerto_SA_SP;
        thread t1(server_to_rm);
        thread t2(client_SA);
        thread t3(cronometro);

        t3.join();
        t1.join();
        t2.join();
    }
    return 0;
}
