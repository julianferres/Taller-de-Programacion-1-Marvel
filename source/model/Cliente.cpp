#include <Cliente.hpp>
#include <ControladorEnvio.hpp>
using namespace std;

#define PUERTO 5001

#define MAXDATOS 256

Cliente::Cliente( char * direccionIP){
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
	//Recivo id
	int cliente=this->sisEnvio.recibirEntero(socketConexion);
	std::cout<<"tengo id: "<<cliente<<endl;
	this->idCliente=cliente;
	std::cout<<"tengo guardado id: "<<this->idCliente<<endl;
	//Recivo cadena
	string mensaje=this->sisEnvio.recibirString(socketConexion);
	std::cout<<"mensaje: "<<mensaje<<endl;

	void *bufer;
	recv(socketConexion,bufer,20,0); //esto hace que no termine el cliente

	close(socketConexion);
}
