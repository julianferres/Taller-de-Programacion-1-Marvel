#ifndef CONFIGURACIONGLOBAL_HPP_
#define CONFIGURACIONGLOBAL_HPP_

enum Direccion{
	DERECHA,
	IZQUIERDA,
	ARRIBA,
	ABAJO
};
namespace constantes_personajes{
	const float VELOCIDAD = 0.2f;
}
namespace constantes_graficas{
	const int FPS = 50;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

namespace globals{
	const float ESCALA_SPRITE = 2.0f;
}

struct Vector2 {
	int x, y;
	Vector2(): x(0),y(0){}
	Vector2( int x, int y) : x(x),y(y){}
	Vector2 cero(){
		return Vector2(0,0);
	}
};



#endif
