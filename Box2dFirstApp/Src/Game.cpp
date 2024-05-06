#include "Game.h"
#include "Box2DHelper.h"
#include <iostream>
#include "bloque.h"

using namespace sf;
using namespace std;


Game::Game(int ancho, int alto, std::string titulo)
{
	wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
	wnd->setVisible(true);
	fps = 60;
	wnd->setFramerateLimit(fps);
	frameTime = 1.0f / fps;
	SetZoom();
	InitPhysics();
	i = 400; j = -400;
	circlecreated = false;
	
    _cañon = new Bloquee(phyWorld, wnd);
	
}



void Game::Loop()
{
	while(wnd->isOpen())
	{
		wnd->clear(clearColor);
		
		DoEvents();
		CheckCollitions();
		UpdatePhysics();
		_cañon->ActualizarPosiciones(cañonBody);
		_cañon->ActualizarRotacion();
		DrawSprite();
		//  Cañon();
		DrawGame();
      
		wnd->display();
		
		//cout << _cañon->GetRotation() << endl;
	
	}
}
void Game::DrawSprite()
{
	
	_cañon->Dibujar();


}

void Game::UpdatePhysics()
{
	phyWorld->Step(frameTime, 8, 8);
	phyWorld->ClearForces();
	phyWorld->DebugDraw();
	
}
void Game::DrawGame()
{ 
	// Dibujamos el suelo
	sf::RectangleShape groundShape(sf::Vector2f(500, 5));
	groundShape.setFillColor(sf::Color::Red);
	groundShape.setPosition(0, 95);
	wnd->draw(groundShape);

	// Dibujamos las paredes
	sf::RectangleShape leftWallShape(sf::Vector2f(10, alto)); // Alto de la ventana
	leftWallShape.setFillColor(sf::Color::Blue);
	leftWallShape.setPosition(100, 0); // X = 100 para que comience donde termina el suelo
	wnd->draw(leftWallShape);

	sf::RectangleShape rightWallShape(sf::Vector2f(10, alto)); // Alto de la ventana
	rightWallShape.setFillColor(sf::Color::Cyan);
	rightWallShape.setPosition(90, 0); // X = 90 para que comience donde termina el suelo
	wnd->draw(rightWallShape);


	sf::RectangleShape upWallShape(sf::Vector2f(500, 5)); // Alto de la ventana
	upWallShape.setFillColor(sf::Color::Red);
	upWallShape.setPosition(0, 0); // X = 90 para que comience donde termina el suelo
	wnd->draw(upWallShape);

	
	
	// Dibujar texto en la esquina superior izquierda
	sf::Font font;
	if (!font.loadFromFile("font.ttf")) {
		// Si la fuente no se pudo cargar, muestra un mensaje en la consola
		return;
	}
	sf::Text text;
	text.setFont(font);
	text.setString("arrow keys");
	text.setCharacterSize(10); // Tamaño del texto
	text.setFillColor(sf::Color::Red);
	text.setPosition(5, 5); 

	sf::Text text2;
	text2.setFont(font);
	text2.setString("& space");
	text2.setCharacterSize(10); // Tamaño del texto
	text2.setFillColor(sf::Color::Red);
	text2.setPosition(5, 14);

	if (text.getPosition().x < 0 || text.getPosition().y < 0 ||
		text.getPosition().x + text.getLocalBounds().width > wnd->getSize().x ||
		text.getPosition().y + text.getLocalBounds().height > wnd->getSize().y) {
		std::cerr << "La posición del texto está fuera de la ventana" << std::endl;
		return;
	}
	wnd->draw(text);
	wnd->draw(text2);
	
	if (Keyboard::isKeyPressed(Keyboard::Space) && !circlecreated)
	{
			circlecreated = true;
	}
	else if (!Keyboard::isKeyPressed(Keyboard::Space) && circlecreated)
	{
		controlBody = Box2DHelper::CreateCircularDynamicBody(phyWorld, 5, 5, 0, 0);

		if (_cañon->GetRotation() >= 0 && _cañon->GetRotation() <= 5) {
			controlBody->SetTransform(b2Vec2(30.0f, 70.0f), 0.0f);
			controlBody->ApplyAngularImpulse(2, true);
			i = 1200; j = -1400;
			cout << i << j << endl;
		}
		if (_cañon->GetRotation() > 5 && _cañon->GetRotation() <= 20) {
			controlBody->SetTransform(b2Vec2(30.0f, 80.0f), 0.0f);
			i = 1400; j = -1000;
			cout << i << j << endl;
			cout << _cañon->GetRotation() << endl;
		}
		if (_cañon->GetRotation() <= 21 && _cañon->GetRotation() >= 19) {
			controlBody->SetTransform(b2Vec2(30.0f, 75.0f), 0.0f);
			i = 1400; j = -500;
			cout << i << j << endl;
			cout << _cañon->GetRotation() << endl;
		}
		if (_cañon->GetRotation() >= 6 && _cañon->GetRotation() <= 8) {
			controlBody->SetTransform(b2Vec2(30.0f, 70.0f), 0.0f);
			i = 1400; j = -1000;
			cout << i << j << endl;
			cout << _cañon->GetRotation() << endl;
		}
		if (_cañon->GetRotation() > 351 && _cañon->GetRotation() <= 364) {
			controlBody->SetTransform(b2Vec2(30.0f, 65.0f), 0.0f);
			i = 1500; j = -2500;
			cout << i << j << endl;
			cout << _cañon->GetRotation() << endl;
		}
		if (_cañon->GetRotation() >= 9 && _cañon->GetRotation() <= 18) {
			controlBody->SetTransform(b2Vec2(30.0f, 75.0f), 0.0f);
		}
		// Establecer la masa y la fuerza del cuerpo
		controlBody->SetAwake(true);
		b2MassData massData;
		massData.mass = 2.0f; // Masa deseada
		massData.center = b2Vec2(0.0f, 0.0f); // Centro de masa deseado
		massData.I = 1.0f;
		controlBody->SetMassData(&massData);

		// Aplicar fuerza al cuerpo
		b2Vec2 fuerza(i, j); // Verifica que i y j tengan valores adecuados
		controlBody->ApplyForce(fuerza, controlBody->GetWorldCenter(), true);

		// Dibujar el cuerpo en la ventana
		sf::CircleShape controlShape(5);
		controlShape.setFillColor(sf::Color::Magenta);
		controlShape.setPosition(controlBody->GetPosition().x - 5, controlBody->GetPosition().y - 5);
		wnd->draw(controlShape);

		
		circlecreated = false;
	}
}

