#include "Ball.hpp"

using namespace std;
using namespace sf;

Ball::Ball()
{
	card = nullptr;
}

Ball& Ball::Instance()
{
	static Ball instance;
	return instance;
}

void Ball::Start()
{

}
