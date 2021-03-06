Dragon Brainfuck Interpreter
============================

This is a simple Brainfuck interpreter.

What's new
----------

Version 3 has been completely rewritten in C (where version 2 was in C++).
Also the new version has almost no dependencies other than the C runtime library.
As an optional feature a compiler mode has been added which allows to compile a brainfuck script into a real program.
This feature requires the presence of the libtcc library.

Requirements
------------

Optional:
* libtcc (TinyCC >= 0.9.26)

Tested Compilers
----------------

* TinyCC (tcc) 0.9.26
* GCC 4.6.3
* Clang 3.0
* Microsoft Visual C++ 2012

Tested Operating Systems
------------------------

* Gentoo Linux
* Linux Mint
* Windows

Travis Status
-------------

[![Build Status](https://travis-ci.org/Drako/dbfi.svg?branch=master)](https://travis-ci.org/Drako/dbfi)

