#include <iostream>

using namespace std;

inline void Foo()
{
    cout << "abc" << endl;
}

int main()
{
    Foo();
    return 0;
}

// no call to Foo

// 0000000000201010 B __bss_start
// 0000000000201010 b completed.7697
//                  U __cxa_atexit@@GLIBC_2.2.5
//                  w __cxa_finalize@@GLIBC_2.2.5
// 0000000000201000 D __data_start
// 0000000000201000 W data_start
// 0000000000000660 t deregister_tm_clones
// 00000000000006f0 t __do_global_dtors_aux
// 0000000000200da0 t __do_global_dtors_aux_fini_array_entry
// 0000000000201008 D __dso_handle
// 0000000000200da8 d _DYNAMIC
// 0000000000201010 D _edata
// 0000000000201018 B _end
// 0000000000000824 T _fini
// 0000000000000730 t frame_dummy
// 0000000000200d90 t __frame_dummy_init_array_entry
// 00000000000009cc r __FRAME_END__
// 0000000000200fa8 d _GLOBAL_OFFSET_TABLE_
// 000000000000078e t _GLOBAL__sub_I_main
//                  w __gmon_start__
// 0000000000000838 r __GNU_EH_FRAME_HDR
// 00000000000005d8 T _init
// 0000000000200da0 t __init_array_end
// 0000000000200d90 t __init_array_start
// 0000000000000830 R _IO_stdin_used
//                  w _ITM_deregisterTMCloneTable
//                  w _ITM_registerTMCloneTable
// 0000000000000820 T __libc_csu_fini
// 00000000000007b0 T __libc_csu_init
//                  U __libc_start_main@@GLIBC_2.2.5
// 000000000000073a T main
// 00000000000006a0 t register_tm_clones
// 0000000000000630 T _start
// 0000000000201010 D __TMC_END__
// 0000000000000745 t _Z41__static_initialization_and_destruction_0ii
//                  U _ZNSt8ios_base4InitC1Ev@@GLIBCXX_3.4
//                  U _ZNSt8ios_base4InitD1Ev@@GLIBCXX_3.4
// 0000000000000834 r _ZStL19piecewise_construct
// 0000000000201011 b _ZStL8__ioinit

// added call to Foo

// 0000000000201010 B __bss_start
// 0000000000201130 b completed.7697
//                  U __cxa_atexit@@GLIBC_2.2.5
//                  w __cxa_finalize@@GLIBC_2.2.5
// 0000000000201000 D __data_start
// 0000000000201000 W data_start
// 00000000000007e0 t deregister_tm_clones
// 0000000000000870 t __do_global_dtors_aux
// 0000000000200d88 t __do_global_dtors_aux_fini_array_entry
// 0000000000201008 D __dso_handle
// 0000000000200d90 d _DYNAMIC
// 0000000000201010 D _edata
// 0000000000201138 B _end
// 00000000000009d4 T _fini
// 00000000000008b0 t frame_dummy
// 0000000000200d78 t __frame_dummy_init_array_entry
// 0000000000000ba4 r __FRAME_END__
// 0000000000200f90 d _GLOBAL_OFFSET_TABLE_
// 0000000000000913 t _GLOBAL__sub_I_main
//                  w __gmon_start__
// 00000000000009ec r __GNU_EH_FRAME_HDR
// 0000000000000738 T _init
// 0000000000200d88 t __init_array_end
// 0000000000200d78 t __init_array_start
// 00000000000009e0 R _IO_stdin_used
//                  w _ITM_deregisterTMCloneTable
//                  w _ITM_registerTMCloneTable
// 00000000000009d0 T __libc_csu_fini
// 0000000000000960 T __libc_csu_init
//                  U __libc_start_main@@GLIBC_2.2.5
// 00000000000008ba T main
// 0000000000000820 t register_tm_clones
// 00000000000007b0 T _start
// 0000000000201010 D __TMC_END__
// 0000000000000928 W _Z3Foov
// 00000000000008ca t _Z41__static_initialization_and_destruction_0ii
//                  U _ZNSolsEPFRSoS_E@@GLIBCXX_3.4
//                  U _ZNSt8ios_base4InitC1Ev@@GLIBCXX_3.4
//                  U _ZNSt8ios_base4InitD1Ev@@GLIBCXX_3.4
// 0000000000201020 B _ZSt4cout@@GLIBCXX_3.4
//                  U _ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@@GLIBCXX_3.4
// 00000000000009e4 r _ZStL19piecewise_construct
// 0000000000201131 b _ZStL8__ioinit
//                  U _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@@GLIBCXX_3.4

// compile with -O

// 0000000000201010 B __bss_start
// 0000000000201130 b completed.7697
//                  U __cxa_atexit@@GLIBC_2.2.5
//                  w __cxa_finalize@@GLIBC_2.2.5
// 0000000000201000 D __data_start
// 0000000000201000 W data_start
// 00000000000008d0 t deregister_tm_clones
// 0000000000000960 t __do_global_dtors_aux
// 0000000000200d78 t __do_global_dtors_aux_fini_array_entry
// 0000000000201008 D __dso_handle
// 0000000000200d80 d _DYNAMIC
// 0000000000201010 D _edata
// 0000000000201138 B _end
// 0000000000000ad4 T _fini
// 00000000000009a0 t frame_dummy
// 0000000000200d68 t __frame_dummy_init_array_entry
// 0000000000000c4c r __FRAME_END__
// 0000000000200f80 d _GLOBAL_OFFSET_TABLE_
// 0000000000000a27 t _GLOBAL__sub_I_main
//                  w __gmon_start__
// 0000000000000ae8 r __GNU_EH_FRAME_HDR
// 00000000000007f8 T _init
// 0000000000200d78 t __init_array_end
// 0000000000200d68 t __init_array_start
// 0000000000000ae0 R _IO_stdin_used
//                  w _ITM_deregisterTMCloneTable
//                  w _ITM_registerTMCloneTable
// 0000000000000ad0 T __libc_csu_fini
// 0000000000000a60 T __libc_csu_init
//                  U __libc_start_main@@GLIBC_2.2.5
// 00000000000009aa T main
// 0000000000000910 t register_tm_clones
// 00000000000008a0 T _start
// 0000000000201010 D __TMC_END__
//                  U _ZNKSt5ctypeIcE13_M_widen_initEv@@GLIBCXX_3.4.11
//                  U _ZNSo3putEc@@GLIBCXX_3.4
//                  U _ZNSo5flushEv@@GLIBCXX_3.4
//                  U _ZNSt8ios_base4InitC1Ev@@GLIBCXX_3.4
//                  U _ZNSt8ios_base4InitD1Ev@@GLIBCXX_3.4
//                  U _ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@@GLIBCXX_3.4.9
//                  U _ZSt16__throw_bad_castv@@GLIBCXX_3.4
// 0000000000201020 B _ZSt4cout@@GLIBCXX_3.4
// 0000000000201131 b _ZStL8__ioinit