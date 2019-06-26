#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include "unidades.hpp"

class State
{
private:
	enum event
	{
		QUIT,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		LEFT_CLICK,
		RIGHT_CLICK,
		NUM_1,
		NUM_2,
		NUM_3,
		NUM_4,
		NUM_5,
		NUM_6,
		NUM_7,
		NUM_8,
		NUM_9,
		PAUSA
	};
	bool quit_requested;
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Surface *window_surface;
	std::vector<event> events_list;
	int width, height;
	int x, y, mouse_x, mouse_y;
	int game_speed;
	Unidades unidades;
	int temp_flag;
	bool PAUSED;
	
public:
	State(SDL_Window *window, SDL_Renderer *renderer, int width, int height);

	~State();

	inline bool QuitRequest(){return quit_requested;}

	inline void set_game_speed(int game_speed){this->game_speed=game_speed;}
	
	//Salva as entradas relevantes do mousse e teclado na events_list
	void Input();

	//Percorre events_list executando as acoes apropriadas para cada evento registrado
	void Update();

	//Funcao onde todas as renderizacoes sao feitas
	void Render();

};


class Game
{
private:
    int width, height;
    std::string name;
    bool window_is_open;
    SDL_Window *window;
    SDL_Renderer *renderer;

public:
	Game();

    ~Game()
    {
    	window_is_open=false;
    	SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    inline bool is_open(){return window_is_open;}

    //inicia o loop primario do jogo
    void Run();

    //Recebe o resolucao e o nome da janela a ser criada
    int set_game(int width, int height, std::string name);

    //inicia funcoes essenciais da biblioteca SDL2
    void init_game();
};