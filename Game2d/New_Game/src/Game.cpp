#include "../include/Game.h"
using namespace std;
 // Khởi tạo game và các thành phần cần thiết
void Game::start() {
	initGame();
	while (true) {
		if (!playAgain) {
			titleScreen();
		}
		while (app.playing) {
			prepareScene();
			drawBackground();

			if (player.getHealth()) {
				getInput();
			}

			if (!app.pause) {
				presentEntities();
				HUD();
			}
			else {
				Pause();
			}

			presentScene();
		}
		endScreen();
	}
}


void Game::initGame() {
	// Khởi tạo SDL với các module Video và Audio
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		cout << "Could not initialize SDL: " << SDL_GetError() << endl;
		exit(-1);
	}
	 // Tạo cửa sổ cho trò chơi
	app.window = SDL_CreateWindow("Galactic Skyfire", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!app.window) {
		cout << "Could not create window : " << SDL_GetError() << endl;
		exit(-1);
	}
	// Tải logo và thiết lập làm biểu tượng của cửa sổ
	SDL_Surface* sf = IMG_Load("../resource/gfx/other/logo.png");
	SDL_SetWindowIcon(app.window, sf);
	// Tạo renderer để vẽ lên cửa sổ
	app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
	if (!app.renderer) {
		cout << "Could not create renderer : " << SDL_GetError() << endl;
		exit(-1);
	}
	// Khởi tạo SDL Image (hỗ trợ định dạng ảnh PNG và JPG)
	if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
		cout << "Could not initialize SDL Image : " << SDL_GetError() << endl;
		exit(-1);
	}
	// Khởi tạo SDL Mixer để xử lý âm thanh
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		cout << "Could not initialize SDL Mixer : " << SDL_GetError() << endl;
		exit(-1);
	}
	// Khởi tạo SDL TTF để xử lý phông chữ
	if (TTF_Init() == -1) {
		cout << "Could not initialize SDL TTF : " << SDL_GetError() << endl;
		exit(-1);
	}
	// Cấp phát bộ nhớ cho các kênh âm thanh
	Mix_AllocateChannels(8);
	// Khởi tạo các giá trị ban đầu
	backgroundX = 0;

	app.playing = false;
	app.background = loadTexture("../resource/gfx/other/background.png");

	// Khởi tạo các đối tượng đạn của người chơi
	playerBullet.setDX(PLAYER_BULLET_SPEED);
	playerBullet.setHealth(1);
	enemyBulletTexture = loadTexture("../resource/gfx/bulletsprites/alienBullet.png");
	enemyTexture = loadTexture("../resource/gfx/spaceship/quai.png");
	 // Tải các nhạc nền và hiệu ứng âm thanh
	music = Mix_LoadMUS("xx.mp3");
	explosionSound = Mix_LoadWAV("../resource/sound/enemyExplosion.ogg");
	playerExplosionSound = Mix_LoadWAV("../resource/sound/explosionSound.wav");
	buttonSound = Mix_LoadWAV("../resource/sound/buttonSound.mp3");
	bulletSound = Mix_LoadWAV("../resource/sound/bulletSound.ogg");
	powerupSound = Mix_LoadWAV("../resource/sound/earnPowerUp.ogg");
	// Tải hình ảnh explosion và phông chữ
	explosionTexture = loadTexture("../resource/gfx/other/explosion.png");
	font = TTF_OpenFont("../resource/font/Goldeneye.ttf", 28);
	titleFont = TTF_OpenFont("../resource/font/Ghost.ttf", 90);
	Mix_PlayMusic(music, -1);
	// Tải các mẫu tàu vũ trụ của người chơi
	shipModel[0] = loadTexture("../resource/gfx/spaceship/maybay1.png");
	shipModel[1] = loadTexture("../resource/gfx/spaceship/maybay2.png");
	shipModel[2] = loadTexture("../resource/gfx/spaceship/maybay3.png");
	shipModel[3] = loadTexture("../resource/gfx/spaceship/maybay4.png");
	shipModel[4] = loadTexture("../resource/gfx/spaceship/maybay5.png");
	// Tải các mẫu đạn của người chơi
	bulletModel[0] = loadTexture("../resource/gfx/bulletsprites/white.png");
	bulletModel[1] = loadTexture("../resource/gfx/bulletsprites/yellow-white.png");
	bulletModel[2] = loadTexture("../resource/gfx/bulletsprites/blue.png");
	bulletModel[3] = loadTexture("../resource/gfx/bulletsprites/green.png");
	bulletModel[4] = loadTexture("../resource/gfx/bulletsprites/rship.png");
	// Tải các mẫu boss của kẻ thù
	enemyBoss[0] = loadTexture("../resource/gfx/spaceship/boss1.png");
	enemyBoss[1] = loadTexture("../resource/gfx/spaceship/boss2.png");
	enemyBoss[2] = loadTexture("../resource/gfx/spaceship/boss3.png");
	// Tải các mẫu đạn của boss
	bossBullet[0] = loadTexture("../resource/gfx/bulletsprites/enemyBoss1.png");
	bossBullet[1] = loadTexture("../resource/gfx/bulletsprites/enemyBoss2.png");
	bossBullet[2] = loadTexture("../resource/gfx/bulletsprites/enemyBoss3.png");

	// Tải các texture cho các nút giao diện
	// Các nút được phân loại theo trạng thái (trạng thái bình thường và khi hover)
	Buttons[0] = loadTexture("../resource/gfx/gui/start1.png");
	Buttons[2] = loadTexture("../resource/gfx/gui/guide_1.png");
	Buttons[4] = loadTexture("../resource/gfx/gui/exit_1.png");
	Buttons[6] = loadTexture("../resource/gfx/arrow/left.png");
	Buttons[8] = loadTexture("../resource/gfx/arrow/right.png");
	Buttons[10] = loadTexture("../resource/gfx/gui/back_1.png");
	Buttons[12] = loadTexture("../resource/gfx/gui/menu_1.png");
	Buttons[14] = loadTexture("../resource/gfx/gui/playagain_1.png");
	Buttons[16] = loadTexture("../resource/gfx/gui/play_1.png");


	Buttons[1] = loadTexture("../resource/gfx/gui/start2.png");
	Buttons[3] = loadTexture("../resource/gfx/gui/guide_2.png");
	Buttons[5] = loadTexture("../resource/gfx/gui/exit_2.png");
	Buttons[7] = loadTexture("../resource/gfx/arrow/hoverleft.png");
	Buttons[9] = loadTexture("../resource/gfx/arrow/hoverright.png");
	Buttons[11] = loadTexture("../resource/gfx/gui/back_2.png");
	Buttons[13] = loadTexture("../resource/gfx/gui/menu_2.png");
	Buttons[15] = loadTexture("../resource/gfx/gui/playagain_2.png");
	Buttons[17] = loadTexture("../resource/gfx/gui/play_2.png");
	// Cài đặt vị trí cho các nút menu
	int w, h;
	menuButton[0].setTexture(Buttons[0]);
	menuButton[1].setTexture(Buttons[2]);
	menuButton[2].setTexture(Buttons[4]);
	for (int i = 0; i < 3; i++) {
		menuButton[i].setX(475); // Vị trí ngang của nút
		menuButton[i].setY(SCREEN_WIDTH / 4 + 25);	// Vị trí dọc của nút
		SDL_QueryTexture(menuButton[i].getTexture(), NULL, NULL, &w, &h);
		menuButton[i].setW(w);	// Chiều rộng của nút
		menuButton[i].setH(h);	// Chiều cao của nút

		if (i) {
			menuButton[i].setY(menuButton[i - 1].getY() + menuButton[i - 1].getH() + 25);  
		}
	}
	// Cài đặt các nút mũi tên
	arrowButton[0].setTexture(Buttons[6]);
	arrowButton[1].setTexture(Buttons[8]);
	for (int i = 0; i < 2; i++) {
		arrowButton[i].setX(300);
		arrowButton[i].setY(300);
		SDL_QueryTexture(menuButton[i].getTexture(), NULL, NULL, &w, &h);
		arrowButton[i].setW(w);
		arrowButton[i].setH(h);
		if (i) {
			arrowButton[i].setX(arrowButton[i - 1].getX() + 575); // Khoảng cách giữa các nút mũi tên
		}
	}
	 // Cài đặt nút "Back" trong menu
	backButton.setY(600);
	backButton.setX(450);
	backButton.setTexture(Buttons[10]);
	SDL_QueryTexture(backButton.getTexture(), NULL, NULL, &w, &h);
	backButton.setW(w);
	backButton.setH(h);
	// Cài đặt nút "End Game" (Kết thúc trò chơi) với các vị trí và kích thước
	endButton[0].setTexture(Buttons[12]);
	endButton[1].setTexture(Buttons[14]);
	for (int i = 0; i < 2; i++) {
		endButton[i].setX(SCREEN_WIDTH / 4 + 25);
		endButton[i].setY(500);
		SDL_QueryTexture(endButton[i].getTexture(), NULL, NULL, &w, &h);
		endButton[i].setW(w);
		endButton[i].setH(h);
		if (i) {
			endButton[i].setX(endButton[i - 1].getX() + endButton[i - 1].getW() + 50);
		}
	}
	// Biến kiểm tra xem người chơi có muốn chơi lại hay không
	playAgain = false;
	// Tải các biểu tượng và hình ảnh khác vào trò chơi
	pauseIcon = loadTexture("../resource/gfx/other/pauseIcon.png");
	lock = loadTexture("../resource/gfx/other/lock.png");
	guide = loadTexture("../resource/gfx/other/guide.png");
	healthbar = loadTexture("../resource/gfx/other/healthbar.png");
	bar = loadTexture("../resource/gfx/other/bar.png");
	powerUp1 = loadTexture("../resource/gfx/other/LP.png");
	powerUp2 = loadTexture("../resource/gfx/other/enhanceATK.png");
	// Cài đặt kích thước đồng hồ
	srclock.w = srclock.h = 200;

	// Các biến liên quan đến trạng thái của trò chơi
	fightingBoss = 0;
	enemySpawnTimer = 60; // Hẹn giờ để sinh kẻ thù
	score = 0; // Điểm số hiện tại

	// Tải điểm cao từ file scores.txt
	ifstream fin("../data/scores.txt");
	if (!fin.is_open()) {
		std::cout << "Can't open file scores.txt";
		exit(-1);
	}
	fin >> highScore;
	fin.close();
}

