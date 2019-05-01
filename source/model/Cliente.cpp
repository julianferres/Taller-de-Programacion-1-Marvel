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
	cout<<"Soy el cliente idCliente: "<<idCliente;

	juegoCliente->iniciarGraficos();
	puts("inicie los graficos");
	GameMenu *menu = new GameMenu(*juegoCliente->graficos(),idCliente);//inicio el menu
	puts("menu");
	string personajeElegido = menu->personajeSeleccionado();//ya seleccione mi personaje
	send(socket1,&personajeElegido,sizeof(personajeElegido),0);//le envio el personaje al servidor
	vector<tuple<string, const string>> personajes;
	recv(socket1,&personajes,sizeof(personajes),0);
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
