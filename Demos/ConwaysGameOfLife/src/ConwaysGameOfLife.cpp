#include "../../../Watty-Core/src/letc.h"
#include "ConwayLayer.h"
#include <math.h>
#include <deque>
// TODO: relative 
#define VERTPATH "J:/OneDrive/Projects/Game_Development/Watty/Demos/res/shaders/basic.vert"
#define FRAGLITPATH "J:/OneDrive/Projects/Game_Development/Watty/Demos/res/shaders/basic_lit.frag"
#define FRAGUNLITPATH "J:/OneDrive/Projects/Game_Development/Watty/Demos/res/shaders/basic_unlit.frag"
#define FONTPATH "J:/OneDrive/Projects/Game_Development/Watty/Demos/res/fonts/Roboto-Regular.ttf"
#define FONTITALICPATH "J:/OneDrive/Projects/Game_Development/Watty/Demos/res/fonts/Roboto-Italic.ttf"
#define GRIDTEXTUREPATH "J:/OneDrive/Projects/Game_Development/Watty/Demos/ConwaysGameOfLife/res/grid.png"
//
//#define WINDOWWIDTH 1600
//#define WINDOWHEIGHT 900

using namespace letc;
using namespace graphics;
using namespace math;

namespace letc {
	namespace physics {
		DebugPhysics* PhysicsWorld2D::debugDraw = new DebugPhysics();
		b2World* PhysicsWorld2D::box2DWorld = new b2World(b2Vec2(0.0f, -20.0f));

	}
}

class PhysicsDemo : public LETC {
private:
	Window* m_window;
	Label* fpsLabel;
	Label* upsLabel;
	Label* mpsLabel;

	float playerSpeed = 10;

	float time = 0.0f;

	GameObject* playerGO;
	GameObject* enemyGO;
	float cellSize = 18;

	bool run = false;
	bool reset = false;
	bool funColors = true;
	bool stepFlag = false;
	bool stepBackFlag = false;

	std::vector<std::vector<bool>> grid;
	std::deque<std::vector<std::vector<bool>>> lastGrids;

	float stepRate   = 2.0f;
	float nextStepTime = 0.0f;
	float spaceDownTime = 0.0f;
	int framesHeld = 0;

	int m_height;
	int m_width;


public:
	PhysicsDemo() {}
	~PhysicsDemo() {

	}

	void init() override {
		m_window = createWindow("Conway's Game of Life {Watty}", 1600, 900, false);
		m_window->setVSync(true);
		glClearColor(1, 1, 1, 1);

		m_width = m_window->getWidth();
		m_height = m_window->getHeight();

		sceneCamera->setProjection(math::Matrix4::orthographic(0,m_width, 0, m_height, -10, 10));
		Layer* gridLayer = new Layer("Grid Layer", new BatchRenderer2D(), new Shader(VERTPATH, FRAGUNLITPATH));

		layers.push_back(gridLayer);
		gridLayer->add(new GameObject(Vector2(0, 0), Vector2(m_width, m_height), new Sprite(new Texture(GRIDTEXTUREPATH))));


		Layer* cellLayer = new Layer("Cell Layer", new BatchRenderer2D(), new Shader(VERTPATH, FRAGUNLITPATH));
		Layer* uiLayer = new Layer("UI Layer", new BatchRenderer2D(), new Shader(VERTPATH, FRAGUNLITPATH));
		layers.push_back(cellLayer);
		layers.push_back(uiLayer);

		/*Resize the 2D std::vector to the specified width and height*/
		grid.resize(m_width/20); //We need HEIGHT/20 sub-vectors
		for (int i = 0; i < grid.size(); ++i)
			grid[i].resize(m_height/20); //each sub-vector has a size of WIDTH

		for (size_t i = 0; i < grid.size(); i++)
		{
			for (size_t j = 0; j < grid[i].size(); j++)
			{
				grid[i][j] = false;
			}
		}

		layers.push_back(new ConwayLayer("Conway Control Layer", stepRate, reset, run, funColors, stepFlag, stepBackFlag, new Shader(VERTPATH, FRAGUNLITPATH)));

		lastGrids.push_back(grid);
	}

