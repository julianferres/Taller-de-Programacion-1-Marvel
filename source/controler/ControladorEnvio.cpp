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

void ControladorEnvio::enviarArrayEnteros(struct vector4 datos,int socket){
	void* buffer=malloc(16);
	memcpy(buffer,&(datos.x),4);
	memcpy(buffer+4,&(datos.y),4);
	memcpy(buffer+8,&(datos.w),4);
	memcpy(buffer+12,&(datos.h),4);
	send(socket,buffer,16,0);
	free(buffer);

}

struct vector4 ControladorEnvio::recibirArrayEnteros(int socket){
	void* buffer=malloc(16);
	recv(socket,buffer,16,0);
	vector4Entero vector;
	memcpy(&(vector.x), buffer, 4);
	memcpy(&(vector.y), buffer+4, 4);
	memcpy(&(vector.w), buffer+8, 4);
	memcpy(&(vector.h), buffer+12, 4);
	return vector;
	free(buffer);
}
