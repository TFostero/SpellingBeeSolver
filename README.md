### Spelling Bee Solver ###

#### Solver for the New York Times Spelling Bee using multithreaded prefix matching tree traversals. ####

This started as a simple program to solve the [NYT Spelling Bee](https://en.wikipedia.org/wiki/The_New_York_Times_Spelling_Bee). You're given 6 optional letters and 1 required letter and need to find as many words at least 4 letters long that have those letters in them.  

I thought it would be interesting and potentially faster to use a [prefix tree](https://en.wikipedia.org/wiki/Trie) to look for words rather than simply checking each word in a dictionary. While traversing the prefix tree is much faster, I found that creating the prefix tree takes a long time, so I added serializing/deserializing to save the prefix tree to a file the first time the program is run and then load the prefix tree from the file on subsequent runs. I then thought it may be faster to create multiple prefix trees and then traverse them in parallel so I added this using C++ async and futures. I also used used the C++ thread library to parallelize the creation and serialization of new prefix trees and deserialization of prefix trees from the existing binary files. 

I then found it might be better remove the serialization/deserialization and run the program as a daemon. The overhead of creating the trees is done once and then the process is always running in the background listening to connections on its socket. 

#### Issues ####
The program takes a big efficiency hit because creating multiple trees using subsets of words from a dictionary means that the prefix trees miss out on a lot of the overlap they'd have if it were just one large tree. I haven't benchmarked, but it's probably faster to parallelize by using sets to find matching words in sections of the dictionary because that will be almost linear speedup. But that's not as cool as prefix matching trees.


**To install:**
>mkdir build\
>cd build\
>cmake ..\
>make\
>cpack -G DEB\
>sudo dpkg -i spellingbeesolver_1.12.1_amd64.deb

**To use:**
>sbsolve [optional character] [required character]
