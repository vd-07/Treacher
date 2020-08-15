# Treacher
## Advantages
1. Searches for any word in raw file format where only words are present
2. Adds new words to any opened file
3. Suggests for word completion
## Analysis
- Time complexity : 
  - Search : O(word_length)
  - Insert : O(word_length)
  - Queries : O(no_of_queries * max_word_length)
  - Autocomplete : O(max_word_length)
- Space complexity : O(no_of_words * max_word_length)
## Features yet to be implemented
1. ~~Added support for searching in external file~~
2. Adding GUI
3. Serve autocomplete results based on top 5 hits in descending order
4. Take input continuously 
5. Take Uppercases as well (maybe possible by extending support for all the ASCII characters)
6. Connect this features as a backend
