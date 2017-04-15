# yaos

The name *yaos* stands for **Y**et **A**nother **O**perating **S**ystem. This is my first attempt at making a simple and small x86 operating system to learn more about OS development.

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
- [Incitatus-OS](https://github.com/ersenal/Incitatus-OS)
- *(French)* [Programmer son propre noyau](http://a.michelizza.free.fr/pmwiki.php?n=TutoOS.TutoOS)
- [Intel 80386 Reference Programmer's Manual](https://pdos.csail.mit.edu/6.828/2005/readings/i386/toc.htm)
- [osdever.net](http://www.osdever.net/tutorials/)
- [The little book about OS development](https://littleosbook.github.io/)
- [/r/osdev/](https://www.reddit.com/r/osdev/)
- [basekernel](https://github.com/dthain/basekernel)
- [os5](https://github.com/thomasloven/os5)
- [axle](https://github.com/codyd51/axle)

## Lessons learned

Since this is my first attempt at making an operating system, I learned a lot about OS development. But, I also made a tons of mistakes, and because I am planning on creating another OS in the future, here are some tips for my future self:

   - **Plan ahead**: since I had no idea of what I was going to implement and how, I pretty much had no design for my OS, and I thought I didn't really need one because I wasn't aiming for a big operating system after all. But, I was totally wrong. Planning the design of the OS and the implementation of its components is a necessity, otherwise you will have a hard time building it because of huge design flaws. I often had to rewrite parts of the kernel, but at a point, it would need to be rewritten from scratch because of this lack of planning.
   - **Code everything by yourself**: GRUB is great, but I would have learned even more by doing a small bootloader by myself, and I would have been much more in control of my OS. Also, don't follow specific tutorials too much, since almost all of them are either outdated, incomplete, or simply wrong, and sticking too much to one tutorial's design is again a mistake. Read as much documentation and information on the topic as possible, plan the implementation, and then code it your way.
   - **Take time for testing**: each component should be heavily tested/reviewed before moving on to another one, and you should know the limits and the possible improvements you can make on components.

## License

All the source code is licensed under the [MIT license](https://opensource.org/licenses/mit-license.php).
