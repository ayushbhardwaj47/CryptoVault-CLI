# 🔐 CryptoVault-CLI

An advanced, highly secure terminal-based password manager built entirely in C. Designed to safely store website credentials, linked identifiers (emails/usernames), and passwords using dynamic memory and symmetric encryption.

## 🚀 Key Features & Concepts Used

* **Dynamic Memory Allocation (DMA):** Utilizes `malloc`, `realloc`, and `free` to scale the vault infinitely without memory leaks or segmentation faults.
* **Bitwise XOR Encryption:** Implements a symmetric cipher using the `^` operator to encrypt passwords in real-time, keeping data safe in RAM.
* **Decoy Authentication (Control Flow):** Features a dual-PIN system. Entering the 'Decoy PIN' boots a fake dummy vault to protect real assets during an emergency.
* **Master Recovery System (Strings):** Uses string manipulation (`strcmp`, `strcspn`) to reset forgotten master PINs via a secret recovery word.
* **Password Strength Analyzer:** Evaluates user inputs for uppercase, lowercase, numbers, and symbols to ensure maximum entropy.
* **Smart Auto-Sorting:** Implements Bubble Sort algorithm to automatically arrange the vault alphabetically before displaying.
* **Array of Structures:** Groups Website, Identifier, and Password into a cohesive `Credential` struct for efficient data handling.

---

## 📸 Project Screenshots

### 1. Initial Setup & Vault Configuration
![Setup](Screenshot%202026-11-03%20100022.png)

### 2. Generating & Adding Passwords
![Adding Passwords](Screenshot%202026-11-03%20100041.png)

### 3. Decoy Vault & Account Recovery
![Recovery](Screenshot%202026-11-03%20100104.png)

---

## 💻 How to Run (Local Compiler)

Since this project features continuous runtime loops and real-time terminal inputs, it is recommended to run it on a local compiler (VS Code, Dev-C++, or GCC) rather than an online web compiler to avoid server timeouts.

```bash
# Compile the code
gcc Main.c -o vault

# Run the executable
./vault

*Created by Ayush Bhardwaj*
