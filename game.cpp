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
}

Unidades::~Unidades()
{
}

bool Unidades::CriaUnidade(int x, int y, tipo_unidade tipo)
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

bool Unidades::RetornaUnidades(int *x, int *y, tipo_unidade *tipo)
{
    if(n_unidades >= contador_RetornaUnidades)
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
    if(n_unidades==0)return false;

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
        unidades_x[i]++;
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
            y-= game_speed;
            break;

        case DOWN:
            y+= game_speed;
            break;

        case LEFT:
            x-= game_speed;
            break;

        case RIGHT:
            x+= game_speed;
            break;

        case LEFT_CLICK:
            unidades.CriaUnidade(mouse_x,mouse_y);
            break;

        }
    }
}

void State::Render()
{
    int temp_x, temp_y;
    SDL_SetRenderDrawColor(renderer,255,0,255,255);
    SDL_RenderClear(renderer);
    SDL_Rect retangulo;

    retangulo.w = 10;
    retangulo.h = 10;



    
    while(unidades.RetornaUnidades(&temp_x, &temp_y))
    {
        SDL_SetRenderDrawColor(renderer,0,255,0,255);
        retangulo.x = temp_x;
        retangulo.y = temp_y;
        SDL_RenderFillRect(renderer,&retangulo);   
    }
    unidades.ResetaContadores();
    unidades.AtualizaUniadades();

    SDL_RenderPresent(renderer);

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
