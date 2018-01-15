# CS50
## SPELLER

This program takes a dictionary ('speller/dictionaries/large' if not specified), loads the dictionary in the memory using a Trie data structure (hash table would work too, but I chose Trie for better performance at the cost of extra memory). It then checks each word of a text file specified in 'speller/texts/' and verifies if that word is present in the dictionary. The output is mispelled words and some additional information (example in 'speller/output.txt'). The program doesn't leak any memory (valgrind check successful).

**The code I have written myself are in 'speller/dictionary.c' and 'speller/dictionary.h'; 'speller/speller.c' was written by CS50 staff.**

Usage: ./speller [ dictionary ] text

Example: ./speller texts/alice.txt

Problem Set link: http://docs.cs50.net/problems/speller/speller.html

Speller was definetly the most fun and challenging problem set of CS50. The 4 functionalities implemented by me are **load**, **check**, **size** and **unload** located in speller/dictionary.c. Those functions make use of pointers, data structures and recursion.
