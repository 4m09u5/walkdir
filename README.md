# Walkdir

### What does this program do?

This program is an analog of `find` utility. It can be used to show contents of a directory and its subdirectories.

### How to build this project

This project can be built in release and debug modes using `make` utility. 

```
make MODE=release
```

or

```
make MODE=debug
```

### How to use this program

Program can be configured using following parameters:

* `-l` to display symbolic links
* `-d` to display directories
* `-f` to display files
* `-s` to sort output accroding to `LC_COLLATE`

Parameters l, d, and f are automatically set if none of them was provided.
