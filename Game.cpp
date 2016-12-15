#include <Game.h>

static bool flip;
custom::Matrix_3 translateMatrix, scaleMatrix, rotateMatrix;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube VBO")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

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

typedef struct
{
	float coordinate[3];
	float color[3];
} Vertex;

// Front Face
Vertex vertex[6];
GLubyte triangles[6];
// Back Face
Vertex backVertex[6];
GLubyte backTriangles[6];
// Left Face
Vertex leftVertex[6];
GLubyte leftTriangles[6];
// Right Face
Vertex rightVertex[6];
GLubyte rightTriangles[6];
// Top Face
Vertex topVertex[6];
GLubyte topTriangles[6];
// Bottom Face
Vertex bottomVertex[6];
GLubyte bottomTriangles[6];

custom::Vector_3 rotateVec[6], translateVec[6], scaleVec[6];

/* Variable to hold the VBO identifier */
GLuint vbo[1];
GLuint index;

void Game::initialize()
{
	isRunning = true;

	glewInit();

	/* Vertices counter-clockwise winding */

	// Front-top Face Coordinates
	// Point B
	vertex[0].coordinate[0] = -0.5f;
	vertex[0].coordinate[1] = -0.5f;
	vertex[0].coordinate[2] = 0.0f;
	// Point A
	vertex[1].coordinate[0] = -0.5f;
	vertex[1].coordinate[1] = 0.5f;
	vertex[1].coordinate[2] = 0.0f;
	// Point D
	vertex[2].coordinate[0] = 0.5f;
	vertex[2].coordinate[1] = 0.5f;
	vertex[2].coordinate[2] = 0.0f;
	// Front-bottom Face Coordinates
	// Point D
	vertex[3].coordinate[0] = 0.5f;
	vertex[3].coordinate[1] = 0.5f;
	vertex[3].coordinate[2] = 0.0f;
	// Point C
	vertex[4].coordinate[0] = 0.5f;
	vertex[4].coordinate[1] = -0.5f;
	vertex[4].coordinate[2] = 0.0f;
	// Point B
	vertex[5].coordinate[0] = -0.5f;
	vertex[5].coordinate[1] = -0.5f;
	vertex[5].coordinate[2] = 0.0f;
	// Front-top Face Colour
	// Point B
	vertex[0].color[0] = 0.1f;
	vertex[0].color[1] = 1.0f;
	vertex[0].color[2] = 0.0f;
	// Point A
	vertex[1].color[0] = 0.2f;
	vertex[1].color[1] = 1.0f;
	vertex[1].color[2] = 0.0f;
	// Point D
	vertex[2].color[0] = 0.3f;
	vertex[2].color[1] = 1.0f;
	vertex[2].color[2] = 0.0f;
	// Front-bottom Face Colour
	// Point D
	vertex[3].color[0] = 0.4f;
	vertex[3].color[1] = 1.0f;
	vertex[3].color[2] = 0.0f;
	// Point C
	vertex[4].color[0] = 0.5f;
	vertex[4].color[1] = 1.0f;
	vertex[4].color[2] = 0.0f;
	// PointB
	vertex[5].color[0] = 0.6f;
	vertex[5].color[1] = 1.0f;
	vertex[5].color[2] = 0.0f;

	// Back-top Face Coordinates
	// Point H
	backVertex[0].coordinate[0] = -0.3f;
	backVertex[0].coordinate[1] = -0.3f;
	backVertex[0].coordinate[2] = 0.5f;
	// Point G
	backVertex[1].coordinate[0] = -0.3f;
	backVertex[1].coordinate[1] = 0.3f;
	backVertex[1].coordinate[2] = 0.5f;
	// Point F
	backVertex[2].coordinate[0] = 0.3f;
	backVertex[2].coordinate[1] = 0.3f;
	backVertex[2].coordinate[2] = 0.5f;
	// Back-bottom Face Coordinates
	// Point F
	backVertex[3].coordinate[0] = 0.3f;
	backVertex[3].coordinate[1] = 0.3f;
	backVertex[3].coordinate[2] = 0.5f;
	// Point E
	backVertex[4].coordinate[0] = 0.3f;
	backVertex[4].coordinate[1] = -0.3f;
	backVertex[4].coordinate[2] = 0.5f;
	// Point H
	backVertex[5].coordinate[0] = -0.3f;
	backVertex[5].coordinate[1] = -0.3f;
	backVertex[5].coordinate[2] = 0.5f;
	// Front-top Face Colour
	// Point H
	backVertex[0].color[0] = 1.0f;
	backVertex[0].color[1] = 0.1f;
	backVertex[0].color[2] = 0.0f;
	// Point G
	backVertex[1].color[0] = 1.0f;
	backVertex[1].color[1] = 0.2f;
	backVertex[1].color[2] = 0.0f;
	// Point F
	backVertex[2].color[0] = 1.0f;
	backVertex[2].color[1] = 0.3f;
	backVertex[2].color[2] = 0.0f;
	// Back-bottom Face Colour
	// Point F
	backVertex[3].color[0] = 1.0f;
	backVertex[3].color[1] = 0.4f;
	backVertex[3].color[2] = 0.0f;
	// Point E
	backVertex[4].color[0] = 1.0f;
	backVertex[4].color[1] = 0.5f;
	backVertex[4].color[2] = 0.0f;
	// Point H
	backVertex[5].color[0] = 1.0f;
	backVertex[5].color[1] = 0.6f;
	backVertex[5].color[2] = 0.0f;

	// Left-top Face Coordinates
	// Point B
	leftVertex[0].coordinate[0] = -0.5f;
	leftVertex[0].coordinate[1] = -0.5f;
	leftVertex[0].coordinate[2] = 0.0f;
	// Point A
	leftVertex[1].coordinate[0] = -0.5f;
	leftVertex[1].coordinate[1] = 0.5f;
	leftVertex[1].coordinate[2] = 0.0f;
	// Point G
	leftVertex[2].coordinate[0] = -0.3f;
	leftVertex[2].coordinate[1] = 0.3f;
	leftVertex[2].coordinate[2] = 0.5f;
	// Left-bottom Face Coordinates
	// Point G
	leftVertex[3].coordinate[0] = -0.3f;
	leftVertex[3].coordinate[1] = 0.3f;
	leftVertex[3].coordinate[2] = 0.5f;
	// Point H
	leftVertex[4].coordinate[0] = -0.3f;
	leftVertex[4].coordinate[1] = -0.3f;
	leftVertex[4].coordinate[2] = 0.5f;
	// Point B
	leftVertex[5].coordinate[0] = -0.5f;
	leftVertex[5].coordinate[1] = -0.5f;
	leftVertex[5].coordinate[2] = 0.0f;
	// Left-top Face Colour
	// Point B
	leftVertex[0].color[0] = 0.0f;
	leftVertex[0].color[1] = 0.1f;
	leftVertex[0].color[2] = 1.0f;
	// Point A
	leftVertex[1].color[0] = 0.0f;
	leftVertex[1].color[1] = 0.2f;
	leftVertex[1].color[2] = 1.0f;
	// Point G
	leftVertex[2].color[0] = 0.0f;
	leftVertex[2].color[1] = 0.3f;
	leftVertex[2].color[2] = 1.0f;
	// Left-bottom Face Colour
	// Point F
	leftVertex[3].color[0] = 0.0f;
	leftVertex[3].color[1] = 0.4f;
	leftVertex[3].color[2] = 1.0f;
	// Point E
	leftVertex[4].color[0] = 0.0f;
	leftVertex[4].color[1] = 0.5f;
	leftVertex[4].color[2] = 1.0f;
	// Point H
	leftVertex[5].color[0] = 0.0f;
	leftVertex[5].color[1] = 0.6f;
	leftVertex[5].color[2] = 1.0f;

	// Right-top Face Coordinates
	// Point C
	rightVertex[0].coordinate[0] = 0.5f;
	rightVertex[0].coordinate[1] = -0.5f;
	rightVertex[0].coordinate[2] = 0.0f;
	// Point D
	rightVertex[1].coordinate[0] = 0.5f;
	rightVertex[1].coordinate[1] = 0.5f;
	rightVertex[1].coordinate[2] = 0.0f;
	// Point F
	rightVertex[2].coordinate[0] = 0.3f;
	rightVertex[2].coordinate[1] = 0.3f;
	rightVertex[2].coordinate[2] = 0.5f;
	// Right-bottom Face Coordinates
	// Point F
	rightVertex[3].coordinate[0] = 0.3f;
	rightVertex[3].coordinate[1] = 0.3f;
	rightVertex[3].coordinate[2] = 0.5f;
	// Point E
	rightVertex[4].coordinate[0] = 0.3f;
	rightVertex[4].coordinate[1] = -0.3f;
	rightVertex[4].coordinate[2] = 0.5f;
	// Point C
	rightVertex[5].coordinate[0] = 0.5f;
	rightVertex[5].coordinate[1] = -0.5f;
	rightVertex[5].coordinate[2] = 0.0f;
	// Right-top Face Colour
	// Point C
	rightVertex[0].color[0] = 1.0f;
	rightVertex[0].color[1] = 0.1f;
	rightVertex[0].color[2] = 1.0f;
	// Point D
	rightVertex[1].color[0] = 1.0f;
	rightVertex[1].color[1] = 0.2f;
	rightVertex[1].color[2] = 1.0f;
	// Point F
	rightVertex[2].color[0] = 1.0f;
	rightVertex[2].color[1] = 0.3f;
	rightVertex[2].color[2] = 1.0f;
	// Right-bottom Face Colour
	// Point F
	rightVertex[3].color[0] = 1.0f;
	rightVertex[3].color[1] = 0.4f;
	rightVertex[3].color[2] = 1.0f;
	// Point E
	rightVertex[4].color[0] = 1.0f;
	rightVertex[4].color[1] = 0.5f;
	rightVertex[4].color[2] = 1.0f;
	// Point C
	rightVertex[5].color[0] = 1.0f;
	rightVertex[5].color[1] = 0.6f;
	rightVertex[5].color[2] = 1.0f;

	// Top-top Face Coordinates
	// Point A
	topVertex[0].coordinate[0] = -0.5f;
	topVertex[0].coordinate[1] = 0.5f;
	topVertex[0].coordinate[2] = 0.0f;
	// Point G
	topVertex[1].coordinate[0] = -0.3f;
	topVertex[1].coordinate[1] = 0.3f;
	topVertex[1].coordinate[2] = 0.5f;
	// Point F
	topVertex[2].coordinate[0] = 0.3f;
	topVertex[2].coordinate[1] = 0.3f;
	topVertex[2].coordinate[2] = 0.5f;
	// Right-bottom Face Coordinates
	// Point F
	topVertex[3].coordinate[0] = 0.3f;
	topVertex[3].coordinate[1] = 0.3f;
	topVertex[3].coordinate[2] = 0.5f;
	// Point D
	topVertex[4].coordinate[0] = 0.5f;
	topVertex[4].coordinate[1] = 0.5f;
	topVertex[4].coordinate[2] = 0.0f;
	// Point A
	topVertex[5].coordinate[0] = -0.5f;
	topVertex[5].coordinate[1] = 0.5f;
	topVertex[5].coordinate[2] = 0.0f;
	// Right-top Face Colour
	// Point A
	topVertex[0].color[0] = 0.0f;
	topVertex[0].color[1] = 1.0f;
	topVertex[0].color[2] = 1.1f;
	// Point G
	topVertex[1].color[0] = 0.0f;
	topVertex[1].color[1] = 1.0f;
	topVertex[1].color[2] = 1.2f;
	// Point F
	topVertex[2].color[0] = 0.0f;
	topVertex[2].color[1] = 1.0f;
	topVertex[2].color[2] = 1.3f;
	// Top-bottom Face Colour
	// Point F
	topVertex[3].color[0] = 0.0f;
	topVertex[3].color[1] = 1.0f;
	topVertex[3].color[2] = 1.4f;
	// Point D
	topVertex[4].color[0] = 0.0f;
	topVertex[4].color[1] = 1.0f;
	topVertex[4].color[2] = 1.5f;
	// Point A
	topVertex[5].color[0] = 0.0f;
	topVertex[5].color[1] = 1.0f;
	topVertex[5].color[2] = 1.6f;

	// Bottom-top Face Coordinates
	// Point B
	bottomVertex[0].coordinate[0] = -0.5f;
	bottomVertex[0].coordinate[1] = -0.5f;
	bottomVertex[0].coordinate[2] = 0.0f;
	// Point H
	bottomVertex[1].coordinate[0] = -0.3f;
	bottomVertex[1].coordinate[1] = -0.3f;
	bottomVertex[1].coordinate[2] = 0.5f;
	// Point E
	bottomVertex[2].coordinate[0] = 0.3f;
	bottomVertex[2].coordinate[1] = -0.3f;
	bottomVertex[2].coordinate[2] = 0.5f;
	// Bottom-bottom Face Coordinates
	// Point E
	bottomVertex[3].coordinate[0] = 0.3f;
	bottomVertex[3].coordinate[1] = -0.3f;
	bottomVertex[3].coordinate[2] = 0.5f;
	// Point C
	bottomVertex[4].coordinate[0] = 0.5f;
	bottomVertex[4].coordinate[1] = -0.5f;
	bottomVertex[4].coordinate[2] = 0.0f;
	// Point B
	bottomVertex[5].coordinate[0] = -0.5f;
	bottomVertex[5].coordinate[1] = -0.5f;
	bottomVertex[5].coordinate[2] = 0.0f;
	// Bottom-top Face Colour
	// Point B
	bottomVertex[0].color[0] = 1.1f;
	bottomVertex[0].color[1] = 0.0f;
	bottomVertex[0].color[2] = 0.0f;
	// Point H
	bottomVertex[1].color[0] = 1.2f;
	bottomVertex[1].color[1] = 0.0f;
	bottomVertex[1].color[2] = 0.0f;
	// Point E
	bottomVertex[2].color[0] = 1.3f;
	bottomVertex[2].color[1] = 0.0f;
	bottomVertex[2].color[2] = 0.0f;
	// Bottom-bottom Face Colour
	// Point E
	bottomVertex[3].color[0] = 1.4f;
	bottomVertex[3].color[1] = 0.0f;
	bottomVertex[3].color[2] = 0.0f;
	// Point C
	bottomVertex[4].color[0] = 1.5f;
	bottomVertex[4].color[1] = 0.0f;
	bottomVertex[4].color[2] = 0.0f;
	// Point H
	bottomVertex[5].color[0] = 1.6f;
	bottomVertex[5].color[1] = 0.0f;
	bottomVertex[5].color[2] = 0.0f;

	// Front face
	triangles[0] = 0;   triangles[1] = 1;   triangles[2] = 2;
	triangles[3] = 3;   triangles[4] = 4;   triangles[5] = 5;

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	// Front face
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, vertex, GL_STATIC_DRAW);
	// Back face
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, backVertex, GL_STATIC_DRAW);
	// Left face
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, leftVertex, GL_STATIC_DRAW);
	// Right face
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, rightVertex, GL_STATIC_DRAW);
	// Top face
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, topVertex, GL_STATIC_DRAW);
	// Bottom face
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, bottomVertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 6, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
	

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!flip)
		{
			flip = true;
		}
		else
			flip = false;
	}

	if (flip)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}


	translateMatrix = translateMatrix.Translate(1.0f, 1.0f);
	rotateMatrix = rotateMatrix.Rotation(1);
	//rotateMatrix = rotateMatrix.RotationX(1);
	//rotateMatrix = rotateMatrix.RotationY(1);
	scaleMatrix = scaleMatrix.Scale(0.00001f, 0.00001f);
	//scaleMatrix = scaleMatrix.Scale3D(1, 1);

	//
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		for (int v = 0; v < 6; v++)
		{
			// Front face
			rotateVec[v] = custom::Vector_3(vertex[v].coordinate[0], vertex[v].coordinate[1], vertex[v].coordinate[2]);
			rotateVec[v] = rotateMatrix * rotateVec[v];
			vertex[v].coordinate[0] = rotateVec[v].getX();
			vertex[v].coordinate[1] = rotateVec[v].getY();
			vertex[v].coordinate[2] = rotateVec[v].getZ();
			// Back face
			rotateVec[v] = custom::Vector_3(backVertex[v].coordinate[0], backVertex[v].coordinate[1], backVertex[v].coordinate[2]);
			rotateVec[v] = rotateMatrix * rotateVec[v];
			backVertex[v].coordinate[0] = rotateVec[v].getX();
			backVertex[v].coordinate[1] = rotateVec[v].getY();
			backVertex[v].coordinate[2] = rotateVec[v].getZ();
			// Left face
			rotateVec[v] = custom::Vector_3(leftVertex[v].coordinate[0], leftVertex[v].coordinate[1], leftVertex[v].coordinate[2]);
			rotateVec[v] = rotateMatrix * rotateVec[v];
			leftVertex[v].coordinate[0] = rotateVec[v].getX();
			leftVertex[v].coordinate[1] = rotateVec[v].getY();
			leftVertex[v].coordinate[2] = rotateVec[v].getZ();
			// Right face
			rotateVec[v] = custom::Vector_3(rightVertex[v].coordinate[0], rightVertex[v].coordinate[1], rightVertex[v].coordinate[2]);
			rotateVec[v] = rotateMatrix * rotateVec[v];
			rightVertex[v].coordinate[0] = rotateVec[v].getX();
			rightVertex[v].coordinate[1] = rotateVec[v].getY();
			rightVertex[v].coordinate[2] = rotateVec[v].getZ();
			// Top face
			rotateVec[v] = custom::Vector_3(topVertex[v].coordinate[0], topVertex[v].coordinate[1], topVertex[v].coordinate[2]);
			rotateVec[v] = rotateMatrix * rotateVec[v];
			topVertex[v].coordinate[0] = rotateVec[v].getX();
			topVertex[v].coordinate[1] = rotateVec[v].getY();
			topVertex[v].coordinate[2] = rotateVec[v].getZ();
			// Bottom face
			rotateVec[v] = custom::Vector_3(bottomVertex[v].coordinate[0], backVertex[v].coordinate[1], backVertex[v].coordinate[2]);
			rotateVec[v] = rotateMatrix * rotateVec[v];
			bottomVertex[v].coordinate[0] = rotateVec[v].getX();
			bottomVertex[v].coordinate[1] = rotateVec[v].getY();
			bottomVertex[v].coordinate[2] = rotateVec[v].getZ();
		}
	}

	//
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		for (int v = 0; v < 6; v++)
		{
			// Front face
			scaleVec[v] = custom::Vector_3(vertex[v].coordinate[0], vertex[v].coordinate[1], vertex[v].coordinate[2]);
			scaleVec[v] = scaleMatrix * scaleVec[v];
			vertex[v].coordinate[0] = scaleVec[v].getX();
			vertex[v].coordinate[1] = scaleVec[v].getY();
			vertex[v].coordinate[2] = scaleVec[v].getZ();
			// Back face
			scaleVec[v] = custom::Vector_3(backVertex[v].coordinate[0], backVertex[v].coordinate[1], backVertex[v].coordinate[2]);
			scaleVec[v] = scaleMatrix * scaleVec[v];
			backVertex[v].coordinate[0] = scaleVec[v].getX();
			backVertex[v].coordinate[1] = scaleVec[v].getY();
			backVertex[v].coordinate[2] = scaleVec[v].getZ();
			// Left face
			scaleVec[v] = custom::Vector_3(leftVertex[v].coordinate[0], leftVertex[v].coordinate[1], leftVertex[v].coordinate[2]);
			scaleVec[v] = scaleMatrix * scaleVec[v];
			leftVertex[v].coordinate[0] = scaleVec[v].getX();
			leftVertex[v].coordinate[1] = scaleVec[v].getY();
			leftVertex[v].coordinate[2] = scaleVec[v].getZ();
			// Right face
			scaleVec[v] = custom::Vector_3(rightVertex[v].coordinate[0], rightVertex[v].coordinate[1], rightVertex[v].coordinate[2]);
			scaleVec[v] = scaleMatrix * scaleVec[v];
			rightVertex[v].coordinate[0] = scaleVec[v].getX();
			rightVertex[v].coordinate[1] = scaleVec[v].getY();
			rightVertex[v].coordinate[2] = scaleVec[v].getZ();
			// Top face
			scaleVec[v] = custom::Vector_3(topVertex[v].coordinate[0], topVertex[v].coordinate[1], topVertex[v].coordinate[2]);
			scaleVec[v] = scaleMatrix * scaleVec[v];
			topVertex[v].coordinate[0] = scaleVec[v].getX();
			topVertex[v].coordinate[1] = scaleVec[v].getY();
			topVertex[v].coordinate[2] = scaleVec[v].getZ();
			// Bottom face
			scaleVec[v] = custom::Vector_3(bottomVertex[v].coordinate[0], backVertex[v].coordinate[1], backVertex[v].coordinate[2]);
			scaleVec[v] = scaleMatrix * scaleVec[v];
			bottomVertex[v].coordinate[0] = scaleVec[v].getX();
			bottomVertex[v].coordinate[1] = scaleVec[v].getY();
			bottomVertex[v].coordinate[2] = scaleVec[v].getZ();
		}
	}

	//
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		for (int v = 0; v < 6; v++)
		{
			// Front face
			translateVec[v] = custom::Vector_3(vertex[v].coordinate[0], vertex[v].coordinate[1], vertex[v].coordinate[2]);
			translateVec[v] = translateMatrix * translateVec[v];
			vertex[v].coordinate[0] = translateVec[v].getX();
			vertex[v].coordinate[1] = translateVec[v].getY();
			vertex[v].coordinate[2] = translateVec[v].getZ();
			// Back face
			translateVec[v] = custom::Vector_3(backVertex[v].coordinate[0], backVertex[v].coordinate[1], backVertex[v].coordinate[2]);
			translateVec[v] = translateMatrix * translateVec[v];
			backVertex[v].coordinate[0] = translateVec[v].getX();
			backVertex[v].coordinate[1] = translateVec[v].getY();
			backVertex[v].coordinate[2] = translateVec[v].getZ();
			// Left face
			translateVec[v] = custom::Vector_3(leftVertex[v].coordinate[0], leftVertex[v].coordinate[1], leftVertex[v].coordinate[2]);
			translateVec[v] = translateMatrix * translateVec[v];
			leftVertex[v].coordinate[0] = translateVec[v].getX();
			leftVertex[v].coordinate[1] = translateVec[v].getY();
			leftVertex[v].coordinate[2] = translateVec[v].getZ();
			// Right face
			translateVec[v] = custom::Vector_3(rightVertex[v].coordinate[0], rightVertex[v].coordinate[1], rightVertex[v].coordinate[2]);
			translateVec[v] = translateMatrix * translateVec[v];
			rightVertex[v].coordinate[0] = translateVec[v].getX();
			rightVertex[v].coordinate[1] = translateVec[v].getY();
			rightVertex[v].coordinate[2] = translateVec[v].getZ();
			// Top face
			translateVec[v] = custom::Vector_3(topVertex[v].coordinate[0], topVertex[v].coordinate[1], topVertex[v].coordinate[2]);
			translateVec[v] = translateMatrix * translateVec[v];
			topVertex[v].coordinate[0] = translateVec[v].getX();
			topVertex[v].coordinate[1] = translateVec[v].getY();
			topVertex[v].coordinate[2] = translateVec[v].getZ();
			// Bottom face
			translateVec[v] = custom::Vector_3(bottomVertex[v].coordinate[0], backVertex[v].coordinate[1], backVertex[v].coordinate[2]);
			translateVec[v] = translateMatrix * translateVec[v];
			bottomVertex[v].coordinate[0] = translateVec[v].getX();
			bottomVertex[v].coordinate[1] = translateVec[v].getY();
			bottomVertex[v].coordinate[2] = translateVec[v].getZ();
		}
	}

	cout << "Update up" << endl;
}

void Game::render()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	//Front face
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, vertex, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glColorPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 12);

	/* Draw Triangle from VBO */
	// Fornt Face
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	// Back face
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, backVertex, GL_STATIC_DRAW);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	// Left face
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, leftVertex, GL_STATIC_DRAW);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	// Right face
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, rightVertex, GL_STATIC_DRAW);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	// Top face
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, topVertex, GL_STATIC_DRAW);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	// Bottom face
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, bottomVertex, GL_STATIC_DRAW);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*)NULL + 0);


	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	window.display();
}

void Game::unload()
{
	cout << "Cleaning up" << endl;

	glDeleteBuffers(1, vbo);
}

