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

#### Program executin

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
