#include <stdio.h>

struct X
{
    explicit X();

    explicit X(int a_, int b_);

    ~X();

    X(const X& other_);

    X& operator=(const X& other_);

    int m_a;
    const int m_b;
};

X::X()
    : m_a(3), m_b(4)
{
    printf("Default Ctor: %p, %d, %d\n", (void*)this, m_a, m_b);
    m_a = 9;
    // m_b = 11;
}

X::X(int a_, int b_)
    : m_a(a_), m_b(b_)
{
    printf("Ctor(int,int): %p, %d, %d\n", (void*)this, m_a, m_b);
}

X::X(const X& other_)
    : m_a(other_.m_a), m_b(other_.m_b)
{
    printf("Copy Ctor: %p, %d, %d\n", (void*)this, m_a, m_b);
}

X& X::operator=(const X& other_)
{
    m_a = other_.m_a;
    //m_b = other_.m_b;

    printf("Copy Assignment: %p, %d, %d\n", (void*)this, m_a, m_b);

    return *this;
}

X::~X()
{
    printf("Dtor: %p, %d, %d\n", (void*)this, m_a, m_b);
}

int main()
{
    X x1;
    X x2(7,1);
    X x3(9, 10);
    X x4(x1);

    x1 = x3;

    return 0;
}

/*
0000000000202018 B __bss_start
0000000000202018 b completed.7697
                 w __cxa_finalize@@GLIBC_2.2.5
0000000000202000 D __data_start
0000000000202000 W data_start
00000000000006e0 t deregister_tm_clones
0000000000000770 t __do_global_dtors_aux
0000000000201d90 t __do_global_dtors_aux_fini_array_entry
0000000000202008 D __dso_handle
0000000000202010 V DW.ref.__gxx_personality_v0
0000000000201d98 d _DYNAMIC
0000000000202018 D _edata
0000000000202020 B _end
0000000000000ac4 T _fini
00000000000007b0 t frame_dummy
0000000000201d88 t __frame_dummy_init_array_entry
0000000000000d84 r __FRAME_END__
0000000000201fa8 d _GLOBAL_OFFSET_TABLE_
                 w __gmon_start__
0000000000000b50 r __GNU_EH_FRAME_HDR
                 U __gxx_personality_v0@@CXXABI_1.3
0000000000000640 T _init
0000000000201d90 t __init_array_end
0000000000201d88 t __init_array_start
0000000000000ad0 R _IO_stdin_used
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
0000000000000ac0 T __libc_csu_fini
0000000000000a50 T __libc_csu_init
                 U __libc_start_main@@GLIBC_2.2.5
000000000000092a T main
                 U printf@@GLIBC_2.2.5
0000000000000720 t register_tm_clones
                 U __stack_chk_fail@@GLIBC_2.4
00000000000006b0 T _start
0000000000202018 D __TMC_END__
                 U _Unwind_Resume@@GCC_3.0
00000000000008ae T _ZN1XaSERKS_
000000000000080e T _ZN1XC1Eii
000000000000085c T _ZN1XC1ERKS_
00000000000007ba T _ZN1XC1Ev
000000000000080e T _ZN1XC2Eii
000000000000085c T _ZN1XC2ERKS_
00000000000007ba T _ZN1XC2Ev
00000000000008f6 T _ZN1XD1Ev
00000000000008f6 T _ZN1XD2Ev
*/

/*
00000000000008ae T X::operator=(X const&)
000000000000080e T X::X(int, int)
000000000000085c T X::X(X const&)
00000000000007ba T X::X()
000000000000080e T X::X(int, int)
000000000000085c T X::X(X const&)
00000000000007ba T X::X()
00000000000008f6 T X::~X()
00000000000008f6 T X::~X()
*/