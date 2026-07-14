# Redis Lite v1 Design Proposal

## Objective

Develop an in-memory key-value data store that runs entirely from the command line. The application will use the custom `HashMap` created previously as its storage engine and provide a simple REPL (Read-Evaluate-Print Loop) for interacting with the stored key-value pairs.

A **REPL (Read-Evaluate-Print Loop)** is a loop that repeatedly:

1. Reads a command from the user.
2. Evaluates (executes) the command.
3. Prints the result.
4. Loops back and waits for the next command until the user exits the application.

---

# Section 1 - Public API

```cpp
class RedisLite
{
public:
    RedisLite();

    void run();

private:
    HashMap<std::string, std::string> store;

    std::string executeCommand(const std::string& line);

    DA<std::string> tokenize(const std::string& line);

    std::string handleSet(const DA<std::string>& tokens);

    std::string handleGet(const DA<std::string>& tokens);

    std::string handleDel(const DA<std::string>& tokens);

    std::string handleExists(const DA<std::string>& tokens);

    std::string handleCount();

    std::string handleClear();
};
```

## Working Flow

The program starts by calling `run()`, which continuously waits for user input.

Suppose the user enters:

```text
SET name Himanshu
```

The complete line is read using `getline()` and stored as a single string.

This string is passed to

```cpp
executeCommand(const std::string& line)
```

Inside this function, the first step is to call

```cpp
tokenize(const std::string& line)
```

The `tokenize()` function splits the input line wherever it finds whitespace and stores each word as a separate string inside a `DynamicArray`.

For the above command, the array becomes

```text
tokens[0] = "SET"
tokens[1] = "name"
tokens[2] = "Himanshu"
```

The first token (`tokens[0]`) represents the command name. It is used to determine which handler function should execute.

Since the command is `"SET"`, `executeCommand()` calls

```cpp
handleSet(tokens);
```

Inside `handleSet()`, the remaining tokens are used as the key and value.

```text
tokens[1] → Key   = "name"
tokens[2] → Value = "Himanshu"
```

The data is then inserted into the `HashMap` using its `insert()` function.

```cpp
store.insert("name", "Himanshu");
```

After successfully storing the key-value pair, `handleSet()` returns

```text
OK
```

This string is returned back to `run()`, which prints it on the console.

```text
> SET name Himanshu
OK
```

The REPL then starts the next iteration and waits for another command from the user.

The same flow is followed for all other commands such as `GET`, `DEL`, `EXISTS`, `COUNT`, and `CLEAR`.

---

# Section 2 - Internal Representation

Redis Lite stores all data inside a `HashMap<std::string, std::string>`. The `RedisLite` class itself does not directly manage any memory. It simply receives commands from the user, processes them, and forwards the required operation to the `HashMap`.

![Redis Lite ](/docs/design/memory_diagram/redislite.jpeg)

## Memory Ownership

```text
RedisLite
    │
    ▼
HashMap<std::string, std::string>
    │
    ▼
DynamicArray (Bucket Array)
    │
    ▼
LinkedList (Collision Chains)
    │
    ▼
Node
    │
    ▼
Key-Value Pair
```

The `RedisLite` object owns the `HashMap`. The `HashMap` manages the bucket array, each bucket manages a `LinkedList`, and each linked list manages its own nodes.

## Rule of Three

The `RedisLite` class itself does not allocate dynamic memory. All dynamic memory is handled internally by the `HashMap`.

Therefore, `RedisLite` relies on the Rule of Three implementations already present in `HashMap`, `DynamicArray`, and `LinkedList`.

---

## Supported Commands

| Command | Description | Output |
|---------|-------------|--------|
| `SET key value` | Inserts a new key-value pair or updates an existing value. | `OK` |
| `GET key` | Returns the value associated with the key. | Value or `(nil)` |
| `DEL key` | Deletes a key from the store. | `1` if deleted, otherwise `0` |
| `EXISTS key` | Checks whether a key exists. | `1` if found, otherwise `0` |
| `COUNT` | Returns the total number of stored key-value pairs. | Number of keys |
| `CLEAR` | Removes every key-value pair from the store. | `OK` |
| `EXIT` | Terminates the application. | Program exits |

