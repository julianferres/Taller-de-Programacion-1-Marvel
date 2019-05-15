#include <ControladorEnvio.hpp>
ControladorEnvio::ControladorEnvio(){

}
void ControladorEnvio::enviarEntero(int entero,int socket){
	void * buffer=malloc(4);
	memcpy(buffer,&(entero),4);
	send(socket,buffer,4,0);
	free(buffer);
}
void ControladorEnvio::enviarString(string cadena,int socket){
	int largo=cadena.size();
	void *buffer=malloc(4);
	memcpy(buffer,&(largo), 4);
	send(socket,buffer,4,0);
	char mensajeEnviar[cadena.size()+1];
	strcpy(mensajeEnviar,cadena.c_str());
	send(socket,mensajeEnviar,cadena.size()+1, 0);
	free(buffer);
}

int ControladorEnvio::recibirEntero(int socket){
	int entero;
	void * buffer =malloc(4);
	recv(socket,buffer,4,0);
	memcpy(&entero,buffer,4);
	return entero;
	free(buffer);
}

string ControladorEnvio::recibirString(int socket){
	void *buffer=malloc(4);
	recv(socket,buffer,4,0);
	int largo;
	memcpy(&largo,buffer,4);
	char bufer[largo+1];
	recv(socket,bufer,largo+1,0);
	string mensaje(bufer);
	return mensaje;
	free(buffer);
}

void ControladorEnvio::enviarArrayEnteros(struct vector8 datos,int socket){
	void* buffer=malloc(16);
	memcpy(buffer,&(datos.x),4);
	memcpy(buffer+4,&(datos.y),4);
	memcpy(buffer+8,&(datos.w),4);
	memcpy(buffer+12,&(datos.h),4);
	send(socket,buffer,16,0);
	free(buffer);

}

struct vector8 ControladorEnvio::recibirArrayEnteros(int socket){
	void* buffer=malloc(16);
	recv(socket,buffer,16,0);
	vector8Entero vector;
	memcpy(&(vector.x), buffer, 4);
	memcpy(&(vector.y), buffer+4, 4);
	memcpy(&(vector.w), buffer+8, 4);
	memcpy(&(vector.h), buffer+12, 4);
	return vector;
	free(buffer);
}
void ControladorEnvio::enviarEvento(SDL_Event evento,int socket){
	void * buffer=malloc(sizeof(SDL_Event));
	memcpy(buffer,&(evento),sizeof(SDL_Event));
	send(socket,buffer,sizeof(SDL_Event),0);
	free(buffer);
}
SDL_Event ControladorEnvio::recibirEvento(int socket){
	SDL_Event evento;
	void * buffer =malloc(sizeof(SDL_Event));
	recv(socket,buffer,sizeof(SDL_Event),0);
	memcpy(&evento,buffer,sizeof(SDL_Event));
	return evento;
	free(buffer);
}

