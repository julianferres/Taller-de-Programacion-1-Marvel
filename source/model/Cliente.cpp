#include <Cliente.hpp>

using namespace std;

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;
extern ControladorSonido *controladorSonido;

struct infoCliente {
		Cliente *cliente;
		int ssocket;
 };
 typedef struct infoCliente iCliente;

Cliente::Cliente( char * direccionIP,int puerto){
	this->iniciarConexion(direccionIP,puerto);
	if(idCliente == -1){//significa que el server esta lleno, me cierro
		cout<<"El servidor esta lleno. Este cliente se va a desconectar."<<endl;
		controladorLogger->registrarEvento("ERROR", "Cliente::El server esta lleno, me desconecto.");
		this->partidallena();
		close(numeroSocket);
		return;
	}
	if(idCliente==0){//el server nunca se levanto
		cout<<"Servidor no encontrado."<<endl;
		close(numeroSocket);
		return;
	}
	cout<<"Conectado al servidor con exito."<<endl;
	struct timeval tv = {2, 0};
	setsockopt(numeroSocket, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *)&tv, sizeof(struct timeval));
	iCliente* args = (iCliente*) malloc(sizeof(infoCliente));
	args->cliente=this;
	juegoCliente = new JuegoCliente(idCliente);
	this->cargarContenidos();
	args->ssocket=numeroSocket;
	juegoCliente->cargarTexturas(personajesYfondos);
	this->recibirTitulos();

	pthread_t thread_enviar,thread_sonidos;
	pthread_create( &thread_enviar , NULL , &Cliente::enviarEventosWrapper ,(void*)args);
	pthread_create( &thread_sonidos , NULL , &Cliente::sonidosWrapper ,(void*)args);

	recibirParaDibujar();

	pthread_join(thread_enviar, NULL);
	pthread_join(thread_sonidos, NULL);
	cout<<"Conexion finalizada."<<endl;
	controladorLogger->registrarEvento("INFO", "Cliente::Conexion finalizada.");
	free(args);
	delete juegoCliente;
	close(numeroSocket);
}


void Cliente::cargarContenidos(){
	controladorSonido->correrCancionFondo("contents/sounds/Menu/menu.mp3",-1);
	int round = 3;
	vector<string> personajes = controladorJson->getNombresPersonajes();
	for(size_t i=0;i<personajes.size();i++){
		const string &filePath = controladorJson->pathImagen(personajes[i]);
		personajesYfondos.push_back(make_tuple(personajes[i],filePath));
		const string &buttonPath = controladorJson->pathBoton((personajes[i]));
		personajesYfondos.push_back(make_tuple(personajes[i]+"Boton",buttonPath));
		personajesYfondos.push_back(make_tuple(this->lifeBar->obtenerNombreBarra(personajes[i]), this->lifeBar->obtenerPath(personajes[i])));

	}
	vector<int> fondos = controladorJson->getZindexes(round);
	for (int r=1; r<4; r++){
		for(size_t i=0;i<fondos.size();i++){
			//TODO Setear numero de round
			const string &filePath = controladorJson->pathFondo(fondos[i],r);
			personajesYfondos.push_back(make_tuple(to_string(fondos[i])+ to_string(r),filePath));
		}
		const string &filePath = "contents/images/banner" + to_string(r) + ".png";
		personajesYfondos.push_back(make_tuple("Banner" + to_string(r),filePath));

	}

	personajesYfondos.push_back(make_tuple(string("Fondo"), string("contents/images/fondo.png")));
	personajesYfondos.push_back(make_tuple(string("ConnectionLost"), string("contents/images/connectionLost.png")));
}

