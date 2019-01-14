#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "MyMatrix3.h"
#include "MyVector3.h"

using namespace std;
using namespace sf;


class Game
{
public:
	Game();
	~Game();
	void run();

	void matrixApp(MyMatrix3 t_matrix);

private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void render();

	Clock clock;
	Time elapsed;

	float rotationAngle = 0.0f;
};