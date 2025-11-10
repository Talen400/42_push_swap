# push_swap

**push_swap** is a project that aims to sort a stack using another auxiliary stack with the minimum number of operations.

---

## Available Operations

The program uses the following operations to manipulate the stacks:

| Operation | Description |
|-----------|-------------|
| `sa` | Swap the first two elements at the top of stack A |
| `sb` | Swap the first two elements at the top of stack B |
| `ss` | Perform `sa` and `sb` simultaneously |
| `pa` | Push the top element from stack B to stack A |
| `pb` | Push the top element from stack A to stack B |
| `ra` | Rotate stack A upwards (first → last) |
| `rb` | Rotate stack B upwards |
| `rr` | Perform `ra` and `rb` simultaneously |
| `rra` | Rotate stack A downwards (last → first) |
| `rrb` | Rotate stack B downwards |
| `rrr` | Perform `rra` and `rrb` simultaneously |

---

## 🧠 Algorithm Explanation

The algorithm uses a **hybrid approach** combining three strategies depending on the input size:

### 1️⃣ **Small Arrays (≤ 5 elements)** — Hardcoded Sorting

For very small inputs, the algorithm uses **optimized hardcoded solutions**:

- **2-3 elements:** Direct comparison and swap
- **4-5 elements:** 
  1. Find the minimum element
  2. Rotate it to the top
  3. Push to stack B
  4. Sort remaining elements
  5. Push back from B

**Time Complexity:** O(1)  
**Operations:** ≤ 12 moves

---

### 2️⃣ **Large Arrays (> 5 elements)** — LIS + Turk Algorithm

For larger inputs, a sophisticated two-phase approach is used:

#### **Phase 1: LIS (Longest Increasing Subsequence) with Dynamic Programming**

The algorithm identifies the **longest sequence of elements already in order** to keep in stack A:
```
Example:
Input: [6, 5, 2, 3, 4, 1, 1012]

LIS found: [2, 3, 4, 1012] (length 4)
         positions: 2, 3, 4, 6

Keep in A: [2, 3, 4, 1012]
Move to B: [6, 5, 1]
```

**Why LIS?**
- Minimizes the number of elements to move
- Elements already in order stay in place
- Reduces total operations

**Dynamic Programming Approach:**
```c
for each position i:
    for each previous position j < i:
        if values[j] < values[i]:
            dp[i] = max(dp[i], dp[j] + 1)
```

**Time Complexity:** O(n²)

---

#### **Phase 2: Turkish Algorithm (Turk)**

After moving non-LIS elements to stack B, push them back to stack A in the optimal order:

**Cost Calculation:**

For each element in B, calculate the cost to insert it into A:
```
cost = rotations_in_A + rotations_in_B
```

**Optimization (operations):**
- Use `rr` (rotate both) when both stacks rotate in the same direction
- Use `rrr` (reverse rotate both) similarly
- Choose the element with **minimum total cost** each iteration

**Example:**
```
Stack A: [2, 3, 4, 1012]
Stack B: [6, 5, 1]

1. Calculate costs:
   - Insert 6: cost = 3
   - Insert 5: cost = 2  ← cheapest!
   - Insert 1: cost = 4

2. Execute optimal moves for element 5
3. Repeat until B is empty
```

**Time Complexity:** O(n²)

---

### 3️⃣ **Final Alignment**

After all elements are in stack A, rotate to position the minimum element at the top:
```
Before: [4, 1012, 1, 2, 3]
After:  [1, 2, 3, 4, 1012] ✅ Sorted!
```

---

## 🎯 Why This Approach?

| Strategy | Problem Solved |
|----------|----------------|
| **LIS** | Minimizes elements to move |
| **Turk Algorithm** | Finds optimal insertion order |
| **Combined rotations (rr/rrr)** | Reduces operation count |
| **Hardcoded small arrays** | Guarantees efficiency for edge cases |

---

