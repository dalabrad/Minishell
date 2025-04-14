# MINI-SHELL PARSER: GUIDE TO COMPILING, TESTING AND USING TOKENS

---

## MAIN STRUCTURE

- `main_test_v.c` - Main testing function.
- `ft_minisplit.c` - Separate input by pipes.
- `ft_clasifyTokens.c` - Classify each word/token.
- `utils_parsing.c` - Auxiliary functions (checking for quotes, spaces, etc).
- `utils_initClean.c` - Memory management.

---

## HOW TO COMPILE

````bash
make testv
````

This command will compile your Minishell with the `main_test_v.c` function for testing.

---

## HOW TO RUN

````bash
./minishell
````

And then you can enter commands like:

````bash
echo "hello world" > out.txt | ls -l | wc -l
````

---

## WHAT IT DOES

1. Separates the input by `|`.
2. Tokenize each pipe segment.
3. Classify tokens as `COMMAND`, `ARG`, `RED_OUT`, etc.
4. Displays information for each token (including whether it was enclosed in quotes).
5. Apply rules to decide which token is the command in each pipe.

---

## EXAMPLE OUTPUT

````bash
=========== PIPE SEGMENTS ===========
 -----> Tokenizing: [echo "hello world" > out.txt]
→ Token: echo | Type: COMMAND | Quoted: no
→ Token: "hello world" | Type: ARG | Quoted: yes
→ Token: &gt; | Type: RED_OUT | Quoted: no
→ Token: out. txt | Type: ARG | Quoted: no
Total tokens: 4

-----> Tokenizing: [ ls -l ]
→ Token: ls | Type: COMMAND | Quoted: no
→ Token: -l | Type: OPTION | Quoted: no
Total tokens: 2

-----> Tokenizing: [ wc -l ]
→ Token: wc | Type: COMMAND | Quoted: no
→ Token: -l | Type: OPTION | Quoted: no
Total tokens: 2
````

---

## ACCESS TO TOKENS

In the `main_test_v.c` function, each group of tokens is stored like this:

````c
t_tokens **tokens_by_segment;
````

This is an array of linked lists. Each position represents a pipe:

````c
tokens_by_segment[0] → first pipe tokens
tokens_by_segment[1] → second pipe tokens
````


From there you can easily access the tokens to execute commands.

### Where are the tokens ready to execute?
After ft_minisplit(), you call:

````c
tokens_by_segment[i] = check_args_fixed(pipe_segments[i], &segment_tokens);
````

Then:

````c
// tokens_by_segment[i] contains the linked list of tokens from PIPE[i]
````

Each t_tokens has:

str: the string of the token

type: type of token (COMMAND, ARG, RED_OUT, etc. )

was_quoted: if it came in quotes

Example:
If you want to execute the first pipe, you can do:

````c
t_tokens *cmd = tokens_by_segment[0];
while (cmd)
{
 printf("TOKEN: %s | TYPE: %d\n", cmd->str, cmd->type);
 cmd = cmd->next;
}
````

---

### Token types (t_TokenType)

````c
typedef enum t_TokenType {
RED_IN,
RED_OUT,
HEREDOC,
APPEND_OUT,
OPTION,
COMMAND,
SETTING,
ARG,
ERROR
} t_TokenType;
````

---

Next step: execution
Starting from the tokens of tokens_by_segment[i]:

The first token with type COMMAND is the main command.

The ones with type ARG, OPTION, etc. go to argv[].

If there are redirections (RED_OUT, HEREDOC, etc.), you can save the filename (token-&gt;next-&gt;str) and apply dup2() afterwards.


## MEMORY CLEANUP

At the end of the loop, tokens and pipe_segments are successfully freed:

````c
free_array2(pipe_segments);
for (size_t j = 0; j <= i_pipes; j++)
 free_tokens_list(tokens_by_segment[j]);
free(tokens_by_segment);
````

---

## DEBUGGING WITH GDB

````bash
make gdb
````

- Test with `"`, `'`, `>`, `>`, `>>`, `<`, `<<`, `|`.
- Validate edge cases like:
  - Unclosed quotes
 - Empty pipes
 - Multiple spaces
- Try changing the config GDB file to make breakpoints in more functions.

---

## MEMORY CLEARING

At the end of the cycle, the tokens and pipe_segments are successfully freed:

````c
free_array2(pipe_segments);
for (size_t j = 0; j <= i_pipes; j++)
 free_tokens_list(tokens_by_segment[j]);
free(tokens_by_segment);
````

---

## DEBUGGING WITH GDB

````bash
make gdb
````

- Test with `"`, `'`, `>`, `>>`, `<`, `<<`, `|`.
- Validate edge cases like:
  - Unclosed quotes
 - Empty pipes
 - Multiple spaces
- Try changing the config GDB file to make breakpoints in more functions.

---

## EXTRA: USEFUL FUNCTIONS

- `poly_substr()` - Separate words by handling quotes.
- `set_command_type()` - Decide which token is the primary command.
- `token_type_str()` - Returns string representative of token type.

---

## FOR RUN TEAM

Use `tokens_by_segment[i]` as input to your executor. Each `t_tokens` node has:

```c
char *str // content
t_TokenType type // token type
int was_quoted // quote
````

---