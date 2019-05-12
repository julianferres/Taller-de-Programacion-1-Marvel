#ifndef HEADERS_MODEL_JUEGOCLIENTE_HPP_
#define HEADERS_MODEL_JUEGOCLIENTE_HPP_
#include <ControladorGrafico.hpp>
#include <ControladorTeclado.hpp>
#include <string>
#include <iostream>
using namespace std;
class JuegoCliente{
	public:
		JuegoCliente();
		~JuegoCliente();
		void gameloop();
		void teclear();
	private:
		ControladorGrafico *graficos;
		ControladorTeclado *teclado;
		bool isRunning;
};
#endif