void Game::titleScreen() {
	SDL_Event e;
	// Các chuỗi chứa tiêu đề và hướng dẫn
	string title1 = "Galactic ", title2 = "SkyFire";
	string instruct = "Press Enter to protect the galaxy!";

	// Tạo các đối tượng surface từ các chuỗi văn bản với màu sắc
	SDL_Surface* titleSpace = TTF_RenderText_Solid(titleFont, title1.c_str(), { 135, 206, 235, 0 });
	SDL_Texture* tSTXT = SDL_CreateTextureFromSurface(app.renderer, titleSpace);

	SDL_Surface* titleShooter = TTF_RenderText_Solid(titleFont, title2.c_str(), { 135, 206, 235, 0 });
	SDL_Texture* tShTXT = SDL_CreateTextureFromSurface(app.renderer, titleShooter);

	SDL_Surface* pressSf = TTF_RenderText_Solid(font, instruct.c_str(), { 135, 206, 235, 0 });
	SDL_Texture* pressTXT = SDL_CreateTextureFromSurface(app.renderer, pressSf);
	// Vòng lặp chính của màn hình tiêu đề
	while (true) {
		drawBackground();
		draw(tSTXT, SCREEN_WIDTH/4, 100);
		draw(tShTXT, SCREEN_WIDTH/4 + 200, 200);
		draw(pressTXT, SCREEN_WIDTH / 4 + 75, 300);
		for (int i = 0; i < 3; i++) {
			draw(menuButton[i].getTexture(), menuButton[i].getX(), menuButton[i].getY());
		}
		presentScene(); // Hiển thị cảnh lên màn hình

		int x, y;
		// Quét sự kiện từ người dùng
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYDOWN:
				if (e.key.keysym.scancode == SDL_SCANCODE_SPACE) {
					if (chooseSpaceship()) return;
				}
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					exit(0);
				}
				if (e.key.keysym.scancode == SDL_SCANCODE_M) {
					if (Mix_PausedMusic()) {
						Mix_ResumeMusic();
					}
					else {
						Mix_PauseMusic();
					}
				}
				break;
			// Lấy vị trí chuột
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&x, &y);
				for (int i = 0; i < 3; i++) {
					// Kiểm tra nếu chuột hover lên nút
					if (x >= menuButton[i].getX() && x <= menuButton[i].getX() + menuButton[i].getW()
						&& y >= menuButton[i].getY() && y <= menuButton[i].getY() + menuButton[i].getH()) {
							// Thay đổi trạng thái hover và texture nút
						if (!menuButton[i].isHovered()) {
							menuButton[i].setHovered(true);
							if (i == 0) menuButton[i].setTexture(Buttons[1]);
							if (i == 1) menuButton[i].setTexture(Buttons[3]);
							if (i == 2) menuButton[i].setTexture(Buttons[5]);
						}
					}
					// Nếu chuột không hover lên nút, đổi lại texture của nút
					else if (menuButton[i].isHovered()) {
						menuButton[i].setHovered(false);
						if (i == 0) menuButton[i].setTexture(Buttons[0]);
						if (i == 1) menuButton[i].setTexture(Buttons[2]);
						if (i == 2) menuButton[i].setTexture(Buttons[4]);
					}
				}
				break;
			// Lấy vị trí chuột khi nhấn chuột
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&x, &y);
				for (int i = 0; i < 3; ++i) {
					if (x >= menuButton[i].getX() && x <= menuButton[i].getX() + menuButton[i].getW()) {
						// Kiểm tra vị trí chuột có nằm trong vùng của nút
						if (y >= menuButton[i].getY() && y <= menuButton[i].getY() + menuButton[i].getH()) {
							// Phát âm thanh khi nhấn nút
							Mix_PlayChannel(-1, buttonSound, 0);
							if (i == 0) {
								if (chooseSpaceship()) return;
							}
							else if (i == 1) {
								Guide();
							}
							else {
								exit(0);
							}
						}
					}
				}
				break;
			}
		}
	}
}


