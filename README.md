### Raom

The beginnings of a compiler. :racing_car:

Currently compiles `+, -, *, /, ()` using LISP syntax.

Developed for macOS. Could run into problems on Linux with `_main` rather than `main`, among other things.

Written in C89 apart from an anonymous union (`__extension__`).

```
(* 5 (+ 90 10))
```
Is compiled to
```
.intel_syntax noprefix
.globl _main
_main:
  push 5
  push 90
  push 10
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rax
  ret
```

Compiling *that* with Clang/GCC and running the binary will return `244`.

You can check the return value of a program with `echo $?`.
