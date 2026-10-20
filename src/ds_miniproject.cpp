// Bank Account Management System (DS Lab Mini Project) - FIXED VERSION
// Uses: ADT (class), singly linked list, stack, queue, arrays,
//       linear search, binary search, bubble sort, selection sort, recursion

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

const int MAXACC = 100;   // maximum number of accounts
int totalAccounts = 0;    // current number of accounts

// ---------------- Safe input functions ----------------

int readInt() {
    int x;
    while (!(cin >> x)) {
        if (cin.eof()) exit(0);
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Enter a number: ";
    }
    return x;
}

double readDouble() {
    double x;
    while (!(cin >> x)) {
        if (cin.eof()) exit(0);
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Enter a number: ";
    }
    return x;
}

// ---------------- ADT: Account ----------------
class Account {
public:
    int accNo;
    string name;
    double balance;

    Account() { accNo = 0; name = ""; balance = 0; }
    Account(int a, string n, double b) { accNo = a; name = n; balance = b; }

    void display() const {
        cout << left << setw(10) << accNo << setw(20) << name << balance << endl;
    }
};

// ---------------- Stack node: transaction history ----------------
struct Txn {
    string type;      // Deposit, Withdraw, Transfer In, Transfer Out
    double amount;
    Txn* next;
};

// ---------------- Linked list node: one account ----------------
struct Node {
    Account data;
    Txn* history;     // top of stack
    Node* next;
};

Node* head = NULL;

// ---------------- Queue (circular array): pending requests ----------------
const int QMAX = 50;
struct Request { int accNo; char type; double amount; };
Request q[QMAX];
int qFront = 0, qRear = -1, qCount = 0;

// ---------------- Stack operations ----------------
void pushTxn(Node* n, string type, double amt) {
    Txn* t = new Txn;
    t->type = type;
    t->amount = amt;
    t->next = n->history;
    n->history = t;
}

bool popTxn(Node* n, string &type, double &amt) {
    if (n->history == NULL) return false;
    Txn* t = n->history;
    type = t->type;
    amt = t->amount;
    n->history = t->next;
    delete t;
    return true;
}

void freeHistory(Node* n) {
    while (n->history != NULL) {
        Txn* t = n->history;
        n->history = t->next;
        delete t;
    }
}

// ---------------- Linear search in linked list ----------------
Node* findAccount(int no) {
    Node* p = head;
    while (p != NULL) {
        if (p->data.accNo == no) return p;
        p = p->next;
    }
    return NULL;
}

// ---------------- Linked list: insert at end ----------------
void createAccount() {
    string name;
    double bal;

    // FIX: array-based features (sort/search) only hold 100 accounts
    if (totalAccounts >= MAXACC) {
        cout << "Account limit reached (" << MAXACC << ").\n";
        return;
    }

    cout << "Enter account number: ";
    int no = readInt();
    if (no <= 0) {
        cout << "Account number must be positive.\n";
        return;
    }
    if (findAccount(no) != NULL) {
        cout << "Account number already exists.\n";
        return;
    }

    // FIX: names with spaces now work
    cout << "Enter holder name: ";
    cin.ignore(10000, '\n');
    getline(cin, name);
    if (name == "") {
        cout << "Name cannot be empty.\n";
        return;
    }

    cout << "Enter opening balance: ";
    bal = readDouble();
    if (bal < 0) {
        cout << "Balance cannot be negative.\n";
        return;
    }

    Node* n = new Node;
    n->data = Account(no, name, bal);
    n->history = NULL;
    n->next = NULL;

    if (head == NULL) head = n;
    else {
        Node* p = head;
        while (p->next != NULL) p = p->next;
        p->next = n;
    }
    totalAccounts++;
    cout << "Account created.\n";
}

// ---------------- Core operations ----------------
bool doDeposit(Node* n, double amt) {
    if (amt <= 0) return false;
    n->data.balance += amt;
    pushTxn(n, "Deposit", amt);
    return true;
}

bool doWithdraw(Node* n, double amt) {
    if (amt <= 0 || amt > n->data.balance) return false;
    n->data.balance -= amt;
    pushTxn(n, "Withdraw", amt);
    return true;
}

void depositMoney() {
    cout << "Account number: ";
    int no = readInt();
    Node* n = findAccount(no);
    if (n == NULL) { cout << "Account not found.\n"; return; }
    cout << "Amount to deposit: ";
    double amt = readDouble();
    if (doDeposit(n, amt)) cout << "Deposited. New balance: " << n->data.balance << endl;
    else cout << "Invalid amount.\n";
}

