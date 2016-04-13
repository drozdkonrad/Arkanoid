#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Ball.h"
#include<Windows.h>
#include <vector>
using namespace sf;
using namespace std;
float	windowWidth = 800, windowHeight = 600;
int		countBricksX = 11, countBricksY = 4;
float	brickWidth = 60, brickHeight = 20;


int main()
{
	Texture tekstura;
	if (!tekstura.loadFromFile("game.png")) return 144;
	Sprite over;
	over.setTexture(tekstura);
	over.setOrigin(over.getGlobalBounds().width / 2, over.getGlobalBounds().height / 2);
	over.setPosition(windowWidth / 2, windowHeight / 2);

	Music music;
	if (!music.openFromFile("sound.wav")) return 144;
	music.setVolume(30);
	music.play();

	SoundBuffer buffer;
	if (!buffer.loadFromFile("fail.wav")) return 144;
	Sound fail(buffer);

	SoundBuffer buffer2;
	if (!buffer2.loadFromFile("failend.wav")) return 144;
	Sound failend(buffer2);
	
	RenderWindow window(VideoMode(windowWidth,windowHeight), "Arkanoid");
	window.setFramerateLimit(170);

	Ball	ball(800, 600);
	Paddle	paddle(windowWidth / 2, windowHeight - 30);
	vector<Brick> bricks;
	
	for (int iX=0; iX < countBricksX; ++iX)
		for (int iY=0; iY < countBricksY; ++iY)
			bricks.emplace_back((iX + 1) * (brickWidth + 3) + 22,
			(iY + 2) * (brickHeight + 3));

	while (window.isOpen())
	{
		window.clear(Color::Black);
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				music.pause();
			}
		}
		if (ball.life <= 0)
		{
			window.clear(Color::Black);
			window.close();
		}
		ball.update(windowWidth,windowHeight);
		paddle.update(windowWidth, windowHeight);
		testCollision(paddle, ball);
		
		for (auto& brick : bricks) testCollision(brick, ball);
		bricks.erase(remove_if(begin(bricks), end(bricks),
			[](const Brick& mBrick){ return mBrick.destroyed; }),
			end(bricks)); //STL ALGORYTM
		window.draw(ball.shape);
		window.draw(paddle.shape);
		for (int i = 0; i < bricks.size(); i++) window.draw(bricks[i].shape);
		if (ball.checkLost(windowHeight, windowWidth)) 
		{
			ball.life--; fail.play();  ball.shape.setPosition(windowWidth / 2, windowHeight / 2); window.clear(Color::Black); window.draw(paddle.shape);
			for (int i = 0; i < bricks.size(); i++) window.draw(bricks[i].shape); window.draw(ball.shape); window.display();  Sleep(2000);
		}
		if (ball.life <= 0){ window.clear(Color::Black); music.pause();  failend.play(); window.draw(over); window.display();  break; }
		window.display();
	}
	Sleep(7000);
}