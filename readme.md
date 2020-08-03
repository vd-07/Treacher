# Treacher
# Advantages
- Time complexity : 
  - Search : O(word_length)
  - Insert : O(word_length)
  - Queries : O(no_of_queries * max_word_length)
  - Autocomplete : O(max_word_length)
- Space complexity : O(no_of_words * max_word_length)
## Features yet to be implemented
1. Serve autocomplete results based on top 5 hits in descending order
2. Take input continuously 
3. Take Uppercases as well (maybe possible by extending support for all the ASCII characters)
4. Connect this features as a backend
