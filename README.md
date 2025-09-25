# 🌌 novanix OS/kernel


**Nox OS (Novanix/alinix kernel)** is a simple operating system built from scratch, featuring a modular kernel with a command-line interface. Designed for learning, experimentation, and expansion, Nox is lightweight, fast, and a great starting point for systems developers and OS enthusiasts.

---

## ✨ Features

- ✅ Custom command-line shell (NoxCLI)
- ✅ Lightweight monolithic kernel
- ✅ Built-in memory management
- ✅ Basic I/O driver system
- ✅ VGA text mode output
- ✅ System timer and clock display
- ✅ Support for custom system calls
- ✅ Modular library integration (`libcx`)
- ✅ Compile and run with QEMU

---


## Note
Some of the codes of this project are not used and are about to be removed. Those parts were copied but are not used, mainly because of dependency. 


## Videos 

<video controls src="etc/vid/REC-20250925184217 copy.mp4" title="Title"></video>

## 📸 Screenshots
![alt text](<etc/photos/Screenshot 2025-07-05 at 10.11.10 PM.png>)
![alt text](<etc/Screenshot 2025-07-14 at 2.42.55 PM.png>)
## 🚀 Installation

Clone the repository and install `libcx`, which contains Nox’s standard library:

```bash
cd libcx
make install
