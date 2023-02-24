# linked_list
C Linked list for int, double, string.

The simplest operations are implemented:
| function | description|
| ---------|------------|
| create*  | create an empty list|
| size     | return current size of the list|
| count    | count appearances of the given element in the list|
| contains | check if the list contains a certain element|
| push_back| append the given element to the end of the list|
| erase    | errase the first occurrence of the given element in the list|
| print    | displays the contents of the list|
| destroy  | destroy the list and frees allocated memory|

*create accepts an argument — type of elemenst. It can be `Int`, `Double` or `String`.

# Quick Start

Change this define in *main.c* to test different types of list values.
```C
#define TYPEOFLIST  (STRING)
```

```console
$ make
$ ./a.out
```

# Usage
This data structure can be very usefull in [Hash Table](https://github.com/Tnirpps/hash_table) implementation.
