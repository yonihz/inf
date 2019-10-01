#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define UNUSED(x) (void)(x)

/* static function */
static void StaticFunc1(void);
static void StaticFunc2(void);
static void StaticFunc3(void);

/* extern function */
extern void ExternFunc(void);

/* non-const static global var */
static int static_global_var = 5;

/* const static global var */
static int const_static_global_var = 20;

/* non-const global var */
int global_var = 8;

/* const global var */
int const_global_var = 10;

/* env var */
/* command line arg */
int main(int argc, char *argv[], char *envp[])
{
    char* argv_var = NULL;
    char* envp_var = NULL;
    
    /* string literal */
    char* str_literal = "string";

    /* non-const local var */
    int local_var = 1;

    /* const local var */
    int const_local_var = 1;

    /* non-const static local var */
    static int static_local_var = 2;

    /* const static local var */
    static const int const_static_local_var = 15;

    /* heap var */
    int* heap_var1 = NULL;
    int* heap_var2 = NULL;
    int* heap_var3 = NULL;
    heap_var1 = malloc(sizeof(char));
    heap_var2 = malloc(sizeof(char));
    heap_var3 = malloc(sizeof(char));

    argv_var = argv[1];
    envp_var = envp[1];

    printf("argv_var %p\n", (void*)argv_var);
    printf("envp_var %p\n", (void*)envp_var);
    printf("str_literal %p\n", (void*)str_literal);
    printf("local_var %p\n", (void*)&local_var);
    printf("const_local_var %p\n", (void*)&const_local_var);
    printf("static_local_var %p\n", (void*)&static_local_var);
    printf("const_static_local_var %p\n", (void*)&const_static_local_var);
    printf("static_global_var %p\n", (void*)&static_global_var);
    printf("const_static_global_var %p\n", (void*)&const_static_global_var);
    printf("global_var %p\n", (void*)&global_var);
    printf("const_global_var %p\n", (void*)&const_global_var);
    printf("\n\nheap_var1 %p\n", (void*)heap_var1);
    printf("heap_var2 %p\n", (void*)heap_var2);
    printf("heap_var3 %p\n", (void*)heap_var3);

    StaticFunc1();

    UNUSED(argc);

    return (0);
}

static void StaticFunc1(void)
{
    int a = 1;
    printf("stack_var1 %p\n", (void*)&a);
    StaticFunc2();
    return;
}

static void StaticFunc2(void)
{
    int a = 1;
    printf("stack_var2 %p\n", (void*)&a);
    StaticFunc3();
    return;
}

static void StaticFunc3(void)
{
    int a = 1;
    printf("stack_var3 %p\n", (void*)&a);
    return;
}