void Cliente::iniciarConexion(char* direccionIP,int puerto){
	int  conexion;
	struct hostent *nodoServidor;
	struct sockaddr_in servidor;

	nodoServidor=gethostbyname(direccionIP);
	if(nodoServidor==NULL)
		controladorLogger->registrarEvento("ERROR", "Cliente::Error en la conexion");

	numeroSocket=socket(AF_INET, SOCK_STREAM, 0);
	servidor.sin_family=AF_INET;
	servidor.sin_port=htons(puerto);
	servidor.sin_addr=*((struct in_addr *)nodoServidor->h_addr);
	bzero(&(servidor.sin_zero),8);
	conexion=connect(numeroSocket,(struct sockaddr *)&servidor,sizeof(struct sockaddr));
	if(conexion==-1){
		controladorLogger->registrarEvento("ERROR", "Cliente::Error al conectar con el servidor");
		this->idCliente=0;
		return;
	}
	controladorLogger->registrarEvento("INFO", "Cliente::Conectado al servidor correctamente.");
	this->idCliente=this->sistemaEnvio.recibirEntero(numeroSocket);

}

void Cliente::partidallena(){
	bool close=false;
	SDL_Event eventoLLeno;
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO );
	SDL_Window* ventana;
	SDL_Renderer* rendererizar;
	SDL_CreateWindowAndRenderer(800,600, false, &ventana, &rendererizar);
	SDL_SetWindowTitle(ventana, "Marvel vs Capcom");
	SDL_Surface* fondo = IMG_Load("contents/images/partidaLLena.png");
	SDL_Texture * texture = SDL_CreateTextureFromSurface(rendererizar, fondo);
	while (!close){
		SDL_WaitEvent(&eventoLLeno);
		switch (eventoLLeno.type){
			case SDL_QUIT:
			close = true;
			break;
		}
		SDL_RenderCopy(rendererizar, texture, NULL, NULL);
		SDL_RenderPresent(rendererizar);
	}
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(fondo);
	SDL_DestroyRenderer(rendererizar);
	SDL_DestroyWindow(ventana);
	SDL_VideoQuit();
	SDL_Quit();
}

void Cliente::recibirParaDibujar(){
	SDL_Event evento;
	evento.type = SDL_MOUSEWHEEL;
	char textura[MAXDATOS];
	char sonido[MAXDATOS];
	int posiciones[8];
	SDL_RendererFlip flip;
	int size;
	int recibido;
	int equipos[4] = { 0, 1, 0, 1};
	bool equiposArmados = true;

	while(running){

		if(!enMenu && equiposArmados){
			equiposArmados = false;
			recv(numeroSocket, equipos, sizeof(equipos), MSG_WAITALL);
			juegoCliente->setearLados(equipos);
		}

		recibido = recv(numeroSocket,&size,sizeof(size),MSG_WAITALL);
		juegoCliente->graficos()->limpiar();
		if(recibido<0){
			if(conectado)
				cout<<"Conexion perdida con el servidor."<<endl;
			cout<<"Intentando reconectar con el servidor..."<<endl;
			juegoCliente->graficos()->dibujarImagen(juegoCliente->getTextura("ConnectionLost"), NULL, NULL, SDL_FLIP_NONE);
			juegoCliente->graficos()->render();
			conectado = false;
			continue;
		}
		if(recibido == 0){
			cout<<"El servidor se ha cerrado. Este cliente se va a desconectar."<<endl;
			running = false;
			return;
		}
		if(!conectado)
			cout<<"Reconectado con el servidor."<<endl;
		conectado = true;
		if(size==-1){
			enMenu=false;
			continue;
		}

		for(int i=0;i<size;i++){
			if(recv(numeroSocket,textura,MAXDATOS,MSG_WAITALL)<0) break;
			if(recv(numeroSocket,posiciones,sizeof(posiciones),MSG_WAITALL)<0) break;
			if(recv(numeroSocket,&flip,sizeof(flip),MSG_WAITALL)<0) break;
			//Personajes por arriba de las barras
			if(!enMenu && i == 3)
					juegoCliente->dibujarBarrasVida();
			juegoCliente->dibujar(string(textura),posiciones,flip);
		}
		if(!enMenu){
			for(int i=0;i<2;i++){
				recv(numeroSocket,sonido,MAXDATOS,MSG_WAITALL);
				if(sonido!="")
					controladorSonido->correrSonido(sonido, false);
			}
		}

		//Personajes por debajo de las barras
		/*if(!enMenu)
							juegoCliente->dibujarBarrasVida();*/

		juegoCliente->graficos()->render();
		send(numeroSocket,&evento,sizeof(evento),0);//heartbeat
	}

}