void Game::DoEvents()
{
	Event evt;
	while(wnd->pollEvent(evt))
	{
		switch(evt.type)
		{
			case Event::Closed:
				wnd->close();
				break;
			case Event::MouseButtonPressed:
				b2Body *body=Box2DHelper::CreateTriangularDynamicBody(phyWorld,b2Vec2(0.0f, 0.0f), 10.0f, 1.0f, 4.0f, 0.1f);
				// Transformamos las coordenadas segun la vista activa
				Vector2f pos = wnd->mapPixelToCoords(Vector2i(evt.mouseButton.x, evt.mouseButton.y));
				body->SetTransform(b2Vec2(pos.x, pos.y), 0.0f);
				break;
		}
	}

	// Movemos el cuerpo
cañonBody->SetAwake(true);

		
}

void Game::CheckCollitions()
{
	// Veremos mas adelante
}

// Definimos el area del mundo que veremos en nuestro juego
// Box2D tiene problemas para simular magnitudes muy grandes
void Game::SetZoom()
{
	View camara;
	// Posicion del view
	camara.setSize(100.0f, 100.0f);
	camara.setCenter(50.0f, 50.0f);
	wnd->setView(camara); //asignamos la camara
}
/*void Game::Cañon()
{
	if (Keyboard::isKeyPressed(Keyboard::Space) && !circlecreated)
	{
		
	controlBody = Box2DHelper::CreateCircularDynamicBody(phyWorld, 5, 5, 0, 0);
	controlBody->SetTransform(b2Vec2(30, 70), 0.0f);
	circlecreated = true;
	if (_cañon->GetRotation() > 0 && _cañon->GetRotation() < 21)
	{
		cout << "cambio de posicion segun la rotacion para abajo" << endl;
		controlBody->SetTransform(b2Vec2(30.0f, 80.0f), 0.0f);
	}
		cout << "entro en la funcion" << endl;
		
		i = 100;
		j = -100;

	sf::CircleShape controlShape(5);
	controlShape.setFillColor(sf::Color::Magenta);
	controlShape.setPosition(controlBody->GetPosition().x - 5, controlBody->GetPosition().y - 5);
	wnd->draw(controlShape);
		b2Vec2 fuerza(i, j);
		b2MassData massData;
		massData.mass = 4.0f; // Masa deseada
		massData.center = b2Vec2(0.0f, 0.0f); // Centro de masa deseado, aquí se establece en el centro del cuerpo
		massData.I = 1.0f;
		controlBody->SetAwake(true);
		controlBody->SetMassData(&massData);
		controlBody->ApplyForce(fuerza, controlBody->GetWorldCenter(), true);

		cout << "i y j son: " << i << " " << j << endl;

	}
	
}*/
void Game::Cañon()
{

}


void Game::InitPhysics()
{
	// Inicializamos el mundo con la gravedad por defecto
	phyWorld = new b2World(b2Vec2(0.0f, 9.8f));

	//MyContactListener* l= new MyContactListener();
	//phyWorld->SetContactListener(l);
	// Creamos el renderer de debug y le seteamos las banderas para que dibuje TODO
	debugRender = new SFMLRenderer(wnd);
	debugRender->SetFlags(UINT_MAX);
	phyWorld->SetDebugDraw(debugRender);

	// Creamos un piso y paredes
	b2Body* groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
	groundBody->SetTransform(b2Vec2(50.0f, 100.0f), 0.0f);

	b2Body* leftWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
	leftWallBody->SetTransform(b2Vec2(0.0f, 50.0f), 0.0f);

	b2Body* rightWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
	rightWallBody->SetTransform(b2Vec2(100.0f, 50.0f), 0.0f);

	b2Body* upWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
	upWallBody->SetTransform(b2Vec2(50.0f, 0.0f), 0.0f);

	
	
	
	

	
	cañonBody = Box2DHelper::CreateCircularDynamicBody(phyWorld, 5, 0, 0, 0);
	cañonBody->SetTransform(b2Vec2(20.0f, 80.0f), 0.0f);

}

Game::~Game(void)
{ }