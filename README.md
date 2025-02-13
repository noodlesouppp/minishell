lexer -> parser -> expander -> executor (this is what ive read to be the best way to tackle the project. some people didnt bother with lexing but it is recommended this way)

1. lexer:
convert raw command line input into tokens(smallest units of meaning) (lexical analysis)

-> first identify and seperate words, quotes, operators (| , > , < ) etc

-> implement tokeniser function that scans all input and outputs an array of tokens

3. parser:

build a structure (abstract syntax tree) that organises the tokens based on the command's intended structure (https://minishell.simple.ink/building-a-linux-shell-f52cadb5145b44b5b34ac4eb84b21593)

-> define the rules for only valid syntax e.g command -> arguments , or command | command, command > file etc

-> convert the tokens into structured data which allows shell to understand sequence and order of commands
https://medium.com/@abkabex/minishell-42-f680eadde592

4. expander:
   
handle the expansion for env vars (like "$(CHAR)") and other special tokens (like $?)

handle the quotes (single + double)

???

5. executor:
   
execute the parsed commands
- the built-ins
- the pipes
- the signals

additionally:
+ display prompt when waiting for new command
+ working command history

ill take a look at what joe has done (i think most of it is for parsing..) and will try and sort out what we can use (hopefully most of it) and then add on the lexing part ourselves. 

ill have to also research more especially about expanding since its quite new to me

for now i think i can handle the signals part (ctrl d, ctrl c etc) and maybe you can handle the pipes part? (i dont know jack shit about pipes right now 💀) but let me know what you think and also if you have any ideas or different approaches you want to go through, im down for anything!
