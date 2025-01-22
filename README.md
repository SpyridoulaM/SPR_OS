# SPR_OS

**Overview**  
SPR_OS is a self-constructed operating system designed to teach the fundamentals of OS development. It is built using various tutorials and resources, forming a **Frankenstein OS** by combining different learning materials.

### Key Resources:
- **[OSDev Wiki: Expanded Main Page](https://wiki.osdev.org/Expanded_Main_Page)**
- **[OSDever Tutorials](http://www.osdever.net/tutorials/)**

- **YouTube Playlists**:
  - **[x86 Operating System Programming](https://youtube.com/playlist?list=PL2EF13wm-hWAglI8rRbdsCPq_wRpYvQQy)**
  - **[Creating a Kernel from Scratch](https://youtube.com/playlist?list=PLFjM7v6KGMpiH2G-kT781ByCNC_0pKpPN)**
  - **[OS Development Series](https://youtube.com/playlist?list=PLm3B56ql_akNcvH8vvJRYOc7TbYhRs19M)**

---

## Running SPR_OS

To run `SPR_OS.iso`, you'll need **QEMU**. You can launch the OS using the following command:

```bash
qemu-system-i386 -cdrom SPR_OS.iso
```
## Building SPR_OS

To build **SPR_OS**, you'll need the following tools:

- **x86 cross-compiler** (you can follow [this guide](https://www.youtube.com/watch?v=EpFUzjYehxs) to set it up)
- **NASM** (assembler)
- **QEMU** (emulator)

Make sure that the `/i686-elf/bin` directory is included in your `PATH`.

Once you have the required tools set up, you can build the OS and run it immediately with the following command:

```bash
make rc
```
