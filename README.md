## Teste Técnico - Linx

### Rúben Jozafá Silva Belém

#### Instalação de dependências

Primeiramente, é necessário possuir o _Git_ instalado. É possível instalá-lo com o comando:

```
sudo apt install git
```

Para compilar o programa, são necessários a instalação do _CMake_, _Make_ e _g++_, com o comando:

```
sudo apt install cmake make g++
```

#### Clonando o repositório

É preciso clonar este repositório com o Git, e então navegar até o diretório clonado (o diretório raíz do projeto, _<dir_raiz\>_) com os comandos:

```
git clone https://github.com/rubenbelem/technical-test-linx.git
cd technical-test-linx
```

#### Compilando o programa

No diretório raíz do projeto, crie um novo diretório _build/_ e navege até ele:

```
mkdir build
cd build
```

No diretório _build/_, crie o projeto _CMake_ com o comando:

```
cmake ..
```

E então compile o projeto com o _Make_:

```
make
```

Com isso, um diretório chamado _bin/_ é criado no diretório raíz do projeto, e nele também é criado o programa "_processor_".

#### Execução do programa

Ainda no diretório _build/_, navegue até o diretório _bin_:

```
cd ../bin
```

O programa "_processor_" recebe dois argumentos. O primeiro é o caminho do arquivo "_catalogo_produtos.json_", que contém a lista de produtos a serem indexados pelo processador de consultas. O segundo é o caminho do arquivo "stopwords.txt", que contém uma lista de palavras comuns de uma língua, a serem ignoradas na etapa indexação.

Há exemplares dessses dois arquivos no diretório _\<dir_raiz\>/data_.

Então, o programa "_processor_" pode ser executado com o comando:

```
./processor ../data/catalogo_produtos.json ../data/stopwords.txt
```
