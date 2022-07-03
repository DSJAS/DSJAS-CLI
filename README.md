# DSJAS-CLI - **Command-Line Interface for DSJAS**

The DSJAS CLI is a \*NIX command line program for interacting with a DSJAS install, performing common development and administration operations.

Features include:

* Interface to DSJAS configs for editing/retrieving
* Interface to DSJAS admin features
* Developer tools for managing plugins and plugin development
* UNIX-style scripting interfaces for extensible scripting

## Build instructions

DSJAS-CLI is written in C99, which means basically any modern compiler will support it. To build, you **must** first have the submodules initialised. If you did not clone with the ``recursive`` options, you need to run:

```shell
git submodule update --init
```

To build, simply run

```shell
make
```

in the root of the project. By default, the compiler uses the ``CC`` environment variable. If this does not work for you, feel free to override it using:

```shell
make CC=COMPILER_HERE
```

### Developer builds

> **NOTE:** Previous versions of the makefile would include a parameter called ``DEBUG`` which enabled debug developer builds. This is no longer supported. You must now set ``CFLAGS`` manually.

To generate a debug build, you can set the ``CFLAGS`` variable to the following:

```shell
make CFLAGS="-O0 -g"
```

This will disable code generation optimisation and enable debug output being placed into the binary (along with some useful data for debuggers, like symbol tables being preserved etc. This will make it much easier to debug the program in programs such as ``gdb`` or ``radare2``.

## Code style

Code style is based off of that in the Linux Kernel. A ``clang-format`` style guide is provided in the root of the project.
