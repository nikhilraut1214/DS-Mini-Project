# Data Structures and Algorithms Used

This document explains the data structures and algorithms present in `src/ds_miniproject.cpp`.

## 1. Account class (ADT)

The `Account` class groups three fields: `accNo`, `name`, and `balance`. Constructors initialize these values, and `display()` prints the account details.

## 2. Singly linked list — account storage

`Node` contains:
- `Account data`
- `Txn* history`
- `Node* next`

The global pointer `head` identifies the first account. Accounts are inserted at the end, searched by traversal, displayed by traversal, and deleted by adjusting links.

| Operation | Function | Complexity |
|---|---|---:|
| Search | `findAccount()` | O(n) |
| Insert at end | `createAccount()` | O(n) |
| Display | `displayAll()` | O(n) |
| Delete by account number | `deleteAccount()` | O(n), plus history cleanup |

## 3. Stack — transaction history

Each account owns a linked stack of `Txn` nodes. The newest transaction is stored at the top.

- Push: `pushTxn()`
- Pop: `popTxn()`
- Display: `showHistory()`
- Undo eligible latest transaction: `undoLast()`

The stack follows **LIFO**. Push and pop take O(1); displaying `h` transactions takes O(h).

The source records transfers in both accounts, but `undoLast()` explicitly refuses to undo transfer entries.

## 4. Circular queue — pending requests

The array `q[QMAX]` stores pending `Request` values. `qFront`, `qRear`, and `qCount` track the queue.

- Enqueue: `addRequest()`
- Dequeue and execute: `processRequest()`

The queue follows **FIFO**. Circular indexing uses modulo arithmetic, so freed array positions can be reused. Queue insertion and removal are O(1).

## 5. Array — temporary account records

`copyToArray()` copies the linked-list account records into a temporary array of capacity `MAXACC`. The array is used by sorting and binary search. It is not the primary account storage.

## 6. Searching

### Linear search

`findAccount()` checks linked-list nodes sequentially. Worst-case time: O(n).

### Binary search

`binarySearch()` searches an array sorted by account number. Search time alone: O(log n). The menu function sorts the array with bubble sort before searching, so the complete operation is O(n²).

## 7. Sorting

### Bubble sort

`bubbleSortByAccNo()` compares adjacent account numbers and swaps records to produce ascending order. Time: O(n²).

### Selection sort

`selectionSortByBalance()` selects the highest remaining balance and moves it to the next output position. The result is descending balance order. Time: O(n²).

## 8. Recursion

`compound()` recursively applies the annual interest factor until `years` reaches zero. Time and recursive call-stack space are O(years).

## 9. Summary

| Concept | Project use | Main principle |
|---|---|---|
| Class / ADT | Account details | Encapsulation of related data and behaviour |
| Singly linked list | Account records | Node traversal and links |
| Stack | Transaction history | LIFO |
| Circular queue | Pending requests | FIFO |
| Array | Temporary account copy | Indexed storage |
| Linear search | Linked-list lookup | Sequential comparison |
| Binary search | Sorted array lookup | Divide search interval in half |
| Bubble sort | Account-number ordering | Adjacent swaps |
| Selection sort | Balance ordering | Repeated maximum selection |
| Recursion | Compound interest | Function calls itself with reduced years |
