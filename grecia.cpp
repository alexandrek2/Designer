#include <iostream>
#include <cmath> // Para round
#include "designer.h"

using namespace std;


int main(void)
{
  const int ALTURA_LINHA = 60; // (540 total / 9 listras)
  const int largura_bandeira = 27 * 30; // 810
  const int altura_bandeira  = 18 * 30; // 540


  int r, g, b; // Cor
  int lin, col;
  int i, j;

  Designer X(largura_bandeira, altura_bandeira);

  for (i=0; i<9; ++i)
  {
    if (i%2 == 0)  // AZUL
    {
      r = 13; g = 94; b = 175;
    }
    else // BRANCO
    {
      r = 255; g = 255; b = 255;
    }

    X.include(Rectangle(r,g,b,1,true,
                        0, largura_bandeira-1,
                        i*ALTURA_LINHA, (i+1)*ALTURA_LINHA-1));
  }

  r = 255; g = 255; b = 255;
  X.include(Rectangle(r,g,b,1,true,
                      0, 5*ALTURA_LINHA-1,
                      0, 5*ALTURA_LINHA-1));
  r = 13; g = 94; b = 175;

  int tamanho_quadrado = 2 * ALTURA_LINHA;

  for (i=0; i<2; ++i)
  {
    lin = i * (tamanho_quadrado + ALTURA_LINHA);

    for (j=0; j<2; ++j)
    {
      col = j * (tamanho_quadrado + ALTURA_LINHA);

      X.include(Rectangle(r,g,b,1,true,
                          col, col + tamanho_quadrado - 1,
                          lin, lin + tamanho_quadrado - 1));
    }
  }

  const string arquivo="grecia.svg";

  X.save(arquivo);
  cout << "Arquivo " << arquivo << " salvo!\n";

  return 0;
}
