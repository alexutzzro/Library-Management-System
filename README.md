# Library Management System - EN

This project is a **Library Management System** developed in C, providing functionalities for managing books and handling loans.

## Features

- Adding, deleting, and updating book information
- Searching for books by title, author, or type
- Managing loans and returns
- Book information is stored in the `biblioteca.txt` file, which must be in the same location as the executable
- Administrator interface with password-protected access. The password is `suntocarte`.

## System Requirements

- C compiler (e.g., GCC)
- CMake for build management
- `ncurses` library for terminal interaction

## Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/alexutzzro/Library-Management-System.git
   cd Library-Management-System
   ```

2. **Compile the project using CMake:**
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

   Ensure that you have installed the `ncurses` library. On Debian-based systems, you can install it with:
   ```bash
   sudo apt-get install libncurses5-dev libncursesw5-dev
   ```

   Additionally, on macOS, you can install `ncurses` with:
   ```bash
   brew install ncurses
   ```

## Usage

After compilation, run the program from the `build` directory:
```bash
./LibraryManagementSystem
```

Follow the on-screen instructions in the terminal to navigate through the menus and use the provided functionalities.

## License

This project was created as part of the Programming Project course at the West University of Timișoara.

---

# Sistem de Gestiune a Bibliotecii - RO

Acest proiect reprezintă un **Sistem de Gestiune a Bibliotecii** dezvoltat în limbajul C, oferind funcționalități pentru administrarea cărților și gestionarea împrumuturilor.

## Caracteristici

- Adăugarea, ștergerea și actualizarea informațiilor despre cărți
- Căutarea cărților după titlu, autor sau tip
- Gestionarea împrumuturilor și returnărilor
- Informațiile despre cărți sunt stocate în fișierul `biblioteca.txt`, care trebuie să fie în aceeași locație cu executabilul
- Interfață pentru administratori cu acces securizat prin parolă. Parola este `suntocarte`.

## Cerințe de sistem

- Compilator C (de exemplu, GCC)
- CMake pentru gestionarea build-ului
- Biblioteca `ncurses` pentru interacțiunea cu terminalul

## Instalare

1. **Clonarea repository-ului:**
   ```bash
   git clone https://github.com/alexutzzro/Library-Management-System.git
   cd Library-Management-System
   ```

2. **Compilarea proiectului folosind CMake:**
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

   Asigură-te că ai instalat biblioteca `ncurses`. Pe sistemele bazate pe Debian, o poți instala cu:
   ```bash
   sudo apt-get install libncurses5-dev libncursesw5-dev
   ```

   De asemenea, pe sistemele MacOS, biblioteca `ncurses` se poate instala cu:
   ```bash
   brew install ncurses
   ```

## Utilizare

După compilare, execută programul din directorul `build`:
```bash
./LibraryManagementSystem
```

Urmează instrucțiunile afișate în terminal pentru a naviga prin meniuri și a utiliza funcționalitățile oferite.

## Licență

Acest proiect a fost realizat în cadrul laboratoarelor de la disciplina Proiect de programare, din cadrul Universității de Vest din Timișoara.
