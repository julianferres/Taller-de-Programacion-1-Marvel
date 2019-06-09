#include <LifeBar.hpp>

LifeBar::LifeBar(){
	lados.insert({"CapitanAmerica", 0});
	lados.insert({"Hulk", 0});
	lados.insert({"Spiderman", 1});
	lados.insert({"Venom", 1});

	alturas.insert({"CapitanAmerica", 0});
	alturas.insert({"Hulk", 1});
	alturas.insert({"Spiderman", 0});
	alturas.insert({"Venom", 1});

	companieros.insert({"CapitanAmerica", "Hulk"});
	companieros.insert({"Hulk", "CapitanAmerica"});
	companieros.insert({"Spiderman", "Venom"});
	companieros.insert({"Venom", "Spiderman"});
}

string LifeBar::obtenerPath(string nombrePersonaje){
	return ("contents/images/"+nombrePersonaje+"-lb.png");
}

string LifeBar::obtenerNombreBarra(string nombrePersonaje){
	return (nombrePersonaje+"-lb");
}

int LifeBar::obtenerAnchoBarra(string nombrePersonaje){
	if(alturas[nombrePersonaje] == 0) return anchoBarraArriba;
	return anchoBarraArriba * 4 / 6;
}

int LifeBar::obtenerLargoBarra(string nombrePersonaje, int anchoVentana){
	if(alturas[nombrePersonaje] == 0) return (anchoVentana / 3);
	return (anchoVentana / 4);
}

int LifeBar::obtenerPosicionHorizontal(string nombrePersonaje, int anchoVentana){
	if(lados[nombrePersonaje] == 0) return posicionHorizontalIzquierda;
	return anchoVentana - obtenerLargoBarra(nombrePersonaje, anchoVentana) - posicionHorizontalIzquierda;
}

int LifeBar::obtenerPosicionVertical(string nombrePersonaje){
	if(alturas[nombrePersonaje] == 0) return posicionVerticalArriba;
	return posicionVerticalAbajo;
}

SDL_RendererFlip LifeBar::obtenerFlipBarra(string nombrePersonaje){
	if(lados[nombrePersonaje] == 0) return SDL_FLIP_HORIZONTAL;
	return SDL_FLIP_NONE;
}



int LifeBar::obtenerAnchoFondoVida(string nombrePersonaje){
	if(alturas[nombrePersonaje] == 0) return anchoFondoVidaArriba;
	return anchoFondoVidaArriba * 4 / 6;
}

int LifeBar::obtenerLargoFondoVida(string nombrePersonaje){
	if(alturas[nombrePersonaje] == 0) return largoFondoVida;
	return (largoFondoVida * 3 / 4);
}

int LifeBar::obtenerPosicionHorizontalFondoVida(string nombrePersonaje, int anchoVentana){
	if(lados[nombrePersonaje] == 0) return posicionHorizontalVidaIzq;
	return anchoVentana - obtenerLargoFondoVida(nombrePersonaje) - posicionHorizontalVidaIzq;
}

int LifeBar::obtenerPosicionVerticalFondoVida(string nombrePersonaje){
	if(alturas[nombrePersonaje] == 0) return posicionVerticalVidaArriba;
	return posicionVerticalVidaAbajo;
}

void LifeBar::actualizarPersonajesActuales(string nombrePersonaje){
	if(alturas[nombrePersonaje] == 1) {
		alturas[nombrePersonaje] = 0;
		alturas[companieros[nombrePersonaje]] = 1;
	}

}