void withdrawMoney() {
    cout << "Account number: ";
    int no = readInt();
    Node* n = findAccount(no);
    if (n == NULL) { cout << "Account not found.\n"; return; }
    cout << "Amount to withdraw: ";
    double amt = readDouble();
    if (doWithdraw(n, amt)) cout << "Withdrawn. New balance: " << n->data.balance << endl;
    else cout << "Invalid amount or insufficient balance.\n";
}

void transferMoney() {
    cout << "From account: ";
    int from = readInt();
    cout << "To account: ";
    int to = readInt();
    Node* a = findAccount(from);
    Node* b = findAccount(to);
    if (a == NULL || b == NULL || from == to) { cout << "Invalid account(s).\n"; return; }
    cout << "Amount: ";
    double amt = readDouble();
    if (amt <= 0 || amt > a->data.balance) { cout << "Invalid amount or insufficient balance.\n"; return; }
    a->data.balance -= amt;
    b->data.balance += amt;
    pushTxn(a, "Transfer Out", amt);
    pushTxn(b, "Transfer In", amt);
    cout << "Transfer done.\n";
}

void checkBalance() {
    cout << "Account number: ";
    int no = readInt();
    Node* n = findAccount(no);
    if (n == NULL) { cout << "Account not found.\n"; return; }
    cout << "Balance: " << n->data.balance << endl;
}

// ---------------- Stack: show history and undo last ----------------
void showHistory() {
    cout << "Account number: ";
    int no = readInt();
    Node* n = findAccount(no);
    if (n == NULL) { cout << "Account not found.\n"; return; }
    if (n->history == NULL) { cout << "No transactions.\n"; return; }
    cout << "Transactions (latest first):\n";
    Txn* t = n->history;
    while (t != NULL) {
        cout << "  " << left << setw(14) << t->type << t->amount << endl;
        t = t->next;
    }
}

void undoLast() {
    cout << "Account number: ";
    int no = readInt();
    Node* n = findAccount(no);
    if (n == NULL) { cout << "Account not found.\n"; return; }
    if (n->history == NULL) { cout << "Nothing to undo.\n"; return; }

    string type = n->history->type;
    double amt = n->history->amount;

    if (type == "Transfer In" || type == "Transfer Out") {
        cout << "Transfers cannot be undone.\n";
        return;
    }
    if (type == "Deposit" && n->data.balance < amt) {
        cout << "Cannot undo: balance too low.\n";
        return;
    }
    popTxn(n, type, amt);
    if (type == "Deposit") n->data.balance -= amt;
    else n->data.balance += amt;
    cout << "Undid last " << type << " of " << amt << ". Balance: " << n->data.balance << endl;
}

// ---------------- Delete node from linked list ----------------
void deleteAccount() {
    cout << "Account number to delete: ";
    int no = readInt();
    Node *p = head, *prev = NULL;
    while (p != NULL && p->data.accNo != no) {
        prev = p;
        p = p->next;
    }
    if (p == NULL) { cout << "Account not found.\n"; return; }

    if (prev == NULL) head = p->next;
    else prev->next = p->next;

    freeHistory(p);
    delete p;
    totalAccounts--;
    cout << "Account deleted.\n";
}

// FIX: free all memory before the program exits
void freeAll() {
    while (head != NULL) {
        Node* p = head;
        head = head->next;
        freeHistory(p);
        delete p;
    }
}

// ---------------- Display all (list traversal) ----------------
void displayAll() {
    if (head == NULL) { cout << "No accounts.\n"; return; }
    cout << left << setw(10) << "AccNo" << setw(20) << "Name" << "Balance\n";
    cout << "------------------------------------------\n";
    for (Node* p = head; p != NULL; p = p->next) p->data.display();
}

// ---------------- Arrays: copy list to array for sorting/searching ----------------
int copyToArray(Account arr[]) {
    int n = 0;
    for (Node* p = head; p != NULL; p = p->next) arr[n++] = p->data;
    return n;
}

// Bubble sort by account number
void bubbleSortByAccNo(Account arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j].accNo > arr[j + 1].accNo) {
                Account t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
            }
}

// Selection sort by balance (highest first)
void selectionSortByBalance(Account arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j].balance > arr[maxIndex].balance) maxIndex = j;
        Account t = arr[i]; arr[i] = arr[maxIndex]; arr[maxIndex] = t;
    }
}