	void update() override {
		getInput();
		if (reset) resetGrid();
		if (run && gameTimer->elapsed() > nextStepTime) {
			nextStepTime = gameTimer->elapsed() + (1.0 / stepRate);
			step();
		}
		if (stepFlag) {
			stepFlag = false;
			run = false;
			step();
		}
		else if (stepBackFlag) {
			stepBackFlag = false;
			run = false;
			stepBack();
		}

		LETC::update();
	
	}

	void render() override {

		LETC::render();

		
	}

	void tick() override {
		
		LETC::tick();
	}

	void getInput() {
		

		if (m_window->keyWasPressed(GLFW_KEY_SPACE)) {
			step();
 			spaceDownTime = gameTimer->elapsed();
		}
		else if (m_window->keyIsDown(GLFW_KEY_SPACE)) {
			// test if held
			if (framesHeld > 2) {
				if (gameTimer->elapsed() > spaceDownTime + 1.0f/stepRate) {
					run = true;
				}
			}
			framesHeld++;
		}
		if (m_window->keyWasReleased(GLFW_KEY_SPACE)) { 
			run = false;
			spaceDownTime = gameTimer->elapsed();
			framesHeld = 0;

		}
		
		if (m_window->keyWasPressed(GLFW_KEY_R)) {
			run = !run;
		}

		if (m_window->mouseButtonIsDown(GLFW_MOUSE_BUTTON_LEFT) && !ImGui::GetIO().WantCaptureMouse) {
			double x, y;
			m_window->getMousePos(x, y);
			y = m_height - y;

			y = y - cellSize / 2;
			x = x - cellSize / 2;

			placeCell(Vector2(x, y));
			lastGrids.back() = grid;

		}
		
		if (m_window->mouseButtonIsDown(GLFW_MOUSE_BUTTON_RIGHT) && !ImGui::GetIO().WantCaptureMouse) {
			double x, y;
			m_window->getMousePos(x, y);
			y = m_height - y;

			y = y - cellSize / 2;
			x = x - cellSize / 2;

			deleteCell(Vector2(x, y));
			lastGrids.back() = grid;

		}

		if (m_window->keyWasPressed(GLFW_KEY_LEFT))
		{
			stepBack();
		}

		if (m_window->keyWasPressed(GLFW_KEY_RIGHT))
		{
			step();
			spaceDownTime = gameTimer->elapsed();

		}
	}

	void placeCell(Vector2 pos) {
		// round to nearest multiple of .2


		pos.x = std::round(pos.x / 20) * 20;
		pos.y = std::round(pos.y / 20) * 20;

		pos.x += 1;
		pos.y += 1;

		int xIndex = pos.x/20;
		int yIndex = (m_height-pos.y)/20;
		if (xIndex >= grid.size() || yIndex >= grid[0].size()) return;
		//if (grid[xIndex][yIndex]) return;
		
		grid[xIndex][yIndex] = true;

		if (funColors) {
			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			
		/*	r = (r + 1) / 4;
			g = (g + 1) / 2;
			b = (b + 1) / 2;*/

			r = pos.x / m_width;
			g = pos.y / m_height;
			b = pos.x / m_width;
			if (r < 0.4f) r = 0.4f;
			if (g < 0.4f) g = 0.4f;
			if (b < 0.5f) b = 0.5f;

			if (r > 0.8f) r = 0.8f;
			if (g > 0.8f) g = 0.8f;
			if (b > 0.9f) b = 0.9f;
			getLayerByName("Cell Layer")->add(new GameObject(pos, Vector2(cellSize, cellSize), new Sprite(Color::RGBA(r, g, b, 1.0f))));

		}
		else
			getLayerByName("Cell Layer")->add(new GameObject(pos, Vector2(cellSize, cellSize), new Sprite(Color::RGBA(0.2, .6f, .8f, 1.0f))));
	}


