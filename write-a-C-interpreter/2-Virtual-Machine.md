In this chapter, we are going to build machine and design our own instruction set that runs on the VM. This VM will be the target platform of the interpreter's code generations phase.

If you've heard of JVM and bytecode, that's what we are trying to build, but way way simpler one.

# How computer work internally

There are three components we need to care about: CPU, register and memory. Code(or assembly unstruction) are stored in the memory as binary data;
CPU will retrieve the instruction one by one and execute them; the running states of the machine is stored in registers.

## Memory

Memory can be used to store data. By data I mean code(or called assembly instructions) or other data such as the
message you want to print out. All of them are stored as binary.

Modern operating system introduced Virtual Memory which maps memory addresses used by a program called virtual address into physical addresses
into physical addresses in computer memory. It can hide the physical details of memory from the program.

The benefit of virtual memory is that it can hide the details of a physical memory from programs. For example, in
32bit machine, all the available memory address is 2^32 = 4G while the actual physical memory may be only 256M.
The program, will still think that it can have 4G memory to use, the OS willmap them to physical ones.

Of course, you don't need to understand the details about that. But what you should understand that a program's usable memory is àrtioned into several
segments:

1. `text` segment: for storing code(instructions).
2. `data` segment: for storing initialized data: For example `int i = 10;` will need to utilize this segment.
3. `bss` segment: for storing un-initialized data. For example `int i[1000];` doesn't need to occupy `100*4` bytes, because the actual values in the array
don't matter, thus we can store them in `bss`to save some space.
4. `stack` segment: used to handling the states of function calls, such as calling frames and local variables of a function.
5. `heap` segment: use to allocate memory dynamically for program.

Our virtual machine tends to be as simple as posible, thus we don't care about the `bss` and `heap`. Our interpreter don't support the initialization  of data
thus we'll merge the `data` and `bss` segment. More over, we only use `data` segment for storing string literals.

We'll drop `heap` as well. This might sound insane because theorically the VM should mantain a `heap` for allocation memories. But hey, an interpreter itself is also a program which had its heap allocated by our computer. We can tell the program that we want to interpret to utilize the interpreter itself is also a program
which had its heap allocated by our computer. We can tell the program that we want to interpret to utilize the interpreter's heap by introducing an instruction
`MSET`. I won't say it is cheating because it reduces the VM's complexity without reducing the knowledge we want to learn about compiler.

Thus we adds the following codes in the global area:

```c
int *text,      // text segment
    *old_text,  // for dump text segment
    *stack;     // stack
char *data;     // data segment

```

Note the `int`here. What we should write is actually `unsigned` because we'll store unsigned data(such as pointer/memory address) in
the `text` segment. Note we want our interpreter to be bootstrapping(interpreter itself), thus we don't want to introduce `unsigned`. Finally
the `data` is `char *`because we'll use it to store strings literals only.

Finally, we add the code in the mian function to actually allocate the segments:

```c
int main() {
close(fd);

...

// allocate memory for virtual machine
if (!(text = old_text = malloc(poolsize))) {
    printf("could not malloc(%d) for text area \n", poolsize);
    return -1;
}
if (!(data = malloc(poolsize))) {
    printf("could not malloc(%d) fir data area \n", poolsize);
    return -1
}
if (!(stack = malloc(poolsize))) {
    printf("could not malloc(%d) for stack area \n", poolsize);
    return -1
}

...

program();

}
```

# Registers

Registers are used to store the running states of computers. There are several of them in real computers while our VM uses only 4:

1. `PC`: program counter, it stores an memory address in which stores the **next** instruction to be run.
2. `SP`: stack pointer, which always points to the top of the stack. Notice the stack grows from high address to low address so that when we push
    a new element to the stack, `SP` decreases
3. `BP`: base pointer, ponts to some elements on the stack. It is used in function calls.
4. `AX`: a general register that we used to store the result of an instruction.

