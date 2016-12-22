# Kernel

Here are a few resources that helped me create the kernel.

## Design

### Boot

- [GRUB](https://www.gnu.org/software/grub/) (bootloader)
- [OSDev.org - Bare Bones](http://wiki.osdev.org/Bare_Bones)
- [OSDev.org - Meaty Skeleton](http://wiki.osdev.org/Meaty_Skeleton)

### Memory

- GDT (Global Descriptor Table)

   - [OSDev.org - Global Descriptor Table](http://wiki.osdev.org/Global_Descriptor_Table)
   - [OSDev.org - GDT Tutorial](http://wiki.osdev.org/GDT_Tutorial)
   - [Bran's Kernel Development - The GDT](http://www.osdever.net/bkerndev/Docs/gdt.htm)

- Paging

   - [OSDev.org - Memory Management](http://wiki.osdev.org/Memory_Management)
   - [OSDev.org - Paging](http://wiki.osdev.org/Paging)
   - [x86 Paging Tutorial](http://www.cirosantilli.com/x86-paging/)
   - *(French)* [Gérer la mémoire - un noyau qui implémente la pagination](http://a.michelizza.free.fr/pmwiki.php?n=TutoOS.Mm)
   - [How to make an OS - Theory: physical and virtual memory](https://samypesse.gitbooks.io/how-to-create-an-operating-system/content/Chapter-8/)
   - [OSDev.org - Setting Up Paging](http://wiki.osdev.org/Setting_Up_Paging)
   - [Little OS Book - Paging](https://littleosbook.github.io/#paging)

- Physical memory

   - [Operating Systems Development - Physical Memory](http://www.brokenthorn.com/Resources/OSDev17.html)
   - [osdever.net - Memory Management 1](http://www.osdever.net/tutorials/view/memory-management-1)
   - [OSDev.org - Detecting Memory](http://wiki.osdev.org/Detecting_Memory_(x86))

- Virtual memory

   - [Operating Systems Development - Virtual Memory](http://www.brokenthorn.com/Resources/OSDev18.html)
   - [osdever.net - Memory Management 2](http://www.osdever.net/tutorials/view/memory-management-2)
   - [Mapping With A Recursive Page Directory](http://www.rohitab.com/discuss/topic/31139-tutorial-paging-memory-mapping-with-a-recursive-page-directory/)

- Memory allocator

   - [A Memory Allocator - Doug Lea](http://g.oswego.edu/dl/html/malloc.html)

### Interrupts

- [OSDev.org - Interrupts](http://wiki.osdev.org/Interrupts)
- [OSDev.org - I Can't Get Interrupts Working](http://wiki.osdev.org/I_Can't_Get_Interrupts_Working)

- IDT (Interrupt Descriptor Table)

   - [Bran's Kernel Development - The IDT](http://www.osdever.net/bkerndev/Docs/idt.htm)
   - [OSDev.org - Interrupt Descriptor Table](http://wiki.osdev.org/Interrupt_Descriptor_Table)

- ISR (Interrupt Service Routine)

   - [Bran's Kernel Development - Interrupt Service Routines](http://www.osdever.net/bkerndev/Docs/isrs.htm)
   - [OSDev.org - Interrupt Service Routines](http://wiki.osdev.org/Interrupt_Service_Routines)

- IRQ (Interrupt Request)

   - [Bran's Kernel Development - IRQs and PICs](http://www.osdever.net/bkerndev/Docs/irqs.htm)
   - [OSDev.org - PIC](http://wiki.osdev.org/PIC)

### File system

- [OSDev.org - File Systems](http://wiki.osdev.org/File_Systems)
- [OSDev.org - Initrd](http://wiki.osdev.org/Initrd)
- [OSDev.org - Tar](http://wiki.osdev.org/Tar)
- [GNU - Basic Tar Format](https://www.gnu.org/software/tar/manual/html_node/Standard.html)
- [OSDev.org - VFS](http://wiki.osdev.org/VFS)
- [James Molloy - The VFS and the initrd](http://knusbaum.inlisp.org/jamesmolloy/tutorial_html/8.-The%20VFS%20and%20the%20initrd.html)

### System Clock

- [Bran's Kernel Development - The PIT: A System Clock](http://www.osdever.net/bkerndev/Docs/pit.htm)
- [OSDev.org - Programmable Interval Timer](http://wiki.osdev.org/PIT)

### Keyboard

- [Bran's Kernel Development - The Keyboard](http://www.osdever.net/bkerndev/Docs/keyboard.htm)
- [OSDev.org - Keyboard](http://wiki.osdev.org/Keyboard)
- [OSDev.org - "8042" PS/2 Controller](http://wiki.osdev.org/%228042%22_PS/2_Controller)
- *(French)* [Gérer les interruptions du clavier](http://a.michelizza.free.fr/pmwiki.php?n=TutoOS.Kbd)

### TTY

- [OSDev.org - Meaty Skeleton](http://wiki.osdev.org/Meaty_Skeleton)
- [OSDev.org - Text Mode Cursor](http://wiki.osdev.org/Text_Mode_Cursor)

### Miscellaneous

- [OSDev.org - Inline Assembly/Examples](http://wiki.osdev.org/Inline_Assembly/Examples)
- [OSDev.org - Kernel Debugging](http://wiki.osdev.org/How_Do_I_Use_A_Debugger_With_My_OS)

## License

All the source code is licensed under the [MIT license](https://opensource.org/licenses/mit-license.php).
