\# Designer — Gerador de Desenhos SVG em C++



Programa em C++ que lê um "roteiro" de formas geométricas a partir de um

arquivo de texto e gera um desenho no formato \*\*SVG\*\*, desenvolvido na

disciplina de Programação Avançada. Utiliza hierarquia de classes e

polimorfismo para representar as diferentes formas.



Inclui exemplos que desenham bandeiras de países (EUA, Grécia) inteiramente

a partir de formas geométricas básicas.



\## Funcionalidades



\- Hierarquia de formas com herança e polimorfismo (`Shape` → `FilledShape` → formas concretas)

\- Formas suportadas: linha, círculo, estrela, retângulo, losango e triângulo

\- Leitura de um roteiro de formas a partir de arquivo de texto

\- Geração e exportação do desenho em formato \*\*SVG\*\*

\- Suporte a cor (RGB) e largura de contorno configuráveis por forma

\- Formas preenchidas ou apenas com contorno



\## Estrutura do projeto



```

shape.h             // Hierarquia de classes das formas geométricas

shape.cpp           // Implementação de leitura/gravação de cada forma

designer.h          // Classe Designer (composição do desenho)

designer.cpp        // Implementação do Designer (leitura do roteiro, geração do SVG)

designer-main.cpp   // Programa principal (lê roteiro e gera o arquivo SVG)

eua.cpp             // Exemplo: desenha a bandeira dos EUA

grecia.cpp          // Exemplo: desenha a bandeira da Grécia

exemplo.txt          // Roteiro de exemplo com formas diversas

brasil.txt           // Roteiro com as formas da bandeira do Brasil

```



\## Como compilar e executar



Programa principal (lê um roteiro de formas e gera um SVG):

```bash

g++ -std=c++17 -o designer designer-main.cpp designer.cpp shape.cpp

./designer

```

O programa pede o nome do arquivo de roteiro (ex: `exemplo.txt` ou `brasil.txt`)

e o nome do arquivo `.svg` a ser gerado.



Exemplos de bandeiras (cada um é um programa independente):

```bash

g++ -std=c++17 -o eua eua.cpp designer.cpp shape.cpp \&\& ./eua

g++ -std=c++17 -o grecia grecia.cpp designer.cpp shape.cpp \&\& ./grecia

```



\## Conceitos de C++ aplicados



\- Herança e polimorfismo (funções virtuais puras, `override`)

\- Padrão \*prototype\* (método `clone()`)

\- Ponteiros e gerenciamento de memória (`vector<Shape\*>`)

\- Sobrecarga de operadores de atribuição por cópia e movimento

\- Leitura e escrita de arquivos (`ifstream`/`ofstream`)

\- Geração de saída em formato SVG (vetor gráfico)



\## Autor



Alexandre Kennedy Rodrigues da Fonseca

