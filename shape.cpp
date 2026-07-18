#include <cmath>
#include "shape.h"

#define MEU_PI 3.14159265358979323846

using namespace std;

///
/// LEITURA DE FORMAS DO ARQUIVO
///

/// Faz os passos comuns para ler qualquer forma.
/// Leh cor e largura do contorno.
void Shape::read(istream& X)
{
  X >> r >> g >> b >> width;
  if (!X.good() || r<0 || r>255 || g<0 || g>255 || b<0 || b>255 || width<=0)
    throw ios_base::failure("invalid shape parameters");
}

/// Faz os passos comuns para ler qualquer forma preenchivel.
/// Leh cor e largura do contorno (usando Shape::read) e depois se eh preenchida.
void FilledShape::read(istream& X)
{
  Shape::read(X); // Gera excecao se houver erro
  int Filled;
  X >> Filled;
  if (!X.good())
    throw ios_base::failure("invalid filled shape parameters");
  filled = (Filled != 0);
}

/// Leh uma linha de uma stream.
/// Leh cor e largura do contorno (usando Shape::read) e depois os 2 pontos.
/* ACRESCENTAR */
void Line::read(istream& X) {
    Shape::read(X);
    X >> x1 >> y1 >> x2 >> y2;
    if (!X.good() || x1<0 || y1<0 || x2<0 || y2<0) throw ios_base::failure("invalid line");
}

/// Leh um circulo de uma stream.
/// Leh cor, largura do contorno e se eh preenchida (usando FilledShape::read)
/// e depois o centro e o raio.
/* ACRESCENTAR */
void Circle::read(istream& X) {
    FilledShape::read(X);
    X >> cx >> cy >> raio;
    if (!X.good() || cx<0 || cy<0 || raio<0) throw ios_base::failure("invalid circle");
}

/// Leh um retangulo de uma stream.
/// Leh cor, largura do contorno e se eh preenchida (usando FilledShape::read)
/// e depois os limites.
/* ACRESCENTAR */
void Rectangle::read(istream& X) {
    FilledShape::read(X);
    X >> x_min >> x_max >> y_min >> y_max;
    if (!X.good() || x_min<0 || x_max<0 || y_min<0 || y_max<0) throw ios_base::failure("invalid rect");
    if (x_min > x_max) swap(x_min, x_max);
    if (y_min > y_max) swap(y_min, y_max);
}
/// Leh um triangulo de uma stream.
/// Leh cor, largura do contorno e se eh preenchida (usando FilledShape::read)
/// e depois os 3 pontos.
/* ACRESCENTAR */
void Triangle::read(istream& X) {
    FilledShape::read(X);
    X >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    if (!X.good() || x1<0 || y1<0 || x2<0 || y2<0 || x3<0 || y3<0) throw ios_base::failure("invalid tri");
}
/// Leh um losango de uma stream.
/// Leh cor, largura do contorno e se eh preenchida (usando FilledShape::read)
/// e depois os limites.
/* ACRESCENTAR */
void Rhombus::read(istream& X) {
    FilledShape::read(X);
    X >> x_min >> x_max >> y_min >> y_max;
    if (!X.good() || x_min<0 || x_max<0 || y_min<0 || y_max<0) throw ios_base::failure("invalid rhombus");
    if (x_min > x_max) swap(x_min, x_max);
    if (y_min > y_max) swap(y_min, y_max);
}

/// Leh uma estrela de uma stream.
/// Leh cor, largura do contorno e se eh preenchida (usando FilledShape::read)
/// e depois o centro e o raio.
/* ACRESCENTAR */
void Star::read(istream& X) {
    FilledShape::read(X);
    X >> cx >> cy >> raio;
    if (!X.good() || cx<0 || cy<0 || raio<0) throw ios_base::failure("invalid star");
}
///
/// SALVAMENTO DAS FIGURAS
///

/// Faz os passos comuns para salvar qualquer forma.
/// Salva cor e largura da linha.
void Shape::save(ostream& X) const
{
  X << " stroke=" << '"' << "rgb("
    << r << ',' << g << ',' << b << ')' << '"';
  X << " stroke-width=" << '"' << width << '"';
}

