#include "game.hpp"

Unidades::Unidades()
{
    n_unidades=0;
    contador_RetornaUnidades=0;
    velocidade_soldado=2;
    velocidade_arqueiro=1;
    velocidade_cavaleiro=5;
    velocidade_coletor=3;
    vida_quartel=40;
    vida_estabulo=50;
    vida_campo_de_arco=50;
    vida_escavadeira=80;
    vida_base=100;    
    srand((unsigned)time(NULL));

}

Unidades::~Unidades()
{
}

bool Unidades::CriaUnidade(int x, int y, int tipo)
{
    for (int i = 0; i < unidades_tipos.size(); i++)
    {
        if(x == unidades_x[i])
        {
            if(y == unidades_y[i])
            {
                //ja existe uma unidade na posicao
                return false;
            }
        }
    }
    unidades_x.push_back(x);
    unidades_y.push_back(y);
    unidades_tipos.push_back(tipo);
    n_unidades++;
    return true;
}

bool Unidades::CriaUnidade(int x, int y)
{
    for (int i = 0; i < unidades_tipos.size(); i++)
    {
        if(x == unidades_x[i])
        {
            if(y == unidades_y[i])
            {
                //ja existe uma unidade na posicao
                return false;
            }
        }
    }
    unidades_x.push_back(x);
    unidades_y.push_back(y);
    n_unidades++;
    return true;
}

bool Unidades::DestroiUnidade(int x, int y)
{
    for (int i = 0; i < n_unidades; i++)
    {
        if(x == unidades_x[i])
        {
            if(y == unidades_y[i])
            {
                unidades_x.erase(unidades_x.begin()+i);
                unidades_y.erase(unidades_y.begin()+i);
                unidades_tipos.erase(unidades_tipos.begin()+i);
                n_unidades--;
                return true;
            }
        }
    }
    return false;
}

bool Unidades::RetornaUnidades(int *x, int *y, int *tipo)
{
    if(n_unidades==0)
        return false;

    if(n_unidades > contador_RetornaUnidades)
    {
        *x = unidades_x[contador_RetornaUnidades];
        *y = unidades_y[contador_RetornaUnidades];
        *tipo = unidades_tipos[contador_RetornaUnidades];
        contador_RetornaUnidades++;
        return true;
    }
    return false;
}

bool Unidades::RetornaUnidades(int *x, int *y)
{
    if(n_unidades==0)
        return false;

    if(n_unidades > contador_RetornaUnidades)
    {
        *x = unidades_x[contador_RetornaUnidades];
        *y = unidades_y[contador_RetornaUnidades];
        contador_RetornaUnidades++;
        return true;
    }
    return false;
}

void Unidades::AtualizaUniadades()
{
    //Aqui vai ta toda logica do jogo

    for (int i = 0; i < n_unidades; i++)
    {
        int distancia=2000, temp_distancia, temp_indice;
        if(unidades_tipos[i] == 1 || unidades_tipos[i] == -1)
        {
            for (int j = 0; j < n_unidades; j++)
            {
                if((i != j) && ((unidades_tipos[i]>0 && unidades_tipos[j]<0)||(unidades_tipos[i]<0 && unidades_tipos[j]>0)))
                {
                    temp_distancia = unidades_x[i] + unidades_y[i] - unidades_x[j] - unidades_y[j];
                    if(temp_distancia<0)
                    {
                        temp_distancia = temp_distancia * (-1);
                    }
                    if(temp_distancia < distancia)
                    {
                        distancia = temp_distancia;
                        temp_indice = j;
                    }
                }
            }

            if(distancia != 2000)
            {
                //colocar comportamento para quando a unidade estiver no mesmo eixo, provavelmente incremento ou decremento aleatorio
                if(unidades_x[i]<unidades_x[temp_indice])
                {
                    unidades_x[i]++;
                }

                if(unidades_x[i]>unidades_x[temp_indice])
                {
                    unidades_x[i]--;
                }

                if(unidades_x[i]==unidades_x[temp_indice])
                {
                    unidades_x[i]+= ((int) rand()%3)-1;
                }

                if(unidades_y[i]<unidades_y[temp_indice])
                {
                    unidades_y[i]++;
                }

                if(unidades_y[i]>unidades_y[temp_indice])
                {
                    unidades_y[i]--;
                }

                if(unidades_y[i]==unidades_y[temp_indice])
                {
                    unidades_y[i]+= ((int) rand()%3)-1;
                }
            }
        }

        if(unidades_tipos[i]==2)
        {

        }

        if(unidades_tipos[i]==3)
        {

        }

        if(unidades_tipos[i]==4)
        {

        }
    }
}


State::State(SDL_Window *window, SDL_Renderer *renderer, int width, int height)
{
    this->width = width;
    this->height = height;
    this->window = window;
    quit_requested = false;
    this->renderer = renderer;
    window_surface = SDL_GetWindowSurface(window);
    game_speed = 10;
    quit_requested = false;
    x = 0;
    y = 0;
    mouse_x = 0;
    mouse_y = 0;
    temp_flag = 1;
}

State::~State()
{

}

