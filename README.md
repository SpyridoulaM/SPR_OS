# SPR_OS

**Description**  
SPR_OS is a personal project where I'm learning how operating systems work in my free time. This project is a bit of a **Frankenstein OS** as most of the code has been pulled from various online resources. The goal is to understand the basics of OS development while building something functional. Below are some of the main resources I've used.

### Resources
- **[OSDev Wiki: Expanded Main Page](https://wiki.osdev.org/Expanded_Main_Page)**
- **[OSDever Tutorials](http://www.osdever.net/tutorials/)**

- **YouTube Tutorials and Series**:
  - **[x86 Operating System Programming](https://youtube.com/playlist?list=PL2EF13wm-hWAglI8rRbdsCPq_wRpYvQQy&si=eB_u-xFsZNFLyHfk)**
  - **[Creating a Kernel from Scratch](https://youtube.com/playlist?list=PLFjM7v6KGMpiH2G-kT781ByCNC_0pKpPN&si=jyIQcacAIsRcEEDQ)**
  - **[OS Development Series](https://youtube.com/playlist?list=PLm3B56ql_akNcvH8vvJRYOc7TbYhRs19M&si=oSKIqGKkr7AHFJzV)**

---

## Requirements

To compile **SPR_OS**, you'll need to set up an **x86 cross-compiler** and ensure that the `/i686-elf/bin` directory is in your `PATH`. The following guide helped me get started: **[Setting up an x86 Cross Compiler](https://www.youtube.com/watch?v=EpFUzjYehxs)**.

In addition, you'll need to install:

- **NASM** (Assembler)
- **QEMU** (Emulator)

---

## Running SPR_OS

If you just want to run the `SPR_OS.iso` file, you'll need **NASM** installed. You can then execute the following command:

```bash
qemu-system-i386 -cdrom SPR_OS.iso
