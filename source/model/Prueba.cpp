/*
 * Servidor
 *
 *
 *
 *

this->teclado = new ControladorTeclado();
this-> parallax = new Parallax(*graficos);//cuando el cliente va a dibujar, se lo paso por parametro
new Jugador(*graficos,controladorJson->jugador1Personaje(0), controladorJson->jugador1Personaje(1),controladorJson->getPosicionXInicialJugador1(),SDL_FLIP_NONE, false);//cuando terminaron de elegir, ahi lee el json
//por ahora los guarda en un arreglo, pero despues se va a usar una clase equipo
//despues de que todos los jugadores eligieron su personaje en el menu, corro el game loop
//el servidor le envia al cliente el filePath de las texturas una sola vez, luego de elegir los personajes
this->colaEventos = new ColaEventos();
enviar Vista al cliente
 * cargo una cola del tipo
 * int identificadorTextura, SDL_Rect* rectanguloOrigen, SDL_Rect* rectanguloDestino, SDL_RendererFlip flip
 * la calculo con el metodo Juego::dibujar y la envio
 *
 *
 *



 * Cliente
 *
 *
 *


SDL_Init(0);
SDL_VideoInit(NULL);
SDL_InitSubSystem(SDL_INIT_TIMER);
this->graficos = new ControladorGrafico();
this->startGameMenu();//recordar que despues hay que modificarlo para elegir una sola vez y salir
//el handleEvent va del lado del servidor, que recibe el evento del mouse
//recibo los filePath, creo las texturas, y las guardo
//SDL_CreateTextureFromSurface(graficos.getRenderer(),graficos.cargarImagen(filePath));
//if(filePath.good) path = sinSprite.png


while(SDL_PollEvent(&evento)){
	enviar al servidor , voy poniendo los eventos en una cola propia del cliente
}//en un hilo distinto al de dibujar, dentro de un while true
Para dibujar, recibo una cola del tipo
 *int identificadorTextura, SDL_Rect* rectanguloOrigen, SDL_Rect* rectanguloDestino, SDL_RendererFlip flip
 *graficos->limpiar();
 *while cola
 *			graficos.dibujarImagen(lo que desencole);
 *graficos->render();
 *


Escenas
 * 1 EL server envia las cosas del menu que tiene que dibujar el cliente
 * 2 El server envia los paths a los clientes
 * 3 El server envia los rectangulos a los clientes
 *
 */
