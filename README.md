# yaos

The name *yaos* stands for **Y**et **A**nother **O**perating **S**ystem. This is a simple and small x86 operating system that I created to learn more about OS development.

## How to use yaos?

### Requirements

To compile and run yaos, you will need:

- A [cross-compiler](http://wiki.osdev.org/GCC_Cross-Compiler) for i686-elf
- A virtual machine to run the OS (I used [qemu](http://wiki.qemu.org/Main_Page) in this project)

### Running yaos

Simply use the Makefile provided as follows:

```bash
# Compile the OS
$ make

# Run yaos in a virtual machine (qemu)
# You may need to use the manual command according to your system:
# qemu-system-YOUR_ARCH -cdrom yaos.iso
$ make run
```

### What you should see

TODO: insert images

## Resources used for this project

- [OSDev.org](http://wiki.osdev.org/Main_Page)
- [Bran's Kernel Development Tutorial](http://www.osdever.net/bkerndev/index.php)
- [Operating System Development Series](http://www.brokenthorn.com/Resources/OSDevIndex.html)
- [How to Make a Computer Operating System](https://www.gitbook.com/book/samypesse/how-to-create-an-operating-system/details)
- [ToaruOS](http://toaruos.org/)
- *(French)* [Programmer son propre noyau](http://a.michelizza.free.fr/pmwiki.php?n=TutoOS.TutoOS)
- [Intel 80386 Reference Programmer's Manual](https://pdos.csail.mit.edu/6.828/2005/readings/i386/toc.htm)
- [osdever.net](http://www.osdever.net/tutorials/)
- [The little book about OS development](https://littleosbook.github.io/)

## License

All the source code is licensed under the [MIT license](https://opensource.org/licenses/mit-license.php).
