<h1 align="center">📄 get_next_line</h1>
<p align="center">
  <i>Read a file line by line in C</i>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue.svg" />
  <img src="https://img.shields.io/badge/Project-42%20School-darkblue" />
</p>

---

## 📘 About the Project

**get_next_line** is a [42 School] project that focuses on reading from a file descriptor **one line at a time**, handling multiple file descriptors simultaneously, and managing memory effectively.

This project is often a student’s first real encounter with:
- File descriptor management
- Static variables
- Buffer manipulation
- Dynamic string assembly in C

---

## 🧠 Project Goals

- Read a file **line by line** using only low-level functions like `read`.
- Handle reading from **multiple file descriptors**.
- Manage memory and buffer leftovers **without leaks**.
- Build a function with this exact prototype:

```c
char *get_next_line(int fd);