bool Game::chooseSpaceship() {
	SDL_Event e;
	int w, h;
	// Cài đặt vị trí và texture cho nút "Back"
	backButton.setY(550);
	backButton.setX(350);
	backButton.setTexture(Buttons[10]);
	SDL_QueryTexture(backButton.getTexture(), NULL, NULL, &w, &h);
	backButton.setW(w);
	backButton.setH(h);
	// Cài đặt vị trí và texture cho nút "Play"
	playButton.setY(550);
	playButton.setX(350 + backButton.getW() + 50);
	playButton.setTexture(Buttons[16]);
	SDL_QueryTexture(playButton.getTexture(), NULL, NULL, &w, &h);
	playButton.setW(w);
	playButton.setH(h);
	// Hiển thị thông điệp hướng dẫn người chơi chọn tàu vũ trụ
	string instruct = "Choose your spaceship";
	SDL_Surface* insSf = TTF_RenderText_Solid(font, instruct.c_str(), { 135, 206, 235, 0 });
	SDL_Texture* insTXT = SDL_CreateTextureFromSurface(app.renderer, insSf);

	int pos = 0;
	SDL_Rect src;
	src.w = src.h = 300;  // Kích thước của hình tàu vũ trụ

	while (true) {
		// Vẽ nền và các đối tượng UI
		drawBackground();
		draw(insTXT, SCREEN_WIDTH / 4 + 150, 100); // Vẽ hướng dẫn người chơi
		draw(backButton.getTexture(), backButton.getX(), backButton.getY());
		draw(playButton.getTexture(), playButton.getX(), playButton.getY());
		// Kiểm tra điều kiện mở khóa tàu vũ trụ
		if (pos == 0 || highScore >= pos * 25 + (pos - 1) * (pos - 1) * 5) {
			drawRect(shipModel[pos], &src, SCREEN_WIDTH / 4 + 175, 200);
		}
		else {
			string unlockRequire = "You need at least " + to_string(pos * 25 + (pos - 1) * (pos - 1) * 5) + " points to unlock.";
			string currHS = "Your current score: " + to_string(highScore);
			// Vẽ thông báo yêu cầu điểm và điểm hiện tại
			SDL_Surface* requireSf = TTF_RenderText_Solid(font, unlockRequire.c_str(), { 135, 206, 235, 0 });
			SDL_DestroyTexture(requireTXT);
			requireTXT = SDL_CreateTextureFromSurface(app.renderer, requireSf);
			SDL_FreeSurface(requireSf);

			SDL_Surface* currSf = TTF_RenderText_Solid(font, currHS.c_str(), { 135, 206, 235, 0 });
			SDL_DestroyTexture(currTXT);
			currTXT = SDL_CreateTextureFromSurface(app.renderer, currSf);
			SDL_FreeSurface(currSf);
			// Vẽ thông tin về yêu cầu mở khóa và điểm số
			draw(requireTXT, SCREEN_WIDTH / 4 + 60, 425);
			draw(currTXT, SCREEN_WIDTH / 4 + 150, 470); 
			drawRect(lock, &srclock, SCREEN_WIDTH / 4 + 225, 200);   // Vẽ hình ảnh khóa
		} 

		// Vẽ các nút điều khiển mũi tên
		for (int i = 0; i < 2; i++) {
			draw(arrowButton[i].getTexture(), arrowButton[i].getX(), arrowButton[i].getY());
		}
		presentScene();  // Hiển thị màn hình

		int x, y;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYDOWN:
				if (e.key.keysym.scancode == SDL_SCANCODE_SPACE) {
					// Khi người chơi nhấn SPACE, chọn tàu vũ trụ nếu đã mở khóa
					if (pos == 0 || highScore >= pos * 25 + (pos - 1) * (pos - 1) * 5) {
						player.setTexture(shipModel[pos]);
						playerBullet.setTexture(bulletModel[pos]);
						// Cài đặt các thông số cho tàu vũ trụ (sát thương, tốc độ tái nạp)
						if (pos < 2) player.setDamageRate(1);
						else if (pos < 4) player.setDamageRate(3);
						else player.setDamageRate(5);

						if (pos % 2 == 0) player.setReloadRate(5);
						else player.setReloadRate(4);
						if (pos == 4) player.setReloadRate(3);

						app.playing = true;
						initPlayer();
						return true;
					}
				}
				if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
					pos = (pos + 1) % 5; // Di chuyển qua tàu vũ trụ tiếp theo
				}
				if (e.key.keysym.scancode == SDL_SCANCODE_LEFT) {
					if (pos > 0) pos = (pos - 1) % 5; // Di chuyển về tàu vũ trụ trước đó
					else pos = 4;
				}
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					exit(0); // Thoát nếu nhấn ESC
				}
				if (e.key.keysym.scancode == SDL_SCANCODE_M) {
					if (Mix_PausedMusic()) {
						Mix_ResumeMusic(); // Dừng hoặc tiếp tục nhạc
					}
					else {
						Mix_PauseMusic();
					}
				}
				break;

			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&x, &y); // Xử lý sự kiện chuột di chuyển để thay đổi texture của các nút khi di chuột qua
				for (int i = 0; i < 2; i++) {
					if (x >= arrowButton[i].getX() && x <= arrowButton[i].getX() + arrowButton[i].getW()
						&& y >= arrowButton[i].getY() && y <= arrowButton[i].getY() + arrowButton[i].getH()) {
						if (!arrowButton[i].isHovered()) {
							arrowButton[i].setHovered(true);
							if (i == 0) arrowButton[i].setTexture(Buttons[7]);
							if (i == 1) arrowButton[i].setTexture(Buttons[9]);
						}
					}
					else if (arrowButton[i].isHovered()) {
						arrowButton[i].setHovered(false);
						if (i == 0) arrowButton[i].setTexture(Buttons[6]);
						if (i == 1) arrowButton[i].setTexture(Buttons[8]);
					}
				}
				// Xử lý hover cho nút "Back"
				if (x >= backButton.getX() && x <= backButton.getX() + backButton.getW()
					&& y >= backButton.getY() && y <= backButton.getY() + backButton.getH()) {
					if (!backButton.isHovered()) {
						backButton.setHovered(true);
						backButton.setTexture(Buttons[11]);
					}
				}
				else if (backButton.isHovered()) {
					backButton.setHovered(false);
					backButton.setTexture(Buttons[10]);
				}
				// Xử lý hover cho nút "Play"
				if (x >= playButton.getX() && x <= playButton.getX() + playButton.getW()
					&& y >= playButton.getY() && y <= playButton.getY() + playButton.getH()) {
					if (!playButton.isHovered()) {
						playButton.setHovered(true);
						playButton.setTexture(Buttons[17]);
					}
				}
				else if (playButton.isHovered()) {
					playButton.setHovered(false);
					playButton.setTexture(Buttons[16]);
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&x, &y); // Xử lý sự kiện chuột nhấn để chọn tàu vũ trụ hoặc nút "Back"/"Play"
				for (int i = 0; i < 2; ++i) {
					if (x >= arrowButton[i].getX() && x <= arrowButton[i].getX() + arrowButton[i].getW()) {
						if (y >= arrowButton[i].getY() && y <= arrowButton[i].getY() + arrowButton[i].getH()) {
							Mix_PlayChannel(-1, buttonSound, 0);   // Phát âm thanh nút nhấn
							if (i == 0) {
								if (pos > 0) pos = (pos - 1) % 5;
								else pos = 4;
							}
							else {
								pos = (pos + 1) % 5;
							}
						}
					}
				}
				// Xử lý nhấn nút "Back"
				if (x >= backButton.getX() && x <= backButton.getX() + backButton.getW()
					&& y >= backButton.getY() && y <= backButton.getY() + backButton.getH()) {
					Mix_PlayChannel(-1, buttonSound, 0);
					return false;
				}
				// Xử lý nhấn nút "Play"
				if (x >= playButton.getX() && x <= playButton.getX() + playButton.getW()
					&& y >= playButton.getY() && y <= playButton.getY() + playButton.getH()) {
					Mix_PlayChannel(-1, buttonSound, 0);
					if (pos == 0 || highScore >= pos * 25 + (pos - 1) * (pos - 1) * 5) {
						player.setTexture(shipModel[pos]);
						playerBullet.setTexture(bulletModel[pos]);

						if (pos < 2) player.setDamageRate(1);
						else if (pos < 4) player.setDamageRate(3);
						else player.setDamageRate(5);

						if (pos % 2 == 0) player.setReloadRate(5);
						else player.setReloadRate(4);
						if (pos == 4) player.setReloadRate(3);

						app.playing = true;
						initPlayer();
						return true;
					}
				}

				break;
			}
		}
	}

}

