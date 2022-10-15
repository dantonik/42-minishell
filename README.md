## minishell

1. Lexer
2. Parser
3. (Expander)
4. Executor
5. Past actions

Lexer -> Tokens
Parser -> AST?


builtins
	echo -n
	cd
	pwd
	export
	unset
	env
	exit


\< redirect input

\> redirect output

\<< ???

\>> redirect output in append mode


handle environment variables
implement pipes
$? expands to the exit status of the most recently executed foreground pipeline
handle ctrl-C/D/\

Bonus part
	&& and || with parenthesis for priorities
	wildcards *
  
