#include "glGame.h"
#include <stdio.h>
#include "glUtils.h"
#include "glSettings.h"
#include <iostream>

void glGame::Load()
{
	backgroundTexture.loadFromFile(concat(glSettings::ASSETS_PATH, "back1.png"));
	backgroundSprite.setTexture(backgroundTexture);

	gProgressBar.Load();

	heroLeft.Load(0);
	heroRight.Load(1);

	gBoard.Load();
}

void glGame::Init(sf::RenderWindow& window)
{
	gProgressBar.Init();

	//wczytanie mapy
	printf("-----------------------------------------------------\n");
	printf("Zaczynamy nowa gre.\n");
	printf("-----------------------------------------------------\n");

	gBoard.Init(window);

	bullet.Init(200,6200,0.2);

	player1View.setSize(sf::Vector2f(window.getSize().x/2.f, window.getSize().y/1.f));
	player2View.setSize(sf::Vector2f(window.getSize().x/2.f, window.getSize().y)/1.f);
	player1View.setCenter(player1View.getSize().x/2.f, gBoard.getTileManager().getMapHeight()-384);
	player2View.setCenter(player2View.getSize().x/2.f, gBoard.getTileManager().getMapHeight()-384);

	// player 2 (right side of the screen)
	player2View.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1));

	// player 1 (left side of the screen)
	player1View.setViewport(sf::FloatRect(0, 0, 0.5f, 1));

	heroLeft.Init(100, gBoard.getTileManager().getMapHeight() - 64 - heroLeft.getHeight(), player1View, glHero::PLAYER::FST);
	heroRight.Init(500, gBoard.getTileManager().getMapHeight() - 64 - heroRight.getHeight(), player2View, glHero::PLAYER::SND);

	playerLeftOnLadder = playerRightOnLadder = false;

	gameState = GAME_STATE::MENU;
	musicObject.HandleMusic();
	isMenu = false;
	isPlaying = false;
	isGameOver = false;
	isWin = false;
}

bool glGame::Win()
{	
	bool win = false;

	if(heroLeft.position.y < 50 && heroRight.position.y < 50){
		win = true;}

	return win;
}

bool glGame::GameOver()
{	
	bool gameOver = false;

	if(heroLeft.death == true && heroRight.death == true){
		gameOver = true;}

	return gameOver;
}

void glGame::GameStateWin()
{
	gameState = GAME_STATE::WIN;
}

void glGame::GameStateGameOver()
{
	gameState = GAME_STATE::GAMEOVER;
}

void glGame::Update()
{	
	glTiledLoader& tileManager = gBoard.getTileManager();

	if (!heroLeft.death)
	{
		// player 1 movement


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			float x = heroLeft.position.x+heroLeft.getWidth()/2;
			float y = heroLeft.position.y+heroLeft.getHeight()/2;
			int a,b;
			gBoard.getTileManager().getTileCoords(x,y,heroLeft.playerId,a,b);
			gBoard.getTileManager().setActive(a,b);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			heroLeft.Update(glHero::LEFT);
			if(gBoard.getTileManager().intersectsWithWallVertically(heroLeft))
				heroLeft.UpdateReverse(glHero::LEFT);
			playerLeftOnLadder = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && tileManager.intersectsWithLadder(heroLeft) )
		{
			heroLeft.Update(glHero::CLIMBUP);
			playerLeftOnLadder = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			heroLeft.Update(glHero::RIGHT);
			if(gBoard.getTileManager().intersectsWithWallVertically(heroLeft))
				heroLeft.UpdateReverse(glHero::RIGHT);
			playerLeftOnLadder = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && tileManager.intersectsWithLadder(heroLeft))
		{
			heroLeft.Update(glHero::CLIMBDOWN);
			playerLeftOnLadder = true;
		}
	
		if (heroLeft.position.x < 0){
			heroLeft.Update(glHero::LEFTBORDER);
		}
		if (heroLeft.position.x > player1View.getSize().x - heroLeft.getWidth()){
			heroLeft.Update(glHero::RIGHTBORDER);
		}

		if(!playerLeftOnLadder)
		{
			// gravity
			heroLeft.Update(glHero::FALL);
			if(gBoard.getTileManager().intersectsWithWall(heroLeft))
				heroLeft.UpdateReverse(glHero::FALL);
		}
	} else
		heroLeft.Update(glHero::NONE);

	// player 2 movement

	if (!heroRight.death)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			heroRight.Update(glHero::LEFT);
			if(gBoard.getTileManager().intersectsWithWallVertically(heroRight))
				heroRight.UpdateReverse(glHero::LEFT);
			playerRightOnLadder = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && tileManager.intersectsWithLadder(heroRight))
		{
			heroRight.Update(glHero::CLIMBUP);
			playerRightOnLadder = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			heroRight.Update(glHero::RIGHT);
			if(gBoard.getTileManager().intersectsWithWallVertically(heroRight))
				heroRight.UpdateReverse(glHero::RIGHT);
			playerRightOnLadder = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && tileManager.intersectsWithLadder(heroRight))
		{
			heroRight.Update(glHero::CLIMBDOWN);
			playerRightOnLadder = true;
		}
	
		if(!playerRightOnLadder)
		{
			// gravity
			heroRight.Update(glHero::FALL);
			if(gBoard.getTileManager().intersectsWithWall(heroRight))
				heroRight.UpdateReverse(glHero::FALL);
		}
	} else
		heroRight.Update(glHero::NONE);

	// progress bar
	gProgressBar.Update(heroLeft.position.y,heroRight.position.y);

	bullet.Update();


	// updating the camera
	float y1 = heroLeft.position.y + heroLeft.getHeight() / 2;
	float y2 = heroRight.position.y + heroRight.getHeight() / 2;

	if (y1 > gBoard.getTileManager().getMapHeight() - 384)
		y1 = gBoard.getTileManager().getMapHeight() - 384;
	if (y2 > gBoard.getTileManager().getMapHeight() - 384)
		y2 = gBoard.getTileManager().getMapHeight() - 384;

	if (y1 < 384)
		y1 = 384;
	if (y2 < 384)
		y2 = 384;

	player1View.setCenter(player1View.getCenter().x, y1);
	player2View.setCenter(player2View.getCenter().x, y2);

	// Death in lava
	if(heroRight.position.y + heroRight.getHeight() > gProgressBar.lava){
		heroRight.death = true;}
	if(heroLeft.position.y + heroLeft.getHeight() > gProgressBar.lava){
		heroLeft.death = true;}
}