void Game::Guide() {
	SDL_Event e;
	backButton.setY(600);
	backButton.setX(450);
	backButton.setTexture(Buttons[10]);
	int w, h;
	SDL_QueryTexture(backButton.getTexture(), NULL, NULL, &w, &h);
	backButton.setW(w);
	backButton.setH(h);


	int x, y;
	while (true) {
		drawBackground();
		draw(backButton.getTexture(), backButton.getX(), backButton.getY());
		draw(guide, 0, 25);
		presentScene();

		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					return;
				}
				if (e.key.keysym.scancode == SDL_SCANCODE_M) {
					if (Mix_PausedMusic()) {
						Mix_ResumeMusic();
					}
					else {
						Mix_PauseMusic();
					}
				}
				break;
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&x, &y);
				if (x >= backButton.getX() && x <= backButton.getX() + backButton.getW()
				&& y >= backButton.getY() && y <= backButton.getY() + backButton.getH()) {
					if (!backButton.isHovered()) {
						backButton.setHovered(true);
						backButton.setTexture(Buttons[11]);
					}
				} else if (backButton.isHovered()) {
					backButton.setHovered(false);
					backButton.setTexture(Buttons[10]);
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&x, &y);
				if (x >= backButton.getX() && x <= backButton.getX() + backButton.getW()
				&& y >= backButton.getY() && y <= backButton.getY() + backButton.getH()) {
					Mix_PlayChannel(-1, buttonSound, 0);
					return;
				}
				break;
			}
		}
	}
}


