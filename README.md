# Welcome to PseudoLang
This is a byte code interpreter for a light weight scripting language which has all the fundamental
features of a programming language and more!

## Current State
Currently, the compiler is very undercooked, and there is a lot of work to be done.
You can input simple expressions with number, boolean, and nil types to get a result
of either a number, boolean, or nil value. Please note that Strings are not yet implemented.
Soon, you can expect String values to work in expressions and print statements to be added, followed by
scoping, variable storage, and most important, install instructions.

Try running: 4 + 5 * (3 - 2 * -8) / 6

### Please Note
The current result of expressions are simply popped off the stack and printed. 
Change line 26 in VM.cpp to the respective value type you're resulting.
