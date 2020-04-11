
#include<iostream>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "Text.h"
#include "PlayerPower.h"
#include "Geometric.h"
#include "Menu.h"

BaseObject g_background;
TTF_Font* font_time = NULL;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
    {
        std::cout << "Can not Initialize: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("Game by Kieu Van Tuyen", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if (g_window == NULL)
    {
        std::cout << "Can not create Window: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
        {
            std::cout << "Can not render screen: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
            {
                std::cout << "Can not Init IMG: " << SDL_GetError() << std::endl;
                success = false;
            }
        }

        if (TTF_Init() == -1)
        {
            success = false;
        }

        font_time = TTF_OpenFont("font/dlxfont_.ttf", 15);
        if (font_time == NULL)
        {
            success = false;
        }

        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        {
            return false;
        }
        g_end = Mix_LoadWAV("sound/ncbtndt.wav");
        g_sound = Mix_LoadMUS("sound/gpmn.wav");
        g_sound_bullet[0] = Mix_LoadWAV("sound/Laser.wav");
        g_sound_bullet[1] = Mix_LoadWAV("sound/Fire.wav");
        g_sound_bullet[2] = Mix_LoadWAV("sound/Fire1.wav");
        g_sound_explosion = Mix_LoadWAV("sound/Bomb1.wav");
        g_sound_ex_main = Mix_LoadWAV("sound/Explosion+1.wav");

        if (g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL
            || g_sound_explosion == NULL || g_sound_ex_main == NULL
            || g_sound == NULL || g_end == NULL)
        {
            return false;
        }
    }
    return success;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("img/background.png", g_screen);
    if (ret == false)
    {
        std::cout << "Can not Load Background: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    TTF_CloseFont(font_time);
    font_time = NULL;

    Mix_FreeChunk(g_sound_bullet[0]);
    g_sound_bullet[0] = NULL;
    Mix_FreeChunk(g_sound_bullet[1]);
    g_sound_bullet[1] = NULL;
    Mix_FreeChunk(g_sound_bullet[2]);
    g_sound_bullet[2] = NULL;
    Mix_FreeChunk(g_end);
    g_sound_bullet[0] = NULL;
    Mix_FreeChunk(g_sound_explosion);
    g_sound_explosion = NULL;
    Mix_FreeChunk(g_sound_ex_main);
    g_sound_ex_main = NULL;

    Mix_FreeMusic(g_sound);
    g_sound = NULL;

    IMG_Quit();
    SDL_Quit();
}

std::vector<ThreatsObiect*> MakeThreadList()
{
    std::vector<ThreatsObiect*> list_threats;


    ThreatsObiect* dynamic_threats = new ThreatsObiect[20];
    for (int i = 0; i < 20; i++)
    {
        ThreatsObiect* p_threat = (dynamic_threats+i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("img/threat_left.png", g_screen);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatsObiect::MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos(500 + i*500);
            p_threat->set_y_pos(200);

            int pos1 = p_threat->get_x_pos() - 60;
            int pos2 = p_threat->get_x_pos() + 60;
            p_threat->SetAnimationPos(pos1, pos2);
            p_threat->set_input_left(1);
            list_threats.push_back(p_threat);
        }
    }



    ThreatsObiect* threat_objs = new ThreatsObiect[20];

    for (int i = 0; i < 20; i++)
    {
        ThreatsObiect* p_threat = (threat_objs + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("img/threat_level.png", g_screen);
            p_threat->set_clips();
            p_threat->set_x_pos(700 + i*1200);
            p_threat->set_y_pos(250);
            p_threat->set_type_move(ThreatsObiect::STATIC_THREAT);
            p_threat->set_input_left(0);

            BulletObject* p_bullet = new BulletObject[1];
            p_threat->InitBullet(p_bullet, g_screen);
            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}
int main(int argc, char* argv[])
{
    ImpTimer fps_timer;

    if (InitData() == false)
    {
        std::cout << "Can not Init Data: " << SDL_GetError() << std::endl;
        return -1;
    }
    if (LoadBackground() == false)
    {
        std::cout << "Can not load background: " << IMG_GetError() << std::endl;
        return -1;
    }


    GameMap game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTiles(g_screen);


    MainObject p_player;
    p_player.LoadImg("img/player_right_.png", g_screen);
    p_player.set_clips();

    PlayerPower player_power;
    player_power.Init(g_screen);

    PlayerMoney player_money;
    player_money.Init(g_screen);
    player_money.SetPos(SCREEN_WIDTH*0.5-300, 0);

    std::vector<ThreatsObiect*>threats_list = MakeThreadList();

    ExplosionObject exp_threat;
    bool tRet = exp_threat.LoadImg("img/exp.png", g_screen);
    if (!tRet)
    {
        return -1;
    }
    exp_threat.set_clip();

    ExplosionObject exp_main;
    bool mRet = exp_main.LoadImg("img/exp1.png", g_screen);
    if (!mRet)
    {
        return -1;
    }
    exp_main.set_clip();

    int num_die = 0;

    //Time text
    Text time_game;
    time_game.SetColor(Text::YELLOW_TEXT);

    Text mark_game;
    mark_game.SetColor(Text::YELLOW_TEXT);
    UINT mark_value = 0;

    Text money_game;
    money_game.SetColor(Text::YELLOW_TEXT);

    bool is_quit = false;
    bool is_show_score=true;

    Menu menu_game;
	menu_game.LoadImg("img/menu.png", g_screen);
	menu_game.SetPostionText();

	BaseObject score_message;
	score_message.setRect(200,150);
	bool ret=score_message.LoadImg("img/score.png",g_screen);
	if(!ret) return -1;

	while(menu_game.is_show_)
	{
		while(SDL_PollEvent(&g_event)!=0)
		{
			if(g_event.type==SDL_QUIT)
			{
				menu_game.is_show_=false;
				is_quit=true;
				is_show_score=false;
			}
			menu_game.CheckEvents(g_event,is_quit,is_show_score);
		}
		SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
		menu_game.CreateText(font_time, g_screen);
		menu_game.RenderMenu(g_screen);
		SDL_RenderPresent(g_screen);
		SDL_Delay(100);
	}

    while(!is_quit)
    {
        fps_timer.start();
        while(SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
                is_show_score=false;
            }

            p_player.HandelInputAction(g_event, g_sound_bullet, g_screen);
        }
        if(Mix_PlayingMusic()==0)
		{
			Mix_PlayMusic(g_sound,-1);
		}

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);

        Map map_data = game_map.getMap();

        p_player.HandleBullet(g_screen);
        p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
        p_player.DoPlayer(map_data);
        p_player.Show(g_screen);


        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);

        //Draw Geometric
        GeometricFormat rectangle_size{0, 0, SCREEN_WIDTH, 40};
        ColorData color_data1{237, 28, 36};
        Geometric::RenderRectangle(rectangle_size, color_data1, g_screen);

        GeometricFormat outline_size(1, 1, SCREEN_WIDTH, 38);
        ColorData color_data2{0, 0, 0};
        Geometric::RenderOutline(outline_size, color_data2, g_screen);

        player_power.Show(g_screen);
        player_money.Show(g_screen);

        for (int i = 0; i < threats_list.size(); i++)
        {
            ThreatsObiect* p_threat = threats_list.at(i);
            if (p_threat != NULL)
            {
                p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
                p_threat->ImpMoveType(g_screen);
                p_threat->DoPlayer(map_data);
                p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threat->Show(g_screen);

                SDL_Rect rect_player = p_player.GetRectFrame();
                bool bCol1 = false;
                std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
                for (int jj = 0; jj < tBullet_list.size(); jj++)
                {
                    BulletObject* pt_bullet = tBullet_list.at(jj);
                    if (pt_bullet)
                    {
                        bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player); //kiem tra va cham giua nhan vat game va dan cua cac nhan vat hiem hoa
                        if (bCol1)
                        {
                            p_threat->RemoveBullet(jj);
                            break;
                        }
                    }
                }

                SDL_Rect rect_threat = p_threat->GetRectFrame();
                bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat); // kiem tra va cham giua nhan vat game va threats
                if (bCol1 || bCol2)
                {
                    int fr_exp_width = exp_main.get_frame_width();
                    int fr_exp_height = exp_main.get_frame_height();
                    for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
                    {
                        int x_pos = (p_player.GetRect().x + p_player.GetRectFrame().w*0.5) - fr_exp_width*0.5; // dat frame vao tam cua vu no
                        int y_pos = (p_player.GetRect().y + p_player.GetRectFrame().h*0.5) - fr_exp_height*0.5;

                        exp_main.set_frame(ex);
                        exp_main.setRect(x_pos, y_pos);
                        exp_main.Show(g_screen);
                        SDL_RenderPresent(g_screen);
                    }
                    Mix_PlayChannel(-1, g_sound_ex_main, 0);
                    num_die++;
                    if (num_die <= 3)
                    {
                        p_player.setRect(0, 0);
                        p_player.set_come_back_time(60);
                        SDL_Delay(1000);
                        player_power.Decrease();
                        player_power.Render(g_screen);
                        continue;
                    }
                    else
                    {
                        is_show_score = true;
                        if (MessageBoxW(NULL, L"GAME OVER", L"Infor", MB_OK | MB_ICONSTOP) == IDOK)
                        {
                            p_threat->Free();
                            close();
                            SDL_Quit();
                            return 0;
                        }
                    }
                }
            }
        }

        std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
        for (int r = 0; r < bullet_arr.size(); r++)
        {
            BulletObject* p_bullet = bullet_arr.at(r);
            if (p_bullet != NULL)
            {
                for (int t = 0; t < threats_list.size(); t++)
                {
                    ThreatsObiect* obj_threat = threats_list.at(t);
                    if (obj_threat != NULL)
                    {
                        SDL_Rect tRect;
                        tRect.x = obj_threat->GetRect().x;
                        tRect.y = obj_threat->GetRect().y;
                        tRect.w = obj_threat->get_width_frame(); //lay mot frame cua nhan vat hiem hoa
                        tRect.h = obj_threat->get_height_frame();

                        SDL_Rect bRect = p_bullet->GetRect();

                        bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);
                        if (bCol)
                        {
                            mark_value ++;
                            int frame_exp_width = exp_threat.get_frame_width();
                            int frame_exp_height = exp_threat.get_frame_height();
                            for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
                            {
                                int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5; // dat frame vao tam cua vu no
                                int y_pos = p_bullet->GetRect().y - frame_exp_height*0.5;

                                exp_threat.set_frame(ex);
                                exp_threat.setRect(x_pos, y_pos);
                                exp_threat.Show(g_screen);
                            }
                            p_player.RemoveBullet(r);
                            obj_threat->Free();
                            threats_list.erase(threats_list.begin()+t);
                            Mix_PlayChannel(-1, g_sound_explosion, 0);
                        }
                    }
                }
            }
        }

        //Show game time
        std::string str_time = "TIME: ";
        Uint32 time_val = SDL_GetTicks()/1000; //thoi gian hien tai
        Uint32 val_time = 304 - time_val;
        if (val_time <= 0)
        {
            is_show_score = true;
            if (MessageBoxW(NULL, L"GAME OVER", L"Infor", MB_OK | MB_ICONSTOP) == IDOK)
            {
                is_quit = true;
                break;
            }
        }
        else
        {
            std::string str_val = std::to_string(val_time);
            str_time += str_val;

            time_game.SetText(str_time);
            time_game.LoadFromRenderText(font_time, g_screen);
            time_game.RenderText(g_screen, SCREEN_WIDTH-200, 15);
        }

        std::string val_str_mark = std::to_string(mark_value);
        std::string strMark("MARK: ");
        strMark += val_str_mark;

        mark_game.SetText(strMark);
        mark_game.LoadFromRenderText(font_time, g_screen);
        mark_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 50, 15);

        int money_count = p_player.GetMoneyCount();
        std::string money_str = std::to_string(money_count);

        money_game.SetText(money_str);
        money_game.LoadFromRenderText(font_time, g_screen);
        money_game.RenderText(g_screen, SCREEN_WIDTH*0.5-250, 15);

        SDL_RenderPresent(g_screen);

        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND; //ms

        if (real_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_imp_time;
            if (delay_time >= 0)
                SDL_Delay(delay_time);
        }
    }
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

    if(is_show_score)
	{
//		mark_game.SetText(to_string(score));
//		score_text.CreateText(g_screen,font_time);
//		score_message.Render(g_screen);
		mark_game.setRect(score_message.GetRect().x+190,score_message.GetRect().y+250);
		mark_game.Render(g_screen);
		SDL_RenderPresent(g_screen);
		//Mix_PlayChannel(-1,g_end,0);
		SDL_Delay(2500);
	}

    close();
    return 0;
}
