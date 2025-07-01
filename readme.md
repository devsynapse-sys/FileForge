<h1 align="center">FileForge</h1>
<p>FileForge is a lightweight, console-based file manager for Windows, built with C++17. It offers a sleek and efficient way to navigate and manage files and directories directly from the command line. With features like colorized output, interactive selection, file search with regex, and byte-by-byte file comparison, FileForge is designed for developers and power users who want a fast and customizable file management tool.</p>

---

## Features

- Directory Navigation: Seamlessly move through directories with cd and view contents with dir.
- Interactive Selection: Select files or folders interactively with numbered menus for quick actions (open, delete, copy, move).
- File Operations: Copy (cp), move (mv), delete (rm), and create (touch) files and directories (mkdir).
- Progress Bar: Visual progress bar for file copying operations.
- File Search: Find files using regular expressions with the find command.
- File Comparison: Compare files byte-by-byte with the diff command.
- Colorized Output: Visually distinguish directories (green), files (cyan), and errors (red).
- Windows-Optimized: Built specifically for Windows with UTF-8 support for file names.

---

## Project Structure

```
FileForge/
├── include/
│   ├── FileManager.hpp
│   ├── DirectoryViewer.hpp
│   ├── FileOperations.hpp
│   ├── ConsoleUtils.hpp
├── src/
│   ├── main.cpp
│   ├── FileManager.cpp
│   ├── DirectoryViewer.cpp
│   ├── FileOperations.cpp
│   ├── ConsoleUtils.cpp
├── README.md
├── .gitignore
```

---

## Prerequisites

Windows operating system
C++17 compatible compiler (e.g., MSVC, MinGW)
Git (optional, for cloning the repository)

---

## Usage
Launch FileForge.exe and type help to see the list of available commands.
