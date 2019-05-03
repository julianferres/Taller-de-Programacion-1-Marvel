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
		//enviarEventos  send(socketCliente, evento,sizeof(evento),0);
		 // recibir vista recv(socket1,buffer,MAXDATOS,0);
		 // dibujar
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

	int idClienteRecibido;
	recv(numeroSocket,&idClienteRecibido,sizeof(int),0);//se conectaron todos los jugadores
	idCliente= ntohl(idClienteRecibido);
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
	char buffer[MAXDATOS];
	vector<tuple<string, const string>> personajesYfondos;
	for(int i=0; i <CANTIDAD_MAXIMA_JUGADORES;i++){//Aca llegan los jugadores seleccionados por todos
		recv(numeroSocket,buffer,MAXDATOS,0);
		const string &filePath = controladorJson->pathImagen(string(buffer));
		tuple <string, const string> tuplaPersonaje=make_tuple(string(buffer),filePath);
		personajesYfondos.push_back(tuplaPersonaje);
		send(numeroSocket,buffer,MAXDATOS,0);//le aviso que termine de trabajar
	}

	int zindex;
	int cantidadZindex = controladorJson->getZindexes().size();
	for(int i=0; i <cantidadZindex;i++){
		recv(numeroSocket,&zindex,sizeof(zindex),0);
		const string &filePath = controladorJson->pathFondo(zindex);
		tuple <string, const string> tuplaFondo=make_tuple(to_string(zindex),filePath);
		personajesYfondos.push_back(tuplaFondo);
		send(numeroSocket,buffer,MAXDATOS,0);//le aviso que termine de trabajar
	}

	juegoCliente->cargarTexturas(personajesYfondos);//creo el mapa(nombre,textura)

	/*ejemplo de como deberia dibujar el cliente
	SDL_Rect rectanguloOrigen = {0,16,100,120};
	SDL_Rect rectanguloOrigen1 = {0,0,800,480};
	SDL_Rect rectanguloDestino = {50,300,200,320};
	juegoCliente->graficos()->limpiar();
	juegoCliente->graficos()->dibujarImagen(juegoCliente->getTextura("1"), &rectanguloOrigen1, NULL, SDL_FLIP_NONE);
	juegoCliente->graficos()->dibujarImagen(juegoCliente->getTextura("CapitanAmerica"), &rectanguloOrigen, &rectanguloDestino, SDL_FLIP_NONE);
	juegoCliente->graficos()->render();*/
}
