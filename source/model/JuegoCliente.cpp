#include <JuegoCliente.hpp>
JuegoCliente::JuegoCliente(){
	SDL_Init(0);
	SDL_VideoInit(NULL);
	SDL_InitSubSystem(SDL_INIT_TIMER);
	this->graficos=new ControladorGrafico();
	this->teclado = new ControladorTeclado();
	this->isRunning=true;
	this->gameloop();
}
JuegoCliente::~JuegoCliente(){
	delete graficos;
	delete teclado;
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	SDL_VideoQuit();
	SDL_QuitSubSystem(SDL_INIT_TIMER);
	SDL_Quit();
}
void JuegoCliente::gameloop(){
	while(this->isRunning){
		this->teclear();
	}
}

void JuegoCliente::teclear(){
	SDL_Event evento;
	teclado->reiniciar();

	while(SDL_PollEvent(&evento)){
		if (evento.type == SDL_QUIT   ){
			isRunning = false;
			break;
		}

		if (evento.window.event == SDL_WINDOWEVENT_RESIZED){
			graficos->maximizarVentana(evento.window.data1, evento.window.data2);
		}

		 switch( evento.type ){
		 	 case SDL_KEYDOWN:
		 		 this->teclado->eventoPresionarTecla(evento);
		 		 break;
		 	 case SDL_KEYUP:
		 		 this->teclado->eventoSoltarTecla(evento);
		 		 break;
		 }
	}

	if(teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_D)){
		cout<<"tecla: "<<SDL_SCANCODE_D<<endl;
	}

	if(teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_A)){
		cout<<"tecla: "<<SDL_SCANCODE_A<<endl;
	}

	if(teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_W)){
		cout<<"tecla: "<<SDL_SCANCODE_W<<endl;
	}

	if(teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_S)){
		cout<<"tecla: "<<SDL_SCANCODE_S<<endl;
	}

	if(teclado->sePresionoUnaTecla(SDL_SCANCODE_E) ){
		cout<<"tecla: "<<SDL_SCANCODE_E<<endl;
	}
	if(teclado->sePresionoUnaTecla(SDL_SCANCODE_F11)){
		this->graficos->cambiarPantallaCompleta();
	}

	if(teclado->sePresionoUnaTecla(SDL_SCANCODE_ESCAPE)){
		cout<<"tecla: SALIDA"<<endl;
		isRunning=false;
	}
}