void Game::endScreen() {
	SDL_Event e;
	string gameover = "GAME OVER"; // Nội dung hiển thị khi kết thúc game
	string endScore = "Your score: " + to_string(score); // Hiển thị điểm số của người chơi
	string congrat = "Congrat. You achieve new high score!"; // Thông báo nếu người chơi đạt điểm cao nhất
	// Tạo surface và texture cho các chuỗi văn bản (game over, điểm số, chúc mừng)
	SDL_Surface* endSf = TTF_RenderText_Solid(titleFont, gameover.c_str(), { 255, 0, 0, 0 });
	SDL_Texture* endTXT = SDL_CreateTextureFromSurface(app.renderer, endSf);

	SDL_Surface* scoreSf = TTF_RenderText_Solid(font, endScore.c_str(), { 255, 255, 255, 0 });
	SDL_Texture* scoreTXT = SDL_CreateTextureFromSurface(app.renderer, scoreSf);

	SDL_Surface* congratSf = TTF_RenderText_Solid(font, congrat.c_str(), { 232, 46, 46, 0 });
	SDL_Texture* congratTXT = SDL_CreateTextureFromSurface(app.renderer, congratSf);
	// Nếu người chơi đã đạt điểm cao nhất, lưu điểm cao mới vào file
	if (surpass) {
		ofstream fout("scores.txt");
		fout << highScore << endl;
		fout.close();
	}

	while (true) {
		drawBackground();
		draw(endTXT, SCREEN_WIDTH / 4, 200);
		draw(scoreTXT, SCREEN_WIDTH / 4 + 225, 350);
		if (surpass) {
			draw(congratTXT, SCREEN_WIDTH / 4 + 100, 400);
		}

		for (int i = 0; i < 2; i++) {
			draw(endButton[i].getTexture(), endButton[i].getX(), endButton[i].getY());
		}
		presentScene();

		int x, y;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_QUIT:
					exit(0);
					break;

				case SDL_KEYDOWN:
					if (e.key.keysym.scancode == SDL_SCANCODE_SPACE) {
						enemySpawnTimer = 60;
						surpass = 0;
						score = 0;
						playAgain = true;
						app.playing = true;
						initPlayer();
						return;
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
						exit(0);
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_M) {
						if (Mix_PausedMusic()) {
							Mix_ResumeMusic();
						}
						else {
							Mix_PauseMusic();
						}
					}
					break;

				case SDL_MOUSEMOTION:
					SDL_GetMouseState(&x, &y);
					for (int i = 0; i < 2; i++) {
						if (x >= endButton[i].getX() && x <= endButton[i].getX() + endButton[i].getW()
							&& y >= endButton[i].getY() && y <= endButton[i].getY() + endButton[i].getH()) {
							if (!endButton[i].isHovered()) {
								endButton[i].setHovered(true);
								if (i == 0) endButton[i].setTexture(Buttons[13]);
								if (i == 1) endButton[i].setTexture(Buttons[15]);
							}
						}
						else if (endButton[i].isHovered()) {
							endButton[i].setHovered(false);
							if (i == 0) endButton[i].setTexture(Buttons[12]);
							if (i == 1) endButton[i].setTexture(Buttons[14]);
						}
					}
					break;

				case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState(&x, &y);
					for (int i = 0; i < 2; i++) {
						if (x >= endButton[i].getX() && x <= endButton[i].getX() + endButton[i].getW()
							&& y >= endButton[i].getY() && y <= endButton[i].getY() + endButton[i].getH()) {
							    Mix_PlayChannel(-1, buttonSound, 0);
								enemySpawnTimer = 60;
								surpass = 0;
								score = 0;
								if (i == 0) {
									playAgain = false;
								} else {
									playAgain = true;
									app.playing = true;
									initPlayer();
								}
								return;
						}
					}
					break;

			}
		}

	}

}



void Game::initPlayer() {
	// Đặt vị trí ban đầu cho nhân vật chính (player) ở giữa màn hình.
	player.setX(SCREEN_WIDTH / 2);
	player.setY(SCREEN_HEIGHT / 2 - 50);

	 // Đặt các giá trị khởi tạo cho trạng thái của nhân vật.
	player.setHealth(30);
	player.setEnhance(0);
	player.setDecay(0);
	player.setStunt(0);
	// Đặt lại tất cả các giá trị đầu vào của nhân vật.
	player.resetInput();
}

void Game::getInput() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_KEYUP:
			player.keyUp(&e.key);
			break;
		case SDL_KEYDOWN:
			if (e.key.keysym.scancode == SDL_SCANCODE_P) {
				Mix_PlayChannel(-1, buttonSound, 0);
				app.pause = !app.pause;
			}
			if (e.key.keysym.scancode == SDL_SCANCODE_M) {
				if (Mix_PausedMusic()) {
					Mix_ResumeMusic();
				} else {
					Mix_PauseMusic();
				}
			}
			player.keyDown(&e.key);
			break;
		}
	}
}

void Game::Pause() {
	// Vẽ biểu tượng "pause" lên màn hình ở vị trí trung tâm.
	draw(pauseIcon, SCREEN_WIDTH / 2 - 210, SCREEN_HEIGHT / 2 - 225);
	string gamepause = "GAME PAUSED";
	SDL_Surface* pauseSf = TTF_RenderText_Solid(font, gamepause.c_str(), { 255, 255, 255, 0 });
	SDL_DestroyTexture(pauseTXT);
	pauseTXT = SDL_CreateTextureFromSurface(app.renderer, pauseSf);
	SDL_FreeSurface(pauseSf);
	draw(pauseTXT, SCREEN_WIDTH / 2 - 100, 3 * SCREEN_HEIGHT / 4 - 50);
}

