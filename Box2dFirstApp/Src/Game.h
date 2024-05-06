#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include <list>
#include "bloque.h"

using namespace sf;
class Game
{
private:
	// Propiedades de la ventana
	int alto;
	int ancho;
	Color clearColor;

	// Objetos de box2d
	
	SFMLRenderer *debugRender;

	//tiempo de frame
	float frameTime;
	int fps;

	// Cuerpo de box2d
	b2Body* controlBody;
	b2Body* wallBody;
	b2Body* cañonBody;
	Bloquee* _cañon;
	bool circlecreated;
	b2Vec2 fuerza;
	b2MassData massData;
	int i;
	int j;

public:
    b2World *phyWorld;RenderWindow *wnd;
	// Constructores, destructores e inicializadores
	Game(int ancho, int alto,std::string titulo);
	void CheckCollitions();
	void CreateEnemy(int x, int y);
	~Game(void);
	void InitPhysics();

	// Main game loop
	void Loop();
	void DrawGame();
	void UpdatePhysics();
	void DoEvents();
	void SetZoom();
	void Cañon();
	void DrawSprite();
	void ActualizarPosicionBomba();
};

