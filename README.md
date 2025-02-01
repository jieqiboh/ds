### Basic DS implementations for my toy OS :P
#### Linked List
This is a general linked list implementation. Nodes can store data of any type using void pointers.
`malloc` should be changed to `kalloc` when using it in OS dev.

#### Hashmap
This is a general hashmap implementation. It comprises an array of linked lists. The linked list nodes contain key-value pairs.

To do:
- account for cases where malloc and free fails
