Solver for the New York Times Spelling Bee using asynchronous prefix matching trie traversals.

Creates a number of prefix matching tries from subsets of a dictionary. Traverses the tries in parallel using async and futures in order to find matching words.
If it's the first time the program is run, after the trees are generated they will be serialized and saved to files. Upon subsequent runs, the trees will be loaded and
deserialized in parallel prior to traversal.