void glGame::Draw(sf::RenderWindow& graphics)
{		
	graphics.setView(graphics.getDefaultView());

	switch(gameState)
	{
		case GAME_STATE::MENU:
			if(!isMenu){
				musicObject.StopAll();
				musicObject.MusicMenu.play();
				isMenu = true;
			}
			chosenOption = mainMenu.Show(graphics, graphics.getSize().x, graphics.getSize().y);
			switch(chosenOption) 
			{
				case glMainMenu::Exit:
					graphics.close();
					break;
				case glMainMenu::Play:
					gameState = GAME_STATE::GAMEPLAY;
					break;
			}
		case GAME_STATE::GAMEPLAY:
			if(!isPlaying){
				musicObject.StopAll();
				musicObject.MusicLevel1.play();
				isPlaying = true;
			}
			graphics.setView(player1View);
			gBoard.Draw(graphics, player1View.getCenter(), player1View.getSize(), true);
			gProgressBar.DrawLava(graphics,true);
			bullet.Draw(graphics);
			heroLeft.Draw(graphics);

			graphics.setView(player2View);
			gBoard.Draw(graphics, player2View.getCenter(), player2View.getSize(), false);
			gProgressBar.DrawLava(graphics,false);
			heroRight.Draw(graphics);

			graphics.setView(graphics.getDefaultView());
			gProgressBar.Draw(graphics);

			break;
		case GAME_STATE::WIN:
			if(!isWin){
				musicObject.StopAll();
				isWin = true;
			}
			break;
		case GAME_STATE::GAMEOVER:
			if(!isGameOver){
				musicObject.StopAll();
				musicObject.MusicGameOver.play();
				isGameOver = true;
			}
			DrawGameOver(graphics);
			break;
	}
	
}

void glGame::DrawGameOver(sf::RenderWindow& graphics)
{
	gameOverBackground.loadFromFile(concat(glSettings::ASSETS_PATH, "gameOver.jpg"));
	gameOverBackgroundSprite.setTexture(gameOverBackground);
	gameOverBackgroundSprite.setOrigin(gameOverBackground.getSize().x/2., gameOverBackground.getSize().y/2.);
	gameOverBackgroundSprite.setPosition(graphics.getSize().x/2., graphics.getSize().y/2.);

	sf::View view(sf::FloatRect(0, 0, graphics.getSize().x, graphics.getSize().y));
	graphics.setView(view);

	graphics.clear(sf::Color(0,0,0));
	graphics.draw(gameOverBackgroundSprite);
}

