# push_swap

**push_swap** is a project that aims to sort a stack using another auxiliary stack.

## Available operations

The program uses the following operations to manipulate the stacks:

- `sa`  — swap the first two elements at the top of stack A
- `sb`  — swap the first two elements at the top of stack B
- `ss`  — perform `sa` and `sb` simultaneously
- `pa`  — push the top element from stack B to stack A
- `pb`  — push the top element from stack A to stack B
- `ra`  — rotate stack A upwards (the first element becomes the last)
- `rb`  — rotate stack B upwards
- `rr`  — perform `ra` and `rb` simultaneously
- `rra` — rotate stack A downwards (the last element becomes the first)
- `rrb` — rotate stack B downwards
- `rrr` — perform `rra` and `rrb` simultaneously

## How to run

To compile the program, use the command:

```
make
```

Then, run the program passing a list of integers, **without duplicates**, for example:

```
./push_swap -1 0 5 4 3 1 2 6
```

The program will process the input and output the sequence of operations to sort the stack.
