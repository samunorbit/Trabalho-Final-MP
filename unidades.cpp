#include "unidades.hpp"

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
    cooldown_soldado = 5;
    cooldown_aqrqueiro = 60;
    cooldown_cavaleiro = 1;
    segundo = 0;
    frame = 0;
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

bool Unidades::DestroiUnidade(int indice)
{
    unidades_x.erase(unidades_x.begin()+indice);
    unidades_y.erase(unidades_y.begin()+indice);
    unidades_tipos.erase(unidades_tipos.begin()+indice);
    n_unidades--;
    return true;
}

int Unidades::VerificaCoodenada(int x, int y)
{
    for (int i = 0; i < n_unidades; i++)
    {
        if(unidades_x[i] == x && unidades_y[i] == y)
        {
            return unidades_tipos[i];
        }
    }
    return -1;
}

bool Unidades::MoveUnidade(int indice, int destino_x, int destino_y)
{
    int relative_x = destino_x - unidades_x[indice], relative_y = destino_y - unidades_y[indice];
    if(relative_x == 0)
    {
        if(relative_y == 0)
        {
            //a unidade esta no destino
            return false;
        }

        if(relative_y > 0)
        {
            if(VerificaCoodenada(unidades_x[indice],unidades_y[indice]+1)==-1)
            {
                unidades_y[indice]++;
            }
            return true;
        }

        if (relative_y < 0)
        {
            if(VerificaCoodenada(unidades_x[indice],unidades_y[indice]-1)==-1)
            {
                unidades_y[indice]--;
            }
            return true;
        }
    }

    if(relative_x > 0)
    {
        if(relative_y == 0)
        {

            if(VerificaCoodenada(unidades_x[indice]+1,unidades_y[indice])==-1)
            {
                unidades_x[indice]++;
            }
            return true;
        }

        if(relative_y > 0)
        {
            if(relative_x > relative_y)
            {
                if(VerificaCoodenada(unidades_x[indice]+1,unidades_y[indice])==-1)
                {
                    unidades_x[indice]++;
                }
                if((int) rand()%2)
                {
                    if(VerificaCoodenada(unidades_x[indice],unidades_y[indice]+1)==-1)
                    {
                        unidades_y[indice]++;
                    }
                }
                return true;
            }

            if(relative_x == relative_y)
            {
                if(VerificaCoodenada(unidades_x[indice]+1,unidades_y[indice])==-1)
                {
                    unidades_x[indice]++;
                }
                if(VerificaCoodenada(unidades_x[indice],unidades_y[indice]+1)==-1)
                {
                    unidades_y[indice]++;
                }
            }

            if(relative_x < relative_y)
            {
                if(VerificaCoodenada(unidades_x[indice],unidades_y[indice]+1)==-1)
                {
                    unidades_y[indice]++;
                }
                if((int) rand()%2)
                {
                    if(VerificaCoodenada(unidades_x[indice]+1,unidades_y[indice])==-1)
                    {
                        unidades_x[indice]++;
                    }
                }
                return true;
            }

        }

        if (relative_y < 0)
        {
            if(relative_x > -relative_y)
            {
                if(VerificaCoodenada(unidades_x[indice]+1,unidades_y[indice])==-1)
                {
                    unidades_x[indice]++;
                }
                if((int) rand()%2)
                {
                    if(VerificaCoodenada(unidades_x[indice],unidades_y[indice]-1)==-1)
                    {
                        unidades_y[indice]--;
                    }
                }
                return true;
            }

            if(relative_x == -relative_y)
            {
                if(VerificaCoodenada(unidades_x[indice]+1,unidades_y[indice])==-1)
                {
                    unidades_x[indice]++;
                }
                if(VerificaCoodenada(unidades_x[indice],unidades_y[indice]-1)==-1)
                {
                    unidades_y[indice]--;
                }
            }

            if(relative_x < -relative_y)
            {
                if(VerificaCoodenada(unidades_x[indice],unidades_y[indice]-1)==-1)
                {
                    unidades_y[indice]--;
                }
                if((int) rand()%2)
                {
                    if(VerificaCoodenada(unidades_x[indice]+1,unidades_y[indice])==-1)
                    {
                        unidades_x[indice]++;
                    }
                }
                return true;
            }
        }
    }

    if(relative_x < 0)
    {
        if(relative_y == 0)
        {
            if(VerificaCoodenada(unidades_x[indice]-1,unidades_y[indice])==-1)
            {
                unidades_x[indice]--;
            }
            return true;
        }

        if(relative_y > 0)
        {
            if(-relative_x > relative_y)
            {
                if(VerificaCoodenada(unidades_x[indice]-1,unidades_y[indice])==-1)
                {
                    unidades_x[indice]--;
                }
                if((int) rand()%2)
                {
                    if(VerificaCoodenada(unidades_x[indice],unidades_y[indice]+1)==-1)
                    {
                        unidades_y[indice]++;
                    }
                }
                return true;
            }

            if(-relative_x == relative_y)
            {
                if(VerificaCoodenada(unidades_x[indice]-1,unidades_y[indice])==-1)
                {
                    unidades_x[indice]--;
                }
                if(VerificaCoodenada(unidades_x[indice],unidades_y[indice]+1)==-1)
                {
                    unidades_y[indice]++;
                }
            }

            if(-relative_x < relative_y)
            {
                if(VerificaCoodenada(unidades_x[indice],unidades_y[indice]+1)==-1)
                {
                    unidades_y[indice]++;
                }
                if((int) rand()%2)
                {
                    if(VerificaCoodenada(unidades_x[indice]-1,unidades_y[indice])==-1)
                    {
                        unidades_x[indice]--;
                    }
                }
                return true;
            }

        }

        if (relative_y < 0)
        {
            if(-relative_x > -relative_y)
            {
                if(VerificaCoodenada(unidades_x[indice]-1,unidades_y[indice])==-1)
                {
                    unidades_x[indice]--;
                }
                if((int) rand()%2)
                {
                    if(VerificaCoodenada(unidades_x[indice],unidades_y[indice]-1)==-1)
                    {
                        unidades_y[indice]--;
                    }
                }
                return true;
            }

            if(relative_x == relative_y)
            {
                if(VerificaCoodenada(unidades_x[indice]-1,unidades_y[indice])==-1)
                {
                    unidades_x[indice]--;
                }
                if(VerificaCoodenada(unidades_x[indice],unidades_y[indice]-1)==-1)
                {
                    unidades_y[indice]--;
                }
            }

            if(-relative_x < -relative_y)
            {
                if(VerificaCoodenada(unidades_x[indice],unidades_y[indice]-1)==-1)
                {
                    unidades_y[indice]--;
                }
                if((int) rand()%2)
                {
                    if(VerificaCoodenada(unidades_x[indice]-1,unidades_y[indice])==-1)
                    {
                        unidades_x[indice]--;
                    }
                }
                return true;
            }
        }

    }
}