void State::Input()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {

        case SDL_QUIT:
            events_list.push_back(QUIT);
            break;

        case SDL_MOUSEMOTION:
            mouse_x = event.motion.x;
            mouse_y = event.motion.y;
            break;

        case SDL_MOUSEBUTTONDOWN:
            events_list.push_back(LEFT_CLICK);
            break;

        case SDL_KEYDOWN:

            switch(event.key.keysym.sym)
            {

            case SDLK_ESCAPE:
                events_list.push_back(QUIT);
                break;

            case SDLK_UP:
                events_list.push_back(UP);
                break;

            case SDLK_DOWN:
                events_list.push_back(DOWN);
                break;

            case SDLK_LEFT:
                events_list.push_back(LEFT);
                break;

            case SDLK_RIGHT:
                events_list.push_back(RIGHT);
                break;

            case SDLK_1:
                events_list.push_back(NUM_1);
                break;

            case SDLK_2:
                events_list.push_back(NUM_2);
                break;

            case SDLK_3:
                events_list.push_back(NUM_3);
                break;

            case SDLK_4:
                events_list.push_back(NUM_4);
                break;

            case SDLK_5:
                events_list.push_back(NUM_5);
                break;

            case SDLK_6:
                events_list.push_back(NUM_6);
                break;

            case SDLK_7:
                events_list.push_back(NUM_7);
                break;

            case SDLK_8:
                events_list.push_back(NUM_8);
                break;

            case SDLK_9:
                events_list.push_back(NUM_9);
                break;
            }
            break;
        }
    }
}

void State::Update()
{
    event last_event;

    while(events_list.size() != 0)
    {
        last_event = events_list.back();
        events_list.pop_back();

        switch(last_event)
        {
        case QUIT:
            quit_requested = true;
            break;

        case UP:
            temp_flag = -1;
            break;

        case DOWN:
            temp_flag = 1;
            break;

        case LEFT:

            break;

        case RIGHT:

            break;

        case RIGHT_CLICK:

            break;

        case LEFT_CLICK:

            break;

        case NUM_1:
            unidades.CriaUnidade(mouse_x,mouse_y,1 * temp_flag);
            break;

        case NUM_2:
            unidades.CriaUnidade(mouse_x,mouse_y,2 * temp_flag);
            break;

        case NUM_3:
            unidades.CriaUnidade(mouse_x,mouse_y,3 * temp_flag);
            break;

        case NUM_4:
            unidades.CriaUnidade(mouse_x,mouse_y,4 * temp_flag);
            break;

        case NUM_5:
            unidades.CriaUnidade(mouse_x,mouse_y,5 * temp_flag);
            break;

        case NUM_6:
            unidades.CriaUnidade(mouse_x,mouse_y,6 * temp_flag);
            break;

        case NUM_7:
            unidades.CriaUnidade(mouse_x,mouse_y,7 * temp_flag);
            break;

        case NUM_8:
            unidades.CriaUnidade(mouse_x,mouse_y,8 * temp_flag);
            break;

        case NUM_9:
            unidades.CriaUnidade(mouse_x,mouse_y,9 * temp_flag);
            break;

        }
    }
}

void State::Render()
{
    int temp_x, temp_y, temp_tipo;
    SDL_SetRenderDrawColor(renderer,255,0,255,255);
    SDL_RenderClear(renderer);
    SDL_Rect retangulo;

    retangulo.w = 10;
    retangulo.h = 10;

    while(unidades.RetornaUnidades(&temp_x, &temp_y, &temp_tipo))
    {
        if(temp_tipo > 0)
        {
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
        }

        if(temp_tipo == 1 || temp_tipo == -1)
        {
            retangulo.w = 5;
            retangulo.h = 5;
            retangulo.x = temp_x;
            retangulo.y = temp_y;
            SDL_RenderFillRect(renderer,&retangulo);
        }

        if(temp_tipo == 2 || temp_tipo == -2)
        {
            retangulo.w = 5;
            retangulo.h = 10;
            retangulo.x = temp_x;
            retangulo.y = temp_y;
            SDL_RenderFillRect(renderer,&retangulo);

        }

        if(temp_tipo == 3 || temp_tipo == -3)
        {
            retangulo.w = 4;
            retangulo.h = 10;

            retangulo.x = temp_x + 3;
            retangulo.y = temp_y;
            SDL_RenderFillRect(renderer,&retangulo);

            retangulo.w = 10;
            retangulo.h = 4;
            retangulo.x = temp_x;
            retangulo.y = temp_y + 6;
            SDL_RenderFillRect(renderer,&retangulo);

        }

        if(temp_tipo == 4 || temp_tipo == -4)
        {
            retangulo.w = 1;
            retangulo.h = 1;
            retangulo.x = temp_x;
            for (int i = 0; i < 10; ++i)
            {
                retangulo.w += 1;
                retangulo.y = temp_y + i;
                SDL_RenderFillRect(renderer,&retangulo);
            }

        }

        if(temp_tipo == 5 || temp_tipo == -5)
        {

        }

        if(temp_tipo == 6 || temp_tipo == -6)
        {

        }

        if(temp_tipo == 7 || temp_tipo == -7)
        {

        }

        if(temp_tipo == 8 || temp_tipo == -8)
        {

        }

        if(temp_tipo == 9 || temp_tipo == -9)
        {

        }
    }
    unidades.ResetaContadores();
    unidades.AtualizaUniadades();

    SDL_RenderPresent(renderer);

}

Game::Game()
{
    name = "GAME";
    window_is_open = false;
    window = NULL;
    renderer = NULL;
    width = 0;
    height = 0;
}


int Game::set_game(int width, int height, std::string name)
{

    this->width=width;
    this->height=height;
    this->name=name;
}

void Game::init_game()
{
    window_is_open=true;
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout<<"ERRO_1:"<<SDL_GetError() << std::endl;
    }
    else
    {
        SDL_Window *window = SDL_CreateWindow(name.c_str(),
                                              SDL_WINDOWPOS_UNDEFINED,
                                              SDL_WINDOWPOS_UNDEFINED,
                                              width, height,
                                              SDL_WINDOW_OPENGL);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    }
    //SDL_ShowCursor(SDL_DISABLE);
}

void Game::Run()
{
    State state(window,renderer, width, height);
    while(!(state.QuitRequest()))
    {
        state.Input();
        state.Update();
        state.Render();
    }
}
