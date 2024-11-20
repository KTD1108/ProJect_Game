#pragma once
#include "../include/Common.h"

#include "../include/Entity.h"
#include "../include/Player.h"
#include "../include/Enemy.h"
#include "../include/Effect.h"
#include "../include/Button.h"

class Game {
private:
	struct {
		SDL_Renderer* renderer;
		SDL_Window* window;
		SDL_Texture* background;
		bool playing;
		bool pause = 0;
	} app;

	SDL_Texture* shipModel[5];
	SDL_Texture* bulletModel[5];

	SDL_Texture* enemyBoss[3];
	SDL_Texture* bossBullet[3];
	double bossHP, currbossHP;
	int realHealth = 0;
	int fightingBoss;

	Player player;
	Entity playerBullet;
	std::vector <Entity> Bullets;

	Enemy* enemy;
	SDL_Texture* enemyTexture;
	Entity enemyBullet;
	SDL_Texture* enemyBulletTexture;
	int enemySpawnTimer;
	std::vector <Enemy*> Enemies;

	int backgroundX;

	Effect explosion;
	std::vector <std::vector<Effect>> Explosion;
	SDL_Texture* explosionTexture;

	std::vector<Entity> powerUps;
	Entity powerup;

	SDL_Texture* pauseIcon;

	//sound and music
	Mix_Chunk* explosionSound = NULL;
	Mix_Chunk* playerExplosionSound = NULL;
	Mix_Chunk* bulletSound = NULL;
	Mix_Chunk* buttonSound =  NULL;
	Mix_Chunk* powerupSound = NULL;
	Mix_Music* music = NULL;

	//font
	TTF_Font* font = NULL;
	TTF_Font* titleFont = NULL;

	//menu
	Button menuButton[3];
	Button endButton[2];
	Button arrowButton[2];
	Button backButton;
	Button playButton;

	SDL_Texture* Buttons[18];
	SDL_Texture* guide;
	bool playAgain;
	SDL_Texture* lock;
	SDL_Texture* healthbar;
	SDL_Texture* bar;
	SDL_Texture* powerUp1;
	SDL_Texture* powerUp2;

	//score
	int score, highScore;
	bool surpass = 0;
	SDL_Texture* scoreTXT = NULL;
	SDL_Texture* hsTXT = NULL;
	SDL_Texture* LPTXT =  NULL;
	SDL_Texture* stuntTXT = NULL;
	SDL_Texture* requireTXT = NULL;
	SDL_Texture* currTXT = NULL;
	SDL_Texture* pauseTXT = NULL;
	SDL_Rect srclock;
	//string stunt = "STUNT";

	/*SDL_Surface* scoreSurface;
	SDL_Surface* hsSurface;
	SDL_Surface* LPSurface;*/
	std::stringstream scoreText, hScoreText, LPText;



	void initGame();
	void titleScreen();
	bool chooseSpaceship();
	void Guide();
	void initPlayer();
	void presentEntities();
	void getInput();
	void HUD();
	void presentScene();
	void draw(SDL_Texture*, int, int);
	void drawRect(SDL_Texture*, SDL_Rect*, int, int);
	void drawBackground();
	void addExplosion(int, int, int);
	void addPowerUp(int, int, int);
	SDL_Texture* loadTexture(std::string);
	bool detectCollision(int, int, int, int, int, int, int, int);
	void endScreen();
	void prepareScene();
	void Pause();
public:
	void start();
};