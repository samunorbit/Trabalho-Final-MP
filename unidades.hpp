#include <bits/stdc++.h>

/*
serao usados inteiros para os diferentes tipos de unidades
valores negativos correspondem a unidades inimigas
recurso 0 recurso
soldado 1 quadradinho
arqueiro 2	retangulo
cavaleiro 3	_|_
coletor 4 triangulo
quartel 5
campo de arco 6
estabulo 7
escavadeira 8
base 9
*/
class Unidades
{
	std::vector<int> unidades_x, unidades_y, unidades_tipos;
	int n_unidades, contador_RetornaUnidades;
	int frame, segundo;

	//propriedades globais das unidades
	int cooldown_soldado, cooldown_aqrqueiro, cooldown_cavaleiro; 
	int velocidade_soldado, velocidade_arqueiro, velocidade_cavaleiro, velocidade_coletor;


public:
	
	int vida_quartel, vida_estabulo, vida_campo_de_arco, vida_escavadeira, vida_base;

	Unidades();

	~Unidades();

	//unico tipo de unidade q pode ser criada pelo jogador sao QUARTEL, ESTABULO, ESCAVADEIRA e BASES
	//retorna falso quando ja existe uma unidade na posicao
	bool CriaUnidade(int x, int y, int tipo);
	bool CriaUnidade(int x, int y);

	//retorna falso quando nao existe uma unidade na posicao
	bool DestroiUnidade(int x, int y);

	//retorna falso nao existe uma unidade na posicao ou existe uma unidade na posicao que a unidade foi movida
	bool MoveUnidade(int x, int y, int novo_x, int novo_y);
	bool MoveUnidade(int indice, int destino_x, int destino_y);

	//cada vez chamada atribui as coodenadas e tipo uma unidade nao repetida 
	//retorna falso quando percorreu rodas unidades
	bool RetornaUnidades(int *x, int *y, int *tipo);
	bool RetornaUnidades(int *x, int *y);

	//cada vez chamda atribui as cordenadas do tipo de unidade pedida
	//retorna falso quando ja percorreu todas as unidades do tipo pedido
	//volta ao começo da lista quando outro tipo de unidade é pedido
	bool RetornaUnidadesPorTipo(int tipo,int *x, int *y);

	//executa as interaçoes entre as unidades e reseta RetornaUnidades e RetornaUnidadesPorTipo
	void AtualizaUniadades();

	//reseta os contadores de RetornaUnidades e RetornaUnidadesPorTipo
	inline void ResetaContadores(){contador_RetornaUnidades = 0;}

	// retorna o numero total de unidades em jogo
	inline int get_n_unidades(){return n_unidades;}
};