void Game::presentEntities() { 
	// Giảm decay nếu lớn hơn 1, nếu bằng 1 thì khôi phục lại sức khỏe thực sự của người chơi
	if (player.getDecay() > 1) player.setDecay(player.getDecay() - 1);
	else if (player.getDecay() == 1) {
		player.setDecay(0);
		player.setHealth(realHealth);
	}
	// Đếm thời gian hiệu ứng đổi màu RGB và reset lại texture nếu đã hết thời gian
	if (player.getRGBTimer() > 0) player.setRGBTimer(player.getRGBTimer() - 1);
	else SDL_SetTextureColorMod(player.getTexture(), 255, 255, 255);
	// Xử lý di chuyển, bắn đạn và hiển thị người chơi nếu còn máu
	if (player.getHealth() > 0) {
		if (player.getStunt() == 0) player.move();  // Người chơi di chuyển nếu không bị choáng
		else player.setStunt(player.getStunt() - 1);

		draw(player.getTexture(), player.getX(), player.getY());
		int wP, hP;
		// Bắn đạn
		if (player.Fire() == true && player.getReload() == 0) {
			SDL_QueryTexture(player.getTexture(), NULL, NULL, &wP, &hP);
			playerBullet.setX(player.getX() + wP / 2);
			playerBullet.setY(player.getY() + hP / 2);
			playerBullet.setType(-1);
			player.setReload(player.getReloadRate());
			Bullets.push_back(playerBullet);
			if (player.getEnhance() > 0) {
				playerBullet.setX(player.getX());
				playerBullet.setY(player.getY());
				Bullets.push_back(playerBullet);

				playerBullet.setX(player.getX());
				playerBullet.setY(player.getY() + hP);
				Bullets.push_back(playerBullet);
			  // Thêm đạn của người chơi vào danh sách đạn
			}
			Mix_PlayChannel(-1, bulletSound, 0);  // Phát âm thanh bắn đạn
		}
	}

	// Tăng số điểm, xác định khi nào sẽ xuất hiện boss
	if (score % 5 == 0) fightingBoss = score/5;

	// Sinh kẻ thù hoặc boss
	if (enemySpawnTimer == 0) {
		if(fightingBoss == 0) {
			// Sinh kẻ thù thông thường
			enemy = new Enemy();
			enemy->setTexture(enemyTexture);
			int rate = rand() % 4; // Xác định hướng spawn
			if (rate < 2) {
				enemy->setX(SCREEN_WIDTH - 80);
				enemy->setDX(ENEMY_SPEED - rand() % 8);
				enemy->setY(rand() % 400 + 100);
			}
			else {
				enemy->setX(SCREEN_WIDTH / 2 + rand() % 200);
				if (rate == 1) {
					enemy->setDY(-ENEMY_SPEED + rand() % 8);
					enemy->setY(-10);
				}
				else {
					enemy->setDY(ENEMY_SPEED - rand() % 8);
					enemy->setY(690);
				}
			}
			enemy->setHealth(5);
			enemySpawnTimer = 60;
			Enemies.push_back(enemy);
		} else {
			// Sinh boss
			enemy = new Enemy();
			enemy->setTexture(enemyBoss[(fightingBoss - 1) % 3]);
			enemy->setX(SCREEN_WIDTH / 2 + rand() % 300);
			enemy->setDY(-ENEMY_SPEED/3 + rand() % 3);
			enemy->setY(-300);
			enemy->setHealth(50*fightingBoss); // Máu boss tăng theo số lần đánh boss
			bossHP = enemy->getHealth();
			enemy->setType(2);
			enemySpawnTimer = -1; // Không spawn kẻ thù thông thường khi đánh boss
			Enemies.push_back(enemy);
		}
	}


	// Kiểm tra và loại bỏ các kẻ thù
	for (auto i = Enemies.begin(); i != Enemies.end(); ) {
		int w, h;
		SDL_QueryTexture((*i)->getTexture(), NULL, NULL, &w, &h);
		if ((*i)->getX() <= -w) {
			// Xóa kẻ thù nếu ra ngoài màn hình
			i = Enemies.erase(i); 
		}
		else if ((*i)->getHealth() <= 0) {
			 // Nổ khi kẻ thù bị tiêu diệt
			addExplosion((*i)->getX(), (*i)->getY(), 0);
			score++; // Tăng điểm khi tiêu diệt kẻ thù
			Mix_PlayChannel(-1, explosionSound, 0);
			if ((*i)->getType() == 2) {
				 // Nếu là boss
				fightingBoss = 0;
				enemySpawnTimer = 80; // Reset thời gian hồi sinh
			}
			i = Enemies.erase(i);
		}
		else {
			// Cập nhật màu sắc nếu bị tấn công
			if ((*i)->getRGBTimer() > 0) (*i)->setRGBTimer((*i)->getRGBTimer() - 1);
			else SDL_SetTextureColorMod((*i)->getTexture(), 255, 255, 255);
			// Kẻ thù bắn đạn
			if ((*i)->getReload() > 0) (*i)->setReload((*i)->getReload() - 1);
			else {
				if ((*i)->getType() == 1) {
					// Kẻ thù thông thường bắn đạn
					enemyBullet.setTexture(enemyBulletTexture);
					enemyBullet.setX((*i)->getX() - w / 2);
					enemyBullet.setY((*i)->getY() + h / 2);
					float dx = player.getX() - enemyBullet.getX();
					float dy = player.getY() - enemyBullet.getY();
					float distance = sqrt(dx * dx + dy * dy);
					dx /= distance;
					dy /= distance;
					enemyBullet.setDX(dx * (ENEMY_BULLET_SPEED + rand() % 8));
					enemyBullet.setDY(dy * (ENEMY_BULLET_SPEED + rand() % 8));
					enemyBullet.setHealth(1);
					enemyBullet.setType(0);
					(*i)->setReload(30 + rand() % 30);
					Bullets.push_back(enemyBullet);
				} else {
					// Boss bắn đạn
					enemyBullet.setTexture(bossBullet[(fightingBoss-1) % 3]);
					enemyBullet.setX((*i)->getX() - w / 2);
					enemyBullet.setY((*i)->getY() + h / 2);
					float dx = player.getX() - enemyBullet.getX();
					float dy = player.getY() - enemyBullet.getY();
					float distance = sqrt(dx * dx + dy * dy);
					dx /= distance;
					dy /= distance;
					enemyBullet.setDX(dx * ENEMY_BULLET_SPEED);
					enemyBullet.setDY(dy * ENEMY_BULLET_SPEED);
					enemyBullet.setHealth(1);
					enemyBullet.setType((fightingBoss - 1) % 3 + 1);
					(*i)->setReload(30 + rand() % 30);
					Bullets.push_back(enemyBullet);
				}
			}
			// Di chuyển kẻ thù
			(*i)->move();
			// Phản chiếu di chuyển nếu chạm vào tường
			if ( ((*i)->getY() < 0 && (*i)->getDY() < 0) || ((*i)->getY() + h > SCREEN_HEIGHT && (*i)->getDY() > 0) ) {
				(*i)->setDY(-(*i)->getDY());
			}  

			draw((*i)->getTexture(), (*i)->getX(), (*i)->getY());
			i++;
		}

	}

	 // Kiểm tra và xử lý các viên đạn trong danh sách
	for (auto i = Bullets.begin(); i != Bullets.end(); ) {
		int w, h;
		SDL_QueryTexture(i->getTexture(), NULL, NULL, &w, &h);
		 // Kiểm tra nếu viên đạn ra khỏi màn hình thì loại bỏ
		if (i->getX() <= -w || i->getX() >= SCREEN_WIDTH || i->getY() <= -h || i->getY() > SCREEN_HEIGHT || !i->getHealth()) {
			i = Bullets.erase(i);
		}
		else {
			i->move();
			draw(i->getTexture(), i->getX(), i->getY());
			i++;
		}
	}

	// Kiểm tra va chạm giữa đạn của người chơi và kẻ thù
	for (auto i = Bullets.begin(); i != Bullets.end(); i++) {
		int wB, hB, wP, hP;
		SDL_QueryTexture(i->getTexture(), NULL, NULL, &wB, &hB);
		SDL_QueryTexture(player.getTexture(), NULL, NULL, &wP, &hP);
		if (detectCollision(i->getX(), i->getY(), wB, hB, player.getX(), player.getY(), wP, hP)) {
			switch (i->Type()) {
			case 0:
				player.setRGBTimer(10);
				SDL_SetTextureColorMod(player.getTexture(), 255, 0, 0);
				i->setHealth(0);
				player.setHealth(player.getHealth() - 2);
				if (player.getHealth() <= 0) {
					player.setHealth(0);
					addExplosion(player.getX(), player.getY(), 1);
					Mix_PlayChannel(-1, playerExplosionSound, 0);
				}
				break;
			case 1:
				player.setRGBTimer(10);
				SDL_SetTextureColorMod(player.getTexture(), 255, 0, 0);
				i->setHealth(0);
				player.setHealth(player.getHealth() - 6);
				if (player.getHealth() <= 0) {
					player.setHealth(0);
					addExplosion(player.getX(), player.getY(), 1);
					Mix_PlayChannel(-1, playerExplosionSound, 0);
				}
				break;
			case 2:
				player.setRGBTimer(60);
				SDL_SetTextureColorMod(player.getTexture(), 255, 255, 51);
				i->setHealth(0);
				player.setHealth(player.getHealth() - 2);
				if(player.getStunt() == 0) player.setStunt(60);
				if (player.getHealth() <= 0) {
					player.setHealth(0);
					addExplosion(player.getX(), player.getY(), 1);
					Mix_PlayChannel(-1, playerExplosionSound, 0);
				}
				break;
			case 3:
				player.setRGBTimer(180);
				SDL_SetTextureColorMod(player.getTexture(), 147, 112, 219);
				i->setHealth(0);
				if (player.getDecay() == 0) {
					realHealth = player.getHealth();
					player.setHealth(1);
					player.setDecay(180);
				}
				else {
					player.setHealth(0);
				}
				if (player.getHealth() <= 0) {
					player.setHealth(0);
					addExplosion(player.getX(), player.getY(), 1);
					Mix_PlayChannel(-1, playerExplosionSound, 0);
				}
				break;
			}
		}
		// Duyệt qua danh sách kẻ địch
		for (auto j = Enemies.begin(); j != Enemies.end(); j++) {
			int wE, hE;
			SDL_QueryTexture((*j)->getTexture(), NULL, NULL, &wE, &hE);

			if (i->Type() == -1 && detectCollision(i->getX(), i->getY(), wB, hB, (*j)->getX(), (*j)->getY(), wE, hE)) {
				(*j)->setRGBTimer(10);
				SDL_SetTextureColorMod((*j)->getTexture(), 255, 0, 0);
				i->setHealth(0);
				(*j)->setHealth((*j)->getHealth() - player.getDamageRate());
				// Kiểm tra nếu kẻ địch đã chết
				if ((*j)->getHealth() <= 0) {
					// Nếu kẻ địch loại 1, rơi vật phẩm ngẫu nhiên với xác suất
					if ((*j)->getType() == 1) {
						int num = rand() % 10 + 1;
						if (num < 4) {
							addPowerUp((*j)->getX(), (*j)->getY(), 1);
						}
						else if (num < 3) {
							addPowerUp((*j)->getX(), (*j)->getY(), 2);
						}
					}
					else {
						addPowerUp((*j)->getX(), (*j)->getY(), 1);
						addPowerUp((*j)->getX(), (*j)->getY(), 2);
					}
				}
			}
			// Kiểm tra nếu người chơi va chạm trực tiếp với kẻ địch
			if (detectCollision(player.getX(), player.getY(), wP, hP, (*j)->getX(), (*j)->getY(), wE, hE)) {
				player.setHealth(0);
				addExplosion(player.getX(), player.getY(), 1);
				Mix_PlayChannel(-1, playerExplosionSound, 0);
				(*j)->setHealth(0);
			}

		}
	}

	//Vẽ hiệu ứng nổ
	for (auto i = Explosion.begin(); i != Explosion.end(); ) {
		bool remove = false;
		for (auto j = i->begin(); j != i->end(); j++) {
			if (j->getA() <= 0) {
				remove = true;
				break;
			}
			SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_ADD);
			SDL_SetTextureBlendMode(j->getTexture(), SDL_BLENDMODE_ADD);

			SDL_SetTextureColorMod(j->getTexture(), j->getR(), j->getG(), j->getB());
			SDL_SetTextureAlphaMod(j->getTexture(), j->getA());

			draw(j->getTexture(), j->getX(), j->getY());
			j->updateA(-15);

		}

		if (remove) {
			i = Explosion.erase(i);
		}
		else {
			i++;
		}
	}

	//làm tăng sức mạnh
	for (auto i = powerUps.begin(); i != powerUps.end(); ) {
		if (i->getHealth() == 0 || i->getX() < 0 || i->getY() < 0 || i->getY() > 680) {
			i = powerUps.erase(i);
			break;
		} else {
			int wPU, hPU, wP, hP;
			SDL_QueryTexture(i->getTexture(), NULL, NULL, &wPU, &hPU);
			SDL_QueryTexture(player.getTexture(), NULL, NULL, &wP, &hP);
			if (detectCollision(i->getX(), i->getY(), wPU, hPU, player.getX(), player.getY(), wP, hP)) {
				if (i->Type() == 1) {
					if (player.getDecay() > 0) {
						realHealth += 4;
					}
					else {
						player.setHealth(player.getHealth() + 4);
					}
				} else {
					player.setEnhance(300);
				}
				Mix_PlayChannel(-1, powerupSound, 0);
				i = powerUps.erase(i);
				break;
			}

			i->move();
			draw(i->getTexture(), i->getX(), i->getY());
			i->setHealth(i->getHealth() - 1);
			i++;
		}
	}

}



