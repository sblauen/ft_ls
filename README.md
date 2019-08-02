# ft_ls
An own implementation of the famous `ls` command.

## Table of Content
* [ft_ls](#ft_ls)
* [Table of Content](#table-of-content)
* [Synopsis](#synopsis)
* [Description](#description)
* [Build](#build)
* [Usage](#usage)

## Synopsis
ft_ls is the first of [42][1]'s Unix branch projects. The purpose is to understand the basics of a \*nix-like filesystem.

## Description
The mandatory part of the project consists of writing a ls command with the options -a, -l, -R, -r and -t.

Only following system calls and standard library functions are allowed:
- lstat,
- stat,
- readlink,
- time,
- write,
- closedir,
- opendir,
- readdir,
- ctime,
- exit,
- getpwuid,
- getgrgid,
- getxattr,
- listxattr,
- free,
- malloc,
- perror,
- strerror.

As bonuses, the options -c, -f, -S, -u and -1 have been added.

The last time it was tested, this implemetation was a bit faster than OS X's ls but slower than GNU's one.

## Build
```
$ git clone https://github.com/sblauen/ft_ls.git && cd ft_ls && make
```

## Usage
```
$ ./ft_ls [-acflRrStu1] [FILE]...
```
[1]: https://42.fr "42Born2Code"
