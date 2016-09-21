# Libc

## Design

This is my own implementation of the standard C library, but separated in two different versions:

- **libc**: The *hosted* version, which is used for user-space programming.
- **libk**: The *freestanding* version, which is used for kernel programming.

I use the special macro `__is_libk` in the C code to distinguish between the two versions. This makes the code less repetitive and more compact.

## Resources

- [OSDev.org - C Library](http://wiki.osdev.org/C_Library)
- [OSDev.org - Creating a C Library](http://wiki.osdev.org/Creating_a_C_Library)
- [OSDev.org - Meaty Skeleton](http://wiki.osdev.org/Meaty_Skeleton)

## License

All the source code is licensed under the [MIT license](https://opensource.org/licenses/mit-license.php).
