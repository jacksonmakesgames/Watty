#include <Watty.h>
#include <res.h>
#include "ConwayLayer.h"
#include <deque>

#define GRIDTEXTUREPATH  "textures/grid.png"

using namespace watty;
using namespace graphics;
using namespace math;

namespace watty {
	namespace physics {
		DebugPhysics* PhysicsWorld2D::debugDraw = new DebugPhysics();
		b2World* PhysicsWorld2D::box2DWorld = new b2World(b2Vec2(0.0f, -20.0f));

	}
}

class SimpleGame : public WattyEngine {
private:
	//Label* upsLabel;
	//Label* fpsLabel;
	//Label* mpsLabel;

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
	SimpleGame() {}
	~SimpleGame() {

	}

	void init() override {
		RawResources::Init();
		window->setVSync(true);
		window->setTitle("Conway's Game of Life {Watty}");
		window->setSize({1600,900});
		glClearColor(1, 1, 1, 1);

		m_width  =  window->getWidth();
		m_height =  window->getHeight();

		//sceneCamera->setProjection(glm::ortho(0, m_width, 0, m_height, -10, 10));
		//sceneCamera->setProjection(glm::ortho(0, m_width, 0, m_height));
		sceneCamera->setSize(glm::vec2(m_width, m_height));
		sceneCamera->position = glm::vec3(800,450,0)+ .5f * cellSize;

		Layer* gridLayer = new Layer("Grid Layer");

		gridLayer->add(new GameObject(glm::vec3(.5f*m_width,.5f*m_height,0) + .5f*cellSize, glm::vec2(m_width, m_height), new Sprite(new Texture(GRIDTEXTUREPATH))));

		Layer* cellLayer = new Layer("Cell Layer");
		Layer* uiLayer = new Layer("UI Layer");

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

		new ConwayLayer("Conway Control Layer", stepRate, reset, run, funColors, stepFlag, stepBackFlag);

		lastGrids.push_back(grid);
	
	}

	void update() override {
		getInput();
		if (reset) resetGrid();
		if (run && Timer::elapsed() > nextStepTime) {
			nextStepTime = Timer::elapsed() + (1.0 / stepRate);
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

		WattyEngine::update();
	
	}

	void render() override {
		
		WattyEngine::render();

		
	}

	void tick() override {
		
		WattyEngine::tick();
	}

	void getInput() {
			sceneCamera->setSize(
				glm::vec2(	
					sceneCamera->getSize().x - 4.0f  * Input::getScrollAmountThisFrameY(),
					sceneCamera->getSize().y - 2.25f * Input::getScrollAmountThisFrameY()
				));

		if (Input::keyWasPressed(GLFW_KEY_SPACE)) {
			step();
 			spaceDownTime = Timer::elapsed();
		}
		else if (Input::keyIsDown(GLFW_KEY_SPACE)) {
			// test if held
			if (framesHeld > 2) {
				if (Timer::elapsed() > spaceDownTime + 1.0f/stepRate) {
					run = true;
				}
			}
			framesHeld++;
		}
		if (Input::keyWasReleased(GLFW_KEY_SPACE)) { 
			run = false;
			spaceDownTime = Timer::elapsed();
			framesHeld = 0;

		}
		
		if (Input::keyWasPressed(GLFW_KEY_R)) {
			run = !run;
		}

		if (Input::mouseButtonIsDown(GLFW_MOUSE_BUTTON_LEFT) && !ImGui::GetIO().WantCaptureMouse) {
			double x, y;
			Input::getMousePos(x, y);
			glm::vec2 pos = window->viewportToWorld({ x,y });
			
			placeCell(pos);
			lastGrids.back() = grid;

		}
		
		if (Input::mouseButtonIsDown(GLFW_MOUSE_BUTTON_RIGHT) && !ImGui::GetIO().WantCaptureMouse) {
			double x, y;
			Input::getMousePos(x, y);

			glm::vec2 pos = window->viewportToWorld({ x,y });
			deleteCell(pos);
			lastGrids.back() = grid;

		}

		if (Input::keyWasPressed(GLFW_KEY_LEFT))
		{
			stepBack();
		}

		if (Input::keyWasPressed(GLFW_KEY_RIGHT))
		{
			step();
			spaceDownTime = Timer::elapsed();

		}
	}

	void placeCell(glm::vec2 pos, bool replace=false) {
		// round to nearest multiple of .2

		pos.x = std::round(pos.x / 20) * 20;
		pos.y = std::round(pos.y / 20) * 20;

		pos.x -= 1;
		pos.y -= 1;
		//pos += (.5f*cellSize);

		int xIndex = pos.x/20;
		int yIndex = (m_height-pos.y)/20;
		//int yIndex = (pos.y)/20;
		if (xIndex >= grid.size() || yIndex >= grid[0].size()) return;
		
		if (!replace && grid[xIndex][yIndex]) return; // Already has one 
		// adjust for size
		
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
			Layer::getLayerByName("Cell Layer")->add(new GameObject(pos, glm::vec2(cellSize, cellSize), new Sprite(Color::RGBA(r, g, b, 1.0f))));

		}
		else
			Layer::getLayerByName("Cell Layer")->add(new GameObject(pos, glm::vec2(cellSize, cellSize), new Sprite(Color::RGBA(0.2, .6f, .8f, 1.0f))));

		grid[xIndex][yIndex] = true;

	}


	void deleteCell(glm::vec2 pos) {

		pos.x = std::round(pos.x / 20) * 20;
		pos.y = std::round(pos.y / 20) * 20;

		pos.x -= 1;
		pos.y -= 1;
		//pos += (.5f*cellSize);

		int xIndex = pos.x / 20;
		int yIndex = (m_height - pos.y) / 20;
		//int yIndex = (pos.y)/20;
		if (xIndex >= grid.size() || yIndex >= grid[0].size()) return;

		grid[xIndex][yIndex] = false;


		clearGridObjects();

		for (size_t i = 0; i < grid.size(); i++)
		{
			for (size_t j = 0; j < grid[i].size(); j++)
			{
				if ((grid[i][j] == true)) {
					glm::vec2 pos;


					pos.x = cellSize + i * 20;
					pos.y = m_height - (j) * 20;
					placeCell(pos, true);

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
					glm::vec2 pos;


					pos.x = cellSize + i * 20;
					pos.y = m_height - (j) * 20;

					placeCell(pos, true);

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
					glm::vec2 pos;
					
					pos.x = cellSize + i * 20;
					pos.y = m_height - (j) * 20;

					placeCell(pos, true);

				}
			}
		}

		lastGrids.push_back(grid);
		if (lastGrids.size() > 1000)
			lastGrids.pop_front();
		
	}

	void clearGridObjects() {
		std::vector<GameObject*> allObjects = Layer::getLayerByName("Cell Layer")->getGameObjects();

		for (size_t i = 0; i < allObjects.size(); i++)
		{
			Layer::getLayerByName("Cell Layer")->remove(allObjects[i]);
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
	SimpleGame game;
	game.start();
	return 0;
}