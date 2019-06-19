#include <bits/stdc++.h>
#include <SDL2/SDL.h>

class Unidades
{
private:
	enum tipo_unidade
	{
		SOLDADO,
		SOLDADO_INIMIGO,
		ARQUEIRO,
		ARQUEIRO_INIMIGO,
		CAVALEIRO,
		CAVALEIRO_INIMIGO,
		COLETOR,
		COLETOR_INIMIGO,
		QUARTEL,
		QUARTEL_INIMIGO,
		CAMPO_DE_ARCO,
		CAMPO_DE_ARCO_INIMIGO,
		ESTABULO,
		ESTABULO_INIMIGO,
		ESCAVADEIRA,
		ESCAVADEIRA_INIMIGA,
		BASE,
		BASE_INIMIGA
	};

	std::vector<int> unidades_x, unidades_y;
	std::vector<tipo_unidade> unidades_tipos;
	int n_unidades, contador_RetornaUnidades;

	//propriedades globais das unidades 
	int velocidade_soldado, velocidade_arqueiro, velocidade_cavaleiro, velocidade_coletor;
	int vida_quartel, vida_estabulo, vida_campo_de_arco, vida_escavadeira, vida_base;

public:

	Unidades();

	~Unidades();

	//unico tipo de unidade q pode ser criada pelo jogador sao QUARTEL, ESTABULO, ESCAVADEIRA e BASES
	//retorna falso quando ja existe uma unidade na posicao
	bool CriaUnidade(int x, int y, tipo_unidade tipo);
	bool CriaUnidade(int x, int y);

	//retorna falso quando nao existe uma unidade na posicao
	bool DestroiUnidade(int x, int y);

	//retorna falso nao existe uma unidade na posicao ou existe uma unidade na posicao que a unidade foi movida
	bool MoveUnidade(int x, int y, int novo_x, int novo_y);

	//cada vez chamada atribui as coodenadas e tipo uma unidade nao repetida 
	//retorna falso quando percorreu rodas unidades
	bool RetornaUnidades(int *x, int *y, tipo_unidade *tipo);
	bool RetornaUnidades(int *x, int *y);

	//cada vez chamda atribui as cordenadas do tipo de unidade pedida
	//retorna falso quando ja percorreu todas as unidades do tipo pedido
	//volta ao começo da lista quando outro tipo de unidade é pedido
	bool RetornaUnidadesPorTipo(tipo_unidade tipo,int *x, int *y);

	//executa as interaçoes entre as unidades e reseta RetornaUnidades e RetornaUnidadesPorTipo
	void AtualizaUniadades();

	//reseta os contadores de RetornaUnidades e RetornaUnidadesPorTipo
	inline void ResetaContadores(){contador_RetornaUnidades = 0;}

	// retorna o numero total de unidades em jogo
	inline int get_n_unidades(){return n_unidades;}
};


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
		NUM_2
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
    std::string name = "GAME";
    bool window_is_open = false;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

public:
	Game()
	{

	}

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