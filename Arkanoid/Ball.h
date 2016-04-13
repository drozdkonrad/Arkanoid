#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
using namespace sf;

struct Ball
{
	CircleShape shape;
	Vector2f velocity;
	float ballRadius = 6;
	float ballVelocity = 3;
	
	int life = 4;

	Ball(float bX, float bY);
	void update(int windowWidth, int windowHeight);
	float x();
	float y();
	float left();
	float right();
	float top();
	float bottom();
	bool Ball::checkLost(float windowHeight, float windowWidth);

	
};

struct Paddle
{
	RectangleShape shape;
	Vector2f velocity;
	float paddleWidth = 70, paddleHeight = 20;
	float paddleVelocity = 2;

	Paddle(float pX, float pY);
	void update(int windowWidth, int windowHeight);
	float x();
	float y();
	float left();
	float right();
	float top();
	float bottom();
};

struct Brick
{
	RectangleShape shape;
	float	brickWidth = 60, brickHeight = 20;
	bool destroyed = false;
	Brick(float bX, float bY);

	float x();
	float y();
	float left();
	float right();
	float top();
	float bottom();
};
void testCollision(Paddle& mPaddle, Ball& mBall);
template<class T1, class T2> bool isCollision(T1& mA, T2& mB);
void testCollision(Brick& mBrick, Ball& mBall);