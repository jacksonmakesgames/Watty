#pragma once
#include <Watty/graphics/layers/GUILayer.h>
namespace watty { namespace graphics {
class ConwayLayer : public GUILayer
{
private:
	float& m_stepRateConway;
	float m_stepRateInternal;
	bool& m_running;
	bool& m_reset;
	bool& m_funColors;
	bool& m_stepFlag;
	bool& m_stepBackFlag;
	bool m_x10Speed = false;
	public:
		ConwayLayer(std::string name, float& stepRate, bool& reset, bool& running, bool& funColors,bool& stepFlag,bool& stepBackFlag);

public:
	void draw() override;

private:

	private:

};

} }
