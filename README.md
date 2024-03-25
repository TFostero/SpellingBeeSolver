### Spelling Bee Solver ###

#### Solver for the New York Times Spelling Bee using multithreaded prefix matching tree traversals. ####

This started as a simple program to solve the [NYT Spelling Bee](https://en.wikipedia.org/wiki/The_New_York_Times_Spelling_Bee). You're given 6 optional letters and 1 required letter and need to find as many words at least 4 letters long that have those letters in them.  

I thought it would be interesting and potentially faster to use a [prefix tree](https://en.wikipedia.org/wiki/Trie) to look for words rather than simply checking each word in a dictionary. While traversing the prefix tree is much faster, I found that creating the prefix tree is very computationally expensive, so I added serializing/deserializing to save the prefix tree to a file the first time the program is run and then load the prefix tree from the file on subsequent runs. I then thought it may be faster to create multiple prefix trees and then traverse them in parallel using multithreading so I added this using C++ async and futures. I also used multithreading using the C++ thread library to parallelize the creation and serialization of new prefix trees and deserialization of prefix trees from the existing binary files. 

#### Issues ####
It's actually still much faster to just load and traverse a dictionary file line by line to find matching words because the overhead involved in creating/loading the prefix trees takes so much time, even with serialization/deserialization of the trees. Once the prefix trees exist though, traversing them is much faster than parsing a whole dictionary. The program also takes a bit of an efficiency hit because creating multiple trees using subsets of words from a dictionary means that the prefix trees miss out on a lot of the overlap they'd have if it were just one large tree. 


To run:
>make
>
>./sbsolve.exe
