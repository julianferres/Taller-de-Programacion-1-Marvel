#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include <iostream>
#include <string.h>
#include <Servidor.hpp>
#include <tuple>

using namespace std;

#define PUERTO 5001
#define CANTIDADDECONEXIONES 5
#define CANTIDAD_ESPERADA_CLIENTES 3

Servidor::Servidor(){

	int socket1, enlace;
	struct sockaddr_in servidor; // informacion de la direccion del servidor

	unsigned int tamanioCliente;
	struct sockaddr_in clientes[CANTIDAD_ESPERADA_CLIENTES];
	tuple<int,int> sockets[CANTIDAD_ESPERADA_CLIENTES];
	int cantidadClientesConectados = 0;


	socket1=socket(AF_INET,SOCK_STREAM,0);//AF_INET IPV4,SOCK_STREAM TCP
	if (socket1==-1){
		cout<<"error en el socket"<<endl;
	};
	servidor.sin_family=AF_INET;
	servidor.sin_port=htons(PUERTO); //definimos el puerto
	servidor.sin_addr.s_addr=INADDR_ANY;// ponemos nuestra ip
	bzero(&(servidor.sin_zero),8); // una cadena de ceros

	enlace=bind(socket1,(struct sockaddr*)&servidor,sizeof(struct sockaddr));
	if(enlace==-1){
		cout<<"error en el enlace"<<endl;
	};
	cout << "se levanto el servidor" << endl;
	listen(socket1,CANTIDADDECONEXIONES);




	while(true){
		struct sockaddr_in cliente;
		clientes[cantidadClientesConectados] = cliente;
		tamanioCliente=sizeof(cliente);
		int socketCliente=accept(socket1,(struct sockaddr*)&cliente,&tamanioCliente);
		if(socketCliente==-1){
			cout<<"error al aceptar al cliente"<<endl;
		}
		int socketClienteControl = accept(socket1,(struct sockaddr*)&cliente,&tamanioCliente);
		if(socketCliente==-1){
			cout<<"error al aceptar al control del cliente"<<endl;
		}
		else{

			sockets[cantidadClientesConectados] = (make_tuple(socketCliente, socketClienteControl));
			cout<<"se conecto alguien"<<endl;
			cantidadClientesConectados ++;
			if(cantidadClientesConectados == CANTIDAD_ESPERADA_CLIENTES){
				cout << "Se conectaron todos los clientes esperados" <<endl;
				//¡iniciar juego!
				break;
			}
		}
			/*recibir eventos recv(socket1,evento,sizeof(evento),0);
			actualizar
			enviarVista send(socket2,mensaje,256,0);  cada 1/60 seg*/
		}

		/*while(true){
		 * enviar señal de control a cada socket de control, para que sepan si el servidor esta funcionando
		 *
		 */
		for(int i = 0; i < CANTIDAD_ESPERADA_CLIENTES; i++){
			close(get<0>(sockets[i]));
			close(get<1>(sockets[i]));
		}
}




