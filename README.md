# Bank Account Management System

A menu-driven **C++ Data Structures Laboratory mini project** that demonstrates how linked lists, stacks, circular queues, arrays, searching, sorting, and recursion can be used in a practical account-management application.

> **Academic project:** This application is intended for learning and demonstration. It is not production banking software. Account data is stored in memory and is not saved after the program exits.

## Features

- Create and delete bank accounts
- Deposit, withdraw, transfer money, and check account balances
- View per-account transaction history
- Undo the latest eligible deposit or withdrawal
- Display all accounts
- Sort accounts by account number (bubble sort)
- Sort accounts by balance, highest first (selection sort)
- Search for an account using binary search
- Calculate compound interest using recursion
- Add deposit/withdrawal requests to a circular queue and process them in FIFO order
- Validate several common invalid inputs and account operations

## Data structures and algorithms

| Concept | Where it is used |
|---|---|
| Class / ADT | `Account` class |
| Singly linked list | Stores account nodes |
| Stack | Stores each account's transaction history |
| Circular queue | Stores pending deposit/withdrawal requests |
| Array | Temporary account collection for sorting and binary search |
| Linear search | Finds an account in the linked list |
| Bubble sort | Sorts account numbers in ascending order |
| Selection sort | Sorts balances in descending order |
| Binary search | Searches the sorted temporary account array |
| Recursion | Calculates compound interest |

## Project structure

```text
Bank-Account-Management-System/
├── src/
│   └── ds_miniproject.cpp
├── docs/
│   ├── PROJECT_DOCUMENTATION.md
│   ├── DATA_STRUCTURES.md
│   ├── VIVA_QUESTIONS.md
│   └── CONTRIBUTING.md
├── screenshots/
│   └── .gitkeep
├── README.md
├── .gitignore
└── LICENSE
```

## Requirements

- A C++ compiler with support for standard C++ (for example, `g++`)
- Windows PowerShell / Command Prompt, Linux terminal, or macOS terminal

No external C++ libraries are required by the source code.

## Compile and run

### Windows (PowerShell)

Open PowerShell in the repository folder:

```powershell
g++ .\src\ds_miniproject.cpp -o bank.exe
.\bank.exe
```

### Linux / macOS

```bash
g++ ./src/ds_miniproject.cpp -o bank
./bank
```

If `g++` is not recognized, install a C++ compiler and make sure its executable directory is added to your system `PATH`.

## Main menu

| Option | Operation |
|---:|---|
| 1 | Create account |
| 2 | Deposit |
| 3 | Withdraw |
| 4 | Transfer |
| 5 | Check balance |
| 6 | Transaction history |
| 7 | Undo last transaction |
| 8 | Display all accounts |
| 9 | Display sorted by account number |
| 10 | Display sorted by balance |
| 11 | Search account (binary search) |
| 12 | Interest calculator (recursion) |
| 13 | Add request to queue |
| 14 | Process next request |
| 15 | Delete account |
| 0 | Exit |

## Screenshots

Add genuine screenshots captured from your own program execution to the `screenshots/` folder. Suggested screenshots:

- `main-menu.png` — initial menu
- `account-creation.png` — successful account creation
- `transactions.png` — deposit / withdrawal / transaction history
- `sorting-searching.png` — sorted display or successful search
- `queue-processing.png` — adding and processing a pending request

Do not add mock or fabricated output screenshots.

## Important implementation notes

- Maximum number of accounts: **100** (`MAXACC`).
- Maximum number of queued requests: **50** (`QMAX`).
- Accounts and transaction history are held in memory only.
- The binary-search menu operation first copies and bubble-sorts the accounts, then performs binary search. Binary search itself is `O(log n)`, but the complete menu operation is `O(n²)` because of the bubble-sort step.
- The current undo function does not reverse transfers. It supports eligible deposits and withdrawals.
- A queued request is validated and applied when it is processed, not when it is first added.

## Documentation

- [Detailed project documentation](docs/PROJECT_DOCUMENTATION.md)
- [Data structures and algorithms](docs/DATA_STRUCTURES.md)
- [Viva questions and answers](docs/VIVA_QUESTIONS.md)
- [Contribution guidelines](docs/CONTRIBUTING.md)

## Limitations and possible future improvements

- Add file handling or database storage for persistence.
- Add authentication and role-based access.
- Add a graphical user interface.
- Add transaction timestamps and account statements.
- Implement safe transfer reversal that updates both accounts consistently.
- Add automated tests for valid and invalid operations.

## Academic use

This repository is prepared as a Data Structures Laboratory mini project. Update the documentation with your institution's required details and add screenshots from actual execution before submitting it.

## License

See [LICENSE](LICENSE). If this project is being submitted or published under an institution-specific rule, confirm that the selected license is appropriate before publishing.