void Game::HUD() {

	if (score > highScore) surpass = 1;

	highScore = max(highScore, score);
	scoreText << "Score : " << score;
	hScoreText << "High Score : " << highScore;

	SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.str().c_str(), { 255, 255, 255, 0 });
	SDL_DestroyTexture(scoreTXT); 
	scoreTXT = SDL_CreateTextureFromSurface(app.renderer, scoreSurface);
	SDL_FreeSurface(scoreSurface);

	SDL_Surface* hsSurface = TTF_RenderText_Solid(font, hScoreText.str().c_str(), { 181, 13, 13, 0 });
	SDL_DestroyTexture(hsTXT);
	hsTXT = SDL_CreateTextureFromSurface(app.renderer, hsSurface);
	SDL_FreeSurface(hsSurface);

	LPText << "Life Points: " << player.getHealth();
	if (player.getDecay()) LPText << " (DECAY)";

	SDL_Surface* LPSurface = TTF_RenderText_Solid(font, LPText.str().c_str(), { 22, 184, 17, 0 });
	if (player.getDecay()) LPSurface = TTF_RenderText_Solid(font, LPText.str().c_str(), { 255, 99, 71, 0 });

	SDL_DestroyTexture(LPTXT);
	LPTXT = SDL_CreateTextureFromSurface(app.renderer, LPSurface);
	SDL_FreeSurface(LPSurface);

	draw(scoreTXT, 20, 20);
	draw(hsTXT, 20, 60);
	draw(LPTXT, 20, 100);

	if (player.getStunt()) {
		string stunt = "STUNT";
		SDL_Surface* stuntSf = TTF_RenderText_Solid(font, stunt.c_str(), { 255, 200, 0, 0 });
		SDL_DestroyTexture(stuntTXT);
		stuntTXT = SDL_CreateTextureFromSurface(app.renderer, stuntSf);
		SDL_FreeSurface(stuntSf);
		draw(stuntTXT, player.getX(), player.getY() - 25);
	}

	if (fightingBoss) {
		currbossHP = bossHP;
		for (auto i = Enemies.begin(); i != Enemies.end(); i++) {
			if ((*i)->getType() == 2) currbossHP = (*i)->getHealth();
			break;
		}

		SDL_Rect rect{ 500, 500, 400, 22};
		SDL_Rect rect2{ 502, 502, static_cast<int>((static_cast<double>(currbossHP) / bossHP) * 392), 18 };


		drawRect(bar, &rect, 850, 650);
		drawRect(healthbar, &rect2, 854, 652);
	}
}

