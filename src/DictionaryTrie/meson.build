#Ji Hyun An A91108783
#Steffe Reyes A16083679


# TODO: Define dictionary_trie using function library()

inc = include_directories('.')

dictionary_trie = library('dictionary_trie', sources: ['DictionaryTrie.cpp', 'DictionaryTrie.hpp'])

dictionary_trie_dep = declare_dependency(include_directories: inc,
  link_with: dictionary_trie)

#From the PA2 write up 
#dictionary_trie = library('dictionary_trie', sources: ['DictionaryTrie.cpp', 'DictionaryTrie.hpp'])
#add more files after DictionaryTrie.cpp as needed 
