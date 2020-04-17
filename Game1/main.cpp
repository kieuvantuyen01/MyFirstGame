/* KHAI BAO THU VIEN */
#include<iostream>
#include<cstdlib>
#include<ctime>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "Map.h"
#include "MainObject.h"
#include "Timer.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "Text.h"
#include "DataGame.h"
#include "Geometric.h"
#include "Menu.h"

// Khai bao doi tuong Background la bien toan cuc
BaseObject gBackground;

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
        gSound_bullet[0] = Mix_LoadWAV("sound/Fire0.wav");
        gSound_bullet[1] = Mix_LoadWAV("sound/Fire1.wav");
        gSound_bullet[2] = Mix_LoadWAV("sound/Fire2.wav");
        gSound_explosion = Mix_LoadWAV("sound/explosion.wav");
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

/* HAM LOAD BACKGROUND */

bool LoadBackground()
{
    bool ret = gBackground.LoadImg("img/background.png", gScreen);
    if (ret == false)
    {
        std::cout << "Can not Load Background: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

/* HAM HUY BIEN CON TRO VA THOAT */

void close()
{
    gBackground.Free();
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

std::vector<ThreatsObiect*> MakeThreadList()
{
    std::vector<ThreatsObiect*> list_threats;
    srand(time(0));

    ThreatsObiect* dynamic_threats = new ThreatsObiect[20];
    for (int i = 0; i < 20; i++)
    {
        ThreatsObiect* p_threat = (dynamic_threats+i);
        if (p_threat != NULL)
        {
            int rand_y_ = SDLCommonFunc::MakeRandValue();
            p_threat->LoadImg("img/threat_left.png", gScreen);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatsObiect::MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos(500 + i*rand_y_*2 + 400);
            p_threat->set_y_pos(200);

            int pos1 = p_threat->get_x_pos() - 60;
            int pos2 = p_threat->get_x_pos() + 60;
            p_threat->SetAnimationPos(pos1, pos2);
            p_threat->set_input_left(1);
            list_threats.push_back(p_threat);
        }
    }

    ThreatsObiect* plane_threats = new ThreatsObiect[20];
    for (int i = 0; i < 20; i++)
    {
        ThreatsObiect* p_threat = (plane_threats+i);
        if (p_threat != NULL)
        {
            int rand_y_ = SDLCommonFunc::MakeRandValue();
            p_threat->LoadImg("img/plane_left.png", gScreen);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatsObiect::FLY_THREAT);
            p_threat->set_x_pos(600 + i*rand_y_*3 + 700);
            p_threat->set_y_pos(rand_y_);

            p_threat->set_input_left(0);

            BulletObject* p_bullet = new BulletObject[1];
            p_threat->InitBullet(p_bullet, gScreen);
            list_threats.push_back(p_threat);
        }
    }

    ThreatsObiect* threat_objs = new ThreatsObiect[20];

    for (int i = 0; i < 20; i++)
    {
        ThreatsObiect* p_threat = (threat_objs + i);
        if (p_threat != NULL)
        {
            int rand_y_ = SDLCommonFunc::MakeRandValue();
            p_threat->LoadImg("img/threat_level.png", gScreen);
            p_threat->set_clips();
            p_threat->set_x_pos(700 + i*rand_y_*3 + 750);
            p_threat->set_y_pos(250);
            p_threat->set_type_move(ThreatsObiect::STATIC_THREAT);
            p_threat->set_input_left(0);

            BulletObject* p_bullet = new BulletObject[1];
            p_threat->InitBullet(p_bullet, gScreen);
            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}

/* HAM MAIN */

int main(int argc, char* argv[])
{
    // Bien xu ly FPS
    //Thuat toan nay tham khao tren kenh phattrienphanmem123az.com
    Timer fps_timer;

    // Kiem tra viec khoi tao SDL va Background

    if (Init() == false)
    {
        std::cout << "Can not Init Data: " << SDL_GetError() << std::endl;
        return -1;
    }

    if (LoadBackground() == false)
    {
        std::cout << "Can not load background: " << IMG_GetError() << std::endl;
        return -1;
    }


    //Khoi tao va Load Ban do Game
    GameMap game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.SetTiles(gScreen);

    //Khoi tao va Load nhan vat chinh
    MainObject p_player;
    p_player.LoadImg("img/player_right_.png", gScreen);
    p_player.set_clips();

    //Khoi tao bien quan ly quan ly cac thong so game
    DataGame game_data;
    game_data.Init(gScreen);

    //Khoi tao bien quan ly Duoc
    PlayerTorch player_torch;
    player_torch.Init(gScreen);
    player_torch.SetPos(20, 100);

    std::vector<ThreatsObiect*>threats_list = MakeThreadList();

    //Khoi tao bien xu ly va cham
    ExplosionObject exp_threat;
    bool tRet = exp_threat.LoadImg("img/exp.png", gScreen);
    if (!tRet)
    {
        return -1;
    }
    exp_threat.set_clip();

    ExplosionObject exp_main;
    bool mRet = exp_main.LoadImg("img/exp1.png", gScreen);
    if (!mRet)
    {
        return -1;
    }
    exp_main.set_clip();

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

    //Khoi tao bien xu ly Load Menu
    Menu menu_game;
	menu_game.LoadImg("img/menu.png", gScreen);
	menu_game.SetPostionText();

	//Khoi tao bien xu ly thong bao diem
	BaseObject score_message;
	score_message.setRect(380, 90);
	bool sret = score_message.LoadImg("img/score.png", gScreen);
	if(!sret) return -1;

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
        fps_timer.start();
        while(SDL_PollEvent(&gEvent) != 0)
        {
            if (gEvent.type == SDL_QUIT)
            {
                is_quit = true;
                is_show_score = false;
            }
            //Xu ly trang thai ban dau cua nhan vat
            p_player.HandelInputAction(gEvent, gSound_bullet, gScreen);
        }


        SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(gScreen);

        //Hien thi Background
        gBackground.Render(gScreen, NULL);

        Map map_data = game_map.getMap();

        //Hien thi nhan vat
        p_player.HandleBullet(gScreen);
        p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
        p_player.DoPlayer(map_data);
        p_player.Show(gScreen);

        //Hien thi ban do Game
        game_map.SetMap(map_data);
        game_map.DrawMap(gScreen);

        //Ve khung chua cac thong so game
        GeometricFormat rectangle_size{0, 0, SCREEN_WIDTH/4, SCREEN_HEIGHT/4};
        ColorData color_data1{237, 28, 36};
        Geometric::RenderRectangle(rectangle_size, color_data1, gScreen);

        GeometricFormat outline_size(1, 1, SCREEN_WIDTH/4, SCREEN_HEIGHT/4-2);
        ColorData color_data2{0, 0, 0};
        Geometric::RenderOutline(outline_size, color_data2, gScreen);

        //Hien thi thong so Game
        game_data.Show(gScreen);
        player_torch.Show(gScreen);

        //Xu ly va cham
        for (int i = 0; i < threats_list.size(); i++)
        {
            //Xu ly vi tri cua nhan vat, cho nhan vat di chuyen, tao dan ban va hien thi
            ThreatsObiect* p_threat = threats_list.at(i);
            if (p_threat != NULL)
            {
                p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
                p_threat->ImpMoveType(gScreen);
                p_threat->DoPlayer(map_data);
                p_threat->GenerateBullet(gScreen, SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threat->Show(gScreen);

                //kiem tra va cham giua nhan vat game va dan cua cac Enemies
                SDL_Rect rect_player = p_player.GetRectFrame();
                bool bCol1 = false;
                std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
                for (int idx1 = 0; idx1 < tBullet_list.size(); idx1++)
                {
                    BulletObject* pt_bullet = tBullet_list.at(idx1);
                    if (pt_bullet)
                    {
                        bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player);
                        if (bCol1)
                        {
                            p_threat->RemoveBullet(idx1);
                            break;
                        }
                    }
                }

                //Kiem tra va cham giua nhan vat game va enemies
                SDL_Rect rect_threat = p_threat->GetRectFrame();
                bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);

                if (bCol1 || bCol2)
                {
                    int fr_exp_width = exp_main.get_frame_width();
                    int fr_exp_height = exp_main.get_frame_height();
                    for (int idx2 = 0; idx2 < NUM_FRAME_EXP; idx2++)
                    {
                        //Dat frame hinh vao tam cua vu no
                        int x_pos = (p_player.GetRect().x + p_player.GetRectFrame().w*0.5) - fr_exp_width*0.5;
                        int y_pos = (p_player.GetRect().y + p_player.GetRectFrame().h*0.5) - fr_exp_height*0.5;

                        exp_main.set_frame(idx2);
                        exp_main.setRect(x_pos, y_pos);
                        exp_main.Show(gScreen);
                        SDL_RenderPresent(gScreen);
                    }

                    Mix_PlayChannel(-1, gSound_ex_main, 0);
                    num_die++;

                    if (num_die <= NUM_DIE)
                    {
                        p_player.setRect(0, 0);
                        p_player.set_come_back_time(60);
                        SDL_Delay(1000);
                        game_data.Decrease();
                        game_data.Render(gScreen);
                        continue;
                    }
                    else
                    {
                        is_show_score = true;
                        p_threat->Free();
                        is_quit = true;
                    }
                }
            }
        }

        //Kiem tra va cham giua dan nhan vat va cac enemies
        std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
        for (int i = 0; i < bullet_arr.size(); i++)
        {
            BulletObject* p_bullet = bullet_arr.at(i);
            if (p_bullet != NULL)
            {
                for (int j = 0; j < threats_list.size(); j++)
                {
                    ThreatsObiect* obj_threat = threats_list.at(j);
                    if (obj_threat != NULL)
                    {
                        SDL_Rect tRect;
                        tRect.x = obj_threat->GetRect().x;
                        tRect.y = obj_threat->GetRect().y;
                        //Lay mot frame cua Enemies
                        tRect.w = obj_threat->get_width_frame();
                        tRect.h = obj_threat->get_height_frame();

                        SDL_Rect bRect = p_bullet->GetRect();

                        bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);
                        if (bCol)
                        {
                            score_value ++;
                            int frame_exp_width = exp_threat.get_frame_width();
                            int frame_exp_height = exp_threat.get_frame_height();
                            for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
                            {
                                // dat frame vao tam cua vu no
                                int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5;
                                int y_pos = p_bullet->GetRect().y - frame_exp_height*0.5;

                                exp_threat.set_frame(ex);
                                exp_threat.setRect(x_pos, y_pos);
                                exp_threat.Show(gScreen);
                            }
                            p_player.RemoveBullet(i);
                            obj_threat->Free();
                            threats_list.erase(threats_list.begin()+j);
                            Mix_PlayChannel(-1, gSound_explosion, 0);
                        }
                    }
                }
            }
        }

        bool won_ = p_player.getRes();
        if (won_)
        {
            is_show_score = true;
            is_quit = true;
            bool sret = score_message.LoadImg("img/happy.png", gScreen);
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
        std::string strScore("ENEMIES: ");
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

        //Xu ly khung hinh tren giay FPS
        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND; //don vi ms

        if (real_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_imp_time;
            if (delay_time >= 0)
            {
                SDL_Delay(delay_time);
            }
        }
    }

    //Xoa cac con tro lien quan den dan ban
    for (int i = 0; i < threats_list.size(); i++)
    {
        ThreatsObiect* p_threat = threats_list.at(i);
        if (p_threat)
        {
            p_threat->Free();
            p_threat = NULL;
        }
    }
    threats_list.clear();

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
