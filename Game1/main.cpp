
/* KHAI BAO THU VIEN */

#include<iostream>
#include<cstdlib>
#include<ctime>
#include "GeneralFunction.h"
#include "BaseObject.h"
#include "Map.h"
#include "MainPlayer.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Text.h"
#include "DataGame.h"
#include "Geometric.h"
#include "Menu.h"

// Khai bao doi tuong Background la bien toan cuc
BaseObject gBackground;

/* HAM KHOI TAO SDL */
bool Init();
/* HAM TAO VA XU LY ENEMIES*/

std::vector<EnemiesObiect*> MakeEnemiesList();

/* HAM HUY BIEN CON TRO VA THOAT */
void close();

/* HAM MAIN */
int main(int argc, char* argv[])
{
    // Bien xu ly FPS
    Uint32 start_frame_time_;
    Uint32 theory_frame_time_;

    // Kiem tra viec khoi tao SDL va Background

    if (Init() == false)
    {
        std::cout << "Can not Init Data: " << SDL_GetError() << std::endl;
        return -1;
    }

    //Khoi tao va Load Ban do Game
    GameMap game_map;
    game_map.LoadMap("map/map01.map");
    game_map.SetTiles(gScreen);

    //Khoi tao bien quan ly quan ly cac thong so game
    DataGame game_data;
    game_data.Init(gScreen);

    //Khoi tao bien xu ly Load Menu
    Menu menu_game;
	menu_game.LoadImg("assert/menu.png", gScreen);
	menu_game.SetPostionText();

	//Khoi tao bien xu ly thong bao diem
	BaseObject score_message;
	score_message.setRect(380, 90);
	bool sret = score_message.LoadImg("assert/score.png", gScreen);
	if(!sret) return -1;

    //Khoi tao bien quan ly Duoc
    PlayerTorch player_torch;
    player_torch.Init(gScreen);
    player_torch.SetPosition(20, 100);

    //Khoi tao va Load nhan vat chinh
    MainPlayer p_player;
    p_player.LoadImg("assert/player_right_.png", gScreen);
    p_player.SetClips();

    //Load cac enemies
    std::vector<EnemiesObiect*>enemies_list = MakeEnemiesList();

    //Khoi tao bien xu ly va cham
    Explosion expEnemy;
    bool tRet = expEnemy.LoadImg("assert/exp.png", gScreen);
    if (!tRet)
    {
        return -1;
    }
    expEnemy.setClip();

    Explosion exp_main;
    bool mRet = exp_main.LoadImg("assert/exp1.png", gScreen);
    if (!mRet)
    {
        return -1;
    }
    exp_main.setClip();

    int num_die = 0;

    //Khoi tao bien xu ly thoi gian
    Text time_game;
    time_game.SetColor(Text::YELLOW_TEXT);

    //Khoi tao bien xu ly diem
    Text score_game;
    score_game.SetColor(Text::YELLOW_TEXT);
    UINT score_value = 0;

    //Khoi tao bien xu ly doi tuong Duoc
    Text torch_game;
    torch_game.SetColor(Text::YELLOW_TEXT);

    bool is_quit = false;
    bool is_show_score=true;

	//Load nhac nen
	if(Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(gSound_start, -1);
    }

    //Hien thi Menu
	while(menu_game.is_show_)
	{
		while(SDL_PollEvent(&gEvent)!=0)
		{
			if(gEvent.type == SDL_QUIT)
			{
				menu_game.is_show_ = false;
				is_quit = true;
				is_show_score = false;
			}
			menu_game.CheckEvents(gEvent, is_quit, is_show_score);
		}
		SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR,
                                        RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		menu_game.CreateText(gFont, gScreen);
		menu_game.RenderMenu(gScreen);
		SDL_RenderPresent(gScreen);
		SDL_Delay(150);
	}

	//Tai Game
    while(!is_quit)
    {
        //Lay thoi gian bat dau cua mot frame
        start_frame_time_ = SDL_GetTicks();
        while(SDL_PollEvent(&gEvent) != 0)
        {
            if (gEvent.type == SDL_QUIT)
            {
                is_quit = true;
                is_show_score = false;
            }
            //Xu ly trang thai ban dau cua nhan vat
            p_player.ImpInputAction(gEvent, gSound_bullet, gScreen);
        }

        SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(gScreen);

        //Hien thi Background
        gBackground.Render(gScreen, NULL);

        Map map_data = game_map.getMap();

        //Hien thi nhan vat
        p_player.ImpBullet(gScreen);
        p_player.SetPlayerMap(map_data.start_x_, map_data.start_y_);
        p_player.DoPlayer(map_data);
        p_player.ShowAnimation(gScreen);

        //Hien thi ban do Game
        game_map.SetMap(map_data);
        game_map.DrawMap(gScreen);

        //Ve khung chua cac thong so game
        RectFormat rectangle_size{0, 0, SCREEN_WIDTH/4, SCREEN_HEIGHT/4};
        ColorData color1{237, 28, 36};
        Geometric::RenderRectangle(rectangle_size, color1, gScreen);

        RectFormat outline_size(1, 1, SCREEN_WIDTH/4, SCREEN_HEIGHT/4-2);
        ColorData color2{0, 0, 0};
        Geometric::RenderOutline(outline_size, color2, gScreen);

        //Hien thi thong so Game
        game_data.Show(gScreen);
        player_torch.Show(gScreen);

        //Xu ly va cham
        for (int i = 0; i < enemies_list.size(); i++)
        {
            //Xu ly vi tri cua nhan vat, cho nhan vat di chuyen, tao dan ban va hien thi
            EnemiesObiect* pEnemy = enemies_list.at(i);
            if (pEnemy != NULL)
            {
                pEnemy->SetMapXY(map_data.start_x_, map_data.start_y_);
                pEnemy->ImpMoveType(gScreen);
                pEnemy->DoEnemy(map_data);
                pEnemy->GenerateBullet(gScreen, SCREEN_WIDTH, SCREEN_HEIGHT);
                pEnemy->Show(gScreen);

                //kiem tra va cham giua nhan vat game va dan cua cac Enemies
                SDL_Rect rect_player = p_player.GetFrameRect();
                bool bCol1 = false;
                std::vector<Bullet*> tBullet_list = pEnemy->get_bullet_list();
                for (int idx1 = 0; idx1 < tBullet_list.size(); idx1++)
                {
                    Bullet* pt_bullet = tBullet_list.at(idx1);
                    if (pt_bullet)
                    {
                        bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player);
                        if (bCol1)
                        {
                            pEnemy->RemoveBullet(idx1);
                            break;
                        }
                    }
                }

                //Kiem tra va cham giua nhan vat game va enemies
                SDL_Rect rect_enemy = pEnemy->GetRectFrame();
                bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_enemy);

                if (bCol1 || bCol2)
                {
                    int fr_exp_width = exp_main.get_frame_width();
                    int fr_exp_height = exp_main.get_frame_height();
                    for (int idx2 = 0; idx2 < NUM_FRAME_EXPLOSION; idx2++)
                    {
                        //Dat frame hinh vao tam cua vu no
                        int x_pos = (p_player.GetRect().x + p_player.GetFrameRect().w*0.5) - fr_exp_width*0.5;
                        int y_pos = (p_player.GetRect().y + p_player.GetFrameRect().h*0.5) - fr_exp_height*0.5;

                        exp_main.setFrame(idx2);
                        exp_main.setRect(x_pos, y_pos);
                        exp_main.Show(gScreen);
                        SDL_RenderPresent(gScreen);
                    }

                    Mix_PlayChannel(-1, gSound_ex_main, 0);
                    num_die++;

                    if (num_die <= NUM_DIE)
                    {
                        p_player.setRect(0, 0);
                        p_player.SetComeBackTime(60);
                        SDL_Delay(1000);
                        game_data.Decrease();
                        game_data.Render(gScreen);
                        continue;
                    }
                    else
                    {
                        is_show_score = true;
                        pEnemy->Clean();
                        is_quit = true;
                    }
                }
            }
        }

        //Kiem tra va cham giua dan nhan vat va cac enemies
        std::vector<Bullet*> bullet_arr = p_player.get_bullet_list();
        for (int i = 0; i < bullet_arr.size(); i++)
        {
            Bullet* p_bullet = bullet_arr.at(i);
            if (p_bullet != NULL)
            {
                for (int j = 0; j < enemies_list.size(); j++)
                {
                    EnemiesObiect* objEnemy = enemies_list.at(j);
                    if (objEnemy != NULL)
                    {
                        SDL_Rect eRect;
                        eRect.x = objEnemy->GetRect().x;
                        eRect.y = objEnemy->GetRect().y;
                        //Lay mot frame cua Enemies
                        eRect.w = objEnemy->get_width_frame();
                        eRect.h = objEnemy->get_height_frame();

                        SDL_Rect bRect = p_bullet->GetRect();

                        bool bCol = SDLCommonFunc::CheckCollision(bRect, eRect);
                        if (bCol)
                        {
                            score_value ++;
                            int frame_exp_width = expEnemy.get_frame_width();
                            int frame_exp_height = expEnemy.get_frame_height();
                            for (int idx = 0; idx < NUM_FRAME_EXPLOSION; idx++)
                            {
                                // dat frame vao tam cua vu no
                                int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5;
                                int y_pos = p_bullet->GetRect().y - frame_exp_height*0.5;

                                expEnemy.setFrame(idx);
                                expEnemy.setRect(x_pos, y_pos);
                                expEnemy.Show(gScreen);
                            }
                            p_player.RemoveBullet(i);
                            objEnemy->Clean();
                            enemies_list.erase(enemies_list.begin()+j);
                            Mix_PlayChannel(-1, gSound_explosion, 0);
                        }
                    }
                }
            }
        }

        bool won_ = p_player.GetRes();
        if (won_)
        {
            is_show_score = true;
            is_quit = true;
            bool sret = score_message.LoadImg("assert/happy.png", gScreen);
            if(!sret) return -1;
        }

        //Hien thi thoi gian
        std::string str_time = "TIME LEFT: ";
        //Lay thoi gian hien tai
        Uint32 time_val = SDL_GetTicks()/1000;
        Uint32 val_time = MAX_TIME_GAME - time_val;
        if (val_time <= 0)
        {
            is_show_score = true;
            is_quit = true;
        }
        else
        {
            std::string str_val = std::to_string(val_time);
            str_time += str_val;

            time_game.SetText(str_time);
            time_game.LoadFromRenderText(gFont, gScreen);
            time_game.RenderText(gScreen, 20, 15);
        }

        //Hien thi so enemies con lai
        std::string val_str_score = std::to_string(MAX_ENEMIES_GAME - score_value);
        std::string strScore("ENEMY: ");
        strScore += val_str_score;
        score_game.SetText(strScore);
        score_game.LoadFromRenderText(gFont, gScreen);
        score_game.RenderText(gScreen, 20, 65);

        //Hien thi so Duoc da co
        int torch_count = p_player.GetTorchCount();
        std::string torch_str = std::to_string(torch_count);

        torch_game.SetText(torch_str);
        torch_game.LoadFromRenderText(gFont, gScreen);
        torch_game.RenderText(gScreen, 120, 115);

        //Update Screen
        SDL_RenderPresent(gScreen);

        //Xu ly khung hinh tren giay (FPS)
        theory_frame_time_ = SDL_GetTicks() - start_frame_time_;
		if (theory_frame_time_ < real_frame_time_)
		{
			SDL_Delay(real_frame_time_ - theory_frame_time_);
		}
    }

    //Xoa cac con tro lien quan den dan ban
    for (int i = 0; i < enemies_list.size(); i++)
    {
        EnemiesObiect* pEnemy = enemies_list.at(i);
        if (pEnemy)
        {
            pEnemy->Clean();
            pEnemy = NULL;
        }
    }
    enemies_list.clear();

    //Dung phat nhac
    Mix_HaltMusic();

    //Hien thi so diem
    if(is_show_score)
    {
        score_game.SetText(std::to_string(score_value));
        score_game.CreateText(gScreen, gFont);
        score_message.Render(gScreen);

        score_game.setRect(score_message.GetRect().x+380, score_message.GetRect().y+92);
        score_game.Render(gScreen);
        SDL_RenderPresent(gScreen);
        Mix_PlayMusic(gSound_end, -1);
        SDLCommonFunc::waitUntilKeyPressed();
    }

    //Ket thuc tro choi
    close();

    return 0;
}

