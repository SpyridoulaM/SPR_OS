# SPR_OS

**Overview**  
SPR_OS is a project where I'm teaching myself the basics of operating system development. It's a bit of a **Frankenstein OS**—pieced together from various online tutorials and resources. Below are some of the key references that helped me along the way:

### Resources
- **[OSDev Wiki: Expanded Main Page](https://wiki.osdev.org/Expanded_Main_Page)**
- **[OSDever Tutorials](http://www.osdever.net/tutorials/)**

- **YouTube Playlists**:
  - **[x86 Operating System Programming](https://youtube.com/playlist?list=PL2EF13wm-hWAglI8rRbdsCPq_wRpYvQQy)**
  - **[Creating a Kernel from Scratch](https://youtube.com/playlist?list=PLFjM7v6KGMpiH2G-kT781ByCNC_0pKpPN)**
  - **[OS Development Series](https://youtube.com/playlist?list=PLm3B56ql_akNcvH8vvJRYOc7TbYhRs19M)**

---

## Requirements

To build **SPR_OS**, you'll need:

- An **x86 cross-compiler** (you can follow [this guide](https://www.youtube.com/watch?v=EpFUzjYehxs) to set it up)
- **NASM** (assembler)
- **QEMU** (emulator)

Make sure the `/i686-elf/bin` directory is in your `PATH`.

---

## Running SPR_OS

To run the `SPR_OS.iso`, you'll need **QEMU**. Then, run the following command:

```bash
qemu-system-i386 -cdrom SPR_OS.iso
