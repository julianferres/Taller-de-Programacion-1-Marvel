#include <Jugador.hpp>
#include <ControladorLogger.hpp>
#include <Juego.hpp>
#include <SpriteAnimado.hpp>

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;

Juego::Juego(){
	int posicionMoverFondoIzq = controladorJson->anchoVentana() * 1/4;
	int posicionMoverFondoDer = controladorJson->anchoVentana() * 3/4;

	this->isRunning=true;
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop(posicionMoverFondoIzq, posicionMoverFondoDer);
}

Juego::~Juego()
{}

void Juego::gameLoop(int posicionMoverFondoIzq, int posicionMoverFondoDer){
	ControladorGrafico graficos;
	ControladorTeclado teclado;
	SDL_Event evento;
	/*SpriteAnimado *pruebaMovimiento;

	pruebaMovimiento=new SpriteAnimado(graficos,"contents/images/CaptainAmericaSprites.png");
	pruebaMovimiento->agregarAnimacion(6,0,286,"caminarDerecha",101,126);
	pruebaMovimiento->agregarAnimacion(9,0,19,"quieto",90,120);
	pruebaMovimiento->iniciarAnimacion("caminarDerecha");*/

	this->dibujarFondo(graficos);
	this->jugador1 = new Jugador(graficos,"CapitanAmerica", "Spiderman");
	this->jugador2 = new Jugador(graficos,"Spiderman2", "CapitanAmerica2");

	while (isRunning){
		startTime = SDL_GetTicks();
		this->teclear(evento,teclado, posicionMoverFondoIzq, posicionMoverFondoDer);
		this->dibujar(graficos);
		if(SDL_GetTicks() - startTime < MAX_FRAME_TIME)
			SDL_Delay( MAX_FRAME_TIME - SDL_GetTicks() +startTime );

	}

}
void Juego::dibujarFondo(ControladorGrafico &graficos){
	this-> parallax = new Parallax(graficos);
	if(this->parallax == NULL)
		controladorLogger->registrarEvento("ERROR", "No se pudo cargar el parallax");
	else
		controladorLogger->registrarEvento("DEBUG", "Se cargo correctamente el parallax");
}

void Juego::dibujar(ControladorGrafico &grafico){
	grafico.limpiar();
	grafico.dibujarImagen(parallax->Backgroundz1(), parallax->Camaraz1(), NULL);
	grafico.dibujarImagen(parallax->Backgroundz2(), parallax->Camaraz2(), NULL);
	grafico.dibujarImagen(parallax->Backgroundz3(), parallax->Camaraz3() , NULL);
	this->jugador1->personajeActualDibujar(grafico);
	this->jugador2->personajeActualDibujar(grafico);
	/*pruebaMovimiento->dibujar(grafico,200,400);
	pruebaMovimiento->update(10);*/
	grafico.render();
}

void Juego::teclear(SDL_Event evento,ControladorTeclado teclado, int posicionMoverFondoIzq, int posicionMoverFondoDer){
	while(SDL_PollEvent(&evento)){
		switch(evento.type){
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				switch(evento.key.keysym.sym){
					case SDLK_RIGHT:
						this->jugador1->personajeActualMoverDerecha();
						//if(jugador1->obtenerPosicionXPersonaje() > posicionMoverFondoDer)
						if(jugador1->obtenerPosicionXPersonaje(true) > posicionMoverFondoDer) this->parallax->MoverCamaraDerecha();
						controladorLogger->registrarEvento("DEBUG", "Jugador 1 a la derecha");
						break;
					case SDLK_LEFT:
						this->jugador1->personajeActualMoverIzquierda();
						if (jugador1->obtenerPosicionXPersonaje(false) < posicionMoverFondoIzq) this->parallax->MoverCamaraIzquierda();
						controladorLogger->registrarEvento("DEBUG", "Jugador 1 a la izquierda");
						break;
					case SDLK_l:
						this->jugador1->cambiarPersonaje();
						controladorLogger->registrarEvento("DEBUG", "Cambio de personaje");
						break;
					case SDLK_UP:
						this->jugador1->personajeActualSaltar();
						break;
					case SDLK_ESCAPE:
						isRunning = false;
						break;
				}
				break;
			default:
				break;
		}
	}
}
