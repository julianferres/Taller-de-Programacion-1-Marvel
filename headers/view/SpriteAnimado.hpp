/*/*
 * SpriteAnimado.hpp
 *
 *  Created on: Mar 24, 2019
 *      Author: luupesado
 */

#ifndef HEADERS_VIEW_SPRITEANIMADO_HPP_
#define HEADERS_VIEW_SPRITEANIMADO_HPP_

#include <Sprite.hpp>
#include <map>
#include <string>
#include <vector>
#include <ConfiguracionGlobal.hpp>

class ControladorGrafico;

class SpriteAnimado: public Sprite{
public:
	//SpriteAnimado();
	//SpriteAnimado(ControladorGrafico &graficos, const std::string &filePath, int x0, int y0, int ancho, int alto,
	//		float posX, float posY, float timeToUpdate);

	/*void iniciarAnimacion
	 * Inicia la animacion que nos pasan si no empezo todavia
	 */
	void iniciarAnimacion(std::string animacion, bool unica = false);
	/* void update
	 * Updates the animation sprite (timer)
	 */
	void update(int tiempoTrancurrido);
	/*void dibujar
	 * Dibija los Sprites en la pantalla
	 */
	void dibujar(ControladorGrafico &graficos, int x, int y);

protected:
	bool _animacionActualUnica;
	double _timeToUpdate;

	std::string _animacionActual;

	/*void agregarAnimacion
	 * Agrega una animacion al mapa de animaciones de un Sprite
	 */
	void agregarAnimacion(int frames, int x, int y, std::string nombre, int ancho, int alto, Vector2 offset);

	/* void reiniciarAnimacion
	 * Reinicia todas la animaciones asociadas a un sprite
	 */
	void reiniciarAnimacion();

	/*void pararAnimacion
	 * frena la animacion que est[a corriendo
	 */
	void pararAnimacion();

	/* esVisible
	 * cambia la visibilidad del sprite
	 */
	void esVisible( bool visible);

	/* void animacionFinalizada
	 * Logica luego de que finaliza una animacion
	 */
	virtual void animacionFinalizada(std::string _animacionActual)=0;

	/*void configurarAnimaciones
	 * Funcion necesaria para configurar todas las animaciones de un Spprite
	 */
	virtual void configurarAnimaciones() = 0;


private:
	std::map<std::string, std::vector<SDL_Rect> > _animaciones;
	std::map<std::string, Vector2> _offsets;

	int _frameIndex;
	double tiempoTrancurrido;
	bool _visible;
};




#endif
