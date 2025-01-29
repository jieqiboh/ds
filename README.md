### Basic DS implementations for my toy OS :P
#### Linked List
This is a general linked list implementation. Nodes can store data of any type using void pointers.
It contains basic functions to:
- init a new linked list
- insert data at the head
- delete a node
- delete an entire linked list
`malloc` should be changed to `kalloc` when using it in OS dev.

#### Hashmap
This is a general hashmap implementation. It comprises an array of linked lists. The linked list nodes contain key-value pairs.
It contains basic functions to:
- init a new hashmap of a certain size
- set a key-value pair
- get the value of a key
linked list + hashmap
basic tests + memory leak free

To do:
- llist_delete: Add feature to delete a node based on its data
- hashmap_set: 
- account for cases where malloc and free fails