in order to fully understand why we need these registers, you need to understand what states will a computer need to store during a computation. They are just a place to store value. you will get better understanding after finished this chapter.

Well, add some code into the global area:

```c
int *pc, *bp, *sp, *ax, *cycle; // virtual machine registers
```

And add the initialization code in `main` function. Note that `pc` should points to the main function of the program to be interpreted.
But we don't have any code generation yet, this skip for now.

```
    memset(stack, 0, poolsize);
    ...

    bp = sp = (int *)((int) stack + poolsize);
    ax = 0;

    ...
    program();

```
What's left is the CPU part, what we should actually do is implementing the instruction sets. We'll save that for a new section.

# Instruction Set

Instruction set is a set of instruction that CPU can understand, it is the language we need to master in order to talk to CPU. We are going to design a language for our VM, is it based on x86 instruction set yet much simpler.

We'll start by adding an `enum`type listing all the instructions that our VM would understand:

```c
// instructions
enum { LEA, IMM, JMP, CALL, JZ, JNZ, ENT, ADJ, LEV, LI, LC, SI, SC, PUSH,
    OR, XOR, AND, EQ, NE, LT, GT, LE, GE, SHL, SHR, ADD, SUB, MUL, DIV, MOD,
    OPEN, READ, CLOS, PRTF, MALC, MSET, MCMP, EXIT };

```

These instructions are ordered intenionally as you will find out later that instructions with arguments comes first while those without arguments comes after. The only benefit here is for printing debug info. However we will not rely on this order to introduce them.

# MOV

`MOV`is one of the most fundamental instructions you'll met. Its job is to move data into registers or the memory, fink of like the assignment expression in C. There are two arguments in `x86`'s `MOV`instruction: `MOV dest, source`(intel style), source can be a number, a register or a memory address.

But we won't follow `x86`. On one hand our VM has only one general register(`AX`), on the other hand it is difficult to determine the type of the arguments(whther it is anumber, register or address). Thus we tear `MOV` apart into 5 pieces:

1. `IMM <num>` to put immediate `<num>` into register `AX`.
2. `LC`to load a character into `AX` memory address which is stored in `AX` before execution.
3. `LI`just like `LC` but dealing with integer instead of character.
4. `SC`to store the character in `AX` into memory whose address is stored on the top of the track.
5. `SI` just like `SC` but dealing with integer instead of character.

What? I want one `MOV, not 5 instruction just to replace it! Don't panic! you should know that `MOV` is actually a set of instruction that depends on the `type`of its argumens, so oyu got `MOVB` for bytes and `MOVW` for words, etc. Now `LC/SC` and `LI/SI` don't seems that bad, uha?

Well the most important reason is tha by turning `MOV` into 5 sub instructions, we reduce the complexity a lot! Only `IMM`will accept an argument now yet no need to worry about its type.

Let's implement it in the `eval` function:

```
void eval() {
    int op, *tmp;
    while (1) {
        op = *pc++; // get next operation code
        if (op == IMM)      {ax = *pc++}                // load immediate value to ax
        else if (op == LC)  {ax = *(char *)ax;}         // load character to ax, address in ax
        else if (op == LI)  {ax = *(int *)ax;}          // load integer to ax, address in ax
        else if (op == SC)  {ax = *(char *)*sp++ = ax;} // save character to address, value in ax, address on stack
        else if (op == SI)  {*(int *)*sp++ = ax;}       // sve integer to address, valu in ax, address on stack
    }

    ...
    return 0;
}
```

`*sp++` is used to `POP` out one stack element.

You might wonder why we store the address in `AX`register for `LI/LC` while storing them on top of the stacksegment for `SI/SC`. The reason is that the result of an instruction is stored i `AX` by default. The memory address is also calculate by an instruction, thus it is more convenient for `LI/LC` to fetch directly from `AX`. Also `PUSH`can only push the value of `AX` onto the stack. So if we want to put an address onto the stack, we'll have to store it in `AX` anyway, why not skip that?




