void *Cliente::enviarEventosWrapper(void* arg){
	iCliente* argumentos = (iCliente*) arg;
	((Cliente *)argumentos->cliente)->enviarEventos(argumentos->ssocket);
	return NULL;
}

void *Cliente::sonidosWrapper(void* arg){
	iCliente* argumentos = (iCliente*) arg;
	((Cliente *)argumentos->cliente)->manejarSonidos();
	return NULL;
}

void Cliente::manejarSonidos(){
	vector<const char* > songs;
	songs.push_back("contents/sounds/Announcer voice/seleheroes.wav");
	songs.push_back("contents/sounds/Announcer voice/ready1.wav");
	songs.push_back("contents/sounds/Announcer voice/engage.wav");
	songs.push_back("contents/sounds/Battle/Captain America Theme.mp3");
	songs.push_back("contents/sounds/Battle/Hulk Theme.mp3");
	songs.push_back("contents/sounds/Battle/Spider Mans Theme.mp3");
	songs.push_back("contents/sounds/Battle/Mega mans Theme.mp3");
	songs.push_back("contents/sounds/Battle/War machines Theme.mp3");
	controladorSonido->correrSonido(songs[0],false);
	while(enMenu){}
	controladorSonido->finalizarCancion();
	controladorSonido->correrSonido(songs[1],true);
	controladorSonido->correrSonido(songs[2],true);
	srand(time(NULL));
	int random = (rand()%(songs.size()-1-3)) +3;
	controladorSonido->correrCancionFondo(songs[random], -1);
	while(running){}

}

void Cliente::enviarEventos(int socket){
	SDL_Event evento;
	while(running){
		while(SDL_PollEvent(&evento)){
			if(!conectado) continue;
			if(evento.type==SDL_QUIT){
				running=false;
				return;
			}
			if(enMenu){
				if(evento.type==SDL_MOUSEBUTTONDOWN||evento.type==SDL_MOUSEBUTTONUP
					||evento.type== SDL_MOUSEMOTION )
					send(socket,&evento,sizeof(evento),0);
			}
			else{
				if(evento.type==SDL_KEYDOWN || evento.type==SDL_KEYUP )
					send(socket,&evento,sizeof(evento),0);
			}
			juegoCliente->handleEvents(evento);
		}
	}
}

void Cliente::recibirTitulos(){
	vector<tuple<string,string,int,string,int ,int ,int >>titulos;
	char nombre[MAXDATOS];
	char path[MAXDATOS];
	int size;
	char descripcion[MAXDATOS];
	int r,g,b;
	int cantidadTitulos;
	recv(numeroSocket,&cantidadTitulos,sizeof(cantidadTitulos),MSG_WAITALL);
	for(size_t i=0;i<cantidadTitulos;i++){
		recv(numeroSocket,nombre,MAXDATOS,MSG_WAITALL);
		recv(numeroSocket,path,MAXDATOS,MSG_WAITALL);
		recv(numeroSocket,&size,sizeof(size),MSG_WAITALL);
		recv(numeroSocket,descripcion,MAXDATOS,MSG_WAITALL);
		recv(numeroSocket,&r,sizeof(r),MSG_WAITALL);
		recv(numeroSocket,&g,sizeof(g),MSG_WAITALL);
		recv(numeroSocket,&b,sizeof(b),MSG_WAITALL);
		titulos.push_back(make_tuple(string(nombre),string(path),size,string(descripcion),r,g,b));
	}
	this->juegoCliente->cargarTitulosMenu(titulos);
}
