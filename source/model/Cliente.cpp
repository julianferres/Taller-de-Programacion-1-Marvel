#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>
#include <iostream>
#include <Cliente.hpp>
#include <string>
#include <tuple>

using namespace std;

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;

Cliente::Cliente( char * direccionIP){
	juegoCliente = new JuegoCliente();
	this->iniciarConexion(direccionIP);
	this->recibirIDcliente();
	this->elegirPersonaje();
	this->cargarContenidos();

	while(true){
		recibirParaDibujar();
	}

	close(numeroSocket);
}


void Cliente::iniciarConexion(char* direccionIP){
	int  conexion;
	struct hostent *nodoServidor;
	struct sockaddr_in servidor;

	nodoServidor=gethostbyname(direccionIP);
	if(nodoServidor==NULL)
		controladorLogger->registrarEvento("ERROR", "Cliente::Error en la conexion");

	numeroSocket=socket(AF_INET, SOCK_STREAM, 0);
	servidor.sin_family=AF_INET;
	servidor.sin_port=htons(PUERTO);
	servidor.sin_addr=*((struct in_addr *)nodoServidor->h_addr);
	bzero(&(servidor.sin_zero),8);
	conexion=connect(numeroSocket,(struct sockaddr *)&servidor,sizeof(struct sockaddr));
	if(conexion==-1)
		controladorLogger->registrarEvento("ERROR", "Cliente::Error al conectar con el servidor");
}

void Cliente::recibirIDcliente(){

	recv(numeroSocket,&idCliente,sizeof(idCliente),0);//se conectaron todos los jugadores
	controladorLogger->registrarEvento("INFO", "Cliente::El cliente "+to_string(idCliente)+"se conecto correctamente");

}

void Cliente::elegirPersonaje(){
	juegoCliente->iniciarGraficos();
	GameMenu *menu = new GameMenu(*juegoCliente->graficos(),idCliente);//inicio el menu

	//Seleccionamos el personaje y lo enviamos al server
	string personajeElegido = menu->personajeSeleccionado();//ya seleccione mi personaje
	controladorLogger->registrarEvento("INFO", "Cliente::El cliente "+to_string(idCliente)+" eligio al personaje" + personajeElegido);
	send(numeroSocket,(personajeElegido.c_str()),MAXDATOS,0);//le envio el personaje al servidor
}

void Cliente::cargarContenidos(){

	this->recibirPersonajes();
	this->recibirFondos();
	juegoCliente->cargarTexturas(personajesYfondos);//creo el mapa(nombre,textura)
}

void Cliente::recibirPersonajes(){
	for(int i=0; i <CANTIDAD_MAXIMA_JUGADORES;i++){
		recv(numeroSocket,buffer,MAXDATOS,0);
		const string &filePath = controladorJson->pathImagen(string(buffer));
		tuple <string, const string> tuplaPersonaje=make_tuple(string(buffer),filePath);
		personajesYfondos.push_back(tuplaPersonaje);
		send(numeroSocket,buffer,MAXDATOS,0);//le aviso que termine de trabajar
		cout<<buffer<<endl;
	}
}

void Cliente::recibirFondos(){
	int cantidadZindex = controladorJson->getZindexes().size();
	int zindexArecibir[cantidadZindex];
	recv(numeroSocket,zindexArecibir,sizeof(zindexArecibir),0);
	for(int i=0; i <cantidadZindex;i++){
		int zindex = zindexArecibir[i];
		const string &filePath = controladorJson->pathFondo(zindex);
		tuple <string, const string> tuplaFondo=make_tuple(to_string(zindex),filePath);
		personajesYfondos.push_back(tuplaFondo);
		cout<<zindex<<endl;
		cout<<filePath<<endl;
	}
}



void Cliente::recibirParaDibujar(){
	juegoCliente->graficos()->limpiar();
	char nombreTextura[MAXDATOS];
	for(int i = 0;i<5;i++){
		recv(numeroSocket,nombreTextura,MAXDATOS,0);
		send(numeroSocket,nombreTextura,MAXDATOS,0);
		int posiciones[8] ;
		recv(numeroSocket,posiciones,sizeof(posiciones),0);
		juegoCliente->dibujar(string(nombreTextura),posiciones);
		send(numeroSocket,nombreTextura,MAXDATOS,0);
	}
	juegoCliente->graficos()->render();

}