/* HAM KHOI TAO SDL */
bool Init()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
    {
        std::cout << "Can not Initialize: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    gWindow = SDL_CreateWindow("Game by Kieu Van Tuyen", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
        std::cout << "Can not create Window: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        gScreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (gScreen == NULL)
        {
            std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
            {
                std::cout << "Can not Init IMG: " << SDL_GetError() << std::endl;
                success = false;
            }
        }

        /* HAM LOAD BACKGROUND */
        bool ret = gBackground.LoadImg("assert/background.png", gScreen);
        if (ret == false)
        {
            std::cout << "Can not Load Background: " << SDL_GetError() << std::endl;
            return false;
        }

        //Khoi tao font chu
        if (TTF_Init() == -1)
        {
            success = false;
        }
        gFont = TTF_OpenFont("font/dlxfont_.ttf", 15);
        if (gFont == NULL)
        {
            success = false;
        }

        //Khoi tao trinh phat nhac
        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        {
            return false;
        }
        gSound_end = Mix_LoadMUS("sound/ncbtndt.wav");
        gSound_start = Mix_LoadMUS("sound/gpmn.wav");
        gSound_bullet[0] = Mix_LoadWAV("sound/bullet_0.wav");
        gSound_bullet[1] = Mix_LoadWAV("sound/bullet_1.wav");
        gSound_bullet[2] = Mix_LoadWAV("sound/bullet_2.wav");
        gSound_explosion = Mix_LoadWAV("sound/enemy_exp.wav");
        gSound_ex_main = Mix_LoadWAV("sound/main_exp.wav");

        if (gSound_bullet[0] == NULL || gSound_bullet[1] == NULL
            || gSound_explosion == NULL || gSound_ex_main == NULL
            || gSound_start == NULL || gSound_end == NULL)
        {
            return false;
        }
    }
    return success;
}

