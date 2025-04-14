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

In the function `main_test_v. c` function, each group of tokens is stored like this:

````c
t_tokens **tokens_by_segment;
````

This is an array of linked lists. Each position represents a pipe:

````c
tokens_by_segment[0] → tokens of first pipe
tokens_by_segment[1] → tokens of second pipe
...
````

From there you can easily access the tokens to execute commands.

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

## COMMON ERRORS

- Make sure `check_args_fixed()` detects quotes correctly.
- Check `pipe_segments[i] != NULL` before using it.
- If you see `pipe_segments[n] is NULL`, `count_splitted()` is probably miscounting.

---

## TESTING RECOMMENDATIONS

- Try `"`, `'`, `>`, `>>`, `>>`, `<`, `<<`, `|`.
- Validate edge cases such as:
  - Unclosed quotes
 - Empty pipes
 - Multiple spaces

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