void Game::prepareScene() {
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
	SDL_RenderClear(app.renderer);
}


void Game::addExplosion(int x, int y, int type) {
	explosion.setTexture(explosionTexture);
	explosion.setX(x + rand() % 32);
	explosion.setY(y + rand() % 32);
	explosion.setDX(0); explosion.setDY(0);
	explosion.setType(type);
	std::vector<Effect> tmp;
	for (int j = 0; j < 10; j++) {
		switch (rand() % 4) {
		case 0:
			explosion.setRGBA(255, 255, 0, 200); //YELLOW
			break;
		case 1:
			explosion.setRGBA(255, 0, 0, 200); //RED
			break;
		case 2:
			explosion.setRGBA(255, 128, 0, 200); //ORANGE
			break;
		case 3:
			explosion.setRGBA(255, 255, 255, 200); //WHITE
			break;
		}
		tmp.push_back(explosion);
	}
	Explosion.push_back(tmp);
}



void Game::addPowerUp(int x, int y, int type) {
	if(type == 1) powerup.setTexture(powerUp1);
	else if(type == 2) powerup.setTexture(powerUp2);
	powerup.setX(x + 20);
	powerup.setY(y + 20);
	powerup.setDX( -rand() % 5  - 1);
	powerup.setDY(rand() % 5 + 1);
	powerup.setHealth(150);
	powerup.setType(type);
	powerUps.push_back(powerup);
}


void Game::presentScene() {
	if (enemySpawnTimer > 0) {
		enemySpawnTimer--;
	}
	if (player.getReload() > 0) {
		player.setReload(player.getReload() - 1);
	}

	if (player.getEnhance() > 0) {
		player.setEnhance(player.getEnhance() - 1);
	}

	if (Explosion.empty() && player.getHealth() <= 0 && app.playing) {
		Bullets.clear();
		Enemies.clear();
		powerUps.clear();
		SDL_SetTextureColorMod(player.getTexture(), 255, 255, 255);
		fightingBoss = 0;
		realHealth = 0;
		app.playing = false;
	}

	scoreText.str(std::string());
	hScoreText.str(std::string());
	LPText.str(std::string());
	SDL_RenderPresent(app.renderer);
	SDL_Delay(16);
}

// Tải một texture từ đường dẫn file
SDL_Texture* Game::loadTexture(std::string path) {
	SDL_Texture* texture = IMG_LoadTexture(app.renderer, path.c_str());
	if (texture == NULL) {
		cout << "Error loading image : " << IMG_GetError() << endl;
		exit(-1);
	}
	return texture;
}

// Vẽ một texture tại vị trí (x, y)
void Game::draw(SDL_Texture* texture, int x, int y) {
	SDL_Rect target;
	target.x = x;
	target.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &target.w, &target.h);
	SDL_RenderCopy(app.renderer, texture, NULL, &target);
}
// Vẽ một phần của texture vào một vị trí trên màn hình
void Game::drawRect(SDL_Texture* texture, SDL_Rect* src, int x, int y) {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = src->w;
	dest.h = src->h;

	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}
// Vẽ nền của trò chơi, làm nền cuộn ngang
void Game::drawBackground() {
	int w, h;
	SDL_QueryTexture(app.background, NULL, NULL, &w, &h);
	if (-w > --backgroundX) {
		backgroundX = 0;
	}
	// Vẽ nền hai lần để tạo hiệu ứng cuộn liên tục
	draw(app.background, backgroundX, 0);
	draw(app.background, backgroundX + w, 0);
}
// Kiểm tra va chạm giữa hai hình chữ nhật
bool Game::detectCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	return (max(x1, x2) < min(x1 + w1, x2 + w2)) && (max(y1, y2) < min(y1 + h1, y2 + h2));
}
