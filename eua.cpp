#include <iostream>
#include <cmath> // Para round
#include "designer.h"

using namespace std;

/// Programa para desenhar, reduzir tamanho pela metade e salvar
/// a bandeira dos EUA, usando a classe Image

int main(void)
{
  // A constante ALTURA_LINHA significa quantos pixels de altura vai ter
  // cada uma das 13 linhas da bandeira.
  // As demais dimensoes são calculadas para manter as proporcoes corretas.
  const int ALTURA_LINHA = 40;
  const int altura_bandeira = 13*ALTURA_LINHA;
  const int largura_bandeira = round(24.7*ALTURA_LINHA);
  const int raio_estrela = round(0.25*ALTURA_LINHA);

  // Variaveis auxiliares
  int r,g,b; // Cor
  int lin,col;
  int i,j;

  Designer X(largura_bandeira, altura_bandeira);

  // Um contorno preto
  X.include(Rectangle(0,0,0,1,true,
                      0,largura_bandeira-1,
                      0,altura_bandeira-1));

  // Desenha as 13 linhas
  for (i=0; i<13; ++i)
  {
    if (i%2 == 0)  // VERMELHO
    {
      r = 191;
      g = 10;
      b = 48;
    }
    else // BRANCO
    {
      r = 255;
      g = 255;
      b = 255;
    }
    X.include(Rectangle(r,g,b,1,true,
                        1,largura_bandeira-2,
                        i*ALTURA_LINHA, (i+1)*ALTURA_LINHA-1));
  }

  // Desenha o campo azul para as estrelas
  r = 0;
  g = 32;
  b = 91;
  X.include(Rectangle(r,g,b,1,true,
                      0,10*ALTURA_LINHA-1, 0,7*ALTURA_LINHA-1));

  // Desenha as estrelas brancas
  r = 255;
  g = 255;
  b = 255;

  // Desenha as 5 linhas com 6 estrelas em cada
  for (i=0; i<5; ++i)
  {
    lin = round((7.0/10.0)*ALTURA_LINHA*(1+2*i));
    for (j=0; j<6; ++j)
    {
      col = round((10.0/12.0)*ALTURA_LINHA*(1+2*j));
      X.include(Star(r,g,b,1,true,
                     col, lin, raio_estrela));
    }
  }

  // Desenha as 4 linhas com 5 estrelas em cada
  for (i=0; i<4; ++i)
  {
    lin = round((7.0/10.0)*ALTURA_LINHA*(2+2*i));
    for (j=0; j<5; ++j)
    {
      col = round((10.0/12.0)*ALTURA_LINHA*(2+2*j));
      X.include(Star(r,g,b,1,true,
                     col, lin, raio_estrela));
    }
  }

  const string arquivo="eua.svg";

  X.save(arquivo);
  cout << "Arquivo " << arquivo << " salvo!\n";

  return 0;
}
