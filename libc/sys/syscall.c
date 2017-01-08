int syscall(int function, int param1, int param2, int param3)
{
   int ret;
   asm volatile("int $0x80" : "=a" (ret) : "0" (function),
                              "b" (param1), "c" (param2), "d" (param3));
   return ret;
}
