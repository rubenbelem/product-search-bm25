## Product Search with BM25 ranking

### Rúben Jozafá Silva Belém

As instruções a seguir foram testadas nos sistemas _Ubuntu 18.04 Bionic Beaver_ e _Linux Mint 19.2 "Tina" Cinnamon_.

#### Instalação de dependências

Primeiramente, é necessário possuir o _Git_ instalado. É possível instalá-lo com o comando:

```
sudo apt install git
```

Para compilar o programa, é necessária a instalação do _CMake_, _Make_ e _g++_, e _libreadline-dev_, com o comando:

```
sudo apt install cmake make g++ libreadline-dev
```

#### Clonando o repositório

É preciso clonar este repositório com o Git, e então navegar até o diretório clonado (o diretório raíz do projeto, _<dir_raiz\>_) com os comandos:

```
git clone https://github.com/rubenbelem/product-search-bm25.git
cd product-search-bm25
```

#### Compilando o programa

No diretório raíz do projeto, execute o comando:

```
cmake -Bbuild -H. && make -C build
```

Com isso, um diretório chamado _bin/_ é criado no diretório raíz do projeto, e nele também é criado o programa "_processador_".

#### Execução do programa

Ainda no diretório raíz, navegue até o diretório _bin_:

```
cd bin
```

O programa "_processador_" recebe três argumentos:

- O primeiro é o caminho do arquivo "_catalogo_produtos.json_", que contém a lista de produtos a serem indexados pelo processador de consultas
- O segundo é o caminho do arquivo "stopwords.txt", que contém uma lista de palavras comuns de uma língua, a serem ignoradas na etapa indexação.
- O terceiro é a forma de ordenação do resultado das consultas. É possível escolher que sejam ordenados pelo ID do produto em ordem crescente, com o valor "id", ou pelo _score_ do _BM25_ em ordem decrescente (pois os resultados de maior qualidade ficam no topo), com o valor "score".

Há exemplares dos dois arquivos mencionados acima no diretório _\<dir_raiz\>/data_.

Então, o programa "_processador_" pode ser executado com os comandos:

```
./processador ../data/catalogo_produtos.json ../data/stopwords.txt id

ou

./processador ../data/catalogo_produtos.json ../data/stopwords.txt score
```

#### Comentários sobre o programa

As consultas realizadas são armazenadas em um histórico. É possível navegar por esse histórico utilizando as setas para cima e para baixo do teclado.

As consultas podem ser feitas com mais de um termo, e com caracteres especiais (como por exemplo "Relógio Azul") que estejam de acordo com a codificação _ISO 8859-1_.

O programa espera receber uma consulta na codificação _UTF-8_, a qual é codificada em _ISO 8859-1_. Os textos dos produtos também são codificados em _ISO 8859-1_ antes de terem seus termos indexados. Ou seja, é necessário executar o programa em um terminal com codificação _UTF-8_, como o _bash_ padrão do _Ubuntu_ ou _Linux Mint_. Os caracteres especiais como "á,ç,ê" etc. são convertidos em caracteres comuns, "a,c,e" etc. Essa transformação ocorre tanto durante a indexação, nos termos a serem indexados, quanto durante o processamento de consultas, nos termos da consulta que serão processados.

Além disso, o programa também suporta correção de termos da consulta para termos com tamanho de até 15 caracteres. A forma de implementação foi: caso um termo da consulta não esteja indexado, o "SpellingCorrector" calcula sugestões de correção e adiciona aquela que obteve um maior "ranking", e então o processador de consultas a adiciona na consulta, realizando um tipo de _expansão local_ [[1]](https://www.iro.umontreal.ca/~nie/IFT6255/carpineto-Survey-QE.pdf) da mesma. Assim, a consulta "relxgio pzul" traz os mesmos resultados da consulta "relógio azul", por exemplo.

O método de correção de termos é o Algoritmo de Peter Norvig [[2]](https://norvig.com/spell-correct.html), escrito originalmente em Python. Utilizei a versão implementada em C++, presente no repositório https://github.com/felipefarinon/spellingcorrector, citada por ele na página onde descreve o algoritmo.

#### Referências

[1]. <a name="ref1"> [C. Carpineto and G. Romano. "A survey of automatic query expansion in information retrieval". ACM Computing Surveys, 44(1):1-50, Jan. 2012](https://www.iro.umontreal.ca/~nie/IFT6255/carpineto-Survey-QE.pdf).
</a>

[2]. ["How to Write a Spelling Corrector", Peter Norvig, Fev. 2007](https://norvig.com/spell-correct.html)