/// Faz os passos comuns para salvar qualquer forma preenchivel.
/// Usa Shape::save e depois salva cor do preenchimento.
void FilledShape::save(ostream& X) const
{
  Shape::save(X);
  if (filled)
  {
    X << " fill=" << '"' << "rgb("
      << r << ',' << g << ',' << b << ')' << '"';
  }
  else
  {
    X << " fill=" << '"' << "none" << '"';
  }
}

/// Salva uma linha.
/// Salva o inicio "<line" e os parametros do elemento;
/// depois, salva os parametros de estilo, usando Shape::save;
/// depois, salva o final "/>" do elemento.
/* ACRESCENTAR */
void Line::save(ostream& X) const {
    X << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\"";
    Shape::save(X);
    X << " />";
}

/// Salva um circulo.
/// Salva o inicio "<circle" e os parametros do elemento;
/// depois, salva os parametros de estilo, usando FilledShape::save;
/// depois, salva o final "/>" do elemento.
/* ACRESCENTAR */
void Circle::save(ostream& X) const{
    X << "<circle r=\"" << raio << "\" cx=\"" << cx << "\" cy=\"" << cy <<"\"";
    FilledShape::save(X);
    X << " />";

}
/// Salva um retangulo
/// Salva o inicio "<rect" e os parametros do elemento;
/// depois, salva os parametros de estilo, usando FilledShape::save;
/// depois, salva o final "/>" do elemento.
/* ACRESCENTAR */
void Rectangle::save(ostream& X) const{
    int w_rect = x_max - x_min ; //+1 removido para igualar os pixels
    int h_rect = y_max - y_min ; //+1 removido para igualar os pixels

    X << "<rect x=\"" << x_min << "\" y=\"" << y_min << "\" width=\"" << w_rect << "\" height=\"" << h_rect << "\"";
    FilledShape::save(X);
    X << " />";
}
/// Salva um triangulo
/// Salva o inicio "<polygon" e os parametros (3 pontos) do elemento;
/// depois, salva os parametros de estilo, usando FilledShape::save;
/// depois, salva o final "/>" do elemento.
/* ACRESCENTAR */
void Triangle::save(ostream& X) const {
    X << "<polygon points=\"" << x1 << "," << y1 << " " << x2 << "," << y2 << " " << x3 << "," << y3 << "\"";
    FilledShape::save(X);
    X << " />";
}

/// Salva um losango
/// Salva o inicio "<polygon" e os parametros (4 pontos) do elemento;
/// depois, salva os parametros de estilo, usando FilledShape::save;
/// depois, salva o final "/>" do elemento.
/* ACRESCENTAR */
void Rhombus::save(ostream& X) const {
    int x_med = (x_min + x_max)/2;
    int y_med = (y_min + y_max)/2;
    X << "<polygon points=\"" << x_min << "," << y_med << " " << x_med << "," << y_min
      << " " << x_max << "," << y_med << " " << x_med << "," << y_max << "\"";
    FilledShape::save(X);
    X << " />";
}
/// Salva uma estrela
/// Salva o inicio "<polygon" e os parametros (10 pontos) do elemento;
/// depois, salva os parametros de estilo, usando FilledShape::save;
/// depois, salva o final "/>" do elemento.
/* ACRESCENTAR */
void Star::save(ostream& X) const {
    X << "<polygon points=\"";
    for(int i=0; i<10; i++) {
        double theta = MEU_PI * i/5.0 + MEU_PI * 1/2;
        double rp = (i%2==0) ? raio : raio/2.5;
        double xp = cx + rp*cos(theta);
        double yp = cy - rp*sin(theta);
        X << xp << "," << yp << (i<9 ? " " : "");
    }
    X << "\"";
    FilledShape::save(X);
    X << " />";
}


/// IMPLEMENTAÇÃO DOS MÉTODOS CLONE

Shape* Line::clone() const {
    return new Line(*this);
}

Shape* Circle::clone() const {
    return new Circle(*this);
}

Shape* Rectangle::clone() const {
    return new Rectangle(*this);
}

Shape* Triangle::clone() const {
    return new Triangle(*this);
}

Shape* Rhombus::clone() const {
    return new Rhombus(*this);
}

Shape* Star::clone() const {
    return new Star(*this);
}
