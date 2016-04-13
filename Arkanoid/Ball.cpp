#include "Ball.h"
#include <SFML/Graphics.hpp>
#include<vector>
using namespace sf;

Ball::Ball(float bX, float bY)
{
	shape.setPosition(bX, bY);
	shape.setFillColor(Color::Red);
	shape.setOrigin(ballRadius, ballRadius);
	shape.setRadius(ballRadius);
}

void Ball::update(int windowWidth, int windowHeight)
{
	shape.move(velocity);
	if (left() < 0) velocity.x = ballVelocity;
	else if (right() > windowWidth) velocity.x = -ballVelocity;
	if (top() < 0) velocity.y = ballVelocity;
	else if (bottom() > windowHeight) velocity.y = -ballVelocity;
}

bool Ball::checkLost(float windowHeight, float windowWidth)
{
	return bottom() > windowHeight;
}



float Ball::x()			{ return shape.getPosition().x; }
float Ball::y()			{ return shape.getPosition().y; }
float Ball::left()		{ return x() - shape.getRadius(); }
float Ball::right()		{ return x() + shape.getRadius(); }
float Ball::top()		{ return y() - shape.getRadius(); }
float Ball::bottom()	{ return y() + shape.getRadius(); }


Paddle::Paddle(float pX, float pY)
{
	shape.setPosition(pX, pY);
	shape.setSize(Vector2f( paddleWidth, paddleHeight ));
	shape.setFillColor(Color::Blue);
	shape.setOrigin(paddleWidth/2, paddleHeight/2);
}
void Paddle::update(int windowWidth, int windowHeight)
{
	shape.move(velocity);

	if (Keyboard::isKeyPressed(Keyboard::Left) && left() > 0) velocity.x = -paddleVelocity;
	else if (Keyboard::isKeyPressed(Keyboard::Right) && right() < windowWidth) velocity.x = paddleVelocity;
	else velocity.x = 0;

}
float Paddle::x()			{ return shape.getPosition().x; }
float Paddle::y()			{ return shape.getPosition().y; }
float Paddle::left()		{ return x() - shape.getSize().x /2.f; }
float Paddle::right()		{ return x() + shape.getSize().x / 2.f; }
float Paddle::top()			{ return y() - shape.getSize().y / 2.f; }
float Paddle::bottom()		{ return y() + shape.getSize().y / 2.f; }

Brick::Brick(float bX, float bY)
{
	shape.setPosition(bX, bY);
	shape.setSize(Vector2f(brickWidth, brickHeight));
	shape.setFillColor(Color::Yellow);
	shape.setOrigin(brickWidth / 2, brickHeight / 2);
}
float Brick::x()			{ return shape.getPosition().x; }
float Brick::y()			{ return shape.getPosition().y; }
float Brick::left()			{ return x() - shape.getSize().x / 2.f; }
float Brick::right()		{ return x() + shape.getSize().x / 2.f; }
float Brick::top()			{ return y() - shape.getSize().y / 2.f; }
float Brick::bottom()		{ return y() + shape.getSize().y / 2.f; }

template<class T1, class T2> bool isCollision(T1& mA,T2& mB)
{
	return (mA.right() >= mB.left() && mA.left() <= mB.right()
		&& mA.bottom() >= mB.top() && mA.top() <= mB.bottom()) || 
		(mB.right() >= mA.left() && mB.left() <= mA.right()
		&& mB.bottom() >= mA.top() && mB.top() <= mA.bottom())
		;
}

void testCollision(Paddle& mPaddle, Ball& mBall)
{
	if (!isCollision(mPaddle, mBall)) return;
	else mBall.velocity.y = -mBall.ballVelocity;

	
	if (mBall.x() < mPaddle.x()) mBall.velocity.x = -mBall.ballVelocity;
	else mBall.velocity.x = mBall.ballVelocity;
	//tutaj mo¿esz dopisaæ, ¿eby odbija³a siê w któr¹œ stronê ...
}
void testCollision(Brick& mBrick, Ball& mBall)
{
	if (!isCollision(mBrick, mBall)) return;
	mBrick.destroyed = true;

	float overlapLeft{ mBall.right() - mBrick.left() };
	float overlapRight{ mBrick.right() - mBall.left() };
	float overlapTop{ mBall.bottom() - mBrick.top() };
	float overlapBottom{ mBrick.bottom() - mBall.top() };

	bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
	bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

	float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
	float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

	if (abs(minOverlapX) < abs(minOverlapY))
		mBall.velocity.x = ballFromLeft ? -mBall.ballVelocity : mBall.ballVelocity;
	else
		mBall.velocity.y = ballFromTop ? -mBall.ballVelocity : mBall.ballVelocity;
}