	void deleteCell(Vector2 pos) {

		pos.x = std::round(pos.x / 20) * 20;
		pos.y = std::round(pos.y / 20) * 20;

		pos.x += 1;
		pos.y += 1;

		int xIndex = pos.x / 20;
		int yIndex = (m_height - pos.y) / 20;
		if (xIndex >= grid.size() || yIndex >= grid[0].size()) return;
		//if (grid[xIndex][yIndex]) return;

		grid[xIndex][yIndex] = false;
		clearGridObjects();

		for (size_t i = 0; i < grid.size(); i++)
		{
			for (size_t j = 0; j < grid[i].size(); j++)
			{
				if ((grid[i][j] == true)) {
					Vector2 pos;

					pos.x = i * 20;
					pos.y = 900 - (j + 1) * 20;
					pos.y = pos.y - cellSize / 2;
					pos.x = pos.x - cellSize / 2;

					placeCell(pos);

				}
			}
		}

	}

	void stepBack() {
		clearGridObjects();
		if (lastGrids.size() > 1)
			lastGrids.pop_back();
		grid = lastGrids.back();

		for (size_t i = 0; i < grid.size(); i++)
		{
			for (size_t j = 0; j < grid[i].size(); j++)
			{
				if ((grid[i][j] == true)) {
					Vector2 pos;

					pos.x = i * 20;
					pos.y = 900 - (j + 1) * 20;
					pos.y = pos.y - cellSize / 2;
					pos.x = pos.x - cellSize / 2;

					placeCell(pos);

				}
			}
		}

	}
		
	void step() {
		// Loop through every cell 
		// l = i // m = j
		std::vector<std::vector<bool>> future = grid;

		for (size_t i = 0; i < grid.size(); i++)
		{
			for (size_t j = 0; j < grid[i].size(); j++)
			{
				// find no of neighbors that are alive 
				int aliveNeighbours = 0;
				int kMin = i == 0 ? 0 : -1;
				int lMin = j == 0 ? 0 : -1;

				int kMax = i + 1 ==    grid.size()  ? 0 : 1;
				int lMax = j + 1 == grid[0].size()  ? 0 : 1;


				for (int k = kMin; k <= kMax; k++) {
					for (int l = lMin; l <= lMax; l++) {
						if (grid[i + k][j + l]) aliveNeighbours++;
					}
				}
				if (grid[i][j]) aliveNeighbours--;
				// Implementing the Rules of Life 
				
				// Cell is lonely and dies 
				if ((grid[i][j] == true) && (aliveNeighbours < 2))
					future[i][j] = false;

				// Cell dies due to over population 
				else if ((grid[i][j] == true) && (aliveNeighbours > 3))
					future[i][j] = false;

				// A new cell is born 
				else if ((grid[i][j] == false) && (aliveNeighbours == 3))
					future[i][j] = true;

				// Remains the same 
				else
					future[i][j] = grid[i][j];
			}
		}

		// output
		clearGridObjects();
		grid = future;
		for (size_t i = 0; i < grid.size(); i++)
		{
			for (size_t j = 0; j < grid[i].size(); j++)
			{
				if ((grid[i][j] == true)) {
					Vector2 pos;
					
					pos.x = i * 20;
					pos.y = 900 - (j+1) * 20;
					pos.y = pos.y - cellSize / 2;
					pos.x = pos.x - cellSize / 2;

					placeCell(pos);

				}
			}
		}

		lastGrids.push_back(grid);
		if (lastGrids.size() > 1000)
			lastGrids.pop_front();
		
	}

	void clearGridObjects() {
		std::vector<GameObject*> allObjects = getLayerByName("Cell Layer")->getGameObjects();

		for (size_t i = 0; i < allObjects.size(); i++)
		{
			getLayerByName("Cell Layer")->remove(allObjects[i]);
		}
	}
	void resetGrid() {
		clearGridObjects();
		for (size_t i = 0; i < grid.size(); i++)
		{
			for (size_t j = 0; j < grid[i].size(); j++)
			{
				grid[i][j] = false;
			}
		}
		reset = false;
	}
};


int main() {
	PhysicsDemo game;
	game.start();
	return 0;
}