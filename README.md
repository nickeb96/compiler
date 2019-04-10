
C Compiler from Scratch
=======================


This is a basic C compiler that I wrote over the summer after my sophomore year.  The goal of this project was to gain a deeper understanding of how compilers work.  The only part that I offloaded to a library is the tokenizer which uses lex.  Eventually I would like to replace it with the tokenizer that I wrote more recently <https://github.com/nickeb96/tokenizer>.

The compiler was written and tested on a mac, but since it outputs x86_64 assembly in GAS syntax it should work on GNU/Linux as well.  The only caveat is that on Darwin all C symbols are prepended with an underscore once they are assembled, which this compiler respects.  This doesn't happen on Linux which may cause linking issues on that platform.

This is not a fully compliant C compiler, there are several features that I did not have time to complete while I was working on it.  Here's a list of some of the most important ones that are or aren't in.

- [x] while loops
- [ ] for loops - I just emulate them with a while loop in the examples.
- [ ] do while loops - Emulate with a while loop and an if statement with a break at the end.
- [x] arithmetic operators
- [x] comparison operators
- [ ] bitwise operators - These would be relatively simple to add.
- [x] dereference and address of operators
- [x] expression grouping with parenthesis, for instance `(x + 1) * y`
- [x] if statements with optional else clause
- [ ] switch statements - A chain of if else statements is a temporary alternative.
- [x] break and continue statements
- [ ] global variables/constants
- [ ] subscript operator - Emulate with pointer arithmetic and a dereference.
- [x] logical and/or operators with proper short circuiting
- [ ] compound assignment (+=, /=, etc.) - Just do the operation and then the assignment.


Another incomplete part is the type system.  Unfortunately the only type available is a 64-bit quadword that can serve as either an integer or a pointer.  The type system was the last thing that I worked on, but it was not fully integrated into the rest of the compiler.  A side effect of this is that pointer arithmetic is not automatically scaled by the size of the type.  For example `(array + i)` would need to be written as `(array + i * 8)`, assuming *array* is an array of quadwords.

This compiler does not strip comments or perform any preprocessor directives, however I wrote a C preprocessor here <https://github.com/nickeb96/preprocessor> that does this and could be run on files before passing them to the compiler.
