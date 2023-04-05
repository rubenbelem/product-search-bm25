## Product Search with BM25 ranking

### Rúben Jozafá Silva Belém

The following instructions were tested at the systems _Ubuntu 18.04 Bionic Beaver_ and _Linux Mint 19.2 "Tina" Cinnamon_. 
#### Installing the dependencies

First of all, you must have `git` installed. You can install it with:

```
sudo apt install git
```

To compile the program you must install `cmake`, `make`, `g++` and `libreadline-dev` with the command:

```
sudo apt install cmake make g++ libreadline-dev
```

#### Cloning the project's repository

Clone this repository with `git` and the go to the repository directory (the root directory of the project _<root_dir>_) with the commands:

```
git clone https://github.com/rubenbelem/product-search-bm25.git
cd product-search-bm25
```

#### Compiling the program

In the root directory of the project, run this command:

```
cmake -Bbuild -H. && make -C build
```

After that, a directory _bin/_ is created inside the root directory with the executable `processor` inside it.

#### Program execution

While still in the root directory, go to _bin_:

```
cd bin
```

The program `processor` receives three arguments:

- The first is the path of the file "_product_catalog.json_", which contains the list of products to be indexed for the query processor.
- The second is the path of the file "stopwords.txt", which contains a list of the most frequent words in a language (Portuguese for this project). Those words will be ignored in the indexing stage.
- The third is the attribute to use when sorting the output. It is possible to sort by product IDs in ascending order, by passing the value `"id"`, or by BM25 score in ascending order (results with the best ranking stay on the top) by passing the value `"score"`.

There are two samples of the product catalog and stopwords files at the `<root_dir>/data`.

Then, the program `processor` can be started with one of the following commands:

```
./processor ../data/product_catalog.json ../data/stopwords.txt id

ou

./processor ../data/product_catalog.json ../data/stopwords.txt score
```

#### Execution with docker-compose

You must have `docker` and `docker-compose` installed for this execution approach.

First, build the query processor with:

```bash
make build-docker
```

The approach for running the query processor inside a docker container uses the environment variables defined in `.docker.env` file. You must set the `HOST_DATA_PATH` variable with the path to the directory that have the product catalog and stopwords file, and set their names at `PRODUCT_CATALOG_PATH` and `STOPWORDS_PATH` file.

Then, just run the command:
```bash
make run-in-docker
```

#### Comments on the program

The submited queries are stored in a queries history. One can navigate through the history using the keyboard <Up> and <Down> keys.

The queries can have multiple terms and  _ISO 8859-1_ encoding characters (like "ó","á","ã"). 

The program hopes to receive a query with _UTF-8_ encoding, which is then encoded with _ISO 8859-1_. The text of the products are also encoded with _ISO 8859-1_ before the indexing stage. That said, one must run the program in a terminal with _UTF-8_ encoding, like _Ubuntu_ standard _bash_ for example. The special characters like "á,ç,ê" are transformed to common characters ("a,c,e"). This transformation is performed in the indexing stage, at the indexed product terms, as well as in the query processing, at the query terms.

Besides that, the program also supports query spelling correction for terms with at most 15 characters. If a query term is not indexed, then the "SpellingCorrector" calculates suggestions of correction and adds the one with the highest "ranking". Then, the query processor add this corrected term in the original query, performing a local query expansion[^queryexpansion]. That said, the query "blue watcx" brings the same results as "blue watch", for example.

The spelling correction method is the Peter Norvig Algorithm[^norvig2007], written originally in Python. It is a brute force approach to spelling correction. I used a version written in C++ from the repository https://github.com/felipefarinon/spellingcorrector, which Peter Norvig quoted in the page where he describes the algorithm.

#### References

[^queryexpansion]: <a name="ref1"> [C. Carpineto and G. Romano. "A survey of automatic query expansion in information retrieval". ACM Computing Surveys, 44(1):1-50, Jan. 2012](https://www.iro.umontreal.ca/~nie/IFT6255/carpineto-Survey-QE.pdf).

[^norvig2007]: ["How to Write a Spelling Corrector", Peter Norvig, Fev. 2007](https://norvig.com/spell-correct.html)
