#include <Cliente.hpp>
#include <ControladorEnvio.hpp>
#include <GameMenu.hpp>
#include <ControladorGrafico.hpp>
using namespace std;

#define PUERTO 5001

#define MAXDATOS 256

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;


Cliente::Cliente( char * direccionIP){
	controladorJson->leerArchivo("");
	this->sisEnvio=ControladorEnvio();
	int socketConexion,numeroBytes,conexion;
	struct hostent *nodoServidor;
	struct sockaddr_in servidor;

	nodoServidor=gethostbyname(direccionIP);
	if(nodoServidor==NULL){
		cout<<"error en la direccion"<<endl;
	}

	socketConexion=socket(AF_INET, SOCK_STREAM, 0);
	servidor.sin_family=AF_INET;
	servidor.sin_port=htons(PUERTO);
	servidor.sin_addr=*((struct in_addr *)nodoServidor->h_addr);
	bzero(&(servidor.sin_zero),8);

	conexion=connect(socketConexion,(struct sockaddr *)&servidor,sizeof(struct sockaddr));
	if(conexion<0){
	cout<<"error al conectar"<<endl;
	};
	//Recivo cadena
	string mensaje=this->sisEnvio.recibirString(socketConexion);
	std::cout<<"mensaje: "<<mensaje<<endl;
	//Recivo id
	int cliente=this->sisEnvio.recibirEntero(socketConexion);
	std::cout<<"tengo id: "<<cliente<<endl;
	this->idCliente=cliente;
	std::cout<<"tengo guardado id: "<<this->idCliente<<endl;
	//=========
	int abrirMenu=this->sisEnvio.recibirEntero(socketConexion);
	if(abrirMenu==1){
		SDL_Init(0);
		SDL_VideoInit(NULL);
		SDL_InitSubSystem(SDL_INIT_TIMER);
		ControladorGrafico *graficos = new ControladorGrafico();
		GameMenu *menu = new GameMenu(*graficos,this->idCliente);
		SDL_VideoQuit();
		SDL_QuitSubSystem(SDL_INIT_TIMER);
		SDL_Quit();
		std:: cout<<"Personaje Elejido: "<<menu->personajeElegidoPorCliente()<<endl;
		delete menu;
		delete graficos;
	}

	string saludo=this->sisEnvio.recibirString(socketConexion);
	cout<<"mensaje: "<<saludo<<endl;

	//recibo entero
	vectorEntero prueba=this->sisEnvio.recibirArrayEnteros(socketConexion);
	cout<<"nuemro x: "<<prueba.x<<endl;
	//fin del recibo entero;


	void *bufer;
	recv(socketConexion,bufer,20,0); //esto hace que no termine el cliente

	close(socketConexion);
}