void sortedDisplay(int choice) {
    Account arr[MAXACC];
    int n = copyToArray(arr);
    if (n == 0) { cout << "No accounts.\n"; return; }
    if (choice == 1) bubbleSortByAccNo(arr, n);
    else selectionSortByBalance(arr, n);
    cout << left << setw(10) << "AccNo" << setw(20) << "Name" << "Balance\n";
    cout << "------------------------------------------\n";
    for (int i = 0; i < n; i++) arr[i].display();
}

// Binary search (array must be sorted by accNo)
int binarySearch(Account arr[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid].accNo == key) return mid;
        else if (arr[mid].accNo < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

void binarySearchAccount() {
    Account arr[MAXACC];
    int n = copyToArray(arr);
    if (n == 0) { cout << "No accounts.\n"; return; }
    bubbleSortByAccNo(arr, n);
    cout << "Account number to search: ";
    int key = readInt();
    int pos = binarySearch(arr, n, key);
    if (pos == -1) cout << "Not found.\n";
    else { cout << "Found:\n"; arr[pos].display(); }
}

// ---------------- Recursion: compound interest ----------------
double compound(double amount, double rate, int years) {
    if (years == 0) return amount;
    return compound(amount * (1 + rate / 100), rate, years - 1);
}

void interestCalc() {
    cout << "Account number: ";
    int no = readInt();
    Node* n = findAccount(no);
    if (n == NULL) { cout << "Account not found.\n"; return; }
    cout << "Interest rate (% per year): ";
    double rate = readDouble();
    cout << "Years (0 to 100): ";
    int years = readInt();
    // FIX: very large years would crash the recursion
    if (rate < 0 || years < 0 || years > 100) { cout << "Invalid input.\n"; return; }
    cout << "Balance after " << years << " years: " << compound(n->data.balance, rate, years) << endl;
}

// ---------------- Queue: pending requests (FIFO) ----------------
void addRequest() {
    if (qCount == QMAX) { cout << "Queue full.\n"; return; }
    Request r;
    cout << "Account number: ";
    r.accNo = readInt();
    cout << "Type (D = deposit, W = withdraw): ";
    cin >> r.type;
    if (r.type != 'D' && r.type != 'd' && r.type != 'W' && r.type != 'w') {
        cout << "Invalid type.\n";
        return;
    }
    cout << "Amount: ";
    r.amount = readDouble();
    qRear = (qRear + 1) % QMAX;
    q[qRear] = r;
    qCount++;
    cout << "Request added. Pending: " << qCount << endl;
}

void processRequest() {
    if (qCount == 0) { cout << "No pending requests.\n"; return; }
    Request r = q[qFront];
    qFront = (qFront + 1) % QMAX;
    qCount--;

    Node* n = findAccount(r.accNo);
    if (n == NULL) { cout << "Request failed: account not found.\n"; return; }

    bool ok;
    if (r.type == 'D' || r.type == 'd') ok = doDeposit(n, r.amount);
    else ok = doWithdraw(n, r.amount);

    if (ok) cout << "Request processed. New balance: " << n->data.balance << endl;
    else cout << "Request failed: invalid amount or insufficient balance.\n";
}

// ---------------- Main menu ----------------
int main() {
    cout << fixed << setprecision(2);   // FIX: all money values now show 2 decimals

    int ch;
    do {
        cout << "\n===== BANK ACCOUNT MANAGEMENT SYSTEM =====\n";
        cout << " 1. Create account\n";
        cout << " 2. Deposit\n";
        cout << " 3. Withdraw\n";
        cout << " 4. Transfer\n";
        cout << " 5. Check balance\n";
        cout << " 6. Transaction history (stack)\n";
        cout << " 7. Undo last transaction (stack)\n";
        cout << " 8. Display all accounts\n";
        cout << " 9. Display sorted by account no (bubble sort)\n";
        cout << "10. Display sorted by balance (selection sort)\n";
        cout << "11. Search account (binary search)\n";
        cout << "12. Interest calculator (recursion)\n";
        cout << "13. Add request to queue\n";
        cout << "14. Process next request (queue)\n";
        cout << "15. Delete account\n";
        cout << " 0. Exit\n";
        cout << "Enter choice: ";
        ch = readInt();

        switch (ch) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: transferMoney(); break;
            case 5: checkBalance(); break;
            case 6: showHistory(); break;
            case 7: undoLast(); break;
            case 8: displayAll(); break;
            case 9: sortedDisplay(1); break;
            case 10: sortedDisplay(2); break;
            case 11: binarySearchAccount(); break;
            case 12: interestCalc(); break;
            case 13: addRequest(); break;
            case 14: processRequest(); break;
            case 15: deleteAccount(); break;
            case 0: cout << "Goodbye.\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (ch != 0);

    freeAll();
    return 0;
}