## Command Execution Flow

```text
User enters command
        │
        ▼
getline()
        │
        ▼
executeCommand()
        │
        ▼
tokenize()
        │
        ▼
Command identified (tokens[0])
        │
        ▼
Calls corresponding handler
        │
        ▼
HashMap operation
        │
        ▼
Returns response string
        │
        ▼
run() prints response
        │
        ▼
Wait for next command
```

Example:

```text
SET name Himanshu
        │
        ▼
["SET", "name", "Himanshu"]
        │
        ▼
handleSet()
        │
        ▼
store.insert("name", "Himanshu")
        │
        ▼
OK
```

---

# Section 4 - Complexity Analysis

| Operation | Best | Average | Worst | Explanation |
|-----------|------|----------|--------|-------------|
| **SET** | O(1) | O(1) | O(n) | Uses `HashMap::insert()`. Worst case occurs during collisions or rehashing. |
| **GET** | O(1) | O(1) | O(n) | Searches one bucket and traverses the collision chain if necessary. |
| **DEL** | O(1) | O(1) | O(n) | Removes a key from the appropriate bucket. |
| **EXISTS** | O(1) | O(1) | O(n) | Performs a HashMap lookup. |
| **COUNT** | O(1) | O(1) | O(1) | Returns the maintained size of the HashMap. |
| **CLEAR** | O(n) | O(n) | O(n) | Removes every stored key-value pair. |
| **Tokenize** | O(k) | O(k) | O(k) | Reads every character of the input line once, where *k* is the length of the input line. |

---
# Section 4 - Design Decisions

## 1. Using HashMap as the Storage Engine

Redis Lite is a key-value data store where every operation is performed using a key. Since the custom `HashMap` developed in Project 01 provides **O(1)** average time complexity for insertion, searching, and deletion, it is the most suitable data structure for this project.

Reusing the existing `HashMap` also demonstrates code reusability and avoids implementing another storage structure from scratch.

---

## 2. Using a REPL

Redis Lite uses a REPL (Read-Evaluate-Print Loop), allowing the user to continuously enter commands without restarting the application.

The REPL reads a command, executes it, prints the result, and waits for the next command until the user exits the application.

---

## 3. Separating Command Handlers

Each command (`SET`, `GET`, `DEL`, `EXISTS`, `COUNT`, and `CLEAR`) is implemented in a separate handler function instead of writing all command logic inside `executeCommand()`.

This keeps the code modular, easier to understand, and easier to maintain. It also allows new commands to be added without modifying the existing handlers.


---

## 4. Tokenizing User Input

The complete user input is first divided into individual words called tokens.

Example:

```text
SET name Himanshu

↓

["SET", "name", "Himanshu"]
```

The first token represents the command, while the remaining tokens represent its arguments.

This makes command parsing simple and allows every handler function to receive input in the same format.



---

## 5. Using String Keys and Values

Redis Lite stores data as:

```cpp
HashMap<std::string, std::string>
```

Using strings allows the program to store any text entered by the user without additional type conversion. It also follows the basic idea of Redis, where data is fundamentally stored as strings.

---

## 6. Returning Strings from Handler Functions

Each handler function returns a `std::string` containing either the result of the command or an error message.

The `run()` function is responsible only for printing the returned string.

This separates command execution from input/output, making the code cleaner and easier to modify in the future.

---

## 7. Reusing Existing Data Structures

Instead of implementing new linked lists or arrays inside Redis Lite, the project directly reuses the `DynamicArray`, `LinkedList`, and `HashMap` developed in Project 01.

This reduces duplicate code, improves reliability by using already tested components, and demonstrates how reusable data structures can be combined to build a complete application.

---
