# linked_list
C Linked list for int, double, string.

The simplest operations are implemented:
| function | description|
| ---------|------------|
| create*  | creates an empty list|
| destroy  | destroys the list and frees allocated memory|
| push_back| appends the given element to the end of the list|
| erase    | errases the first occurrence of the given element in the list|
| count    | counts appearances of the given element in the list|
| print    | displays the contents of the list|

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
This data structure can be very usefull in implementation [Hash Table](https://en.wikipedia.org/wiki/Hash_table).