void glGame::HandleEvent(sf::Event event)
{
	if(event.type == event.KeyPressed)
	{
		/*sf::Keyboard::Key key = event.key.code;
		if(key == sf::Keyboard::Left)
		{
		}
		else if(key == sf::Keyboard::Up)
		{
			player1View.move(0.f, 2.f);
		}
		else if(key == sf::Keyboard::Right)
		{			
		}
		else if(key == sf::Keyboard::Down)
		{
			player1View.move(0.f, -2.f);
		}
		else if(key == sf::Keyboard::A)
		{
		}
		else if(key == sf::Keyboard::W)
		{
			player2View.move(0.f, 2.f);
		}
		else if(key == sf::Keyboard::D)
		{
		}
		else if(key == sf::Keyboard::S)
		{
			player2View.move(0.f, -2.f);
		}*/
	}
}

void glGame::CheckColisions()
{
	sf::Vector2f mHeroSadPos =  mHeroSad.mActiveSprite.GetPosition();
	sf::Vector2f mHeroHappyPos = mHeroHappy.mActiveSprite.GetPosition();
	float mHeroSadWidth  = mHeroSad.mActiveSprite.GetSize().x;
	float mHeroSadHeight = mHeroSad.mActiveSprite.GetSize().y;
	float mHeroHappyWidth  = mHeroHappy.mActiveSprite.GetSize().x;
	float mHeroHappyHeight = mHeroHappy.mActiveSprite.GetSize().y;
	
	std::vector<seEgg>::iterator it;
	for (int i = 0; i < mEggsVec.size(); ++i) {
		mEggsVec.at(i).Step();

		if(!mEggsVec.at(i).mDying)
		{
			sf::Vector2f positions = mEggsVec.at(i).mSprite.GetPosition();
			float height = mEggsVec.at(i).mSprite.GetSize().y;
			float width = mEggsVec.at(i).mSprite.GetSize().x;
			float srodekPostaciSad = mHeroSadPos.x + mHeroSadWidth/2;
			float srodekPostaciHappy = mHeroHappyPos.x + mHeroHappyWidth/2;
			float doljajka = mEggsVec.at(i).mSprite.GetPosition().y + height/2;
			float diffHappy;
			float diffSad;
			bool exit =false;

			if (srodekPostaciSad>positions.x){
				diffSad=srodekPostaciSad-positions.x;
			}else{
				diffSad=positions.x-srodekPostaciSad;
			}

			if (srodekPostaciHappy>positions.x){
				diffHappy=srodekPostaciHappy-positions.x;
			}else{
				diffHappy=positions.x-srodekPostaciHappy;
			}

			if (doljajka>(viewHeight-25.0f)){
				cout<<"jajko spadlo"<<endl;	

					playSound("FallEgg_0");

				if (mEggsVec.at(i).mType<=1){
					lives--;
					combo=1;
				}
				mEggsVec.at(i).mDying = true;
				mEggsVec.at(i).mFallen = true;
			}else{
				if (diffSad<(mHeroSadWidth/2+width/2+3) && (doljajka>mHeroSadPos.y)){
					if(mEggsVec.at(i).mType==0 &&  mHeroSad.counter<5){
						cout<<"sad zlapal"<<endl;
						playSound("FallEgg_1");
						mEggsVec.at(i).mDying = true;
						mScore.AddScore(combo*basicScores);
						combo++;
						mHeroSad.counter++;	
						exit=true;
					}else if (mEggsVec.at(i).mType==3){
						cout<<"sad dodaje zycie"<<endl;
						if (lives<10)lives++;
						mEggsVec.at(i).mDying = true;
						exit=true;
					}
				}
				if (!exit && diffHappy<(mHeroHappyWidth/2+width/2+3) && (doljajka>mHeroHappyPos.y)){
					if(mEggsVec.at(i).mType==1 &&  mHeroHappy.counter<5){
						cout<<"happy zlapal"<<endl;
						playSound("CatchEgg_1");
						mEggsVec.at(i).mDying = true;
						mScore.AddScore(combo*basicScores);
						combo++;
						mHeroHappy.counter++;
					}else if(mEggsVec.at(i).mType==3){
						cout<<"happy dodaje zycie"<<endl;
						if (lives<10)lives++;
						mEggsVec.at(i).mDying = true;
					}
				}
			}
			mCombo.SetCurrentScore(combo);

		}
		else if(mEggsVec.at(i).mScale >= 1)
		{
			mEggsVec.erase(mEggsVec.begin() + i);
			--i;
		}
	}
}