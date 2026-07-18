#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <iostream>

class Shape;
typedef Shape* pShape;

/// Classe base de todas as formas
class Shape
{
public:
  // Construtor (especifico e default)
  Shape(int R=0, int G=0, int B=0, int W=1):
    r(R),
    g(G),
    b(B),
    width(W)
  {}

  virtual ~Shape() {}
  virtual Shape* clone() const = 0;

  // Leh uma forma generica de uma stream.
  // Leh a cor da forma e a largura do contorno.
  virtual void read(std::istream& X);

  // Salva a cor da forma e a largura do contorno em formato SVG
  virtual void save(std::ostream& X) const;

protected:
  // A cor da forma.
  // Precisa ser consultado pela FilledShape (por isso eh protegido).
  int r,g,b;

private:
  // Largura do contorno da forma
  int width=1;
};

/// Classe base de todas as formas que podem ser preenchidas ou nao
class FilledShape: public Shape
{
public:
  // Construtor (especifico e default)
  FilledShape(int R=0, int G=0, int B=0, int W=1, bool F=true):
    Shape(R,G,B,W),
    filled(F)
  {}

  // Leh uma forma preenchivel generica de uma stream.
  // Leh cor e largura (usando Shape::read) e depois se eh preenchida ou nao.
  virtual void read(std::istream& X);

  // Salva a forma preenchivel em formato SVG.
  // Salva a cor e largura (usando Shape::save) e o depois se eh preenchida ou nao.
  virtual void save(std::ostream& X) const;

private:
  // forma preenchida ou nao
  bool filled=false;
};

/// Classe que representa linhas
/* ACRESCENTAR */
class Line : public Shape {
    int x1, y1, x2, y2;
public:
    Line(int R=0, int G=0, int B=0, int W=1, int X1=0, int Y1=0, int X2=0, int Y2=0)
        : Shape(R,G,B,W), x1(X1), y1(Y1), x2(X2), y2(Y2) {}
    void read(std::istream& X) override;
    void save(std::ostream& X) const override;
    Shape* clone() const override;
};
/// Classe que representa circulos
/* ACRESCENTAR */
class Circle : public FilledShape {
    int cx, cy, raio;
public:
    Circle(int R=0, int G=0, int B=0, int W=1, bool F=true, int Cx=0, int Cy=0, int Raio=0)
        : FilledShape(R,G,B,W,F), cx(Cx), cy(Cy), raio(Raio) {}
    void read(std::istream& X) override;
    void save(std::ostream& X) const override;
    Shape* clone() const override;
};
/// Classe que representa estrelas
/* ACRESCENTAR */
class Star : public FilledShape {
    int cx, cy, raio;
public:
    Star(int R=0, int G=0, int B=0, int W=1, bool F=true, int Cx=0, int Cy=0, int Raio=0)
        : FilledShape(R,G,B,W,F), cx(Cx), cy(Cy), raio(Raio) {}
    void read(std::istream& X) override;
    void save(std::ostream& X) const override;
    Shape* clone() const override;
};
/// Classe que representa retangulos
/* ACRESCENTAR */
class Rectangle : public FilledShape {
    int x_min, x_max, y_min, y_max;
public:
    Rectangle(int R=0, int G=0, int B=0, int W=1, bool F=true, int Xm=0, int XM=0, int Ym=0, int YM=0)
        : FilledShape(R,G,B,W,F), x_min(Xm), x_max(XM), y_min(Ym), y_max(YM) {}
    void read(std::istream& X) override;
    void save(std::ostream& X) const override;
    Shape* clone() const override;
};
/// Classe que representa losangos
/* ACRESCENTAR */
class Rhombus : public FilledShape {
    int x_min, x_max, y_min, y_max;
public:
    Rhombus(int R=0, int G=0, int B=0, int W=1, bool F=true, int Xm=0, int XM=0, int Ym=0, int YM=0)
        : FilledShape(R,G,B,W,F), x_min(Xm), x_max(XM), y_min(Ym), y_max(YM) {}
    void read(std::istream& X) override;
    void save(std::ostream& X) const override;
    Shape* clone() const override;
};
/// Classe que representa triangulos
/* ACRESCENTAR */
class Triangle : public FilledShape {
    int x1, y1, x2, y2, x3, y3;
public:
    Triangle(int R=0, int G=0, int B=0, int W=1, bool F=true, int X1=0, int Y1=0, int X2=0, int Y2=0, int X3=0, int Y3=0)
        : FilledShape(R,G,B,W,F), x1(X1), y1(Y1), x2(X2), y2(Y2), x3(X3), y3(Y3) {}
    void read(std::istream& X) override;
    void save(std::ostream& X) const override;
    Shape* clone() const override;
};
#endif // _SHAPE_H_
