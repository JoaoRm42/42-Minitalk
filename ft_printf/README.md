# 42 ft_printf Project

Welcome to the 42 ft_printf Project repository! This project is part of the 42 curriculum, and its goal is to reimplement the standard `printf` function in C. This project will help you understand variadic functions, formatted output, and other advanced C programming concepts.

## Table of Contents
- [Introduction](#introduction)
- [Project Objectives](#project-objectives)
- [Features](#features)
- [Requirements](#requirements)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Testing](#testing)
- [Contributing](#contributing)
- [Acknowledgments](#acknowledgments)
- [Code](#code)

## Introduction

The `ft_printf` project is designed to help students gain a deeper understanding of variadic functions and formatted output in C by reimplementing the `printf` function. This function is widely used for output in C programs, and recreating it will provide valuable insights into its inner workings.

## Project Objectives

- Implement a custom `printf` function.
- Handle format specifiers and output formatting rules.
- Manage variadic function arguments.
- Ensure the function behaves similarly to the standard `printf`.

## Features

### Mandatory
- Supported conversions: `%c`, `%s`, `%p`, `%d`, `%i`, `%u`, `%x`, `%X`, `%%`.
- Output count return value, compatible with `printf` behavior.

### Bonus
- Flags support: `-`, `0`, `.`, `#`, `+`, and space.
- Field minimum width support.
- Combination of flags under all required conversions.

## Requirements

- A Unix-based operating system (Linux or macOS).
- GCC/Clang compiler.
- Make.
- Basic understanding of C programming.

## Project Structure

A brief overview of the project structure:

```text
.
├── ft_printf.c
├── ft_printf.h
├── ft_printaddr.c
├── ft_printhexa.c
├── ft_printnbr.c
├── ft_printstr.c
├── ft_singlechar.c
├── ft_printf_bonus.c
├── ft_printf_bonus.h
├── ft_printf_parse_bonus.c
├── ft_printf_format_bonus.c
├── ft_printf_text_bonus.c
├── ft_printf_dispatch_bonus.c
├── ft_printf_convert_bonus.c
├── ft_printf_output_bonus.c
├── Makefile
└── README.md
```

## Installation

1. **Clone the Repository**:
```bash
git clone https://github.com/joaoped2-42PORTO/42-ft_printf.git
cd 42-ft_printf
```

2. **Compile Mandatory**:
```bash
make
```

3. **Compile Bonus**:
```bash
make bonus
```

This will generate `libftprintf.a`.

## Usage

To use `ft_printf` in your own projects, include the header and link the library.

1. **Include the Header**:
```c
#include "ft_printf.h"
```

2. **Link the Library**:
```bash
gcc -o myprogram myprogram.c -L. -lftprintf
```

3. **Run the Program**:
```bash
./myprogram
```

## Testing

- Norminette:
```bash
norminette *.c *.h
```

- Rebuild from scratch:
```bash
make fclean && make
make fclean && make bonus
```

## Contributing

Contributions are welcome! If you have suggestions or improvements, feel free to open an issue or submit a pull request.

## Acknowledgments

- The 42 Network for providing the project and evaluation framework.
- The C community for documentation and references.

## Code

- Norminette: OK
- Mandatory: ✅
- Bonus: ✅