int Unidades::InimigoMaisProximo(int indice)
{
    int distancia=2000,temp_distancia ,temp_distancia_x,temp_distancia_y, temp_indice;
    for (int j = 0; j < n_unidades; j++)
    {
        if((indice != j) && ((unidades_tipos[indice]>0 && unidades_tipos[j]<0) || (unidades_tipos[indice]<0 && unidades_tipos[j]>0)))
        {
            temp_distancia_x = unidades_x[indice] - unidades_x[j] ;

            if(temp_distancia_x<0)
            {
                temp_distancia_x = temp_distancia_x * (-1);
            }

            temp_distancia_y = unidades_y[indice] - unidades_y[j];

            if(temp_distancia_y<0)
            {
                temp_distancia_y = temp_distancia_y * (-1);
            }
            temp_distancia = temp_distancia_x + temp_distancia_y;

            if(temp_distancia < distancia)
            {
                distancia = temp_distancia;
                temp_indice = j;
            }
        }
    }

    if(distancia != 2000)
    {
        return temp_indice;
    }
    return -1;
}

int Unidades::InimigoMaisProximo(int indice, int *dist)
{
    int distancia=2000, temp_distancia, temp_indice;
    for (int j = 0; j < n_unidades; j++)
    {
        if((indice != j) && ((unidades_tipos[indice]>0 && unidades_tipos[j]<0)||(unidades_tipos[indice]<0 && unidades_tipos[j]>0)))
        {
            temp_distancia = unidades_x[indice] + unidades_y[indice] - unidades_x[j] - unidades_y[j];
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
        *dist = distancia;
        return temp_indice;
    }
    return -1;
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
    int temp_x,temp_y;
    frame++;
    if(frame == 60)
    {
        segundo++;
        frame = 0;
    }

    for (int i = 0; i < n_unidades; i++)
    {
        int j = InimigoMaisProximo(i);

        if(unidades_tipos[i]==5||unidades_tipos[i]==-5)
        {
            CriaUnidade(unidades_x[i]-1,unidades_y[i],unidades_tipos[i]/5);
        }

        if(j !=-1 && (unidades_tipos[i] <= 4 && unidades_tipos[i] >= -4 && unidades_tipos[i] != 0))
        {
            MoveUnidade(i,unidades_x[j],unidades_y[j]);
            temp_x = unidades_x[i] - unidades_x[j];
            temp_y = unidades_y[i] - unidades_y[j];
            if(temp_x < 2 && temp_x > -2 && temp_y < 2 && temp_y > -2)
            {
                DestroiUnidade(i);
                DestroiUnidade(j);
            }
        }

    }
}
