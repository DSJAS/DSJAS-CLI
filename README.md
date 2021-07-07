# DSJAS-CLI - **Command-Line Interface for DSJAS**

The DSJAS CLI is a \*NIX command line program for interacting with a DSJAS install, performing common development and administration operations.

Features include:

* Interface to DSJAS configs for editing/retrieving
* Interface to DSJAS admin features
* Developer tools for managing plugins and plugin development
* UNIX-style scripting interfaces for extensible scripting

## Build instructions

DSJAS-CLI is written in C99, which means basically any modern compiler will support it. To build, you **must** first have the submodules initialised. If you did not clone with the ``recursive`` options, you need to run:

```
git submodule update --init
```

To build, simply run 

```
make
```

in the root of the project. By default, the compiler uses the ``CC`` environment variable. If this does not work for you, feel free to override it using:

```
make CC=COMPILER_HERE
```

### Developer builds

Dev builds can be generated setting the ``DEBUG`` make variable, like so:

```
make DEBUG=1
```

By default, this will disable optimisation and generate an executable with readable debug information. This should make it much easier to debug using tools such as ``gdb`` and ``radare2``.

## Code style

Code style is based off of that in the Linux Kernel. A ``clang-format`` style guide is provided in the root of the project.
