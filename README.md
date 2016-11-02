# 42sh

## Description

42sh is a bash clone made at the 42 school.

This project is designed to be simple and modular.

Fell free to reuse some code. As This project is designed to be modular, you can compile separatly the parser to understand how it's works.

```
make
./42sh
```

## Features

* Job control
* History
* Pipes, redirections, heredoc
* Auto-completion
* Line edit
* Builtins

## Show me the code!

* srcs/shell folder handles the main stuff and environement
* srcs/prompt hanldes termcaps stuff
* scrs/parser is the command line parser
* srcs/lexer handles lexing
* srcs/executor handles command line execution (pipes, exec, etc)
* srcs/builtins handles all the builtins
