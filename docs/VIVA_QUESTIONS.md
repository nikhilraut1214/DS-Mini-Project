# Bank Account Management System --- Viva Questions and Answers

## Project basics

**1. What is the title of your project?**\
Bank Account Management System.

**2. Which programming language is used?**\
C++.

**3. What is the main purpose of this project?**\
To perform basic bank account operations and demonstrate data structures
and algorithms in C++.

**4. Which data structures are used?**\
A singly linked list, stack, circular queue, and array.

**5. Why is this project related to Data Structures?**\
Different data structures are used to store accounts, maintain
transaction history, manage pending requests, and perform searching and
sorting.

## Linked list and ADT

**6. What is an ADT?**\
An Abstract Data Type defines data and the operations that can be
performed on it, without requiring the user to know all implementation
details.

**7. Which class represents a bank account?**\
The `Account` class.

**8. What information does the Account class store?**\
Account number, account holder name, and balance.

**9. Which linked list is used?**\
A singly linked list.

**10. What does a node contain in this project?**\
An `Account` object, a pointer to the transaction-history stack, and a
pointer to the next account node.

**11. What is the purpose of `head`?**\
It points to the first node of the linked list.

**12. How is an account inserted?**\
`createAccount()` creates a new node and inserts it at the end of the
linked list.

**13. What is the time complexity of searching an account in the linked
list?**\
O(n), because nodes may need to be checked one by one.

## Stack

**14. What is a stack?**\
A linear data structure that follows LIFO: Last In, First Out.

**15. Where is the stack used?**\
Each account has a linked stack of transactions.

**16. What does `pushTxn()` do?**\
It inserts a new transaction at the top of the account's history stack.

**17. What does `popTxn()` do?**\
It removes the top transaction from the stack and returns its type and
amount through reference parameters.

**18. Why is the latest transaction displayed first?**\
Because new transactions are inserted at the top of the stack.

**19. Can every transaction be undone in this project?**\
No. The current implementation does not allow transfer transactions to
be undone. It supports undo for eligible deposits and withdrawals.

**20. What is the time complexity of push and pop?**\
O(1).

## Queue

**21. What is a queue?**\
A linear data structure that follows FIFO: First In, First Out.

**22. Where is the queue used?**\
To store pending deposit and withdrawal requests.

**23. Which type of queue is implemented?**\
A circular queue using an array.

**24. Why use a circular queue?**\
It reuses array positions by wrapping the rear and front indices around
using modulo arithmetic.

**25. What is the maximum queue capacity?**\
50 requests, defined by `QMAX`.

**26. Which variables manage the queue?**\
`qFront`, `qRear`, and `qCount`.

**27. What is the time complexity of insertion and deletion?**\
O(1) for each queue operation.

## Searching and sorting

**28. What is linear search?**\
A search technique that checks elements one by one until the required
element is found or the collection ends.

**29. Where is linear search used?**\
In `findAccount()`, which searches the linked list by account number.

**30. What is binary search?**\
A searching algorithm that repeatedly divides a sorted collection into
halves.

**31. Why must data be sorted before binary search?**\
Binary search decides which half can contain the key based on the
ordering of elements. This decision is not reliable for unsorted data.

**32. How does this project prepare data for binary search?**\
It copies accounts into an array and sorts that array by account number
using bubble sort.

**33. What is the time complexity of binary search itself?**\
O(log n).

**34. Which sorting algorithms are used?**\
Bubble sort and selection sort.

**35. Where is bubble sort used?**\
To sort accounts in ascending order of account number.

**36. Where is selection sort used?**\
To sort accounts by balance in descending order.

**37. What is the time complexity of these sorting algorithms in this
implementation?**\
O(n²) for both bubble sort and selection sort.

## Recursion and C++

**38. Where is recursion used?**\
In the compound interest calculation function `compound()`.

**39. What is recursion?**\
A technique in which a function calls itself to solve a smaller version
of a problem.

**40. What is the base case in `compound()`?**\
When `years == 0`, the function returns the current amount.

**41. Why is a base case necessary?**\
It stops recursive calls and prevents infinite recursion.

**42. What is a pointer?**\
A variable that stores the memory address of another variable or object.

**43. Why is `new` used?**\
To allocate memory dynamically for account and transaction nodes.

**44. Why is `delete` used?**\
To release dynamically allocated memory when nodes are removed or the
program exits.

**45. What does `NULL` indicate here?**\
A null pointer, meaning the pointer does not point to a valid node.

**46. What is the purpose of `getline()`?**\
It reads a complete line of text, allowing account holder names to
contain spaces.

**47. Why are `cin.clear()` and `cin.ignore()` used?**\
They help recover from invalid formatted input by clearing the error
state and discarding unwanted input characters.

**48. What is the purpose of `iomanip`?**\
It provides output formatting tools such as `setw`, `left`, and
`setprecision`.

## Project limitations and reasoning

**49. Is account information stored permanently?**\
No. The current program stores account information in memory, so it is
lost when the program exits.

**50. What is the maximum number of accounts?**\
100, defined by `MAXACC`.

**51. Why is the account count limited to 100?**\
The sorting and binary-search features use a temporary array with
capacity 100.

**52. What happens when an account is deleted?**\
The account node is removed from the linked list, its
transaction-history nodes are freed, and the account count is decreased.

**53. What happens when the program exits normally?**\
`freeAll()` releases the remaining account nodes and their transaction
histories.

**54. What is the difference between a stack and a queue?**\
A stack follows LIFO, while a queue follows FIFO.

**55. What improvements can be made in the future?**\
File or database storage, authentication, a graphical interface,
transaction timestamps, automated testing, and safe transfer reversal.

**56. Is this suitable for real banking use?**\
No. It is an educational project. It lacks persistent storage,
authentication, security controls, and production-grade transaction
handling.