/*
info proc mapping

          Start Addr           End Addr       Size     Offset objfile
            0x400000           0x401000     0x1000        0x0 /home/yoni/yoni-horovitz/quizzes/MemoryMapping/a.out
            0x600000           0x601000     0x1000        0x0 /home/yoni/yoni-horovitz/quizzes/MemoryMapping/a.out
            0x601000           0x602000     0x1000     0x1000 /home/yoni/yoni-horovitz/quizzes/MemoryMapping/a.out
            0x602000           0x623000    0x21000        0x0 [heap]
      0x7ffff7a0d000     0x7ffff7bcd000   0x1c0000        0x0 /lib/x86_64-linux-gnu/libc-2.23.so
      0x7ffff7bcd000     0x7ffff7dcd000   0x200000   0x1c0000 /lib/x86_64-linux-gnu/libc-2.23.so
      0x7ffff7dcd000     0x7ffff7dd1000     0x4000   0x1c0000 /lib/x86_64-linux-gnu/libc-2.23.so
      0x7ffff7dd1000     0x7ffff7dd3000     0x2000   0x1c4000 /lib/x86_64-linux-gnu/libc-2.23.so
      0x7ffff7dd3000     0x7ffff7dd7000     0x4000        0x0
      0x7ffff7dd7000     0x7ffff7dfd000    0x26000        0x0 /lib/x86_64-linux-gnu/ld-2.23.so
      0x7ffff7fdb000     0x7ffff7fde000     0x3000        0x0
      0x7ffff7ff7000     0x7ffff7ffa000     0x3000        0x0 [vvar]
      0x7ffff7ffa000     0x7ffff7ffc000     0x2000        0x0 [vdso]
      0x7ffff7ffc000     0x7ffff7ffd000     0x1000    0x25000 /lib/x86_64-linux-gnu/ld-2.23.so
      0x7ffff7ffd000     0x7ffff7ffe000     0x1000    0x26000 /lib/x86_64-linux-gnu/ld-2.23.so
      0x7ffff7ffe000     0x7ffff7fff000     0x1000        0x0
      0x7ffffffde000     0x7ffffffff000    0x21000        0x0 [stack]
  0xffffffffff600000 0xffffffffff601000     0x1000        0x0 [vsyscall]

info files

file type elf64-x86-64.
        Entry point: 0x4004e0
        0x0000000000400238 - 0x0000000000400254 is .interp
        0x0000000000400254 - 0x0000000000400274 is .note.ABI-tag
        0x0000000000400274 - 0x0000000000400298 is .note.gnu.build-id
        0x0000000000400298 - 0x00000000004002b4 is .gnu.hash
        0x00000000004002b8 - 0x0000000000400348 is .dynsym
        0x0000000000400348 - 0x00000000004003a9 is .dynstr
        0x00000000004003aa - 0x00000000004003b6 is .gnu.version
        0x00000000004003b8 - 0x00000000004003e8 is .gnu.version_r
        0x00000000004003e8 - 0x0000000000400400 is .rela.dyn
        0x0000000000400400 - 0x0000000000400460 is .rela.plt
        0x0000000000400460 - 0x000000000040047a is .init
        0x0000000000400480 - 0x00000000004004d0 is .plt
        0x00000000004004d0 - 0x00000000004004d8 is .plt.got
        0x00000000004004e0 - 0x0000000000400922 is .text
        0x0000000000400924 - 0x000000000040092d is .fini
        0x0000000000400930 - 0x0000000000400a6c is .rodata
        0x0000000000400a6c - 0x0000000000400ab8 is .eh_frame_hdr
        0x0000000000400ab8 - 0x0000000000400c0c is .eh_frame
        0x0000000000600e10 - 0x0000000000600e18 is .init_array
        0x0000000000600e18 - 0x0000000000600e20 is .fini_array
        0x0000000000600e20 - 0x0000000000600e28 is .jcr
        0x0000000000600e28 - 0x0000000000600ff8 is .dynamic
        0x0000000000600ff8 - 0x0000000000601000 is .got
        0x0000000000601000 - 0x0000000000601038 is .got.plt
        0x0000000000601038 - 0x000000000060105c is .data
        0x000000000060105c - 0x0000000000601060 is .bss
        0x00007ffff7dd71c8 - 0x00007ffff7dd71ec is .note.gnu.build-id in /lib64/ld-linux-x86-64.so.2
        0x00007ffff7dd71f0 - 0x00007ffff7dd72b0 is .hash in /lib64/ld-linux-x86-64.so.2
        0x00007ffff7dd72b0 - 0x00007ffff7dd7390 is .gnu.hash in /lib64/ld-linux-x86-64.so.2
        0x00007ffff7dd7390 - 0x00007ffff7dd7648 is .dynsym in /lib64/ld-linux-x86-64.so.2
        0x00007ffff7dd7648 - 0x00007ffff7dd77ef is .dynstr in /lib64/ld-linux-x86-64.so.2
        0x00007ffff7dd77f0 - 0x00007ffff7dd782a is .gnu.version in /lib64/ld-linux-x86-64.so.2
        0x00007ffff7dd7830 - 0x00007ffff7dd78d4 is .gnu.version_d in /lib64/ld-linux-x86-64.so.2
        0x00007ffff7dd78d8 - 0x00007ffff7dd79f8 is .rela.dyn in /lib64/ld-linux-x86-64.so.2
        0x00007ffff7dd79f8 - 0x00007ffff7dd7a58 is .rela.plt in /lib64/ld-linux-x86-64.so.2
        0x00007ffff7dd7a60 - 0x00007ffff7dd7ab0 is .plt in /lib64/ld-linux-x86-64.so.2
        0x00007ffff7dd7ab0 - 0x00007ffff7dd7ab8 is .plt.got in /lib64/ld-linux-x86-64.so.2
        0x00007ffff7dd7ac0 - 0x00007ffff7df5790 is .text in /lib64/ld-linux-x86-64.so.2
        0x00007ffff7df57a0 - 0x00007ffff7df9860 is .rodata in /lib64/ld-linux-x86-64.so.2
        0x00007ffff7df9860 - 0x00007ffff7df9861 is .stapsdt.base in /lib64/ld-linux-x86-64.so.2
        0x00007ffff7df9864 - 0x00007ffff7df9ea8 is .eh_frame_hdr in /lib64/ld-linux-x86-64.so.2
        0x00007ffff7df9ea8 - 0x00007ffff7dfc390 is .eh_frame in /lib64/ld-linux-x86-64.so.2
        0x00007ffff7ffcbc0 - 0x00007ffff7ffce7c is .data.rel.ro in /lib64/ld-linux-x86-64.so.2
        0x00007ffff7ffce80 - 0x00007ffff7ffcff0 is .dynamic in /lib64/ld-linux-x86-64.so.2
        0x00007ffff7ffcff0 - 0x00007ffff7ffd000 is .got in /lib64/ld-linux-x86-64.so.2
        0x00007ffff7ffd000 - 0x00007ffff7ffd038 is .got.plt in /lib64/ld-linux-x86-64.so.2
        0x00007ffff7ffd040 - 0x00007ffff7ffdfc0 is .data in /lib64/ld-linux-x86-64.so.2
        0x00007ffff7ffdfc0 - 0x00007ffff7ffe168 is .bss in /lib64/ld-linux-x86-64.so.2
        0x00007ffff7ffa120 - 0x00007ffff7ffa160 is .hash in system-supplied DSO at 0x7ffff7ffa000
        0x00007ffff7ffa160 - 0x00007ffff7ffa1a8 is .gnu.hash in system-supplied DSO at 0x7ffff7ffa000
        0x00007ffff7ffa1a8 - 0x00007ffff7ffa2b0 is .dynsym in system-supplied DSO at 0x7ffff7ffa000
        0x00007ffff7ffa2b0 - 0x00007ffff7ffa30e is .dynstr in system-supplied DSO at 0x7ffff7ffa000
        0x00007ffff7ffa30e - 0x00007ffff7ffa324 is .gnu.version in system-supplied DSO at 0x7ffff7ffa000
        0x00007ffff7ffa328 - 0x00007ffff7ffa360 is .gnu.version_d in system-supplied DSO at 0x7ffff7ffa000
        0x00007ffff7ffa360 - 0x00007ffff7ffa470 is .dynamic in system-supplied DSO at 0x7ffff7ffa000
        0x00007ffff7ffa470 - 0x00007ffff7ffa7b0 is .rodata in system-supplied DSO at 0x7ffff7ffa000
        0x00007ffff7ffa7b0 - 0x00007ffff7ffa7ec is .note in system-supplied DSO at 0x7ffff7ffa000
        0x00007ffff7ffa7ec - 0x00007ffff7ffa828 is .eh_frame_hdr in system-supplied DSO at 0x7ffff7ffa000
        0x00007ffff7ffa828 - 0x00007ffff7ffa968 is .eh_frame in system-supplied DSO at 0x7ffff7ffa000
        0x00007ffff7ffa970 - 0x00007ffff7ffaf7a is .text in system-supplied DSO at 0x7ffff7ffa000
        0x00007ffff7ffaf7a - 0x00007ffff7ffb009 is .altinstructions in system-supplied DSO at 0x7ffff7ffa000
        0x00007ffff7ffb009 - 0x00007ffff7ffb02b is .altinstr_replacement in system-supplied DSO at 0x7ffff7ffa000
        0x00007ffff7a0d270 - 0x00007ffff7a0d294 is .note.gnu.build-id in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7a0d294 - 0x00007ffff7a0d2b4 is .note.ABI-tag in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7a0d2b8 - 0x00007ffff7a10d80 is .gnu.hash in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7a10d80 - 0x00007ffff7a1dff8 is .dynsym in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7a1dff8 - 0x00007ffff7a239d7 is .dynstr in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7a239d8 - 0x00007ffff7a24b62 is .gnu.version in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7a24b68 - 0x00007ffff7a24edc is .gnu.version_d in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7a24ee0 - 0x00007ffff7a24f10 is .gnu.version_r in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7a24f10 - 0x00007ffff7a2c680 is .rela.dyn in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7a2c680 - 0x00007ffff7a2c7b8 is .rela.plt in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7a2c7c0 - 0x00007ffff7a2c8a0 is .plt in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7a2c8a0 - 0x00007ffff7a2c8b0 is .plt.got in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7a2c8b0 - 0x00007ffff7b7fb04 is .text in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7b7fb10 - 0x00007ffff7b8202d is __libc_freeres_fn in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7b82030 - 0x00007ffff7b822f2 is __libc_thread_freeres_fn in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7b82300 - 0x00007ffff7ba3650 is .rodata in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7ba3650 - 0x00007ffff7ba3651 is .stapsdt.base in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7ba3660 - 0x00007ffff7ba367c is .interp in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7ba367c - 0x00007ffff7ba8b38 is .eh_frame_hdr in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7ba8b38 - 0x00007ffff7bc93cc is .eh_frame in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7bc93cc - 0x00007ffff7bc980d is .gcc_except_table in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7bc9810 - 0x00007ffff7bccb10 is .hash in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7dcd7c0 - 0x00007ffff7dcd7d0 is .tdata in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7dcd7d0 - 0x00007ffff7dcd838 is .tbss in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7dcd7d0 - 0x00007ffff7dcd7e0 is .init_array in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7dcd7e0 - 0x00007ffff7dcd8d8 is __libc_subfreeres in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7dcd8d8 - 0x00007ffff7dcd8e0 is __libc_atexit in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7dcd8e0 - 0x00007ffff7dcd900 is __libc_thread_subfreeres in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7dcd900 - 0x00007ffff7dd0ba0 is .data.rel.ro in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7dd0ba0 - 0x00007ffff7dd0d80 is .dynamic in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7dd0d80 - 0x00007ffff7dd0ff0 is .got in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7dd1000 - 0x00007ffff7dd1080 is .got.plt in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7dd1080 - 0x00007ffff7dd2720 is .data in /lib/x86_64-linux-gnu/libc.so.6
        0x00007ffff7dd2720 - 0x00007ffff7dd69a0 is .bss in /lib/x86_64-linux-gnu/libc.so.6

nm -a

0000000000000000 a 
000000000060105c b .bss
000000000060105c B __bss_start
0000000000000000 n .comment
000000000060105c b completed.7594
0000000000601054 D const_global_var
000000000060104c d const_static_global_var
0000000000400a68 r const_static_local_var.1883
0000000000000000 a crtstuff.c
0000000000000000 a crtstuff.c
0000000000601038 d .data
0000000000601038 D __data_start
0000000000601038 W data_start
0000000000000000 N .debug_abbrev
0000000000000000 N .debug_aranges
0000000000000000 N .debug_info
0000000000000000 N .debug_line
0000000000000000 N .debug_str
0000000000400510 t deregister_tm_clones
0000000000400590 t __do_global_dtors_aux
0000000000600e18 t __do_global_dtors_aux_fini_array_entry
0000000000601040 D __dso_handle
0000000000600e28 d .dynamic
0000000000600e28 d _DYNAMIC
0000000000400348 r .dynstr
00000000004002b8 r .dynsym
000000000060105c D _edata
0000000000400ab8 r .eh_frame
0000000000400a6c r .eh_frame_hdr
0000000000601060 B _end
0000000000400924 T _fini
0000000000400924 t .fini
0000000000600e18 t .fini_array
00000000004005b0 t frame_dummy
0000000000600e10 t __frame_dummy_init_array_entry
0000000000400c08 r __FRAME_END__
0000000000601000 d _GLOBAL_OFFSET_TABLE_
0000000000601050 D global_var
                 w __gmon_start__
0000000000400a6c r __GNU_EH_FRAME_HDR
0000000000400298 r .gnu.hash
00000000004003aa r .gnu.version
00000000004003b8 r .gnu.version_r
0000000000600ff8 d .got
0000000000601000 d .got.plt
0000000000400460 T _init
0000000000400460 t .init
0000000000600e10 t .init_array
0000000000600e18 t __init_array_end
0000000000600e10 t __init_array_start
0000000000400238 r .interp
0000000000400930 R _IO_stdin_used
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
0000000000600e20 d .jcr
0000000000600e20 d __JCR_END__
0000000000600e20 d __JCR_LIST__
                 w _Jv_RegisterClasses
0000000000400920 T __libc_csu_fini
00000000004008b0 T __libc_csu_init
                 U __libc_start_main@@GLIBC_2.2.5
00000000004005d6 T main
                 U malloc@@GLIBC_2.2.5
0000000000000000 a memmap.c
0000000000400254 r .note.ABI-tag
0000000000400274 r .note.gnu.build-id
0000000000400480 t .plt
00000000004004d0 t .plt.got
                 U printf@@GLIBC_2.2.5
0000000000400550 t register_tm_clones
00000000004003e8 r .rela.dyn
0000000000400400 r .rela.plt
0000000000400930 r .rodata
                 U __stack_chk_fail@@GLIBC_2.4
00000000004004e0 T _start
00000000004007c0 t StaticFunc1
0000000000400810 t StaticFunc2
0000000000400860 t StaticFunc3
0000000000601048 d static_global_var
0000000000601058 d static_local_var.1882
00000000004004e0 t .text
0000000000601060 D __TMC_END__

Virtual memory size: 4456448
Resident set size: 187
rlim: 18446744073709551615
Start of text: 0x400000
End of text: 0x400c0c
Start of stack: 0x7fffffffdc80

addresses are run-time

argv_var 0x7ffd26213092
envp_var 0x7ffd262130a0
str_literal 0x400934
local_var 0x7ffd26211ac0
const_local_var 0x7ffd26211ac4
static_local_var 0x601058
const_static_local_var 0x400a68
static_global_var 0x601048
const_static_global_var 0x60104c
global_var 0x601050
const_global_var 0x601054


heap_var1 0xd50010
heap_var2 0xd50030
heap_var3 0xd50050
stack_var1 0x7ffd26211a84
stack_var2 0x7ffd26211a64
stack_var3 0x7ffd26211a44
*/