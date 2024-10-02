
# Msh

a C based unix shell that mimics the behavior of Bash. 


![App Screenshot](https://github.com/resherra/msh/blob/master/msh.png)


## Run Locally

Clone the project

```bash
  gcl git@github.com:resherra/msh.git && cd msh
```


Get the Readline library if its not already exist (i'm using brew) && change the paths in the Makefile

```bash
  brew install readline
```

Build the program's files && Run

```bash
  make && ./msh 
```