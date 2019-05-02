#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>
#include <iostream>
#include <Cliente.hpp>
#include <GameMenu.hpp>
#include <JuegoCliente.hpp>
#include <ControladorLogger.hpp>
#include <string>
#include <tuple>
#define CANTIDAD_MAXIMA_JUGADORES 4
using namespace std;

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;

#define PUERTO 5001
#define NO_TODOS_CLIENTES_CONECTADOS -1
#define MAXDATOS 256

Cliente::Cliente( char * direccionIP){
	int socket1, socketControl, numeroBytes,conexion, conexionControl;
	char buffer[MAXDATOS];
	struct hostent *nodoServidor;
	struct sockaddr_in servidor;

	nodoServidor=gethostbyname(direccionIP);
	if(nodoServidor==NULL)
		cout<<"error en la direccion"<<endl;

	socket1=socket(AF_INET, SOCK_STREAM, 0);
	servidor.sin_family=AF_INET;
	servidor.sin_port=htons(PUERTO);
	servidor.sin_addr=*((struct in_addr *)nodoServidor->h_addr);
	bzero(&(servidor.sin_zero),8);
	conexion=connect(socket1,(struct sockaddr *)&servidor,sizeof(struct sockaddr));
	if(conexion==-1)
		cout<<"error al conectar"<<endl;

	JuegoCliente *juegoCliente = new JuegoCliente();
	int idClienteRecibido;
	int idCliente;


	recv(socket1,&idClienteRecibido,sizeof(int),0);//se conectaron todos los jugadores

	idCliente= ntohl(idClienteRecibido);
	cout<<"Soy el cliente idCliente: "<<idCliente << endl;

	juegoCliente->iniciarGraficos();
	puts("inicie los graficos");
	GameMenu *menu = new GameMenu(*juegoCliente->graficos(),idCliente);//inicio el menu

	//Seleccionamos el personaje y lo enviamos al server
	string personajeElegido = menu->personajeSeleccionado();//ya seleccione mi personaje
	send(socket1,(personajeElegido.c_str()),sizeof(personajeElegido),0);//le envio el personaje al servidor


	//Aca llegan los jugadores seleccionados por todos
	vector<tuple<string, const string>> personajes;
	for(int i=0; i <CANTIDAD_MAXIMA_JUGADORES;i++){
		recv(socket1,buffer,256,0);
		const string &filePath = controladorJson->pathImagen(string(buffer));
		tuple <string, const string> tuplaPersonaje=make_tuple(string(buffer),filePath);
		personajes.push_back(tuplaPersonaje);
		cout << get<0>(personajes[i]) << "," << get<1>(personajes[i]) << endl;

	}

	cout<< personajes.size();
	juegoCliente->cargarTexturasJugadores(personajes);//creo el mapa



	while(true){
		cin>>buffer;
		send(socket1,buffer,MAXDATOS,0);
		recv(socket1,buffer,MAXDATOS,0);
		cout<<buffer<<endl;


	}



	/*while(true){
		enviarEventos  send(socketCliente, evento,sizeof(evento),0);
		 * recibir vista recv(socket1,buffer,MAXDATOS,0);
		 * dibujar


	}*/


	close(socket1);
}