## 📊 Algorithm Visualization
```
┌─────────────────────────────────────────┐
│  Input: Unsorted Stack                  │
└──────────────┬──────────────────────────┘
               │
               ▼
        ┌──────────────┐
        │  Size ≤ 5?   │
        └──────┬───────┘
          YES  │  NO
               │
       ┌───────┴────────┐
       ▼                ▼
  ┌─────────┐    ┌──────────────┐
  │Hardcoded│    │Calculate LIS │
  │Solution │    │  (Phase 1)   │
  └─────────┘    └──────┬───────┘
                        │
                        ▼
                 ┌──────────────┐
                 │ Move non-LIS │
                 │  to stack B  │
                 └──────┬───────┘
                        │
                        ▼
                 ┌──────────────┐
                 │Turkish Algo  │
                 │  (Phase 2)   │
                 └──────┬───────┘
                        │
                        ▼
                 ┌──────────────┐
                 │Final Align   │
                 └──────┬───────┘
                        │
                        ▼
             ┌──────────────────┐
             │   Sorted Stack!  │
             └──────────────────┘
```

---

## 🚀 How to Run

### Compilation
```bash
make              # Compiles push_swap only
make bonus        # Compiles push_swap + checker
```

### Basic Usage
```bash
./push_swap 3 2 5 1 4
```

### With Random Numbers
```bash
ARG=$(shuf -i 1-100 -n 10); ./push_swap $ARG
```

---

## 🎁 Bonus: Checker

The **checker** program validates whether a sequence of operations correctly sorts the stack.

### How It Works

1. Reads the initial stack from arguments
2. Reads operations from **stdin** (one per line)
3. Executes each operation
4. Checks if the final stack is sorted and stack B is empty

### Usage

#### **Method 1: Pipe from push_swap**
```bash
./push_swap 3 2 5 1 4 | ./checker 3 2 5 1 4
```

**Expected output:**
- `OK` — Stack is sorted correctly ✅
- `KO` — Stack is not sorted ❌
- `Error` — Invalid operation or input

---

#### **Method 2: Manual Input**
```bash
./checker 3 2 1
```
Then type operations manually:
```
sa
rra
^D  (Ctrl+D to finish)
```

**Output:** `OK` or `KO`

---

#### **Method 3: From File**
```bash
./push_swap 5 4 3 2 1 > operations.txt
./checker 5 4 3 2 1 < operations.txt
```

---

### Checker Validation

The checker validates:

✅ **Valid operations:**
- `sa`, `sb`, `ss`
- `pa`, `pb`
- `ra`, `rb`, `rr`
- `rra`, `rrb`, `rrr`

❌ **Invalid operations:**
- Unknown commands
- Operations with wrong format
- Extra characters or spaces

---

### Example Workflow
```bash
# Generate operations
$ ./push_swap 2 1 3 0
pb
pb
sa
pa
pa

# Validate with checker
$ ./push_swap 2 1 3 0 | ./checker 2 1 3 0
OK ✅

# Test with wrong operations
$ echo -e "sa\nwrong\npa" | ./checker 3 2 1
Error ❌
```

---

## 📈 Performance

| Elements | Operations (Average) | Max Operations |
|----------|---------------------|----------------|
| 3        | ≤ 3                 | 3              |
| 5        | ≤ 12                | 12             |
| 100      | ~550                | < 700          |
| 500      | ~5000               | < 5500         |

---

## 🧪 Testing

### Test push_swap
```bash
# Test with 100 random numbers
ARG=$(shuf -i 1-500 -n 100 | tr '\n' ' '); \
./push_swap $ARG | wc -l

# Verify correctness
ARG=$(shuf -i 1-500 -n 100 | tr '\n' ' '); \
./push_swap $ARG | ./checker $ARG
```

---

## 🐛 Error Handling

Both programs handle the following errors:

| Error | Description | Output |
|-------|-------------|--------|
| No arguments | `./push_swap` | *(no output)* |
| Non-numeric | `./push_swap 1 2 abc` | `Error` |
| Duplicates | `./push_swap 1 2 2 3` | `Error` |
| Overflow | `./push_swap 2147483648` | `Error` |
| Invalid operation (checker) | Unknown command | `Error` |

---

## 📚 References

- [Longest Increasing Subsequence (LIS)](https://en.wikipedia.org/wiki/Longest_increasing_subsequence)
- [Dynamic Programming](https://en.wikipedia.org/wiki/Dynamic_programming)
- [Greedy Algorithm (Turk)](https://en.wikipedia.org/wiki/Greedy_algorithm)
- [Stack Data Structure](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))

---

## 👤 Author

**tlavared** - 42 São Paulo


*Made with ❤️ at 42 São Paulo*
