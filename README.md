>>> The Makefile contains the target in it.So, to complie type "make".To execute the executable "a.out" press "./a.out".The shell will be presented.
Details of each file:
>>>header.h : It contains all the libraries which are to be included.
>>>declaration.h : It contains the declaration of all functions and the global variables.
>>>Makefile : It contains the target which is to be compiled.
>>>shell.c : It contains the main while loop which runs all the time and it calls the prompt and input functions.It also contains the handler function which takes care of the signals and indicates us when a background process is terminated.It also contains the handler functions for CTRL+C and CTRL+V .(Spec 5 in Assignment 3).
>>>prompt.c : It contains the function prompt which prints the command prompt.
>>>input.c : It contains input and execute functions.Input function takes the input and tokenize it w.r.t "; and " ".And it specifies whether it is a background or a foreground process.
>>>execute.c : It executes the given command .
>>>echo.c : It contains the echo function which executes the echo command.
>>>pwd.c : It contains the pwd function which executes the pwd command. 
>>>cd.c : It contains the cd function which executes the cd command.
>>>ls.c : It contains the ls function which executes the ls command.
>>>pinfo.c : It contains the pinfo function which executes the pinfo command.
>>>IORedirection.c : It contains the Onlyredirection function which executes redirections without piping.(Spec 1).
>>>pipe.c : It contains the piping function which deals with the pipes without redirection and pipes with redirection(Spec 2 and Spec 3).
>>>jobs.c : It contains all the functions related to the Specification 4.
>>>Bonus : The first part of the bonus (cd -) is done in the cd file.# Custom_Linux_Shell
# Linux_Shell