/* HAM HUY BIEN CON TRO VA THOAT */

void close()
{
    gBackground.Clean();
    SDL_DestroyRenderer(gScreen);
    gScreen = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    TTF_CloseFont(gFont);
    gFont = NULL;

    Mix_FreeChunk(gSound_bullet[0]);
    gSound_bullet[0] = NULL;
    Mix_FreeChunk(gSound_bullet[1]);
    gSound_bullet[1] = NULL;
    Mix_FreeChunk(gSound_bullet[2]);
    gSound_bullet[2] = NULL;
    Mix_FreeChunk(gSound_explosion);
    gSound_explosion = NULL;
    Mix_FreeChunk(gSound_ex_main);
    gSound_ex_main = NULL;

    Mix_FreeMusic(gSound_start);
    gSound_start = NULL;
    Mix_FreeMusic(gSound_end);
    gSound_end = NULL;

    IMG_Quit();
    SDL_Quit();
}

/* HAM TAO VA XU LY ENEMIES*/

std::vector<EnemiesObiect*> MakeEnemiesList()
{
    std::vector<EnemiesObiect*> listEnemies;
    srand(time(0));

    EnemiesObiect* soldier_enemies = new EnemiesObiect[20];
    for (int i = 0; i < 20; i++)
    {
        EnemiesObiect* pEnemy = (soldier_enemies+i);
        if (pEnemy != NULL)
        {
            int rand_y_ = SDLCommonFunc::MakeRandValue();
            pEnemy->LoadImg("assert/enemy_left.png", gScreen);
            pEnemy->SetClips();
            pEnemy->set_type_move(EnemiesObiect::MOVE_IN_SPACE_ENEMY);
            pEnemy->set_x_pos(500 + i*rand_y_*2 + 400);
            pEnemy->set_y_pos(200);

            int pos1 = pEnemy->get_x_pos() - 60;
            int pos2 = pEnemy->get_x_pos() + 60;
            pEnemy->SetAnimationPos(pos1, pos2);
            pEnemy->set_input_left(1);
            listEnemies.push_back(pEnemy);
        }
    }

    EnemiesObiect* plane_enemies = new EnemiesObiect[20];
    for (int i = 0; i < 20; i++)
    {
        EnemiesObiect* pEnemy = (plane_enemies+i);
        if (pEnemy != NULL)
        {
            int rand_y_ = SDLCommonFunc::MakeRandValue();
            pEnemy->LoadImg("assert/plane_left.png", gScreen);
            pEnemy->SetClips();
            pEnemy->set_type_move(EnemiesObiect::FLY_ENEMY);
            pEnemy->set_x_pos(600 + i*rand_y_*3 + 700);
            pEnemy->set_y_pos(rand_y_);

            pEnemy->set_input_left(0);

            Bullet* p_bullet = new Bullet[1];
            pEnemy->InitBullet(p_bullet, gScreen);
            listEnemies.push_back(pEnemy);
        }
    }

    EnemiesObiect* tank_enemies = new EnemiesObiect[20];

    for (int i = 0; i < 20; i++)
    {
        EnemiesObiect* pEnemy = (tank_enemies + i);
        if (pEnemy != NULL)
        {
            int rand_y_ = SDLCommonFunc::MakeRandValue();
            pEnemy->LoadImg("assert/enemy_tank.png", gScreen);
            pEnemy->SetClips();
            pEnemy->set_x_pos(700 + i*rand_y_*3 + 750);
            pEnemy->set_y_pos(250);
            pEnemy->set_type_move(EnemiesObiect::STATIC_ENEMY);
            pEnemy->set_input_left(0);

            Bullet* p_bullet = new Bullet[1];
            pEnemy->InitBullet(p_bullet, gScreen);
            listEnemies.push_back(pEnemy);
        }
    }
    return listEnemies;
}
