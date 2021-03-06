#include <Game.h>

bool flip = false;
int current = 1;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube")
{

}

Game::~Game() {}

float vertices[] = {

	1.0f, 1.0f, -5.0f, // 0
	-1.0f, 1.0f, -5.0f, // 1
	-1.0f, -1.0f, -5.0f, // 2
	1.0f, -1.0f, -5.0f, // 3

	1.0f, 1.0f, -15.0f, // 4
   -1.0f, 1.0f, -15.0f, // 5
   -1.0f, -1.0f, -15.0f, // 6
	1.0f, -1.0f, -15.0f, //7
	 
};



float colors[] = { 0.583f,  0.771f,  0.014f,
0.609f,  0.115f,  0.436f,
0.327f,  0.483f,  0.844f,
0.822f,  0.569f,  0.201f,
0.435f,  0.602f,  0.223f,
0.310f,  0.747f,  0.185f,
0.597f,  0.770f,  0.761f,
0.559f,  0.436f,  0.730f,
 };

unsigned int vertex_index[] = { 0, 1, 2 ,2 ,3, 0,  // front face
								4, 5, 6, 6, 7, 4, // back face
								0, 1, 4, 4, 5, 1, // top  face
								0, 3, 4, 4, 7, 3, // right face
								2, 3, 7, 7, 6, 2, // bottom face
								6, 2, 1 , 6, 1, 5 // left face
								};

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

		

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

void Game::matrixApp(MyMatrix3 t_matrix)
{

	for (int index = 0; index < 36; index += 3)
	{
		MyVector3 t_vector = MyVector3(vertices[index],vertices[index + 1], vertices[index + 2]);

		t_vector = t_matrix * t_vector;
		
		vertices[index] = t_vector.x;
		vertices[index + 1] = t_vector.y;
		vertices[index + 2] = t_vector.z;
	}
}

void Game::initialize()
{
	isRunning = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		matrixApp(MyMatrix3::translation(MyVector3(0.0005,0,0)));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		matrixApp(MyMatrix3::translation(MyVector3(-0.0005, 0, 0)));
	}
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		matrixApp(MyMatrix3::rotationZ(0.005));
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		matrixApp(MyMatrix3::scale(1.005));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		matrixApp(MyMatrix3::scale(0.995));
	}

}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glVertexPointer(3, GL_FLOAT, 0, &vertices);
	glColorPointer(3, GL_FLOAT, 0, &colors);

	//glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, &vertex_index);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	window.display();

}
