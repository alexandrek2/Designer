#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "designer.h"

using namespace std;

/// Construtor especifico
Designer::Designer(int Width, int Height):
  width(Width>=0 ? Width : 0), height(Height>=0 ? Height : 0), VS()
{}

/// Construtor por copia
/* ACRESCENTAR */
Designer::Designer(const Designer& D) : width(D.width), height(D.height),VS(D.VS.size(), nullptr)
{

   for(int i = 0; i < (int)D.VS.size(); ++i)
        {
        if (D.VS.at(i) != nullptr) VS.at(i) = D.VS.at(i)->clone();
        }
}
/// Construtor por movimento
/* ACRESCENTAR */
Designer::Designer(Designer&& D) : Designer()
{
  std::swap(width, D.width);
  std::swap(height, D.height);
  VS.swap(D.VS);
}
/// Atribuicao por copia
Designer& Designer::operator=(const Designer& D)
{
    if (this == &D) return *this;

    this->clear();
    width = D.width;
    height = D.height;
    VS.resize(D.VS.size(),nullptr);
    for(int i = 0; i < (int)D.VS.size(); ++i)
  {
  if (D.VS.at(i) != nullptr) VS.at(i) = D.VS.at(i)->clone();
  }

  return *this;
}

/// Atribuicao por movimento
Designer& Designer::operator=(Designer&& D)
{
  if (this == &D) return *this;
  this->clear();
  std::swap(width, D.width);
  std::swap(height, D.height);
  VS.swap(D.VS);
  return *this;
}

/// Limpa o desenho
void Designer::clear()
{
  width = height = 0;
  /* ACRESCENTAR */

  for (auto P : VS) delete P;
  VS.clear();
}


/// Inclusao de nova forma no desenho
/// Inclusao de nova forma no desenho
void Designer::include(const Shape& S)
{
    // Usa o metodo clone (que implementamos no shape.cpp) para criar uma copia
    VS.push_back(S.clone());
}

/// Leitura de arquivo com as formas
void Designer::read(const string& fileName)
{
  ifstream arq(fileName);
  if (!arq.is_open())
  {
    string msg = "could not open file "+fileName;
    throw ios_base::failure(msg);
  }

  // Leh o cabecalho
  string texto;
  int W,H;
  arq >> texto >> W >> H;
  if (!arq.good() || texto!="DESIGNER" || W<=0 || H<=0)
    throw ios_base::failure("invalid file");

  // Cria um novo Designer temporario, inicialmente vazio (sem formas)
  Designer prov(W,H);

  // Laco de leitura das diversas formas do desenho.
  // Permanece ateh o fim do arquivo.
  bool arquivo_acabou = false;
  char tipo_forma;

  do
  {
    // Leh o tipo de forma (char)
    arq >> tipo_forma;
    // Testa se acabou o arquivo
    if (!arq.good())
    {
      arquivo_acabou = true;
      continue;
    }
    tipo_forma = toupper(tipo_forma);
    // Cria dinamicamente (aloca) a nova forma de acordo com o caractere lido.
    // Se o caractere nao for nenhum dos identificadores de formas,
    // ignora o restante da linha do arquivo
    /* ACRESCENTAR */
    pShape novo = nullptr; // Ponteiro temporário para a nova forma

    switch (tipo_forma)
    {
      case '-': // Hífen = Linha
        novo = new Line;
        break;
      case 'C': // C = Círculo
        novo = new Circle;
        break;
      case 'R': // R = Retângulo
        novo = new Rectangle;
        break;
      case 'T': // T = Triângulo
        novo = new Triangle;
        break;
      case 'L': // L = Losango
        novo = new Rhombus;
        break;
      case 'S': // S = Estrela
        novo = new Star;
        break;
      default:
        arq.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    // Se a nova forma foi alocada (caractere corresponde a uma das formas):
    // - Leh a forma do arquivo
    // - Acrescenta a forma no Designer temporario (prov)
    /* ACRESCENTAR */
    if (novo != nullptr)
    {
      try
      {
        novo->read(arq);
        prov.VS.push_back(novo);
      }
      catch (...)
      {
        delete novo; // Limpa a memória em caso de falha na leitura
        throw;       // Repassa a exceção
      }
    }
  }
  while(!arquivo_acabou);

  // Testa o numero de formas lidas
  if (prov.getNumShapes() == 0) throw ios_base::failure("empty file");

  // Faz *this assumir o conteudo de prov
  *this = move(prov);
}

/// Salvamento do desenho em formato SVG
void Designer::save(const string& fileName) const
{
  // Nao exporta se o desenho for vazio
  if (getNumShapes()==0 || width<=0 || height<=0) throw logic_error("empty designer");

  // Abre o arquivo SVG para escrita
  ofstream arq(fileName);
  if (!arq.is_open())
  {
    string msg = "could not open file "+fileName;
    throw ios_base::failure(msg);
  }

  // Escreve o cabecalho inicial
  arq << "<svg"
      << " width=" << '"' << width << '"'
      << " height=" << '"' << height << '"'
      << " xmlns=" << '"' << "http://www.w3.org/2000/svg"  << '"'
      << ">\n";

  // Salva as formas
  for (auto S : VS)
  {
    S->save(arq);
    arq << endl;
  }

  // Escreve o rodapeh final
  arq << "</svg>" << endl;
}
