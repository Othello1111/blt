# 1 "bltWindow.c"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "bltWindow.c"
# 29 "bltWindow.c"
# 1 "bltInt.h" 1
# 39 "bltInt.h"
# 1 "/tmp/t852/include/tcl.h" 1
# 141 "/tmp/t852/include/tcl.h"
# 1 "/usr/include/stdio.h" 1 3
# 28 "/usr/include/stdio.h" 3
# 1 "/usr/include/features.h" 1 3
# 296 "/usr/include/features.h" 3
# 1 "/usr/include/sys/cdefs.h" 1 3
# 297 "/usr/include/features.h" 2 3
# 319 "/usr/include/features.h" 3
# 1 "/usr/include/gnu/stubs.h" 1 3
# 320 "/usr/include/features.h" 2 3
# 29 "/usr/include/stdio.h" 2 3





# 1 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stddef.h" 1 3
# 213 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stddef.h" 3
typedef unsigned int size_t;
# 35 "/usr/include/stdio.h" 2 3

# 1 "/usr/include/bits/types.h" 1 3
# 28 "/usr/include/bits/types.h" 3
# 1 "/usr/include/bits/wordsize.h" 1 3
# 29 "/usr/include/bits/types.h" 2 3


# 1 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stddef.h" 1 3
# 32 "/usr/include/bits/types.h" 2 3


typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;




__extension__ typedef signed long long int __int64_t;
__extension__ typedef unsigned long long int __uint64_t;







__extension__ typedef long long int __quad_t;
__extension__ typedef unsigned long long int __u_quad_t;
# 129 "/usr/include/bits/types.h" 3
# 1 "/usr/include/bits/typesizes.h" 1 3
# 130 "/usr/include/bits/types.h" 2 3






__extension__ typedef unsigned long long int __dev_t;
__extension__ typedef unsigned int __uid_t;
__extension__ typedef unsigned int __gid_t;
__extension__ typedef unsigned long int __ino_t;
__extension__ typedef unsigned long long int __ino64_t;
__extension__ typedef unsigned int __mode_t;
__extension__ typedef unsigned int __nlink_t;
__extension__ typedef long int __off_t;
__extension__ typedef long long int __off64_t;
__extension__ typedef int __pid_t;
__extension__ typedef struct { int __val[2]; } __fsid_t;
__extension__ typedef long int __clock_t;
__extension__ typedef unsigned long int __rlim_t;
__extension__ typedef unsigned long long int __rlim64_t;
__extension__ typedef unsigned int __id_t;
__extension__ typedef long int __time_t;
__extension__ typedef unsigned int __useconds_t;
__extension__ typedef long int __suseconds_t;

__extension__ typedef int __daddr_t;
__extension__ typedef long int __swblk_t;
__extension__ typedef int __key_t;


__extension__ typedef int __clockid_t;


__extension__ typedef int __timer_t;


__extension__ typedef long int __blksize_t;




__extension__ typedef long int __blkcnt_t;
__extension__ typedef long long int __blkcnt64_t;


__extension__ typedef unsigned long int __fsblkcnt_t;
__extension__ typedef unsigned long long int __fsblkcnt64_t;


__extension__ typedef unsigned long int __fsfilcnt_t;
__extension__ typedef unsigned long long int __fsfilcnt64_t;

__extension__ typedef int __ssize_t;



typedef __off64_t __loff_t;
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;


__extension__ typedef int __intptr_t;


__extension__ typedef unsigned int __socklen_t;
# 37 "/usr/include/stdio.h" 2 3









typedef struct _IO_FILE FILE;





# 62 "/usr/include/stdio.h" 3
typedef struct _IO_FILE __FILE;
# 72 "/usr/include/stdio.h" 3
# 1 "/usr/include/libio.h" 1 3
# 32 "/usr/include/libio.h" 3
# 1 "/usr/include/_G_config.h" 1 3
# 14 "/usr/include/_G_config.h" 3
# 1 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stddef.h" 1 3
# 325 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stddef.h" 3
typedef long int wchar_t;
# 354 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stddef.h" 3
typedef unsigned int wint_t;
# 15 "/usr/include/_G_config.h" 2 3
# 24 "/usr/include/_G_config.h" 3
# 1 "/usr/include/wchar.h" 1 3
# 48 "/usr/include/wchar.h" 3
# 1 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stddef.h" 1 3
# 49 "/usr/include/wchar.h" 2 3

# 1 "/usr/include/bits/wchar.h" 1 3
# 51 "/usr/include/wchar.h" 2 3
# 76 "/usr/include/wchar.h" 3
typedef struct
{
  int __count;
  union
  {
    wint_t __wch;
    char __wchb[4];
  } __value;
} __mbstate_t;
# 25 "/usr/include/_G_config.h" 2 3

typedef struct
{
  __off_t __pos;
  __mbstate_t __state;
} _G_fpos_t;
typedef struct
{
  __off64_t __pos;
  __mbstate_t __state;
} _G_fpos64_t;
# 44 "/usr/include/_G_config.h" 3
# 1 "/usr/include/gconv.h" 1 3
# 28 "/usr/include/gconv.h" 3
# 1 "/usr/include/wchar.h" 1 3
# 48 "/usr/include/wchar.h" 3
# 1 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stddef.h" 1 3
# 49 "/usr/include/wchar.h" 2 3
# 29 "/usr/include/gconv.h" 2 3


# 1 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stddef.h" 1 3
# 32 "/usr/include/gconv.h" 2 3





enum
{
  __GCONV_OK = 0,
  __GCONV_NOCONV,
  __GCONV_NODB,
  __GCONV_NOMEM,

  __GCONV_EMPTY_INPUT,
  __GCONV_FULL_OUTPUT,
  __GCONV_ILLEGAL_INPUT,
  __GCONV_INCOMPLETE_INPUT,

  __GCONV_ILLEGAL_DESCRIPTOR,
  __GCONV_INTERNAL_ERROR
};



enum
{
  __GCONV_IS_LAST = 0x0001,
  __GCONV_IGNORE_ERRORS = 0x0002
};



struct __gconv_step;
struct __gconv_step_data;
struct __gconv_loaded_object;
struct __gconv_trans_data;



typedef int (*__gconv_fct) (struct __gconv_step *, struct __gconv_step_data *,
                            __const unsigned char **, __const unsigned char *,
                            unsigned char **, size_t *, int, int);


typedef wint_t (*__gconv_btowc_fct) (struct __gconv_step *, unsigned char);


typedef int (*__gconv_init_fct) (struct __gconv_step *);
typedef void (*__gconv_end_fct) (struct __gconv_step *);



typedef int (*__gconv_trans_fct) (struct __gconv_step *,
                                  struct __gconv_step_data *, void *,
                                  __const unsigned char *,
                                  __const unsigned char **,
                                  __const unsigned char *, unsigned char **,
                                  size_t *);


typedef int (*__gconv_trans_context_fct) (void *, __const unsigned char *,
                                          __const unsigned char *,
                                          unsigned char *, unsigned char *);


typedef int (*__gconv_trans_query_fct) (__const char *, __const char ***,
                                        size_t *);


typedef int (*__gconv_trans_init_fct) (void **, const char *);
typedef void (*__gconv_trans_end_fct) (void *);

struct __gconv_trans_data
{

  __gconv_trans_fct __trans_fct;
  __gconv_trans_context_fct __trans_context_fct;
  __gconv_trans_end_fct __trans_end_fct;
  void *__data;
  struct __gconv_trans_data *__next;
};



struct __gconv_step
{
  struct __gconv_loaded_object *__shlib_handle;
  __const char *__modname;

  int __counter;

  char *__from_name;
  char *__to_name;

  __gconv_fct __fct;
  __gconv_btowc_fct __btowc_fct;
  __gconv_init_fct __init_fct;
  __gconv_end_fct __end_fct;



  int __min_needed_from;
  int __max_needed_from;
  int __min_needed_to;
  int __max_needed_to;


  int __stateful;

  void *__data;
};



struct __gconv_step_data
{
  unsigned char *__outbuf;
  unsigned char *__outbufend;



  int __flags;



  int __invocation_counter;



  int __internal_use;

  __mbstate_t *__statep;
  __mbstate_t __state;



  struct __gconv_trans_data *__trans;
};



typedef struct __gconv_info
{
  size_t __nsteps;
  struct __gconv_step *__steps;
  __extension__ struct __gconv_step_data __data [];
} *__gconv_t;
# 45 "/usr/include/_G_config.h" 2 3
typedef union
{
  struct __gconv_info __cd;
  struct
  {
    struct __gconv_info __cd;
    struct __gconv_step_data __data;
  } __combined;
} _G_iconv_t;

typedef int _G_int16_t __attribute__ ((__mode__ (__HI__)));
typedef int _G_int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int _G_uint16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int _G_uint32_t __attribute__ ((__mode__ (__SI__)));
# 33 "/usr/include/libio.h" 2 3
# 53 "/usr/include/libio.h" 3
# 1 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stdarg.h" 1 3
# 43 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stdarg.h" 3
typedef __builtin_va_list __gnuc_va_list;
# 54 "/usr/include/libio.h" 2 3
# 163 "/usr/include/libio.h" 3
struct _IO_jump_t; struct _IO_FILE;
# 173 "/usr/include/libio.h" 3
typedef void _IO_lock_t;





struct _IO_marker {
  struct _IO_marker *_next;
  struct _IO_FILE *_sbuf;



  int _pos;
# 196 "/usr/include/libio.h" 3
};


enum __codecvt_result
{
  __codecvt_ok,
  __codecvt_partial,
  __codecvt_error,
  __codecvt_noconv
};
# 264 "/usr/include/libio.h" 3
struct _IO_FILE {
  int _flags;




  char* _IO_read_ptr;
  char* _IO_read_end;
  char* _IO_read_base;
  char* _IO_write_base;
  char* _IO_write_ptr;
  char* _IO_write_end;
  char* _IO_buf_base;
  char* _IO_buf_end;

  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;



  int _flags2;

  __off_t _old_offset;



  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];



  _IO_lock_t *_lock;
# 312 "/usr/include/libio.h" 3
  __off64_t _offset;





  void *__pad1;
  void *__pad2;

  int _mode;

  char _unused2[15 * sizeof (int) - 2 * sizeof (void *)];

};


typedef struct _IO_FILE _IO_FILE;


struct _IO_FILE_plus;

extern struct _IO_FILE_plus _IO_2_1_stdin_;
extern struct _IO_FILE_plus _IO_2_1_stdout_;
extern struct _IO_FILE_plus _IO_2_1_stderr_;
# 351 "/usr/include/libio.h" 3
typedef __ssize_t __io_read_fn (void *__cookie, char *__buf, size_t __nbytes);







typedef __ssize_t __io_write_fn (void *__cookie, __const char *__buf,
                                 size_t __n);







typedef int __io_seek_fn (void *__cookie, __off64_t *__pos, int __w);


typedef int __io_close_fn (void *__cookie);
# 403 "/usr/include/libio.h" 3
extern int __underflow (_IO_FILE *) ;
extern int __uflow (_IO_FILE *) ;
extern int __overflow (_IO_FILE *, int) ;
extern wint_t __wunderflow (_IO_FILE *) ;
extern wint_t __wuflow (_IO_FILE *) ;
extern wint_t __woverflow (_IO_FILE *, wint_t) ;
# 433 "/usr/include/libio.h" 3
extern int _IO_getc (_IO_FILE *__fp) ;
extern int _IO_putc (int __c, _IO_FILE *__fp) ;
extern int _IO_feof (_IO_FILE *__fp) ;
extern int _IO_ferror (_IO_FILE *__fp) ;

extern int _IO_peekc_locked (_IO_FILE *__fp) ;





extern void _IO_flockfile (_IO_FILE *) ;
extern void _IO_funlockfile (_IO_FILE *) ;
extern int _IO_ftrylockfile (_IO_FILE *) ;
# 463 "/usr/include/libio.h" 3
extern int _IO_vfscanf (_IO_FILE * __restrict, const char * __restrict,
                        __gnuc_va_list, int *__restrict) ;
extern int _IO_vfprintf (_IO_FILE *__restrict, const char *__restrict,
                         __gnuc_va_list) ;
extern __ssize_t _IO_padn (_IO_FILE *, int, __ssize_t) ;
extern size_t _IO_sgetn (_IO_FILE *, void *, size_t) ;

extern __off64_t _IO_seekoff (_IO_FILE *, __off64_t, int, int) ;
extern __off64_t _IO_seekpos (_IO_FILE *, __off64_t, int) ;

extern void _IO_free_backup_area (_IO_FILE *) ;
# 73 "/usr/include/stdio.h" 2 3
# 86 "/usr/include/stdio.h" 3


typedef _G_fpos_t fpos_t;




# 138 "/usr/include/stdio.h" 3
# 1 "/usr/include/bits/stdio_lim.h" 1 3
# 139 "/usr/include/stdio.h" 2 3



extern struct _IO_FILE *stdin;
extern struct _IO_FILE *stdout;
extern struct _IO_FILE *stderr;









extern int remove (__const char *__filename) ;

extern int rename (__const char *__old, __const char *__new) ;









extern FILE *tmpfile (void);
# 180 "/usr/include/stdio.h" 3
extern char *tmpnam (char *__s) ;





extern char *tmpnam_r (char *__s) ;
# 198 "/usr/include/stdio.h" 3
extern char *tempnam (__const char *__dir, __const char *__pfx)
     __attribute__ ((__malloc__));








extern int fclose (FILE *__stream);




extern int fflush (FILE *__stream);

# 223 "/usr/include/stdio.h" 3
extern int fflush_unlocked (FILE *__stream);
# 237 "/usr/include/stdio.h" 3






extern FILE *fopen (__const char *__restrict __filename,
                    __const char *__restrict __modes);




extern FILE *freopen (__const char *__restrict __filename,
                      __const char *__restrict __modes,
                      FILE *__restrict __stream);
# 264 "/usr/include/stdio.h" 3

# 275 "/usr/include/stdio.h" 3
extern FILE *fdopen (int __fd, __const char *__modes) ;
# 296 "/usr/include/stdio.h" 3



extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) ;



extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
                    int __modes, size_t __n) ;





extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
                       size_t __size) ;


extern void setlinebuf (FILE *__stream) ;








extern int fprintf (FILE *__restrict __stream,
                    __const char *__restrict __format, ...);




extern int printf (__const char *__restrict __format, ...);

extern int sprintf (char *__restrict __s,
                    __const char *__restrict __format, ...) ;





extern int vfprintf (FILE *__restrict __s, __const char *__restrict __format,
                     __gnuc_va_list __arg);




extern int vprintf (__const char *__restrict __format, __gnuc_va_list __arg);

extern int vsprintf (char *__restrict __s, __const char *__restrict __format,
                     __gnuc_va_list __arg) ;





extern int snprintf (char *__restrict __s, size_t __maxlen,
                     __const char *__restrict __format, ...)
     __attribute__ ((__format__ (__printf__, 3, 4)));

extern int vsnprintf (char *__restrict __s, size_t __maxlen,
                      __const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 3, 0)));

# 390 "/usr/include/stdio.h" 3





extern int fscanf (FILE *__restrict __stream,
                   __const char *__restrict __format, ...);




extern int scanf (__const char *__restrict __format, ...);

extern int sscanf (__const char *__restrict __s,
                   __const char *__restrict __format, ...) ;

# 432 "/usr/include/stdio.h" 3





extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);





extern int getchar (void);

# 456 "/usr/include/stdio.h" 3
extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
# 467 "/usr/include/stdio.h" 3
extern int fgetc_unlocked (FILE *__stream);











extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);





extern int putchar (int __c);

# 500 "/usr/include/stdio.h" 3
extern int fputc_unlocked (int __c, FILE *__stream);







extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);






extern int getw (FILE *__stream);


extern int putw (int __w, FILE *__stream);








extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream);






extern char *gets (char *__s);

# 580 "/usr/include/stdio.h" 3





extern int fputs (__const char *__restrict __s, FILE *__restrict __stream);





extern int puts (__const char *__s);






extern int ungetc (int __c, FILE *__stream);






extern size_t fread (void *__restrict __ptr, size_t __size,
                     size_t __n, FILE *__restrict __stream);




extern size_t fwrite (__const void *__restrict __ptr, size_t __size,
                      size_t __n, FILE *__restrict __s);

# 633 "/usr/include/stdio.h" 3
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
                              size_t __n, FILE *__restrict __stream);
extern size_t fwrite_unlocked (__const void *__restrict __ptr, size_t __size,
                               size_t __n, FILE *__restrict __stream);








extern int fseek (FILE *__stream, long int __off, int __whence);




extern long int ftell (FILE *__stream);




extern void rewind (FILE *__stream);

# 688 "/usr/include/stdio.h" 3






extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos);




extern int fsetpos (FILE *__stream, __const fpos_t *__pos);
# 711 "/usr/include/stdio.h" 3

# 720 "/usr/include/stdio.h" 3


extern void clearerr (FILE *__stream) ;

extern int feof (FILE *__stream) ;

extern int ferror (FILE *__stream) ;




extern void clearerr_unlocked (FILE *__stream) ;
extern int feof_unlocked (FILE *__stream) ;
extern int ferror_unlocked (FILE *__stream) ;








extern void perror (__const char *__s);






# 1 "/usr/include/bits/sys_errlist.h" 1 3
# 27 "/usr/include/bits/sys_errlist.h" 3
extern int sys_nerr;
extern __const char *__const sys_errlist[];
# 750 "/usr/include/stdio.h" 2 3




extern int fileno (FILE *__stream) ;




extern int fileno_unlocked (FILE *__stream) ;
# 769 "/usr/include/stdio.h" 3
extern FILE *popen (__const char *__command, __const char *__modes);





extern int pclose (FILE *__stream);





extern char *ctermid (char *__s) ;
# 809 "/usr/include/stdio.h" 3
extern void flockfile (FILE *__stream) ;



extern int ftrylockfile (FILE *__stream) ;


extern void funlockfile (FILE *__stream) ;
# 830 "/usr/include/stdio.h" 3
# 1 "/usr/include/bits/stdio.h" 1 3
# 33 "/usr/include/bits/stdio.h" 3
extern __inline int
vprintf (__const char *__restrict __fmt, __gnuc_va_list __arg)
{
  return vfprintf (stdout, __fmt, __arg);
}


extern __inline int
getchar (void)
{
  return _IO_getc (stdin);
}




extern __inline int
getc_unlocked (FILE *__fp)
{
  return ((__fp)->_IO_read_ptr >= (__fp)->_IO_read_end ? __uflow (__fp) : *(unsigned char *) (__fp)->_IO_read_ptr++);
}


extern __inline int
getchar_unlocked (void)
{
  return ((stdin)->_IO_read_ptr >= (stdin)->_IO_read_end ? __uflow (stdin) : *(unsigned char *) (stdin)->_IO_read_ptr++);
}




extern __inline int
putchar (int __c)
{
  return _IO_putc (__c, stdout);
}




extern __inline int
fputc_unlocked (int __c, FILE *__stream)
{
  return (((__stream)->_IO_write_ptr >= (__stream)->_IO_write_end) ? __overflow (__stream, (unsigned char) (__c)) : (unsigned char) (*(__stream)->_IO_write_ptr++ = (__c)));
}





extern __inline int
putc_unlocked (int __c, FILE *__stream)
{
  return (((__stream)->_IO_write_ptr >= (__stream)->_IO_write_end) ? __overflow (__stream, (unsigned char) (__c)) : (unsigned char) (*(__stream)->_IO_write_ptr++ = (__c)));
}


extern __inline int
putchar_unlocked (int __c)
{
  return (((stdout)->_IO_write_ptr >= (stdout)->_IO_write_end) ? __overflow (stdout, (unsigned char) (__c)) : (unsigned char) (*(stdout)->_IO_write_ptr++ = (__c)));
}
# 111 "/usr/include/bits/stdio.h" 3
extern __inline int
feof_unlocked (FILE *__stream)
{
  return (((__stream)->_flags & 0x10) != 0);
}


extern __inline int
ferror_unlocked (FILE *__stream)
{
  return (((__stream)->_flags & 0x20) != 0);
}
# 831 "/usr/include/stdio.h" 2 3



# 142 "/tmp/t852/include/tcl.h" 2
# 153 "/tmp/t852/include/tcl.h"
# 1 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stdarg.h" 1 3
# 110 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stdarg.h" 3
typedef __gnuc_va_list va_list;
# 154 "/tmp/t852/include/tcl.h" 2
# 309 "/tmp/t852/include/tcl.h"
        typedef void *ClientData;
# 363 "/tmp/t852/include/tcl.h"
typedef struct stat Tcl_StatBuf;
# 399 "/tmp/t852/include/tcl.h"
typedef long long Tcl_WideInt;
typedef unsigned long long Tcl_WideUInt;
# 449 "/tmp/t852/include/tcl.h"
typedef struct Tcl_Interp {
    char *result;

    void (*freeProc) (char *blockPtr);







    int errorLine;


} Tcl_Interp;

typedef struct Tcl_AsyncHandler_ *Tcl_AsyncHandler;
typedef struct Tcl_Channel_ *Tcl_Channel;
typedef struct Tcl_ChannelTypeVersion_ *Tcl_ChannelTypeVersion;
typedef struct Tcl_Command_ *Tcl_Command;
typedef struct Tcl_Condition_ *Tcl_Condition;
typedef struct Tcl_Dict_ *Tcl_Dict;
typedef struct Tcl_EncodingState_ *Tcl_EncodingState;
typedef struct Tcl_Encoding_ *Tcl_Encoding;
typedef struct Tcl_Event Tcl_Event;
typedef struct Tcl_InterpState_ *Tcl_InterpState;
typedef struct Tcl_LoadHandle_ *Tcl_LoadHandle;
typedef struct Tcl_Mutex_ *Tcl_Mutex;
typedef struct Tcl_Pid_ *Tcl_Pid;
typedef struct Tcl_RegExp_ *Tcl_RegExp;
typedef struct Tcl_ThreadDataKey_ *Tcl_ThreadDataKey;
typedef struct Tcl_ThreadId_ *Tcl_ThreadId;
typedef struct Tcl_TimerToken_ *Tcl_TimerToken;
typedef struct Tcl_Trace_ *Tcl_Trace;
typedef struct Tcl_Var_ *Tcl_Var;
# 494 "/tmp/t852/include/tcl.h"
typedef void (Tcl_ThreadCreateProc) (ClientData clientData);
# 558 "/tmp/t852/include/tcl.h"
typedef struct Tcl_RegExpIndices {
    long start;

    long end;

} Tcl_RegExpIndices;

typedef struct Tcl_RegExpInfo {
    int nsubs;

    Tcl_RegExpIndices *matches;
    long extendStart;

    long reserved;
} Tcl_RegExpInfo;






typedef Tcl_StatBuf *Tcl_Stat_;
typedef struct stat *Tcl_OldStat_;
# 623 "/tmp/t852/include/tcl.h"
typedef enum {
    TCL_INT, TCL_DOUBLE, TCL_EITHER, TCL_WIDE_INT
} Tcl_ValueType;

typedef struct Tcl_Value {
    Tcl_ValueType type;

    long intValue;
    double doubleValue;
    Tcl_WideInt wideValue;
} Tcl_Value;






struct Tcl_Obj;





typedef int (Tcl_AppInitProc) (Tcl_Interp *interp);
typedef int (Tcl_AsyncProc) (ClientData clientData, Tcl_Interp *interp, int code);

typedef void (Tcl_ChannelProc) (ClientData clientData, int mask);
typedef void (Tcl_CloseProc) (ClientData data);
typedef void (Tcl_CmdDeleteProc) (ClientData clientData);
typedef int (Tcl_CmdProc) (ClientData clientData, Tcl_Interp *interp, int argc, char *argv[]);

typedef void (Tcl_CmdTraceProc) (ClientData clientData, Tcl_Interp *interp, int level, char *command, Tcl_CmdProc *proc, ClientData cmdClientData, int argc, char *argv[]);


typedef int (Tcl_CmdObjTraceProc) (ClientData clientData, Tcl_Interp *interp, int level, const char *command, Tcl_Command commandInfo, int objc, struct Tcl_Obj * const * objv);


typedef void (Tcl_CmdObjTraceDeleteProc) (ClientData clientData);
typedef void (Tcl_DupInternalRepProc) (struct Tcl_Obj *srcPtr, struct Tcl_Obj *dupPtr);

typedef int (Tcl_EncodingConvertProc)(ClientData clientData, const char *src, int srcLen, int flags, Tcl_EncodingState *statePtr, char *dst, int dstLen, int *srcReadPtr, int *dstWrotePtr, int *dstCharsPtr);



typedef void (Tcl_EncodingFreeProc)(ClientData clientData);
typedef int (Tcl_EventProc) (Tcl_Event *evPtr, int flags);
typedef void (Tcl_EventCheckProc) (ClientData clientData, int flags);

typedef int (Tcl_EventDeleteProc) (Tcl_Event *evPtr, ClientData clientData);

typedef void (Tcl_EventSetupProc) (ClientData clientData, int flags);

typedef void (Tcl_ExitProc) (ClientData clientData);
typedef void (Tcl_FileProc) (ClientData clientData, int mask);
typedef void (Tcl_FileFreeProc) (ClientData clientData);
typedef void (Tcl_FreeInternalRepProc) (struct Tcl_Obj *objPtr);
typedef void (Tcl_FreeProc) (char *blockPtr);
typedef void (Tcl_IdleProc) (ClientData clientData);
typedef void (Tcl_InterpDeleteProc) (ClientData clientData, Tcl_Interp *interp);

typedef int (Tcl_MathProc) (ClientData clientData, Tcl_Interp *interp, Tcl_Value *args, Tcl_Value *resultPtr);

typedef void (Tcl_NamespaceDeleteProc) (ClientData clientData);
typedef int (Tcl_ObjCmdProc) (ClientData clientData, Tcl_Interp *interp, int objc, struct Tcl_Obj * const * objv);

typedef int (Tcl_PackageInitProc) (Tcl_Interp *interp);
typedef int (Tcl_PackageUnloadProc) (Tcl_Interp *interp, int flags);

typedef void (Tcl_PanicProc) (const char *format, ...);
typedef void (Tcl_TcpAcceptProc) (ClientData callbackData, Tcl_Channel chan, char *address, int port);

typedef void (Tcl_TimerProc) (ClientData clientData);
typedef int (Tcl_SetFromAnyProc) (Tcl_Interp *interp, struct Tcl_Obj *objPtr);

typedef void (Tcl_UpdateStringProc) (struct Tcl_Obj *objPtr);
typedef char *(Tcl_VarTraceProc) (ClientData clientData, Tcl_Interp *interp, char *part1, char *part2, int flags);


typedef void (Tcl_CommandTraceProc) (ClientData clientData, Tcl_Interp *interp, const char *oldName, const char *newName, int flags);


typedef void (Tcl_CreateFileHandlerProc) (int fd, int mask, Tcl_FileProc *proc, ClientData clientData);

typedef void (Tcl_DeleteFileHandlerProc) (int fd);
typedef void (Tcl_AlertNotifierProc) (ClientData clientData);
typedef void (Tcl_ServiceModeHookProc) (int mode);
typedef ClientData (Tcl_InitNotifierProc) (void);
typedef void (Tcl_FinalizeNotifierProc) (ClientData clientData);
typedef void (Tcl_MainLoopProc) (void);







typedef struct Tcl_ObjType {
    char *name;
    Tcl_FreeInternalRepProc *freeIntRepProc;



    Tcl_DupInternalRepProc *dupIntRepProc;


    Tcl_UpdateStringProc *updateStringProc;


    Tcl_SetFromAnyProc *setFromAnyProc;



} Tcl_ObjType;







typedef struct Tcl_Obj {
    int refCount;
    char *bytes;
# 756 "/tmp/t852/include/tcl.h"
    int length;

    Tcl_ObjType *typePtr;



    union {
        long longValue;
        double doubleValue;
        void *otherValuePtr;
        Tcl_WideInt wideValue;
        struct {
            void *ptr1;
            void *ptr2;
        } twoPtrValue;
        struct {

            void *ptr;
            unsigned long value;

        } ptrAndLongRep;
    } internalRep;
} Tcl_Obj;
# 791 "/tmp/t852/include/tcl.h"
void Tcl_IncrRefCount (Tcl_Obj *objPtr);
void Tcl_DecrRefCount (Tcl_Obj *objPtr);
int Tcl_IsShared (Tcl_Obj *objPtr);







typedef struct Tcl_SavedResult {
    char *result;
    Tcl_FreeProc *freeProc;
    Tcl_Obj *objResultPtr;
    char *appendResult;
    int appendAvl;
    int appendUsed;
    char resultSpace[200 +1];
} Tcl_SavedResult;







typedef struct Tcl_Namespace {
    char *name;



    char *fullName;

    ClientData clientData;

    Tcl_NamespaceDeleteProc *deleteProc;


    struct Tcl_Namespace *parentPtr;



} Tcl_Namespace;
# 857 "/tmp/t852/include/tcl.h"
typedef struct Tcl_CallFrame {
    Tcl_Namespace *nsPtr;
    int dummy1;
    int dummy2;
    char *dummy3;
    char *dummy4;
    char *dummy5;
    int dummy6;
    char *dummy7;
    char *dummy8;
    int dummy9;
    char *dummy10;
    char *dummy11;
    char *dummy12;
} Tcl_CallFrame;
# 887 "/tmp/t852/include/tcl.h"
typedef struct Tcl_CmdInfo {
    int isNativeObjectProc;



    Tcl_ObjCmdProc *objProc;
    ClientData objClientData;
    Tcl_CmdProc *proc;
    ClientData clientData;
    Tcl_CmdDeleteProc *deleteProc;


    ClientData deleteData;

    Tcl_Namespace *namespacePtr;




} Tcl_CmdInfo;
# 915 "/tmp/t852/include/tcl.h"
typedef struct Tcl_DString {
    char *string;

    int length;

    int spaceAvl;

    char staticSpace[200];


} Tcl_DString;
# 1074 "/tmp/t852/include/tcl.h"
typedef struct Tcl_HashKeyType Tcl_HashKeyType;
typedef struct Tcl_HashTable Tcl_HashTable;
typedef struct Tcl_HashEntry Tcl_HashEntry;

typedef unsigned int (Tcl_HashKeyProc) (Tcl_HashTable *tablePtr, void *keyPtr);

typedef int (Tcl_CompareHashKeysProc) (void *keyPtr, Tcl_HashEntry *hPtr);

typedef Tcl_HashEntry *(Tcl_AllocHashEntryProc) ( Tcl_HashTable *tablePtr, void *keyPtr);

typedef void (Tcl_FreeHashEntryProc) (Tcl_HashEntry *hPtr);
# 1103 "/tmp/t852/include/tcl.h"
struct Tcl_HashEntry {
    Tcl_HashEntry *nextPtr;

    Tcl_HashTable *tablePtr;

    void *hash;







    ClientData clientData;

    union {
        char *oneWordValue;
        Tcl_Obj *objPtr;
        int words[1];


        char string[4];

    } key;
};
# 1152 "/tmp/t852/include/tcl.h"
struct Tcl_HashKeyType {
    int version;



    int flags;
    Tcl_HashKeyProc *hashKeyProc;



    Tcl_CompareHashKeysProc *compareKeysProc;




    Tcl_AllocHashEntryProc *allocEntryProc;
# 1181 "/tmp/t852/include/tcl.h"
    Tcl_FreeHashEntryProc *freeEntryProc;






};
# 1197 "/tmp/t852/include/tcl.h"
struct Tcl_HashTable {
    Tcl_HashEntry **buckets;


    Tcl_HashEntry *staticBuckets[4];


    int numBuckets;

    int numEntries;

    int rebuildSize;

    int downShift;


    int mask;
    int keyType;




    Tcl_HashEntry *(*findProc) (Tcl_HashTable *tablePtr, const char *key);

    Tcl_HashEntry *(*createProc) (Tcl_HashTable *tablePtr, const char *key, int *newPtr);

    Tcl_HashKeyType *typePtr;

};






typedef struct Tcl_HashSearch {
    Tcl_HashTable *tablePtr;
    int nextIndex;

    Tcl_HashEntry *nextEntryPtr;

} Tcl_HashSearch;
# 1272 "/tmp/t852/include/tcl.h"
typedef struct {
    void *next;

    int epoch;

    Tcl_Dict dictionaryPtr;
} Tcl_DictSearch;
# 1301 "/tmp/t852/include/tcl.h"
struct Tcl_Event {
    Tcl_EventProc *proc;
    struct Tcl_Event *nextPtr;
};





typedef enum {
    TCL_QUEUE_TAIL, TCL_QUEUE_HEAD, TCL_QUEUE_MARK
} Tcl_QueuePosition;
# 1328 "/tmp/t852/include/tcl.h"
typedef struct Tcl_Time {
    long sec;
    long usec;
} Tcl_Time;

typedef void (Tcl_SetTimerProc) (Tcl_Time *timePtr);
typedef int (Tcl_WaitForEventProc) (Tcl_Time *timePtr);





typedef void (Tcl_GetTimeProc) (Tcl_Time *timebuf, ClientData clientData);

typedef void (Tcl_ScaleTimeProc) (Tcl_Time *timebuf, ClientData clientData);
# 1401 "/tmp/t852/include/tcl.h"
typedef int (Tcl_DriverBlockModeProc) ( ClientData instanceData, int mode);

typedef int (Tcl_DriverCloseProc) (ClientData instanceData, Tcl_Interp *interp);

typedef int (Tcl_DriverClose2Proc) (ClientData instanceData, Tcl_Interp *interp, int flags);

typedef int (Tcl_DriverInputProc) (ClientData instanceData, char *buf, int toRead, int *errorCodePtr);

typedef int (Tcl_DriverOutputProc) (ClientData instanceData, char *buf, int toWrite, int *errorCodePtr);

typedef int (Tcl_DriverSeekProc) (ClientData instanceData, long offset, int mode, int *errorCodePtr);

typedef int (Tcl_DriverSetOptionProc) ( ClientData instanceData, Tcl_Interp *interp, const char *optionName, const char *value);


typedef int (Tcl_DriverGetOptionProc) ( ClientData instanceData, Tcl_Interp *interp, char *optionName, Tcl_DString *dsPtr);


typedef void (Tcl_DriverWatchProc) ( ClientData instanceData, int mask);

typedef int (Tcl_DriverGetHandleProc) ( ClientData instanceData, int direction, ClientData *handlePtr);


typedef int (Tcl_DriverFlushProc) (ClientData instanceData);
typedef int (Tcl_DriverHandlerProc) ( ClientData instanceData, int interestMask);

typedef Tcl_WideInt (Tcl_DriverWideSeekProc) ( ClientData instanceData, Tcl_WideInt offset, int mode, int *errorCodePtr);





typedef void (Tcl_DriverThreadActionProc) ( ClientData instanceData, int action);




typedef int (Tcl_DriverTruncateProc) ( ClientData instanceData, Tcl_WideInt length);
# 1452 "/tmp/t852/include/tcl.h"
typedef struct Tcl_ChannelType {
    char *typeName;


    Tcl_ChannelTypeVersion version;

    Tcl_DriverCloseProc *closeProc;



    Tcl_DriverInputProc *inputProc;

    Tcl_DriverOutputProc *outputProc;

    Tcl_DriverSeekProc *seekProc;


    Tcl_DriverSetOptionProc *setOptionProc;

    Tcl_DriverGetOptionProc *getOptionProc;

    Tcl_DriverWatchProc *watchProc;


    Tcl_DriverGetHandleProc *getHandleProc;


    Tcl_DriverClose2Proc *close2Proc;



    Tcl_DriverBlockModeProc *blockModeProc;





    Tcl_DriverFlushProc *flushProc;


    Tcl_DriverHandlerProc *handlerProc;






    Tcl_DriverWideSeekProc *wideSeekProc;
# 1508 "/tmp/t852/include/tcl.h"
    Tcl_DriverThreadActionProc *threadActionProc;
# 1517 "/tmp/t852/include/tcl.h"
    Tcl_DriverTruncateProc *truncateProc;



} Tcl_ChannelType;
# 1537 "/tmp/t852/include/tcl.h"
typedef enum Tcl_PathType {
    TCL_PATH_ABSOLUTE,
    TCL_PATH_RELATIVE,
    TCL_PATH_VOLUME_RELATIVE
} Tcl_PathType;






typedef struct Tcl_GlobTypeData {
    int type;
    int perm;
    Tcl_Obj *macType;
    Tcl_Obj *macCreator;
} Tcl_GlobTypeData;
# 1585 "/tmp/t852/include/tcl.h"
typedef int (Tcl_FSStatProc) (Tcl_Obj *pathPtr, Tcl_StatBuf *buf);
typedef int (Tcl_FSAccessProc) (Tcl_Obj *pathPtr, int mode);
typedef Tcl_Channel (Tcl_FSOpenFileChannelProc) ( Tcl_Interp *interp, Tcl_Obj *pathPtr, int mode, int permissions);

typedef int (Tcl_FSMatchInDirectoryProc) (Tcl_Interp *interp, Tcl_Obj *result, Tcl_Obj *pathPtr, const char *pattern, Tcl_GlobTypeData * types);


typedef Tcl_Obj * (Tcl_FSGetCwdProc) (Tcl_Interp *interp);
typedef int (Tcl_FSChdirProc) (Tcl_Obj *pathPtr);
typedef int (Tcl_FSLstatProc) (Tcl_Obj *pathPtr, Tcl_StatBuf *buf);

typedef int (Tcl_FSCreateDirectoryProc) (Tcl_Obj *pathPtr);
typedef int (Tcl_FSDeleteFileProc) (Tcl_Obj *pathPtr);
typedef int (Tcl_FSCopyDirectoryProc) (Tcl_Obj *srcPathPtr, Tcl_Obj *destPathPtr, Tcl_Obj **errorPtr);

typedef int (Tcl_FSCopyFileProc) (Tcl_Obj *srcPathPtr, Tcl_Obj *destPathPtr);

typedef int (Tcl_FSRemoveDirectoryProc) (Tcl_Obj *pathPtr, int recursive, Tcl_Obj **errorPtr);

typedef int (Tcl_FSRenameFileProc) (Tcl_Obj *srcPathPtr, Tcl_Obj *destPathPtr);

typedef void (Tcl_FSUnloadFileProc) (Tcl_LoadHandle loadHandle);
typedef Tcl_Obj * (Tcl_FSListVolumesProc) (void);

struct utimbuf;
typedef int (Tcl_FSUtimeProc) (Tcl_Obj *pathPtr, struct utimbuf *tval);

typedef int (Tcl_FSNormalizePathProc) (Tcl_Interp *interp, Tcl_Obj *pathPtr, int nextCheckpoint);

typedef int (Tcl_FSFileAttrsGetProc) (Tcl_Interp *interp, int index, Tcl_Obj *pathPtr, Tcl_Obj **objPtrRef);

typedef const char ** (Tcl_FSFileAttrStringsProc) ( Tcl_Obj *pathPtr, Tcl_Obj **objPtrRef);

typedef int (Tcl_FSFileAttrsSetProc) (Tcl_Interp *interp, int index, Tcl_Obj *pathPtr, Tcl_Obj *objPtr);

typedef Tcl_Obj * (Tcl_FSLinkProc) (Tcl_Obj *pathPtr, Tcl_Obj *toPtr, int linkType);

typedef int (Tcl_FSLoadFileProc) (Tcl_Interp * interp, Tcl_Obj *pathPtr, Tcl_LoadHandle *handlePtr, Tcl_FSUnloadFileProc **unloadProcPtr);


typedef int (Tcl_FSPathInFilesystemProc) (Tcl_Obj *pathPtr, ClientData *clientDataPtr);

typedef Tcl_Obj * (Tcl_FSFilesystemPathTypeProc) ( Tcl_Obj *pathPtr);

typedef Tcl_Obj * (Tcl_FSFilesystemSeparatorProc) ( Tcl_Obj *pathPtr);

typedef void (Tcl_FSFreeInternalRepProc) (ClientData clientData);
typedef ClientData (Tcl_FSDupInternalRepProc) ( ClientData clientData);

typedef Tcl_Obj * (Tcl_FSInternalToNormalizedProc) ( ClientData clientData);

typedef ClientData (Tcl_FSCreateInternalRepProc) ( Tcl_Obj *pathPtr);


typedef struct Tcl_FSVersion_ *Tcl_FSVersion;
# 1665 "/tmp/t852/include/tcl.h"
typedef struct Tcl_Filesystem {
    const char *typeName;
    int structureLength;

    Tcl_FSVersion version;
    Tcl_FSPathInFilesystemProc *pathInFilesystemProc;



    Tcl_FSDupInternalRepProc *dupInternalRepProc;


    Tcl_FSFreeInternalRepProc *freeInternalRepProc;



    Tcl_FSInternalToNormalizedProc *internalToNormalizedProc;




    Tcl_FSCreateInternalRepProc *createInternalRepProc;







    Tcl_FSNormalizePathProc *normalizePathProc;




    Tcl_FSFilesystemPathTypeProc *filesystemPathTypeProc;


    Tcl_FSFilesystemSeparatorProc *filesystemSeparatorProc;



    Tcl_FSStatProc *statProc;


    Tcl_FSAccessProc *accessProc;



    Tcl_FSOpenFileChannelProc *openFileChannelProc;




    Tcl_FSMatchInDirectoryProc *matchInDirectoryProc;





    Tcl_FSUtimeProc *utimeProc;




    Tcl_FSLinkProc *linkProc;



    Tcl_FSListVolumesProc *listVolumesProc;




    Tcl_FSFileAttrStringsProc *fileAttrStringsProc;






    Tcl_FSFileAttrsGetProc *fileAttrsGetProc;



    Tcl_FSFileAttrsSetProc *fileAttrsSetProc;



    Tcl_FSCreateDirectoryProc *createDirectoryProc;



    Tcl_FSRemoveDirectoryProc *removeDirectoryProc;



    Tcl_FSDeleteFileProc *deleteFileProc;



    Tcl_FSCopyFileProc *copyFileProc;





    Tcl_FSRenameFileProc *renameFileProc;




    Tcl_FSCopyDirectoryProc *copyDirectoryProc;






    Tcl_FSLstatProc *lstatProc;


    Tcl_FSLoadFileProc *loadFileProc;




    Tcl_FSGetCwdProc *getCwdProc;





    Tcl_FSChdirProc *chdirProc;
# 1812 "/tmp/t852/include/tcl.h"
} Tcl_Filesystem;
# 1832 "/tmp/t852/include/tcl.h"
typedef struct Tcl_NotifierProcs {
    Tcl_SetTimerProc *setTimerProc;
    Tcl_WaitForEventProc *waitForEventProc;
    Tcl_CreateFileHandlerProc *createFileHandlerProc;
    Tcl_DeleteFileHandlerProc *deleteFileHandlerProc;
    Tcl_InitNotifierProc *initNotifierProc;
    Tcl_FinalizeNotifierProc *finalizeNotifierProc;
    Tcl_AlertNotifierProc *alertNotifierProc;
    Tcl_ServiceModeHookProc *serviceModeHookProc;
} Tcl_NotifierProcs;






typedef struct Tcl_EncodingType {
    const char *encodingName;


    Tcl_EncodingConvertProc *toUtfProc;


    Tcl_EncodingConvertProc *fromUtfProc;


    Tcl_EncodingFreeProc *freeProc;


    ClientData clientData;

    int nullSize;




} Tcl_EncodingType;
# 1914 "/tmp/t852/include/tcl.h"
typedef struct Tcl_Token {
    int type;

    const char *start;
    int size;
    int numComponents;




} Tcl_Token;
# 2030 "/tmp/t852/include/tcl.h"
typedef struct Tcl_Parse {
    const char *commentStart;

    int commentSize;



    const char *commandStart;

    int commandSize;



    int numWords;

    Tcl_Token *tokenPtr;




    int numTokens;
    int tokensAvailable;

    int errorType;







    const char *string;

    const char *end;

    Tcl_Interp *interp;

    const char *term;





    int incomplete;



    Tcl_Token staticTokens[20];





} Tcl_Parse;
# 2149 "/tmp/t852/include/tcl.h"
typedef unsigned short Tcl_UniChar;







typedef struct Tcl_Config {
    const char *key;

    const char *value;

} Tcl_Config;
# 2177 "/tmp/t852/include/tcl.h"
typedef void (Tcl_LimitHandlerProc) (ClientData clientData, Tcl_Interp *interp);

typedef void (Tcl_LimitHandlerDeleteProc) (ClientData clientData);


typedef struct mp_int mp_int;



typedef unsigned long mp_digit;
# 2207 "/tmp/t852/include/tcl.h"
extern const char * Tcl_InitStubs (Tcl_Interp *interp, const char *version, int exact);

extern const char * TclTomMathInitializeStubs ( Tcl_Interp *interp, const char *version, int epoch, int revision);
# 2234 "/tmp/t852/include/tcl.h"
extern void Tcl_Main (int argc, char **argv, Tcl_AppInitProc *appInitProc);

extern const char * Tcl_PkgInitStubsCheck (Tcl_Interp *interp, const char *version, int exact);
# 2247 "/tmp/t852/include/tcl.h"
# 1 "/tmp/t852/include/tclDecls.h" 1
# 43 "/tmp/t852/include/tclDecls.h"
extern int Tcl_PkgProvideEx (Tcl_Interp* interp,
                                const char* name, const char* version,
                                ClientData clientData);




extern char * Tcl_PkgRequireEx (Tcl_Interp * interp,
                                const char * name, const char * version,
                                int exact, ClientData * clientDataPtr);




extern void Tcl_Panic (const char * format, ...);




extern char * Tcl_Alloc (unsigned int size);




extern void Tcl_Free (char * ptr);




extern char * Tcl_Realloc (char * ptr, unsigned int size);




extern char * Tcl_DbCkalloc (unsigned int size, const char * file,
                                int line);




extern int Tcl_DbCkfree (char * ptr, const char * file,
                                int line);




extern char * Tcl_DbCkrealloc (char * ptr, unsigned int size,
                                const char * file, int line);





extern void Tcl_CreateFileHandler (int fd, int mask,
                                Tcl_FileProc * proc, ClientData clientData);
# 112 "/tmp/t852/include/tclDecls.h"
extern void Tcl_DeleteFileHandler (int fd);
# 125 "/tmp/t852/include/tclDecls.h"
extern void Tcl_SetTimer (Tcl_Time * timePtr);




extern void Tcl_Sleep (int ms);




extern int Tcl_WaitForEvent (Tcl_Time * timePtr);




extern int Tcl_AppendAllObjTypes (Tcl_Interp * interp,
                                Tcl_Obj * objPtr);




extern void Tcl_AppendStringsToObj (Tcl_Obj * objPtr, ...);




extern void Tcl_AppendToObj (Tcl_Obj* objPtr, const char* bytes,
                                int length);




extern Tcl_Obj * Tcl_ConcatObj (int objc, Tcl_Obj *const objv[]);




extern int Tcl_ConvertToType (Tcl_Interp * interp,
                                Tcl_Obj * objPtr, Tcl_ObjType * typePtr);




extern void Tcl_DbDecrRefCount (Tcl_Obj * objPtr,
                                const char * file, int line);




extern void Tcl_DbIncrRefCount (Tcl_Obj * objPtr,
                                const char * file, int line);




extern int Tcl_DbIsShared (Tcl_Obj * objPtr, const char * file,
                                int line);




extern Tcl_Obj * Tcl_DbNewBooleanObj (int boolValue,
                                const char * file, int line);




extern Tcl_Obj * Tcl_DbNewByteArrayObj (const unsigned char * bytes,
                                int length, const char * file, int line);




extern Tcl_Obj * Tcl_DbNewDoubleObj (double doubleValue,
                                const char * file, int line);




extern Tcl_Obj * Tcl_DbNewListObj (int objc, Tcl_Obj *const * objv,
                                const char * file, int line);




extern Tcl_Obj * Tcl_DbNewLongObj (long longValue, const char * file,
                                int line);




extern Tcl_Obj * Tcl_DbNewObj (const char * file, int line);




extern Tcl_Obj * Tcl_DbNewStringObj (const char * bytes, int length,
                                const char * file, int line);




extern Tcl_Obj * Tcl_DuplicateObj (Tcl_Obj * objPtr);




extern void TclFreeObj (Tcl_Obj * objPtr);




extern int Tcl_GetBoolean (Tcl_Interp * interp,
                                const char * src, int * boolPtr);




extern int Tcl_GetBooleanFromObj (Tcl_Interp * interp,
                                Tcl_Obj * objPtr, int * boolPtr);




extern unsigned char * Tcl_GetByteArrayFromObj (Tcl_Obj * objPtr,
                                int * lengthPtr);




extern int Tcl_GetDouble (Tcl_Interp * interp, const char * src,
                                double * doublePtr);




extern int Tcl_GetDoubleFromObj (Tcl_Interp * interp,
                                Tcl_Obj * objPtr, double * doublePtr);




extern int Tcl_GetIndexFromObj (Tcl_Interp * interp,
                                Tcl_Obj * objPtr, char ** tablePtr,
                                const char * msg, int flags, int * indexPtr);




extern int Tcl_GetInt (Tcl_Interp * interp, const char * src,
                                int * intPtr);




extern int Tcl_GetIntFromObj (Tcl_Interp * interp,
                                Tcl_Obj * objPtr, int * intPtr);




extern int Tcl_GetLongFromObj (Tcl_Interp * interp,
                                Tcl_Obj * objPtr, long * longPtr);




extern Tcl_ObjType * Tcl_GetObjType (const char * typeName);




extern char * Tcl_GetStringFromObj (Tcl_Obj * objPtr,
                                int * lengthPtr);




extern void Tcl_InvalidateStringRep (Tcl_Obj * objPtr);




extern int Tcl_ListObjAppendList (Tcl_Interp * interp,
                                Tcl_Obj * listPtr, Tcl_Obj * elemListPtr);




extern int Tcl_ListObjAppendElement (Tcl_Interp * interp,
                                Tcl_Obj * listPtr, Tcl_Obj * objPtr);




extern int Tcl_ListObjGetElements (Tcl_Interp * interp,
                                Tcl_Obj * listPtr, int * objcPtr,
                                Tcl_Obj *** objvPtr);




extern int Tcl_ListObjIndex (Tcl_Interp * interp,
                                Tcl_Obj * listPtr, int index,
                                Tcl_Obj ** objPtrPtr);




extern int Tcl_ListObjLength (Tcl_Interp * interp,
                                Tcl_Obj * listPtr, int * lengthPtr);




extern int Tcl_ListObjReplace (Tcl_Interp * interp,
                                Tcl_Obj * listPtr, int first, int count,
                                int objc, Tcl_Obj *const objv[]);




extern Tcl_Obj * Tcl_NewBooleanObj (int boolValue);




extern Tcl_Obj * Tcl_NewByteArrayObj (const unsigned char* bytes,
                                int length);




extern Tcl_Obj * Tcl_NewDoubleObj (double doubleValue);




extern Tcl_Obj * Tcl_NewIntObj (int intValue);




extern Tcl_Obj * Tcl_NewListObj (int objc, Tcl_Obj *const objv[]);




extern Tcl_Obj * Tcl_NewLongObj (long longValue);




extern Tcl_Obj * Tcl_NewObj (void);




extern Tcl_Obj * Tcl_NewStringObj (const char * bytes, int length);




extern void Tcl_SetBooleanObj (Tcl_Obj * objPtr, int boolValue);




extern unsigned char * Tcl_SetByteArrayLength (Tcl_Obj * objPtr, int length);




extern void Tcl_SetByteArrayObj (Tcl_Obj * objPtr,
                                const unsigned char * bytes, int length);




extern void Tcl_SetDoubleObj (Tcl_Obj * objPtr,
                                double doubleValue);




extern void Tcl_SetIntObj (Tcl_Obj * objPtr, int intValue);




extern void Tcl_SetListObj (Tcl_Obj * objPtr, int objc,
                                Tcl_Obj *const objv[]);




extern void Tcl_SetLongObj (Tcl_Obj * objPtr, long longValue);




extern void Tcl_SetObjLength (Tcl_Obj * objPtr, int length);




extern void Tcl_SetStringObj (Tcl_Obj* objPtr, const char* bytes,
                                int length);




extern void Tcl_AddErrorInfo (Tcl_Interp * interp,
                                const char * message);




extern void Tcl_AddObjErrorInfo (Tcl_Interp * interp,
                                const char * message, int length);




extern void Tcl_AllowExceptions (Tcl_Interp * interp);




extern void Tcl_AppendElement (Tcl_Interp * interp,
                                const char * element);




extern void Tcl_AppendResult (Tcl_Interp * interp, ...);




extern Tcl_AsyncHandler Tcl_AsyncCreate (Tcl_AsyncProc * proc,
                                ClientData clientData);




extern void Tcl_AsyncDelete (Tcl_AsyncHandler async);




extern int Tcl_AsyncInvoke (Tcl_Interp * interp, int code);




extern void Tcl_AsyncMark (Tcl_AsyncHandler async);




extern int Tcl_AsyncReady (void);




extern void Tcl_BackgroundError (Tcl_Interp * interp);




extern char Tcl_Backslash (const char * src, int * readPtr);




extern int Tcl_BadChannelOption (Tcl_Interp * interp,
                                const char * optionName,
                                const char * optionList);




extern void Tcl_CallWhenDeleted (Tcl_Interp * interp,
                                Tcl_InterpDeleteProc * proc,
                                ClientData clientData);




extern void Tcl_CancelIdleCall (Tcl_IdleProc * idleProc,
                                ClientData clientData);




extern int Tcl_Close (Tcl_Interp * interp, Tcl_Channel chan);




extern int Tcl_CommandComplete (const char * cmd);




extern char * Tcl_Concat (int argc, char * const * argv);




extern int Tcl_ConvertElement (const char * src, char * dst,
                                int flags);




extern int Tcl_ConvertCountedElement (const char * src,
                                int length, char * dst, int flags);




extern int Tcl_CreateAlias (Tcl_Interp * slave,
                                const char * slaveCmd, Tcl_Interp * target,
                                const char * targetCmd, int argc,
                                char * const * argv);




extern int Tcl_CreateAliasObj (Tcl_Interp * slave,
                                const char * slaveCmd, Tcl_Interp * target,
                                const char * targetCmd, int objc,
                                Tcl_Obj *const objv[]);




extern Tcl_Channel Tcl_CreateChannel (Tcl_ChannelType * typePtr,
                                const char * chanName,
                                ClientData instanceData, int mask);




extern void Tcl_CreateChannelHandler (Tcl_Channel chan, int mask,
                                Tcl_ChannelProc * proc,
                                ClientData clientData);




extern void Tcl_CreateCloseHandler (Tcl_Channel chan,
                                Tcl_CloseProc * proc, ClientData clientData);




extern Tcl_Command Tcl_CreateCommand (Tcl_Interp * interp,
                                const char * cmdName, Tcl_CmdProc * proc,
                                ClientData clientData,
                                Tcl_CmdDeleteProc * deleteProc);




extern void Tcl_CreateEventSource (
                                Tcl_EventSetupProc * setupProc,
                                Tcl_EventCheckProc * checkProc,
                                ClientData clientData);




extern void Tcl_CreateExitHandler (Tcl_ExitProc * proc,
                                ClientData clientData);




extern Tcl_Interp * Tcl_CreateInterp (void);




extern void Tcl_CreateMathFunc (Tcl_Interp * interp,
                                const char * name, int numArgs,
                                Tcl_ValueType * argTypes,
                                Tcl_MathProc * proc, ClientData clientData);




extern Tcl_Command Tcl_CreateObjCommand (Tcl_Interp * interp,
                                const char * cmdName, Tcl_ObjCmdProc * proc,
                                ClientData clientData,
                                Tcl_CmdDeleteProc * deleteProc);




extern Tcl_Interp * Tcl_CreateSlave (Tcl_Interp * interp,
                                const char * slaveName, int isSafe);




extern Tcl_TimerToken Tcl_CreateTimerHandler (int milliseconds,
                                Tcl_TimerProc * proc, ClientData clientData);




extern Tcl_Trace Tcl_CreateTrace (Tcl_Interp * interp, int level,
                                Tcl_CmdTraceProc * proc,
                                ClientData clientData);




extern void Tcl_DeleteAssocData (Tcl_Interp * interp,
                                const char * name);




extern void Tcl_DeleteChannelHandler (Tcl_Channel chan,
                                Tcl_ChannelProc * proc,
                                ClientData clientData);




extern void Tcl_DeleteCloseHandler (Tcl_Channel chan,
                                Tcl_CloseProc * proc, ClientData clientData);




extern int Tcl_DeleteCommand (Tcl_Interp * interp,
                                const char * cmdName);




extern int Tcl_DeleteCommandFromToken (Tcl_Interp * interp,
                                Tcl_Command command);




extern void Tcl_DeleteEvents (Tcl_EventDeleteProc * proc,
                                ClientData clientData);




extern void Tcl_DeleteEventSource (
                                Tcl_EventSetupProc * setupProc,
                                Tcl_EventCheckProc * checkProc,
                                ClientData clientData);




extern void Tcl_DeleteExitHandler (Tcl_ExitProc * proc,
                                ClientData clientData);




extern void Tcl_DeleteHashEntry (Tcl_HashEntry * entryPtr);




extern void Tcl_DeleteHashTable (Tcl_HashTable * tablePtr);




extern void Tcl_DeleteInterp (Tcl_Interp * interp);





extern void Tcl_DetachPids (int numPids, Tcl_Pid * pidPtr);
# 733 "/tmp/t852/include/tclDecls.h"
extern void Tcl_DeleteTimerHandler (Tcl_TimerToken token);




extern void Tcl_DeleteTrace (Tcl_Interp * interp,
                                Tcl_Trace trace);




extern void Tcl_DontCallWhenDeleted (Tcl_Interp * interp,
                                Tcl_InterpDeleteProc * proc,
                                ClientData clientData);




extern int Tcl_DoOneEvent (int flags);




extern void Tcl_DoWhenIdle (Tcl_IdleProc * proc,
                                ClientData clientData);




extern char * Tcl_DStringAppend (Tcl_DString * dsPtr,
                                const char * bytes, int length);




extern char * Tcl_DStringAppendElement (Tcl_DString * dsPtr,
                                const char * element);




extern void Tcl_DStringEndSublist (Tcl_DString * dsPtr);




extern void Tcl_DStringFree (Tcl_DString * dsPtr);




extern void Tcl_DStringGetResult (Tcl_Interp * interp,
                                Tcl_DString * dsPtr);




extern void Tcl_DStringInit (Tcl_DString * dsPtr);




extern void Tcl_DStringResult (Tcl_Interp * interp,
                                Tcl_DString * dsPtr);




extern void Tcl_DStringSetLength (Tcl_DString * dsPtr,
                                int length);




extern void Tcl_DStringStartSublist (Tcl_DString * dsPtr);




extern int Tcl_Eof (Tcl_Channel chan);




extern char * Tcl_ErrnoId (void);




extern char * Tcl_ErrnoMsg (int err);




extern int Tcl_Eval (Tcl_Interp * interp, const char * script);




extern int Tcl_EvalFile (Tcl_Interp * interp,
                                const char * fileName);




extern int Tcl_EvalObj (Tcl_Interp * interp, Tcl_Obj * objPtr);




extern void Tcl_EventuallyFree (ClientData clientData,
                                Tcl_FreeProc * freeProc);




extern void Tcl_Exit (int status);




extern int Tcl_ExposeCommand (Tcl_Interp * interp,
                                const char * hiddenCmdToken,
                                const char * cmdName);




extern int Tcl_ExprBoolean (Tcl_Interp * interp,
                                const char * expr, int * ptr);




extern int Tcl_ExprBooleanObj (Tcl_Interp * interp,
                                Tcl_Obj * objPtr, int * ptr);




extern int Tcl_ExprDouble (Tcl_Interp * interp,
                                const char * expr, double * ptr);




extern int Tcl_ExprDoubleObj (Tcl_Interp * interp,
                                Tcl_Obj * objPtr, double * ptr);




extern int Tcl_ExprLong (Tcl_Interp * interp, const char * expr,
                                long * ptr);




extern int Tcl_ExprLongObj (Tcl_Interp * interp,
                                Tcl_Obj * objPtr, long * ptr);




extern int Tcl_ExprObj (Tcl_Interp * interp, Tcl_Obj * objPtr,
                                Tcl_Obj ** resultPtrPtr);




extern int Tcl_ExprString (Tcl_Interp * interp,
                                const char * expr);




extern void Tcl_Finalize (void);




extern void Tcl_FindExecutable (const char * argv0);




extern Tcl_HashEntry * Tcl_FirstHashEntry (Tcl_HashTable * tablePtr,
                                Tcl_HashSearch * searchPtr);




extern int Tcl_Flush (Tcl_Channel chan);




extern void Tcl_FreeResult (Tcl_Interp * interp);




extern int Tcl_GetAlias (Tcl_Interp * interp,
                                const char * slaveCmd,
                                Tcl_Interp ** targetInterpPtr,
                                char ** targetCmdPtr, int * argcPtr,
                                char *** argvPtr);




extern int Tcl_GetAliasObj (Tcl_Interp * interp,
                                const char * slaveCmd,
                                Tcl_Interp ** targetInterpPtr,
                                char ** targetCmdPtr, int * objcPtr,
                                Tcl_Obj *** objv);




extern ClientData Tcl_GetAssocData (Tcl_Interp * interp,
                                const char * name,
                                Tcl_InterpDeleteProc ** procPtr);




extern Tcl_Channel Tcl_GetChannel (Tcl_Interp * interp,
                                const char * chanName, int * modePtr);




extern int Tcl_GetChannelBufferSize (Tcl_Channel chan);




extern int Tcl_GetChannelHandle (Tcl_Channel chan,
                                int direction, ClientData * handlePtr);




extern ClientData Tcl_GetChannelInstanceData (Tcl_Channel chan);




extern int Tcl_GetChannelMode (Tcl_Channel chan);




extern char * Tcl_GetChannelName (Tcl_Channel chan);




extern int Tcl_GetChannelOption (Tcl_Interp * interp,
                                Tcl_Channel chan, const char * optionName,
                                Tcl_DString * dsPtr);




extern Tcl_ChannelType * Tcl_GetChannelType (Tcl_Channel chan);




extern int Tcl_GetCommandInfo (Tcl_Interp * interp,
                                const char * cmdName, Tcl_CmdInfo * infoPtr);




extern char * Tcl_GetCommandName (Tcl_Interp * interp,
                                Tcl_Command command);




extern int Tcl_GetErrno (void);




extern char * Tcl_GetHostName (void);




extern int Tcl_GetInterpPath (Tcl_Interp * askInterp,
                                Tcl_Interp * slaveInterp);




extern Tcl_Interp * Tcl_GetMaster (Tcl_Interp * interp);




extern const char * Tcl_GetNameOfExecutable (void);




extern Tcl_Obj * Tcl_GetObjResult (Tcl_Interp * interp);





extern int Tcl_GetOpenFile (Tcl_Interp * interp,
                                const char * chanID, int forWriting,
                                int checkUsage, ClientData * filePtr);
# 1065 "/tmp/t852/include/tclDecls.h"
extern Tcl_PathType Tcl_GetPathType (const char * path);




extern int Tcl_Gets (Tcl_Channel chan, Tcl_DString * dsPtr);




extern int Tcl_GetsObj (Tcl_Channel chan, Tcl_Obj * objPtr);




extern int Tcl_GetServiceMode (void);




extern Tcl_Interp * Tcl_GetSlave (Tcl_Interp * interp,
                                const char * slaveName);




extern Tcl_Channel Tcl_GetStdChannel (int type);




extern char * Tcl_GetStringResult (Tcl_Interp * interp);




extern char * Tcl_GetVar (Tcl_Interp * interp,
                                const char * varName, int flags);




extern char * Tcl_GetVar2 (Tcl_Interp * interp,
                                const char * part1, const char * part2,
                                int flags);




extern int Tcl_GlobalEval (Tcl_Interp * interp,
                                const char * command);




extern int Tcl_GlobalEvalObj (Tcl_Interp * interp,
                                Tcl_Obj * objPtr);




extern int Tcl_HideCommand (Tcl_Interp * interp,
                                const char * cmdName,
                                const char * hiddenCmdToken);




extern int Tcl_Init (Tcl_Interp * interp);




extern void Tcl_InitHashTable (Tcl_HashTable * tablePtr,
                                int keyType);




extern int Tcl_InputBlocked (Tcl_Channel chan);




extern int Tcl_InputBuffered (Tcl_Channel chan);




extern int Tcl_InterpDeleted (Tcl_Interp * interp);




extern int Tcl_IsSafe (Tcl_Interp * interp);




extern char * Tcl_JoinPath (int argc, char * const * argv,
                                Tcl_DString * resultPtr);




extern int Tcl_LinkVar (Tcl_Interp * interp,
                                const char * varName, char * addr, int type);





extern Tcl_Channel Tcl_MakeFileChannel (ClientData handle, int mode);




extern int Tcl_MakeSafe (Tcl_Interp * interp);




extern Tcl_Channel Tcl_MakeTcpClientChannel (ClientData tcpSocket);




extern char * Tcl_Merge (int argc, char * const * argv);




extern Tcl_HashEntry * Tcl_NextHashEntry (Tcl_HashSearch * searchPtr);




extern void Tcl_NotifyChannel (Tcl_Channel channel, int mask);




extern Tcl_Obj * Tcl_ObjGetVar2 (Tcl_Interp * interp,
                                Tcl_Obj * part1Ptr, Tcl_Obj * part2Ptr,
                                int flags);




extern Tcl_Obj * Tcl_ObjSetVar2 (Tcl_Interp * interp,
                                Tcl_Obj * part1Ptr, Tcl_Obj * part2Ptr,
                                Tcl_Obj * newValuePtr, int flags);





extern Tcl_Channel Tcl_OpenCommandChannel (Tcl_Interp * interp,
                                int argc, char ** argv, int flags);
# 1245 "/tmp/t852/include/tclDecls.h"
extern Tcl_Channel Tcl_OpenFileChannel (Tcl_Interp * interp,
                                const char * fileName,
                                const char * modeString, int permissions);




extern Tcl_Channel Tcl_OpenTcpClient (Tcl_Interp * interp, int port,
                                const char * address, const char * myaddr,
                                int myport, int async);




extern Tcl_Channel Tcl_OpenTcpServer (Tcl_Interp * interp, int port,
                                const char * host,
                                Tcl_TcpAcceptProc * acceptProc,
                                ClientData callbackData);




extern void Tcl_Preserve (ClientData data);




extern void Tcl_PrintDouble (Tcl_Interp * interp, double value,
                                char * dst);




extern int Tcl_PutEnv (const char * assignment);




extern char * Tcl_PosixError (Tcl_Interp * interp);




extern void Tcl_QueueEvent (Tcl_Event * evPtr,
                                Tcl_QueuePosition position);




extern int Tcl_Read (Tcl_Channel chan, char * bufPtr,
                                int toRead);





extern void Tcl_ReapDetachedProcs (void);
# 1321 "/tmp/t852/include/tclDecls.h"
extern int Tcl_RecordAndEval (Tcl_Interp * interp,
                                const char * cmd, int flags);




extern int Tcl_RecordAndEvalObj (Tcl_Interp * interp,
                                Tcl_Obj * cmdPtr, int flags);




extern void Tcl_RegisterChannel (Tcl_Interp * interp,
                                Tcl_Channel chan);




extern void Tcl_RegisterObjType (Tcl_ObjType * typePtr);




extern Tcl_RegExp Tcl_RegExpCompile (Tcl_Interp * interp,
                                const char * pattern);




extern int Tcl_RegExpExec (Tcl_Interp * interp,
                                Tcl_RegExp regexp, const char * text,
                                const char * start);




extern int Tcl_RegExpMatch (Tcl_Interp * interp,
                                const char * text, const char * pattern);




extern void Tcl_RegExpRange (Tcl_RegExp regexp, int index,
                                char ** startPtr,
                                char ** endPtr);




extern void Tcl_Release (ClientData clientData);




extern void Tcl_ResetResult (Tcl_Interp * interp);




extern int Tcl_ScanElement (const char * str, int * flagPtr);




extern int Tcl_ScanCountedElement (const char * str, int length,
                                int * flagPtr);




extern int Tcl_SeekOld (Tcl_Channel chan, int offset, int mode);




extern int Tcl_ServiceAll (void);




extern int Tcl_ServiceEvent (int flags);




extern void Tcl_SetAssocData (Tcl_Interp * interp,
                                const char * name,
                                Tcl_InterpDeleteProc * proc,
                                ClientData clientData);




extern void Tcl_SetChannelBufferSize (Tcl_Channel chan, int sz);




extern int Tcl_SetChannelOption (Tcl_Interp * interp,
                                Tcl_Channel chan, const char * optionName,
                                const char * newValue);




extern int Tcl_SetCommandInfo (Tcl_Interp * interp,
                                const char * cmdName,
                                const Tcl_CmdInfo * infoPtr);




extern void Tcl_SetErrno (int err);




extern void Tcl_SetErrorCode (Tcl_Interp * interp, ...);




extern void Tcl_SetMaxBlockTime (Tcl_Time * timePtr);




extern void Tcl_SetPanicProc (Tcl_PanicProc * panicProc);




extern int Tcl_SetRecursionLimit (Tcl_Interp * interp,
                                int depth);




extern void Tcl_SetResult (Tcl_Interp * interp, char * result,
                                Tcl_FreeProc * freeProc);




extern int Tcl_SetServiceMode (int mode);




extern void Tcl_SetObjErrorCode (Tcl_Interp * interp,
                                Tcl_Obj * errorObjPtr);




extern void Tcl_SetObjResult (Tcl_Interp * interp,
                                Tcl_Obj * resultObjPtr);




extern void Tcl_SetStdChannel (Tcl_Channel channel, int type);




extern char * Tcl_SetVar (Tcl_Interp * interp,
                                const char * varName, const char * newValue,
                                int flags);




extern char * Tcl_SetVar2 (Tcl_Interp * interp,
                                const char * part1, const char * part2,
                                const char * newValue, int flags);




extern char * Tcl_SignalId (int sig);




extern char * Tcl_SignalMsg (int sig);




extern void Tcl_SourceRCFile (Tcl_Interp * interp);




extern int Tcl_SplitList (Tcl_Interp * interp,
                                const char * listStr, int * argcPtr,
                                char *** argvPtr);




extern void Tcl_SplitPath (const char * path, int * argcPtr,
                                char *** argvPtr);




extern void Tcl_StaticPackage (Tcl_Interp * interp,
                                const char * pkgName,
                                Tcl_PackageInitProc * initProc,
                                Tcl_PackageInitProc * safeInitProc);




extern int Tcl_StringMatch (const char * str,
                                const char * pattern);




extern int Tcl_TellOld (Tcl_Channel chan);




extern int Tcl_TraceVar (Tcl_Interp * interp,
                                const char * varName, int flags,
                                Tcl_VarTraceProc * proc,
                                ClientData clientData);




extern int Tcl_TraceVar2 (Tcl_Interp * interp,
                                const char * part1, const char * part2,
                                int flags, Tcl_VarTraceProc * proc,
                                ClientData clientData);




extern char * Tcl_TranslateFileName (Tcl_Interp * interp,
                                const char * name, Tcl_DString * bufferPtr);




extern int Tcl_Ungets (Tcl_Channel chan, const char * str,
                                int len, int atHead);




extern void Tcl_UnlinkVar (Tcl_Interp * interp,
                                const char * varName);




extern int Tcl_UnregisterChannel (Tcl_Interp * interp,
                                Tcl_Channel chan);




extern int Tcl_UnsetVar (Tcl_Interp * interp,
                                const char * varName, int flags);




extern int Tcl_UnsetVar2 (Tcl_Interp * interp,
                                const char * part1, const char * part2,
                                int flags);




extern void Tcl_UntraceVar (Tcl_Interp * interp,
                                const char * varName, int flags,
                                Tcl_VarTraceProc * proc,
                                ClientData clientData);




extern void Tcl_UntraceVar2 (Tcl_Interp * interp,
                                const char * part1, const char * part2,
                                int flags, Tcl_VarTraceProc * proc,
                                ClientData clientData);




extern void Tcl_UpdateLinkedVar (Tcl_Interp * interp,
                                const char * varName);




extern int Tcl_UpVar (Tcl_Interp * interp,
                                const char * frameName, const char * varName,
                                const char * localName, int flags);




extern int Tcl_UpVar2 (Tcl_Interp * interp,
                                const char * frameName, const char * part1,
                                const char * part2, const char * localName,
                                int flags);




extern int Tcl_VarEval (Tcl_Interp * interp, ...);




extern ClientData Tcl_VarTraceInfo (Tcl_Interp * interp,
                                const char * varName, int flags,
                                Tcl_VarTraceProc * procPtr,
                                ClientData prevClientData);




extern ClientData Tcl_VarTraceInfo2 (Tcl_Interp * interp,
                                const char * part1, const char * part2,
                                int flags, Tcl_VarTraceProc * procPtr,
                                ClientData prevClientData);




extern int Tcl_Write (Tcl_Channel chan, const char * s,
                                int slen);




extern void Tcl_WrongNumArgs (Tcl_Interp * interp, int objc,
                                Tcl_Obj *const objv[], const char * message);




extern int Tcl_DumpActiveMemory (const char * fileName);




extern void Tcl_ValidateAllMemory (const char * file, int line);




extern void Tcl_AppendResultVA (Tcl_Interp * interp,
                                va_list argList);




extern void Tcl_AppendStringsToObjVA (Tcl_Obj * objPtr,
                                va_list argList);




extern char * Tcl_HashStats (Tcl_HashTable * tablePtr);




extern char * Tcl_ParseVar (Tcl_Interp * interp,
                                const char * start, char ** termPtr);




extern char * Tcl_PkgPresent (Tcl_Interp * interp,
                                const char * name, const char * version,
                                int exact);




extern char * Tcl_PkgPresentEx (Tcl_Interp * interp,
                                const char * name, const char * version,
                                int exact, ClientData * clientDataPtr);




extern int Tcl_PkgProvide (Tcl_Interp * interp,
                                const char * name, const char * version);




extern char * Tcl_PkgRequire (Tcl_Interp * interp,
                                const char * name, const char * version,
                                int exact);




extern void Tcl_SetErrorCodeVA (Tcl_Interp * interp,
                                va_list argList);




extern int Tcl_VarEvalVA (Tcl_Interp * interp, va_list argList);




extern Tcl_Pid Tcl_WaitPid (Tcl_Pid pid, int * statPtr, int options);




extern void Tcl_PanicVA (const char * format, va_list argList);




extern void Tcl_GetVersion (int * major, int * minor,
                                int * patchLevel, int * type);




extern void Tcl_InitMemory (Tcl_Interp * interp);




extern Tcl_Channel Tcl_StackChannel (Tcl_Interp * interp,
                                Tcl_ChannelType * typePtr,
                                ClientData instanceData, int mask,
                                Tcl_Channel prevChan);




extern int Tcl_UnstackChannel (Tcl_Interp * interp,
                                Tcl_Channel chan);




extern Tcl_Channel Tcl_GetStackedChannel (Tcl_Channel chan);




extern void Tcl_SetMainLoop (Tcl_MainLoopProc * proc);





extern void Tcl_AppendObjToObj (Tcl_Obj * objPtr,
                                Tcl_Obj * appendObjPtr);




extern Tcl_Encoding Tcl_CreateEncoding (const Tcl_EncodingType * typePtr);




extern void Tcl_CreateThreadExitHandler (Tcl_ExitProc * proc,
                                ClientData clientData);




extern void Tcl_DeleteThreadExitHandler (Tcl_ExitProc * proc,
                                ClientData clientData);




extern void Tcl_DiscardResult (Tcl_SavedResult * statePtr);




extern int Tcl_EvalEx (Tcl_Interp * interp, const char * script,
                                int numBytes, int flags);




extern int Tcl_EvalObjv (Tcl_Interp * interp, int objc,
                                Tcl_Obj *const objv[], int flags);




extern int Tcl_EvalObjEx (Tcl_Interp * interp, Tcl_Obj * objPtr,
                                int flags);




extern void Tcl_ExitThread (int status);




extern int Tcl_ExternalToUtf (Tcl_Interp * interp,
                                Tcl_Encoding encoding, const char * src,
                                int srcLen, int flags,
                                Tcl_EncodingState * statePtr, char * dst,
                                int dstLen, int * srcReadPtr,
                                int * dstWrotePtr, int * dstCharsPtr);




extern char * Tcl_ExternalToUtfDString (Tcl_Encoding encoding,
                                const char * src, int srcLen,
                                Tcl_DString * dsPtr);




extern void Tcl_FinalizeThread (void);




extern void Tcl_FinalizeNotifier (ClientData clientData);




extern void Tcl_FreeEncoding (Tcl_Encoding encoding);




extern Tcl_ThreadId Tcl_GetCurrentThread (void);




extern Tcl_Encoding Tcl_GetEncoding (Tcl_Interp * interp,
                                const char * name);




extern char * Tcl_GetEncodingName (Tcl_Encoding encoding);




extern void Tcl_GetEncodingNames (Tcl_Interp * interp);




extern int Tcl_GetIndexFromObjStruct (Tcl_Interp * interp,
                                Tcl_Obj * objPtr, const void * tablePtr,
                                int offset, const char * msg, int flags,
                                int * indexPtr);




extern void * Tcl_GetThreadData (Tcl_ThreadDataKey * keyPtr,
                                int size);




extern Tcl_Obj * Tcl_GetVar2Ex (Tcl_Interp * interp,
                                const char * part1, const char * part2,
                                int flags);




extern ClientData Tcl_InitNotifier (void);




extern void Tcl_MutexLock (Tcl_Mutex * mutexPtr);




extern void Tcl_MutexUnlock (Tcl_Mutex * mutexPtr);




extern void Tcl_ConditionNotify (Tcl_Condition * condPtr);




extern void Tcl_ConditionWait (Tcl_Condition * condPtr,
                                Tcl_Mutex * mutexPtr, Tcl_Time * timePtr);




extern int Tcl_NumUtfChars (const char * src, int length);




extern int Tcl_ReadChars (Tcl_Channel channel, Tcl_Obj * objPtr,
                                int charsToRead, int appendFlag);




extern void Tcl_RestoreResult (Tcl_Interp * interp,
                                Tcl_SavedResult * statePtr);




extern void Tcl_SaveResult (Tcl_Interp * interp,
                                Tcl_SavedResult * statePtr);




extern int Tcl_SetSystemEncoding (Tcl_Interp * interp,
                                const char * name);




extern Tcl_Obj * Tcl_SetVar2Ex (Tcl_Interp * interp,
                                const char * part1, const char * part2,
                                Tcl_Obj * newValuePtr, int flags);




extern void Tcl_ThreadAlert (Tcl_ThreadId threadId);




extern void Tcl_ThreadQueueEvent (Tcl_ThreadId threadId,
                                Tcl_Event* evPtr, Tcl_QueuePosition position);




extern Tcl_UniChar Tcl_UniCharAtIndex (const char * src, int index);




extern Tcl_UniChar Tcl_UniCharToLower (int ch);




extern Tcl_UniChar Tcl_UniCharToTitle (int ch);




extern Tcl_UniChar Tcl_UniCharToUpper (int ch);




extern int Tcl_UniCharToUtf (int ch, char * buf);




extern char * Tcl_UtfAtIndex (const char * src, int index);




extern int Tcl_UtfCharComplete (const char * src, int length);




extern int Tcl_UtfBackslash (const char * src, int * readPtr,
                                char * dst);




extern char * Tcl_UtfFindFirst (const char * src, int ch);




extern char * Tcl_UtfFindLast (const char * src, int ch);




extern char * Tcl_UtfNext (const char * src);




extern char * Tcl_UtfPrev (const char * src,
                                const char * start);




extern int Tcl_UtfToExternal (Tcl_Interp * interp,
                                Tcl_Encoding encoding, const char * src,
                                int srcLen, int flags,
                                Tcl_EncodingState * statePtr, char * dst,
                                int dstLen, int * srcReadPtr,
                                int * dstWrotePtr, int * dstCharsPtr);




extern char * Tcl_UtfToExternalDString (Tcl_Encoding encoding,
                                const char * src, int srcLen,
                                Tcl_DString * dsPtr);




extern int Tcl_UtfToLower (char * src);




extern int Tcl_UtfToTitle (char * src);




extern int Tcl_UtfToUniChar (const char * src,
                                Tcl_UniChar * chPtr);




extern int Tcl_UtfToUpper (char * src);




extern int Tcl_WriteChars (Tcl_Channel chan, const char * src,
                                int srcLen);




extern int Tcl_WriteObj (Tcl_Channel chan, Tcl_Obj * objPtr);




extern char * Tcl_GetString (Tcl_Obj * objPtr);




extern char * Tcl_GetDefaultEncodingDir (void);




extern void Tcl_SetDefaultEncodingDir (const char * path);




extern void Tcl_AlertNotifier (ClientData clientData);




extern void Tcl_ServiceModeHook (int mode);




extern int Tcl_UniCharIsAlnum (int ch);




extern int Tcl_UniCharIsAlpha (int ch);




extern int Tcl_UniCharIsDigit (int ch);




extern int Tcl_UniCharIsLower (int ch);




extern int Tcl_UniCharIsSpace (int ch);




extern int Tcl_UniCharIsUpper (int ch);




extern int Tcl_UniCharIsWordChar (int ch);




extern int Tcl_UniCharLen (const Tcl_UniChar * uniStr);




extern int Tcl_UniCharNcmp (const Tcl_UniChar * ucs,
                                const Tcl_UniChar * uct,
                                unsigned long numChars);




extern char * Tcl_UniCharToUtfDString (const Tcl_UniChar * uniStr,
                                int uniLength, Tcl_DString * dsPtr);




extern Tcl_UniChar * Tcl_UtfToUniCharDString (const char * src,
                                int length, Tcl_DString * dsPtr);




extern Tcl_RegExp Tcl_GetRegExpFromObj (Tcl_Interp * interp,
                                Tcl_Obj * patObj, int flags);




extern Tcl_Obj * Tcl_EvalTokens (Tcl_Interp * interp,
                                Tcl_Token * tokenPtr, int count);




extern void Tcl_FreeParse (Tcl_Parse * parsePtr);




extern void Tcl_LogCommandInfo (Tcl_Interp * interp,
                                const char * script, const char * command,
                                int length);




extern int Tcl_ParseBraces (Tcl_Interp * interp,
                                const char * start, int numBytes,
                                Tcl_Parse * parsePtr, int append,
                                char ** termPtr);




extern int Tcl_ParseCommand (Tcl_Interp * interp,
                                const char * start, int numBytes, int nested,
                                Tcl_Parse * parsePtr);




extern int Tcl_ParseExpr (Tcl_Interp * interp,
                                const char * start, int numBytes,
                                Tcl_Parse * parsePtr);




extern int Tcl_ParseQuotedString (Tcl_Interp * interp,
                                const char * start, int numBytes,
                                Tcl_Parse * parsePtr, int append,
                                char ** termPtr);




extern int Tcl_ParseVarName (Tcl_Interp * interp,
                                const char * start, int numBytes,
                                Tcl_Parse * parsePtr, int append);




extern char * Tcl_GetCwd (Tcl_Interp * interp,
                                Tcl_DString * cwdPtr);




extern int Tcl_Chdir (const char * dirName);




extern int Tcl_Access (const char * path, int mode);




extern int Tcl_Stat (const char * path, struct stat * bufPtr);




extern int Tcl_UtfNcmp (const char * s1, const char * s2,
                                unsigned long n);




extern int Tcl_UtfNcasecmp (const char * s1, const char * s2,
                                unsigned long n);




extern int Tcl_StringCaseMatch (const char * str,
                                const char * pattern, int nocase);




extern int Tcl_UniCharIsControl (int ch);




extern int Tcl_UniCharIsGraph (int ch);




extern int Tcl_UniCharIsPrint (int ch);




extern int Tcl_UniCharIsPunct (int ch);




extern int Tcl_RegExpExecObj (Tcl_Interp * interp,
                                Tcl_RegExp regexp, Tcl_Obj * textObj,
                                int offset, int nmatches, int flags);




extern void Tcl_RegExpGetInfo (Tcl_RegExp regexp,
                                Tcl_RegExpInfo * infoPtr);




extern Tcl_Obj * Tcl_NewUnicodeObj (const Tcl_UniChar * unicode,
                                int numChars);




extern void Tcl_SetUnicodeObj (Tcl_Obj * objPtr,
                                const Tcl_UniChar * unicode, int numChars);




extern int Tcl_GetCharLength (Tcl_Obj * objPtr);




extern Tcl_UniChar Tcl_GetUniChar (Tcl_Obj * objPtr, int index);




extern Tcl_UniChar * Tcl_GetUnicode (Tcl_Obj * objPtr);




extern Tcl_Obj * Tcl_GetRange (Tcl_Obj * objPtr, int first, int last);




extern void Tcl_AppendUnicodeToObj (Tcl_Obj * objPtr,
                                const Tcl_UniChar * unicode, int length);




extern int Tcl_RegExpMatchObj (Tcl_Interp * interp,
                                Tcl_Obj * textObj, Tcl_Obj * patternObj);




extern void Tcl_SetNotifier (Tcl_NotifierProcs * notifierProcPtr);




extern Tcl_Mutex * Tcl_GetAllocMutex (void);




extern int Tcl_GetChannelNames (Tcl_Interp * interp);




extern int Tcl_GetChannelNamesEx (Tcl_Interp * interp,
                                const char * pattern);




extern int Tcl_ProcObjCmd (ClientData clientData,
                                Tcl_Interp * interp, int objc,
                                Tcl_Obj *const objv[]);




extern void Tcl_ConditionFinalize (Tcl_Condition * condPtr);




extern void Tcl_MutexFinalize (Tcl_Mutex * mutex);




extern int Tcl_CreateThread (Tcl_ThreadId * idPtr,
                                Tcl_ThreadCreateProc proc,
                                ClientData clientData, int stackSize,
                                int flags);




extern int Tcl_ReadRaw (Tcl_Channel chan, char * dst,
                                int bytesToRead);




extern int Tcl_WriteRaw (Tcl_Channel chan, const char * src,
                                int srcLen);




extern Tcl_Channel Tcl_GetTopChannel (Tcl_Channel chan);




extern int Tcl_ChannelBuffered (Tcl_Channel chan);




extern char * Tcl_ChannelName (
                                const Tcl_ChannelType * chanTypePtr);




extern Tcl_ChannelTypeVersion Tcl_ChannelVersion (
                                const Tcl_ChannelType * chanTypePtr);




extern Tcl_DriverBlockModeProc * Tcl_ChannelBlockModeProc (
                                const Tcl_ChannelType * chanTypePtr);




extern Tcl_DriverCloseProc * Tcl_ChannelCloseProc (
                                const Tcl_ChannelType * chanTypePtr);




extern Tcl_DriverClose2Proc * Tcl_ChannelClose2Proc (
                                const Tcl_ChannelType * chanTypePtr);




extern Tcl_DriverInputProc * Tcl_ChannelInputProc (
                                const Tcl_ChannelType * chanTypePtr);




extern Tcl_DriverOutputProc * Tcl_ChannelOutputProc (
                                const Tcl_ChannelType * chanTypePtr);




extern Tcl_DriverSeekProc * Tcl_ChannelSeekProc (
                                const Tcl_ChannelType * chanTypePtr);




extern Tcl_DriverSetOptionProc * Tcl_ChannelSetOptionProc (
                                const Tcl_ChannelType * chanTypePtr);




extern Tcl_DriverGetOptionProc * Tcl_ChannelGetOptionProc (
                                const Tcl_ChannelType * chanTypePtr);




extern Tcl_DriverWatchProc * Tcl_ChannelWatchProc (
                                const Tcl_ChannelType * chanTypePtr);




extern Tcl_DriverGetHandleProc * Tcl_ChannelGetHandleProc (
                                const Tcl_ChannelType * chanTypePtr);




extern Tcl_DriverFlushProc * Tcl_ChannelFlushProc (
                                const Tcl_ChannelType * chanTypePtr);




extern Tcl_DriverHandlerProc * Tcl_ChannelHandlerProc (
                                const Tcl_ChannelType * chanTypePtr);




extern int Tcl_JoinThread (Tcl_ThreadId threadId, int* result);




extern int Tcl_IsChannelShared (Tcl_Channel channel);




extern int Tcl_IsChannelRegistered (Tcl_Interp* interp,
                                Tcl_Channel channel);




extern void Tcl_CutChannel (Tcl_Channel channel);




extern void Tcl_SpliceChannel (Tcl_Channel channel);




extern void Tcl_ClearChannelHandlers (Tcl_Channel channel);




extern int Tcl_IsChannelExisting (const char* channelName);




extern int Tcl_UniCharNcasecmp (const Tcl_UniChar * ucs,
                                const Tcl_UniChar * uct,
                                unsigned long numChars);




extern int Tcl_UniCharCaseMatch (const Tcl_UniChar * uniStr,
                                const Tcl_UniChar * uniPattern, int nocase);




extern Tcl_HashEntry * Tcl_FindHashEntry (Tcl_HashTable * tablePtr,
                                const char * key);




extern Tcl_HashEntry * Tcl_CreateHashEntry (Tcl_HashTable * tablePtr,
                                const char * key, int * newPtr);




extern void Tcl_InitCustomHashTable (Tcl_HashTable * tablePtr,
                                int keyType, Tcl_HashKeyType * typePtr);




extern void Tcl_InitObjHashTable (Tcl_HashTable * tablePtr);




extern ClientData Tcl_CommandTraceInfo (Tcl_Interp * interp,
                                const char * varName, int flags,
                                Tcl_CommandTraceProc * procPtr,
                                ClientData prevClientData);




extern int Tcl_TraceCommand (Tcl_Interp * interp,
                                const char * varName, int flags,
                                Tcl_CommandTraceProc * proc,
                                ClientData clientData);




extern void Tcl_UntraceCommand (Tcl_Interp * interp,
                                const char * varName, int flags,
                                Tcl_CommandTraceProc * proc,
                                ClientData clientData);




extern char * Tcl_AttemptAlloc (unsigned int size);




extern char * Tcl_AttemptDbCkalloc (unsigned int size,
                                const char * file, int line);




extern char * Tcl_AttemptRealloc (char * ptr, unsigned int size);




extern char * Tcl_AttemptDbCkrealloc (char * ptr,
                                unsigned int size, const char * file,
                                int line);




extern int Tcl_AttemptSetObjLength (Tcl_Obj * objPtr,
                                int length);




extern Tcl_ThreadId Tcl_GetChannelThread (Tcl_Channel channel);




extern Tcl_UniChar * Tcl_GetUnicodeFromObj (Tcl_Obj * objPtr,
                                int * lengthPtr);




extern int Tcl_GetMathFuncInfo (Tcl_Interp * interp,
                                const char * name, int * numArgsPtr,
                                Tcl_ValueType ** argTypesPtr,
                                Tcl_MathProc ** procPtr,
                                ClientData * clientDataPtr);




extern Tcl_Obj * Tcl_ListMathFuncs (Tcl_Interp * interp,
                                const char * pattern);




extern Tcl_Obj * Tcl_SubstObj (Tcl_Interp * interp, Tcl_Obj * objPtr,
                                int flags);




extern int Tcl_DetachChannel (Tcl_Interp* interp,
                                Tcl_Channel channel);




extern int Tcl_IsStandardChannel (Tcl_Channel channel);




extern int Tcl_FSCopyFile (Tcl_Obj * srcPathPtr,
                                Tcl_Obj * destPathPtr);




extern int Tcl_FSCopyDirectory (Tcl_Obj * srcPathPtr,
                                Tcl_Obj * destPathPtr, Tcl_Obj ** errorPtr);




extern int Tcl_FSCreateDirectory (Tcl_Obj * pathPtr);




extern int Tcl_FSDeleteFile (Tcl_Obj * pathPtr);




extern int Tcl_FSLoadFile (Tcl_Interp * interp,
                                Tcl_Obj * pathPtr, const char * sym1,
                                const char * sym2,
                                Tcl_PackageInitProc ** proc1Ptr,
                                Tcl_PackageInitProc ** proc2Ptr,
                                Tcl_LoadHandle * handlePtr,
                                Tcl_FSUnloadFileProc ** unloadProcPtr);




extern int Tcl_FSMatchInDirectory (Tcl_Interp * interp,
                                Tcl_Obj * result, Tcl_Obj * pathPtr,
                                const char * pattern,
                                Tcl_GlobTypeData * types);




extern Tcl_Obj * Tcl_FSLink (Tcl_Obj * pathPtr, Tcl_Obj * toPtr,
                                int linkAction);




extern int Tcl_FSRemoveDirectory (Tcl_Obj * pathPtr,
                                int recursive, Tcl_Obj ** errorPtr);




extern int Tcl_FSRenameFile (Tcl_Obj * srcPathPtr,
                                Tcl_Obj * destPathPtr);




extern int Tcl_FSLstat (Tcl_Obj * pathPtr, Tcl_StatBuf * buf);




extern int Tcl_FSUtime (Tcl_Obj * pathPtr,
                                struct utimbuf * tval);




extern int Tcl_FSFileAttrsGet (Tcl_Interp * interp, int index,
                                Tcl_Obj * pathPtr, Tcl_Obj ** objPtrRef);




extern int Tcl_FSFileAttrsSet (Tcl_Interp * interp, int index,
                                Tcl_Obj * pathPtr, Tcl_Obj * objPtr);




extern const char ** Tcl_FSFileAttrStrings (Tcl_Obj * pathPtr,
                                Tcl_Obj ** objPtrRef);




extern int Tcl_FSStat (Tcl_Obj * pathPtr, Tcl_StatBuf * buf);




extern int Tcl_FSAccess (Tcl_Obj * pathPtr, int mode);




extern Tcl_Channel Tcl_FSOpenFileChannel (Tcl_Interp * interp,
                                Tcl_Obj * pathPtr, const char * modeString,
                                int permissions);




extern Tcl_Obj* Tcl_FSGetCwd (Tcl_Interp * interp);




extern int Tcl_FSChdir (Tcl_Obj * pathPtr);




extern int Tcl_FSConvertToPathType (Tcl_Interp * interp,
                                Tcl_Obj * pathPtr);




extern Tcl_Obj* Tcl_FSJoinPath (Tcl_Obj * listObj, int elements);




extern Tcl_Obj* Tcl_FSSplitPath (Tcl_Obj* pathPtr, int * lenPtr);




extern int Tcl_FSEqualPaths (Tcl_Obj* firstPtr,
                                Tcl_Obj* secondPtr);




extern Tcl_Obj* Tcl_FSGetNormalizedPath (Tcl_Interp * interp,
                                Tcl_Obj* pathPtr);




extern Tcl_Obj* Tcl_FSJoinToPath (Tcl_Obj * pathPtr, int objc,
                                Tcl_Obj *const objv[]);




extern ClientData Tcl_FSGetInternalRep (Tcl_Obj* pathPtr,
                                Tcl_Filesystem * fsPtr);




extern Tcl_Obj* Tcl_FSGetTranslatedPath (Tcl_Interp * interp,
                                Tcl_Obj* pathPtr);




extern int Tcl_FSEvalFile (Tcl_Interp * interp,
                                Tcl_Obj * fileName);




extern Tcl_Obj* Tcl_FSNewNativePath (Tcl_Filesystem* fromFilesystem,
                                ClientData clientData);




extern const char* Tcl_FSGetNativePath (Tcl_Obj* pathPtr);




extern Tcl_Obj* Tcl_FSFileSystemInfo (Tcl_Obj* pathPtr);




extern Tcl_Obj* Tcl_FSPathSeparator (Tcl_Obj* pathPtr);




extern Tcl_Obj* Tcl_FSListVolumes (void);




extern int Tcl_FSRegister (ClientData clientData,
                                Tcl_Filesystem * fsPtr);




extern int Tcl_FSUnregister (Tcl_Filesystem * fsPtr);




extern ClientData Tcl_FSData (Tcl_Filesystem * fsPtr);




extern const char* Tcl_FSGetTranslatedStringPath (Tcl_Interp * interp,
                                Tcl_Obj* pathPtr);




extern Tcl_Filesystem* Tcl_FSGetFileSystemForPath (Tcl_Obj* pathPtr);




extern Tcl_PathType Tcl_FSGetPathType (Tcl_Obj * pathPtr);




extern int Tcl_OutputBuffered (Tcl_Channel chan);




extern void Tcl_FSMountsChanged (Tcl_Filesystem * fsPtr);




extern int Tcl_EvalTokensStandard (Tcl_Interp * interp,
                                Tcl_Token * tokenPtr, int count);




extern void Tcl_GetTime (Tcl_Time* timeBuf);




extern Tcl_Trace Tcl_CreateObjTrace (Tcl_Interp* interp, int level,
                                int flags, Tcl_CmdObjTraceProc* objProc,
                                ClientData clientData,
                                Tcl_CmdObjTraceDeleteProc* delProc);




extern int Tcl_GetCommandInfoFromToken (Tcl_Command token,
                                Tcl_CmdInfo* infoPtr);




extern int Tcl_SetCommandInfoFromToken (Tcl_Command token,
                                const Tcl_CmdInfo* infoPtr);




extern Tcl_Obj * Tcl_DbNewWideIntObj (Tcl_WideInt wideValue,
                                const char * file, int line);




extern int Tcl_GetWideIntFromObj (Tcl_Interp * interp,
                                Tcl_Obj * objPtr, Tcl_WideInt * widePtr);




extern Tcl_Obj * Tcl_NewWideIntObj (Tcl_WideInt wideValue);




extern void Tcl_SetWideIntObj (Tcl_Obj * objPtr,
                                Tcl_WideInt wideValue);




extern Tcl_StatBuf * Tcl_AllocStatBuf (void);




extern Tcl_WideInt Tcl_Seek (Tcl_Channel chan, Tcl_WideInt offset,
                                int mode);




extern Tcl_WideInt Tcl_Tell (Tcl_Channel chan);




extern Tcl_DriverWideSeekProc * Tcl_ChannelWideSeekProc (
                                const Tcl_ChannelType * chanTypePtr);




extern int Tcl_DictObjPut (Tcl_Interp * interp,
                                Tcl_Obj * dictPtr, Tcl_Obj * keyPtr,
                                Tcl_Obj * valuePtr);




extern int Tcl_DictObjGet (Tcl_Interp * interp,
                                Tcl_Obj * dictPtr, Tcl_Obj * keyPtr,
                                Tcl_Obj ** valuePtrPtr);




extern int Tcl_DictObjRemove (Tcl_Interp * interp,
                                Tcl_Obj * dictPtr, Tcl_Obj * keyPtr);




extern int Tcl_DictObjSize (Tcl_Interp * interp,
                                Tcl_Obj * dictPtr, int * sizePtr);




extern int Tcl_DictObjFirst (Tcl_Interp * interp,
                                Tcl_Obj * dictPtr,
                                Tcl_DictSearch * searchPtr,
                                Tcl_Obj ** keyPtrPtr, Tcl_Obj ** valuePtrPtr,
                                int * donePtr);




extern void Tcl_DictObjNext (Tcl_DictSearch * searchPtr,
                                Tcl_Obj ** keyPtrPtr, Tcl_Obj ** valuePtrPtr,
                                int * donePtr);




extern void Tcl_DictObjDone (Tcl_DictSearch * searchPtr);




extern int Tcl_DictObjPutKeyList (Tcl_Interp * interp,
                                Tcl_Obj * dictPtr, int keyc,
                                Tcl_Obj *const * keyv, Tcl_Obj * valuePtr);




extern int Tcl_DictObjRemoveKeyList (Tcl_Interp * interp,
                                Tcl_Obj * dictPtr, int keyc,
                                Tcl_Obj *const * keyv);




extern Tcl_Obj * Tcl_NewDictObj (void);




extern Tcl_Obj * Tcl_DbNewDictObj (const char * file, int line);




extern void Tcl_RegisterConfig (Tcl_Interp* interp,
                                const char* pkgName,
                                Tcl_Config* configuration,
                                const char* valEncoding);




extern Tcl_Namespace * Tcl_CreateNamespace (Tcl_Interp * interp,
                                const char * name, ClientData clientData,
                                Tcl_NamespaceDeleteProc * deleteProc);




extern void Tcl_DeleteNamespace (Tcl_Namespace * nsPtr);




extern int Tcl_AppendExportList (Tcl_Interp * interp,
                                Tcl_Namespace * nsPtr, Tcl_Obj * objPtr);




extern int Tcl_Export (Tcl_Interp * interp,
                                Tcl_Namespace * nsPtr, const char * pattern,
                                int resetListFirst);




extern int Tcl_Import (Tcl_Interp * interp,
                                Tcl_Namespace * nsPtr, const char * pattern,
                                int allowOverwrite);




extern int Tcl_ForgetImport (Tcl_Interp * interp,
                                Tcl_Namespace * nsPtr, const char * pattern);




extern Tcl_Namespace * Tcl_GetCurrentNamespace (Tcl_Interp * interp);




extern Tcl_Namespace * Tcl_GetGlobalNamespace (Tcl_Interp * interp);




extern Tcl_Namespace * Tcl_FindNamespace (Tcl_Interp * interp,
                                const char * name,
                                Tcl_Namespace * contextNsPtr, int flags);




extern Tcl_Command Tcl_FindCommand (Tcl_Interp * interp,
                                const char * name,
                                Tcl_Namespace * contextNsPtr, int flags);




extern Tcl_Command Tcl_GetCommandFromObj (Tcl_Interp * interp,
                                Tcl_Obj * objPtr);




extern void Tcl_GetCommandFullName (Tcl_Interp * interp,
                                Tcl_Command command, Tcl_Obj * objPtr);




extern int Tcl_FSEvalFileEx (Tcl_Interp * interp,
                                Tcl_Obj * fileName,
                                const char * encodingName);




extern Tcl_ExitProc * Tcl_SetExitProc (Tcl_ExitProc * proc);




extern void Tcl_LimitAddHandler (Tcl_Interp * interp, int type,
                                Tcl_LimitHandlerProc * handlerProc,
                                ClientData clientData,
                                Tcl_LimitHandlerDeleteProc * deleteProc);




extern void Tcl_LimitRemoveHandler (Tcl_Interp * interp,
                                int type, Tcl_LimitHandlerProc * handlerProc,
                                ClientData clientData);




extern int Tcl_LimitReady (Tcl_Interp * interp);




extern int Tcl_LimitCheck (Tcl_Interp * interp);




extern int Tcl_LimitExceeded (Tcl_Interp * interp);




extern void Tcl_LimitSetCommands (Tcl_Interp * interp,
                                int commandLimit);




extern void Tcl_LimitSetTime (Tcl_Interp * interp,
                                Tcl_Time * timeLimitPtr);




extern void Tcl_LimitSetGranularity (Tcl_Interp * interp,
                                int type, int granularity);




extern int Tcl_LimitTypeEnabled (Tcl_Interp * interp, int type);




extern int Tcl_LimitTypeExceeded (Tcl_Interp * interp, int type);




extern void Tcl_LimitTypeSet (Tcl_Interp * interp, int type);




extern void Tcl_LimitTypeReset (Tcl_Interp * interp, int type);




extern int Tcl_LimitGetCommands (Tcl_Interp * interp);




extern void Tcl_LimitGetTime (Tcl_Interp * interp,
                                Tcl_Time * timeLimitPtr);




extern int Tcl_LimitGetGranularity (Tcl_Interp * interp,
                                int type);




extern Tcl_InterpState Tcl_SaveInterpState (Tcl_Interp * interp, int status);




extern int Tcl_RestoreInterpState (Tcl_Interp * interp,
                                Tcl_InterpState state);




extern void Tcl_DiscardInterpState (Tcl_InterpState state);




extern int Tcl_SetReturnOptions (Tcl_Interp * interp,
                                Tcl_Obj * options);




extern Tcl_Obj * Tcl_GetReturnOptions (Tcl_Interp * interp,
                                int result);




extern int Tcl_IsEnsemble (Tcl_Command token);




extern Tcl_Command Tcl_CreateEnsemble (Tcl_Interp * interp,
                                const char * name,
                                Tcl_Namespace * namespacePtr, int flags);




extern Tcl_Command Tcl_FindEnsemble (Tcl_Interp * interp,
                                Tcl_Obj * cmdNameObj, int flags);




extern int Tcl_SetEnsembleSubcommandList (Tcl_Interp * interp,
                                Tcl_Command token, Tcl_Obj * subcmdList);




extern int Tcl_SetEnsembleMappingDict (Tcl_Interp * interp,
                                Tcl_Command token, Tcl_Obj * mapDict);




extern int Tcl_SetEnsembleUnknownHandler (Tcl_Interp * interp,
                                Tcl_Command token, Tcl_Obj * unknownList);




extern int Tcl_SetEnsembleFlags (Tcl_Interp * interp,
                                Tcl_Command token, int flags);




extern int Tcl_GetEnsembleSubcommandList (Tcl_Interp * interp,
                                Tcl_Command token, Tcl_Obj ** subcmdListPtr);




extern int Tcl_GetEnsembleMappingDict (Tcl_Interp * interp,
                                Tcl_Command token, Tcl_Obj ** mapDictPtr);




extern int Tcl_GetEnsembleUnknownHandler (Tcl_Interp * interp,
                                Tcl_Command token, Tcl_Obj ** unknownListPtr);




extern int Tcl_GetEnsembleFlags (Tcl_Interp * interp,
                                Tcl_Command token, int * flagsPtr);




extern int Tcl_GetEnsembleNamespace (Tcl_Interp * interp,
                                Tcl_Command token,
                                Tcl_Namespace ** namespacePtrPtr);




extern void Tcl_SetTimeProc (Tcl_GetTimeProc* getProc,
                                Tcl_ScaleTimeProc* scaleProc,
                                ClientData clientData);




extern void Tcl_QueryTimeProc (Tcl_GetTimeProc** getProc,
                                Tcl_ScaleTimeProc** scaleProc,
                                ClientData* clientData);




extern Tcl_DriverThreadActionProc * Tcl_ChannelThreadActionProc (
                                const Tcl_ChannelType * chanTypePtr);




extern Tcl_Obj* Tcl_NewBignumObj (mp_int* value);




extern Tcl_Obj* Tcl_DbNewBignumObj (mp_int* value, const char* file,
                                int line);




extern void Tcl_SetBignumObj (Tcl_Obj* obj, mp_int* value);




extern int Tcl_GetBignumFromObj (Tcl_Interp* interp,
                                Tcl_Obj* obj, mp_int* value);




extern int Tcl_TakeBignumFromObj (Tcl_Interp* interp,
                                Tcl_Obj* obj, mp_int* value);




extern int Tcl_TruncateChannel (Tcl_Channel chan,
                                Tcl_WideInt length);




extern Tcl_DriverTruncateProc * Tcl_ChannelTruncateProc (
                                const Tcl_ChannelType * chanTypePtr);




extern void Tcl_SetChannelErrorInterp (Tcl_Interp* interp,
                                Tcl_Obj* msg);




extern void Tcl_GetChannelErrorInterp (Tcl_Interp* interp,
                                Tcl_Obj** msg);




extern void Tcl_SetChannelError (Tcl_Channel chan, Tcl_Obj* msg);




extern void Tcl_GetChannelError (Tcl_Channel chan, Tcl_Obj** msg);




extern int Tcl_InitBignumFromDouble (Tcl_Interp* interp,
                                double initval, mp_int * toInit);




extern Tcl_Obj * Tcl_GetNamespaceUnknownHandler (Tcl_Interp * interp,
                                Tcl_Namespace * nsPtr);




extern int Tcl_SetNamespaceUnknownHandler (Tcl_Interp * interp,
                                Tcl_Namespace * nsPtr, Tcl_Obj * handlerPtr);




extern int Tcl_GetEncodingFromObj (Tcl_Interp* interp,
                                Tcl_Obj* objPtr, Tcl_Encoding* encodingPtr);




extern Tcl_Obj* Tcl_GetEncodingSearchPath (void);




extern int Tcl_SetEncodingSearchPath (Tcl_Obj* searchPath);




extern const char * Tcl_GetEncodingNameFromEnvironment (
                                Tcl_DString* bufPtr);




extern int Tcl_PkgRequireProc (Tcl_Interp * interp,
                                const char * name, int objc,
                                Tcl_Obj *const objv[],
                                ClientData * clientDataPtr);




extern void Tcl_AppendObjToErrorInfo (Tcl_Interp * interp,
                                Tcl_Obj * objPtr);




extern void Tcl_AppendLimitedToObj (Tcl_Obj * objPtr,
                                const char * bytes, int length, int limit,
                                const char * ellipsis);




extern Tcl_Obj * Tcl_Format (Tcl_Interp * interp, const char * format,
                                int objc, Tcl_Obj * const objv[]);




extern int Tcl_AppendFormatToObj (Tcl_Interp * interp,
                                Tcl_Obj * objPtr, const char * format,
                                int objc, Tcl_Obj * const objv[]);




extern Tcl_Obj * Tcl_ObjPrintf (const char * format, ...);




extern void Tcl_AppendPrintfToObj (Tcl_Obj * objPtr,
                                const char * format, ...);


typedef struct TclStubHooks {
    struct TclPlatStubs *tclPlatStubs;
    struct TclIntStubs *tclIntStubs;
    struct TclIntPlatStubs *tclIntPlatStubs;
} TclStubHooks;

typedef struct TclStubs {
    int magic;
    struct TclStubHooks *hooks;

    int (*tcl_PkgProvideEx) (Tcl_Interp* interp, const char* name, const char* version, ClientData clientData);
    char * (*tcl_PkgRequireEx) (Tcl_Interp * interp, const char * name, const char * version, int exact, ClientData * clientDataPtr);
    void (*tcl_Panic) (const char * format, ...);
    char * (*tcl_Alloc) (unsigned int size);
    void (*tcl_Free) (char * ptr);
    char * (*tcl_Realloc) (char * ptr, unsigned int size);
    char * (*tcl_DbCkalloc) (unsigned int size, const char * file, int line);
    int (*tcl_DbCkfree) (char * ptr, const char * file, int line);
    char * (*tcl_DbCkrealloc) (char * ptr, unsigned int size, const char * file, int line);

    void (*tcl_CreateFileHandler) (int fd, int mask, Tcl_FileProc * proc, ClientData clientData);
# 3534 "/tmp/t852/include/tclDecls.h"
    void (*tcl_DeleteFileHandler) (int fd);







    void (*tcl_SetTimer) (Tcl_Time * timePtr);
    void (*tcl_Sleep) (int ms);
    int (*tcl_WaitForEvent) (Tcl_Time * timePtr);
    int (*tcl_AppendAllObjTypes) (Tcl_Interp * interp, Tcl_Obj * objPtr);
    void (*tcl_AppendStringsToObj) (Tcl_Obj * objPtr, ...);
    void (*tcl_AppendToObj) (Tcl_Obj* objPtr, const char* bytes, int length);
    Tcl_Obj * (*tcl_ConcatObj) (int objc, Tcl_Obj *const objv[]);
    int (*tcl_ConvertToType) (Tcl_Interp * interp, Tcl_Obj * objPtr, Tcl_ObjType * typePtr);
    void (*tcl_DbDecrRefCount) (Tcl_Obj * objPtr, const char * file, int line);
    void (*tcl_DbIncrRefCount) (Tcl_Obj * objPtr, const char * file, int line);
    int (*tcl_DbIsShared) (Tcl_Obj * objPtr, const char * file, int line);
    Tcl_Obj * (*tcl_DbNewBooleanObj) (int boolValue, const char * file, int line);
    Tcl_Obj * (*tcl_DbNewByteArrayObj) (const unsigned char * bytes, int length, const char * file, int line);
    Tcl_Obj * (*tcl_DbNewDoubleObj) (double doubleValue, const char * file, int line);
    Tcl_Obj * (*tcl_DbNewListObj) (int objc, Tcl_Obj *const * objv, const char * file, int line);
    Tcl_Obj * (*tcl_DbNewLongObj) (long longValue, const char * file, int line);
    Tcl_Obj * (*tcl_DbNewObj) (const char * file, int line);
    Tcl_Obj * (*tcl_DbNewStringObj) (const char * bytes, int length, const char * file, int line);
    Tcl_Obj * (*tcl_DuplicateObj) (Tcl_Obj * objPtr);
    void (*tclFreeObj) (Tcl_Obj * objPtr);
    int (*tcl_GetBoolean) (Tcl_Interp * interp, const char * src, int * boolPtr);
    int (*tcl_GetBooleanFromObj) (Tcl_Interp * interp, Tcl_Obj * objPtr, int * boolPtr);
    unsigned char * (*tcl_GetByteArrayFromObj) (Tcl_Obj * objPtr, int * lengthPtr);
    int (*tcl_GetDouble) (Tcl_Interp * interp, const char * src, double * doublePtr);
    int (*tcl_GetDoubleFromObj) (Tcl_Interp * interp, Tcl_Obj * objPtr, double * doublePtr);
    int (*tcl_GetIndexFromObj) (Tcl_Interp * interp, Tcl_Obj * objPtr, char ** tablePtr, const char * msg, int flags, int * indexPtr);
    int (*tcl_GetInt) (Tcl_Interp * interp, const char * src, int * intPtr);
    int (*tcl_GetIntFromObj) (Tcl_Interp * interp, Tcl_Obj * objPtr, int * intPtr);
    int (*tcl_GetLongFromObj) (Tcl_Interp * interp, Tcl_Obj * objPtr, long * longPtr);
    Tcl_ObjType * (*tcl_GetObjType) (const char * typeName);
    char * (*tcl_GetStringFromObj) (Tcl_Obj * objPtr, int * lengthPtr);
    void (*tcl_InvalidateStringRep) (Tcl_Obj * objPtr);
    int (*tcl_ListObjAppendList) (Tcl_Interp * interp, Tcl_Obj * listPtr, Tcl_Obj * elemListPtr);
    int (*tcl_ListObjAppendElement) (Tcl_Interp * interp, Tcl_Obj * listPtr, Tcl_Obj * objPtr);
    int (*tcl_ListObjGetElements) (Tcl_Interp * interp, Tcl_Obj * listPtr, int * objcPtr, Tcl_Obj *** objvPtr);
    int (*tcl_ListObjIndex) (Tcl_Interp * interp, Tcl_Obj * listPtr, int index, Tcl_Obj ** objPtrPtr);
    int (*tcl_ListObjLength) (Tcl_Interp * interp, Tcl_Obj * listPtr, int * lengthPtr);
    int (*tcl_ListObjReplace) (Tcl_Interp * interp, Tcl_Obj * listPtr, int first, int count, int objc, Tcl_Obj *const objv[]);
    Tcl_Obj * (*tcl_NewBooleanObj) (int boolValue);
    Tcl_Obj * (*tcl_NewByteArrayObj) (const unsigned char* bytes, int length);
    Tcl_Obj * (*tcl_NewDoubleObj) (double doubleValue);
    Tcl_Obj * (*tcl_NewIntObj) (int intValue);
    Tcl_Obj * (*tcl_NewListObj) (int objc, Tcl_Obj *const objv[]);
    Tcl_Obj * (*tcl_NewLongObj) (long longValue);
    Tcl_Obj * (*tcl_NewObj) (void);
    Tcl_Obj * (*tcl_NewStringObj) (const char * bytes, int length);
    void (*tcl_SetBooleanObj) (Tcl_Obj * objPtr, int boolValue);
    unsigned char * (*tcl_SetByteArrayLength) (Tcl_Obj * objPtr, int length);
    void (*tcl_SetByteArrayObj) (Tcl_Obj * objPtr, const unsigned char * bytes, int length);
    void (*tcl_SetDoubleObj) (Tcl_Obj * objPtr, double doubleValue);
    void (*tcl_SetIntObj) (Tcl_Obj * objPtr, int intValue);
    void (*tcl_SetListObj) (Tcl_Obj * objPtr, int objc, Tcl_Obj *const objv[]);
    void (*tcl_SetLongObj) (Tcl_Obj * objPtr, long longValue);
    void (*tcl_SetObjLength) (Tcl_Obj * objPtr, int length);
    void (*tcl_SetStringObj) (Tcl_Obj* objPtr, const char* bytes, int length);
    void (*tcl_AddErrorInfo) (Tcl_Interp * interp, const char * message);
    void (*tcl_AddObjErrorInfo) (Tcl_Interp * interp, const char * message, int length);
    void (*tcl_AllowExceptions) (Tcl_Interp * interp);
    void (*tcl_AppendElement) (Tcl_Interp * interp, const char * element);
    void (*tcl_AppendResult) (Tcl_Interp * interp, ...);
    Tcl_AsyncHandler (*tcl_AsyncCreate) (Tcl_AsyncProc * proc, ClientData clientData);
    void (*tcl_AsyncDelete) (Tcl_AsyncHandler async);
    int (*tcl_AsyncInvoke) (Tcl_Interp * interp, int code);
    void (*tcl_AsyncMark) (Tcl_AsyncHandler async);
    int (*tcl_AsyncReady) (void);
    void (*tcl_BackgroundError) (Tcl_Interp * interp);
    char (*tcl_Backslash) (const char * src, int * readPtr);
    int (*tcl_BadChannelOption) (Tcl_Interp * interp, const char * optionName, const char * optionList);
    void (*tcl_CallWhenDeleted) (Tcl_Interp * interp, Tcl_InterpDeleteProc * proc, ClientData clientData);
    void (*tcl_CancelIdleCall) (Tcl_IdleProc * idleProc, ClientData clientData);
    int (*tcl_Close) (Tcl_Interp * interp, Tcl_Channel chan);
    int (*tcl_CommandComplete) (const char * cmd);
    char * (*tcl_Concat) (int argc, char * const * argv);
    int (*tcl_ConvertElement) (const char * src, char * dst, int flags);
    int (*tcl_ConvertCountedElement) (const char * src, int length, char * dst, int flags);
    int (*tcl_CreateAlias) (Tcl_Interp * slave, const char * slaveCmd, Tcl_Interp * target, const char * targetCmd, int argc, char * const * argv);
    int (*tcl_CreateAliasObj) (Tcl_Interp * slave, const char * slaveCmd, Tcl_Interp * target, const char * targetCmd, int objc, Tcl_Obj *const objv[]);
    Tcl_Channel (*tcl_CreateChannel) (Tcl_ChannelType * typePtr, const char * chanName, ClientData instanceData, int mask);
    void (*tcl_CreateChannelHandler) (Tcl_Channel chan, int mask, Tcl_ChannelProc * proc, ClientData clientData);
    void (*tcl_CreateCloseHandler) (Tcl_Channel chan, Tcl_CloseProc * proc, ClientData clientData);
    Tcl_Command (*tcl_CreateCommand) (Tcl_Interp * interp, const char * cmdName, Tcl_CmdProc * proc, ClientData clientData, Tcl_CmdDeleteProc * deleteProc);
    void (*tcl_CreateEventSource) (Tcl_EventSetupProc * setupProc, Tcl_EventCheckProc * checkProc, ClientData clientData);
    void (*tcl_CreateExitHandler) (Tcl_ExitProc * proc, ClientData clientData);
    Tcl_Interp * (*tcl_CreateInterp) (void);
    void (*tcl_CreateMathFunc) (Tcl_Interp * interp, const char * name, int numArgs, Tcl_ValueType * argTypes, Tcl_MathProc * proc, ClientData clientData);
    Tcl_Command (*tcl_CreateObjCommand) (Tcl_Interp * interp, const char * cmdName, Tcl_ObjCmdProc * proc, ClientData clientData, Tcl_CmdDeleteProc * deleteProc);
    Tcl_Interp * (*tcl_CreateSlave) (Tcl_Interp * interp, const char * slaveName, int isSafe);
    Tcl_TimerToken (*tcl_CreateTimerHandler) (int milliseconds, Tcl_TimerProc * proc, ClientData clientData);
    Tcl_Trace (*tcl_CreateTrace) (Tcl_Interp * interp, int level, Tcl_CmdTraceProc * proc, ClientData clientData);
    void (*tcl_DeleteAssocData) (Tcl_Interp * interp, const char * name);
    void (*tcl_DeleteChannelHandler) (Tcl_Channel chan, Tcl_ChannelProc * proc, ClientData clientData);
    void (*tcl_DeleteCloseHandler) (Tcl_Channel chan, Tcl_CloseProc * proc, ClientData clientData);
    int (*tcl_DeleteCommand) (Tcl_Interp * interp, const char * cmdName);
    int (*tcl_DeleteCommandFromToken) (Tcl_Interp * interp, Tcl_Command command);
    void (*tcl_DeleteEvents) (Tcl_EventDeleteProc * proc, ClientData clientData);
    void (*tcl_DeleteEventSource) (Tcl_EventSetupProc * setupProc, Tcl_EventCheckProc * checkProc, ClientData clientData);
    void (*tcl_DeleteExitHandler) (Tcl_ExitProc * proc, ClientData clientData);
    void (*tcl_DeleteHashEntry) (Tcl_HashEntry * entryPtr);
    void (*tcl_DeleteHashTable) (Tcl_HashTable * tablePtr);
    void (*tcl_DeleteInterp) (Tcl_Interp * interp);

    void (*tcl_DetachPids) (int numPids, Tcl_Pid * pidPtr);







    void (*tcl_DeleteTimerHandler) (Tcl_TimerToken token);
    void (*tcl_DeleteTrace) (Tcl_Interp * interp, Tcl_Trace trace);
    void (*tcl_DontCallWhenDeleted) (Tcl_Interp * interp, Tcl_InterpDeleteProc * proc, ClientData clientData);
    int (*tcl_DoOneEvent) (int flags);
    void (*tcl_DoWhenIdle) (Tcl_IdleProc * proc, ClientData clientData);
    char * (*tcl_DStringAppend) (Tcl_DString * dsPtr, const char * bytes, int length);
    char * (*tcl_DStringAppendElement) (Tcl_DString * dsPtr, const char * element);
    void (*tcl_DStringEndSublist) (Tcl_DString * dsPtr);
    void (*tcl_DStringFree) (Tcl_DString * dsPtr);
    void (*tcl_DStringGetResult) (Tcl_Interp * interp, Tcl_DString * dsPtr);
    void (*tcl_DStringInit) (Tcl_DString * dsPtr);
    void (*tcl_DStringResult) (Tcl_Interp * interp, Tcl_DString * dsPtr);
    void (*tcl_DStringSetLength) (Tcl_DString * dsPtr, int length);
    void (*tcl_DStringStartSublist) (Tcl_DString * dsPtr);
    int (*tcl_Eof) (Tcl_Channel chan);
    char * (*tcl_ErrnoId) (void);
    char * (*tcl_ErrnoMsg) (int err);
    int (*tcl_Eval) (Tcl_Interp * interp, const char * script);
    int (*tcl_EvalFile) (Tcl_Interp * interp, const char * fileName);
    int (*tcl_EvalObj) (Tcl_Interp * interp, Tcl_Obj * objPtr);
    void (*tcl_EventuallyFree) (ClientData clientData, Tcl_FreeProc * freeProc);
    void (*tcl_Exit) (int status);
    int (*tcl_ExposeCommand) (Tcl_Interp * interp, const char * hiddenCmdToken, const char * cmdName);
    int (*tcl_ExprBoolean) (Tcl_Interp * interp, const char * expr, int * ptr);
    int (*tcl_ExprBooleanObj) (Tcl_Interp * interp, Tcl_Obj * objPtr, int * ptr);
    int (*tcl_ExprDouble) (Tcl_Interp * interp, const char * expr, double * ptr);
    int (*tcl_ExprDoubleObj) (Tcl_Interp * interp, Tcl_Obj * objPtr, double * ptr);
    int (*tcl_ExprLong) (Tcl_Interp * interp, const char * expr, long * ptr);
    int (*tcl_ExprLongObj) (Tcl_Interp * interp, Tcl_Obj * objPtr, long * ptr);
    int (*tcl_ExprObj) (Tcl_Interp * interp, Tcl_Obj * objPtr, Tcl_Obj ** resultPtrPtr);
    int (*tcl_ExprString) (Tcl_Interp * interp, const char * expr);
    void (*tcl_Finalize) (void);
    void (*tcl_FindExecutable) (const char * argv0);
    Tcl_HashEntry * (*tcl_FirstHashEntry) (Tcl_HashTable * tablePtr, Tcl_HashSearch * searchPtr);
    int (*tcl_Flush) (Tcl_Channel chan);
    void (*tcl_FreeResult) (Tcl_Interp * interp);
    int (*tcl_GetAlias) (Tcl_Interp * interp, const char * slaveCmd, Tcl_Interp ** targetInterpPtr, char ** targetCmdPtr, int * argcPtr, char *** argvPtr);
    int (*tcl_GetAliasObj) (Tcl_Interp * interp, const char * slaveCmd, Tcl_Interp ** targetInterpPtr, char ** targetCmdPtr, int * objcPtr, Tcl_Obj *** objv);
    ClientData (*tcl_GetAssocData) (Tcl_Interp * interp, const char * name, Tcl_InterpDeleteProc ** procPtr);
    Tcl_Channel (*tcl_GetChannel) (Tcl_Interp * interp, const char * chanName, int * modePtr);
    int (*tcl_GetChannelBufferSize) (Tcl_Channel chan);
    int (*tcl_GetChannelHandle) (Tcl_Channel chan, int direction, ClientData * handlePtr);
    ClientData (*tcl_GetChannelInstanceData) (Tcl_Channel chan);
    int (*tcl_GetChannelMode) (Tcl_Channel chan);
    char * (*tcl_GetChannelName) (Tcl_Channel chan);
    int (*tcl_GetChannelOption) (Tcl_Interp * interp, Tcl_Channel chan, const char * optionName, Tcl_DString * dsPtr);
    Tcl_ChannelType * (*tcl_GetChannelType) (Tcl_Channel chan);
    int (*tcl_GetCommandInfo) (Tcl_Interp * interp, const char * cmdName, Tcl_CmdInfo * infoPtr);
    char * (*tcl_GetCommandName) (Tcl_Interp * interp, Tcl_Command command);
    int (*tcl_GetErrno) (void);
    char * (*tcl_GetHostName) (void);
    int (*tcl_GetInterpPath) (Tcl_Interp * askInterp, Tcl_Interp * slaveInterp);
    Tcl_Interp * (*tcl_GetMaster) (Tcl_Interp * interp);
    const char * (*tcl_GetNameOfExecutable) (void);
    Tcl_Obj * (*tcl_GetObjResult) (Tcl_Interp * interp);

    int (*tcl_GetOpenFile) (Tcl_Interp * interp, const char * chanID, int forWriting, int checkUsage, ClientData * filePtr);







    Tcl_PathType (*tcl_GetPathType) (const char * path);
    int (*tcl_Gets) (Tcl_Channel chan, Tcl_DString * dsPtr);
    int (*tcl_GetsObj) (Tcl_Channel chan, Tcl_Obj * objPtr);
    int (*tcl_GetServiceMode) (void);
    Tcl_Interp * (*tcl_GetSlave) (Tcl_Interp * interp, const char * slaveName);
    Tcl_Channel (*tcl_GetStdChannel) (int type);
    char * (*tcl_GetStringResult) (Tcl_Interp * interp);
    char * (*tcl_GetVar) (Tcl_Interp * interp, const char * varName, int flags);
    char * (*tcl_GetVar2) (Tcl_Interp * interp, const char * part1, const char * part2, int flags);
    int (*tcl_GlobalEval) (Tcl_Interp * interp, const char * command);
    int (*tcl_GlobalEvalObj) (Tcl_Interp * interp, Tcl_Obj * objPtr);
    int (*tcl_HideCommand) (Tcl_Interp * interp, const char * cmdName, const char * hiddenCmdToken);
    int (*tcl_Init) (Tcl_Interp * interp);
    void (*tcl_InitHashTable) (Tcl_HashTable * tablePtr, int keyType);
    int (*tcl_InputBlocked) (Tcl_Channel chan);
    int (*tcl_InputBuffered) (Tcl_Channel chan);
    int (*tcl_InterpDeleted) (Tcl_Interp * interp);
    int (*tcl_IsSafe) (Tcl_Interp * interp);
    char * (*tcl_JoinPath) (int argc, char * const * argv, Tcl_DString * resultPtr);
    int (*tcl_LinkVar) (Tcl_Interp * interp, const char * varName, char * addr, int type);
    void *reserved188;
    Tcl_Channel (*tcl_MakeFileChannel) (ClientData handle, int mode);
    int (*tcl_MakeSafe) (Tcl_Interp * interp);
    Tcl_Channel (*tcl_MakeTcpClientChannel) (ClientData tcpSocket);
    char * (*tcl_Merge) (int argc, char * const * argv);
    Tcl_HashEntry * (*tcl_NextHashEntry) (Tcl_HashSearch * searchPtr);
    void (*tcl_NotifyChannel) (Tcl_Channel channel, int mask);
    Tcl_Obj * (*tcl_ObjGetVar2) (Tcl_Interp * interp, Tcl_Obj * part1Ptr, Tcl_Obj * part2Ptr, int flags);
    Tcl_Obj * (*tcl_ObjSetVar2) (Tcl_Interp * interp, Tcl_Obj * part1Ptr, Tcl_Obj * part2Ptr, Tcl_Obj * newValuePtr, int flags);

    Tcl_Channel (*tcl_OpenCommandChannel) (Tcl_Interp * interp, int argc, char ** argv, int flags);







    Tcl_Channel (*tcl_OpenFileChannel) (Tcl_Interp * interp, const char * fileName, const char * modeString, int permissions);
    Tcl_Channel (*tcl_OpenTcpClient) (Tcl_Interp * interp, int port, const char * address, const char * myaddr, int myport, int async);
    Tcl_Channel (*tcl_OpenTcpServer) (Tcl_Interp * interp, int port, const char * host, Tcl_TcpAcceptProc * acceptProc, ClientData callbackData);
    void (*tcl_Preserve) (ClientData data);
    void (*tcl_PrintDouble) (Tcl_Interp * interp, double value, char * dst);
    int (*tcl_PutEnv) (const char * assignment);
    char * (*tcl_PosixError) (Tcl_Interp * interp);
    void (*tcl_QueueEvent) (Tcl_Event * evPtr, Tcl_QueuePosition position);
    int (*tcl_Read) (Tcl_Channel chan, char * bufPtr, int toRead);

    void (*tcl_ReapDetachedProcs) (void);







    int (*tcl_RecordAndEval) (Tcl_Interp * interp, const char * cmd, int flags);
    int (*tcl_RecordAndEvalObj) (Tcl_Interp * interp, Tcl_Obj * cmdPtr, int flags);
    void (*tcl_RegisterChannel) (Tcl_Interp * interp, Tcl_Channel chan);
    void (*tcl_RegisterObjType) (Tcl_ObjType * typePtr);
    Tcl_RegExp (*tcl_RegExpCompile) (Tcl_Interp * interp, const char * pattern);
    int (*tcl_RegExpExec) (Tcl_Interp * interp, Tcl_RegExp regexp, const char * text, const char * start);
    int (*tcl_RegExpMatch) (Tcl_Interp * interp, const char * text, const char * pattern);
    void (*tcl_RegExpRange) (Tcl_RegExp regexp, int index, char ** startPtr, char ** endPtr);
    void (*tcl_Release) (ClientData clientData);
    void (*tcl_ResetResult) (Tcl_Interp * interp);
    int (*tcl_ScanElement) (const char * str, int * flagPtr);
    int (*tcl_ScanCountedElement) (const char * str, int length, int * flagPtr);
    int (*tcl_SeekOld) (Tcl_Channel chan, int offset, int mode);
    int (*tcl_ServiceAll) (void);
    int (*tcl_ServiceEvent) (int flags);
    void (*tcl_SetAssocData) (Tcl_Interp * interp, const char * name, Tcl_InterpDeleteProc * proc, ClientData clientData);
    void (*tcl_SetChannelBufferSize) (Tcl_Channel chan, int sz);
    int (*tcl_SetChannelOption) (Tcl_Interp * interp, Tcl_Channel chan, const char * optionName, const char * newValue);
    int (*tcl_SetCommandInfo) (Tcl_Interp * interp, const char * cmdName, const Tcl_CmdInfo * infoPtr);
    void (*tcl_SetErrno) (int err);
    void (*tcl_SetErrorCode) (Tcl_Interp * interp, ...);
    void (*tcl_SetMaxBlockTime) (Tcl_Time * timePtr);
    void (*tcl_SetPanicProc) (Tcl_PanicProc * panicProc);
    int (*tcl_SetRecursionLimit) (Tcl_Interp * interp, int depth);
    void (*tcl_SetResult) (Tcl_Interp * interp, char * result, Tcl_FreeProc * freeProc);
    int (*tcl_SetServiceMode) (int mode);
    void (*tcl_SetObjErrorCode) (Tcl_Interp * interp, Tcl_Obj * errorObjPtr);
    void (*tcl_SetObjResult) (Tcl_Interp * interp, Tcl_Obj * resultObjPtr);
    void (*tcl_SetStdChannel) (Tcl_Channel channel, int type);
    char * (*tcl_SetVar) (Tcl_Interp * interp, const char * varName, const char * newValue, int flags);
    char * (*tcl_SetVar2) (Tcl_Interp * interp, const char * part1, const char * part2, const char * newValue, int flags);
    char * (*tcl_SignalId) (int sig);
    char * (*tcl_SignalMsg) (int sig);
    void (*tcl_SourceRCFile) (Tcl_Interp * interp);
    int (*tcl_SplitList) (Tcl_Interp * interp, const char * listStr, int * argcPtr, char *** argvPtr);
    void (*tcl_SplitPath) (const char * path, int * argcPtr, char *** argvPtr);
    void (*tcl_StaticPackage) (Tcl_Interp * interp, const char * pkgName, Tcl_PackageInitProc * initProc, Tcl_PackageInitProc * safeInitProc);
    int (*tcl_StringMatch) (const char * str, const char * pattern);
    int (*tcl_TellOld) (Tcl_Channel chan);
    int (*tcl_TraceVar) (Tcl_Interp * interp, const char * varName, int flags, Tcl_VarTraceProc * proc, ClientData clientData);
    int (*tcl_TraceVar2) (Tcl_Interp * interp, const char * part1, const char * part2, int flags, Tcl_VarTraceProc * proc, ClientData clientData);
    char * (*tcl_TranslateFileName) (Tcl_Interp * interp, const char * name, Tcl_DString * bufferPtr);
    int (*tcl_Ungets) (Tcl_Channel chan, const char * str, int len, int atHead);
    void (*tcl_UnlinkVar) (Tcl_Interp * interp, const char * varName);
    int (*tcl_UnregisterChannel) (Tcl_Interp * interp, Tcl_Channel chan);
    int (*tcl_UnsetVar) (Tcl_Interp * interp, const char * varName, int flags);
    int (*tcl_UnsetVar2) (Tcl_Interp * interp, const char * part1, const char * part2, int flags);
    void (*tcl_UntraceVar) (Tcl_Interp * interp, const char * varName, int flags, Tcl_VarTraceProc * proc, ClientData clientData);
    void (*tcl_UntraceVar2) (Tcl_Interp * interp, const char * part1, const char * part2, int flags, Tcl_VarTraceProc * proc, ClientData clientData);
    void (*tcl_UpdateLinkedVar) (Tcl_Interp * interp, const char * varName);
    int (*tcl_UpVar) (Tcl_Interp * interp, const char * frameName, const char * varName, const char * localName, int flags);
    int (*tcl_UpVar2) (Tcl_Interp * interp, const char * frameName, const char * part1, const char * part2, const char * localName, int flags);
    int (*tcl_VarEval) (Tcl_Interp * interp, ...);
    ClientData (*tcl_VarTraceInfo) (Tcl_Interp * interp, const char * varName, int flags, Tcl_VarTraceProc * procPtr, ClientData prevClientData);
    ClientData (*tcl_VarTraceInfo2) (Tcl_Interp * interp, const char * part1, const char * part2, int flags, Tcl_VarTraceProc * procPtr, ClientData prevClientData);
    int (*tcl_Write) (Tcl_Channel chan, const char * s, int slen);
    void (*tcl_WrongNumArgs) (Tcl_Interp * interp, int objc, Tcl_Obj *const objv[], const char * message);
    int (*tcl_DumpActiveMemory) (const char * fileName);
    void (*tcl_ValidateAllMemory) (const char * file, int line);
    void (*tcl_AppendResultVA) (Tcl_Interp * interp, va_list argList);
    void (*tcl_AppendStringsToObjVA) (Tcl_Obj * objPtr, va_list argList);
    char * (*tcl_HashStats) (Tcl_HashTable * tablePtr);
    char * (*tcl_ParseVar) (Tcl_Interp * interp, const char * start, char ** termPtr);
    char * (*tcl_PkgPresent) (Tcl_Interp * interp, const char * name, const char * version, int exact);
    char * (*tcl_PkgPresentEx) (Tcl_Interp * interp, const char * name, const char * version, int exact, ClientData * clientDataPtr);
    int (*tcl_PkgProvide) (Tcl_Interp * interp, const char * name, const char * version);
    char * (*tcl_PkgRequire) (Tcl_Interp * interp, const char * name, const char * version, int exact);
    void (*tcl_SetErrorCodeVA) (Tcl_Interp * interp, va_list argList);
    int (*tcl_VarEvalVA) (Tcl_Interp * interp, va_list argList);
    Tcl_Pid (*tcl_WaitPid) (Tcl_Pid pid, int * statPtr, int options);
    void (*tcl_PanicVA) (const char * format, va_list argList);
    void (*tcl_GetVersion) (int * major, int * minor, int * patchLevel, int * type);
    void (*tcl_InitMemory) (Tcl_Interp * interp);
    Tcl_Channel (*tcl_StackChannel) (Tcl_Interp * interp, Tcl_ChannelType * typePtr, ClientData instanceData, int mask, Tcl_Channel prevChan);
    int (*tcl_UnstackChannel) (Tcl_Interp * interp, Tcl_Channel chan);
    Tcl_Channel (*tcl_GetStackedChannel) (Tcl_Channel chan);
    void (*tcl_SetMainLoop) (Tcl_MainLoopProc * proc);
    void *reserved285;
    void (*tcl_AppendObjToObj) (Tcl_Obj * objPtr, Tcl_Obj * appendObjPtr);
    Tcl_Encoding (*tcl_CreateEncoding) (const Tcl_EncodingType * typePtr);
    void (*tcl_CreateThreadExitHandler) (Tcl_ExitProc * proc, ClientData clientData);
    void (*tcl_DeleteThreadExitHandler) (Tcl_ExitProc * proc, ClientData clientData);
    void (*tcl_DiscardResult) (Tcl_SavedResult * statePtr);
    int (*tcl_EvalEx) (Tcl_Interp * interp, const char * script, int numBytes, int flags);
    int (*tcl_EvalObjv) (Tcl_Interp * interp, int objc, Tcl_Obj *const objv[], int flags);
    int (*tcl_EvalObjEx) (Tcl_Interp * interp, Tcl_Obj * objPtr, int flags);
    void (*tcl_ExitThread) (int status);
    int (*tcl_ExternalToUtf) (Tcl_Interp * interp, Tcl_Encoding encoding, const char * src, int srcLen, int flags, Tcl_EncodingState * statePtr, char * dst, int dstLen, int * srcReadPtr, int * dstWrotePtr, int * dstCharsPtr);
    char * (*tcl_ExternalToUtfDString) (Tcl_Encoding encoding, const char * src, int srcLen, Tcl_DString * dsPtr);
    void (*tcl_FinalizeThread) (void);
    void (*tcl_FinalizeNotifier) (ClientData clientData);
    void (*tcl_FreeEncoding) (Tcl_Encoding encoding);
    Tcl_ThreadId (*tcl_GetCurrentThread) (void);
    Tcl_Encoding (*tcl_GetEncoding) (Tcl_Interp * interp, const char * name);
    char * (*tcl_GetEncodingName) (Tcl_Encoding encoding);
    void (*tcl_GetEncodingNames) (Tcl_Interp * interp);
    int (*tcl_GetIndexFromObjStruct) (Tcl_Interp * interp, Tcl_Obj * objPtr, const void * tablePtr, int offset, const char * msg, int flags, int * indexPtr);
    void * (*tcl_GetThreadData) (Tcl_ThreadDataKey * keyPtr, int size);
    Tcl_Obj * (*tcl_GetVar2Ex) (Tcl_Interp * interp, const char * part1, const char * part2, int flags);
    ClientData (*tcl_InitNotifier) (void);
    void (*tcl_MutexLock) (Tcl_Mutex * mutexPtr);
    void (*tcl_MutexUnlock) (Tcl_Mutex * mutexPtr);
    void (*tcl_ConditionNotify) (Tcl_Condition * condPtr);
    void (*tcl_ConditionWait) (Tcl_Condition * condPtr, Tcl_Mutex * mutexPtr, Tcl_Time * timePtr);
    int (*tcl_NumUtfChars) (const char * src, int length);
    int (*tcl_ReadChars) (Tcl_Channel channel, Tcl_Obj * objPtr, int charsToRead, int appendFlag);
    void (*tcl_RestoreResult) (Tcl_Interp * interp, Tcl_SavedResult * statePtr);
    void (*tcl_SaveResult) (Tcl_Interp * interp, Tcl_SavedResult * statePtr);
    int (*tcl_SetSystemEncoding) (Tcl_Interp * interp, const char * name);
    Tcl_Obj * (*tcl_SetVar2Ex) (Tcl_Interp * interp, const char * part1, const char * part2, Tcl_Obj * newValuePtr, int flags);
    void (*tcl_ThreadAlert) (Tcl_ThreadId threadId);
    void (*tcl_ThreadQueueEvent) (Tcl_ThreadId threadId, Tcl_Event* evPtr, Tcl_QueuePosition position);
    Tcl_UniChar (*tcl_UniCharAtIndex) (const char * src, int index);
    Tcl_UniChar (*tcl_UniCharToLower) (int ch);
    Tcl_UniChar (*tcl_UniCharToTitle) (int ch);
    Tcl_UniChar (*tcl_UniCharToUpper) (int ch);
    int (*tcl_UniCharToUtf) (int ch, char * buf);
    char * (*tcl_UtfAtIndex) (const char * src, int index);
    int (*tcl_UtfCharComplete) (const char * src, int length);
    int (*tcl_UtfBackslash) (const char * src, int * readPtr, char * dst);
    char * (*tcl_UtfFindFirst) (const char * src, int ch);
    char * (*tcl_UtfFindLast) (const char * src, int ch);
    char * (*tcl_UtfNext) (const char * src);
    char * (*tcl_UtfPrev) (const char * src, const char * start);
    int (*tcl_UtfToExternal) (Tcl_Interp * interp, Tcl_Encoding encoding, const char * src, int srcLen, int flags, Tcl_EncodingState * statePtr, char * dst, int dstLen, int * srcReadPtr, int * dstWrotePtr, int * dstCharsPtr);
    char * (*tcl_UtfToExternalDString) (Tcl_Encoding encoding, const char * src, int srcLen, Tcl_DString * dsPtr);
    int (*tcl_UtfToLower) (char * src);
    int (*tcl_UtfToTitle) (char * src);
    int (*tcl_UtfToUniChar) (const char * src, Tcl_UniChar * chPtr);
    int (*tcl_UtfToUpper) (char * src);
    int (*tcl_WriteChars) (Tcl_Channel chan, const char * src, int srcLen);
    int (*tcl_WriteObj) (Tcl_Channel chan, Tcl_Obj * objPtr);
    char * (*tcl_GetString) (Tcl_Obj * objPtr);
    char * (*tcl_GetDefaultEncodingDir) (void);
    void (*tcl_SetDefaultEncodingDir) (const char * path);
    void (*tcl_AlertNotifier) (ClientData clientData);
    void (*tcl_ServiceModeHook) (int mode);
    int (*tcl_UniCharIsAlnum) (int ch);
    int (*tcl_UniCharIsAlpha) (int ch);
    int (*tcl_UniCharIsDigit) (int ch);
    int (*tcl_UniCharIsLower) (int ch);
    int (*tcl_UniCharIsSpace) (int ch);
    int (*tcl_UniCharIsUpper) (int ch);
    int (*tcl_UniCharIsWordChar) (int ch);
    int (*tcl_UniCharLen) (const Tcl_UniChar * uniStr);
    int (*tcl_UniCharNcmp) (const Tcl_UniChar * ucs, const Tcl_UniChar * uct, unsigned long numChars);
    char * (*tcl_UniCharToUtfDString) (const Tcl_UniChar * uniStr, int uniLength, Tcl_DString * dsPtr);
    Tcl_UniChar * (*tcl_UtfToUniCharDString) (const char * src, int length, Tcl_DString * dsPtr);
    Tcl_RegExp (*tcl_GetRegExpFromObj) (Tcl_Interp * interp, Tcl_Obj * patObj, int flags);
    Tcl_Obj * (*tcl_EvalTokens) (Tcl_Interp * interp, Tcl_Token * tokenPtr, int count);
    void (*tcl_FreeParse) (Tcl_Parse * parsePtr);
    void (*tcl_LogCommandInfo) (Tcl_Interp * interp, const char * script, const char * command, int length);
    int (*tcl_ParseBraces) (Tcl_Interp * interp, const char * start, int numBytes, Tcl_Parse * parsePtr, int append, char ** termPtr);
    int (*tcl_ParseCommand) (Tcl_Interp * interp, const char * start, int numBytes, int nested, Tcl_Parse * parsePtr);
    int (*tcl_ParseExpr) (Tcl_Interp * interp, const char * start, int numBytes, Tcl_Parse * parsePtr);
    int (*tcl_ParseQuotedString) (Tcl_Interp * interp, const char * start, int numBytes, Tcl_Parse * parsePtr, int append, char ** termPtr);
    int (*tcl_ParseVarName) (Tcl_Interp * interp, const char * start, int numBytes, Tcl_Parse * parsePtr, int append);
    char * (*tcl_GetCwd) (Tcl_Interp * interp, Tcl_DString * cwdPtr);
    int (*tcl_Chdir) (const char * dirName);
    int (*tcl_Access) (const char * path, int mode);
    int (*tcl_Stat) (const char * path, struct stat * bufPtr);
    int (*tcl_UtfNcmp) (const char * s1, const char * s2, unsigned long n);
    int (*tcl_UtfNcasecmp) (const char * s1, const char * s2, unsigned long n);
    int (*tcl_StringCaseMatch) (const char * str, const char * pattern, int nocase);
    int (*tcl_UniCharIsControl) (int ch);
    int (*tcl_UniCharIsGraph) (int ch);
    int (*tcl_UniCharIsPrint) (int ch);
    int (*tcl_UniCharIsPunct) (int ch);
    int (*tcl_RegExpExecObj) (Tcl_Interp * interp, Tcl_RegExp regexp, Tcl_Obj * textObj, int offset, int nmatches, int flags);
    void (*tcl_RegExpGetInfo) (Tcl_RegExp regexp, Tcl_RegExpInfo * infoPtr);
    Tcl_Obj * (*tcl_NewUnicodeObj) (const Tcl_UniChar * unicode, int numChars);
    void (*tcl_SetUnicodeObj) (Tcl_Obj * objPtr, const Tcl_UniChar * unicode, int numChars);
    int (*tcl_GetCharLength) (Tcl_Obj * objPtr);
    Tcl_UniChar (*tcl_GetUniChar) (Tcl_Obj * objPtr, int index);
    Tcl_UniChar * (*tcl_GetUnicode) (Tcl_Obj * objPtr);
    Tcl_Obj * (*tcl_GetRange) (Tcl_Obj * objPtr, int first, int last);
    void (*tcl_AppendUnicodeToObj) (Tcl_Obj * objPtr, const Tcl_UniChar * unicode, int length);
    int (*tcl_RegExpMatchObj) (Tcl_Interp * interp, Tcl_Obj * textObj, Tcl_Obj * patternObj);
    void (*tcl_SetNotifier) (Tcl_NotifierProcs * notifierProcPtr);
    Tcl_Mutex * (*tcl_GetAllocMutex) (void);
    int (*tcl_GetChannelNames) (Tcl_Interp * interp);
    int (*tcl_GetChannelNamesEx) (Tcl_Interp * interp, const char * pattern);
    int (*tcl_ProcObjCmd) (ClientData clientData, Tcl_Interp * interp, int objc, Tcl_Obj *const objv[]);
    void (*tcl_ConditionFinalize) (Tcl_Condition * condPtr);
    void (*tcl_MutexFinalize) (Tcl_Mutex * mutex);
    int (*tcl_CreateThread) (Tcl_ThreadId * idPtr, Tcl_ThreadCreateProc proc, ClientData clientData, int stackSize, int flags);
    int (*tcl_ReadRaw) (Tcl_Channel chan, char * dst, int bytesToRead);
    int (*tcl_WriteRaw) (Tcl_Channel chan, const char * src, int srcLen);
    Tcl_Channel (*tcl_GetTopChannel) (Tcl_Channel chan);
    int (*tcl_ChannelBuffered) (Tcl_Channel chan);
    char * (*tcl_ChannelName) (const Tcl_ChannelType * chanTypePtr);
    Tcl_ChannelTypeVersion (*tcl_ChannelVersion) (const Tcl_ChannelType * chanTypePtr);
    Tcl_DriverBlockModeProc * (*tcl_ChannelBlockModeProc) (const Tcl_ChannelType * chanTypePtr);
    Tcl_DriverCloseProc * (*tcl_ChannelCloseProc) (const Tcl_ChannelType * chanTypePtr);
    Tcl_DriverClose2Proc * (*tcl_ChannelClose2Proc) (const Tcl_ChannelType * chanTypePtr);
    Tcl_DriverInputProc * (*tcl_ChannelInputProc) (const Tcl_ChannelType * chanTypePtr);
    Tcl_DriverOutputProc * (*tcl_ChannelOutputProc) (const Tcl_ChannelType * chanTypePtr);
    Tcl_DriverSeekProc * (*tcl_ChannelSeekProc) (const Tcl_ChannelType * chanTypePtr);
    Tcl_DriverSetOptionProc * (*tcl_ChannelSetOptionProc) (const Tcl_ChannelType * chanTypePtr);
    Tcl_DriverGetOptionProc * (*tcl_ChannelGetOptionProc) (const Tcl_ChannelType * chanTypePtr);
    Tcl_DriverWatchProc * (*tcl_ChannelWatchProc) (const Tcl_ChannelType * chanTypePtr);
    Tcl_DriverGetHandleProc * (*tcl_ChannelGetHandleProc) (const Tcl_ChannelType * chanTypePtr);
    Tcl_DriverFlushProc * (*tcl_ChannelFlushProc) (const Tcl_ChannelType * chanTypePtr);
    Tcl_DriverHandlerProc * (*tcl_ChannelHandlerProc) (const Tcl_ChannelType * chanTypePtr);
    int (*tcl_JoinThread) (Tcl_ThreadId threadId, int* result);
    int (*tcl_IsChannelShared) (Tcl_Channel channel);
    int (*tcl_IsChannelRegistered) (Tcl_Interp* interp, Tcl_Channel channel);
    void (*tcl_CutChannel) (Tcl_Channel channel);
    void (*tcl_SpliceChannel) (Tcl_Channel channel);
    void (*tcl_ClearChannelHandlers) (Tcl_Channel channel);
    int (*tcl_IsChannelExisting) (const char* channelName);
    int (*tcl_UniCharNcasecmp) (const Tcl_UniChar * ucs, const Tcl_UniChar * uct, unsigned long numChars);
    int (*tcl_UniCharCaseMatch) (const Tcl_UniChar * uniStr, const Tcl_UniChar * uniPattern, int nocase);
    Tcl_HashEntry * (*tcl_FindHashEntry) (Tcl_HashTable * tablePtr, const char * key);
    Tcl_HashEntry * (*tcl_CreateHashEntry) (Tcl_HashTable * tablePtr, const char * key, int * newPtr);
    void (*tcl_InitCustomHashTable) (Tcl_HashTable * tablePtr, int keyType, Tcl_HashKeyType * typePtr);
    void (*tcl_InitObjHashTable) (Tcl_HashTable * tablePtr);
    ClientData (*tcl_CommandTraceInfo) (Tcl_Interp * interp, const char * varName, int flags, Tcl_CommandTraceProc * procPtr, ClientData prevClientData);
    int (*tcl_TraceCommand) (Tcl_Interp * interp, const char * varName, int flags, Tcl_CommandTraceProc * proc, ClientData clientData);
    void (*tcl_UntraceCommand) (Tcl_Interp * interp, const char * varName, int flags, Tcl_CommandTraceProc * proc, ClientData clientData);
    char * (*tcl_AttemptAlloc) (unsigned int size);
    char * (*tcl_AttemptDbCkalloc) (unsigned int size, const char * file, int line);
    char * (*tcl_AttemptRealloc) (char * ptr, unsigned int size);
    char * (*tcl_AttemptDbCkrealloc) (char * ptr, unsigned int size, const char * file, int line);
    int (*tcl_AttemptSetObjLength) (Tcl_Obj * objPtr, int length);
    Tcl_ThreadId (*tcl_GetChannelThread) (Tcl_Channel channel);
    Tcl_UniChar * (*tcl_GetUnicodeFromObj) (Tcl_Obj * objPtr, int * lengthPtr);
    int (*tcl_GetMathFuncInfo) (Tcl_Interp * interp, const char * name, int * numArgsPtr, Tcl_ValueType ** argTypesPtr, Tcl_MathProc ** procPtr, ClientData * clientDataPtr);
    Tcl_Obj * (*tcl_ListMathFuncs) (Tcl_Interp * interp, const char * pattern);
    Tcl_Obj * (*tcl_SubstObj) (Tcl_Interp * interp, Tcl_Obj * objPtr, int flags);
    int (*tcl_DetachChannel) (Tcl_Interp* interp, Tcl_Channel channel);
    int (*tcl_IsStandardChannel) (Tcl_Channel channel);
    int (*tcl_FSCopyFile) (Tcl_Obj * srcPathPtr, Tcl_Obj * destPathPtr);
    int (*tcl_FSCopyDirectory) (Tcl_Obj * srcPathPtr, Tcl_Obj * destPathPtr, Tcl_Obj ** errorPtr);
    int (*tcl_FSCreateDirectory) (Tcl_Obj * pathPtr);
    int (*tcl_FSDeleteFile) (Tcl_Obj * pathPtr);
    int (*tcl_FSLoadFile) (Tcl_Interp * interp, Tcl_Obj * pathPtr, const char * sym1, const char * sym2, Tcl_PackageInitProc ** proc1Ptr, Tcl_PackageInitProc ** proc2Ptr, Tcl_LoadHandle * handlePtr, Tcl_FSUnloadFileProc ** unloadProcPtr);
    int (*tcl_FSMatchInDirectory) (Tcl_Interp * interp, Tcl_Obj * result, Tcl_Obj * pathPtr, const char * pattern, Tcl_GlobTypeData * types);
    Tcl_Obj * (*tcl_FSLink) (Tcl_Obj * pathPtr, Tcl_Obj * toPtr, int linkAction);
    int (*tcl_FSRemoveDirectory) (Tcl_Obj * pathPtr, int recursive, Tcl_Obj ** errorPtr);
    int (*tcl_FSRenameFile) (Tcl_Obj * srcPathPtr, Tcl_Obj * destPathPtr);
    int (*tcl_FSLstat) (Tcl_Obj * pathPtr, Tcl_StatBuf * buf);
    int (*tcl_FSUtime) (Tcl_Obj * pathPtr, struct utimbuf * tval);
    int (*tcl_FSFileAttrsGet) (Tcl_Interp * interp, int index, Tcl_Obj * pathPtr, Tcl_Obj ** objPtrRef);
    int (*tcl_FSFileAttrsSet) (Tcl_Interp * interp, int index, Tcl_Obj * pathPtr, Tcl_Obj * objPtr);
    const char ** (*tcl_FSFileAttrStrings) (Tcl_Obj * pathPtr, Tcl_Obj ** objPtrRef);
    int (*tcl_FSStat) (Tcl_Obj * pathPtr, Tcl_StatBuf * buf);
    int (*tcl_FSAccess) (Tcl_Obj * pathPtr, int mode);
    Tcl_Channel (*tcl_FSOpenFileChannel) (Tcl_Interp * interp, Tcl_Obj * pathPtr, const char * modeString, int permissions);
    Tcl_Obj* (*tcl_FSGetCwd) (Tcl_Interp * interp);
    int (*tcl_FSChdir) (Tcl_Obj * pathPtr);
    int (*tcl_FSConvertToPathType) (Tcl_Interp * interp, Tcl_Obj * pathPtr);
    Tcl_Obj* (*tcl_FSJoinPath) (Tcl_Obj * listObj, int elements);
    Tcl_Obj* (*tcl_FSSplitPath) (Tcl_Obj* pathPtr, int * lenPtr);
    int (*tcl_FSEqualPaths) (Tcl_Obj* firstPtr, Tcl_Obj* secondPtr);
    Tcl_Obj* (*tcl_FSGetNormalizedPath) (Tcl_Interp * interp, Tcl_Obj* pathPtr);
    Tcl_Obj* (*tcl_FSJoinToPath) (Tcl_Obj * pathPtr, int objc, Tcl_Obj *const objv[]);
    ClientData (*tcl_FSGetInternalRep) (Tcl_Obj* pathPtr, Tcl_Filesystem * fsPtr);
    Tcl_Obj* (*tcl_FSGetTranslatedPath) (Tcl_Interp * interp, Tcl_Obj* pathPtr);
    int (*tcl_FSEvalFile) (Tcl_Interp * interp, Tcl_Obj * fileName);
    Tcl_Obj* (*tcl_FSNewNativePath) (Tcl_Filesystem* fromFilesystem, ClientData clientData);
    const char* (*tcl_FSGetNativePath) (Tcl_Obj* pathPtr);
    Tcl_Obj* (*tcl_FSFileSystemInfo) (Tcl_Obj* pathPtr);
    Tcl_Obj* (*tcl_FSPathSeparator) (Tcl_Obj* pathPtr);
    Tcl_Obj* (*tcl_FSListVolumes) (void);
    int (*tcl_FSRegister) (ClientData clientData, Tcl_Filesystem * fsPtr);
    int (*tcl_FSUnregister) (Tcl_Filesystem * fsPtr);
    ClientData (*tcl_FSData) (Tcl_Filesystem * fsPtr);
    const char* (*tcl_FSGetTranslatedStringPath) (Tcl_Interp * interp, Tcl_Obj* pathPtr);
    Tcl_Filesystem* (*tcl_FSGetFileSystemForPath) (Tcl_Obj* pathPtr);
    Tcl_PathType (*tcl_FSGetPathType) (Tcl_Obj * pathPtr);
    int (*tcl_OutputBuffered) (Tcl_Channel chan);
    void (*tcl_FSMountsChanged) (Tcl_Filesystem * fsPtr);
    int (*tcl_EvalTokensStandard) (Tcl_Interp * interp, Tcl_Token * tokenPtr, int count);
    void (*tcl_GetTime) (Tcl_Time* timeBuf);
    Tcl_Trace (*tcl_CreateObjTrace) (Tcl_Interp* interp, int level, int flags, Tcl_CmdObjTraceProc* objProc, ClientData clientData, Tcl_CmdObjTraceDeleteProc* delProc);
    int (*tcl_GetCommandInfoFromToken) (Tcl_Command token, Tcl_CmdInfo* infoPtr);
    int (*tcl_SetCommandInfoFromToken) (Tcl_Command token, const Tcl_CmdInfo* infoPtr);
    Tcl_Obj * (*tcl_DbNewWideIntObj) (Tcl_WideInt wideValue, const char * file, int line);
    int (*tcl_GetWideIntFromObj) (Tcl_Interp * interp, Tcl_Obj * objPtr, Tcl_WideInt * widePtr);
    Tcl_Obj * (*tcl_NewWideIntObj) (Tcl_WideInt wideValue);
    void (*tcl_SetWideIntObj) (Tcl_Obj * objPtr, Tcl_WideInt wideValue);
    Tcl_StatBuf * (*tcl_AllocStatBuf) (void);
    Tcl_WideInt (*tcl_Seek) (Tcl_Channel chan, Tcl_WideInt offset, int mode);
    Tcl_WideInt (*tcl_Tell) (Tcl_Channel chan);
    Tcl_DriverWideSeekProc * (*tcl_ChannelWideSeekProc) (const Tcl_ChannelType * chanTypePtr);
    int (*tcl_DictObjPut) (Tcl_Interp * interp, Tcl_Obj * dictPtr, Tcl_Obj * keyPtr, Tcl_Obj * valuePtr);
    int (*tcl_DictObjGet) (Tcl_Interp * interp, Tcl_Obj * dictPtr, Tcl_Obj * keyPtr, Tcl_Obj ** valuePtrPtr);
    int (*tcl_DictObjRemove) (Tcl_Interp * interp, Tcl_Obj * dictPtr, Tcl_Obj * keyPtr);
    int (*tcl_DictObjSize) (Tcl_Interp * interp, Tcl_Obj * dictPtr, int * sizePtr);
    int (*tcl_DictObjFirst) (Tcl_Interp * interp, Tcl_Obj * dictPtr, Tcl_DictSearch * searchPtr, Tcl_Obj ** keyPtrPtr, Tcl_Obj ** valuePtrPtr, int * donePtr);
    void (*tcl_DictObjNext) (Tcl_DictSearch * searchPtr, Tcl_Obj ** keyPtrPtr, Tcl_Obj ** valuePtrPtr, int * donePtr);
    void (*tcl_DictObjDone) (Tcl_DictSearch * searchPtr);
    int (*tcl_DictObjPutKeyList) (Tcl_Interp * interp, Tcl_Obj * dictPtr, int keyc, Tcl_Obj *const * keyv, Tcl_Obj * valuePtr);
    int (*tcl_DictObjRemoveKeyList) (Tcl_Interp * interp, Tcl_Obj * dictPtr, int keyc, Tcl_Obj *const * keyv);
    Tcl_Obj * (*tcl_NewDictObj) (void);
    Tcl_Obj * (*tcl_DbNewDictObj) (const char * file, int line);
    void (*tcl_RegisterConfig) (Tcl_Interp* interp, const char* pkgName, Tcl_Config* configuration, const char* valEncoding);
    Tcl_Namespace * (*tcl_CreateNamespace) (Tcl_Interp * interp, const char * name, ClientData clientData, Tcl_NamespaceDeleteProc * deleteProc);
    void (*tcl_DeleteNamespace) (Tcl_Namespace * nsPtr);
    int (*tcl_AppendExportList) (Tcl_Interp * interp, Tcl_Namespace * nsPtr, Tcl_Obj * objPtr);
    int (*tcl_Export) (Tcl_Interp * interp, Tcl_Namespace * nsPtr, const char * pattern, int resetListFirst);
    int (*tcl_Import) (Tcl_Interp * interp, Tcl_Namespace * nsPtr, const char * pattern, int allowOverwrite);
    int (*tcl_ForgetImport) (Tcl_Interp * interp, Tcl_Namespace * nsPtr, const char * pattern);
    Tcl_Namespace * (*tcl_GetCurrentNamespace) (Tcl_Interp * interp);
    Tcl_Namespace * (*tcl_GetGlobalNamespace) (Tcl_Interp * interp);
    Tcl_Namespace * (*tcl_FindNamespace) (Tcl_Interp * interp, const char * name, Tcl_Namespace * contextNsPtr, int flags);
    Tcl_Command (*tcl_FindCommand) (Tcl_Interp * interp, const char * name, Tcl_Namespace * contextNsPtr, int flags);
    Tcl_Command (*tcl_GetCommandFromObj) (Tcl_Interp * interp, Tcl_Obj * objPtr);
    void (*tcl_GetCommandFullName) (Tcl_Interp * interp, Tcl_Command command, Tcl_Obj * objPtr);
    int (*tcl_FSEvalFileEx) (Tcl_Interp * interp, Tcl_Obj * fileName, const char * encodingName);
    Tcl_ExitProc * (*tcl_SetExitProc) (Tcl_ExitProc * proc);
    void (*tcl_LimitAddHandler) (Tcl_Interp * interp, int type, Tcl_LimitHandlerProc * handlerProc, ClientData clientData, Tcl_LimitHandlerDeleteProc * deleteProc);
    void (*tcl_LimitRemoveHandler) (Tcl_Interp * interp, int type, Tcl_LimitHandlerProc * handlerProc, ClientData clientData);
    int (*tcl_LimitReady) (Tcl_Interp * interp);
    int (*tcl_LimitCheck) (Tcl_Interp * interp);
    int (*tcl_LimitExceeded) (Tcl_Interp * interp);
    void (*tcl_LimitSetCommands) (Tcl_Interp * interp, int commandLimit);
    void (*tcl_LimitSetTime) (Tcl_Interp * interp, Tcl_Time * timeLimitPtr);
    void (*tcl_LimitSetGranularity) (Tcl_Interp * interp, int type, int granularity);
    int (*tcl_LimitTypeEnabled) (Tcl_Interp * interp, int type);
    int (*tcl_LimitTypeExceeded) (Tcl_Interp * interp, int type);
    void (*tcl_LimitTypeSet) (Tcl_Interp * interp, int type);
    void (*tcl_LimitTypeReset) (Tcl_Interp * interp, int type);
    int (*tcl_LimitGetCommands) (Tcl_Interp * interp);
    void (*tcl_LimitGetTime) (Tcl_Interp * interp, Tcl_Time * timeLimitPtr);
    int (*tcl_LimitGetGranularity) (Tcl_Interp * interp, int type);
    Tcl_InterpState (*tcl_SaveInterpState) (Tcl_Interp * interp, int status);
    int (*tcl_RestoreInterpState) (Tcl_Interp * interp, Tcl_InterpState state);
    void (*tcl_DiscardInterpState) (Tcl_InterpState state);
    int (*tcl_SetReturnOptions) (Tcl_Interp * interp, Tcl_Obj * options);
    Tcl_Obj * (*tcl_GetReturnOptions) (Tcl_Interp * interp, int result);
    int (*tcl_IsEnsemble) (Tcl_Command token);
    Tcl_Command (*tcl_CreateEnsemble) (Tcl_Interp * interp, const char * name, Tcl_Namespace * namespacePtr, int flags);
    Tcl_Command (*tcl_FindEnsemble) (Tcl_Interp * interp, Tcl_Obj * cmdNameObj, int flags);
    int (*tcl_SetEnsembleSubcommandList) (Tcl_Interp * interp, Tcl_Command token, Tcl_Obj * subcmdList);
    int (*tcl_SetEnsembleMappingDict) (Tcl_Interp * interp, Tcl_Command token, Tcl_Obj * mapDict);
    int (*tcl_SetEnsembleUnknownHandler) (Tcl_Interp * interp, Tcl_Command token, Tcl_Obj * unknownList);
    int (*tcl_SetEnsembleFlags) (Tcl_Interp * interp, Tcl_Command token, int flags);
    int (*tcl_GetEnsembleSubcommandList) (Tcl_Interp * interp, Tcl_Command token, Tcl_Obj ** subcmdListPtr);
    int (*tcl_GetEnsembleMappingDict) (Tcl_Interp * interp, Tcl_Command token, Tcl_Obj ** mapDictPtr);
    int (*tcl_GetEnsembleUnknownHandler) (Tcl_Interp * interp, Tcl_Command token, Tcl_Obj ** unknownListPtr);
    int (*tcl_GetEnsembleFlags) (Tcl_Interp * interp, Tcl_Command token, int * flagsPtr);
    int (*tcl_GetEnsembleNamespace) (Tcl_Interp * interp, Tcl_Command token, Tcl_Namespace ** namespacePtrPtr);
    void (*tcl_SetTimeProc) (Tcl_GetTimeProc* getProc, Tcl_ScaleTimeProc* scaleProc, ClientData clientData);
    void (*tcl_QueryTimeProc) (Tcl_GetTimeProc** getProc, Tcl_ScaleTimeProc** scaleProc, ClientData* clientData);
    Tcl_DriverThreadActionProc * (*tcl_ChannelThreadActionProc) (const Tcl_ChannelType * chanTypePtr);
    Tcl_Obj* (*tcl_NewBignumObj) (mp_int* value);
    Tcl_Obj* (*tcl_DbNewBignumObj) (mp_int* value, const char* file, int line);
    void (*tcl_SetBignumObj) (Tcl_Obj* obj, mp_int* value);
    int (*tcl_GetBignumFromObj) (Tcl_Interp* interp, Tcl_Obj* obj, mp_int* value);
    int (*tcl_TakeBignumFromObj) (Tcl_Interp* interp, Tcl_Obj* obj, mp_int* value);
    int (*tcl_TruncateChannel) (Tcl_Channel chan, Tcl_WideInt length);
    Tcl_DriverTruncateProc * (*tcl_ChannelTruncateProc) (const Tcl_ChannelType * chanTypePtr);
    void (*tcl_SetChannelErrorInterp) (Tcl_Interp* interp, Tcl_Obj* msg);
    void (*tcl_GetChannelErrorInterp) (Tcl_Interp* interp, Tcl_Obj** msg);
    void (*tcl_SetChannelError) (Tcl_Channel chan, Tcl_Obj* msg);
    void (*tcl_GetChannelError) (Tcl_Channel chan, Tcl_Obj** msg);
    int (*tcl_InitBignumFromDouble) (Tcl_Interp* interp, double initval, mp_int * toInit);
    Tcl_Obj * (*tcl_GetNamespaceUnknownHandler) (Tcl_Interp * interp, Tcl_Namespace * nsPtr);
    int (*tcl_SetNamespaceUnknownHandler) (Tcl_Interp * interp, Tcl_Namespace * nsPtr, Tcl_Obj * handlerPtr);
    int (*tcl_GetEncodingFromObj) (Tcl_Interp* interp, Tcl_Obj* objPtr, Tcl_Encoding* encodingPtr);
    Tcl_Obj* (*tcl_GetEncodingSearchPath) (void);
    int (*tcl_SetEncodingSearchPath) (Tcl_Obj* searchPath);
    const char * (*tcl_GetEncodingNameFromEnvironment) (Tcl_DString* bufPtr);
    int (*tcl_PkgRequireProc) (Tcl_Interp * interp, const char * name, int objc, Tcl_Obj *const objv[], ClientData * clientDataPtr);
    void (*tcl_AppendObjToErrorInfo) (Tcl_Interp * interp, Tcl_Obj * objPtr);
    void (*tcl_AppendLimitedToObj) (Tcl_Obj * objPtr, const char * bytes, int length, int limit, const char * ellipsis);
    Tcl_Obj * (*tcl_Format) (Tcl_Interp * interp, const char * format, int objc, Tcl_Obj * const objv[]);
    int (*tcl_AppendFormatToObj) (Tcl_Interp * interp, Tcl_Obj * objPtr, const char * format, int objc, Tcl_Obj * const objv[]);
    Tcl_Obj * (*tcl_ObjPrintf) (const char * format, ...);
    void (*tcl_AppendPrintfToObj) (Tcl_Obj * objPtr, const char * format, ...);
} TclStubs;




extern TclStubs *tclStubsPtr;
# 2248 "/tmp/t852/include/tcl.h" 2






# 1 "/tmp/t852/include/tclPlatDecls.h" 1
# 83 "/tmp/t852/include/tclPlatDecls.h"
typedef struct TclPlatStubs {
    int magic;
    struct TclPlatStubHooks *hooks;
# 95 "/tmp/t852/include/tclPlatDecls.h"
} TclPlatStubs;




extern TclPlatStubs *tclPlatStubsPtr;
# 2255 "/tmp/t852/include/tcl.h" 2
# 2430 "/tmp/t852/include/tcl.h"
extern int Tcl_AppInit (Tcl_Interp *interp);
# 40 "bltInt.h" 2

# 1 "/tmp/t852/include/tk.h" 1
# 78 "/tmp/t852/include/tk.h"
# 1 "/usr/X11R6/include/X11/Xlib.h" 1
# 51 "/usr/X11R6/include/X11/Xlib.h"
# 1 "/usr/include/sys/types.h" 1 3
# 29 "/usr/include/sys/types.h" 3






typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;




typedef __loff_t loff_t;



typedef __ino_t ino_t;
# 62 "/usr/include/sys/types.h" 3
typedef __dev_t dev_t;




typedef __gid_t gid_t;




typedef __mode_t mode_t;




typedef __nlink_t nlink_t;




typedef __uid_t uid_t;





typedef __off_t off_t;
# 100 "/usr/include/sys/types.h" 3
typedef __pid_t pid_t;




typedef __id_t id_t;




typedef __ssize_t ssize_t;





typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;





typedef __key_t key_t;
# 133 "/usr/include/sys/types.h" 3
# 1 "/usr/include/time.h" 1 3
# 74 "/usr/include/time.h" 3


typedef __time_t time_t;



# 92 "/usr/include/time.h" 3
typedef __clockid_t clockid_t;
# 104 "/usr/include/time.h" 3
typedef __timer_t timer_t;
# 134 "/usr/include/sys/types.h" 2 3
# 147 "/usr/include/sys/types.h" 3
# 1 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stddef.h" 1 3
# 148 "/usr/include/sys/types.h" 2 3



typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
# 191 "/usr/include/sys/types.h" 3
typedef int int8_t __attribute__ ((__mode__ (__QI__)));
typedef int int16_t __attribute__ ((__mode__ (__HI__)));
typedef int int32_t __attribute__ ((__mode__ (__SI__)));
typedef int int64_t __attribute__ ((__mode__ (__DI__)));


typedef unsigned int u_int8_t __attribute__ ((__mode__ (__QI__)));
typedef unsigned int u_int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int u_int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int u_int64_t __attribute__ ((__mode__ (__DI__)));

typedef int register_t __attribute__ ((__mode__ (__word__)));
# 213 "/usr/include/sys/types.h" 3
# 1 "/usr/include/endian.h" 1 3
# 37 "/usr/include/endian.h" 3
# 1 "/usr/include/bits/endian.h" 1 3
# 38 "/usr/include/endian.h" 2 3
# 214 "/usr/include/sys/types.h" 2 3


# 1 "/usr/include/sys/select.h" 1 3
# 31 "/usr/include/sys/select.h" 3
# 1 "/usr/include/bits/select.h" 1 3
# 32 "/usr/include/sys/select.h" 2 3


# 1 "/usr/include/bits/sigset.h" 1 3
# 23 "/usr/include/bits/sigset.h" 3
typedef int __sig_atomic_t;




typedef struct
  {
    unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
  } __sigset_t;
# 35 "/usr/include/sys/select.h" 2 3



typedef __sigset_t sigset_t;





# 1 "/usr/include/time.h" 1 3
# 118 "/usr/include/time.h" 3
struct timespec
  {
    __time_t tv_sec;
    long int tv_nsec;
  };
# 45 "/usr/include/sys/select.h" 2 3

# 1 "/usr/include/bits/time.h" 1 3
# 69 "/usr/include/bits/time.h" 3
struct timeval
  {
    __time_t tv_sec;
    __suseconds_t tv_usec;
  };
# 47 "/usr/include/sys/select.h" 2 3


typedef __suseconds_t suseconds_t;





typedef long int __fd_mask;
# 67 "/usr/include/sys/select.h" 3
typedef struct
  {






    __fd_mask __fds_bits[1024 / (8 * sizeof (__fd_mask))];


  } fd_set;






typedef __fd_mask fd_mask;
# 99 "/usr/include/sys/select.h" 3

# 109 "/usr/include/sys/select.h" 3
extern int select (int __nfds, fd_set *__restrict __readfds,
                   fd_set *__restrict __writefds,
                   fd_set *__restrict __exceptfds,
                   struct timeval *__restrict __timeout);
# 128 "/usr/include/sys/select.h" 3

# 217 "/usr/include/sys/types.h" 2 3


# 1 "/usr/include/sys/sysmacros.h" 1 3
# 29 "/usr/include/sys/sysmacros.h" 3
__extension__
extern __inline unsigned int gnu_dev_major (unsigned long long int __dev)
     ;
__extension__
extern __inline unsigned int gnu_dev_minor (unsigned long long int __dev)
     ;
__extension__
extern __inline unsigned long long int gnu_dev_makedev (unsigned int __major,
                                                        unsigned int __minor)
     ;


__extension__ extern __inline unsigned int
gnu_dev_major (unsigned long long int __dev)
{
  return ((__dev >> 8) & 0xfff) | ((unsigned int) (__dev >> 32) & ~0xfff);
}

__extension__ extern __inline unsigned int
gnu_dev_minor (unsigned long long int __dev)
{
  return (__dev & 0xff) | ((unsigned int) (__dev >> 12) & ~0xff);
}

__extension__ extern __inline unsigned long long int
gnu_dev_makedev (unsigned int __major, unsigned int __minor)
{
  return ((__minor & 0xff) | ((__major & 0xfff) << 8)
          | (((unsigned long long int) (__minor & ~0xff)) << 12)
          | (((unsigned long long int) (__major & ~0xfff)) << 32));
}
# 220 "/usr/include/sys/types.h" 2 3
# 231 "/usr/include/sys/types.h" 3
typedef __blkcnt_t blkcnt_t;



typedef __fsblkcnt_t fsblkcnt_t;



typedef __fsfilcnt_t fsfilcnt_t;
# 266 "/usr/include/sys/types.h" 3
# 1 "/usr/include/bits/pthreadtypes.h" 1 3
# 23 "/usr/include/bits/pthreadtypes.h" 3
# 1 "/usr/include/bits/sched.h" 1 3
# 83 "/usr/include/bits/sched.h" 3
struct __sched_param
  {
    int __sched_priority;
  };
# 24 "/usr/include/bits/pthreadtypes.h" 2 3


struct _pthread_fastlock
{
  long int __status;
  int __spinlock;

};



typedef struct _pthread_descr_struct *_pthread_descr;





typedef struct __pthread_attr_s
{
  int __detachstate;
  int __schedpolicy;
  struct __sched_param __schedparam;
  int __inheritsched;
  int __scope;
  size_t __guardsize;
  int __stackaddr_set;
  void *__stackaddr;
  size_t __stacksize;
} pthread_attr_t;





__extension__ typedef long long __pthread_cond_align_t;




typedef struct
{
  struct _pthread_fastlock __c_lock;
  _pthread_descr __c_waiting;
  char __padding[48 - sizeof (struct _pthread_fastlock)
                 - sizeof (_pthread_descr) - sizeof (__pthread_cond_align_t)];
  __pthread_cond_align_t __align;
} pthread_cond_t;



typedef struct
{
  int __dummy;
} pthread_condattr_t;


typedef unsigned int pthread_key_t;





typedef struct
{
  int __m_reserved;
  int __m_count;
  _pthread_descr __m_owner;
  int __m_kind;
  struct _pthread_fastlock __m_lock;
} pthread_mutex_t;



typedef struct
{
  int __mutexkind;
} pthread_mutexattr_t;



typedef int pthread_once_t;
# 150 "/usr/include/bits/pthreadtypes.h" 3
typedef unsigned long int pthread_t;
# 267 "/usr/include/sys/types.h" 2 3



# 52 "/usr/X11R6/include/X11/Xlib.h" 2



# 1 "/usr/X11R6/include/X11/X.h" 1
# 71 "/usr/X11R6/include/X11/X.h"
typedef unsigned long XID;



typedef unsigned long Mask;



typedef unsigned long Atom;

typedef unsigned long VisualID;
typedef unsigned long Time;
# 101 "/usr/X11R6/include/X11/X.h"
typedef XID Window;
typedef XID Drawable;


typedef XID Font;

typedef XID Pixmap;
typedef XID Cursor;
typedef XID Colormap;
typedef XID GContext;
typedef XID KeySym;

typedef unsigned char KeyCode;
# 56 "/usr/X11R6/include/X11/Xlib.h" 2


# 1 "/usr/X11R6/include/X11/Xfuncproto.h" 1
# 59 "/usr/X11R6/include/X11/Xlib.h" 2
# 1 "/usr/X11R6/include/X11/Xosdefs.h" 1
# 60 "/usr/X11R6/include/X11/Xlib.h" 2
# 72 "/usr/X11R6/include/X11/Xlib.h"
# 1 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stddef.h" 1 3
# 151 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stddef.h" 3
typedef int ptrdiff_t;
# 73 "/usr/X11R6/include/X11/Xlib.h" 2
# 94 "/usr/X11R6/include/X11/Xlib.h"
typedef char *XPointer;
# 166 "/usr/X11R6/include/X11/Xlib.h"
typedef struct _XExtData {
        int number;
        struct _XExtData *next;
        int (*free_private)(

        struct _XExtData *extension

        );
        XPointer private_data;
} XExtData;




typedef struct {
        int extension;
        int major_opcode;
        int first_event;
        int first_error;
} XExtCodes;





typedef struct {
    int depth;
    int bits_per_pixel;
    int scanline_pad;
} XPixmapFormatValues;





typedef struct {
        int function;
        unsigned long plane_mask;
        unsigned long foreground;
        unsigned long background;
        int line_width;
        int line_style;
        int cap_style;

        int join_style;
        int fill_style;

        int fill_rule;
        int arc_mode;
        Pixmap tile;
        Pixmap stipple;
        int ts_x_origin;
        int ts_y_origin;
        Font font;
        int subwindow_mode;
        int graphics_exposures;
        int clip_x_origin;
        int clip_y_origin;
        Pixmap clip_mask;
        int dash_offset;
        char dashes;
} XGCValues;






typedef struct _XGC







*GC;




typedef struct {
        XExtData *ext_data;
        VisualID visualid;



        int class;

        unsigned long red_mask, green_mask, blue_mask;
        int bits_per_rgb;
        int map_entries;
} Visual;




typedef struct {
        int depth;
        int nvisuals;
        Visual *visuals;
} Depth;







struct _XDisplay;

typedef struct {
        XExtData *ext_data;
        struct _XDisplay *display;
        Window root;
        int width, height;
        int mwidth, mheight;
        int ndepths;
        Depth *depths;
        int root_depth;
        Visual *root_visual;
        GC default_gc;
        Colormap cmap;
        unsigned long white_pixel;
        unsigned long black_pixel;
        int max_maps, min_maps;
        int backing_store;
        int save_unders;
        long root_input_mask;
} Screen;




typedef struct {
        XExtData *ext_data;
        int depth;
        int bits_per_pixel;
        int scanline_pad;
} ScreenFormat;




typedef struct {
    Pixmap background_pixmap;
    unsigned long background_pixel;
    Pixmap border_pixmap;
    unsigned long border_pixel;
    int bit_gravity;
    int win_gravity;
    int backing_store;
    unsigned long backing_planes;
    unsigned long backing_pixel;
    int save_under;
    long event_mask;
    long do_not_propagate_mask;
    int override_redirect;
    Colormap colormap;
    Cursor cursor;
} XSetWindowAttributes;

typedef struct {
    int x, y;
    int width, height;
    int border_width;
    int depth;
    Visual *visual;
    Window root;



    int class;

    int bit_gravity;
    int win_gravity;
    int backing_store;
    unsigned long backing_planes;
    unsigned long backing_pixel;
    int save_under;
    Colormap colormap;
    int map_installed;
    int map_state;
    long all_event_masks;
    long your_event_mask;
    long do_not_propagate_mask;
    int override_redirect;
    Screen *screen;
} XWindowAttributes;






typedef struct {
        int family;
        int length;
        char *address;
} XHostAddress;




typedef struct _XImage {
    int width, height;
    int xoffset;
    int format;
    char *data;
    int byte_order;
    int bitmap_unit;
    int bitmap_bit_order;
    int bitmap_pad;
    int depth;
    int bytes_per_line;
    int bits_per_pixel;
    unsigned long red_mask;
    unsigned long green_mask;
    unsigned long blue_mask;
    XPointer obdata;
    struct funcs {

        struct _XImage *(*create_image)(
                struct _XDisplay* ,
                Visual* ,
                unsigned int ,
                int ,
                int ,
                char* ,
                unsigned int ,
                unsigned int ,
                int ,
                int );
        int (*destroy_image) (struct _XImage *);
        unsigned long (*get_pixel) (struct _XImage *, int, int);
        int (*put_pixel) (struct _XImage *, int, int, unsigned long);
        struct _XImage *(*sub_image)(struct _XImage *, int, int, unsigned int, unsigned int);
        int (*add_pixel) (struct _XImage *, long);
# 412 "/usr/X11R6/include/X11/Xlib.h"
        } f;
} XImage;




typedef struct {
    int x, y;
    int width, height;
    int border_width;
    Window sibling;
    int stack_mode;
} XWindowChanges;




typedef struct {
        unsigned long pixel;
        unsigned short red, green, blue;
        char flags;
        char pad;
} XColor;






typedef struct {
    short x1, y1, x2, y2;
} XSegment;

typedef struct {
    short x, y;
} XPoint;

typedef struct {
    short x, y;
    unsigned short width, height;
} XRectangle;

typedef struct {
    short x, y;
    unsigned short width, height;
    short angle1, angle2;
} XArc;




typedef struct {
        int key_click_percent;
        int bell_percent;
        int bell_pitch;
        int bell_duration;
        int led;
        int led_mode;
        int key;
        int auto_repeat_mode;
} XKeyboardControl;



typedef struct {
        int key_click_percent;
        int bell_percent;
        unsigned int bell_pitch, bell_duration;
        unsigned long led_mask;
        int global_auto_repeat;
        char auto_repeats[32];
} XKeyboardState;



typedef struct {
        Time time;
        short x, y;
} XTimeCoord;



typedef struct {
        int max_keypermod;
        KeyCode *modifiermap;
} XModifierKeymap;
# 506 "/usr/X11R6/include/X11/Xlib.h"
typedef struct _XDisplay Display;


struct _XPrivate;
struct _XrmHashBucketRec;

typedef struct



{
        XExtData *ext_data;
        struct _XPrivate *private1;
        int fd;
        int private2;
        int proto_major_version;
        int proto_minor_version;
        char *vendor;
        XID private3;
        XID private4;
        XID private5;
        int private6;
        XID (*resource_alloc)(

                struct _XDisplay*

        );
        int byte_order;
        int bitmap_unit;
        int bitmap_pad;
        int bitmap_bit_order;
        int nformats;
        ScreenFormat *pixmap_format;
        int private8;
        int release;
        struct _XPrivate *private9, *private10;
        int qlen;
        unsigned long last_request_read;
        unsigned long request;
        XPointer private11;
        XPointer private12;
        XPointer private13;
        XPointer private14;
        unsigned max_request_size;
        struct _XrmHashBucketRec *db;
        int (*private15)(

                struct _XDisplay*

                );
        char *display_name;
        int default_screen;
        int nscreens;
        Screen *screens;
        unsigned long motion_buffer;
        unsigned long private16;
        int min_keycode;
        int max_keycode;
        XPointer private17;
        XPointer private18;
        int private19;
        char *xdefaults;

}



*_XPrivDisplay;
# 582 "/usr/X11R6/include/X11/Xlib.h"
typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window window;
        Window root;
        Window subwindow;
        Time time;
        int x, y;
        int x_root, y_root;
        unsigned int state;
        unsigned int keycode;
        int same_screen;
} XKeyEvent;
typedef XKeyEvent XKeyPressedEvent;
typedef XKeyEvent XKeyReleasedEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window window;
        Window root;
        Window subwindow;
        Time time;
        int x, y;
        int x_root, y_root;
        unsigned int state;
        unsigned int button;
        int same_screen;
} XButtonEvent;
typedef XButtonEvent XButtonPressedEvent;
typedef XButtonEvent XButtonReleasedEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window window;
        Window root;
        Window subwindow;
        Time time;
        int x, y;
        int x_root, y_root;
        unsigned int state;
        char is_hint;
        int same_screen;
} XMotionEvent;
typedef XMotionEvent XPointerMovedEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window window;
        Window root;
        Window subwindow;
        Time time;
        int x, y;
        int x_root, y_root;
        int mode;
        int detail;




        int same_screen;
        int focus;
        unsigned int state;
} XCrossingEvent;
typedef XCrossingEvent XEnterWindowEvent;
typedef XCrossingEvent XLeaveWindowEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window window;
        int mode;
        int detail;





} XFocusChangeEvent;
typedef XFocusChangeEvent XFocusInEvent;
typedef XFocusChangeEvent XFocusOutEvent;


typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window window;
        char key_vector[32];
} XKeymapEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window window;
        int x, y;
        int width, height;
        int count;
} XExposeEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Drawable drawable;
        int x, y;
        int width, height;
        int count;
        int major_code;
        int minor_code;
} XGraphicsExposeEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Drawable drawable;
        int major_code;
        int minor_code;
} XNoExposeEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window window;
        int state;
} XVisibilityEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window parent;
        Window window;
        int x, y;
        int width, height;
        int border_width;
        int override_redirect;
} XCreateWindowEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window event;
        Window window;
} XDestroyWindowEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window event;
        Window window;
        int from_configure;
} XUnmapEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window event;
        Window window;
        int override_redirect;
} XMapEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window parent;
        Window window;
} XMapRequestEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window event;
        Window window;
        Window parent;
        int x, y;
        int override_redirect;
} XReparentEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window event;
        Window window;
        int x, y;
        int width, height;
        int border_width;
        Window above;
        int override_redirect;
} XConfigureEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window event;
        Window window;
        int x, y;
} XGravityEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window window;
        int width, height;
} XResizeRequestEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window parent;
        Window window;
        int x, y;
        int width, height;
        int border_width;
        Window above;
        int detail;
        unsigned long value_mask;
} XConfigureRequestEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window event;
        Window window;
        int place;
} XCirculateEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window parent;
        Window window;
        int place;
} XCirculateRequestEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window window;
        Atom atom;
        Time time;
        int state;
} XPropertyEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window window;
        Atom selection;
        Time time;
} XSelectionClearEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window owner;
        Window requestor;
        Atom selection;
        Atom target;
        Atom property;
        Time time;
} XSelectionRequestEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window requestor;
        Atom selection;
        Atom target;
        Atom property;
        Time time;
} XSelectionEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window window;
        Colormap colormap;



        int new;

        int state;
} XColormapEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window window;
        Atom message_type;
        int format;
        union {
                char b[20];
                short s[10];
                long l[5];
                } data;
} XClientMessageEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window window;
        int request;

        int first_keycode;
        int count;
} XMappingEvent;

typedef struct {
        int type;
        Display *display;
        XID resourceid;
        unsigned long serial;
        unsigned char error_code;
        unsigned char request_code;
        unsigned char minor_code;
} XErrorEvent;

typedef struct {
        int type;
        unsigned long serial;
        int send_event;
        Display *display;
        Window window;
} XAnyEvent;





typedef union _XEvent {
        int type;
        XAnyEvent xany;
        XKeyEvent xkey;
        XButtonEvent xbutton;
        XMotionEvent xmotion;
        XCrossingEvent xcrossing;
        XFocusChangeEvent xfocus;
        XExposeEvent xexpose;
        XGraphicsExposeEvent xgraphicsexpose;
        XNoExposeEvent xnoexpose;
        XVisibilityEvent xvisibility;
        XCreateWindowEvent xcreatewindow;
        XDestroyWindowEvent xdestroywindow;
        XUnmapEvent xunmap;
        XMapEvent xmap;
        XMapRequestEvent xmaprequest;
        XReparentEvent xreparent;
        XConfigureEvent xconfigure;
        XGravityEvent xgravity;
        XResizeRequestEvent xresizerequest;
        XConfigureRequestEvent xconfigurerequest;
        XCirculateEvent xcirculate;
        XCirculateRequestEvent xcirculaterequest;
        XPropertyEvent xproperty;
        XSelectionClearEvent xselectionclear;
        XSelectionRequestEvent xselectionrequest;
        XSelectionEvent xselection;
        XColormapEvent xcolormap;
        XClientMessageEvent xclient;
        XMappingEvent xmapping;
        XErrorEvent xerror;
        XKeymapEvent xkeymap;
        long pad[24];
} XEvent;







typedef struct {
    short lbearing;
    short rbearing;
    short width;
    short ascent;
    short descent;
    unsigned short attributes;
} XCharStruct;





typedef struct {
    Atom name;
    unsigned long card32;
} XFontProp;

typedef struct {
    XExtData *ext_data;
    Font fid;
    unsigned direction;
    unsigned min_char_or_byte2;
    unsigned max_char_or_byte2;
    unsigned min_byte1;
    unsigned max_byte1;
    int all_chars_exist;
    unsigned default_char;
    int n_properties;
    XFontProp *properties;
    XCharStruct min_bounds;
    XCharStruct max_bounds;
    XCharStruct *per_char;
    int ascent;
    int descent;
} XFontStruct;




typedef struct {
    char *chars;
    int nchars;
    int delta;
    Font font;
} XTextItem;

typedef struct {
    unsigned char byte1;
    unsigned char byte2;
} XChar2b;

typedef struct {
    XChar2b *chars;
    int nchars;
    int delta;
    Font font;
} XTextItem16;


typedef union { Display *display;
                GC gc;
                Visual *visual;
                Screen *screen;
                ScreenFormat *pixmap_format;
                XFontStruct *font; } XEDataObject;

typedef struct {
    XRectangle max_ink_extent;
    XRectangle max_logical_extent;
} XFontSetExtents;





typedef struct _XOM *XOM;
typedef struct _XOC *XOC, *XFontSet;

typedef struct {
    char *chars;
    int nchars;
    int delta;
    XFontSet font_set;
} XmbTextItem;

typedef struct {
    wchar_t *chars;
    int nchars;
    int delta;
    XFontSet font_set;
} XwcTextItem;
# 1116 "/usr/X11R6/include/X11/Xlib.h"
typedef struct {
    int charset_count;
    char **charset_list;
} XOMCharSetList;

typedef enum {
    XOMOrientation_LTR_TTB,
    XOMOrientation_RTL_TTB,
    XOMOrientation_TTB_LTR,
    XOMOrientation_TTB_RTL,
    XOMOrientation_Context
} XOrientation;

typedef struct {
    int num_orientation;
    XOrientation *orientation;
} XOMOrientation;

typedef struct {
    int num_font;
    XFontStruct **font_struct_list;
    char **font_name_list;
} XOMFontInfo;

typedef struct _XIM *XIM;
typedef struct _XIC *XIC;

typedef void (*XIMProc)(

    XIM,
    XPointer,
    XPointer

);

typedef int (*XICProc)(

    XIC,
    XPointer,
    XPointer

);

typedef void (*XIDProc)(

    Display*,
    XPointer,
    XPointer

);

typedef unsigned long XIMStyle;

typedef struct {
    unsigned short count_styles;
    XIMStyle *supported_styles;
} XIMStyles;
# 1235 "/usr/X11R6/include/X11/Xlib.h"
typedef void *XVaNestedList;




typedef struct {
    XPointer client_data;
    XIMProc callback;
} XIMCallback;

typedef struct {
    XPointer client_data;
    XICProc callback;
} XICCallback;

typedef unsigned long XIMFeedback;
# 1262 "/usr/X11R6/include/X11/Xlib.h"
typedef struct _XIMText {
    unsigned short length;
    XIMFeedback *feedback;
    int encoding_is_wchar;
    union {
        char *multi_byte;
        wchar_t *wide_char;
    } string;
} XIMText;

typedef unsigned long XIMPreeditState;





typedef struct _XIMPreeditStateNotifyCallbackStruct {
    XIMPreeditState state;
} XIMPreeditStateNotifyCallbackStruct;

typedef unsigned long XIMResetState;




typedef unsigned long XIMStringConversionFeedback;
# 1296 "/usr/X11R6/include/X11/Xlib.h"
typedef struct _XIMStringConversionText {
    unsigned short length;
    XIMStringConversionFeedback *feedback;
    int encoding_is_wchar;
    union {
        char *mbs;
        wchar_t *wcs;
    } string;
} XIMStringConversionText;

typedef unsigned short XIMStringConversionPosition;

typedef unsigned short XIMStringConversionType;






typedef unsigned short XIMStringConversionOperation;




typedef enum {
    XIMForwardChar, XIMBackwardChar,
    XIMForwardWord, XIMBackwardWord,
    XIMCaretUp, XIMCaretDown,
    XIMNextLine, XIMPreviousLine,
    XIMLineStart, XIMLineEnd,
    XIMAbsolutePosition,
    XIMDontChange
} XIMCaretDirection;

typedef struct _XIMStringConversionCallbackStruct {
    XIMStringConversionPosition position;
    XIMCaretDirection direction;
    XIMStringConversionOperation operation;
    unsigned short factor;
    XIMStringConversionText *text;
} XIMStringConversionCallbackStruct;

typedef struct _XIMPreeditDrawCallbackStruct {
    int caret;
    int chg_first;
    int chg_length;
    XIMText *text;
} XIMPreeditDrawCallbackStruct;

typedef enum {
    XIMIsInvisible,
    XIMIsPrimary,
    XIMIsSecondary
} XIMCaretStyle;

typedef struct _XIMPreeditCaretCallbackStruct {
    int position;
    XIMCaretDirection direction;
    XIMCaretStyle style;
} XIMPreeditCaretCallbackStruct;

typedef enum {
    XIMTextType,
    XIMBitmapType
} XIMStatusDataType;

typedef struct _XIMStatusDrawCallbackStruct {
    XIMStatusDataType type;
    union {
        XIMText *text;
        Pixmap bitmap;
    } data;
} XIMStatusDrawCallbackStruct;

typedef struct _XIMHotKeyTrigger {
    KeySym keysym;
    int modifier;
    int modifier_mask;
} XIMHotKeyTrigger;

typedef struct _XIMHotKeyTriggers {
    int num_hot_key;
    XIMHotKeyTrigger *key;
} XIMHotKeyTriggers;

typedef unsigned long XIMHotKeyState;




typedef struct {
    unsigned short count_values;
    char **supported_values;
} XIMValuesList;







extern int _Xdebug;

extern XFontStruct *XLoadQueryFont(

    Display* ,
    const char*

);

extern XFontStruct *XQueryFont(

    Display* ,
    XID

);


extern XTimeCoord *XGetMotionEvents(

    Display* ,
    Window ,
    Time ,
    Time ,
    int*

);

extern XModifierKeymap *XDeleteModifiermapEntry(

    XModifierKeymap* ,

    unsigned int ,



    int

);

extern XModifierKeymap *XGetModifierMapping(

    Display*

);

extern XModifierKeymap *XInsertModifiermapEntry(

    XModifierKeymap* ,

    unsigned int ,



    int

);

extern XModifierKeymap *XNewModifiermap(

    int

);

extern XImage *XCreateImage(

    Display* ,
    Visual* ,
    unsigned int ,
    int ,
    int ,
    char* ,
    unsigned int ,
    unsigned int ,
    int ,
    int

);
extern int XInitImage(

    XImage*

);
extern XImage *XGetImage(

    Display* ,
    Drawable ,
    int ,
    int ,
    unsigned int ,
    unsigned int ,
    unsigned long ,
    int

);
extern XImage *XGetSubImage(

    Display* ,
    Drawable ,
    int ,
    int ,
    unsigned int ,
    unsigned int ,
    unsigned long ,
    int ,
    XImage* ,
    int ,
    int

);




extern Display *XOpenDisplay(

    const char*

);

extern void XrmInitialize(

    void

);

extern char *XFetchBytes(

    Display* ,
    int*

);
extern char *XFetchBuffer(

    Display* ,
    int* ,
    int

);
extern char *XGetAtomName(

    Display* ,
    Atom

);
extern int XGetAtomNames(

    Display* ,
    Atom* ,
    int ,
    char**

);
extern char *XGetDefault(

    Display* ,
    const char* ,
    const char*

);
extern char *XDisplayName(

    const char*

);
extern char *XKeysymToString(

    KeySym

);

extern int (*XSynchronize(

    Display* ,
    int

))(

    Display*

);
extern int (*XSetAfterFunction(

    Display* ,
    int (*) (

             Display*

            )

))(

    Display*

);
extern Atom XInternAtom(

    Display* ,
    const char* ,
    int

);
extern int XInternAtoms(

    Display* ,
    char** ,
    int ,
    int ,
    Atom*

);
extern Colormap XCopyColormapAndFree(

    Display* ,
    Colormap

);
extern Colormap XCreateColormap(

    Display* ,
    Window ,
    Visual* ,
    int

);
extern Cursor XCreatePixmapCursor(

    Display* ,
    Pixmap ,
    Pixmap ,
    XColor* ,
    XColor* ,
    unsigned int ,
    unsigned int

);
extern Cursor XCreateGlyphCursor(

    Display* ,
    Font ,
    Font ,
    unsigned int ,
    unsigned int ,
    XColor const * ,
    XColor const *

);
extern Cursor XCreateFontCursor(

    Display* ,
    unsigned int

);
extern Font XLoadFont(

    Display* ,
    const char*

);
extern GC XCreateGC(

    Display* ,
    Drawable ,
    unsigned long ,
    XGCValues*

);
extern GContext XGContextFromGC(

    GC

);
extern void XFlushGC(

    Display* ,
    GC

);
extern Pixmap XCreatePixmap(

    Display* ,
    Drawable ,
    unsigned int ,
    unsigned int ,
    unsigned int

);
extern Pixmap XCreateBitmapFromData(

    Display* ,
    Drawable ,
    const char* ,
    unsigned int ,
    unsigned int

);
extern Pixmap XCreatePixmapFromBitmapData(

    Display* ,
    Drawable ,
    char* ,
    unsigned int ,
    unsigned int ,
    unsigned long ,
    unsigned long ,
    unsigned int

);
extern Window XCreateSimpleWindow(

    Display* ,
    Window ,
    int ,
    int ,
    unsigned int ,
    unsigned int ,
    unsigned int ,
    unsigned long ,
    unsigned long

);
extern Window XGetSelectionOwner(

    Display* ,
    Atom

);
extern Window XCreateWindow(

    Display* ,
    Window ,
    int ,
    int ,
    unsigned int ,
    unsigned int ,
    unsigned int ,
    int ,
    unsigned int ,
    Visual* ,
    unsigned long ,
    XSetWindowAttributes*

);
extern Colormap *XListInstalledColormaps(

    Display* ,
    Window ,
    int*

);
extern char **XListFonts(

    Display* ,
    const char* ,
    int ,
    int*

);
extern char **XListFontsWithInfo(

    Display* ,
    const char* ,
    int ,
    int* ,
    XFontStruct**

);
extern char **XGetFontPath(

    Display* ,
    int*

);
extern char **XListExtensions(

    Display* ,
    int*

);
extern Atom *XListProperties(

    Display* ,
    Window ,
    int*

);
extern XHostAddress *XListHosts(

    Display* ,
    int* ,
    int*

);
extern KeySym XKeycodeToKeysym(

    Display* ,

    unsigned int ,



    int

);
extern KeySym XLookupKeysym(

    XKeyEvent* ,
    int

);
extern KeySym *XGetKeyboardMapping(

    Display* ,

    unsigned int ,



    int ,
    int*

);
extern KeySym XStringToKeysym(

    const char*

);
extern long XMaxRequestSize(

    Display*

);
extern long XExtendedMaxRequestSize(

    Display*

);
extern char *XResourceManagerString(

    Display*

);
extern char *XScreenResourceString(

        Screen*

);
extern unsigned long XDisplayMotionBufferSize(

    Display*

);
extern VisualID XVisualIDFromVisual(

    Visual*

);



extern int XInitThreads(

    void

);

extern void XLockDisplay(

    Display*

);

extern void XUnlockDisplay(

    Display*

);



extern XExtCodes *XInitExtension(

    Display* ,
    const char*

);

extern XExtCodes *XAddExtension(

    Display*

);
extern XExtData *XFindOnExtensionList(

    XExtData** ,
    int

);
extern XExtData **XEHeadOfExtensionList(

    XEDataObject

);


extern Window XRootWindow(

    Display* ,
    int

);
extern Window XDefaultRootWindow(

    Display*

);
extern Window XRootWindowOfScreen(

    Screen*

);
extern Visual *XDefaultVisual(

    Display* ,
    int

);
extern Visual *XDefaultVisualOfScreen(

    Screen*

);
extern GC XDefaultGC(

    Display* ,
    int

);
extern GC XDefaultGCOfScreen(

    Screen*

);
extern unsigned long XBlackPixel(

    Display* ,
    int

);
extern unsigned long XWhitePixel(

    Display* ,
    int

);
extern unsigned long XAllPlanes(

    void

);
extern unsigned long XBlackPixelOfScreen(

    Screen*

);
extern unsigned long XWhitePixelOfScreen(

    Screen*

);
extern unsigned long XNextRequest(

    Display*

);
extern unsigned long XLastKnownRequestProcessed(

    Display*

);
extern char *XServerVendor(

    Display*

);
extern char *XDisplayString(

    Display*

);
extern Colormap XDefaultColormap(

    Display* ,
    int

);
extern Colormap XDefaultColormapOfScreen(

    Screen*

);
extern Display *XDisplayOfScreen(

    Screen*

);
extern Screen *XScreenOfDisplay(

    Display* ,
    int

);
extern Screen *XDefaultScreenOfDisplay(

    Display*

);
extern long XEventMaskOfScreen(

    Screen*

);

extern int XScreenNumberOfScreen(

    Screen*

);

typedef int (*XErrorHandler) (

    Display* ,
    XErrorEvent*

);

extern XErrorHandler XSetErrorHandler (

    XErrorHandler

);


typedef int (*XIOErrorHandler) (

    Display*

);

extern XIOErrorHandler XSetIOErrorHandler (

    XIOErrorHandler

);


extern XPixmapFormatValues *XListPixmapFormats(

    Display* ,
    int*

);
extern int *XListDepths(

    Display* ,
    int ,
    int*

);



extern int XReconfigureWMWindow(

    Display* ,
    Window ,
    int ,
    unsigned int ,
    XWindowChanges*

);

extern int XGetWMProtocols(

    Display* ,
    Window ,
    Atom** ,
    int*

);
extern int XSetWMProtocols(

    Display* ,
    Window ,
    Atom* ,
    int

);
extern int XIconifyWindow(

    Display* ,
    Window ,
    int

);
extern int XWithdrawWindow(

    Display* ,
    Window ,
    int

);
extern int XGetCommand(

    Display* ,
    Window ,
    char*** ,
    int*

);
extern int XGetWMColormapWindows(

    Display* ,
    Window ,
    Window** ,
    int*

);
extern int XSetWMColormapWindows(

    Display* ,
    Window ,
    Window* ,
    int

);
extern void XFreeStringList(

    char**

);
extern int XSetTransientForHint(

    Display* ,
    Window ,
    Window

);



extern int XActivateScreenSaver(

    Display*

);

extern int XAddHost(

    Display* ,
    XHostAddress*

);

extern int XAddHosts(

    Display* ,
    XHostAddress* ,
    int

);

extern int XAddToExtensionList(

    struct _XExtData** ,
    XExtData*

);

extern int XAddToSaveSet(

    Display* ,
    Window

);

extern int XAllocColor(

    Display* ,
    Colormap ,
    XColor*

);

extern int XAllocColorCells(

    Display* ,
    Colormap ,
    int ,
    unsigned long* ,
    unsigned int ,
    unsigned long* ,
    unsigned int

);

extern int XAllocColorPlanes(

    Display* ,
    Colormap ,
    int ,
    unsigned long* ,
    int ,
    int ,
    int ,
    int ,
    unsigned long* ,
    unsigned long* ,
    unsigned long*

);

extern int XAllocNamedColor(

    Display* ,
    Colormap ,
    const char* ,
    XColor* ,
    XColor*

);

extern int XAllowEvents(

    Display* ,
    int ,
    Time

);

extern int XAutoRepeatOff(

    Display*

);

extern int XAutoRepeatOn(

    Display*

);

extern int XBell(

    Display* ,
    int

);

extern int XBitmapBitOrder(

    Display*

);

extern int XBitmapPad(

    Display*

);

extern int XBitmapUnit(

    Display*

);

extern int XCellsOfScreen(

    Screen*

);

extern int XChangeActivePointerGrab(

    Display* ,
    unsigned int ,
    Cursor ,
    Time

);

extern int XChangeGC(

    Display* ,
    GC ,
    unsigned long ,
    XGCValues*

);

extern int XChangeKeyboardControl(

    Display* ,
    unsigned long ,
    XKeyboardControl*

);

extern int XChangeKeyboardMapping(

    Display* ,
    int ,
    int ,
    KeySym* ,
    int

);

extern int XChangePointerControl(

    Display* ,
    int ,
    int ,
    int ,
    int ,
    int

);

extern int XChangeProperty(

    Display* ,
    Window ,
    Atom ,
    Atom ,
    int ,
    int ,
    const unsigned char* ,
    int

);

extern int XChangeSaveSet(

    Display* ,
    Window ,
    int

);

extern int XChangeWindowAttributes(

    Display* ,
    Window ,
    unsigned long ,
    XSetWindowAttributes*

);

extern int XCheckIfEvent(

    Display* ,
    XEvent* ,
    int (*) (

               Display* ,
               XEvent* ,
               XPointer

             ) ,
    XPointer

);

extern int XCheckMaskEvent(

    Display* ,
    long ,
    XEvent*

);

extern int XCheckTypedEvent(

    Display* ,
    int ,
    XEvent*

);

extern int XCheckTypedWindowEvent(

    Display* ,
    Window ,
    int ,
    XEvent*

);

extern int XCheckWindowEvent(

    Display* ,
    Window ,
    long ,
    XEvent*

);

extern int XCirculateSubwindows(

    Display* ,
    Window ,
    int

);

extern int XCirculateSubwindowsDown(

    Display* ,
    Window

);

extern int XCirculateSubwindowsUp(

    Display* ,
    Window

);

extern int XClearArea(

    Display* ,
    Window ,
    int ,
    int ,
    unsigned int ,
    unsigned int ,
    int

);

extern int XClearWindow(

    Display* ,
    Window

);

extern int XCloseDisplay(

    Display*

);

extern int XConfigureWindow(

    Display* ,
    Window ,
    unsigned int ,
    XWindowChanges*

);

extern int XConnectionNumber(

    Display*

);

extern int XConvertSelection(

    Display* ,
    Atom ,
    Atom ,
    Atom ,
    Window ,
    Time

);

extern int XCopyArea(

    Display* ,
    Drawable ,
    Drawable ,
    GC ,
    int ,
    int ,
    unsigned int ,
    unsigned int ,
    int ,
    int

);

extern int XCopyGC(

    Display* ,
    GC ,
    unsigned long ,
    GC

);

extern int XCopyPlane(

    Display* ,
    Drawable ,
    Drawable ,
    GC ,
    int ,
    int ,
    unsigned int ,
    unsigned int ,
    int ,
    int ,
    unsigned long

);

extern int XDefaultDepth(

    Display* ,
    int

);

extern int XDefaultDepthOfScreen(

    Screen*

);

extern int XDefaultScreen(

    Display*

);

extern int XDefineCursor(

    Display* ,
    Window ,
    Cursor

);

extern int XDeleteProperty(

    Display* ,
    Window ,
    Atom

);

extern int XDestroyWindow(

    Display* ,
    Window

);

extern int XDestroySubwindows(

    Display* ,
    Window

);

extern int XDoesBackingStore(

    Screen*

);

extern int XDoesSaveUnders(

    Screen*

);

extern int XDisableAccessControl(

    Display*

);


extern int XDisplayCells(

    Display* ,
    int

);

extern int XDisplayHeight(

    Display* ,
    int

);

extern int XDisplayHeightMM(

    Display* ,
    int

);

extern int XDisplayKeycodes(

    Display* ,
    int* ,
    int*

);

extern int XDisplayPlanes(

    Display* ,
    int

);

extern int XDisplayWidth(

    Display* ,
    int

);

extern int XDisplayWidthMM(

    Display* ,
    int

);

extern int XDrawArc(

    Display* ,
    Drawable ,
    GC ,
    int ,
    int ,
    unsigned int ,
    unsigned int ,
    int ,
    int

);

extern int XDrawArcs(

    Display* ,
    Drawable ,
    GC ,
    XArc* ,
    int

);

extern int XDrawImageString(

    Display* ,
    Drawable ,
    GC ,
    int ,
    int ,
    const char* ,
    int

);

extern int XDrawImageString16(

    Display* ,
    Drawable ,
    GC ,
    int ,
    int ,
    const XChar2b* ,
    int

);

extern int XDrawLine(

    Display* ,
    Drawable ,
    GC ,
    int ,
    int ,
    int ,
    int

);

extern int XDrawLines(

    Display* ,
    Drawable ,
    GC ,
    XPoint* ,
    int ,
    int

);

extern int XDrawPoint(

    Display* ,
    Drawable ,
    GC ,
    int ,
    int

);

extern int XDrawPoints(

    Display* ,
    Drawable ,
    GC ,
    XPoint* ,
    int ,
    int

);

extern int XDrawRectangle(

    Display* ,
    Drawable ,
    GC ,
    int ,
    int ,
    unsigned int ,
    unsigned int

);

extern int XDrawRectangles(

    Display* ,
    Drawable ,
    GC ,
    XRectangle* ,
    int

);

extern int XDrawSegments(

    Display* ,
    Drawable ,
    GC ,
    XSegment* ,
    int

);

extern int XDrawString(

    Display* ,
    Drawable ,
    GC ,
    int ,
    int ,
    const char* ,
    int

);

extern int XDrawString16(

    Display* ,
    Drawable ,
    GC ,
    int ,
    int ,
    const XChar2b* ,
    int

);

extern int XDrawText(

    Display* ,
    Drawable ,
    GC ,
    int ,
    int ,
    XTextItem* ,
    int

);

extern int XDrawText16(

    Display* ,
    Drawable ,
    GC ,
    int ,
    int ,
    XTextItem16* ,
    int

);

extern int XEnableAccessControl(

    Display*

);

extern int XEventsQueued(

    Display* ,
    int

);

extern int XFetchName(

    Display* ,
    Window ,
    char**

);

extern int XFillArc(

    Display* ,
    Drawable ,
    GC ,
    int ,
    int ,
    unsigned int ,
    unsigned int ,
    int ,
    int

);

extern int XFillArcs(

    Display* ,
    Drawable ,
    GC ,
    XArc* ,
    int

);

extern int XFillPolygon(

    Display* ,
    Drawable ,
    GC ,
    XPoint* ,
    int ,
    int ,
    int

);

extern int XFillRectangle(

    Display* ,
    Drawable ,
    GC ,
    int ,
    int ,
    unsigned int ,
    unsigned int

);

extern int XFillRectangles(

    Display* ,
    Drawable ,
    GC ,
    XRectangle* ,
    int

);

extern int XFlush(

    Display*

);

extern int XForceScreenSaver(

    Display* ,
    int

);

extern int XFree(

    void*

);

extern int XFreeColormap(

    Display* ,
    Colormap

);

extern int XFreeColors(

    Display* ,
    Colormap ,
    unsigned long* ,
    int ,
    unsigned long

);

extern int XFreeCursor(

    Display* ,
    Cursor

);

extern int XFreeExtensionList(

    char**

);

extern int XFreeFont(

    Display* ,
    XFontStruct*

);

extern int XFreeFontInfo(

    char** ,
    XFontStruct* ,
    int

);

extern int XFreeFontNames(

    char**

);

extern int XFreeFontPath(

    char**

);

extern int XFreeGC(

    Display* ,
    GC

);

extern int XFreeModifiermap(

    XModifierKeymap*

);

extern int XFreePixmap(

    Display* ,
    Pixmap

);

extern int XGeometry(

    Display* ,
    int ,
    const char* ,
    const char* ,
    unsigned int ,
    unsigned int ,
    unsigned int ,
    int ,
    int ,
    int* ,
    int* ,
    int* ,
    int*

);

extern int XGetErrorDatabaseText(

    Display* ,
    const char* ,
    const char* ,
    const char* ,
    char* ,
    int

);

extern int XGetErrorText(

    Display* ,
    int ,
    char* ,
    int

);

extern int XGetFontProperty(

    XFontStruct* ,
    Atom ,
    unsigned long*

);

extern int XGetGCValues(

    Display* ,
    GC ,
    unsigned long ,
    XGCValues*

);

extern int XGetGeometry(

    Display* ,
    Drawable ,
    Window* ,
    int* ,
    int* ,
    unsigned int* ,
    unsigned int* ,
    unsigned int* ,
    unsigned int*

);

extern int XGetIconName(

    Display* ,
    Window ,
    char**

);

extern int XGetInputFocus(

    Display* ,
    Window* ,
    int*

);

extern int XGetKeyboardControl(

    Display* ,
    XKeyboardState*

);

extern int XGetPointerControl(

    Display* ,
    int* ,
    int* ,
    int*

);

extern int XGetPointerMapping(

    Display* ,
    unsigned char* ,
    int

);

extern int XGetScreenSaver(

    Display* ,
    int* ,
    int* ,
    int* ,
    int*

);

extern int XGetTransientForHint(

    Display* ,
    Window ,
    Window*

);

extern int XGetWindowProperty(

    Display* ,
    Window ,
    Atom ,
    long ,
    long ,
    int ,
    Atom ,
    Atom* ,
    int* ,
    unsigned long* ,
    unsigned long* ,
    unsigned char**

);

extern int XGetWindowAttributes(

    Display* ,
    Window ,
    XWindowAttributes*

);

extern int XGrabButton(

    Display* ,
    unsigned int ,
    unsigned int ,
    Window ,
    int ,
    unsigned int ,
    int ,
    int ,
    Window ,
    Cursor

);

extern int XGrabKey(

    Display* ,
    int ,
    unsigned int ,
    Window ,
    int ,
    int ,
    int

);

extern int XGrabKeyboard(

    Display* ,
    Window ,
    int ,
    int ,
    int ,
    Time

);

extern int XGrabPointer(

    Display* ,
    Window ,
    int ,
    unsigned int ,
    int ,
    int ,
    Window ,
    Cursor ,
    Time

);

extern int XGrabServer(

    Display*

);

extern int XHeightMMOfScreen(

    Screen*

);

extern int XHeightOfScreen(

    Screen*

);

extern int XIfEvent(

    Display* ,
    XEvent* ,
    int (*) (

               Display* ,
               XEvent* ,
               XPointer

             ) ,
    XPointer

);

extern int XImageByteOrder(

    Display*

);

extern int XInstallColormap(

    Display* ,
    Colormap

);

extern KeyCode XKeysymToKeycode(

    Display* ,
    KeySym

);

extern int XKillClient(

    Display* ,
    XID

);

extern int XLookupColor(

    Display* ,
    Colormap ,
    const char* ,
    XColor* ,
    XColor*

);

extern int XLowerWindow(

    Display* ,
    Window

);

extern int XMapRaised(

    Display* ,
    Window

);

extern int XMapSubwindows(

    Display* ,
    Window

);

extern int XMapWindow(

    Display* ,
    Window

);

extern int XMaskEvent(

    Display* ,
    long ,
    XEvent*

);

extern int XMaxCmapsOfScreen(

    Screen*

);

extern int XMinCmapsOfScreen(

    Screen*

);

extern int XMoveResizeWindow(

    Display* ,
    Window ,
    int ,
    int ,
    unsigned int ,
    unsigned int

);

extern int XMoveWindow(

    Display* ,
    Window ,
    int ,
    int

);

extern int XNextEvent(

    Display* ,
    XEvent*

);

extern int XNoOp(

    Display*

);

extern int XParseColor(

    Display* ,
    Colormap ,
    const char* ,
    XColor*

);

extern int XParseGeometry(

    const char* ,
    int* ,
    int* ,
    unsigned int* ,
    unsigned int*

);

extern int XPeekEvent(

    Display* ,
    XEvent*

);

extern int XPeekIfEvent(

    Display* ,
    XEvent* ,
    int (*) (

               Display* ,
               XEvent* ,
               XPointer

             ) ,
    XPointer

);

extern int XPending(

    Display*

);

extern int XPlanesOfScreen(

    Screen*


);

extern int XProtocolRevision(

    Display*

);

extern int XProtocolVersion(

    Display*

);


extern int XPutBackEvent(

    Display* ,
    XEvent*

);

extern int XPutImage(

    Display* ,
    Drawable ,
    GC ,
    XImage* ,
    int ,
    int ,
    int ,
    int ,
    unsigned int ,
    unsigned int

);

extern int XQLength(

    Display*

);

extern int XQueryBestCursor(

    Display* ,
    Drawable ,
    unsigned int ,
    unsigned int ,
    unsigned int* ,
    unsigned int*

);

extern int XQueryBestSize(

    Display* ,
    int ,
    Drawable ,
    unsigned int ,
    unsigned int ,
    unsigned int* ,
    unsigned int*

);

extern int XQueryBestStipple(

    Display* ,
    Drawable ,
    unsigned int ,
    unsigned int ,
    unsigned int* ,
    unsigned int*

);

extern int XQueryBestTile(

    Display* ,
    Drawable ,
    unsigned int ,
    unsigned int ,
    unsigned int* ,
    unsigned int*

);

extern int XQueryColor(

    Display* ,
    Colormap ,
    XColor*

);

extern int XQueryColors(

    Display* ,
    Colormap ,
    XColor* ,
    int

);

extern int XQueryExtension(

    Display* ,
    const char* ,
    int* ,
    int* ,
    int*

);

extern int XQueryKeymap(

    Display* ,
    char [32]

);

extern int XQueryPointer(

    Display* ,
    Window ,
    Window* ,
    Window* ,
    int* ,
    int* ,
    int* ,
    int* ,
    unsigned int*

);

extern int XQueryTextExtents(

    Display* ,
    XID ,
    const char* ,
    int ,
    int* ,
    int* ,
    int* ,
    XCharStruct*

);

extern int XQueryTextExtents16(

    Display* ,
    XID ,
    const XChar2b* ,
    int ,
    int* ,
    int* ,
    int* ,
    XCharStruct*

);

extern int XQueryTree(

    Display* ,
    Window ,
    Window* ,
    Window* ,
    Window** ,
    unsigned int*

);

extern int XRaiseWindow(

    Display* ,
    Window

);

extern int XReadBitmapFile(

    Display* ,
    Drawable ,
    const char* ,
    unsigned int* ,
    unsigned int* ,
    Pixmap* ,
    int* ,
    int*

);

extern int XReadBitmapFileData(

    const char* ,
    unsigned int* ,
    unsigned int* ,
    unsigned char** ,
    int* ,
    int*

);

extern int XRebindKeysym(

    Display* ,
    KeySym ,
    KeySym* ,
    int ,
    const unsigned char* ,
    int

);

extern int XRecolorCursor(

    Display* ,
    Cursor ,
    XColor* ,
    XColor*

);

extern int XRefreshKeyboardMapping(

    XMappingEvent*

);

extern int XRemoveFromSaveSet(

    Display* ,
    Window

);

extern int XRemoveHost(

    Display* ,
    XHostAddress*

);

extern int XRemoveHosts(

    Display* ,
    XHostAddress* ,
    int

);

extern int XReparentWindow(

    Display* ,
    Window ,
    Window ,
    int ,
    int

);

extern int XResetScreenSaver(

    Display*

);

extern int XResizeWindow(

    Display* ,
    Window ,
    unsigned int ,
    unsigned int

);

extern int XRestackWindows(

    Display* ,
    Window* ,
    int

);

extern int XRotateBuffers(

    Display* ,
    int

);

extern int XRotateWindowProperties(

    Display* ,
    Window ,
    Atom* ,
    int ,
    int

);

extern int XScreenCount(

    Display*

);

extern int XSelectInput(

    Display* ,
    Window ,
    long

);

extern int XSendEvent(

    Display* ,
    Window ,
    int ,
    long ,
    XEvent*

);

extern int XSetAccessControl(

    Display* ,
    int

);

extern int XSetArcMode(

    Display* ,
    GC ,
    int

);

extern int XSetBackground(

    Display* ,
    GC ,
    unsigned long

);

extern int XSetClipMask(

    Display* ,
    GC ,
    Pixmap

);

extern int XSetClipOrigin(

    Display* ,
    GC ,
    int ,
    int

);

extern int XSetClipRectangles(

    Display* ,
    GC ,
    int ,
    int ,
    XRectangle* ,
    int ,
    int

);

extern int XSetCloseDownMode(

    Display* ,
    int

);

extern int XSetCommand(

    Display* ,
    Window ,
    char** ,
    int

);

extern int XSetDashes(

    Display* ,
    GC ,
    int ,
    const char* ,
    int

);

extern int XSetFillRule(

    Display* ,
    GC ,
    int

);

extern int XSetFillStyle(

    Display* ,
    GC ,
    int

);

extern int XSetFont(

    Display* ,
    GC ,
    Font

);

extern int XSetFontPath(

    Display* ,
    char** ,
    int

);

extern int XSetForeground(

    Display* ,
    GC ,
    unsigned long

);

extern int XSetFunction(

    Display* ,
    GC ,
    int

);

extern int XSetGraphicsExposures(

    Display* ,
    GC ,
    int

);

extern int XSetIconName(

    Display* ,
    Window ,
    const char*

);

extern int XSetInputFocus(

    Display* ,
    Window ,
    int ,
    Time

);

extern int XSetLineAttributes(

    Display* ,
    GC ,
    unsigned int ,
    int ,
    int ,
    int

);

extern int XSetModifierMapping(

    Display* ,
    XModifierKeymap*

);

extern int XSetPlaneMask(

    Display* ,
    GC ,
    unsigned long

);

extern int XSetPointerMapping(

    Display* ,
    const unsigned char* ,
    int

);

extern int XSetScreenSaver(

    Display* ,
    int ,
    int ,
    int ,
    int

);

extern int XSetSelectionOwner(

    Display* ,
    Atom ,
    Window ,
    Time

);

extern int XSetState(

    Display* ,
    GC ,
    unsigned long ,
    unsigned long ,
    int ,
    unsigned long

);

extern int XSetStipple(

    Display* ,
    GC ,
    Pixmap

);

extern int XSetSubwindowMode(

    Display* ,
    GC ,
    int

);

extern int XSetTSOrigin(

    Display* ,
    GC ,
    int ,
    int

);

extern int XSetTile(

    Display* ,
    GC ,
    Pixmap

);

extern int XSetWindowBackground(

    Display* ,
    Window ,
    unsigned long

);

extern int XSetWindowBackgroundPixmap(

    Display* ,
    Window ,
    Pixmap

);

extern int XSetWindowBorder(

    Display* ,
    Window ,
    unsigned long

);

extern int XSetWindowBorderPixmap(

    Display* ,
    Window ,
    Pixmap

);

extern int XSetWindowBorderWidth(

    Display* ,
    Window ,
    unsigned int

);

extern int XSetWindowColormap(

    Display* ,
    Window ,
    Colormap

);

extern int XStoreBuffer(

    Display* ,
    const char* ,
    int ,
    int

);

extern int XStoreBytes(

    Display* ,
    const char* ,
    int

);

extern int XStoreColor(

    Display* ,
    Colormap ,
    XColor*

);

extern int XStoreColors(

    Display* ,
    Colormap ,
    XColor* ,
    int

);

extern int XStoreName(

    Display* ,
    Window ,
    const char*

);

extern int XStoreNamedColor(

    Display* ,
    Colormap ,
    const char* ,
    unsigned long ,
    int

);

extern int XSync(

    Display* ,
    int

);

extern int XTextExtents(

    XFontStruct* ,
    const char* ,
    int ,
    int* ,
    int* ,
    int* ,
    XCharStruct*

);

extern int XTextExtents16(

    XFontStruct* ,
    const XChar2b* ,
    int ,
    int* ,
    int* ,
    int* ,
    XCharStruct*

);

extern int XTextWidth(

    XFontStruct* ,
    const char* ,
    int

);

extern int XTextWidth16(

    XFontStruct* ,
    const XChar2b* ,
    int

);

extern int XTranslateCoordinates(

    Display* ,
    Window ,
    Window ,
    int ,
    int ,
    int* ,
    int* ,
    Window*

);

extern int XUndefineCursor(

    Display* ,
    Window

);

extern int XUngrabButton(

    Display* ,
    unsigned int ,
    unsigned int ,
    Window

);

extern int XUngrabKey(

    Display* ,
    int ,
    unsigned int ,
    Window

);

extern int XUngrabKeyboard(

    Display* ,
    Time

);

extern int XUngrabPointer(

    Display* ,
    Time

);

extern int XUngrabServer(

    Display*

);

extern int XUninstallColormap(

    Display* ,
    Colormap

);

extern int XUnloadFont(

    Display* ,
    Font

);

extern int XUnmapSubwindows(

    Display* ,
    Window

);

extern int XUnmapWindow(

    Display* ,
    Window

);

extern int XVendorRelease(

    Display*

);

extern int XWarpPointer(

    Display* ,
    Window ,
    Window ,
    int ,
    int ,
    unsigned int ,
    unsigned int ,
    int ,
    int

);

extern int XWidthMMOfScreen(

    Screen*

);

extern int XWidthOfScreen(

    Screen*

);

extern int XWindowEvent(

    Display* ,
    Window ,
    long ,
    XEvent*

);

extern int XWriteBitmapFile(

    Display* ,
    const char* ,
    Pixmap ,
    unsigned int ,
    unsigned int ,
    int ,
    int

);

extern int XSupportsLocale (void);

extern char *XSetLocaleModifiers(
    const char*
);

extern XOM XOpenOM(

    Display* ,
    struct _XrmHashBucketRec* ,
    const char* ,
    const char*

);

extern int XCloseOM(

    XOM

);

extern char *XSetOMValues(

    XOM ,
    ...

);

extern char *XGetOMValues(

    XOM ,
    ...

);

extern Display *XDisplayOfOM(

    XOM

);

extern char *XLocaleOfOM(

    XOM

);

extern XOC XCreateOC(

    XOM ,
    ...

);

extern void XDestroyOC(

    XOC

);

extern XOM XOMOfOC(

    XOC

);

extern char *XSetOCValues(

    XOC ,
    ...

);

extern char *XGetOCValues(

    XOC ,
    ...

);

extern XFontSet XCreateFontSet(

    Display* ,
    const char* ,
    char*** ,
    int* ,
    char**

);

extern void XFreeFontSet(

    Display* ,
    XFontSet

);

extern int XFontsOfFontSet(

    XFontSet ,
    XFontStruct*** ,
    char***

);

extern char *XBaseFontNameListOfFontSet(

    XFontSet

);

extern char *XLocaleOfFontSet(

    XFontSet

);

extern int XContextDependentDrawing(

    XFontSet

);

extern int XDirectionalDependentDrawing(

    XFontSet

);

extern int XContextualDrawing(

    XFontSet

);

extern XFontSetExtents *XExtentsOfFontSet(

    XFontSet

);

extern int XmbTextEscapement(

    XFontSet ,
    const char* ,
    int

);

extern int XwcTextEscapement(

    XFontSet ,
    const wchar_t* ,
    int

);

extern int Xutf8TextEscapement(

    XFontSet ,
    const char* ,
    int

);

extern int XmbTextExtents(

    XFontSet ,
    const char* ,
    int ,
    XRectangle* ,
    XRectangle*

);

extern int XwcTextExtents(

    XFontSet ,
    const wchar_t* ,
    int ,
    XRectangle* ,
    XRectangle*

);

extern int Xutf8TextExtents(

    XFontSet ,
    const char* ,
    int ,
    XRectangle* ,
    XRectangle*

);

extern int XmbTextPerCharExtents(

    XFontSet ,
    const char* ,
    int ,
    XRectangle* ,
    XRectangle* ,
    int ,
    int* ,
    XRectangle* ,
    XRectangle*

);

extern int XwcTextPerCharExtents(

    XFontSet ,
    const wchar_t* ,
    int ,
    XRectangle* ,
    XRectangle* ,
    int ,
    int* ,
    XRectangle* ,
    XRectangle*

);

extern int Xutf8TextPerCharExtents(

    XFontSet ,
    const char* ,
    int ,
    XRectangle* ,
    XRectangle* ,
    int ,
    int* ,
    XRectangle* ,
    XRectangle*

);

extern void XmbDrawText(

    Display* ,
    Drawable ,
    GC ,
    int ,
    int ,
    XmbTextItem* ,
    int

);

extern void XwcDrawText(

    Display* ,
    Drawable ,
    GC ,
    int ,
    int ,
    XwcTextItem* ,
    int

);

extern void Xutf8DrawText(

    Display* ,
    Drawable ,
    GC ,
    int ,
    int ,
    XmbTextItem* ,
    int

);

extern void XmbDrawString(

    Display* ,
    Drawable ,
    XFontSet ,
    GC ,
    int ,
    int ,
    const char* ,
    int

);

extern void XwcDrawString(

    Display* ,
    Drawable ,
    XFontSet ,
    GC ,
    int ,
    int ,
    const wchar_t* ,
    int

);

extern void Xutf8DrawString(

    Display* ,
    Drawable ,
    XFontSet ,
    GC ,
    int ,
    int ,
    const char* ,
    int

);

extern void XmbDrawImageString(

    Display* ,
    Drawable ,
    XFontSet ,
    GC ,
    int ,
    int ,
    const char* ,
    int

);

extern void XwcDrawImageString(

    Display* ,
    Drawable ,
    XFontSet ,
    GC ,
    int ,
    int ,
    const wchar_t* ,
    int

);

extern void Xutf8DrawImageString(

    Display* ,
    Drawable ,
    XFontSet ,
    GC ,
    int ,
    int ,
    const char* ,
    int

);

extern XIM XOpenIM(

    Display* ,
    struct _XrmHashBucketRec* ,
    char* ,
    char*

);

extern int XCloseIM(

    XIM

);

extern char *XGetIMValues(

    XIM , ...

);

extern char *XSetIMValues(

    XIM , ...

);

extern Display *XDisplayOfIM(

    XIM

);

extern char *XLocaleOfIM(

    XIM

);

extern XIC XCreateIC(

    XIM , ...

);

extern void XDestroyIC(

    XIC

);

extern void XSetICFocus(

    XIC

);

extern void XUnsetICFocus(

    XIC

);

extern wchar_t *XwcResetIC(

    XIC

);

extern char *XmbResetIC(

    XIC

);

extern char *Xutf8ResetIC(

    XIC

);

extern char *XSetICValues(

    XIC , ...

);

extern char *XGetICValues(

    XIC , ...

);

extern XIM XIMOfIC(

    XIC

);

extern int XFilterEvent(

    XEvent* ,
    Window

);

extern int XmbLookupString(

    XIC ,
    XKeyPressedEvent* ,
    char* ,
    int ,
    KeySym* ,
    int*

);

extern int XwcLookupString(

    XIC ,
    XKeyPressedEvent* ,
    wchar_t* ,
    int ,
    KeySym* ,
    int*

);

extern int Xutf8LookupString(

    XIC ,
    XKeyPressedEvent* ,
    char* ,
    int ,
    KeySym* ,
    int*

);

extern XVaNestedList XVaCreateNestedList(

    int , ...

);



extern int XRegisterIMInstantiateCallback(

    Display* ,
    struct _XrmHashBucketRec* ,
    char* ,
    char* ,
    XIDProc ,
    XPointer

);

extern int XUnregisterIMInstantiateCallback(

    Display* ,
    struct _XrmHashBucketRec* ,
    char* ,
    char* ,
    XIDProc ,
    XPointer

);

typedef void (*XConnectionWatchProc)(

    Display* ,
    XPointer ,
    int ,
    int ,
    XPointer*

);


extern int XInternalConnectionNumbers(

    Display* ,
    int** ,
    int*

);

extern void XProcessInternalConnection(

    Display* ,
    int

);

extern int XAddConnectionWatch(

    Display* ,
    XConnectionWatchProc ,
    XPointer

);

extern void XRemoveConnectionWatch(

    Display* ,
    XConnectionWatchProc ,
    XPointer

);

extern void XSetAuthorization(

    char * ,
    int ,
    char * ,
    int

);

extern int _Xmbtowc(

    wchar_t * ,




    char * ,
    int


);

extern int _Xwctomb(

    char * ,
    wchar_t

);


# 79 "/tmp/t852/include/tk.h" 2



# 1 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stddef.h" 1 3
# 83 "/tmp/t852/include/tk.h" 2
# 102 "/tmp/t852/include/tk.h"
typedef struct Tk_BindingTable_ *Tk_BindingTable;
typedef struct Tk_Canvas_ *Tk_Canvas;
typedef struct Tk_Cursor_ *Tk_Cursor;
typedef struct Tk_ErrorHandler_ *Tk_ErrorHandler;
typedef struct Tk_Font_ *Tk_Font;
typedef struct Tk_Image__ *Tk_Image;
typedef struct Tk_ImageMaster_ *Tk_ImageMaster;
typedef struct Tk_OptionTable_ *Tk_OptionTable;
typedef struct Tk_PostscriptInfo_ *Tk_PostscriptInfo;
typedef struct Tk_TextLayout_ *Tk_TextLayout;
typedef struct Tk_Window_ *Tk_Window;
typedef struct Tk_3DBorder_ *Tk_3DBorder;
typedef struct Tk_Style_ *Tk_Style;
typedef struct Tk_StyleEngine_ *Tk_StyleEngine;
typedef struct Tk_StyledElement_ *Tk_StyledElement;





typedef const char *Tk_Uid;






typedef enum {
    TK_OPTION_BOOLEAN,
    TK_OPTION_INT,
    TK_OPTION_DOUBLE,
    TK_OPTION_STRING,
    TK_OPTION_STRING_TABLE,
    TK_OPTION_COLOR,
    TK_OPTION_FONT,
    TK_OPTION_BITMAP,
    TK_OPTION_BORDER,
    TK_OPTION_RELIEF,
    TK_OPTION_CURSOR,
    TK_OPTION_JUSTIFY,
    TK_OPTION_ANCHOR,
    TK_OPTION_SYNONYM,
    TK_OPTION_PIXELS,
    TK_OPTION_WINDOW,
    TK_OPTION_END,
    TK_OPTION_CUSTOM,
    TK_OPTION_STYLE
} Tk_OptionType;
# 158 "/tmp/t852/include/tk.h"
typedef struct Tk_OptionSpec {
    Tk_OptionType type;


    const char *optionName;

    const char *dbName;
    const char *dbClass;
    const char *defValue;


    int objOffset;





    int internalOffset;







    int flags;

    ClientData clientData;


    int typeMask;






} Tk_OptionSpec;
# 211 "/tmp/t852/include/tk.h"
typedef int (Tk_CustomOptionSetProc) (ClientData clientData, Tcl_Interp *interp, Tk_Window tkwin, Tcl_Obj **value, char *widgRec, int offset, char *saveInternalPtr, int flags);


typedef Tcl_Obj *(Tk_CustomOptionGetProc) (ClientData clientData, Tk_Window tkwin, char *widgRec, int offset);

typedef void (Tk_CustomOptionRestoreProc) (ClientData clientData, Tk_Window tkwin, char *internalPtr, char *saveInternalPtr);

typedef void (Tk_CustomOptionFreeProc) (ClientData clientData, Tk_Window tkwin, char *internalPtr);


typedef struct Tk_ObjCustomOption {
    const char *name;
    Tk_CustomOptionSetProc *setProc;


    Tk_CustomOptionGetProc *getProc;



    Tk_CustomOptionRestoreProc *restoreProc;


    Tk_CustomOptionFreeProc *freeProc;


    ClientData clientData;

} Tk_ObjCustomOption;
# 260 "/tmp/t852/include/tk.h"
typedef struct Tk_SavedOption {
    struct TkOption *optionPtr;

    Tcl_Obj *valuePtr;


    double internalForm;
# 276 "/tmp/t852/include/tk.h"
} Tk_SavedOption;







typedef struct Tk_SavedOptions {
    char *recordPtr;

    Tk_Window tkwin;

    int numItems;
    Tk_SavedOption items[20];

    struct Tk_SavedOptions *nextPtr;




} Tk_SavedOptions;
# 313 "/tmp/t852/include/tk.h"
typedef int (Tk_OptionParseProc) (ClientData clientData, Tcl_Interp *interp, Tk_Window tkwin, char *value, char *widgRec, int offset);


typedef char *(Tk_OptionPrintProc) (ClientData clientData, Tk_Window tkwin, char *widgRec, int offset, Tcl_FreeProc **freeProcPtr);



typedef struct Tk_CustomOption {
    Tk_OptionParseProc *parseProc;


    Tk_OptionPrintProc *printProc;


    ClientData clientData;


} Tk_CustomOption;
# 339 "/tmp/t852/include/tk.h"
typedef struct Tk_ConfigSpec {
    int type;


    char *argvName;

    Tk_Uid dbName;
    Tk_Uid dbClass;
    Tk_Uid defValue;

    int offset;


    int specFlags;


    Tk_CustomOption *customPtr;



} Tk_ConfigSpec;






typedef enum {
    TK_CONFIG_BOOLEAN, TK_CONFIG_INT, TK_CONFIG_DOUBLE, TK_CONFIG_STRING,
    TK_CONFIG_UID, TK_CONFIG_COLOR, TK_CONFIG_FONT, TK_CONFIG_BITMAP,
    TK_CONFIG_BORDER, TK_CONFIG_RELIEF, TK_CONFIG_CURSOR,
    TK_CONFIG_ACTIVE_CURSOR, TK_CONFIG_JUSTIFY, TK_CONFIG_ANCHOR,
    TK_CONFIG_SYNONYM, TK_CONFIG_CAP_STYLE, TK_CONFIG_JOIN_STYLE,
    TK_CONFIG_PIXELS, TK_CONFIG_MM, TK_CONFIG_WINDOW, TK_CONFIG_CUSTOM,
    TK_CONFIG_END
} Tk_ConfigTypes;
# 402 "/tmp/t852/include/tk.h"
typedef struct {
    char *key;

    int type;
    char *src;

    char *dst;

    char *help;

} Tk_ArgvInfo;
# 447 "/tmp/t852/include/tk.h"
typedef enum {
    TK_DEFER_EVENT, TK_PROCESS_EVENT, TK_DISCARD_EVENT
} Tk_RestrictAction;
# 494 "/tmp/t852/include/tk.h"
typedef enum {
    TK_ANCHOR_N, TK_ANCHOR_NE, TK_ANCHOR_E, TK_ANCHOR_SE,
    TK_ANCHOR_S, TK_ANCHOR_SW, TK_ANCHOR_W, TK_ANCHOR_NW,
    TK_ANCHOR_CENTER
} Tk_Anchor;





typedef enum {
    TK_JUSTIFY_LEFT, TK_JUSTIFY_RIGHT, TK_JUSTIFY_CENTER
} Tk_Justify;






typedef struct Tk_FontMetrics {
    int ascent;



    int descent;



    int linespace;




} Tk_FontMetrics;
# 549 "/tmp/t852/include/tk.h"
typedef Window (Tk_ClassCreateProc) (Tk_Window tkwin, Window parent, ClientData instanceData);

typedef void (Tk_ClassWorldChangedProc) (ClientData instanceData);
typedef void (Tk_ClassModalProc) (Tk_Window tkwin, XEvent *eventPtr);


typedef struct Tk_ClassProcs {
    unsigned int size;
    Tk_ClassWorldChangedProc *worldChangedProc;



    Tk_ClassCreateProc *createProc;


    Tk_ClassModalProc *modalProc;



} Tk_ClassProcs;
# 594 "/tmp/t852/include/tk.h"
typedef void (Tk_GeomRequestProc) (ClientData clientData, Tk_Window tkwin);

typedef void (Tk_GeomLostSlaveProc) (ClientData clientData, Tk_Window tkwin);


typedef struct Tk_GeomMgr {
    const char *name;


    Tk_GeomRequestProc *requestProc;


    Tk_GeomLostSlaveProc *lostSlaveProc;




} Tk_GeomMgr;
# 654 "/tmp/t852/include/tk.h"
typedef struct {
    int type;
    unsigned long serial;
    int send_event;

    Display *display;
    Window event;
    Window root;
    Window subwindow;
    Time time;
    int x, y;

    int x_root, y_root;
    unsigned int state;
    Tk_Uid name;
    int same_screen;
    Tcl_Obj *user_data;



} XVirtualEvent;

typedef struct {
    int type;
    unsigned long serial;
    int send_event;

    Display *display;
    Window window;
} XActivateDeactivateEvent;
typedef XActivateDeactivateEvent XActivateEvent;
typedef XActivateDeactivateEvent XDeactivateEvent;
# 755 "/tmp/t852/include/tk.h"
typedef struct Tk_FakeWin {
    Display *display;
    char *dummy1;
    int screenNum;
    Visual *visual;
    int depth;
    Window window;
    char *dummy2;
    char *dummy3;
    Tk_Window parentPtr;
    char *dummy4;
    char *dummy5;
    char *pathName;
    Tk_Uid nameUid;
    Tk_Uid classUid;
    XWindowChanges changes;
    unsigned int dummy6;
    XSetWindowAttributes atts;
    unsigned long dummy7;
    unsigned int flags;
    char *dummy8;

    XIC dummy9;

    ClientData *dummy10;
    int dummy11;
    int dummy12;
    char *dummy13;
    char *dummy14;
    ClientData dummy15;
    int reqWidth, reqHeight;
    int internalBorderLeft;
    char *dummy16;
    char *dummy17;
    ClientData dummy18;
    char *dummy19;
    int internalBorderRight;
    int internalBorderTop;
    int internalBorderBottom;
    int minReqWidth;
    int minReqHeight;
} Tk_FakeWin;
# 892 "/tmp/t852/include/tk.h"
typedef enum {
    TK_STATE_NULL = -1, TK_STATE_ACTIVE, TK_STATE_DISABLED,
    TK_STATE_NORMAL, TK_STATE_HIDDEN
} Tk_State;

typedef struct Tk_SmoothMethod {
    char *name;
    int (*coordProc) (Tk_Canvas canvas, double *pointPtr, int numPoints, int numSteps, XPoint xPoints[], double dblPoints[]);


    void (*postscriptProc) (Tcl_Interp *interp, Tk_Canvas canvas, double *coordPtr, int numPoints, int numSteps);


} Tk_SmoothMethod;
# 915 "/tmp/t852/include/tk.h"
typedef struct Tk_Item {
    int id;

    struct Tk_Item *nextPtr;


    Tk_Uid staticTagSpace[3];

    Tk_Uid *tagPtr;


    int tagSpace;

    int numTags;

    struct Tk_ItemType *typePtr;

    int x1, y1, x2, y2;




    struct Tk_Item *prevPtr;


    Tk_State state;
    char *reserved1;
    int redraw_flags;
# 952 "/tmp/t852/include/tk.h"
} Tk_Item;
# 983 "/tmp/t852/include/tk.h"
typedef int Tk_ItemCreateProc (Tcl_Interp *interp, Tk_Canvas canvas, Tk_Item *itemPtr, int argc, Tcl_Obj *const objv[]);


typedef int Tk_ItemConfigureProc (Tcl_Interp *interp, Tk_Canvas canvas, Tk_Item *itemPtr, int argc, Tcl_Obj *const objv[], int flags);


typedef int Tk_ItemCoordProc (Tcl_Interp *interp, Tk_Canvas canvas, Tk_Item *itemPtr, int argc, Tcl_Obj *const argv[]);



typedef void Tk_ItemDeleteProc (Tk_Canvas canvas, Tk_Item *itemPtr, Display *display);

typedef void Tk_ItemDisplayProc (Tk_Canvas canvas, Tk_Item *itemPtr, Display *display, Drawable dst, int x, int y, int width, int height);


typedef double Tk_ItemPointProc (Tk_Canvas canvas, Tk_Item *itemPtr, double *pointPtr);

typedef int Tk_ItemAreaProc (Tk_Canvas canvas, Tk_Item *itemPtr, double *rectPtr);

typedef int Tk_ItemPostscriptProc (Tcl_Interp *interp, Tk_Canvas canvas, Tk_Item *itemPtr, int prepass);

typedef void Tk_ItemScaleProc (Tk_Canvas canvas, Tk_Item *itemPtr, double originX, double originY, double scaleX, double scaleY);


typedef void Tk_ItemTranslateProc (Tk_Canvas canvas, Tk_Item *itemPtr, double deltaX, double deltaY);

typedef int Tk_ItemIndexProc (Tcl_Interp *interp, Tk_Canvas canvas, Tk_Item *itemPtr, char *indexString, int *indexPtr);


typedef void Tk_ItemCursorProc (Tk_Canvas canvas, Tk_Item *itemPtr, int index);

typedef int Tk_ItemSelectionProc (Tk_Canvas canvas, Tk_Item *itemPtr, int offset, char *buffer, int maxBytes);


typedef void Tk_ItemInsertProc (Tk_Canvas canvas, Tk_Item *itemPtr, int beforeThis, char *string);

typedef void Tk_ItemDCharsProc (Tk_Canvas canvas, Tk_Item *itemPtr, int first, int last);




typedef struct Tk_ItemType {
    char *name;

    int itemSize;

    Tk_ItemCreateProc *createProc;


    Tk_ConfigSpec *configSpecs;


    Tk_ItemConfigureProc *configProc;


    Tk_ItemCoordProc *coordProc;

    Tk_ItemDeleteProc *deleteProc;


    Tk_ItemDisplayProc *displayProc;

    int alwaysRedraw;


    Tk_ItemPointProc *pointProc;

    Tk_ItemAreaProc *areaProc;

    Tk_ItemPostscriptProc *postscriptProc;


    Tk_ItemScaleProc *scaleProc;
    Tk_ItemTranslateProc *translateProc;


    Tk_ItemIndexProc *indexProc;


    Tk_ItemCursorProc *icursorProc;


    Tk_ItemSelectionProc *selectionProc;


    Tk_ItemInsertProc *insertProc;


    Tk_ItemDCharsProc *dCharsProc;


    struct Tk_ItemType *nextPtr;
    char *reserved1;
    int reserved2;
    char *reserved3;
    char *reserved4;
} Tk_ItemType;
# 1091 "/tmp/t852/include/tk.h"
typedef struct Tk_CanvasTextInfo {
    Tk_3DBorder selBorder;

    int selBorderWidth;

    XColor *selFgColorPtr;

    Tk_Item *selItemPtr;


    int selectFirst;

    int selectLast;

    Tk_Item *anchorItemPtr;


    int selectAnchor;



    Tk_3DBorder insertBorder;

    int insertWidth;

    int insertBorderWidth;

    Tk_Item *focusItemPtr;

    int gotFocus;

    int cursorOn;


} Tk_CanvasTextInfo;





typedef struct Tk_Dash {
    int number;
    union {
        char *pt;
        char array[sizeof(char *)];
    } pattern;
} Tk_Dash;

typedef struct Tk_TSOffset {
    int flags;
    int xoffset;
    int yoffset;
} Tk_TSOffset;
# 1158 "/tmp/t852/include/tk.h"
typedef struct Tk_Outline {
    GC gc;
    double width;
    double activeWidth;
    double disabledWidth;
    int offset;
    Tk_Dash dash;
    Tk_Dash activeDash;
    Tk_Dash disabledDash;
    void *reserved1;
    void *reserved2;
    void *reserved3;
    Tk_TSOffset tsoffset;
    XColor *color;
    XColor *activeColor;
    XColor *disabledColor;
    Pixmap stipple;
    Pixmap activeStipple;

    Pixmap disabledStipple;

} Tk_Outline;
# 1189 "/tmp/t852/include/tk.h"
typedef struct Tk_ImageType Tk_ImageType;





typedef int (Tk_ImageCreateProc) (Tcl_Interp *interp, char *name, int objc, Tcl_Obj *const objv[], Tk_ImageType *typePtr, Tk_ImageMaster master, ClientData *masterDataPtr);



typedef ClientData (Tk_ImageGetProc) (Tk_Window tkwin, ClientData masterData);

typedef void (Tk_ImageDisplayProc) (ClientData instanceData, Display *display, Drawable drawable, int imageX, int imageY, int width, int height, int drawableX, int drawableY);


typedef void (Tk_ImageFreeProc) (ClientData instanceData, Display *display);

typedef void (Tk_ImageDeleteProc) (ClientData masterData);
typedef void (Tk_ImageChangedProc) (ClientData clientData, int x, int y, int width, int height, int imageWidth, int imageHeight);


typedef int (Tk_ImagePostscriptProc) (ClientData clientData, Tcl_Interp *interp, Tk_Window tkwin, Tk_PostscriptInfo psinfo, int x, int y, int width, int height, int prepass);
# 1222 "/tmp/t852/include/tk.h"
struct Tk_ImageType {
    char *name;
    Tk_ImageCreateProc *createProc;


    Tk_ImageGetProc *getProc;


    Tk_ImageDisplayProc *displayProc;


    Tk_ImageFreeProc *freeProc;


    Tk_ImageDeleteProc *deleteProc;



    Tk_ImagePostscriptProc *postscriptProc;


    struct Tk_ImageType *nextPtr;



    char *reserved;
};
# 1263 "/tmp/t852/include/tk.h"
typedef void *Tk_PhotoHandle;





typedef struct Tk_PhotoImageBlock {
    unsigned char *pixelPtr;
    int width;
    int height;
    int pitch;

    int pixelSize;

    int offset[4];


} Tk_PhotoImageBlock;
# 1295 "/tmp/t852/include/tk.h"
typedef struct Tk_PhotoImageFormat Tk_PhotoImageFormat;
# 1314 "/tmp/t852/include/tk.h"
typedef int (Tk_ImageFileMatchProc) (Tcl_Channel chan, const char *fileName, Tcl_Obj *format, int *widthPtr, int *heightPtr, Tcl_Interp *interp);


typedef int (Tk_ImageStringMatchProc) (Tcl_Obj *dataObj, Tcl_Obj *format, int *widthPtr, int *heightPtr, Tcl_Interp *interp);


typedef int (Tk_ImageFileReadProc) (Tcl_Interp *interp, Tcl_Channel chan, const char *fileName, Tcl_Obj *format, Tk_PhotoHandle imageHandle, int destX, int destY, int width, int height, int srcX, int srcY);



typedef int (Tk_ImageStringReadProc) (Tcl_Interp *interp, Tcl_Obj *dataObj, Tcl_Obj *format, Tk_PhotoHandle imageHandle, int destX, int destY, int width, int height, int srcX, int srcY);


typedef int (Tk_ImageFileWriteProc) (Tcl_Interp *interp, const char *fileName, Tcl_Obj *format, Tk_PhotoImageBlock *blockPtr);

typedef int (Tk_ImageStringWriteProc) (Tcl_Interp *interp, Tcl_Obj *format, Tk_PhotoImageBlock *blockPtr);
# 1339 "/tmp/t852/include/tk.h"
struct Tk_PhotoImageFormat {
    char *name;
    Tk_ImageFileMatchProc *fileMatchProc;


    Tk_ImageStringMatchProc *stringMatchProc;


    Tk_ImageFileReadProc *fileReadProc;


    Tk_ImageStringReadProc *stringReadProc;


    Tk_ImageFileWriteProc *fileWriteProc;


    Tk_ImageStringWriteProc *stringWriteProc;



    struct Tk_PhotoImageFormat *nextPtr;



};
# 1391 "/tmp/t852/include/tk.h"
typedef void (Tk_GetElementSizeProc) (ClientData clientData, char *recordPtr, const Tk_OptionSpec **optionsPtr, Tk_Window tkwin, int width, int height, int inner, int *widthPtr, int *heightPtr);


typedef void (Tk_GetElementBoxProc) (ClientData clientData, char *recordPtr, const Tk_OptionSpec **optionsPtr, Tk_Window tkwin, int x, int y, int width, int height, int inner, int *xPtr, int *yPtr, int *widthPtr, int *heightPtr);



typedef int (Tk_GetElementBorderWidthProc) (ClientData clientData, char *recordPtr, const Tk_OptionSpec **optionsPtr, Tk_Window tkwin);

typedef void (Tk_DrawElementProc) (ClientData clientData, char *recordPtr, const Tk_OptionSpec **optionsPtr, Tk_Window tkwin, Drawable d, int x, int y, int width, int height, int state);



typedef struct Tk_ElementOptionSpec {
    char *name;
    Tk_OptionType type;

} Tk_ElementOptionSpec;

typedef struct Tk_ElementSpec {
    int version;
    char *name;
    Tk_ElementOptionSpec *options;


    Tk_GetElementSizeProc *getSize;



    Tk_GetElementBoxProc *getBox;


    Tk_GetElementBorderWidthProc *getBorderWidth;


    Tk_DrawElementProc *draw;

} Tk_ElementSpec;
# 1487 "/tmp/t852/include/tk.h"
const char * Tk_InitStubs (Tcl_Interp *interp, const char *version, int exact);

const char * Tk_PkgInitStubsCheck (Tcl_Interp *interp, const char *version, int exact);
# 1510 "/tmp/t852/include/tk.h"
typedef int (Tk_ErrorProc) (ClientData clientData, XErrorEvent *errEventPtr);

typedef void (Tk_EventProc) (ClientData clientData, XEvent *eventPtr);

typedef int (Tk_GenericProc) (ClientData clientData, XEvent *eventPtr);

typedef int (Tk_ClientMessageProc) (Tk_Window tkwin, XEvent *eventPtr);

typedef int (Tk_GetSelProc) (ClientData clientData, Tcl_Interp *interp, char *portion);

typedef void (Tk_LostSelProc) (ClientData clientData);
typedef Tk_RestrictAction (Tk_RestrictProc) ( ClientData clientData, XEvent *eventPtr);

typedef int (Tk_SelectionProc) (ClientData clientData, int offset, char *buffer, int maxBytes);
# 1534 "/tmp/t852/include/tk.h"
# 1 "/tmp/t852/include/tkDecls.h" 1
# 37 "/tmp/t852/include/tkDecls.h"
extern void Tk_MainLoop (void);




extern XColor * Tk_3DBorderColor (Tk_3DBorder border);




extern GC Tk_3DBorderGC (Tk_Window tkwin, Tk_3DBorder border,
                                int which);




extern void Tk_3DHorizontalBevel (Tk_Window tkwin,
                                Drawable drawable, Tk_3DBorder border, int x,
                                int y, int width, int height, int leftIn,
                                int rightIn, int topBevel, int relief);




extern void Tk_3DVerticalBevel (Tk_Window tkwin,
                                Drawable drawable, Tk_3DBorder border, int x,
                                int y, int width, int height, int leftBevel,
                                int relief);




extern void Tk_AddOption (Tk_Window tkwin, const char * name,
                                const char * value, int priority);




extern void Tk_BindEvent (Tk_BindingTable bindingTable,
                                XEvent * eventPtr, Tk_Window tkwin,
                                int numObjects, ClientData * objectPtr);




extern void Tk_CanvasDrawableCoords (Tk_Canvas canvas, double x,
                                double y, short * drawableXPtr,
                                short * drawableYPtr);




extern void Tk_CanvasEventuallyRedraw (Tk_Canvas canvas, int x1,
                                int y1, int x2, int y2);




extern int Tk_CanvasGetCoord (Tcl_Interp * interp,
                                Tk_Canvas canvas, const char * str,
                                double * doublePtr);




extern Tk_CanvasTextInfo * Tk_CanvasGetTextInfo (Tk_Canvas canvas);




extern int Tk_CanvasPsBitmap (Tcl_Interp * interp,
                                Tk_Canvas canvas, Pixmap bitmap, int x,
                                int y, int width, int height);




extern int Tk_CanvasPsColor (Tcl_Interp * interp,
                                Tk_Canvas canvas, XColor * colorPtr);




extern int Tk_CanvasPsFont (Tcl_Interp * interp,
                                Tk_Canvas canvas, Tk_Font font);




extern void Tk_CanvasPsPath (Tcl_Interp * interp,
                                Tk_Canvas canvas, double * coordPtr,
                                int numPoints);




extern int Tk_CanvasPsStipple (Tcl_Interp * interp,
                                Tk_Canvas canvas, Pixmap bitmap);




extern double Tk_CanvasPsY (Tk_Canvas canvas, double y);




extern void Tk_CanvasSetStippleOrigin (Tk_Canvas canvas, GC gc);




extern int Tk_CanvasTagsParseProc (ClientData clientData,
                                Tcl_Interp * interp, Tk_Window tkwin,
                                const char * value, char * widgRec,
                                int offset);




extern char * Tk_CanvasTagsPrintProc (ClientData clientData,
                                Tk_Window tkwin, char * widgRec, int offset,
                                Tcl_FreeProc ** freeProcPtr);




extern Tk_Window Tk_CanvasTkwin (Tk_Canvas canvas);




extern void Tk_CanvasWindowCoords (Tk_Canvas canvas, double x,
                                double y, short * screenXPtr,
                                short * screenYPtr);




extern void Tk_ChangeWindowAttributes (Tk_Window tkwin,
                                unsigned long valueMask,
                                XSetWindowAttributes * attsPtr);




extern int Tk_CharBbox (Tk_TextLayout layout, int index,
                                int * xPtr, int * yPtr, int * widthPtr,
                                int * heightPtr);




extern void Tk_ClearSelection (Tk_Window tkwin, Atom selection);




extern int Tk_ClipboardAppend (Tcl_Interp * interp,
                                Tk_Window tkwin, Atom target, Atom format,
                                char* buffer);




extern int Tk_ClipboardClear (Tcl_Interp * interp,
                                Tk_Window tkwin);




extern int Tk_ConfigureInfo (Tcl_Interp * interp,
                                Tk_Window tkwin, Tk_ConfigSpec * specs,
                                char * widgRec, const char * argvName,
                                int flags);




extern int Tk_ConfigureValue (Tcl_Interp * interp,
                                Tk_Window tkwin, Tk_ConfigSpec * specs,
                                char * widgRec, const char * argvName,
                                int flags);




extern int Tk_ConfigureWidget (Tcl_Interp * interp,
                                Tk_Window tkwin, Tk_ConfigSpec * specs,
                                int argc, char ** argv,
                                char * widgRec, int flags);




extern void Tk_ConfigureWindow (Tk_Window tkwin,
                                unsigned int valueMask,
                                XWindowChanges * valuePtr);




extern Tk_TextLayout Tk_ComputeTextLayout (Tk_Font font, const char * str,
                                int numChars, int wrapLength,
                                Tk_Justify justify, int flags,
                                int * widthPtr, int * heightPtr);




extern Tk_Window Tk_CoordsToWindow (int rootX, int rootY,
                                Tk_Window tkwin);




extern unsigned long Tk_CreateBinding (Tcl_Interp * interp,
                                Tk_BindingTable bindingTable,
                                ClientData object, const char * eventStr,
                                const char * command, int append);




extern Tk_BindingTable Tk_CreateBindingTable (Tcl_Interp * interp);




extern Tk_ErrorHandler Tk_CreateErrorHandler (Display * display, int errNum,
                                int request, int minorCode,
                                Tk_ErrorProc * errorProc,
                                ClientData clientData);




extern void Tk_CreateEventHandler (Tk_Window token,
                                unsigned long mask, Tk_EventProc * proc,
                                ClientData clientData);




extern void Tk_CreateGenericHandler (Tk_GenericProc * proc,
                                ClientData clientData);




extern void Tk_CreateImageType (Tk_ImageType * typePtr);




extern void Tk_CreateItemType (Tk_ItemType * typePtr);




extern void Tk_CreatePhotoImageFormat (
                                Tk_PhotoImageFormat * formatPtr);




extern void Tk_CreateSelHandler (Tk_Window tkwin, Atom selection,
                                Atom target, Tk_SelectionProc * proc,
                                ClientData clientData, Atom format);




extern Tk_Window Tk_CreateWindow (Tcl_Interp * interp,
                                Tk_Window parent, const char * name,
                                const char * screenName);




extern Tk_Window Tk_CreateWindowFromPath (Tcl_Interp * interp,
                                Tk_Window tkwin, const char * pathName,
                                const char * screenName);




extern int Tk_DefineBitmap (Tcl_Interp * interp,
                                const char * name, const char * source,
                                int width, int height);




extern void Tk_DefineCursor (Tk_Window window, Tk_Cursor cursor);




extern void Tk_DeleteAllBindings (Tk_BindingTable bindingTable,
                                ClientData object);




extern int Tk_DeleteBinding (Tcl_Interp * interp,
                                Tk_BindingTable bindingTable,
                                ClientData object, const char * eventStr);




extern void Tk_DeleteBindingTable (Tk_BindingTable bindingTable);




extern void Tk_DeleteErrorHandler (Tk_ErrorHandler handler);




extern void Tk_DeleteEventHandler (Tk_Window token,
                                unsigned long mask, Tk_EventProc * proc,
                                ClientData clientData);




extern void Tk_DeleteGenericHandler (Tk_GenericProc * proc,
                                ClientData clientData);




extern void Tk_DeleteImage (Tcl_Interp * interp,
                                const char * name);




extern void Tk_DeleteSelHandler (Tk_Window tkwin, Atom selection,
                                Atom target);




extern void Tk_DestroyWindow (Tk_Window tkwin);




extern char * Tk_DisplayName (Tk_Window tkwin);




extern int Tk_DistanceToTextLayout (Tk_TextLayout layout, int x,
                                int y);




extern void Tk_Draw3DPolygon (Tk_Window tkwin, Drawable drawable,
                                Tk_3DBorder border, XPoint * pointPtr,
                                int numPoints, int borderWidth,
                                int leftRelief);




extern void Tk_Draw3DRectangle (Tk_Window tkwin,
                                Drawable drawable, Tk_3DBorder border, int x,
                                int y, int width, int height,
                                int borderWidth, int relief);




extern void Tk_DrawChars (Display * display, Drawable drawable,
                                GC gc, Tk_Font tkfont, const char * source,
                                int numBytes, int x, int y);




extern void Tk_DrawFocusHighlight (Tk_Window tkwin, GC gc,
                                int width, Drawable drawable);




extern void Tk_DrawTextLayout (Display * display,
                                Drawable drawable, GC gc,
                                Tk_TextLayout layout, int x, int y,
                                int firstChar, int lastChar);




extern void Tk_Fill3DPolygon (Tk_Window tkwin, Drawable drawable,
                                Tk_3DBorder border, XPoint * pointPtr,
                                int numPoints, int borderWidth,
                                int leftRelief);




extern void Tk_Fill3DRectangle (Tk_Window tkwin,
                                Drawable drawable, Tk_3DBorder border, int x,
                                int y, int width, int height,
                                int borderWidth, int relief);




extern Tk_PhotoHandle Tk_FindPhoto (Tcl_Interp * interp,
                                const char * imageName);




extern Font Tk_FontId (Tk_Font font);




extern void Tk_Free3DBorder (Tk_3DBorder border);




extern void Tk_FreeBitmap (Display * display, Pixmap bitmap);




extern void Tk_FreeColor (XColor * colorPtr);




extern void Tk_FreeColormap (Display * display,
                                Colormap colormap);




extern void Tk_FreeCursor (Display * display, Tk_Cursor cursor);




extern void Tk_FreeFont (Tk_Font f);




extern void Tk_FreeGC (Display * display, GC gc);




extern void Tk_FreeImage (Tk_Image image);




extern void Tk_FreeOptions (Tk_ConfigSpec * specs,
                                char * widgRec, Display * display,
                                int needFlags);




extern void Tk_FreePixmap (Display * display, Pixmap pixmap);




extern void Tk_FreeTextLayout (Tk_TextLayout textLayout);




extern void Tk_FreeXId (Display * display, XID xid);




extern GC Tk_GCForColor (XColor * colorPtr, Drawable drawable);




extern void Tk_GeometryRequest (Tk_Window tkwin, int reqWidth,
                                int reqHeight);




extern Tk_3DBorder Tk_Get3DBorder (Tcl_Interp * interp, Tk_Window tkwin,
                                Tk_Uid colorName);




extern void Tk_GetAllBindings (Tcl_Interp * interp,
                                Tk_BindingTable bindingTable,
                                ClientData object);




extern int Tk_GetAnchor (Tcl_Interp * interp, const char * str,
                                Tk_Anchor * anchorPtr);




extern char * Tk_GetAtomName (Tk_Window tkwin, Atom atom);




extern char * Tk_GetBinding (Tcl_Interp * interp,
                                Tk_BindingTable bindingTable,
                                ClientData object, const char * eventStr);




extern Pixmap Tk_GetBitmap (Tcl_Interp * interp, Tk_Window tkwin,
                                const char * str);




extern Pixmap Tk_GetBitmapFromData (Tcl_Interp * interp,
                                Tk_Window tkwin, const char * source,
                                int width, int height);




extern int Tk_GetCapStyle (Tcl_Interp * interp,
                                const char * str, int * capPtr);




extern XColor * Tk_GetColor (Tcl_Interp * interp, Tk_Window tkwin,
                                Tk_Uid name);




extern XColor * Tk_GetColorByValue (Tk_Window tkwin,
                                XColor * colorPtr);




extern Colormap Tk_GetColormap (Tcl_Interp * interp, Tk_Window tkwin,
                                const char * str);




extern Tk_Cursor Tk_GetCursor (Tcl_Interp * interp, Tk_Window tkwin,
                                Tk_Uid str);




extern Tk_Cursor Tk_GetCursorFromData (Tcl_Interp * interp,
                                Tk_Window tkwin, const char * source,
                                const char * mask, int width, int height,
                                int xHot, int yHot, Tk_Uid fg, Tk_Uid bg);




extern Tk_Font Tk_GetFont (Tcl_Interp * interp, Tk_Window tkwin,
                                const char * str);




extern Tk_Font Tk_GetFontFromObj (Tk_Window tkwin, Tcl_Obj * objPtr);




extern void Tk_GetFontMetrics (Tk_Font font,
                                Tk_FontMetrics * fmPtr);




extern GC Tk_GetGC (Tk_Window tkwin, unsigned long valueMask,
                                XGCValues * valuePtr);




extern Tk_Image Tk_GetImage (Tcl_Interp * interp, Tk_Window tkwin,
                                const char * name,
                                Tk_ImageChangedProc * changeProc,
                                ClientData clientData);




extern ClientData Tk_GetImageMasterData (Tcl_Interp * interp,
                                const char * name,
                                Tk_ImageType ** typePtrPtr);




extern Tk_ItemType * Tk_GetItemTypes (void);




extern int Tk_GetJoinStyle (Tcl_Interp * interp,
                                const char * str, int * joinPtr);




extern int Tk_GetJustify (Tcl_Interp * interp, const char * str,
                                Tk_Justify * justifyPtr);




extern int Tk_GetNumMainWindows (void);




extern Tk_Uid Tk_GetOption (Tk_Window tkwin, const char * name,
                                const char * className);




extern int Tk_GetPixels (Tcl_Interp * interp, Tk_Window tkwin,
                                const char * str, int * intPtr);




extern Pixmap Tk_GetPixmap (Display * display, Drawable d,
                                int width, int height, int depth);




extern int Tk_GetRelief (Tcl_Interp * interp, const char * name,
                                int * reliefPtr);




extern void Tk_GetRootCoords (Tk_Window tkwin, int * xPtr,
                                int * yPtr);




extern int Tk_GetScrollInfo (Tcl_Interp * interp, int argc,
                                char ** argv, double * dblPtr,
                                int * intPtr);




extern int Tk_GetScreenMM (Tcl_Interp * interp, Tk_Window tkwin,
                                const char * str, double * doublePtr);




extern int Tk_GetSelection (Tcl_Interp * interp,
                                Tk_Window tkwin, Atom selection, Atom target,
                                Tk_GetSelProc * proc, ClientData clientData);




extern Tk_Uid Tk_GetUid (const char * str);




extern Visual * Tk_GetVisual (Tcl_Interp * interp, Tk_Window tkwin,
                                const char * str, int * depthPtr,
                                Colormap * colormapPtr);




extern void Tk_GetVRootGeometry (Tk_Window tkwin, int * xPtr,
                                int * yPtr, int * widthPtr, int * heightPtr);




extern int Tk_Grab (Tcl_Interp * interp, Tk_Window tkwin,
                                int grabGlobal);




extern void Tk_HandleEvent (XEvent * eventPtr);




extern Tk_Window Tk_IdToWindow (Display * display, Window window);




extern void Tk_ImageChanged (Tk_ImageMaster master, int x, int y,
                                int width, int height, int imageWidth,
                                int imageHeight);




extern int Tk_Init (Tcl_Interp * interp);




extern Atom Tk_InternAtom (Tk_Window tkwin, const char * name);




extern int Tk_IntersectTextLayout (Tk_TextLayout layout, int x,
                                int y, int width, int height);




extern void Tk_MaintainGeometry (Tk_Window slave,
                                Tk_Window master, int x, int y, int width,
                                int height);




extern Tk_Window Tk_MainWindow (Tcl_Interp * interp);




extern void Tk_MakeWindowExist (Tk_Window tkwin);




extern void Tk_ManageGeometry (Tk_Window tkwin,
                                const Tk_GeomMgr * mgrPtr,
                                ClientData clientData);




extern void Tk_MapWindow (Tk_Window tkwin);




extern int Tk_MeasureChars (Tk_Font tkfont, const char * source,
                                int numBytes, int maxPixels, int flags,
                                int * lengthPtr);




extern void Tk_MoveResizeWindow (Tk_Window tkwin, int x, int y,
                                int width, int height);




extern void Tk_MoveWindow (Tk_Window tkwin, int x, int y);




extern void Tk_MoveToplevelWindow (Tk_Window tkwin, int x, int y);




extern char * Tk_NameOf3DBorder (Tk_3DBorder border);




extern char * Tk_NameOfAnchor (Tk_Anchor anchor);




extern char * Tk_NameOfBitmap (Display * display,
                                Pixmap bitmap);




extern char * Tk_NameOfCapStyle (int cap);




extern char * Tk_NameOfColor (XColor * colorPtr);




extern char * Tk_NameOfCursor (Display * display,
                                Tk_Cursor cursor);




extern char * Tk_NameOfFont (Tk_Font font);




extern char * Tk_NameOfImage (Tk_ImageMaster imageMaster);




extern char * Tk_NameOfJoinStyle (int join);




extern char * Tk_NameOfJustify (Tk_Justify justify);




extern char * Tk_NameOfRelief (int relief);




extern Tk_Window Tk_NameToWindow (Tcl_Interp * interp,
                                const char * pathName, Tk_Window tkwin);




extern void Tk_OwnSelection (Tk_Window tkwin, Atom selection,
                                Tk_LostSelProc * proc, ClientData clientData);




extern int Tk_ParseArgv (Tcl_Interp * interp, Tk_Window tkwin,
                                int * argcPtr, char ** argv,
                                Tk_ArgvInfo * argTable, int flags);




extern void Tk_PhotoPutBlock_NoComposite (Tk_PhotoHandle handle,
                                Tk_PhotoImageBlock * blockPtr, int x, int y,
                                int width, int height);




extern void Tk_PhotoPutZoomedBlock_NoComposite (
                                Tk_PhotoHandle handle,
                                Tk_PhotoImageBlock * blockPtr, int x, int y,
                                int width, int height, int zoomX, int zoomY,
                                int subsampleX, int subsampleY);




extern int Tk_PhotoGetImage (Tk_PhotoHandle handle,
                                Tk_PhotoImageBlock * blockPtr);




extern void Tk_PhotoBlank (Tk_PhotoHandle handle);




extern void Tk_PhotoExpand_Panic (Tk_PhotoHandle handle,
                                int width, int height);




extern void Tk_PhotoGetSize (Tk_PhotoHandle handle,
                                int * widthPtr, int * heightPtr);




extern void Tk_PhotoSetSize_Panic (Tk_PhotoHandle handle,
                                int width, int height);




extern int Tk_PointToChar (Tk_TextLayout layout, int x, int y);




extern int Tk_PostscriptFontName (Tk_Font tkfont,
                                Tcl_DString * dsPtr);




extern void Tk_PreserveColormap (Display * display,
                                Colormap colormap);




extern void Tk_QueueWindowEvent (XEvent * eventPtr,
                                Tcl_QueuePosition position);




extern void Tk_RedrawImage (Tk_Image image, int imageX,
                                int imageY, int width, int height,
                                Drawable drawable, int drawableX,
                                int drawableY);




extern void Tk_ResizeWindow (Tk_Window tkwin, int width,
                                int height);




extern int Tk_RestackWindow (Tk_Window tkwin, int aboveBelow,
                                Tk_Window other);




extern Tk_RestrictProc * Tk_RestrictEvents (Tk_RestrictProc * proc,
                                ClientData arg, ClientData * prevArgPtr);




extern int Tk_SafeInit (Tcl_Interp * interp);




extern const char * Tk_SetAppName (Tk_Window tkwin, const char * name);




extern void Tk_SetBackgroundFromBorder (Tk_Window tkwin,
                                Tk_3DBorder border);




extern void Tk_SetClass (Tk_Window tkwin, const char * className);




extern void Tk_SetGrid (Tk_Window tkwin, int reqWidth,
                                int reqHeight, int gridWidth, int gridHeight);




extern void Tk_SetInternalBorder (Tk_Window tkwin, int width);




extern void Tk_SetWindowBackground (Tk_Window tkwin,
                                unsigned long pixel);




extern void Tk_SetWindowBackgroundPixmap (Tk_Window tkwin,
                                Pixmap pixmap);




extern void Tk_SetWindowBorder (Tk_Window tkwin,
                                unsigned long pixel);




extern void Tk_SetWindowBorderWidth (Tk_Window tkwin, int width);




extern void Tk_SetWindowBorderPixmap (Tk_Window tkwin,
                                Pixmap pixmap);




extern void Tk_SetWindowColormap (Tk_Window tkwin,
                                Colormap colormap);




extern int Tk_SetWindowVisual (Tk_Window tkwin, Visual * visual,
                                int depth, Colormap colormap);




extern void Tk_SizeOfBitmap (Display * display, Pixmap bitmap,
                                int * widthPtr, int * heightPtr);




extern void Tk_SizeOfImage (Tk_Image image, int * widthPtr,
                                int * heightPtr);




extern int Tk_StrictMotif (Tk_Window tkwin);




extern void Tk_TextLayoutToPostscript (Tcl_Interp * interp,
                                Tk_TextLayout layout);




extern int Tk_TextWidth (Tk_Font font, const char * str,
                                int numBytes);




extern void Tk_UndefineCursor (Tk_Window window);




extern void Tk_UnderlineChars (Display * display,
                                Drawable drawable, GC gc, Tk_Font tkfont,
                                const char * source, int x, int y,
                                int firstByte, int lastByte);




extern void Tk_UnderlineTextLayout (Display * display,
                                Drawable drawable, GC gc,
                                Tk_TextLayout layout, int x, int y,
                                int underline);




extern void Tk_Ungrab (Tk_Window tkwin);




extern void Tk_UnmaintainGeometry (Tk_Window slave,
                                Tk_Window master);




extern void Tk_UnmapWindow (Tk_Window tkwin);




extern void Tk_UnsetGrid (Tk_Window tkwin);




extern void Tk_UpdatePointer (Tk_Window tkwin, int x, int y,
                                int state);




extern Pixmap Tk_AllocBitmapFromObj (Tcl_Interp * interp,
                                Tk_Window tkwin, Tcl_Obj * objPtr);




extern Tk_3DBorder Tk_Alloc3DBorderFromObj (Tcl_Interp * interp,
                                Tk_Window tkwin, Tcl_Obj * objPtr);




extern XColor * Tk_AllocColorFromObj (Tcl_Interp * interp,
                                Tk_Window tkwin, Tcl_Obj * objPtr);




extern Tk_Cursor Tk_AllocCursorFromObj (Tcl_Interp * interp,
                                Tk_Window tkwin, Tcl_Obj * objPtr);




extern Tk_Font Tk_AllocFontFromObj (Tcl_Interp * interp,
                                Tk_Window tkwin, Tcl_Obj * objPtr);




extern Tk_OptionTable Tk_CreateOptionTable (Tcl_Interp * interp,
                                const Tk_OptionSpec * templatePtr);




extern void Tk_DeleteOptionTable (Tk_OptionTable optionTable);




extern void Tk_Free3DBorderFromObj (Tk_Window tkwin,
                                Tcl_Obj * objPtr);




extern void Tk_FreeBitmapFromObj (Tk_Window tkwin,
                                Tcl_Obj * objPtr);




extern void Tk_FreeColorFromObj (Tk_Window tkwin,
                                Tcl_Obj * objPtr);




extern void Tk_FreeConfigOptions (char * recordPtr,
                                Tk_OptionTable optionToken, Tk_Window tkwin);




extern void Tk_FreeSavedOptions (Tk_SavedOptions * savePtr);




extern void Tk_FreeCursorFromObj (Tk_Window tkwin,
                                Tcl_Obj * objPtr);




extern void Tk_FreeFontFromObj (Tk_Window tkwin,
                                Tcl_Obj * objPtr);




extern Tk_3DBorder Tk_Get3DBorderFromObj (Tk_Window tkwin,
                                Tcl_Obj * objPtr);




extern int Tk_GetAnchorFromObj (Tcl_Interp * interp,
                                Tcl_Obj * objPtr, Tk_Anchor * anchorPtr);




extern Pixmap Tk_GetBitmapFromObj (Tk_Window tkwin,
                                Tcl_Obj * objPtr);




extern XColor * Tk_GetColorFromObj (Tk_Window tkwin,
                                Tcl_Obj * objPtr);




extern Tk_Cursor Tk_GetCursorFromObj (Tk_Window tkwin,
                                Tcl_Obj * objPtr);




extern Tcl_Obj * Tk_GetOptionInfo (Tcl_Interp * interp,
                                char * recordPtr, Tk_OptionTable optionTable,
                                Tcl_Obj * namePtr, Tk_Window tkwin);




extern Tcl_Obj * Tk_GetOptionValue (Tcl_Interp * interp,
                                char * recordPtr, Tk_OptionTable optionTable,
                                Tcl_Obj * namePtr, Tk_Window tkwin);




extern int Tk_GetJustifyFromObj (Tcl_Interp * interp,
                                Tcl_Obj * objPtr, Tk_Justify * justifyPtr);




extern int Tk_GetMMFromObj (Tcl_Interp * interp,
                                Tk_Window tkwin, Tcl_Obj * objPtr,
                                double * doublePtr);




extern int Tk_GetPixelsFromObj (Tcl_Interp * interp,
                                Tk_Window tkwin, Tcl_Obj * objPtr,
                                int * intPtr);




extern int Tk_GetReliefFromObj (Tcl_Interp * interp,
                                Tcl_Obj * objPtr, int * resultPtr);




extern int Tk_GetScrollInfoObj (Tcl_Interp * interp, int objc,
                                Tcl_Obj *const objv[], double * dblPtr,
                                int * intPtr);




extern int Tk_InitOptions (Tcl_Interp * interp,
                                char * recordPtr, Tk_OptionTable optionToken,
                                Tk_Window tkwin);




extern void Tk_MainEx (int argc, char ** argv,
                                Tcl_AppInitProc * appInitProc,
                                Tcl_Interp * interp);




extern void Tk_RestoreSavedOptions (Tk_SavedOptions * savePtr);




extern int Tk_SetOptions (Tcl_Interp * interp, char * recordPtr,
                                Tk_OptionTable optionTable, int objc,
                                Tcl_Obj *const objv[], Tk_Window tkwin,
                                Tk_SavedOptions * savePtr, int * maskPtr);




extern void Tk_InitConsoleChannels (Tcl_Interp * interp);




extern int Tk_CreateConsoleWindow (Tcl_Interp * interp);




extern void Tk_CreateSmoothMethod (Tcl_Interp * interp,
                                Tk_SmoothMethod * method);






extern int Tk_GetDash (Tcl_Interp * interp, const char * value,
                                Tk_Dash * dash);




extern void Tk_CreateOutline (Tk_Outline * outline);




extern void Tk_DeleteOutline (Display * display,
                                Tk_Outline * outline);




extern int Tk_ConfigOutlineGC (XGCValues * gcValues,
                                Tk_Canvas canvas, Tk_Item * item,
                                Tk_Outline * outline);




extern int Tk_ChangeOutlineGC (Tk_Canvas canvas, Tk_Item * item,
                                Tk_Outline * outline);




extern int Tk_ResetOutlineGC (Tk_Canvas canvas, Tk_Item * item,
                                Tk_Outline * outline);




extern int Tk_CanvasPsOutline (Tk_Canvas canvas, Tk_Item * item,
                                Tk_Outline * outline);




extern void Tk_SetTSOrigin (Tk_Window tkwin, GC gc, int x, int y);




extern int Tk_CanvasGetCoordFromObj (Tcl_Interp * interp,
                                Tk_Canvas canvas, Tcl_Obj * obj,
                                double * doublePtr);




extern void Tk_CanvasSetOffset (Tk_Canvas canvas, GC gc,
                                Tk_TSOffset * offset);




extern void Tk_DitherPhoto (Tk_PhotoHandle handle, int x, int y,
                                int width, int height);




extern int Tk_PostscriptBitmap (Tcl_Interp * interp,
                                Tk_Window tkwin, Tk_PostscriptInfo psInfo,
                                Pixmap bitmap, int startX, int startY,
                                int width, int height);




extern int Tk_PostscriptColor (Tcl_Interp * interp,
                                Tk_PostscriptInfo psInfo, XColor * colorPtr);




extern int Tk_PostscriptFont (Tcl_Interp * interp,
                                Tk_PostscriptInfo psInfo, Tk_Font font);




extern int Tk_PostscriptImage (Tk_Image image,
                                Tcl_Interp * interp, Tk_Window tkwin,
                                Tk_PostscriptInfo psinfo, int x, int y,
                                int width, int height, int prepass);




extern void Tk_PostscriptPath (Tcl_Interp * interp,
                                Tk_PostscriptInfo psInfo, double * coordPtr,
                                int numPoints);




extern int Tk_PostscriptStipple (Tcl_Interp * interp,
                                Tk_Window tkwin, Tk_PostscriptInfo psInfo,
                                Pixmap bitmap);




extern double Tk_PostscriptY (double y, Tk_PostscriptInfo psInfo);




extern int Tk_PostscriptPhoto (Tcl_Interp * interp,
                                Tk_PhotoImageBlock * blockPtr,
                                Tk_PostscriptInfo psInfo, int width,
                                int height);




extern void Tk_CreateClientMessageHandler (
                                Tk_ClientMessageProc * proc);




extern void Tk_DeleteClientMessageHandler (
                                Tk_ClientMessageProc * proc);




extern Tk_Window Tk_CreateAnonymousWindow (Tcl_Interp * interp,
                                Tk_Window parent, const char * screenName);




extern void Tk_SetClassProcs (Tk_Window tkwin,
                                Tk_ClassProcs * procs,
                                ClientData instanceData);




extern void Tk_SetInternalBorderEx (Tk_Window tkwin, int left,
                                int right, int top, int bottom);




extern void Tk_SetMinimumRequestSize (Tk_Window tkwin,
                                int minWidth, int minHeight);




extern void Tk_SetCaretPos (Tk_Window tkwin, int x, int y,
                                int height);




extern void Tk_PhotoPutBlock_Panic (Tk_PhotoHandle handle,
                                Tk_PhotoImageBlock * blockPtr, int x, int y,
                                int width, int height, int compRule);




extern void Tk_PhotoPutZoomedBlock_Panic (Tk_PhotoHandle handle,
                                Tk_PhotoImageBlock * blockPtr, int x, int y,
                                int width, int height, int zoomX, int zoomY,
                                int subsampleX, int subsampleY, int compRule);




extern int Tk_CollapseMotionEvents (Display * display,
                                int collapse);




extern Tk_StyleEngine Tk_RegisterStyleEngine (const char * name,
                                Tk_StyleEngine parent);




extern Tk_StyleEngine Tk_GetStyleEngine (const char * name);




extern int Tk_RegisterStyledElement (Tk_StyleEngine engine,
                                Tk_ElementSpec * templatePtr);




extern int Tk_GetElementId (const char * name);




extern Tk_Style Tk_CreateStyle (const char * name,
                                Tk_StyleEngine engine, ClientData clientData);




extern Tk_Style Tk_GetStyle (Tcl_Interp * interp, const char * name);




extern void Tk_FreeStyle (Tk_Style style);




extern const char * Tk_NameOfStyle (Tk_Style style);




extern Tk_Style Tk_AllocStyleFromObj (Tcl_Interp * interp,
                                Tcl_Obj * objPtr);




extern Tk_Style Tk_GetStyleFromObj (Tcl_Obj * objPtr);




extern void Tk_FreeStyleFromObj (Tcl_Obj * objPtr);




extern Tk_StyledElement Tk_GetStyledElement (Tk_Style style, int elementId,
                                Tk_OptionTable optionTable);




extern void Tk_GetElementSize (Tk_Style style,
                                Tk_StyledElement element, char * recordPtr,
                                Tk_Window tkwin, int width, int height,
                                int inner, int * widthPtr, int * heightPtr);




extern void Tk_GetElementBox (Tk_Style style,
                                Tk_StyledElement element, char * recordPtr,
                                Tk_Window tkwin, int x, int y, int width,
                                int height, int inner, int * xPtr,
                                int * yPtr, int * widthPtr, int * heightPtr);




extern int Tk_GetElementBorderWidth (Tk_Style style,
                                Tk_StyledElement element, char * recordPtr,
                                Tk_Window tkwin);




extern void Tk_DrawElement (Tk_Style style,
                                Tk_StyledElement element, char * recordPtr,
                                Tk_Window tkwin, Drawable d, int x, int y,
                                int width, int height, int state);




extern int Tk_PhotoExpand (Tcl_Interp * interp,
                                Tk_PhotoHandle handle, int width, int height);




extern int Tk_PhotoPutBlock (Tcl_Interp * interp,
                                Tk_PhotoHandle handle,
                                Tk_PhotoImageBlock * blockPtr, int x, int y,
                                int width, int height, int compRule);




extern int Tk_PhotoPutZoomedBlock (Tcl_Interp * interp,
                                Tk_PhotoHandle handle,
                                Tk_PhotoImageBlock * blockPtr, int x, int y,
                                int width, int height, int zoomX, int zoomY,
                                int subsampleX, int subsampleY, int compRule);




extern int Tk_PhotoSetSize (Tcl_Interp * interp,
                                Tk_PhotoHandle handle, int width, int height);




extern long Tk_GetUserInactiveTime (Display * dpy);




extern void Tk_ResetUserInactiveTime (Display * dpy);




extern Tcl_Interp * Tk_Interp (Tk_Window tkwin);




extern void Tk_CreateOldImageType (Tk_ImageType * typePtr);




extern void Tk_CreateOldPhotoImageFormat (
                                Tk_PhotoImageFormat * formatPtr);


typedef struct TkStubHooks {
    struct TkPlatStubs *tkPlatStubs;
    struct TkIntStubs *tkIntStubs;
    struct TkIntPlatStubs *tkIntPlatStubs;
    struct TkIntXlibStubs *tkIntXlibStubs;
} TkStubHooks;

typedef struct TkStubs {
    int magic;
    struct TkStubHooks *hooks;

    void (*tk_MainLoop) (void);
    XColor * (*tk_3DBorderColor) (Tk_3DBorder border);
    GC (*tk_3DBorderGC) (Tk_Window tkwin, Tk_3DBorder border, int which);
    void (*tk_3DHorizontalBevel) (Tk_Window tkwin, Drawable drawable, Tk_3DBorder border, int x, int y, int width, int height, int leftIn, int rightIn, int topBevel, int relief);
    void (*tk_3DVerticalBevel) (Tk_Window tkwin, Drawable drawable, Tk_3DBorder border, int x, int y, int width, int height, int leftBevel, int relief);
    void (*tk_AddOption) (Tk_Window tkwin, const char * name, const char * value, int priority);
    void (*tk_BindEvent) (Tk_BindingTable bindingTable, XEvent * eventPtr, Tk_Window tkwin, int numObjects, ClientData * objectPtr);
    void (*tk_CanvasDrawableCoords) (Tk_Canvas canvas, double x, double y, short * drawableXPtr, short * drawableYPtr);
    void (*tk_CanvasEventuallyRedraw) (Tk_Canvas canvas, int x1, int y1, int x2, int y2);
    int (*tk_CanvasGetCoord) (Tcl_Interp * interp, Tk_Canvas canvas, const char * str, double * doublePtr);
    Tk_CanvasTextInfo * (*tk_CanvasGetTextInfo) (Tk_Canvas canvas);
    int (*tk_CanvasPsBitmap) (Tcl_Interp * interp, Tk_Canvas canvas, Pixmap bitmap, int x, int y, int width, int height);
    int (*tk_CanvasPsColor) (Tcl_Interp * interp, Tk_Canvas canvas, XColor * colorPtr);
    int (*tk_CanvasPsFont) (Tcl_Interp * interp, Tk_Canvas canvas, Tk_Font font);
    void (*tk_CanvasPsPath) (Tcl_Interp * interp, Tk_Canvas canvas, double * coordPtr, int numPoints);
    int (*tk_CanvasPsStipple) (Tcl_Interp * interp, Tk_Canvas canvas, Pixmap bitmap);
    double (*tk_CanvasPsY) (Tk_Canvas canvas, double y);
    void (*tk_CanvasSetStippleOrigin) (Tk_Canvas canvas, GC gc);
    int (*tk_CanvasTagsParseProc) (ClientData clientData, Tcl_Interp * interp, Tk_Window tkwin, const char * value, char * widgRec, int offset);
    char * (*tk_CanvasTagsPrintProc) (ClientData clientData, Tk_Window tkwin, char * widgRec, int offset, Tcl_FreeProc ** freeProcPtr);
    Tk_Window (*tk_CanvasTkwin) (Tk_Canvas canvas);
    void (*tk_CanvasWindowCoords) (Tk_Canvas canvas, double x, double y, short * screenXPtr, short * screenYPtr);
    void (*tk_ChangeWindowAttributes) (Tk_Window tkwin, unsigned long valueMask, XSetWindowAttributes * attsPtr);
    int (*tk_CharBbox) (Tk_TextLayout layout, int index, int * xPtr, int * yPtr, int * widthPtr, int * heightPtr);
    void (*tk_ClearSelection) (Tk_Window tkwin, Atom selection);
    int (*tk_ClipboardAppend) (Tcl_Interp * interp, Tk_Window tkwin, Atom target, Atom format, char* buffer);
    int (*tk_ClipboardClear) (Tcl_Interp * interp, Tk_Window tkwin);
    int (*tk_ConfigureInfo) (Tcl_Interp * interp, Tk_Window tkwin, Tk_ConfigSpec * specs, char * widgRec, const char * argvName, int flags);
    int (*tk_ConfigureValue) (Tcl_Interp * interp, Tk_Window tkwin, Tk_ConfigSpec * specs, char * widgRec, const char * argvName, int flags);
    int (*tk_ConfigureWidget) (Tcl_Interp * interp, Tk_Window tkwin, Tk_ConfigSpec * specs, int argc, char ** argv, char * widgRec, int flags);
    void (*tk_ConfigureWindow) (Tk_Window tkwin, unsigned int valueMask, XWindowChanges * valuePtr);
    Tk_TextLayout (*tk_ComputeTextLayout) (Tk_Font font, const char * str, int numChars, int wrapLength, Tk_Justify justify, int flags, int * widthPtr, int * heightPtr);
    Tk_Window (*tk_CoordsToWindow) (int rootX, int rootY, Tk_Window tkwin);
    unsigned long (*tk_CreateBinding) (Tcl_Interp * interp, Tk_BindingTable bindingTable, ClientData object, const char * eventStr, const char * command, int append);
    Tk_BindingTable (*tk_CreateBindingTable) (Tcl_Interp * interp);
    Tk_ErrorHandler (*tk_CreateErrorHandler) (Display * display, int errNum, int request, int minorCode, Tk_ErrorProc * errorProc, ClientData clientData);
    void (*tk_CreateEventHandler) (Tk_Window token, unsigned long mask, Tk_EventProc * proc, ClientData clientData);
    void (*tk_CreateGenericHandler) (Tk_GenericProc * proc, ClientData clientData);
    void (*tk_CreateImageType) (Tk_ImageType * typePtr);
    void (*tk_CreateItemType) (Tk_ItemType * typePtr);
    void (*tk_CreatePhotoImageFormat) (Tk_PhotoImageFormat * formatPtr);
    void (*tk_CreateSelHandler) (Tk_Window tkwin, Atom selection, Atom target, Tk_SelectionProc * proc, ClientData clientData, Atom format);
    Tk_Window (*tk_CreateWindow) (Tcl_Interp * interp, Tk_Window parent, const char * name, const char * screenName);
    Tk_Window (*tk_CreateWindowFromPath) (Tcl_Interp * interp, Tk_Window tkwin, const char * pathName, const char * screenName);
    int (*tk_DefineBitmap) (Tcl_Interp * interp, const char * name, const char * source, int width, int height);
    void (*tk_DefineCursor) (Tk_Window window, Tk_Cursor cursor);
    void (*tk_DeleteAllBindings) (Tk_BindingTable bindingTable, ClientData object);
    int (*tk_DeleteBinding) (Tcl_Interp * interp, Tk_BindingTable bindingTable, ClientData object, const char * eventStr);
    void (*tk_DeleteBindingTable) (Tk_BindingTable bindingTable);
    void (*tk_DeleteErrorHandler) (Tk_ErrorHandler handler);
    void (*tk_DeleteEventHandler) (Tk_Window token, unsigned long mask, Tk_EventProc * proc, ClientData clientData);
    void (*tk_DeleteGenericHandler) (Tk_GenericProc * proc, ClientData clientData);
    void (*tk_DeleteImage) (Tcl_Interp * interp, const char * name);
    void (*tk_DeleteSelHandler) (Tk_Window tkwin, Atom selection, Atom target);
    void (*tk_DestroyWindow) (Tk_Window tkwin);
    char * (*tk_DisplayName) (Tk_Window tkwin);
    int (*tk_DistanceToTextLayout) (Tk_TextLayout layout, int x, int y);
    void (*tk_Draw3DPolygon) (Tk_Window tkwin, Drawable drawable, Tk_3DBorder border, XPoint * pointPtr, int numPoints, int borderWidth, int leftRelief);
    void (*tk_Draw3DRectangle) (Tk_Window tkwin, Drawable drawable, Tk_3DBorder border, int x, int y, int width, int height, int borderWidth, int relief);
    void (*tk_DrawChars) (Display * display, Drawable drawable, GC gc, Tk_Font tkfont, const char * source, int numBytes, int x, int y);
    void (*tk_DrawFocusHighlight) (Tk_Window tkwin, GC gc, int width, Drawable drawable);
    void (*tk_DrawTextLayout) (Display * display, Drawable drawable, GC gc, Tk_TextLayout layout, int x, int y, int firstChar, int lastChar);
    void (*tk_Fill3DPolygon) (Tk_Window tkwin, Drawable drawable, Tk_3DBorder border, XPoint * pointPtr, int numPoints, int borderWidth, int leftRelief);
    void (*tk_Fill3DRectangle) (Tk_Window tkwin, Drawable drawable, Tk_3DBorder border, int x, int y, int width, int height, int borderWidth, int relief);
    Tk_PhotoHandle (*tk_FindPhoto) (Tcl_Interp * interp, const char * imageName);
    Font (*tk_FontId) (Tk_Font font);
    void (*tk_Free3DBorder) (Tk_3DBorder border);
    void (*tk_FreeBitmap) (Display * display, Pixmap bitmap);
    void (*tk_FreeColor) (XColor * colorPtr);
    void (*tk_FreeColormap) (Display * display, Colormap colormap);
    void (*tk_FreeCursor) (Display * display, Tk_Cursor cursor);
    void (*tk_FreeFont) (Tk_Font f);
    void (*tk_FreeGC) (Display * display, GC gc);
    void (*tk_FreeImage) (Tk_Image image);
    void (*tk_FreeOptions) (Tk_ConfigSpec * specs, char * widgRec, Display * display, int needFlags);
    void (*tk_FreePixmap) (Display * display, Pixmap pixmap);
    void (*tk_FreeTextLayout) (Tk_TextLayout textLayout);
    void (*tk_FreeXId) (Display * display, XID xid);
    GC (*tk_GCForColor) (XColor * colorPtr, Drawable drawable);
    void (*tk_GeometryRequest) (Tk_Window tkwin, int reqWidth, int reqHeight);
    Tk_3DBorder (*tk_Get3DBorder) (Tcl_Interp * interp, Tk_Window tkwin, Tk_Uid colorName);
    void (*tk_GetAllBindings) (Tcl_Interp * interp, Tk_BindingTable bindingTable, ClientData object);
    int (*tk_GetAnchor) (Tcl_Interp * interp, const char * str, Tk_Anchor * anchorPtr);
    char * (*tk_GetAtomName) (Tk_Window tkwin, Atom atom);
    char * (*tk_GetBinding) (Tcl_Interp * interp, Tk_BindingTable bindingTable, ClientData object, const char * eventStr);
    Pixmap (*tk_GetBitmap) (Tcl_Interp * interp, Tk_Window tkwin, const char * str);
    Pixmap (*tk_GetBitmapFromData) (Tcl_Interp * interp, Tk_Window tkwin, const char * source, int width, int height);
    int (*tk_GetCapStyle) (Tcl_Interp * interp, const char * str, int * capPtr);
    XColor * (*tk_GetColor) (Tcl_Interp * interp, Tk_Window tkwin, Tk_Uid name);
    XColor * (*tk_GetColorByValue) (Tk_Window tkwin, XColor * colorPtr);
    Colormap (*tk_GetColormap) (Tcl_Interp * interp, Tk_Window tkwin, const char * str);
    Tk_Cursor (*tk_GetCursor) (Tcl_Interp * interp, Tk_Window tkwin, Tk_Uid str);
    Tk_Cursor (*tk_GetCursorFromData) (Tcl_Interp * interp, Tk_Window tkwin, const char * source, const char * mask, int width, int height, int xHot, int yHot, Tk_Uid fg, Tk_Uid bg);
    Tk_Font (*tk_GetFont) (Tcl_Interp * interp, Tk_Window tkwin, const char * str);
    Tk_Font (*tk_GetFontFromObj) (Tk_Window tkwin, Tcl_Obj * objPtr);
    void (*tk_GetFontMetrics) (Tk_Font font, Tk_FontMetrics * fmPtr);
    GC (*tk_GetGC) (Tk_Window tkwin, unsigned long valueMask, XGCValues * valuePtr);
    Tk_Image (*tk_GetImage) (Tcl_Interp * interp, Tk_Window tkwin, const char * name, Tk_ImageChangedProc * changeProc, ClientData clientData);
    ClientData (*tk_GetImageMasterData) (Tcl_Interp * interp, const char * name, Tk_ImageType ** typePtrPtr);
    Tk_ItemType * (*tk_GetItemTypes) (void);
    int (*tk_GetJoinStyle) (Tcl_Interp * interp, const char * str, int * joinPtr);
    int (*tk_GetJustify) (Tcl_Interp * interp, const char * str, Tk_Justify * justifyPtr);
    int (*tk_GetNumMainWindows) (void);
    Tk_Uid (*tk_GetOption) (Tk_Window tkwin, const char * name, const char * className);
    int (*tk_GetPixels) (Tcl_Interp * interp, Tk_Window tkwin, const char * str, int * intPtr);
    Pixmap (*tk_GetPixmap) (Display * display, Drawable d, int width, int height, int depth);
    int (*tk_GetRelief) (Tcl_Interp * interp, const char * name, int * reliefPtr);
    void (*tk_GetRootCoords) (Tk_Window tkwin, int * xPtr, int * yPtr);
    int (*tk_GetScrollInfo) (Tcl_Interp * interp, int argc, char ** argv, double * dblPtr, int * intPtr);
    int (*tk_GetScreenMM) (Tcl_Interp * interp, Tk_Window tkwin, const char * str, double * doublePtr);
    int (*tk_GetSelection) (Tcl_Interp * interp, Tk_Window tkwin, Atom selection, Atom target, Tk_GetSelProc * proc, ClientData clientData);
    Tk_Uid (*tk_GetUid) (const char * str);
    Visual * (*tk_GetVisual) (Tcl_Interp * interp, Tk_Window tkwin, const char * str, int * depthPtr, Colormap * colormapPtr);
    void (*tk_GetVRootGeometry) (Tk_Window tkwin, int * xPtr, int * yPtr, int * widthPtr, int * heightPtr);
    int (*tk_Grab) (Tcl_Interp * interp, Tk_Window tkwin, int grabGlobal);
    void (*tk_HandleEvent) (XEvent * eventPtr);
    Tk_Window (*tk_IdToWindow) (Display * display, Window window);
    void (*tk_ImageChanged) (Tk_ImageMaster master, int x, int y, int width, int height, int imageWidth, int imageHeight);
    int (*tk_Init) (Tcl_Interp * interp);
    Atom (*tk_InternAtom) (Tk_Window tkwin, const char * name);
    int (*tk_IntersectTextLayout) (Tk_TextLayout layout, int x, int y, int width, int height);
    void (*tk_MaintainGeometry) (Tk_Window slave, Tk_Window master, int x, int y, int width, int height);
    Tk_Window (*tk_MainWindow) (Tcl_Interp * interp);
    void (*tk_MakeWindowExist) (Tk_Window tkwin);
    void (*tk_ManageGeometry) (Tk_Window tkwin, const Tk_GeomMgr * mgrPtr, ClientData clientData);
    void (*tk_MapWindow) (Tk_Window tkwin);
    int (*tk_MeasureChars) (Tk_Font tkfont, const char * source, int numBytes, int maxPixels, int flags, int * lengthPtr);
    void (*tk_MoveResizeWindow) (Tk_Window tkwin, int x, int y, int width, int height);
    void (*tk_MoveWindow) (Tk_Window tkwin, int x, int y);
    void (*tk_MoveToplevelWindow) (Tk_Window tkwin, int x, int y);
    char * (*tk_NameOf3DBorder) (Tk_3DBorder border);
    char * (*tk_NameOfAnchor) (Tk_Anchor anchor);
    char * (*tk_NameOfBitmap) (Display * display, Pixmap bitmap);
    char * (*tk_NameOfCapStyle) (int cap);
    char * (*tk_NameOfColor) (XColor * colorPtr);
    char * (*tk_NameOfCursor) (Display * display, Tk_Cursor cursor);
    char * (*tk_NameOfFont) (Tk_Font font);
    char * (*tk_NameOfImage) (Tk_ImageMaster imageMaster);
    char * (*tk_NameOfJoinStyle) (int join);
    char * (*tk_NameOfJustify) (Tk_Justify justify);
    char * (*tk_NameOfRelief) (int relief);
    Tk_Window (*tk_NameToWindow) (Tcl_Interp * interp, const char * pathName, Tk_Window tkwin);
    void (*tk_OwnSelection) (Tk_Window tkwin, Atom selection, Tk_LostSelProc * proc, ClientData clientData);
    int (*tk_ParseArgv) (Tcl_Interp * interp, Tk_Window tkwin, int * argcPtr, char ** argv, Tk_ArgvInfo * argTable, int flags);
    void (*tk_PhotoPutBlock_NoComposite) (Tk_PhotoHandle handle, Tk_PhotoImageBlock * blockPtr, int x, int y, int width, int height);
    void (*tk_PhotoPutZoomedBlock_NoComposite) (Tk_PhotoHandle handle, Tk_PhotoImageBlock * blockPtr, int x, int y, int width, int height, int zoomX, int zoomY, int subsampleX, int subsampleY);
    int (*tk_PhotoGetImage) (Tk_PhotoHandle handle, Tk_PhotoImageBlock * blockPtr);
    void (*tk_PhotoBlank) (Tk_PhotoHandle handle);
    void (*tk_PhotoExpand_Panic) (Tk_PhotoHandle handle, int width, int height);
    void (*tk_PhotoGetSize) (Tk_PhotoHandle handle, int * widthPtr, int * heightPtr);
    void (*tk_PhotoSetSize_Panic) (Tk_PhotoHandle handle, int width, int height);
    int (*tk_PointToChar) (Tk_TextLayout layout, int x, int y);
    int (*tk_PostscriptFontName) (Tk_Font tkfont, Tcl_DString * dsPtr);
    void (*tk_PreserveColormap) (Display * display, Colormap colormap);
    void (*tk_QueueWindowEvent) (XEvent * eventPtr, Tcl_QueuePosition position);
    void (*tk_RedrawImage) (Tk_Image image, int imageX, int imageY, int width, int height, Drawable drawable, int drawableX, int drawableY);
    void (*tk_ResizeWindow) (Tk_Window tkwin, int width, int height);
    int (*tk_RestackWindow) (Tk_Window tkwin, int aboveBelow, Tk_Window other);
    Tk_RestrictProc * (*tk_RestrictEvents) (Tk_RestrictProc * proc, ClientData arg, ClientData * prevArgPtr);
    int (*tk_SafeInit) (Tcl_Interp * interp);
    const char * (*tk_SetAppName) (Tk_Window tkwin, const char * name);
    void (*tk_SetBackgroundFromBorder) (Tk_Window tkwin, Tk_3DBorder border);
    void (*tk_SetClass) (Tk_Window tkwin, const char * className);
    void (*tk_SetGrid) (Tk_Window tkwin, int reqWidth, int reqHeight, int gridWidth, int gridHeight);
    void (*tk_SetInternalBorder) (Tk_Window tkwin, int width);
    void (*tk_SetWindowBackground) (Tk_Window tkwin, unsigned long pixel);
    void (*tk_SetWindowBackgroundPixmap) (Tk_Window tkwin, Pixmap pixmap);
    void (*tk_SetWindowBorder) (Tk_Window tkwin, unsigned long pixel);
    void (*tk_SetWindowBorderWidth) (Tk_Window tkwin, int width);
    void (*tk_SetWindowBorderPixmap) (Tk_Window tkwin, Pixmap pixmap);
    void (*tk_SetWindowColormap) (Tk_Window tkwin, Colormap colormap);
    int (*tk_SetWindowVisual) (Tk_Window tkwin, Visual * visual, int depth, Colormap colormap);
    void (*tk_SizeOfBitmap) (Display * display, Pixmap bitmap, int * widthPtr, int * heightPtr);
    void (*tk_SizeOfImage) (Tk_Image image, int * widthPtr, int * heightPtr);
    int (*tk_StrictMotif) (Tk_Window tkwin);
    void (*tk_TextLayoutToPostscript) (Tcl_Interp * interp, Tk_TextLayout layout);
    int (*tk_TextWidth) (Tk_Font font, const char * str, int numBytes);
    void (*tk_UndefineCursor) (Tk_Window window);
    void (*tk_UnderlineChars) (Display * display, Drawable drawable, GC gc, Tk_Font tkfont, const char * source, int x, int y, int firstByte, int lastByte);
    void (*tk_UnderlineTextLayout) (Display * display, Drawable drawable, GC gc, Tk_TextLayout layout, int x, int y, int underline);
    void (*tk_Ungrab) (Tk_Window tkwin);
    void (*tk_UnmaintainGeometry) (Tk_Window slave, Tk_Window master);
    void (*tk_UnmapWindow) (Tk_Window tkwin);
    void (*tk_UnsetGrid) (Tk_Window tkwin);
    void (*tk_UpdatePointer) (Tk_Window tkwin, int x, int y, int state);
    Pixmap (*tk_AllocBitmapFromObj) (Tcl_Interp * interp, Tk_Window tkwin, Tcl_Obj * objPtr);
    Tk_3DBorder (*tk_Alloc3DBorderFromObj) (Tcl_Interp * interp, Tk_Window tkwin, Tcl_Obj * objPtr);
    XColor * (*tk_AllocColorFromObj) (Tcl_Interp * interp, Tk_Window tkwin, Tcl_Obj * objPtr);
    Tk_Cursor (*tk_AllocCursorFromObj) (Tcl_Interp * interp, Tk_Window tkwin, Tcl_Obj * objPtr);
    Tk_Font (*tk_AllocFontFromObj) (Tcl_Interp * interp, Tk_Window tkwin, Tcl_Obj * objPtr);
    Tk_OptionTable (*tk_CreateOptionTable) (Tcl_Interp * interp, const Tk_OptionSpec * templatePtr);
    void (*tk_DeleteOptionTable) (Tk_OptionTable optionTable);
    void (*tk_Free3DBorderFromObj) (Tk_Window tkwin, Tcl_Obj * objPtr);
    void (*tk_FreeBitmapFromObj) (Tk_Window tkwin, Tcl_Obj * objPtr);
    void (*tk_FreeColorFromObj) (Tk_Window tkwin, Tcl_Obj * objPtr);
    void (*tk_FreeConfigOptions) (char * recordPtr, Tk_OptionTable optionToken, Tk_Window tkwin);
    void (*tk_FreeSavedOptions) (Tk_SavedOptions * savePtr);
    void (*tk_FreeCursorFromObj) (Tk_Window tkwin, Tcl_Obj * objPtr);
    void (*tk_FreeFontFromObj) (Tk_Window tkwin, Tcl_Obj * objPtr);
    Tk_3DBorder (*tk_Get3DBorderFromObj) (Tk_Window tkwin, Tcl_Obj * objPtr);
    int (*tk_GetAnchorFromObj) (Tcl_Interp * interp, Tcl_Obj * objPtr, Tk_Anchor * anchorPtr);
    Pixmap (*tk_GetBitmapFromObj) (Tk_Window tkwin, Tcl_Obj * objPtr);
    XColor * (*tk_GetColorFromObj) (Tk_Window tkwin, Tcl_Obj * objPtr);
    Tk_Cursor (*tk_GetCursorFromObj) (Tk_Window tkwin, Tcl_Obj * objPtr);
    Tcl_Obj * (*tk_GetOptionInfo) (Tcl_Interp * interp, char * recordPtr, Tk_OptionTable optionTable, Tcl_Obj * namePtr, Tk_Window tkwin);
    Tcl_Obj * (*tk_GetOptionValue) (Tcl_Interp * interp, char * recordPtr, Tk_OptionTable optionTable, Tcl_Obj * namePtr, Tk_Window tkwin);
    int (*tk_GetJustifyFromObj) (Tcl_Interp * interp, Tcl_Obj * objPtr, Tk_Justify * justifyPtr);
    int (*tk_GetMMFromObj) (Tcl_Interp * interp, Tk_Window tkwin, Tcl_Obj * objPtr, double * doublePtr);
    int (*tk_GetPixelsFromObj) (Tcl_Interp * interp, Tk_Window tkwin, Tcl_Obj * objPtr, int * intPtr);
    int (*tk_GetReliefFromObj) (Tcl_Interp * interp, Tcl_Obj * objPtr, int * resultPtr);
    int (*tk_GetScrollInfoObj) (Tcl_Interp * interp, int objc, Tcl_Obj *const objv[], double * dblPtr, int * intPtr);
    int (*tk_InitOptions) (Tcl_Interp * interp, char * recordPtr, Tk_OptionTable optionToken, Tk_Window tkwin);
    void (*tk_MainEx) (int argc, char ** argv, Tcl_AppInitProc * appInitProc, Tcl_Interp * interp);
    void (*tk_RestoreSavedOptions) (Tk_SavedOptions * savePtr);
    int (*tk_SetOptions) (Tcl_Interp * interp, char * recordPtr, Tk_OptionTable optionTable, int objc, Tcl_Obj *const objv[], Tk_Window tkwin, Tk_SavedOptions * savePtr, int * maskPtr);
    void (*tk_InitConsoleChannels) (Tcl_Interp * interp);
    int (*tk_CreateConsoleWindow) (Tcl_Interp * interp);
    void (*tk_CreateSmoothMethod) (Tcl_Interp * interp, Tk_SmoothMethod * method);
    void *reserved218;
    void *reserved219;
    int (*tk_GetDash) (Tcl_Interp * interp, const char * value, Tk_Dash * dash);
    void (*tk_CreateOutline) (Tk_Outline * outline);
    void (*tk_DeleteOutline) (Display * display, Tk_Outline * outline);
    int (*tk_ConfigOutlineGC) (XGCValues * gcValues, Tk_Canvas canvas, Tk_Item * item, Tk_Outline * outline);
    int (*tk_ChangeOutlineGC) (Tk_Canvas canvas, Tk_Item * item, Tk_Outline * outline);
    int (*tk_ResetOutlineGC) (Tk_Canvas canvas, Tk_Item * item, Tk_Outline * outline);
    int (*tk_CanvasPsOutline) (Tk_Canvas canvas, Tk_Item * item, Tk_Outline * outline);
    void (*tk_SetTSOrigin) (Tk_Window tkwin, GC gc, int x, int y);
    int (*tk_CanvasGetCoordFromObj) (Tcl_Interp * interp, Tk_Canvas canvas, Tcl_Obj * obj, double * doublePtr);
    void (*tk_CanvasSetOffset) (Tk_Canvas canvas, GC gc, Tk_TSOffset * offset);
    void (*tk_DitherPhoto) (Tk_PhotoHandle handle, int x, int y, int width, int height);
    int (*tk_PostscriptBitmap) (Tcl_Interp * interp, Tk_Window tkwin, Tk_PostscriptInfo psInfo, Pixmap bitmap, int startX, int startY, int width, int height);
    int (*tk_PostscriptColor) (Tcl_Interp * interp, Tk_PostscriptInfo psInfo, XColor * colorPtr);
    int (*tk_PostscriptFont) (Tcl_Interp * interp, Tk_PostscriptInfo psInfo, Tk_Font font);
    int (*tk_PostscriptImage) (Tk_Image image, Tcl_Interp * interp, Tk_Window tkwin, Tk_PostscriptInfo psinfo, int x, int y, int width, int height, int prepass);
    void (*tk_PostscriptPath) (Tcl_Interp * interp, Tk_PostscriptInfo psInfo, double * coordPtr, int numPoints);
    int (*tk_PostscriptStipple) (Tcl_Interp * interp, Tk_Window tkwin, Tk_PostscriptInfo psInfo, Pixmap bitmap);
    double (*tk_PostscriptY) (double y, Tk_PostscriptInfo psInfo);
    int (*tk_PostscriptPhoto) (Tcl_Interp * interp, Tk_PhotoImageBlock * blockPtr, Tk_PostscriptInfo psInfo, int width, int height);
    void (*tk_CreateClientMessageHandler) (Tk_ClientMessageProc * proc);
    void (*tk_DeleteClientMessageHandler) (Tk_ClientMessageProc * proc);
    Tk_Window (*tk_CreateAnonymousWindow) (Tcl_Interp * interp, Tk_Window parent, const char * screenName);
    void (*tk_SetClassProcs) (Tk_Window tkwin, Tk_ClassProcs * procs, ClientData instanceData);
    void (*tk_SetInternalBorderEx) (Tk_Window tkwin, int left, int right, int top, int bottom);
    void (*tk_SetMinimumRequestSize) (Tk_Window tkwin, int minWidth, int minHeight);
    void (*tk_SetCaretPos) (Tk_Window tkwin, int x, int y, int height);
    void (*tk_PhotoPutBlock_Panic) (Tk_PhotoHandle handle, Tk_PhotoImageBlock * blockPtr, int x, int y, int width, int height, int compRule);
    void (*tk_PhotoPutZoomedBlock_Panic) (Tk_PhotoHandle handle, Tk_PhotoImageBlock * blockPtr, int x, int y, int width, int height, int zoomX, int zoomY, int subsampleX, int subsampleY, int compRule);
    int (*tk_CollapseMotionEvents) (Display * display, int collapse);
    Tk_StyleEngine (*tk_RegisterStyleEngine) (const char * name, Tk_StyleEngine parent);
    Tk_StyleEngine (*tk_GetStyleEngine) (const char * name);
    int (*tk_RegisterStyledElement) (Tk_StyleEngine engine, Tk_ElementSpec * templatePtr);
    int (*tk_GetElementId) (const char * name);
    Tk_Style (*tk_CreateStyle) (const char * name, Tk_StyleEngine engine, ClientData clientData);
    Tk_Style (*tk_GetStyle) (Tcl_Interp * interp, const char * name);
    void (*tk_FreeStyle) (Tk_Style style);
    const char * (*tk_NameOfStyle) (Tk_Style style);
    Tk_Style (*tk_AllocStyleFromObj) (Tcl_Interp * interp, Tcl_Obj * objPtr);
    Tk_Style (*tk_GetStyleFromObj) (Tcl_Obj * objPtr);
    void (*tk_FreeStyleFromObj) (Tcl_Obj * objPtr);
    Tk_StyledElement (*tk_GetStyledElement) (Tk_Style style, int elementId, Tk_OptionTable optionTable);
    void (*tk_GetElementSize) (Tk_Style style, Tk_StyledElement element, char * recordPtr, Tk_Window tkwin, int width, int height, int inner, int * widthPtr, int * heightPtr);
    void (*tk_GetElementBox) (Tk_Style style, Tk_StyledElement element, char * recordPtr, Tk_Window tkwin, int x, int y, int width, int height, int inner, int * xPtr, int * yPtr, int * widthPtr, int * heightPtr);
    int (*tk_GetElementBorderWidth) (Tk_Style style, Tk_StyledElement element, char * recordPtr, Tk_Window tkwin);
    void (*tk_DrawElement) (Tk_Style style, Tk_StyledElement element, char * recordPtr, Tk_Window tkwin, Drawable d, int x, int y, int width, int height, int state);
    int (*tk_PhotoExpand) (Tcl_Interp * interp, Tk_PhotoHandle handle, int width, int height);
    int (*tk_PhotoPutBlock) (Tcl_Interp * interp, Tk_PhotoHandle handle, Tk_PhotoImageBlock * blockPtr, int x, int y, int width, int height, int compRule);
    int (*tk_PhotoPutZoomedBlock) (Tcl_Interp * interp, Tk_PhotoHandle handle, Tk_PhotoImageBlock * blockPtr, int x, int y, int width, int height, int zoomX, int zoomY, int subsampleX, int subsampleY, int compRule);
    int (*tk_PhotoSetSize) (Tcl_Interp * interp, Tk_PhotoHandle handle, int width, int height);
    long (*tk_GetUserInactiveTime) (Display * dpy);
    void (*tk_ResetUserInactiveTime) (Display * dpy);
    Tcl_Interp * (*tk_Interp) (Tk_Window tkwin);
    void (*tk_CreateOldImageType) (Tk_ImageType * typePtr);
    void (*tk_CreateOldPhotoImageFormat) (Tk_PhotoImageFormat * formatPtr);
} TkStubs;




extern TkStubs *tkStubsPtr;
# 1535 "/tmp/t852/include/tk.h" 2
# 42 "bltInt.h" 2





# 1 "bltTkInt.h" 1
# 30 "bltTkInt.h"
typedef struct {
    Tk_Uid family;
    int pointsize;

    int weight;
    int slant;
    int underline;
    int overstrike;
} TkFontAttributes;

typedef struct {
    int ascent;
    int descent;
    int maxWidth;
    int fixed;

} TkFontMetrics;


typedef struct TkFontStruct {




    int resourceRefCount;
# 64 "bltTkInt.h"
    int objRefCount;




    Tcl_HashEntry *cacheHashPtr;

    Tcl_HashEntry *namedHashPtr;




    Screen *screen;

    int tabWidth;
    int underlinePos;


    int underlineHeight;







    Font fid;


    TkFontAttributes fa;





    TkFontMetrics fm;


    struct TkFontStruct *nextPtr;





} TkFont;





typedef struct TkRegionStruct *TkRegion;

typedef struct {
    int type;
    union {
        Pixmap pixmap;
        TkRegion region;
    } value;
} TkpClipMask;
# 196 "bltTkInt.h"
typedef struct TkBorderStruct {
    Screen *screen;
    Visual *visual;

    int depth;

    Colormap colormap;

    int refCount;


    int objRefCount;


    XColor *bgColor;

    XColor *darkColor;


    XColor *lightColor;



    Pixmap shadow;



    GC bgGC;

    GC darkGC;


    GC lightGC;


    Tcl_HashEntry *hashPtr;

    struct TkBorderStruct *nextPtr;




} TkBorder;
# 48 "bltInt.h" 2


# 1 "/usr/include/assert.h" 1 3
# 65 "/usr/include/assert.h" 3



extern void __assert_fail (__const char *__assertion, __const char *__file,
                           unsigned int __line, __const char *__function)
     __attribute__ ((__noreturn__));


extern void __assert_perror_fail (int __errnum, __const char *__file,
                                  unsigned int __line,
                                  __const char *__function)
     __attribute__ ((__noreturn__));




extern void __assert (const char *__assertion, const char *__file, int __line)
     __attribute__ ((__noreturn__));



# 51 "bltInt.h" 2




# 1 "bltConfig.h" 1
# 56 "bltInt.h" 2
# 79 "bltInt.h"
# 1 "blt.h" 1
# 53 "blt.h"
# 1 "bltVector.h" 1
# 29 "bltVector.h"
typedef enum {
    BLT_VECTOR_NOTIFY_UPDATE = 1,
    BLT_VECTOR_NOTIFY_DESTROY


} Blt_VectorNotify;

typedef struct Blt_VectorIdStruct *Blt_VectorId;

typedef void (Blt_VectorChangedProc) (Tcl_Interp *interp, ClientData clientData, Blt_VectorNotify notify);


typedef struct {
    double *valueArr;
    int numValues;
    int arraySize;
    double min, max;
    int dirty;
    int reserved;

} Blt_Vector;

typedef double (Blt_VectorIndexProc) (Blt_Vector * vecPtr);

typedef enum {
    BLT_MATH_FUNC_SCALAR = 1,

    BLT_MATH_FUNC_VECTOR
} Blt_MathFuncType;
# 81 "bltVector.h"
extern double Blt_VecMin (Blt_Vector *vPtr);
extern double Blt_VecMax (Blt_Vector *vPtr);

extern Blt_VectorId Blt_AllocVectorId (Tcl_Interp *interp, char *vecName);


extern void Blt_SetVectorChangedProc (Blt_VectorId clientId, Blt_VectorChangedProc * proc, ClientData clientData);


extern void Blt_FreeVectorId (Blt_VectorId clientId);

extern int Blt_GetVectorById (Tcl_Interp *interp, Blt_VectorId clientId, Blt_Vector **vecPtrPtr);


extern char *Blt_NameOfVectorId (Blt_VectorId clientId);

extern char *Blt_NameOfVector (Blt_Vector *vecPtr);

extern int Blt_VectorNotifyPending (Blt_VectorId clientId);

extern int Blt_CreateVector (Tcl_Interp *interp, char *vecName, int size, Blt_Vector ** vecPtrPtr);


extern int Blt_GetVector (Tcl_Interp *interp, char *vecName, Blt_Vector **vecPtrPtr);


extern int Blt_VectorExists (Tcl_Interp *interp, char *vecName);

extern int Blt_ResetVector (Blt_Vector *vecPtr, double *dataArr, int nValues, int arraySize, Tcl_FreeProc *freeProc);


extern int Blt_ResizeVector (Blt_Vector *vecPtr, int nValues);

extern int Blt_DeleteVectorByName (Tcl_Interp *interp, char *vecName);


extern int Blt_DeleteVector (Blt_Vector *vecPtr);

extern int Blt_ExprVector (Tcl_Interp *interp, char *expression, Blt_Vector *vecPtr);


extern void Blt_InstallIndexProc (Tcl_Interp *interp, char *indexName, Blt_VectorIndexProc * procPtr);
# 54 "blt.h" 2
# 1 "bltHash.h" 1
# 61 "bltHash.h"
# 1 "/usr/include/inttypes.h" 1 3
# 28 "/usr/include/inttypes.h" 3
# 1 "/usr/include/stdint.h" 1 3
# 28 "/usr/include/stdint.h" 3
# 1 "/usr/include/bits/wordsize.h" 1 3
# 29 "/usr/include/stdint.h" 2 3
# 49 "/usr/include/stdint.h" 3
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;

typedef unsigned int uint32_t;





__extension__
typedef unsigned long long int uint64_t;






typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef int int_least32_t;



__extension__
typedef long long int int_least64_t;



typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;



__extension__
typedef unsigned long long int uint_least64_t;






typedef signed char int_fast8_t;





typedef int int_fast16_t;
typedef int int_fast32_t;
__extension__
typedef long long int int_fast64_t;



typedef unsigned char uint_fast8_t;





typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
__extension__
typedef unsigned long long int uint_fast64_t;
# 126 "/usr/include/stdint.h" 3
typedef int intptr_t;


typedef unsigned int uintptr_t;
# 138 "/usr/include/stdint.h" 3
__extension__
typedef long long int intmax_t;
__extension__
typedef unsigned long long int uintmax_t;
# 29 "/usr/include/inttypes.h" 2 3






typedef long int __gwchar_t;
# 274 "/usr/include/inttypes.h" 3

# 288 "/usr/include/inttypes.h" 3
typedef struct
  {
    long long int quot;
    long long int rem;
  } imaxdiv_t;





extern intmax_t imaxabs (intmax_t __n) __attribute__ ((__const__));


extern imaxdiv_t imaxdiv (intmax_t __numer, intmax_t __denom)
      __attribute__ ((__const__));


extern intmax_t strtoimax (__const char *__restrict __nptr,
                           char **__restrict __endptr, int __base) ;


extern uintmax_t strtoumax (__const char *__restrict __nptr,
                            char ** __restrict __endptr, int __base) ;


extern intmax_t wcstoimax (__const __gwchar_t *__restrict __nptr,
                           __gwchar_t **__restrict __endptr, int __base)
     ;


extern uintmax_t wcstoumax (__const __gwchar_t *__restrict __nptr,
                            __gwchar_t ** __restrict __endptr, int __base)
     ;
# 390 "/usr/include/inttypes.h" 3
__extension__
extern long long int __strtoll_internal (__const char *__restrict __nptr,
                                         char **__restrict __endptr,
                                         int __base, int __group) ;


extern __inline intmax_t
strtoimax (__const char *__restrict nptr, char **__restrict endptr,
           int base)
{
  return __strtoll_internal (nptr, endptr, base, 0);
}



__extension__
extern unsigned long long int __strtoull_internal (__const char *
                                                   __restrict __nptr,
                                                   char **
                                                   __restrict __endptr,
                                                   int __base,
                                                   int __group) ;


extern __inline uintmax_t
strtoumax (__const char *__restrict nptr, char **__restrict endptr,
           int base)
{
  return __strtoull_internal (nptr, endptr, base, 0);
}



__extension__
extern long long int __wcstoll_internal (__const __gwchar_t *
                                         __restrict __nptr,
                                         __gwchar_t **__restrict __endptr,
                                         int __base, int __group) ;


extern __inline intmax_t
wcstoimax (__const __gwchar_t *__restrict nptr, __gwchar_t **__restrict endptr,
           int base)
{
  return __wcstoll_internal (nptr, endptr, base, 0);
}




__extension__
extern unsigned long long int __wcstoull_internal (__const __gwchar_t *
                                                   __restrict __nptr,
                                                   __gwchar_t **
                                                   __restrict __endptr,
                                                   int __base,
                                                   int __group) ;


extern __inline uintmax_t
wcstoumax (__const __gwchar_t *__restrict nptr, __gwchar_t **__restrict endptr,
           int base)
{
  return __wcstoull_internal (nptr, endptr, base, 0);
}





# 62 "bltHash.h" 2
# 82 "bltHash.h"
typedef uint32_t Blt_Hash;


# 1 "bltPool.h" 1



typedef struct Blt_PoolChainStruct {
   struct Blt_PoolChainStruct *nextPtr;
} Blt_PoolChain;





typedef struct Blt_PoolStruct *Blt_Pool;

typedef void *(Blt_PoolAllocProc) (Blt_Pool pool, size_t size);
typedef void (Blt_PoolFreeProc) (Blt_Pool pool, void *item);

struct Blt_PoolStruct {
    Blt_PoolChain *headPtr;
    Blt_PoolChain *freePtr;

    size_t poolSize;
    size_t itemSize;
    size_t bytesLeft;
    size_t waste;

    Blt_PoolAllocProc *allocProc;
    Blt_PoolFreeProc *freeProc;
};

extern Blt_Pool Blt_PoolCreate (int type);
extern void Blt_PoolDestroy (Blt_Pool pool);
# 86 "bltHash.h" 2
# 103 "bltHash.h"
typedef union {
    void *oneWordValue;
    unsigned long words[1];



    char string[4];


} Blt_HashKey;






typedef struct Blt_HashEntry {
    struct Blt_HashEntry *nextPtr;


    Blt_Hash hval;

    ClientData clientData;

    Blt_HashKey key;
} Blt_HashEntry;







typedef struct Blt_HashTable {
    Blt_HashEntry **buckets;


    Blt_HashEntry *staticBuckets[4];


    size_t numBuckets;

    size_t numEntries;

    size_t rebuildSize;

    Blt_Hash mask;

    unsigned int downShift;


    size_t keyType;





    Blt_HashEntry *(*findProc) (struct Blt_HashTable *tablePtr, const void *key);

    Blt_HashEntry *(*createProc) (struct Blt_HashTable *tablePtr, const void *key, int *newPtr);


    Blt_Pool hPool;





} Blt_HashTable;






typedef struct {
    Blt_HashTable *tablePtr;
    unsigned long nextIndex;

    Blt_HashEntry *nextEntryPtr;

} Blt_HashSearch;
# 205 "bltHash.h"
extern void Blt_InitHashTable (Blt_HashTable *tablePtr, size_t keyType);


extern void Blt_InitHashTableWithPool (Blt_HashTable *tablePtr, size_t keyType);


extern void Blt_DeleteHashTable (Blt_HashTable *tablePtr);

extern void Blt_DeleteHashEntry (Blt_HashTable *tablePtr, Blt_HashEntry *entryPtr);


extern Blt_HashEntry *Blt_FirstHashEntry (Blt_HashTable *tablePtr, Blt_HashSearch *searchPtr);


extern Blt_HashEntry *Blt_NextHashEntry (Blt_HashSearch *srchPtr);

extern char *Blt_HashStats (Blt_HashTable *tablePtr);
# 55 "blt.h" 2

typedef char *Blt_Uid;

extern Blt_Uid Blt_GetUid (char *string);
extern void Blt_FreeUid (Blt_Uid uid);
extern Blt_Uid Blt_FindUid (char *string);


extern int Blt_GetArrayFromObj (Tcl_Interp *interp, Tcl_Obj *objPtr, Blt_HashTable **tablePtrPtr);

extern Tcl_Obj *Blt_NewArrayObj (int objc, Tcl_Obj *objv[]);
extern void Blt_RegisterArrayObj (Tcl_Interp *interp);
extern int Blt_IsArrayObj (Tcl_Obj *obj);
# 80 "bltInt.h" 2
# 1 "bltNsUtil.h" 1
# 50 "bltNsUtil.h"
extern Tcl_Command Tcl_FindCommand (Tcl_Interp *interp, const char *name, Tcl_Namespace *nsPtr, int flags);
# 62 "bltNsUtil.h"
extern Tcl_Namespace *Tcl_GetCurrentNamespace (Tcl_Interp *interp);

extern Tcl_Namespace *Tcl_GetGlobalNamespace (Tcl_Interp *interp);


extern Tcl_Namespace *Tcl_CreateNamespace (Tcl_Interp *interp, const char *name, ClientData clientData, Tcl_NamespaceDeleteProc *nsDelProc);


extern void Tcl_DeleteNamespace (Tcl_Namespace *nsPtr);

extern Tcl_Namespace *Tcl_FindNamespace (Tcl_Interp *interp, const char *name, Tcl_Namespace *context, int flags);


extern int Tcl_Export (Tcl_Interp *interp, Tcl_Namespace *nsPtr, const char *name, int resetFlag);


extern Tcl_Var Tcl_FindNamespaceVar (Tcl_Interp *interp, char *name, Tcl_Namespace *contextNsPtr, int flags);


extern void Tcl_PopCallFrame (Tcl_Interp *interp);

extern int Tcl_PushCallFrame (Tcl_Interp *interp, Tcl_CallFrame * framePtr, Tcl_Namespace *nsPtr, int isProcCallFrame);


extern Tcl_HashTable *Blt_GetArrayVariableTable ( Tcl_Interp *interp, const char *varName, int flags);
# 95 "bltNsUtil.h"
extern Tcl_Namespace *Blt_GetVariableNamespace (Tcl_Interp *interp, const char *varName);


extern Tcl_Namespace *Blt_GetCommandNamespace (Tcl_Interp *interp, Tcl_Command cmdToken);


extern Tcl_CallFrame *Blt_EnterNamespace (Tcl_Interp *interp, Tcl_Namespace *nsPtr);


extern void Blt_LeaveNamespace (Tcl_Interp *interp, Tcl_CallFrame * framePtr);


extern int Blt_ParseQualifiedName (Tcl_Interp *interp, const char *name, Tcl_Namespace **nsPtrPtr, const char **namePtr);


extern char *Blt_GetQualifiedName (Tcl_Namespace *nsPtr, const char *name, Tcl_DString *resultPtr);


extern Tcl_Command Blt_CreateCommand (Tcl_Interp *interp, const char *cmdName, Tcl_CmdProc *proc, ClientData clientData, Tcl_CmdDeleteProc *deleteProc);
# 81 "bltInt.h" 2


# 1 "/usr/include/stdlib.h" 1 3
# 33 "/usr/include/stdlib.h" 3
# 1 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stddef.h" 1 3
# 34 "/usr/include/stdlib.h" 2 3


# 93 "/usr/include/stdlib.h" 3


typedef struct
  {
    int quot;
    int rem;
  } div_t;



typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;



# 137 "/usr/include/stdlib.h" 3
extern size_t __ctype_get_mb_cur_max (void) ;




extern double atof (__const char *__nptr) __attribute__ ((__pure__));

extern int atoi (__const char *__nptr) __attribute__ ((__pure__));

extern long int atol (__const char *__nptr) __attribute__ ((__pure__));





__extension__ extern long long int atoll (__const char *__nptr)
     __attribute__ ((__pure__));





extern double strtod (__const char *__restrict __nptr,
                      char **__restrict __endptr) ;

# 174 "/usr/include/stdlib.h" 3


extern long int strtol (__const char *__restrict __nptr,
                        char **__restrict __endptr, int __base) ;

extern unsigned long int strtoul (__const char *__restrict __nptr,
                                  char **__restrict __endptr, int __base)
     ;




__extension__
extern long long int strtoq (__const char *__restrict __nptr,
                             char **__restrict __endptr, int __base) ;

__extension__
extern unsigned long long int strtouq (__const char *__restrict __nptr,
                                       char **__restrict __endptr, int __base)
     ;





__extension__
extern long long int strtoll (__const char *__restrict __nptr,
                              char **__restrict __endptr, int __base) ;

__extension__
extern unsigned long long int strtoull (__const char *__restrict __nptr,
                                        char **__restrict __endptr, int __base)
     ;

# 264 "/usr/include/stdlib.h" 3
extern double __strtod_internal (__const char *__restrict __nptr,
                                 char **__restrict __endptr, int __group)
     ;
extern float __strtof_internal (__const char *__restrict __nptr,
                                char **__restrict __endptr, int __group)
     ;
extern long double __strtold_internal (__const char *__restrict __nptr,
                                       char **__restrict __endptr,
                                       int __group) ;

extern long int __strtol_internal (__const char *__restrict __nptr,
                                   char **__restrict __endptr,
                                   int __base, int __group) ;



extern unsigned long int __strtoul_internal (__const char *__restrict __nptr,
                                             char **__restrict __endptr,
                                             int __base, int __group) ;
# 307 "/usr/include/stdlib.h" 3

extern __inline double
strtod (__const char *__restrict __nptr, char **__restrict __endptr)
{
  return __strtod_internal (__nptr, __endptr, 0);
}
extern __inline long int
strtol (__const char *__restrict __nptr, char **__restrict __endptr,
        int __base)
{
  return __strtol_internal (__nptr, __endptr, __base, 0);
}
extern __inline unsigned long int
strtoul (__const char *__restrict __nptr, char **__restrict __endptr,
         int __base)
{
  return __strtoul_internal (__nptr, __endptr, __base, 0);
}

# 343 "/usr/include/stdlib.h" 3
__extension__ extern __inline long long int
strtoq (__const char *__restrict __nptr, char **__restrict __endptr,
        int __base)
{
  return __strtoll_internal (__nptr, __endptr, __base, 0);
}
__extension__ extern __inline unsigned long long int
strtouq (__const char *__restrict __nptr, char **__restrict __endptr,
         int __base)
{
  return __strtoull_internal (__nptr, __endptr, __base, 0);
}




__extension__ extern __inline long long int
strtoll (__const char *__restrict __nptr, char **__restrict __endptr,
         int __base)
{
  return __strtoll_internal (__nptr, __endptr, __base, 0);
}
__extension__ extern __inline unsigned long long int
strtoull (__const char * __restrict __nptr, char **__restrict __endptr,
          int __base)
{
  return __strtoull_internal (__nptr, __endptr, __base, 0);
}




extern __inline double
atof (__const char *__nptr)
{
  return strtod (__nptr, (char **) ((void *)0));
}
extern __inline int
atoi (__const char *__nptr)
{
  return (int) strtol (__nptr, (char **) ((void *)0), 10);
}
extern __inline long int
atol (__const char *__nptr)
{
  return strtol (__nptr, (char **) ((void *)0), 10);
}




__extension__ extern __inline long long int
atoll (__const char *__nptr)
{
  return strtoll (__nptr, (char **) ((void *)0), 10);
}

# 408 "/usr/include/stdlib.h" 3
extern char *l64a (long int __n) ;


extern long int a64l (__const char *__s) __attribute__ ((__pure__));
# 423 "/usr/include/stdlib.h" 3
extern long int random (void) ;


extern void srandom (unsigned int __seed) ;





extern char *initstate (unsigned int __seed, char *__statebuf,
                        size_t __statelen) ;



extern char *setstate (char *__statebuf) ;







struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };

extern int random_r (struct random_data *__restrict __buf,
                     int32_t *__restrict __result) ;

extern int srandom_r (unsigned int __seed, struct random_data *__buf) ;

extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
                        size_t __statelen,
                        struct random_data *__restrict __buf) ;

extern int setstate_r (char *__restrict __statebuf,
                       struct random_data *__restrict __buf) ;






extern int rand (void) ;

extern void srand (unsigned int __seed) ;




extern int rand_r (unsigned int *__seed) ;







extern double drand48 (void) ;
extern double erand48 (unsigned short int __xsubi[3]) ;


extern long int lrand48 (void) ;
extern long int nrand48 (unsigned short int __xsubi[3]) ;


extern long int mrand48 (void) ;
extern long int jrand48 (unsigned short int __xsubi[3]) ;


extern void srand48 (long int __seedval) ;
extern unsigned short int *seed48 (unsigned short int __seed16v[3]) ;
extern void lcong48 (unsigned short int __param[7]) ;





struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    unsigned long long int __a;
  };


extern int drand48_r (struct drand48_data *__restrict __buffer,
                      double *__restrict __result) ;
extern int erand48_r (unsigned short int __xsubi[3],
                      struct drand48_data *__restrict __buffer,
                      double *__restrict __result) ;


extern int lrand48_r (struct drand48_data *__restrict __buffer,
                      long int *__restrict __result) ;
extern int nrand48_r (unsigned short int __xsubi[3],
                      struct drand48_data *__restrict __buffer,
                      long int *__restrict __result) ;


extern int mrand48_r (struct drand48_data *__restrict __buffer,
                      long int *__restrict __result) ;
extern int jrand48_r (unsigned short int __xsubi[3],
                      struct drand48_data *__restrict __buffer,
                      long int *__restrict __result) ;


extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     ;

extern int seed48_r (unsigned short int __seed16v[3],
                     struct drand48_data *__buffer) ;

extern int lcong48_r (unsigned short int __param[7],
                      struct drand48_data *__buffer) ;









extern void *malloc (size_t __size) __attribute__ ((__malloc__));

extern void *calloc (size_t __nmemb, size_t __size)
     __attribute__ ((__malloc__));







extern void *realloc (void *__ptr, size_t __size) __attribute__ ((__malloc__));

extern void free (void *__ptr) ;




extern void cfree (void *__ptr) ;



# 1 "/usr/include/alloca.h" 1 3
# 25 "/usr/include/alloca.h" 3
# 1 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stddef.h" 1 3
# 26 "/usr/include/alloca.h" 2 3







extern void *alloca (size_t __size) ;






# 579 "/usr/include/stdlib.h" 2 3




extern void *valloc (size_t __size) __attribute__ ((__malloc__));
# 592 "/usr/include/stdlib.h" 3


extern void abort (void) __attribute__ ((__noreturn__));



extern int atexit (void (*__func) (void)) ;





extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     ;






extern void exit (int __status) __attribute__ ((__noreturn__));

# 624 "/usr/include/stdlib.h" 3


extern char *getenv (__const char *__name) ;




extern char *__secure_getenv (__const char *__name) ;





extern int putenv (char *__string) ;





extern int setenv (__const char *__name, __const char *__value, int __replace)
     ;


extern int unsetenv (__const char *__name) ;






extern int clearenv (void) ;
# 663 "/usr/include/stdlib.h" 3
extern char *mktemp (char *__template) ;
# 674 "/usr/include/stdlib.h" 3
extern int mkstemp (char *__template);
# 693 "/usr/include/stdlib.h" 3
extern char *mkdtemp (char *__template) ;








extern int system (__const char *__command);

# 720 "/usr/include/stdlib.h" 3
extern char *realpath (__const char *__restrict __name,
                       char *__restrict __resolved) ;






typedef int (*__compar_fn_t) (__const void *, __const void *);









extern void *bsearch (__const void *__key, __const void *__base,
                      size_t __nmemb, size_t __size, __compar_fn_t __compar);



extern void qsort (void *__base, size_t __nmemb, size_t __size,
                   __compar_fn_t __compar);



extern int abs (int __x) __attribute__ ((__const__));
extern long int labs (long int __x) __attribute__ ((__const__));












extern div_t div (int __numer, int __denom)
     __attribute__ ((__const__));
extern ldiv_t ldiv (long int __numer, long int __denom)
     __attribute__ ((__const__));

# 784 "/usr/include/stdlib.h" 3
extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
                   int *__restrict __sign) ;




extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
                   int *__restrict __sign) ;




extern char *gcvt (double __value, int __ndigit, char *__buf) ;




extern char *qecvt (long double __value, int __ndigit,
                    int *__restrict __decpt, int *__restrict __sign) ;
extern char *qfcvt (long double __value, int __ndigit,
                    int *__restrict __decpt, int *__restrict __sign) ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf) ;




extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
                   int *__restrict __sign, char *__restrict __buf,
                   size_t __len) ;
extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
                   int *__restrict __sign, char *__restrict __buf,
                   size_t __len) ;

extern int qecvt_r (long double __value, int __ndigit,
                    int *__restrict __decpt, int *__restrict __sign,
                    char *__restrict __buf, size_t __len) ;
extern int qfcvt_r (long double __value, int __ndigit,
                    int *__restrict __decpt, int *__restrict __sign,
                    char *__restrict __buf, size_t __len) ;







extern int mblen (__const char *__s, size_t __n) ;


extern int mbtowc (wchar_t *__restrict __pwc,
                   __const char *__restrict __s, size_t __n) ;


extern int wctomb (char *__s, wchar_t __wchar) ;



extern size_t mbstowcs (wchar_t *__restrict __pwcs,
                        __const char *__restrict __s, size_t __n) ;

extern size_t wcstombs (char *__restrict __s,
                        __const wchar_t *__restrict __pwcs, size_t __n)
     ;








extern int rpmatch (__const char *__response) ;
# 916 "/usr/include/stdlib.h" 3
extern int getloadavg (double __loadavg[], int __nelem) ;






# 84 "bltInt.h" 2



# 1 "/usr/include/string.h" 1 3
# 28 "/usr/include/string.h" 3





# 1 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stddef.h" 1 3
# 34 "/usr/include/string.h" 2 3




extern void *memcpy (void *__restrict __dest,
                     __const void *__restrict __src, size_t __n) ;


extern void *memmove (void *__dest, __const void *__src, size_t __n)
     ;






extern void *memccpy (void *__restrict __dest, __const void *__restrict __src,
                      int __c, size_t __n)
     ;





extern void *memset (void *__s, int __c, size_t __n) ;


extern int memcmp (__const void *__s1, __const void *__s2, size_t __n)
     __attribute__ ((__pure__));


extern void *memchr (__const void *__s, int __c, size_t __n)
      __attribute__ ((__pure__));

# 80 "/usr/include/string.h" 3


extern char *strcpy (char *__restrict __dest, __const char *__restrict __src)
     ;

extern char *strncpy (char *__restrict __dest,
                      __const char *__restrict __src, size_t __n) ;


extern char *strcat (char *__restrict __dest, __const char *__restrict __src)
     ;

extern char *strncat (char *__restrict __dest, __const char *__restrict __src,
                      size_t __n) ;


extern int strcmp (__const char *__s1, __const char *__s2)
     __attribute__ ((__pure__));

extern int strncmp (__const char *__s1, __const char *__s2, size_t __n)
     __attribute__ ((__pure__));


extern int strcoll (__const char *__s1, __const char *__s2)
     __attribute__ ((__pure__));

extern size_t strxfrm (char *__restrict __dest,
                       __const char *__restrict __src, size_t __n) ;

# 126 "/usr/include/string.h" 3
extern char *strdup (__const char *__s) __attribute__ ((__malloc__));
# 160 "/usr/include/string.h" 3


extern char *strchr (__const char *__s, int __c) __attribute__ ((__pure__));

extern char *strrchr (__const char *__s, int __c) __attribute__ ((__pure__));











extern size_t strcspn (__const char *__s, __const char *__reject)
     __attribute__ ((__pure__));


extern size_t strspn (__const char *__s, __const char *__accept)
     __attribute__ ((__pure__));

extern char *strpbrk (__const char *__s, __const char *__accept)
     __attribute__ ((__pure__));

extern char *strstr (__const char *__haystack, __const char *__needle)
     __attribute__ ((__pure__));



extern char *strtok (char *__restrict __s, __const char *__restrict __delim)
     ;




extern char *__strtok_r (char *__restrict __s,
                         __const char *__restrict __delim,
                         char **__restrict __save_ptr) ;

extern char *strtok_r (char *__restrict __s, __const char *__restrict __delim,
                       char **__restrict __save_ptr) ;
# 228 "/usr/include/string.h" 3


extern size_t strlen (__const char *__s) __attribute__ ((__pure__));

# 241 "/usr/include/string.h" 3


extern char *strerror (int __errnum) ;




extern char *strerror_r (int __errnum, char *__buf, size_t __buflen) ;




extern void __bzero (void *__s, size_t __n) ;



extern void bcopy (__const void *__src, void *__dest, size_t __n) ;


extern void bzero (void *__s, size_t __n) ;


extern int bcmp (__const void *__s1, __const void *__s2, size_t __n)
     __attribute__ ((__pure__));


extern char *index (__const char *__s, int __c) __attribute__ ((__pure__));


extern char *rindex (__const char *__s, int __c) __attribute__ ((__pure__));



extern int ffs (int __i) __attribute__ ((__const__));
# 287 "/usr/include/string.h" 3
extern int strcasecmp (__const char *__s1, __const char *__s2)
     __attribute__ ((__pure__));


extern int strncasecmp (__const char *__s1, __const char *__s2, size_t __n)
     __attribute__ ((__pure__));
# 309 "/usr/include/string.h" 3
extern char *strsep (char **__restrict __stringp,
                     __const char *__restrict __delim) ;
# 372 "/usr/include/string.h" 3
# 1 "/usr/include/bits/string.h" 1 3
# 373 "/usr/include/string.h" 2 3


# 1 "/usr/include/bits/string2.h" 1 3
# 389 "/usr/include/bits/string2.h" 3
extern void *__rawmemchr (const void *__s, int __c);
# 919 "/usr/include/bits/string2.h" 3
extern __inline size_t __strcspn_c1 (__const char *__s, int __reject);
extern __inline size_t
__strcspn_c1 (__const char *__s, int __reject)
{
  register size_t __result = 0;
  while (__s[__result] != '\0' && __s[__result] != __reject)
    ++__result;
  return __result;
}

extern __inline size_t __strcspn_c2 (__const char *__s, int __reject1,
                                     int __reject2);
extern __inline size_t
__strcspn_c2 (__const char *__s, int __reject1, int __reject2)
{
  register size_t __result = 0;
  while (__s[__result] != '\0' && __s[__result] != __reject1
         && __s[__result] != __reject2)
    ++__result;
  return __result;
}

extern __inline size_t __strcspn_c3 (__const char *__s, int __reject1,
                                     int __reject2, int __reject3);
extern __inline size_t
__strcspn_c3 (__const char *__s, int __reject1, int __reject2,
              int __reject3)
{
  register size_t __result = 0;
  while (__s[__result] != '\0' && __s[__result] != __reject1
         && __s[__result] != __reject2 && __s[__result] != __reject3)
    ++__result;
  return __result;
}
# 976 "/usr/include/bits/string2.h" 3
extern __inline size_t __strspn_c1 (__const char *__s, int __accept);
extern __inline size_t
__strspn_c1 (__const char *__s, int __accept)
{
  register size_t __result = 0;

  while (__s[__result] == __accept)
    ++__result;
  return __result;
}

extern __inline size_t __strspn_c2 (__const char *__s, int __accept1,
                                    int __accept2);
extern __inline size_t
__strspn_c2 (__const char *__s, int __accept1, int __accept2)
{
  register size_t __result = 0;

  while (__s[__result] == __accept1 || __s[__result] == __accept2)
    ++__result;
  return __result;
}

extern __inline size_t __strspn_c3 (__const char *__s, int __accept1,
                                    int __accept2, int __accept3);
extern __inline size_t
__strspn_c3 (__const char *__s, int __accept1, int __accept2, int __accept3)
{
  register size_t __result = 0;

  while (__s[__result] == __accept1 || __s[__result] == __accept2
         || __s[__result] == __accept3)
    ++__result;
  return __result;
}
# 1033 "/usr/include/bits/string2.h" 3
extern __inline char *__strpbrk_c2 (__const char *__s, int __accept1,
                                     int __accept2);
extern __inline char *
__strpbrk_c2 (__const char *__s, int __accept1, int __accept2)
{

  while (*__s != '\0' && *__s != __accept1 && *__s != __accept2)
    ++__s;
  return *__s == '\0' ? ((void *)0) : (char *) (size_t) __s;
}

extern __inline char *__strpbrk_c3 (__const char *__s, int __accept1,
                                     int __accept2, int __accept3);
extern __inline char *
__strpbrk_c3 (__const char *__s, int __accept1, int __accept2,
              int __accept3)
{

  while (*__s != '\0' && *__s != __accept1 && *__s != __accept2
         && *__s != __accept3)
    ++__s;
  return *__s == '\0' ? ((void *)0) : (char *) (size_t) __s;
}
# 1085 "/usr/include/bits/string2.h" 3
extern __inline char *__strtok_r_1c (char *__s, char __sep, char **__nextp);
extern __inline char *
__strtok_r_1c (char *__s, char __sep, char **__nextp)
{
  char *__result;
  if (__s == ((void *)0))
    __s = *__nextp;
  while (*__s == __sep)
    ++__s;
  __result = ((void *)0);
  if (*__s != '\0')
    {
      __result = __s++;
      while (*__s != '\0')
        if (*__s++ == __sep)
          {
            __s[-1] = '\0';
            break;
          }
      *__nextp = __s;
    }
  return __result;
}
# 1117 "/usr/include/bits/string2.h" 3
extern char *__strsep_g (char **__stringp, __const char *__delim);
# 1135 "/usr/include/bits/string2.h" 3
extern __inline char *__strsep_1c (char **__s, char __reject);
extern __inline char *
__strsep_1c (char **__s, char __reject)
{
  register char *__retval = *__s;
  if (__retval != ((void *)0) && (*__s = (__extension__ (__builtin_constant_p (__reject) && (__reject) == '\0' ? (char *) __rawmemchr (__retval, __reject) : strchr (__retval, __reject)))) != ((void *)0))
    *(*__s)++ = '\0';
  return __retval;
}

extern __inline char *__strsep_2c (char **__s, char __reject1, char __reject2);
extern __inline char *
__strsep_2c (char **__s, char __reject1, char __reject2)
{
  register char *__retval = *__s;
  if (__retval != ((void *)0))
    {
      register char *__cp = __retval;
      while (1)
        {
          if (*__cp == '\0')
            {
              __cp = ((void *)0);
          break;
            }
          if (*__cp == __reject1 || *__cp == __reject2)
            {
              *__cp++ = '\0';
              break;
            }
          ++__cp;
        }
      *__s = __cp;
    }
  return __retval;
}

extern __inline char *__strsep_3c (char **__s, char __reject1, char __reject2,
                                   char __reject3);
extern __inline char *
__strsep_3c (char **__s, char __reject1, char __reject2, char __reject3)
{
  register char *__retval = *__s;
  if (__retval != ((void *)0))
    {
      register char *__cp = __retval;
      while (1)
        {
          if (*__cp == '\0')
            {
              __cp = ((void *)0);
          break;
            }
          if (*__cp == __reject1 || *__cp == __reject2 || *__cp == __reject3)
            {
              *__cp++ = '\0';
              break;
            }
          ++__cp;
        }
      *__s = __cp;
    }
  return __retval;
}
# 1216 "/usr/include/bits/string2.h" 3
extern char *__strdup (__const char *__string) __attribute__ ((__malloc__));
# 1235 "/usr/include/bits/string2.h" 3
extern char *__strndup (__const char *__string, size_t __n)
     __attribute__ ((__malloc__));
# 376 "/usr/include/string.h" 2 3




# 88 "bltInt.h" 2



# 1 "/usr/include/errno.h" 1 3
# 32 "/usr/include/errno.h" 3




# 1 "/usr/include/bits/errno.h" 1 3
# 25 "/usr/include/bits/errno.h" 3
# 1 "/usr/include/linux/errno.h" 1 3



# 1 "/usr/include/asm/errno.h" 1 3
# 5 "/usr/include/linux/errno.h" 2 3
# 26 "/usr/include/bits/errno.h" 2 3
# 38 "/usr/include/bits/errno.h" 3
extern int *__errno_location (void) __attribute__ ((__const__));
# 37 "/usr/include/errno.h" 2 3
# 59 "/usr/include/errno.h" 3

# 92 "bltInt.h" 2



# 1 "/usr/include/ctype.h" 1 3
# 30 "/usr/include/ctype.h" 3

# 48 "/usr/include/ctype.h" 3
enum
{
  _ISupper = ((0) < 8 ? ((1 << (0)) << 8) : ((1 << (0)) >> 8)),
  _ISlower = ((1) < 8 ? ((1 << (1)) << 8) : ((1 << (1)) >> 8)),
  _ISalpha = ((2) < 8 ? ((1 << (2)) << 8) : ((1 << (2)) >> 8)),
  _ISdigit = ((3) < 8 ? ((1 << (3)) << 8) : ((1 << (3)) >> 8)),
  _ISxdigit = ((4) < 8 ? ((1 << (4)) << 8) : ((1 << (4)) >> 8)),
  _ISspace = ((5) < 8 ? ((1 << (5)) << 8) : ((1 << (5)) >> 8)),
  _ISprint = ((6) < 8 ? ((1 << (6)) << 8) : ((1 << (6)) >> 8)),
  _ISgraph = ((7) < 8 ? ((1 << (7)) << 8) : ((1 << (7)) >> 8)),
  _ISblank = ((8) < 8 ? ((1 << (8)) << 8) : ((1 << (8)) >> 8)),
  _IScntrl = ((9) < 8 ? ((1 << (9)) << 8) : ((1 << (9)) >> 8)),
  _ISpunct = ((10) < 8 ? ((1 << (10)) << 8) : ((1 << (10)) >> 8)),
  _ISalnum = ((11) < 8 ? ((1 << (11)) << 8) : ((1 << (11)) >> 8))
};
# 81 "/usr/include/ctype.h" 3
extern __const unsigned short int **__ctype_b_loc (void)
     __attribute__ ((__const));
extern __const __int32_t **__ctype_tolower_loc (void)
     __attribute__ ((__const));
extern __const __int32_t **__ctype_toupper_loc (void)
     __attribute__ ((__const));
# 96 "/usr/include/ctype.h" 3






extern int isalnum (int) ;
extern int isalpha (int) ;
extern int iscntrl (int) ;
extern int isdigit (int) ;
extern int islower (int) ;
extern int isgraph (int) ;
extern int isprint (int) ;
extern int ispunct (int) ;
extern int isspace (int) ;
extern int isupper (int) ;
extern int isxdigit (int) ;



extern int tolower (int __c) ;


extern int toupper (int __c) ;


# 142 "/usr/include/ctype.h" 3
extern int isascii (int __c) ;



extern int toascii (int __c) ;



extern int _toupper (int) ;
extern int _tolower (int) ;
# 190 "/usr/include/ctype.h" 3
extern __inline int
tolower (int __c)
{
  return __c >= -128 && __c < 256 ? (*__ctype_tolower_loc ())[__c] : __c;
}

extern __inline int
toupper (int __c)
{
  return __c >= -128 && __c < 256 ? (*__ctype_toupper_loc ())[__c] : __c;
}
# 323 "/usr/include/ctype.h" 3

# 96 "bltInt.h" 2



# 1 "/usr/include/memory.h" 1 3
# 100 "bltInt.h" 2



# 1 "/usr/include/unistd.h" 1 3
# 28 "/usr/include/unistd.h" 3

# 171 "/usr/include/unistd.h" 3
# 1 "/usr/include/bits/posix_opt.h" 1 3
# 172 "/usr/include/unistd.h" 2 3
# 195 "/usr/include/unistd.h" 3
# 1 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stddef.h" 1 3
# 196 "/usr/include/unistd.h" 2 3
# 243 "/usr/include/unistd.h" 3
typedef __socklen_t socklen_t;
# 256 "/usr/include/unistd.h" 3
extern int access (__const char *__name, int __type) ;
# 286 "/usr/include/unistd.h" 3
extern __off_t lseek (int __fd, __off_t __offset, int __whence) ;
# 305 "/usr/include/unistd.h" 3
extern int close (int __fd);






extern ssize_t read (int __fd, void *__buf, size_t __nbytes);





extern ssize_t write (int __fd, __const void *__buf, size_t __n);
# 369 "/usr/include/unistd.h" 3
extern int pipe (int __pipedes[2]) ;
# 378 "/usr/include/unistd.h" 3
extern unsigned int alarm (unsigned int __seconds) ;
# 390 "/usr/include/unistd.h" 3
extern unsigned int sleep (unsigned int __seconds);






extern __useconds_t ualarm (__useconds_t __value, __useconds_t __interval)
     ;






extern int usleep (__useconds_t __useconds);
# 414 "/usr/include/unistd.h" 3
extern int pause (void);



extern int chown (__const char *__file, __uid_t __owner, __gid_t __group)
     ;



extern int fchown (int __fd, __uid_t __owner, __gid_t __group) ;




extern int lchown (__const char *__file, __uid_t __owner, __gid_t __group)
     ;




extern int chdir (__const char *__path) ;



extern int fchdir (int __fd) ;
# 448 "/usr/include/unistd.h" 3
extern char *getcwd (char *__buf, size_t __size) ;
# 461 "/usr/include/unistd.h" 3
extern char *getwd (char *__buf) ;




extern int dup (int __fd) ;


extern int dup2 (int __fd, int __fd2) ;


extern char **__environ;







extern int execve (__const char *__path, char *__const __argv[],
                   char *__const __envp[]) ;
# 492 "/usr/include/unistd.h" 3
extern int execv (__const char *__path, char *__const __argv[]) ;



extern int execle (__const char *__path, __const char *__arg, ...) ;



extern int execl (__const char *__path, __const char *__arg, ...) ;



extern int execvp (__const char *__file, char *__const __argv[]) ;




extern int execlp (__const char *__file, __const char *__arg, ...) ;




extern int nice (int __inc) ;




extern void _exit (int __status) __attribute__ ((__noreturn__));





# 1 "/usr/include/bits/confname.h" 1 3
# 25 "/usr/include/bits/confname.h" 3
enum
  {
    _PC_LINK_MAX,

    _PC_MAX_CANON,

    _PC_MAX_INPUT,

    _PC_NAME_MAX,

    _PC_PATH_MAX,

    _PC_PIPE_BUF,

    _PC_CHOWN_RESTRICTED,

    _PC_NO_TRUNC,

    _PC_VDISABLE,

    _PC_SYNC_IO,

    _PC_ASYNC_IO,

    _PC_PRIO_IO,

    _PC_SOCK_MAXBUF,

    _PC_FILESIZEBITS,

    _PC_REC_INCR_XFER_SIZE,

    _PC_REC_MAX_XFER_SIZE,

    _PC_REC_MIN_XFER_SIZE,

    _PC_REC_XFER_ALIGN,

    _PC_ALLOC_SIZE_MIN,

    _PC_SYMLINK_MAX,

    _PC_2_SYMLINKS

  };


enum
  {
    _SC_ARG_MAX,

    _SC_CHILD_MAX,

    _SC_CLK_TCK,

    _SC_NGROUPS_MAX,

    _SC_OPEN_MAX,

    _SC_STREAM_MAX,

    _SC_TZNAME_MAX,

    _SC_JOB_CONTROL,

    _SC_SAVED_IDS,

    _SC_REALTIME_SIGNALS,

    _SC_PRIORITY_SCHEDULING,

    _SC_TIMERS,

    _SC_ASYNCHRONOUS_IO,

    _SC_PRIORITIZED_IO,

    _SC_SYNCHRONIZED_IO,

    _SC_FSYNC,

    _SC_MAPPED_FILES,

    _SC_MEMLOCK,

    _SC_MEMLOCK_RANGE,

    _SC_MEMORY_PROTECTION,

    _SC_MESSAGE_PASSING,

    _SC_SEMAPHORES,

    _SC_SHARED_MEMORY_OBJECTS,

    _SC_AIO_LISTIO_MAX,

    _SC_AIO_MAX,

    _SC_AIO_PRIO_DELTA_MAX,

    _SC_DELAYTIMER_MAX,

    _SC_MQ_OPEN_MAX,

    _SC_MQ_PRIO_MAX,

    _SC_VERSION,

    _SC_PAGESIZE,


    _SC_RTSIG_MAX,

    _SC_SEM_NSEMS_MAX,

    _SC_SEM_VALUE_MAX,

    _SC_SIGQUEUE_MAX,

    _SC_TIMER_MAX,




    _SC_BC_BASE_MAX,

    _SC_BC_DIM_MAX,

    _SC_BC_SCALE_MAX,

    _SC_BC_STRING_MAX,

    _SC_COLL_WEIGHTS_MAX,

    _SC_EQUIV_CLASS_MAX,

    _SC_EXPR_NEST_MAX,

    _SC_LINE_MAX,

    _SC_RE_DUP_MAX,

    _SC_CHARCLASS_NAME_MAX,


    _SC_2_VERSION,

    _SC_2_C_BIND,

    _SC_2_C_DEV,

    _SC_2_FORT_DEV,

    _SC_2_FORT_RUN,

    _SC_2_SW_DEV,

    _SC_2_LOCALEDEF,


    _SC_PII,

    _SC_PII_XTI,

    _SC_PII_SOCKET,

    _SC_PII_INTERNET,

    _SC_PII_OSI,

    _SC_POLL,

    _SC_SELECT,

    _SC_UIO_MAXIOV,

    _SC_IOV_MAX = _SC_UIO_MAXIOV,

    _SC_PII_INTERNET_STREAM,

    _SC_PII_INTERNET_DGRAM,

    _SC_PII_OSI_COTS,

    _SC_PII_OSI_CLTS,

    _SC_PII_OSI_M,

    _SC_T_IOV_MAX,



    _SC_THREADS,

    _SC_THREAD_SAFE_FUNCTIONS,

    _SC_GETGR_R_SIZE_MAX,

    _SC_GETPW_R_SIZE_MAX,

    _SC_LOGIN_NAME_MAX,

    _SC_TTY_NAME_MAX,

    _SC_THREAD_DESTRUCTOR_ITERATIONS,

    _SC_THREAD_KEYS_MAX,

    _SC_THREAD_STACK_MIN,

    _SC_THREAD_THREADS_MAX,

    _SC_THREAD_ATTR_STACKADDR,

    _SC_THREAD_ATTR_STACKSIZE,

    _SC_THREAD_PRIORITY_SCHEDULING,

    _SC_THREAD_PRIO_INHERIT,

    _SC_THREAD_PRIO_PROTECT,

    _SC_THREAD_PROCESS_SHARED,


    _SC_NPROCESSORS_CONF,

    _SC_NPROCESSORS_ONLN,

    _SC_PHYS_PAGES,

    _SC_AVPHYS_PAGES,

    _SC_ATEXIT_MAX,

    _SC_PASS_MAX,


    _SC_XOPEN_VERSION,

    _SC_XOPEN_XCU_VERSION,

    _SC_XOPEN_UNIX,

    _SC_XOPEN_CRYPT,

    _SC_XOPEN_ENH_I18N,

    _SC_XOPEN_SHM,


    _SC_2_CHAR_TERM,

    _SC_2_C_VERSION,

    _SC_2_UPE,


    _SC_XOPEN_XPG2,

    _SC_XOPEN_XPG3,

    _SC_XOPEN_XPG4,


    _SC_CHAR_BIT,

    _SC_CHAR_MAX,

    _SC_CHAR_MIN,

    _SC_INT_MAX,

    _SC_INT_MIN,

    _SC_LONG_BIT,

    _SC_WORD_BIT,

    _SC_MB_LEN_MAX,

    _SC_NZERO,

    _SC_SSIZE_MAX,

    _SC_SCHAR_MAX,

    _SC_SCHAR_MIN,

    _SC_SHRT_MAX,

    _SC_SHRT_MIN,

    _SC_UCHAR_MAX,

    _SC_UINT_MAX,

    _SC_ULONG_MAX,

    _SC_USHRT_MAX,


    _SC_NL_ARGMAX,

    _SC_NL_LANGMAX,

    _SC_NL_MSGMAX,

    _SC_NL_NMAX,

    _SC_NL_SETMAX,

    _SC_NL_TEXTMAX,


    _SC_XBS5_ILP32_OFF32,

    _SC_XBS5_ILP32_OFFBIG,

    _SC_XBS5_LP64_OFF64,

    _SC_XBS5_LPBIG_OFFBIG,


    _SC_XOPEN_LEGACY,

    _SC_XOPEN_REALTIME,

    _SC_XOPEN_REALTIME_THREADS,


    _SC_ADVISORY_INFO,

    _SC_BARRIERS,

    _SC_BASE,

    _SC_C_LANG_SUPPORT,

    _SC_C_LANG_SUPPORT_R,

    _SC_CLOCK_SELECTION,

    _SC_CPUTIME,

    _SC_THREAD_CPUTIME,

    _SC_DEVICE_IO,

    _SC_DEVICE_SPECIFIC,

    _SC_DEVICE_SPECIFIC_R,

    _SC_FD_MGMT,

    _SC_FIFO,

    _SC_PIPE,

    _SC_FILE_ATTRIBUTES,

    _SC_FILE_LOCKING,

    _SC_FILE_SYSTEM,

    _SC_MONOTONIC_CLOCK,

    _SC_MULTI_PROCESS,

    _SC_SINGLE_PROCESS,

    _SC_NETWORKING,

    _SC_READER_WRITER_LOCKS,

    _SC_SPIN_LOCKS,

    _SC_REGEXP,

    _SC_REGEX_VERSION,

    _SC_SHELL,

    _SC_SIGNALS,

    _SC_SPAWN,

    _SC_SPORADIC_SERVER,

    _SC_THREAD_SPORADIC_SERVER,

    _SC_SYSTEM_DATABASE,

    _SC_SYSTEM_DATABASE_R,

    _SC_TIMEOUTS,

    _SC_TYPED_MEMORY_OBJECTS,

    _SC_USER_GROUPS,

    _SC_USER_GROUPS_R,

    _SC_2_PBS,

    _SC_2_PBS_ACCOUNTING,

    _SC_2_PBS_LOCATE,

    _SC_2_PBS_MESSAGE,

    _SC_2_PBS_TRACK,

    _SC_SYMLOOP_MAX,

    _SC_STREAMS,

    _SC_2_PBS_CHECKPOINT,


    _SC_V6_ILP32_OFF32,

    _SC_V6_ILP32_OFFBIG,

    _SC_V6_LP64_OFF64,

    _SC_V6_LPBIG_OFFBIG,


    _SC_HOST_NAME_MAX,

    _SC_TRACE,

    _SC_TRACE_EVENT_FILTER,

    _SC_TRACE_INHERIT,

    _SC_TRACE_LOG

  };


enum
  {
    _CS_PATH,


    _CS_V6_WIDTH_RESTRICTED_ENVS,


    _CS_GNU_LIBC_VERSION,

    _CS_GNU_LIBPTHREAD_VERSION,


    _CS_LFS_CFLAGS = 1000,

    _CS_LFS_LDFLAGS,

    _CS_LFS_LIBS,

    _CS_LFS_LINTFLAGS,

    _CS_LFS64_CFLAGS,

    _CS_LFS64_LDFLAGS,

    _CS_LFS64_LIBS,

    _CS_LFS64_LINTFLAGS,


    _CS_XBS5_ILP32_OFF32_CFLAGS = 1100,

    _CS_XBS5_ILP32_OFF32_LDFLAGS,

    _CS_XBS5_ILP32_OFF32_LIBS,

    _CS_XBS5_ILP32_OFF32_LINTFLAGS,

    _CS_XBS5_ILP32_OFFBIG_CFLAGS,

    _CS_XBS5_ILP32_OFFBIG_LDFLAGS,

    _CS_XBS5_ILP32_OFFBIG_LIBS,

    _CS_XBS5_ILP32_OFFBIG_LINTFLAGS,

    _CS_XBS5_LP64_OFF64_CFLAGS,

    _CS_XBS5_LP64_OFF64_LDFLAGS,

    _CS_XBS5_LP64_OFF64_LIBS,

    _CS_XBS5_LP64_OFF64_LINTFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_CFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_LDFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_LIBS,

    _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS,


    _CS_POSIX_V6_ILP32_OFF32_CFLAGS,

    _CS_POSIX_V6_ILP32_OFF32_LDFLAGS,

    _CS_POSIX_V6_ILP32_OFF32_LIBS,

    _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_LIBS,

    _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS,

    _CS_POSIX_V6_LP64_OFF64_CFLAGS,

    _CS_POSIX_V6_LP64_OFF64_LDFLAGS,

    _CS_POSIX_V6_LP64_OFF64_LIBS,

    _CS_POSIX_V6_LP64_OFF64_LINTFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LIBS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS

  };
# 526 "/usr/include/unistd.h" 2 3


extern long int pathconf (__const char *__path, int __name) ;


extern long int fpathconf (int __fd, int __name) ;


extern long int sysconf (int __name) __attribute__ ((__const__));



extern size_t confstr (int __name, char *__buf, size_t __len) ;




extern __pid_t getpid (void) ;


extern __pid_t getppid (void) ;




extern __pid_t getpgrp (void) ;
# 561 "/usr/include/unistd.h" 3
extern __pid_t __getpgid (__pid_t __pid) ;
# 570 "/usr/include/unistd.h" 3
extern int setpgid (__pid_t __pid, __pid_t __pgid) ;
# 587 "/usr/include/unistd.h" 3
extern int setpgrp (void) ;
# 605 "/usr/include/unistd.h" 3
extern __pid_t setsid (void) ;







extern __uid_t getuid (void) ;


extern __uid_t geteuid (void) ;


extern __gid_t getgid (void) ;


extern __gid_t getegid (void) ;




extern int getgroups (int __size, __gid_t __list[]) ;
# 638 "/usr/include/unistd.h" 3
extern int setuid (__uid_t __uid) ;




extern int setreuid (__uid_t __ruid, __uid_t __euid) ;




extern int seteuid (__uid_t __uid) ;






extern int setgid (__gid_t __gid) ;




extern int setregid (__gid_t __rgid, __gid_t __egid) ;




extern int setegid (__gid_t __gid) ;
# 690 "/usr/include/unistd.h" 3
extern __pid_t fork (void) ;






extern __pid_t vfork (void) ;





extern char *ttyname (int __fd) ;



extern int ttyname_r (int __fd, char *__buf, size_t __buflen) ;



extern int isatty (int __fd) ;





extern int ttyslot (void) ;




extern int link (__const char *__from, __const char *__to) ;



extern int symlink (__const char *__from, __const char *__to) ;




extern int readlink (__const char *__restrict __path, char *__restrict __buf,
                     size_t __len) ;



extern int unlink (__const char *__name) ;


extern int rmdir (__const char *__path) ;



extern __pid_t tcgetpgrp (int __fd) ;


extern int tcsetpgrp (int __fd, __pid_t __pgrp_id) ;






extern char *getlogin (void);
# 766 "/usr/include/unistd.h" 3
extern int setlogin (__const char *__name) ;
# 775 "/usr/include/unistd.h" 3
# 1 "/usr/include/getopt.h" 1 3
# 55 "/usr/include/getopt.h" 3
extern char *optarg;
# 69 "/usr/include/getopt.h" 3
extern int optind;




extern int opterr;



extern int optopt;
# 153 "/usr/include/getopt.h" 3
extern int getopt (int ___argc, char *const *___argv, const char *__shortopts)
       ;
# 776 "/usr/include/unistd.h" 2 3







extern int gethostname (char *__name, size_t __len) ;






extern int sethostname (__const char *__name, size_t __len) ;



extern int sethostid (long int __id) ;





extern int getdomainname (char *__name, size_t __len) ;
extern int setdomainname (__const char *__name, size_t __len) ;





extern int vhangup (void) ;


extern int revoke (__const char *__file) ;







extern int profil (unsigned short int *__sample_buffer, size_t __size,
                   size_t __offset, unsigned int __scale) ;





extern int acct (__const char *__name) ;



extern char *getusershell (void) ;
extern void endusershell (void) ;
extern void setusershell (void) ;





extern int daemon (int __nochdir, int __noclose) ;






extern int chroot (__const char *__path) ;



extern char *getpass (__const char *__prompt);
# 857 "/usr/include/unistd.h" 3
extern int fsync (int __fd);






extern long int gethostid (void);


extern void sync (void) ;




extern int getpagesize (void) __attribute__ ((__const__));




extern int truncate (__const char *__file, __off_t __length) ;
# 893 "/usr/include/unistd.h" 3
extern int ftruncate (int __fd, __off_t __length) ;
# 909 "/usr/include/unistd.h" 3
extern int getdtablesize (void) ;
# 918 "/usr/include/unistd.h" 3
extern int brk (void *__addr) ;





extern void *sbrk (intptr_t __delta) ;
# 939 "/usr/include/unistd.h" 3
extern long int syscall (long int __sysno, ...) ;
# 962 "/usr/include/unistd.h" 3
extern int lockf (int __fd, int __cmd, __off_t __len);
# 993 "/usr/include/unistd.h" 3
extern int fdatasync (int __fildes) ;
# 1024 "/usr/include/unistd.h" 3

# 104 "bltInt.h" 2



# 1 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/limits.h" 1 3
# 11 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/limits.h" 3
# 1 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/syslimits.h" 1 3






# 1 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/limits.h" 1 3
# 132 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/limits.h" 3
# 1 "/usr/include/limits.h" 1 3
# 144 "/usr/include/limits.h" 3
# 1 "/usr/include/bits/posix1_lim.h" 1 3
# 153 "/usr/include/bits/posix1_lim.h" 3
# 1 "/usr/include/bits/local_lim.h" 1 3
# 36 "/usr/include/bits/local_lim.h" 3
# 1 "/usr/include/linux/limits.h" 1 3
# 37 "/usr/include/bits/local_lim.h" 2 3
# 154 "/usr/include/bits/posix1_lim.h" 2 3
# 145 "/usr/include/limits.h" 2 3



# 1 "/usr/include/bits/posix2_lim.h" 1 3
# 149 "/usr/include/limits.h" 2 3
# 133 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/limits.h" 2 3
# 8 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/syslimits.h" 2 3
# 12 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/limits.h" 2 3
# 108 "bltInt.h" 2


# 1 "bltMath.h" 1
# 29 "bltMath.h"
# 1 "/usr/include/math.h" 1 3
# 29 "/usr/include/math.h" 3




# 1 "/usr/include/bits/huge_val.h" 1 3
# 34 "/usr/include/math.h" 2 3






# 1 "/usr/include/bits/mathdef.h" 1 3
# 41 "/usr/include/math.h" 2 3
# 65 "/usr/include/math.h" 3
# 1 "/usr/include/bits/mathcalls.h" 1 3
# 53 "/usr/include/bits/mathcalls.h" 3


extern double acos (double __x) ; extern double __acos (double __x) ;

extern double asin (double __x) ; extern double __asin (double __x) ;

extern double atan (double __x) ; extern double __atan (double __x) ;

extern double atan2 (double __y, double __x) ; extern double __atan2 (double __y, double __x) ;


extern double cos (double __x) ; extern double __cos (double __x) ;

extern double sin (double __x) ; extern double __sin (double __x) ;

extern double tan (double __x) ; extern double __tan (double __x) ;




extern double cosh (double __x) ; extern double __cosh (double __x) ;

extern double sinh (double __x) ; extern double __sinh (double __x) ;

extern double tanh (double __x) ; extern double __tanh (double __x) ;

# 87 "/usr/include/bits/mathcalls.h" 3


extern double acosh (double __x) ; extern double __acosh (double __x) ;

extern double asinh (double __x) ; extern double __asinh (double __x) ;

extern double atanh (double __x) ; extern double __atanh (double __x) ;







extern double exp (double __x) ; extern double __exp (double __x) ;


extern double frexp (double __x, int *__exponent) ; extern double __frexp (double __x, int *__exponent) ;


extern double ldexp (double __x, int __exponent) ; extern double __ldexp (double __x, int __exponent) ;


extern double log (double __x) ; extern double __log (double __x) ;


extern double log10 (double __x) ; extern double __log10 (double __x) ;


extern double modf (double __x, double *__iptr) ; extern double __modf (double __x, double *__iptr) ;

# 127 "/usr/include/bits/mathcalls.h" 3


extern double expm1 (double __x) ; extern double __expm1 (double __x) ;


extern double log1p (double __x) ; extern double __log1p (double __x) ;


extern double logb (double __x) ; extern double __logb (double __x) ;

# 152 "/usr/include/bits/mathcalls.h" 3


extern double pow (double __x, double __y) ; extern double __pow (double __x, double __y) ;


extern double sqrt (double __x) ; extern double __sqrt (double __x) ;





extern double hypot (double __x, double __y) ; extern double __hypot (double __x, double __y) ;






extern double cbrt (double __x) ; extern double __cbrt (double __x) ;








extern double ceil (double __x) __attribute__ ((__const__)); extern double __ceil (double __x) __attribute__ ((__const__));


extern double fabs (double __x) __attribute__ ((__const__)); extern double __fabs (double __x) __attribute__ ((__const__));


extern double floor (double __x) __attribute__ ((__const__)); extern double __floor (double __x) __attribute__ ((__const__));


extern double fmod (double __x, double __y) ; extern double __fmod (double __x, double __y) ;




extern int __isinf (double __value) __attribute__ ((__const__));


extern int __finite (double __value) __attribute__ ((__const__));





extern int isinf (double __value) __attribute__ ((__const__));


extern int finite (double __value) __attribute__ ((__const__));


extern double drem (double __x, double __y) ; extern double __drem (double __x, double __y) ;



extern double significand (double __x) ; extern double __significand (double __x) ;





extern double copysign (double __x, double __y) __attribute__ ((__const__)); extern double __copysign (double __x, double __y) __attribute__ ((__const__));

# 231 "/usr/include/bits/mathcalls.h" 3
extern int __isnan (double __value) __attribute__ ((__const__));



extern int isnan (double __value) __attribute__ ((__const__));


extern double j0 (double) ; extern double __j0 (double) ;
extern double j1 (double) ; extern double __j1 (double) ;
extern double jn (int, double) ; extern double __jn (int, double) ;
extern double y0 (double) ; extern double __y0 (double) ;
extern double y1 (double) ; extern double __y1 (double) ;
extern double yn (int, double) ; extern double __yn (int, double) ;






extern double erf (double) ; extern double __erf (double) ;
extern double erfc (double) ; extern double __erfc (double) ;
extern double lgamma (double) ; extern double __lgamma (double) ;

# 265 "/usr/include/bits/mathcalls.h" 3
extern double gamma (double) ; extern double __gamma (double) ;






extern double lgamma_r (double, int *__signgamp) ; extern double __lgamma_r (double, int *__signgamp) ;







extern double rint (double __x) ; extern double __rint (double __x) ;


extern double nextafter (double __x, double __y) __attribute__ ((__const__)); extern double __nextafter (double __x, double __y) __attribute__ ((__const__));





extern double remainder (double __x, double __y) ; extern double __remainder (double __x, double __y) ;



extern double scalbn (double __x, int __n) ; extern double __scalbn (double __x, int __n) ;



extern int ilogb (double __x) ; extern int __ilogb (double __x) ;
# 66 "/usr/include/math.h" 2 3
# 88 "/usr/include/math.h" 3
# 1 "/usr/include/bits/mathcalls.h" 1 3
# 53 "/usr/include/bits/mathcalls.h" 3


extern float acosf (float __x) ; extern float __acosf (float __x) ;

extern float asinf (float __x) ; extern float __asinf (float __x) ;

extern float atanf (float __x) ; extern float __atanf (float __x) ;

extern float atan2f (float __y, float __x) ; extern float __atan2f (float __y, float __x) ;


extern float cosf (float __x) ; extern float __cosf (float __x) ;

extern float sinf (float __x) ; extern float __sinf (float __x) ;

extern float tanf (float __x) ; extern float __tanf (float __x) ;




extern float coshf (float __x) ; extern float __coshf (float __x) ;

extern float sinhf (float __x) ; extern float __sinhf (float __x) ;

extern float tanhf (float __x) ; extern float __tanhf (float __x) ;

# 87 "/usr/include/bits/mathcalls.h" 3


extern float acoshf (float __x) ; extern float __acoshf (float __x) ;

extern float asinhf (float __x) ; extern float __asinhf (float __x) ;

extern float atanhf (float __x) ; extern float __atanhf (float __x) ;







extern float expf (float __x) ; extern float __expf (float __x) ;


extern float frexpf (float __x, int *__exponent) ; extern float __frexpf (float __x, int *__exponent) ;


extern float ldexpf (float __x, int __exponent) ; extern float __ldexpf (float __x, int __exponent) ;


extern float logf (float __x) ; extern float __logf (float __x) ;


extern float log10f (float __x) ; extern float __log10f (float __x) ;


extern float modff (float __x, float *__iptr) ; extern float __modff (float __x, float *__iptr) ;

# 127 "/usr/include/bits/mathcalls.h" 3


extern float expm1f (float __x) ; extern float __expm1f (float __x) ;


extern float log1pf (float __x) ; extern float __log1pf (float __x) ;


extern float logbf (float __x) ; extern float __logbf (float __x) ;

# 152 "/usr/include/bits/mathcalls.h" 3


extern float powf (float __x, float __y) ; extern float __powf (float __x, float __y) ;


extern float sqrtf (float __x) ; extern float __sqrtf (float __x) ;





extern float hypotf (float __x, float __y) ; extern float __hypotf (float __x, float __y) ;






extern float cbrtf (float __x) ; extern float __cbrtf (float __x) ;








extern float ceilf (float __x) __attribute__ ((__const__)); extern float __ceilf (float __x) __attribute__ ((__const__));


extern float fabsf (float __x) __attribute__ ((__const__)); extern float __fabsf (float __x) __attribute__ ((__const__));


extern float floorf (float __x) __attribute__ ((__const__)); extern float __floorf (float __x) __attribute__ ((__const__));


extern float fmodf (float __x, float __y) ; extern float __fmodf (float __x, float __y) ;




extern int __isinff (float __value) __attribute__ ((__const__));


extern int __finitef (float __value) __attribute__ ((__const__));





extern int isinff (float __value) __attribute__ ((__const__));


extern int finitef (float __value) __attribute__ ((__const__));


extern float dremf (float __x, float __y) ; extern float __dremf (float __x, float __y) ;



extern float significandf (float __x) ; extern float __significandf (float __x) ;





extern float copysignf (float __x, float __y) __attribute__ ((__const__)); extern float __copysignf (float __x, float __y) __attribute__ ((__const__));

# 231 "/usr/include/bits/mathcalls.h" 3
extern int __isnanf (float __value) __attribute__ ((__const__));



extern int isnanf (float __value) __attribute__ ((__const__));


extern float j0f (float) ; extern float __j0f (float) ;
extern float j1f (float) ; extern float __j1f (float) ;
extern float jnf (int, float) ; extern float __jnf (int, float) ;
extern float y0f (float) ; extern float __y0f (float) ;
extern float y1f (float) ; extern float __y1f (float) ;
extern float ynf (int, float) ; extern float __ynf (int, float) ;






extern float erff (float) ; extern float __erff (float) ;
extern float erfcf (float) ; extern float __erfcf (float) ;
extern float lgammaf (float) ; extern float __lgammaf (float) ;

# 265 "/usr/include/bits/mathcalls.h" 3
extern float gammaf (float) ; extern float __gammaf (float) ;






extern float lgammaf_r (float, int *__signgamp) ; extern float __lgammaf_r (float, int *__signgamp) ;







extern float rintf (float __x) ; extern float __rintf (float __x) ;


extern float nextafterf (float __x, float __y) __attribute__ ((__const__)); extern float __nextafterf (float __x, float __y) __attribute__ ((__const__));





extern float remainderf (float __x, float __y) ; extern float __remainderf (float __x, float __y) ;



extern float scalbnf (float __x, int __n) ; extern float __scalbnf (float __x, int __n) ;



extern int ilogbf (float __x) ; extern int __ilogbf (float __x) ;
# 89 "/usr/include/math.h" 2 3
# 109 "/usr/include/math.h" 3
# 1 "/usr/include/bits/mathcalls.h" 1 3
# 53 "/usr/include/bits/mathcalls.h" 3


extern long double acosl (long double __x) ; extern long double __acosl (long double __x) ;

extern long double asinl (long double __x) ; extern long double __asinl (long double __x) ;

extern long double atanl (long double __x) ; extern long double __atanl (long double __x) ;

extern long double atan2l (long double __y, long double __x) ; extern long double __atan2l (long double __y, long double __x) ;


extern long double cosl (long double __x) ; extern long double __cosl (long double __x) ;

extern long double sinl (long double __x) ; extern long double __sinl (long double __x) ;

extern long double tanl (long double __x) ; extern long double __tanl (long double __x) ;




extern long double coshl (long double __x) ; extern long double __coshl (long double __x) ;

extern long double sinhl (long double __x) ; extern long double __sinhl (long double __x) ;

extern long double tanhl (long double __x) ; extern long double __tanhl (long double __x) ;

# 87 "/usr/include/bits/mathcalls.h" 3


extern long double acoshl (long double __x) ; extern long double __acoshl (long double __x) ;

extern long double asinhl (long double __x) ; extern long double __asinhl (long double __x) ;

extern long double atanhl (long double __x) ; extern long double __atanhl (long double __x) ;







extern long double expl (long double __x) ; extern long double __expl (long double __x) ;


extern long double frexpl (long double __x, int *__exponent) ; extern long double __frexpl (long double __x, int *__exponent) ;


extern long double ldexpl (long double __x, int __exponent) ; extern long double __ldexpl (long double __x, int __exponent) ;


extern long double logl (long double __x) ; extern long double __logl (long double __x) ;


extern long double log10l (long double __x) ; extern long double __log10l (long double __x) ;


extern long double modfl (long double __x, long double *__iptr) ; extern long double __modfl (long double __x, long double *__iptr) ;

# 127 "/usr/include/bits/mathcalls.h" 3


extern long double expm1l (long double __x) ; extern long double __expm1l (long double __x) ;


extern long double log1pl (long double __x) ; extern long double __log1pl (long double __x) ;


extern long double logbl (long double __x) ; extern long double __logbl (long double __x) ;

# 152 "/usr/include/bits/mathcalls.h" 3


extern long double powl (long double __x, long double __y) ; extern long double __powl (long double __x, long double __y) ;


extern long double sqrtl (long double __x) ; extern long double __sqrtl (long double __x) ;





extern long double hypotl (long double __x, long double __y) ; extern long double __hypotl (long double __x, long double __y) ;






extern long double cbrtl (long double __x) ; extern long double __cbrtl (long double __x) ;








extern long double ceill (long double __x) __attribute__ ((__const__)); extern long double __ceill (long double __x) __attribute__ ((__const__));


extern long double fabsl (long double __x) __attribute__ ((__const__)); extern long double __fabsl (long double __x) __attribute__ ((__const__));


extern long double floorl (long double __x) __attribute__ ((__const__)); extern long double __floorl (long double __x) __attribute__ ((__const__));


extern long double fmodl (long double __x, long double __y) ; extern long double __fmodl (long double __x, long double __y) ;




extern int __isinfl (long double __value) __attribute__ ((__const__));


extern int __finitel (long double __value) __attribute__ ((__const__));





extern int isinfl (long double __value) __attribute__ ((__const__));


extern int finitel (long double __value) __attribute__ ((__const__));


extern long double dreml (long double __x, long double __y) ; extern long double __dreml (long double __x, long double __y) ;



extern long double significandl (long double __x) ; extern long double __significandl (long double __x) ;





extern long double copysignl (long double __x, long double __y) __attribute__ ((__const__)); extern long double __copysignl (long double __x, long double __y) __attribute__ ((__const__));

# 231 "/usr/include/bits/mathcalls.h" 3
extern int __isnanl (long double __value) __attribute__ ((__const__));



extern int isnanl (long double __value) __attribute__ ((__const__));


extern long double j0l (long double) ; extern long double __j0l (long double) ;
extern long double j1l (long double) ; extern long double __j1l (long double) ;
extern long double jnl (int, long double) ; extern long double __jnl (int, long double) ;
extern long double y0l (long double) ; extern long double __y0l (long double) ;
extern long double y1l (long double) ; extern long double __y1l (long double) ;
extern long double ynl (int, long double) ; extern long double __ynl (int, long double) ;






extern long double erfl (long double) ; extern long double __erfl (long double) ;
extern long double erfcl (long double) ; extern long double __erfcl (long double) ;
extern long double lgammal (long double) ; extern long double __lgammal (long double) ;

# 265 "/usr/include/bits/mathcalls.h" 3
extern long double gammal (long double) ; extern long double __gammal (long double) ;






extern long double lgammal_r (long double, int *__signgamp) ; extern long double __lgammal_r (long double, int *__signgamp) ;







extern long double rintl (long double __x) ; extern long double __rintl (long double __x) ;


extern long double nextafterl (long double __x, long double __y) __attribute__ ((__const__)); extern long double __nextafterl (long double __x, long double __y) __attribute__ ((__const__));





extern long double remainderl (long double __x, long double __y) ; extern long double __remainderl (long double __x, long double __y) ;



extern long double scalbnl (long double __x, int __n) ; extern long double __scalbnl (long double __x, int __n) ;



extern int ilogbl (long double __x) ; extern int __ilogbl (long double __x) ;
# 110 "/usr/include/math.h" 2 3
# 125 "/usr/include/math.h" 3
extern int signgam;
# 252 "/usr/include/math.h" 3
typedef enum
{
  _IEEE_ = -1,
  _SVID_,
  _XOPEN_,
  _POSIX_,
  _ISOC_
} _LIB_VERSION_TYPE;




extern _LIB_VERSION_TYPE _LIB_VERSION;
# 277 "/usr/include/math.h" 3
struct exception

  {
    int type;
    char *name;
    double arg1;
    double arg2;
    double retval;
  };




extern int matherr (struct exception *__exc);
# 362 "/usr/include/math.h" 3
# 1 "/usr/include/bits/mathinline.h" 1 3
# 291 "/usr/include/bits/mathinline.h" 3
extern __inline double __sgn (double) ; extern __inline double __sgn (double __x) { return __x == 0.0 ? 0.0 : (__x > 0.0 ? 1.0 : -1.0); } extern __inline float __sgnf (float) ; extern __inline float __sgnf (float __x) { return __x == 0.0 ? 0.0 : (__x > 0.0 ? 1.0 : -1.0); } extern __inline long double __sgnl (long double) ; extern __inline long double __sgnl (long double __x) { return __x == 0.0 ? 0.0 : (__x > 0.0 ? 1.0 : -1.0); }
# 426 "/usr/include/bits/mathinline.h" 3
extern __inline double atan2 (double __y, double __x) { register long double __value; __asm __volatile__ ("fpatan" : "=t" (__value) : "0" (__x), "u" (__y) : "st(1)"); return __value; } extern __inline float atan2f (float __y, float __x) { register long double __value; __asm __volatile__ ("fpatan" : "=t" (__value) : "0" (__x), "u" (__y) : "st(1)"); return __value; } extern __inline long double atan2l (long double __y, long double __x) { register long double __value; __asm __volatile__ ("fpatan" : "=t" (__value) : "0" (__x), "u" (__y) : "st(1)"); return __value; }
extern __inline long double __atan2l (long double __y, long double __x) { register long double __value; __asm __volatile__ ("fpatan" : "=t" (__value) : "0" (__x), "u" (__y) : "st(1)"); return __value; }


extern __inline double fmod (double __x, double __y) { register long double __value; __asm __volatile__ ("1:	fprem\n\t" "fnstsw	%%ax\n\t" "sahf\n\t" "jp	1b" : "=t" (__value) : "0" (__x), "u" (__y) : "ax", "cc"); return __value; } extern __inline float fmodf (float __x, float __y) { register long double __value; __asm __volatile__ ("1:	fprem\n\t" "fnstsw	%%ax\n\t" "sahf\n\t" "jp	1b" : "=t" (__value) : "0" (__x), "u" (__y) : "ax", "cc"); return __value; } extern __inline long double fmodl (long double __x, long double __y) { register long double __value; __asm __volatile__ ("1:	fprem\n\t" "fnstsw	%%ax\n\t" "sahf\n\t" "jp	1b" : "=t" (__value) : "0" (__x), "u" (__y) : "ax", "cc"); return __value; }
# 447 "/usr/include/bits/mathinline.h" 3
extern __inline double fabs (double __x) { return __builtin_fabs (__x); }
extern __inline float fabsf (float __x) { return __builtin_fabsf (__x); }
extern __inline long double fabsl (long double __x) { return __builtin_fabsl (__x); }
extern __inline long double __fabsl (long double __x) { return __builtin_fabsl (__x); }
# 469 "/usr/include/bits/mathinline.h" 3
extern __inline double atan (double __x) { register double __result; __asm __volatile__ ("fld1; fpatan" : "=t" (__result) : "0" (__x) : "st(1)"); return __result; } extern __inline float atanf (float __x) { register float __result; __asm __volatile__ ("fld1; fpatan" : "=t" (__result) : "0" (__x) : "st(1)"); return __result; } extern __inline long double atanl (long double __x) { register long double __result; __asm __volatile__ ("fld1; fpatan" : "=t" (__result) : "0" (__x) : "st(1)"); return __result; }

extern __inline long double __sgn1l (long double) ; extern __inline long double __sgn1l (long double __x) { __extension__ union { long double __xld; unsigned int __xi[3]; } __n = { __xld: __x }; __n.__xi[2] = (__n.__xi[2] & 0x8000) | 0x3fff; __n.__xi[1] = 0x80000000; __n.__xi[0] = 0; return __n.__xld; }
# 495 "/usr/include/bits/mathinline.h" 3
extern __inline double floor (double __x) { register long double __value; __volatile unsigned short int __cw; __volatile unsigned short int __cwtmp; __asm __volatile ("fnstcw %0" : "=m" (__cw)); __cwtmp = (__cw & 0xf3ff) | 0x0400; __asm __volatile ("fldcw %0" : : "m" (__cwtmp)); __asm __volatile ("frndint" : "=t" (__value) : "0" (__x)); __asm __volatile ("fldcw %0" : : "m" (__cw)); return __value; } extern __inline float floorf (float __x) { register long double __value; __volatile unsigned short int __cw; __volatile unsigned short int __cwtmp; __asm __volatile ("fnstcw %0" : "=m" (__cw)); __cwtmp = (__cw & 0xf3ff) | 0x0400; __asm __volatile ("fldcw %0" : : "m" (__cwtmp)); __asm __volatile ("frndint" : "=t" (__value) : "0" (__x)); __asm __volatile ("fldcw %0" : : "m" (__cw)); return __value; } extern __inline long double floorl (long double __x) { register long double __value; __volatile unsigned short int __cw; __volatile unsigned short int __cwtmp; __asm __volatile ("fnstcw %0" : "=m" (__cw)); __cwtmp = (__cw & 0xf3ff) | 0x0400; __asm __volatile ("fldcw %0" : : "m" (__cwtmp)); __asm __volatile ("frndint" : "=t" (__value) : "0" (__x)); __asm __volatile ("fldcw %0" : : "m" (__cw)); return __value; }
# 506 "/usr/include/bits/mathinline.h" 3
extern __inline double ceil (double __x) { register long double __value; __volatile unsigned short int __cw; __volatile unsigned short int __cwtmp; __asm __volatile ("fnstcw %0" : "=m" (__cw)); __cwtmp = (__cw & 0xf3ff) | 0x0800; __asm __volatile ("fldcw %0" : : "m" (__cwtmp)); __asm __volatile ("frndint" : "=t" (__value) : "0" (__x)); __asm __volatile ("fldcw %0" : : "m" (__cw)); return __value; } extern __inline float ceilf (float __x) { register long double __value; __volatile unsigned short int __cw; __volatile unsigned short int __cwtmp; __asm __volatile ("fnstcw %0" : "=m" (__cw)); __cwtmp = (__cw & 0xf3ff) | 0x0800; __asm __volatile ("fldcw %0" : : "m" (__cwtmp)); __asm __volatile ("frndint" : "=t" (__value) : "0" (__x)); __asm __volatile ("fldcw %0" : : "m" (__cw)); return __value; } extern __inline long double ceill (long double __x) { register long double __value; __volatile unsigned short int __cw; __volatile unsigned short int __cwtmp; __asm __volatile ("fnstcw %0" : "=m" (__cw)); __cwtmp = (__cw & 0xf3ff) | 0x0800; __asm __volatile ("fldcw %0" : : "m" (__cwtmp)); __asm __volatile ("frndint" : "=t" (__value) : "0" (__x)); __asm __volatile ("fldcw %0" : : "m" (__cw)); return __value; }
# 655 "/usr/include/bits/mathinline.h" 3
extern __inline double drem (double __x, double __y) { register double __value; register int __clobbered; __asm __volatile__ ("1:	fprem1\n\t" "fstsw	%%ax\n\t" "sahf\n\t" "jp	1b" : "=t" (__value), "=&a" (__clobbered) : "0" (__x), "u" (__y) : "cc"); return __value; } extern __inline float dremf (float __x, float __y) { register double __value; register int __clobbered; __asm __volatile__ ("1:	fprem1\n\t" "fstsw	%%ax\n\t" "sahf\n\t" "jp	1b" : "=t" (__value), "=&a" (__clobbered) : "0" (__x), "u" (__y) : "cc"); return __value; } extern __inline long double dreml (long double __x, long double __y) { register double __value; register int __clobbered; __asm __volatile__ ("1:	fprem1\n\t" "fstsw	%%ax\n\t" "sahf\n\t" "jp	1b" : "=t" (__value), "=&a" (__clobbered) : "0" (__x), "u" (__y) : "cc"); return __value; }
# 668 "/usr/include/bits/mathinline.h" 3
extern __inline int
__finite (double __x)
{
  return (__extension__
          (((((union { double __d; int __i[2]; }) {__d: __x}).__i[1]
             | 0x800fffffu) + 1) >> 31));
}
# 363 "/usr/include/math.h" 2 3
# 423 "/usr/include/math.h" 3

# 30 "bltMath.h" 2


# 1 "/usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/float.h" 1 3
# 33 "bltMath.h" 2
# 166 "bltMath.h"
extern double bltNaN;
# 186 "bltMath.h"
extern void strtolower (char *s);
# 111 "bltInt.h" 2
# 166 "bltInt.h"
extern void Blt_Assert (char *expr, char *file, int line);
# 176 "bltInt.h"
extern Tcl_Obj *bltEmptyStringObjPtr;
# 186 "bltInt.h"
typedef struct {
    char *name;
    Tcl_CmdProc *cmdProc;
    Tcl_CmdDeleteProc *cmdDeleteProc;
    ClientData clientData;
} Blt_CmdSpec;
# 201 "bltInt.h"
typedef struct {
    char *name;
    Tcl_ObjCmdProc *cmdProc;
    Tcl_CmdDeleteProc *cmdDeleteProc;
    ClientData clientData;
} Blt_ObjCmdSpec;
# 219 "bltInt.h"
typedef int (*Blt_Op) ();
# 232 "bltInt.h"
typedef struct {
    char *name;
    int minChars;
    Blt_Op proc;
    int minArgs;
    int maxArgs;
    char *usage;

} Blt_OpSpec;

typedef enum {
    BLT_OP_ARG0,
    BLT_OP_ARG1,
    BLT_OP_ARG2,
    BLT_OP_ARG3,
    BLT_OP_ARG4

} Blt_OpIndex;




extern Blt_Op Blt_GetOp (Tcl_Interp *interp, int nSpecs, Blt_OpSpec *specArr, int operPos, int argc, char **argv, int flags);



extern Blt_Op Blt_GetOpFromObj (Tcl_Interp *interp, int nSpecs, Blt_OpSpec *specArr, int operPos, int objc, Tcl_Obj *const *objv, int flags);
# 276 "bltInt.h"
extern int Blt_DictionaryCompare (char *s1, char *s2);

extern void Blt_Panic (char * args, ...);


extern void Blt_Draw3DRectangle (Tk_Window tkwin, Drawable drawable, Tk_3DBorder border, int x, int y, int width, int height, int borderWidth, int relief);


extern void Blt_Fill3DRectangle (Tk_Window tkwin, Drawable drawable, Tk_3DBorder border, int x, int y, int width, int height, int borderWidth, int relief);
# 373 "bltInt.h"
extern FILE *Blt_OpenUtfFile (char *fileName, char *mode);





typedef char *DestroyData;
# 436 "bltInt.h"
typedef int (QSortCompareProc) (const void *, const void *);
# 457 "bltInt.h"
typedef struct {
    short int side1, side2;
} Blt_Pad;
# 492 "bltInt.h"
typedef struct {
    unsigned char values[12];
    int offset;
} Blt_Dashes;



extern void Blt_SetDashes (Display *display, GC gc, Blt_Dashes *dashesPtr);

extern Blt_Dashes *Blt_GetDashes (GC gc);
# 512 "bltInt.h"
typedef struct {
    double x, y;
} Point2D;
# 525 "bltInt.h"
typedef struct {
    double x, y, z;
} Point3D;
# 538 "bltInt.h"
typedef struct {
    Point2D p, q;
} Segment2D;
# 551 "bltInt.h"
typedef struct {
    short int width, height;
} Dim2D;
# 564 "bltInt.h"
typedef struct {
    int left, right, top, bottom;
} Region2D;




typedef struct {
    double left, right, top, bottom;
} Extents2D;

typedef struct {
    double left, right, top, bottom, front, back;
} Extents3D;
# 596 "bltInt.h"
typedef struct {
    XColor *fgColor, *bgColor;
} ColorPair;





extern int Blt_GetColorPair (Tcl_Interp *interp, Tk_Window tkwin, char *fgColor, char *bgColor, ColorPair *pairPtr, int colorFlag);

extern void Blt_FreeColorPair (ColorPair *pairPtr);
# 622 "bltInt.h"
# 1 "bltText.h" 1
# 95 "bltText.h"
typedef struct {
    char *text;

    short int x, y;


    short int sx, sy;

    short int count;



    short int width;



} TextFragment;
# 120 "bltText.h"
typedef struct {
    int nFrags;
    short int width, height;
    TextFragment fragArr[1];
} TextLayout;

typedef struct {
    XColor *color;
    int offset;
} Shadow;
# 145 "bltText.h"
typedef struct {
    unsigned int state;

    short int width, height;

    XColor *color;
    XColor *activeColor;
    Tk_Font font;
    Tk_3DBorder border;

    Shadow shadow;
    Tk_Justify justify;


    GC gc;
    double theta;
    Tk_Anchor anchor;

    Blt_Pad padX, padY;
    short int leader;

} TextStyle;


extern TextLayout *Blt_GetTextLayout (char *string, TextStyle *stylePtr);


extern void Blt_GetTextExtents (TextStyle *stylePtr, char *text, int *widthPtr, int *heightPtr);


extern void Blt_InitTextStyle (TextStyle *stylePtr);

extern void Blt_ResetTextStyle (Tk_Window tkwin, TextStyle *stylePtr);


extern void Blt_FreeTextStyle (Display *display, TextStyle *stylePtr);


extern void Blt_SetDrawTextStyle (TextStyle *stylePtr, Tk_Font font, GC gc, XColor *normalColor, XColor *activeColor, XColor *shadowColor, double theta, Tk_Anchor anchor, Tk_Justify justify, int leader, int shadowOffset);




extern void Blt_SetPrintTextStyle (TextStyle *stylePtr, Tk_Font font, XColor *fgColor, XColor *bgColor, XColor *shadowColor, double theta, Tk_Anchor anchor, Tk_Justify justify, int leader, int shadowOffset);




extern void Blt_DrawText (Tk_Window tkwin, Drawable drawable, char *string, TextStyle *stylePtr, int x, int y);


extern void Blt_DrawTextLayout (Tk_Window tkwin, Drawable drawable, TextLayout *textPtr, TextStyle *stylePtr, int x, int y);



extern void Blt_DrawText2 (Tk_Window tkwin, Drawable drawable, char *string, TextStyle *stylePtr, int x, int y, Dim2D * dimPtr);



extern Pixmap Blt_CreateTextBitmap (Tk_Window tkwin, TextLayout *textPtr, TextStyle *stylePtr, int *widthPtr, int *heightPtr);



extern int Blt_DrawRotatedText (Display *display, Drawable drawable, int x, int y, double theta, TextStyle *stylePtr, TextLayout *textPtr);
# 623 "bltInt.h" 2
# 638 "bltInt.h"
extern char *Blt_Itoa (int value);
extern char *Blt_Utoa (unsigned int value);
extern char *Blt_Dtoa (Tcl_Interp *interp, double value);
extern Tcl_Command Blt_InitCmd (Tcl_Interp *interp, char *namespace, Blt_CmdSpec *specPtr);



extern Tcl_Command Blt_InitObjCmd (Tcl_Interp *interp, char *namespace, Blt_ObjCmdSpec *specPtr);
# 660 "bltInt.h"
extern int Blt_InitCmds (Tcl_Interp *interp, char *namespace, Blt_CmdSpec *specPtr, int nCmds);


extern int Blt_NaturalSpline (Point2D *origPts, int nOrigPts, Point2D *intpPts, int nIntpPts);


extern int Blt_QuadraticSpline (Point2D *origPts, int nOrigPts, Point2D *intpPts, int nIntpPts);


extern int Blt_SimplifyLine (Point2D *origPts, int low, int high, double tolerance, int indices[]);


extern int Blt_NaturalParametricSpline (Point2D *origPts, int nOrigPts, Extents2D *extsPtr, int isClosed, Point2D *intpPts, int nIntpPts);



extern int Blt_CatromParametricSpline (Point2D *origPts, int nOrigPts, Point2D *intpPts, int nIntpPts);


extern int Blt_StringToFlag (ClientData clientData, Tcl_Interp *interp, Tk_Window tkwin, char *string, char *widgRec, int flags);


extern char *Blt_FlagToString (ClientData clientData, Tk_Window tkwin, char *string, int offset, Tcl_FreeProc **freeProc);


extern void Blt_InitHexTable (char *table);

extern GC Blt_GetPrivateGC (Tk_Window tkwin, unsigned long gcMask, XGCValues *valuePtr);


extern GC Blt_GetPrivateGCFromDrawable (Display *display, Drawable drawable, unsigned long gcMask, XGCValues *valuePtr);


extern void Blt_FreePrivateGC (Display *display, GC gc);

extern Tk_Window Blt_FindChild (Tk_Window parent, char *name);

extern Tk_Window Blt_FirstChild (Tk_Window parent);

extern Tk_Window Blt_NextChild (Tk_Window tkwin);

extern void Blt_RelinkWindow (Tk_Window tkwin, Tk_Window newParent, int x, int y);


extern Tk_Window Blt_Toplevel (Tk_Window tkwin);

extern int Blt_GetPixels (Tcl_Interp *interp, Tk_Window tkwin, char *string, int check, int *valuePtr);

extern int Blt_GetPosition (Tcl_Interp *interp, char *string, int *indexPtr);

extern int Blt_GetCount (Tcl_Interp *interp, char *string, int check, int *valuePtr);


extern char *Blt_NameOfFill (int fill);

extern int Blt_GetXY (Tcl_Interp *interp, Tk_Window tkwin, char *string, int *x, int *y);


extern Point2D Blt_GetProjection (int x, int y, Point2D *p, Point2D *q);


extern void Blt_DrawArrow (Display *display, Drawable drawable, GC gc, int x, int y, int arrowHeight, int orientation);


extern Tk_OptionParseProc Blt_StringToEnum;
extern Tk_OptionPrintProc Blt_EnumToString;

extern int Blt_ConfigModified (Tk_ConfigSpec * specs, ...);

extern void Blt_DStringAppendElements (Tcl_DString * args, ...);

extern void Blt_MakeTransparentWindowExist (Tk_Window tkwin, Window parent, int isBusy);


extern Window Blt_GetParent (Display *display, Window tkwin);

extern void Blt_GetBoundingBox (int width, int height, double theta, double *widthPtr, double *heightPtr, Point2D *points);


extern void Blt_InitEpsCanvasItem (Tcl_Interp *interp);

extern void Blt_TranslateAnchor (int x, int y, int width, int height, Tk_Anchor anchor, int *transXPtr, int *transYPtr);


extern Point2D Blt_TranslatePoint (Point2D *pointPtr, int width, int height, Tk_Anchor anchor);


extern int Blt_ConfigureWidgetComponent (Tcl_Interp *interp, Tk_Window tkwin, char *name, char *class, Tk_ConfigSpec *specs, int argc, char **argv, char *widgRec, int flags);



extern void Blt_HSV (XColor *colorPtr, double *huePtr, double *valPtr, double *satPtr);


extern void Blt_RGB (double hue, double sat, double val, XColor *colorPtr);


extern int Blt_ParseFlag (ClientData, Tcl_Interp *, Tk_Window, char *, char *, int);

extern char *Blt_FlagPrint (ClientData, Tk_Window, char *, int, Tcl_FreeProc **);


extern int Blt_MaxRequestSize (Display *display, unsigned int elemSize);


extern Window Blt_GetRealWindowId (Tk_Window tkwin);
extern int Blt_RootX (Tk_Window tkwin);
extern int Blt_RootY (Tk_Window tkwin);
extern void Blt_RootCoordinates (Tk_Window tkwin, int x, int y, int *rootXPtr, int *rootYPtr);

extern void Blt_MapToplevel (Tk_Window tkwin);
extern void Blt_UnmapToplevel (Tk_Window tkwin);
extern void Blt_RaiseToplevel (Tk_Window tkwin);
extern void Blt_LowerToplevel (Tk_Window tkwin);
extern void Blt_ResizeToplevel (Tk_Window tkwin, int width, int height);

extern void Blt_MoveToplevel (Tk_Window tkwin, int x, int y);
extern void Blt_MoveResizeToplevel (Tk_Window tkwin, int x, int y, int width, int height);

extern ClientData Blt_GetWindowInstanceData (Tk_Window tkwin);

extern void Blt_SetWindowInstanceData (Tk_Window tkwin, ClientData instanceData);


extern void Blt_DeleteWindowInstanceData (Tk_Window tkwin);

extern int Blt_AdjustViewport (int offset, int worldSize, int windowSize, int scrollUnits, int scrollMode);


extern int Blt_GetScrollInfo (Tcl_Interp *interp, int argc, char **argv, int *offsetPtr, int worldSize, int windowSize, int scrollUnits, int scrollMode);




extern int Blt_GetScrollInfoFromObj (Tcl_Interp *interp, int objc, Tcl_Obj *const *objv, int *offsetPtr, int worldSize, int windowSize, int scrollUnits, int scrollMode);




extern void Blt_UpdateScrollbar (Tcl_Interp *interp, char *scrollCmd, double firstFract, double lastFract);


extern int Blt_ReparentWindow (Display *display, Window window, Window newParent, int x, int y);
# 840 "bltInt.h"
extern Tcl_AppInitProc Blt_BeepInit;


extern Tcl_AppInitProc Blt_BgexecInit;


extern Tcl_AppInitProc Blt_BitmapInit;


extern Tcl_AppInitProc Blt_BusyInit;


extern Tcl_AppInitProc Blt_ContainerInit;


extern Tcl_AppInitProc Blt_Crc32Init;


extern Tcl_AppInitProc Blt_CutbufferInit;


extern Tcl_AppInitProc Blt_DebugInit;


extern Tcl_AppInitProc Blt_DragDropInit;


extern Tcl_AppInitProc Blt_DndInit;


extern Tcl_AppInitProc Blt_GraphInit;


extern Tcl_AppInitProc Blt_HierboxInit;


extern Tcl_AppInitProc Blt_HiertableInit;


extern Tcl_AppInitProc Blt_HtextInit;







extern Tcl_AppInitProc Blt_TableInit;


extern Tcl_AppInitProc Blt_VectorInit;


extern Tcl_AppInitProc Blt_WinopInit;


extern Tcl_AppInitProc Blt_WatchInit;


extern Tcl_AppInitProc Blt_SplineInit;


extern Tcl_AppInitProc Blt_TabsetInit;


extern Tcl_AppInitProc Blt_TabnotebookInit;


extern Tcl_AppInitProc Blt_TreeInit;


extern Tcl_AppInitProc Blt_TreeViewInit;


extern Tcl_AppInitProc Blt_FrameInit;


extern Tcl_AppInitProc Blt_ButtonInit;


extern Tcl_AppInitProc Blt_ScrollbarInit;
# 929 "bltInt.h"
extern Tcl_AppInitProc Blt_TedInit;






typedef void *(Blt_MallocProc) (size_t size);
typedef void *(Blt_CallocProc) (int nElem, size_t size);
typedef void *(Blt_ReallocProc) (void *ptr, size_t size);
typedef void (Blt_FreeProc) (void *ptr);

extern Blt_MallocProc *Blt_MallocProcPtr;
extern Blt_FreeProc *Blt_FreeProcPtr;
extern Blt_ReallocProc *Blt_ReallocProcPtr;





extern char *Blt_Strdup (const char *ptr);
extern void *Blt_Calloc (unsigned int nElem, size_t size);
# 30 "bltWindow.c" 2



# 1 "/usr/X11R6/include/X11/Xproto.h" 1
# 76 "/usr/X11R6/include/X11/Xproto.h"
# 1 "/usr/X11R6/include/X11/Xmd.h" 1
# 135 "/usr/X11R6/include/X11/Xmd.h"
typedef long INT32;

typedef short INT16;



typedef signed char INT8;
# 150 "/usr/X11R6/include/X11/Xmd.h"
typedef unsigned long CARD32;

typedef unsigned short CARD16;
typedef unsigned char CARD8;

typedef CARD32 BITS32;
typedef CARD16 BITS16;


typedef CARD8 BYTE;
typedef CARD8 BOOL;
# 77 "/usr/X11R6/include/X11/Xproto.h" 2
# 1 "/usr/X11R6/include/X11/Xprotostr.h" 1
# 55 "/usr/X11R6/include/X11/Xprotostr.h"
typedef struct _xSegment {
    INT16 x1 , y1 , x2 , y2 ;
} xSegment;



typedef struct _xPoint {
        INT16 x , y ;
} xPoint;

typedef struct _xRectangle {
    INT16 x , y ;
    CARD16 width , height ;
} xRectangle;



typedef struct _xArc {
    INT16 x , y ;
    CARD16 width , height ;
    INT16 angle1 , angle2 ;
} xArc;
# 78 "/usr/X11R6/include/X11/Xproto.h" 2
# 263 "/usr/X11R6/include/X11/Xproto.h"
typedef CARD16 KeyButMask;






typedef struct {
    CARD8 byteOrder;
    BYTE pad;
    CARD16 majorVersion , minorVersion ;
    CARD16 nbytesAuthProto ;
    CARD16 nbytesAuthString ;
    CARD16 pad2 ;
} xConnClientPrefix;

typedef struct {
    CARD8 success;
    BYTE lengthReason;
    CARD16 majorVersion ,
                   minorVersion ;
    CARD16 length ;
} xConnSetupPrefix;


typedef struct {
    CARD32 release ;
    CARD32 ridBase ,
                   ridMask ;
    CARD32 motionBufferSize ;
    CARD16 nbytesVendor ;
    CARD16 maxRequestSize ;
    CARD8 numRoots;
    CARD8 numFormats;
    CARD8 imageByteOrder;
    CARD8 bitmapBitOrder;
    CARD8 bitmapScanlineUnit,
                   bitmapScanlinePad;
    CARD8 minKeyCode, maxKeyCode;
    CARD32 pad2 ;
} xConnSetup;

typedef struct {
    CARD8 depth;
    CARD8 bitsPerPixel;
    CARD8 scanLinePad;
    CARD8 pad1;
    CARD32 pad2 ;
} xPixmapFormat;



typedef struct {
    CARD8 depth;
    CARD8 pad1;
    CARD16 nVisuals ;
    CARD32 pad2 ;
    } xDepth;

typedef struct {
    CARD32 visualID ;



    CARD8 class;

    CARD8 bitsPerRGB;
    CARD16 colormapEntries ;
    CARD32 redMask , greenMask , blueMask ;
    CARD32 pad ;
    } xVisualType;

typedef struct {
    CARD32 windowId ;
    CARD32 defaultColormap ;
    CARD32 whitePixel , blackPixel ;
    CARD32 currentInputMask ;
    CARD16 pixWidth , pixHeight ;
    CARD16 mmWidth , mmHeight ;
    CARD16 minInstalledMaps , maxInstalledMaps ;
    CARD32 rootVisualID ;
    CARD8 backingStore;
    BOOL saveUnders;
    CARD8 rootDepth;
    CARD8 nDepths;
} xWindowRoot;
# 358 "/usr/X11R6/include/X11/Xproto.h"
typedef struct {
    CARD32 time ;
    INT16 x , y ;
} xTimecoord;

typedef struct {
    CARD8 family;
    BYTE pad;
    CARD16 length ;
} xHostEntry;

typedef struct {
    INT16 leftSideBearing ,
          rightSideBearing ,
          characterWidth ,
          ascent ,
          descent ;
    CARD16 attributes ;
} xCharInfo;

typedef struct {
    CARD32 name ;
    CARD32 value ;
} xFontProp;




typedef struct {
    CARD8 len;

    INT8 delta;
} xTextElt;


typedef struct {
    CARD32 pixel ;
    CARD16 red , green , blue ;
    CARD8 flags;
    CARD8 pad;
} xColorItem;


typedef struct {
    CARD16 red , green , blue , pad ;
} xrgb;

typedef CARD8 KEYCODE;
# 416 "/usr/X11R6/include/X11/Xproto.h"
typedef struct {
    BYTE type;
    BYTE data1;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD32 data00 ;
    CARD32 data01 ;
    CARD32 data02 ;
    CARD32 data03 ;
    CARD32 data04 ;
    CARD32 data05 ;
    } xGenericReply;



typedef struct {
    BYTE type;
    CARD8 backingStore;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD32 visualID ;



    CARD16 class ;

    CARD8 bitGravity;
    CARD8 winGravity;
    CARD32 backingBitPlanes ;
    CARD32 backingPixel ;
    BOOL saveUnder;
    BOOL mapInstalled;
    CARD8 mapState;
    BOOL override;
    CARD32 colormap ;
    CARD32 allEventMasks ;
    CARD32 yourEventMask ;
    CARD16 doNotPropagateMask ;
    CARD16 pad ;
    } xGetWindowAttributesReply;

typedef struct {
    BYTE type;
    CARD8 depth;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD32 root ;
    INT16 x , y ;
    CARD16 width , height ;
    CARD16 borderWidth ;
    CARD16 pad1 ;
    CARD32 pad2 ;
    CARD32 pad3 ;
    } xGetGeometryReply;

typedef struct {
    BYTE type;
    BYTE pad1;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD32 root , parent ;
    CARD16 nChildren ;
    CARD16 pad2 ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    } xQueryTreeReply;

typedef struct {
    BYTE type;
    BYTE pad1;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD32 atom ;
    CARD32 pad2 ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
    } xInternAtomReply;

typedef struct {
    BYTE type;
    BYTE pad1;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD16 nameLength ;
    CARD16 pad2 ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
    CARD32 pad7 ;
    } xGetAtomNameReply;

typedef struct {
    BYTE type;
    CARD8 format;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD32 propertyType ;
    CARD32 bytesAfter ;
    CARD32 nItems ;
    CARD32 pad1 ;
    CARD32 pad2 ;
    CARD32 pad3 ;
    } xGetPropertyReply;

typedef struct {
    BYTE type;
    BYTE pad1;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD16 nProperties ;
    CARD16 pad2 ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
    CARD32 pad7 ;
    } xListPropertiesReply;

typedef struct {
    BYTE type;
    BYTE pad1;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD32 owner ;
    CARD32 pad2 ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
    } xGetSelectionOwnerReply;

typedef struct {
    BYTE type;
    BYTE status;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD32 pad1 ;
    CARD32 pad2 ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
    } xGrabPointerReply;

typedef xGrabPointerReply xGrabKeyboardReply;

typedef struct {
    BYTE type;
    BOOL sameScreen;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD32 root , child ;
    INT16 rootX , rootY , winX , winY ;
    CARD16 mask ;
    CARD16 pad1 ;
    CARD32 pad ;
    } xQueryPointerReply;

typedef struct {
    BYTE type;
    BYTE pad1;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD32 nEvents ;
    CARD32 pad2 ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
    } xGetMotionEventsReply;

typedef struct {
    BYTE type;
    BOOL sameScreen;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD32 child ;
    INT16 dstX , dstY ;
    CARD32 pad2 ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    } xTranslateCoordsReply;

typedef struct {
    BYTE type;
    CARD8 revertTo;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD32 focus ;
    CARD32 pad1 ;
    CARD32 pad2 ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    } xGetInputFocusReply;

typedef struct {
    BYTE type;
    BYTE pad1;
    CARD16 sequenceNumber ;
    CARD32 length ;
    BYTE map[32];
    } xQueryKeymapReply;


typedef struct _xQueryFontReply {
    BYTE type;
    BYTE pad1;
    CARD16 sequenceNumber ;
    CARD32 length ;
    xCharInfo minBounds;

    CARD32 walign1 ;

    xCharInfo maxBounds;

    CARD32 walign2 ;

    CARD16 minCharOrByte2 , maxCharOrByte2 ;
    CARD16 defaultChar ;
    CARD16 nFontProps ;
    CARD8 drawDirection;
    CARD8 minByte1, maxByte1;
    BOOL allCharsExist;
    INT16 fontAscent , fontDescent ;
    CARD32 nCharInfos ;
} xQueryFontReply;

typedef struct {
    BYTE type;
    CARD8 drawDirection;
    CARD16 sequenceNumber ;
    CARD32 length ;
    INT16 fontAscent , fontDescent ;
    INT16 overallAscent , overallDescent ;
    INT32 overallWidth , overallLeft , overallRight ;
    CARD32 pad ;
    } xQueryTextExtentsReply;

typedef struct {
    BYTE type;
    BYTE pad1;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD16 nFonts ;
    CARD16 pad2 ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
    CARD32 pad7 ;
    } xListFontsReply;


typedef struct {
    BYTE type;
    CARD8 nameLength;
    CARD16 sequenceNumber ;
    CARD32 length ;
    xCharInfo minBounds;

    CARD32 walign1 ;

    xCharInfo maxBounds;

    CARD32 walign2 ;

    CARD16 minCharOrByte2 , maxCharOrByte2 ;
    CARD16 defaultChar ;
    CARD16 nFontProps ;
    CARD8 drawDirection;
    CARD8 minByte1, maxByte1;
    BOOL allCharsExist;
    INT16 fontAscent , fontDescent ;
    CARD32 nReplies ;
} xListFontsWithInfoReply;

typedef struct {
    BYTE type;
    BYTE pad1;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD16 nPaths ;
    CARD16 pad2 ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
    CARD32 pad7 ;
    } xGetFontPathReply;

typedef struct {
    BYTE type;
    CARD8 depth;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD32 visual ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
    CARD32 pad7 ;
    } xGetImageReply;

typedef struct {
    BYTE type;
    BYTE pad1;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD16 nColormaps ;
    CARD16 pad2 ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
    CARD32 pad7 ;
    } xListInstalledColormapsReply;

typedef struct {
    BYTE type;
    BYTE pad1;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD16 red , green , blue ;
    CARD16 pad2 ;
    CARD32 pixel ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    } xAllocColorReply;

typedef struct {
    BYTE type;
    BYTE pad1;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD32 pixel ;
    CARD16 exactRed , exactGreen , exactBlue ;
    CARD16 screenRed , screenGreen , screenBlue ;
    CARD32 pad2 ;
    CARD32 pad3 ;
    } xAllocNamedColorReply;

typedef struct {
    BYTE type;
    BYTE pad1;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD16 nPixels , nMasks ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
    CARD32 pad7 ;
    } xAllocColorCellsReply;

typedef struct {
    BYTE type;
    BYTE pad1;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD16 nPixels ;
    CARD16 pad2 ;
    CARD32 redMask , greenMask , blueMask ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    } xAllocColorPlanesReply;

typedef struct {
    BYTE type;
    BYTE pad1;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD16 nColors ;
    CARD16 pad2 ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
    CARD32 pad7 ;
    } xQueryColorsReply;

typedef struct {
    BYTE type;
    BYTE pad1;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD16 exactRed , exactGreen , exactBlue ;
    CARD16 screenRed , screenGreen , screenBlue ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    } xLookupColorReply;

typedef struct {
    BYTE type;
    BYTE pad1;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD16 width , height ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
    CARD32 pad7 ;
    } xQueryBestSizeReply;

typedef struct {
    BYTE type;
    BYTE pad1;
    CARD16 sequenceNumber ;
    CARD32 length ;
    BOOL present;
    CARD8 major_opcode;
    CARD8 first_event;
    CARD8 first_error;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
    CARD32 pad7 ;
    } xQueryExtensionReply;

typedef struct {
    BYTE type;
    CARD8 nExtensions;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD32 pad2 ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
    CARD32 pad7 ;
    } xListExtensionsReply;


typedef struct {
    BYTE type;
    CARD8 success;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD32 pad2 ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
    CARD32 pad7 ;
    } xSetMappingReply;
typedef xSetMappingReply xSetPointerMappingReply;
typedef xSetMappingReply xSetModifierMappingReply;

typedef struct {
    BYTE type;
    CARD8 nElts;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD32 pad2 ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
    CARD32 pad7 ;
    } xGetPointerMappingReply;

typedef struct {
    BYTE type;
    CARD8 keySymsPerKeyCode;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD32 pad2 ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
    CARD32 pad7 ;
} xGetKeyboardMappingReply;

typedef struct {
    BYTE type;
    CARD8 numKeyPerModifier;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD32 pad1 ;
    CARD32 pad2 ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
} xGetModifierMappingReply;

typedef struct {
    BYTE type;
    BOOL globalAutoRepeat;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD32 ledMask ;
    CARD8 keyClickPercent, bellPercent;
    CARD16 bellPitch , bellDuration ;
    CARD16 pad ;
    BYTE map[32];
    } xGetKeyboardControlReply;

typedef struct {
    BYTE type;
    BYTE pad1;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD16 accelNumerator , accelDenominator ;
    CARD16 threshold ;
    CARD16 pad2 ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
    } xGetPointerControlReply;

typedef struct {
    BYTE type;
    BYTE pad1;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD16 timeout , interval ;
    BOOL preferBlanking;
    BOOL allowExposures;
    CARD16 pad2 ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
    } xGetScreenSaverReply;

typedef struct {
    BYTE type;
    BOOL enabled;
    CARD16 sequenceNumber ;
    CARD32 length ;
    CARD16 nHosts ;
    CARD16 pad1 ;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
    CARD32 pad7 ;
    } xListHostsReply;
# 975 "/usr/X11R6/include/X11/Xproto.h"
typedef struct {
    BYTE type;
    BYTE errorCode;
    CARD16 sequenceNumber ;
    CARD32 resourceID ;
    CARD16 minorCode ;
    CARD8 majorCode;
    BYTE pad1;
    CARD32 pad3 ;
    CARD32 pad4 ;
    CARD32 pad5 ;
    CARD32 pad6 ;
    CARD32 pad7 ;
} xError;






typedef struct _xEvent {
    union {
        struct {
            BYTE type;
            BYTE detail;
            CARD16 sequenceNumber ;
            } u;
        struct {
            CARD32 pad00 ;
            CARD32 time ;
            CARD32 root , event , child ;
            INT16 rootX , rootY , eventX , eventY ;
            KeyButMask state ;
            BOOL sameScreen;
            BYTE pad1;
        } keyButtonPointer;
        struct {
            CARD32 pad00 ;
            CARD32 time ;
            CARD32 root , event , child ;
            INT16 rootX , rootY , eventX , eventY ;
            KeyButMask state ;
            BYTE mode;
            BYTE flags;


        } enterLeave;
        struct {
            CARD32 pad00 ;
            CARD32 window ;
            BYTE mode;
            BYTE pad1, pad2, pad3;
        } focus;
        struct {
            CARD32 pad00 ;
            CARD32 window ;
            CARD16 x , y , width , height ;
            CARD16 count ;
            CARD16 pad2 ;
        } expose;
        struct {
            CARD32 pad00 ;
            CARD32 drawable ;
            CARD16 x , y , width , height ;
            CARD16 minorEvent ;
            CARD16 count ;
            BYTE majorEvent;
            BYTE pad1, pad2, pad3;
        } graphicsExposure;
        struct {
            CARD32 pad00 ;
            CARD32 drawable ;
            CARD16 minorEvent ;
            BYTE majorEvent;
            BYTE bpad;
        } noExposure;
        struct {
            CARD32 pad00 ;
            CARD32 window ;
            CARD8 state;
            BYTE pad1, pad2, pad3;
        } visibility;
        struct {
            CARD32 pad00 ;
            CARD32 parent , window ;
            INT16 x , y ;
            CARD16 width , height , borderWidth ;
            BOOL override;
            BYTE bpad;
        } createNotify;
# 1073 "/usr/X11R6/include/X11/Xproto.h"
        struct {
            CARD32 pad00 ;
            CARD32 event , window ;
        } destroyNotify;
        struct {
            CARD32 pad00 ;
            CARD32 event , window ;
            BOOL fromConfigure;
            BYTE pad1, pad2, pad3;
        } unmapNotify;
        struct {
            CARD32 pad00 ;
            CARD32 event , window ;
            BOOL override;
            BYTE pad1, pad2, pad3;
        } mapNotify;
        struct {
            CARD32 pad00 ;
            CARD32 parent , window ;
        } mapRequest;
        struct {
            CARD32 pad00 ;
            CARD32 event , window , parent ;
            INT16 x , y ;
            BOOL override;
            BYTE pad1, pad2, pad3;
        } reparent;
        struct {
            CARD32 pad00 ;
            CARD32 event , window , aboveSibling ;
            INT16 x , y ;
            CARD16 width , height , borderWidth ;
            BOOL override;
            BYTE bpad;
        } configureNotify;
        struct {
            CARD32 pad00 ;
            CARD32 parent , window , sibling ;
            INT16 x , y ;
            CARD16 width , height , borderWidth ;
            CARD16 valueMask ;
            CARD32 pad1 ;
        } configureRequest;
        struct {
            CARD32 pad00 ;
            CARD32 event , window ;
            INT16 x , y ;
            CARD32 pad1 , pad2 , pad3 , pad4 ;
        } gravity;
        struct {
            CARD32 pad00 ;
            CARD32 window ;
            CARD16 width , height ;
        } resizeRequest;
        struct {


            CARD32 pad00 ;
            CARD32 event , window , parent ;
            BYTE place;
            BYTE pad1, pad2, pad3;
        } circulate;
        struct {
            CARD32 pad00 ;
            CARD32 window ;
            CARD32 atom ;
            CARD32 time ;
            BYTE state;
            BYTE pad1;
            CARD16 pad2 ;
        } property;
        struct {
            CARD32 pad00 ;
            CARD32 time ;
            CARD32 window ;
            CARD32 atom ;
        } selectionClear;
        struct {
            CARD32 pad00 ;
            CARD32 time ;
            CARD32 owner , requestor ;
            CARD32 selection , target , property ;
        } selectionRequest;
        struct {
            CARD32 pad00 ;
            CARD32 time ;
            CARD32 requestor ;
            CARD32 selection , target , property ;
        } selectionNotify;
        struct {
            CARD32 pad00 ;
            CARD32 window ;
            CARD32 colormap ;



            BOOL new;

            BYTE state;
            BYTE pad1, pad2;
        } colormap;
        struct {
            CARD32 pad00 ;
            CARD8 request;
            CARD8 firstKeyCode;
            CARD8 count;
            BYTE pad1;
        } mappingNotify;
        struct {
            CARD32 pad00 ;
            CARD32 window ;
            union {
                struct {
                    CARD32 type ;
                    INT32 longs0 ;
                    INT32 longs1 ;
                    INT32 longs2 ;
                    INT32 longs3 ;
                    INT32 longs4 ;
                } l;
                struct {
                    CARD32 type ;
                    INT16 shorts0 ;
                    INT16 shorts1 ;
                    INT16 shorts2 ;
                    INT16 shorts3 ;
                    INT16 shorts4 ;
                    INT16 shorts5 ;
                    INT16 shorts6 ;
                    INT16 shorts7 ;
                    INT16 shorts8 ;
                    INT16 shorts9 ;
                } s;
                struct {
                    CARD32 type ;
                    INT8 bytes[20];
                } b;
            } u;
        } clientMessage;
    } u;
} xEvent;





typedef struct {
    BYTE type;
    BYTE map[31];
    } xKeymapEvent;
# 1231 "/usr/X11R6/include/X11/Xproto.h"
typedef union {
    xGenericReply generic;
    xGetGeometryReply geom;
    xQueryTreeReply tree;
    xInternAtomReply atom;
    xGetAtomNameReply atomName;
    xGetPropertyReply property;
    xListPropertiesReply listProperties;
    xGetSelectionOwnerReply selection;
    xGrabPointerReply grabPointer;
    xGrabKeyboardReply grabKeyboard;
    xQueryPointerReply pointer;
    xGetMotionEventsReply motionEvents;
    xTranslateCoordsReply coords;
    xGetInputFocusReply inputFocus;
    xQueryTextExtentsReply textExtents;
    xListFontsReply fonts;
    xGetFontPathReply fontPath;
    xGetImageReply image;
    xListInstalledColormapsReply colormaps;
    xAllocColorReply allocColor;
    xAllocNamedColorReply allocNamedColor;
    xAllocColorCellsReply colorCells;
    xAllocColorPlanesReply colorPlanes;
    xQueryColorsReply colors;
    xLookupColorReply lookupColor;
    xQueryBestSizeReply bestSize;
    xQueryExtensionReply extension;
    xListExtensionsReply extensions;
    xSetModifierMappingReply setModifierMapping;
    xGetModifierMappingReply getModifierMapping;
    xSetPointerMappingReply setPointerMapping;
    xGetKeyboardMappingReply getKeyboardMapping;
    xGetPointerMappingReply getPointerMapping;
    xGetPointerControlReply pointerControl;
    xGetScreenSaverReply screenSaver;
    xListHostsReply hosts;
    xError error;
    xEvent event;
} xReply;
# 1281 "/usr/X11R6/include/X11/Xproto.h"
typedef struct _xReq {
        CARD8 reqType;
        CARD8 data;
        CARD16 length ;

} xReq;
# 1295 "/usr/X11R6/include/X11/Xproto.h"
typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 id ;
    } xResourceReq;

typedef struct {
    CARD8 reqType;
    CARD8 depth;
    CARD16 length ;
    CARD32 wid , parent ;
    INT16 x , y ;
    CARD16 width , height , borderWidth ;



    CARD16 class ;

    CARD32 visual ;
    CARD32 mask ;
} xCreateWindowReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 window ;
    CARD32 valueMask ;
} xChangeWindowAttributesReq;

typedef struct {
    CARD8 reqType;
    BYTE mode;
    CARD16 length ;
    CARD32 window ;
} xChangeSaveSetReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 window , parent ;
    INT16 x , y ;
} xReparentWindowReq;

typedef struct {
    CARD8 reqType;
    CARD8 pad;
    CARD16 length ;
    CARD32 window ;
    CARD16 mask ;
    CARD16 pad2 ;
} xConfigureWindowReq;

typedef struct {
    CARD8 reqType;
    CARD8 direction;
    CARD16 length ;
    CARD32 window ;
} xCirculateWindowReq;

typedef struct {
    CARD8 reqType;
    BOOL onlyIfExists;
    CARD16 length ;
    CARD16 nbytes ;
    CARD16 pad ;
} xInternAtomReq;

typedef struct {
    CARD8 reqType;
    CARD8 mode;
    CARD16 length ;
    CARD32 window ;
    CARD32 property , type ;
    CARD8 format;
    BYTE pad[3];
    CARD32 nUnits ;
} xChangePropertyReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 window ;
    CARD32 property ;
} xDeletePropertyReq;

typedef struct {
    CARD8 reqType;



    BOOL delete;

    CARD16 length ;
    CARD32 window ;
    CARD32 property , type ;
    CARD32 longOffset ;
    CARD32 longLength ;
} xGetPropertyReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 window ;
    CARD32 selection ;
    CARD32 time ;
} xSetSelectionOwnerReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 requestor ;
    CARD32 selection , target , property ;
    CARD32 time ;
    } xConvertSelectionReq;

typedef struct {
    CARD8 reqType;
    BOOL propagate;
    CARD16 length ;
    CARD32 destination ;
    CARD32 eventMask ;




    xEvent event;

} xSendEventReq;

typedef struct {
    CARD8 reqType;
    BOOL ownerEvents;
    CARD16 length ;
    CARD32 grabWindow ;
    CARD16 eventMask ;
    BYTE pointerMode, keyboardMode;
    CARD32 confineTo ;
    CARD32 cursor ;
    CARD32 time ;
} xGrabPointerReq;

typedef struct {
    CARD8 reqType;
    BOOL ownerEvents;
    CARD16 length ;
    CARD32 grabWindow ;
    CARD16 eventMask ;
    BYTE pointerMode, keyboardMode;
    CARD32 confineTo ;
    CARD32 cursor ;
    CARD8 button;
    BYTE pad;
    CARD16 modifiers ;
} xGrabButtonReq;

typedef struct {
    CARD8 reqType;
    CARD8 button;
    CARD16 length ;
    CARD32 grabWindow ;
    CARD16 modifiers ;
    CARD16 pad ;
} xUngrabButtonReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 cursor ;
    CARD32 time ;
    CARD16 eventMask ;
    CARD16 pad2 ;
} xChangeActivePointerGrabReq;

typedef struct {
    CARD8 reqType;
    BOOL ownerEvents;
    CARD16 length ;
    CARD32 grabWindow ;
    CARD32 time ;
    BYTE pointerMode, keyboardMode;
    CARD16 pad ;
} xGrabKeyboardReq;

typedef struct {
    CARD8 reqType;
    BOOL ownerEvents;
    CARD16 length ;
    CARD32 grabWindow ;
    CARD16 modifiers ;
    CARD8 key;
    BYTE pointerMode, keyboardMode;
    BYTE pad1, pad2, pad3;
} xGrabKeyReq;

typedef struct {
    CARD8 reqType;
    CARD8 key;
    CARD16 length ;
    CARD32 grabWindow ;
    CARD16 modifiers ;
    CARD16 pad ;
} xUngrabKeyReq;

typedef struct {
    CARD8 reqType;
    CARD8 mode;
    CARD16 length ;
    CARD32 time ;
} xAllowEventsReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 window ;
    CARD32 start , stop ;
} xGetMotionEventsReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 srcWid , dstWid ;
    INT16 srcX , srcY ;
} xTranslateCoordsReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 srcWid , dstWid ;
    INT16 srcX , srcY ;
    CARD16 srcWidth , srcHeight ;
    INT16 dstX , dstY ;
} xWarpPointerReq;

typedef struct {
    CARD8 reqType;
    CARD8 revertTo;
    CARD16 length ;
    CARD32 focus ;
    CARD32 time ;
} xSetInputFocusReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 fid ;
    CARD16 nbytes ;
    BYTE pad1, pad2;
} xOpenFontReq;

typedef struct {
    CARD8 reqType;
    BOOL oddLength;
    CARD16 length ;
    CARD32 fid ;
    } xQueryTextExtentsReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD16 maxNames ;
    CARD16 nbytes ;
} xListFontsReq;

typedef xListFontsReq xListFontsWithInfoReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD16 nFonts ;
    BYTE pad1, pad2;
} xSetFontPathReq;

typedef struct {
    CARD8 reqType;
    CARD8 depth;
    CARD16 length ;
    CARD32 pid ;
    CARD32 drawable ;
    CARD16 width , height ;
} xCreatePixmapReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 gc ;
    CARD32 drawable ;
    CARD32 mask ;
} xCreateGCReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 gc ;
    CARD32 mask ;
} xChangeGCReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 srcGC , dstGC ;
    CARD32 mask ;
} xCopyGCReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 gc ;
    CARD16 dashOffset ;
    CARD16 nDashes ;
} xSetDashesReq;

typedef struct {
    CARD8 reqType;
    BYTE ordering;
    CARD16 length ;
    CARD32 gc ;
    INT16 xOrigin , yOrigin ;
} xSetClipRectanglesReq;

typedef struct {
    CARD8 reqType;
    BOOL exposures;
    CARD16 length ;
    CARD32 window ;
    INT16 x , y ;
    CARD16 width , height ;
} xClearAreaReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 srcDrawable , dstDrawable ;
    CARD32 gc ;
    INT16 srcX , srcY , dstX , dstY ;
    CARD16 width , height ;
} xCopyAreaReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 srcDrawable , dstDrawable ;
    CARD32 gc ;
    INT16 srcX , srcY , dstX , dstY ;
    CARD16 width , height ;
    CARD32 bitPlane ;
} xCopyPlaneReq;

typedef struct {
    CARD8 reqType;
    BYTE coordMode;
    CARD16 length ;
    CARD32 drawable ;
    CARD32 gc ;
} xPolyPointReq;

typedef xPolyPointReq xPolyLineReq;



typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 drawable ;
    CARD32 gc ;
} xPolySegmentReq;

typedef xPolySegmentReq xPolyArcReq;
typedef xPolySegmentReq xPolyRectangleReq;
typedef xPolySegmentReq xPolyFillRectangleReq;
typedef xPolySegmentReq xPolyFillArcReq;

typedef struct _FillPolyReq {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 drawable ;
    CARD32 gc ;
    BYTE shape;
    BYTE coordMode;
    CARD16 pad1 ;
} xFillPolyReq;


typedef struct _PutImageReq {
    CARD8 reqType;
    CARD8 format;
    CARD16 length ;
    CARD32 drawable ;
    CARD32 gc ;
    CARD16 width , height ;
    INT16 dstX , dstY ;
    CARD8 leftPad;
    CARD8 depth;
    CARD16 pad ;
} xPutImageReq;

typedef struct {
    CARD8 reqType;
    CARD8 format;
    CARD16 length ;
    CARD32 drawable ;
    INT16 x , y ;
    CARD16 width , height ;
    CARD32 planeMask ;
} xGetImageReq;



typedef struct {
    CARD8 reqType;
    CARD8 pad;
    CARD16 length ;
    CARD32 drawable ;
    CARD32 gc ;
    INT16 x , y ;
} xPolyTextReq;

typedef xPolyTextReq xPolyText8Req;
typedef xPolyTextReq xPolyText16Req;

typedef struct {
    CARD8 reqType;
    BYTE nChars;
    CARD16 length ;
    CARD32 drawable ;
    CARD32 gc ;
    INT16 x , y ;
} xImageTextReq;

typedef xImageTextReq xImageText8Req;
typedef xImageTextReq xImageText16Req;

typedef struct {
    CARD8 reqType;
    BYTE alloc;
    CARD16 length ;
    CARD32 mid ;
    CARD32 window ;
    CARD32 visual ;
} xCreateColormapReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 mid ;
    CARD32 srcCmap ;
} xCopyColormapAndFreeReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 cmap ;
    CARD16 red , green , blue ;
    CARD16 pad2 ;
} xAllocColorReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 cmap ;
    CARD16 nbytes ;
    BYTE pad1, pad2;
} xAllocNamedColorReq;

typedef struct {
    CARD8 reqType;
    BOOL contiguous;
    CARD16 length ;
    CARD32 cmap ;
    CARD16 colors , planes ;
} xAllocColorCellsReq;

typedef struct {
    CARD8 reqType;
    BOOL contiguous;
    CARD16 length ;
    CARD32 cmap ;
    CARD16 colors , red , green , blue ;
} xAllocColorPlanesReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 cmap ;
    CARD32 planeMask ;
} xFreeColorsReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 cmap ;
} xStoreColorsReq;

typedef struct {
    CARD8 reqType;
    CARD8 flags;
    CARD16 length ;
    CARD32 cmap ;
    CARD32 pixel ;
    CARD16 nbytes ;
    BYTE pad1, pad2;
    } xStoreNamedColorReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 cmap ;
} xQueryColorsReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 cmap ;
    CARD16 nbytes ;
    BYTE pad1, pad2;
} xLookupColorReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 cid ;
    CARD32 source , mask ;
    CARD16 foreRed , foreGreen , foreBlue ;
    CARD16 backRed , backGreen , backBlue ;
    CARD16 x , y ;
} xCreateCursorReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 cid ;
    CARD32 source , mask ;
    CARD16 sourceChar , maskChar ;
    CARD16 foreRed , foreGreen , foreBlue ;
    CARD16 backRed , backGreen , backBlue ;
} xCreateGlyphCursorReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 cursor ;
    CARD16 foreRed , foreGreen , foreBlue ;
    CARD16 backRed , backGreen , backBlue ;
} xRecolorCursorReq;

typedef struct {
    CARD8 reqType;



    CARD8 class;

    CARD16 length ;
    CARD32 drawable ;
    CARD16 width , height ;
} xQueryBestSizeReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD16 nbytes ;
    BYTE pad1, pad2;
} xQueryExtensionReq;

typedef struct {
    CARD8 reqType;
    CARD8 numKeyPerModifier;
    CARD16 length ;
} xSetModifierMappingReq;

typedef struct {
    CARD8 reqType;
    CARD8 nElts;
    CARD16 length ;
} xSetPointerMappingReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD8 firstKeyCode;
    CARD8 count;
    CARD16 pad1 ;
} xGetKeyboardMappingReq;

typedef struct {
    CARD8 reqType;
    CARD8 keyCodes;
    CARD16 length ;
    CARD8 firstKeyCode;
    CARD8 keySymsPerKeyCode;
    CARD16 pad1 ;
} xChangeKeyboardMappingReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 mask ;
} xChangeKeyboardControlReq;

typedef struct {
    CARD8 reqType;
    INT8 percent;
    CARD16 length ;
} xBellReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    INT16 accelNum , accelDenum ;
    INT16 threshold ;
    BOOL doAccel, doThresh;
} xChangePointerControlReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    INT16 timeout , interval ;
    BYTE preferBlank, allowExpose;
    CARD16 pad2 ;
} xSetScreenSaverReq;

typedef struct {
    CARD8 reqType;
    BYTE mode;
    CARD16 length ;
    CARD8 hostFamily;
    BYTE pad;
    CARD16 hostLength ;
} xChangeHostsReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    } xListHostsReq;

typedef struct {
    CARD8 reqType;
    BYTE mode;
    CARD16 length ;
    } xChangeModeReq;

typedef xChangeModeReq xSetAccessControlReq;
typedef xChangeModeReq xSetCloseDownModeReq;
typedef xChangeModeReq xForceScreenSaverReq;

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length ;
    CARD32 window ;
    CARD16 nAtoms ;
    INT16 nPositions ;
    } xRotatePropertiesReq;
# 34 "bltWindow.c" 2


typedef struct TkIdStackStruct TkIdStack;
typedef struct TkErrorHandlerStruct TkErrorHandler;
typedef struct TkSelectionInfoStruct TkSelectionInfo;
typedef struct TkClipboardTargetStruct TkClipboardTarget;


typedef struct TkWindowStruct TkWindow;

typedef struct TkWindowEventStruct TkWindowEvent;
typedef struct TkMainInfoStruct TkMainInfo;
typedef struct TkEventHandlerStruct TkEventHandler;
typedef struct TkSelHandlerStruct TkSelHandler;
typedef struct TkWinInfoStruct TkWinInfo;
typedef struct TkClassProcsStruct TkClassProcs;
typedef struct TkWindowPrivateStruct TkWindowPrivate;
typedef struct TkGrabEventStruct TkGrabEvent;
typedef struct TkColormapStruct TkColormap;
typedef struct TkStressedCmapStruct TkStressedCmap;
typedef struct TkWmInfoStruct TkWmInfo;
# 75 "bltWindow.c"
typedef struct TkCaret {
    struct TkWindow *winPtr;

    int x;
    int y;
    int height;
} TkCaret;
# 90 "bltWindow.c"
typedef struct TkDisplayStruct {
    Display *display;
    struct TkDisplayStruct *nextPtr;
    char *name;

    Time lastEventTime;






    int borderInit;
    Tcl_HashTable borderTable;






    int atomInit;

    Tcl_HashTable nameTable;
    Tcl_HashTable atomTable;





    int bindInfoStale;


    unsigned int modeModMask;


    unsigned int metaModMask;


    unsigned int altModMask;


    enum {
        LU_IGNORE, LU_CAPS, LU_SHIFT
    } lockUsage;
    int numModKeyCodes;

    KeyCode *modKeyCodes;
# 145 "bltWindow.c"
    int bitmapInit;
    int bitmapAutoNumber;
    Tcl_HashTable bitmapNameTable;


    Tcl_HashTable bitmapIdTable;

    Tcl_HashTable bitmapDataTable;
# 162 "bltWindow.c"
    int numIdSearches;
    int numSlowSearches;





    int colorInit;
    TkStressedCmap *stressPtr;


    Tcl_HashTable colorNameTable;


    Tcl_HashTable colorValueTable;







    int cursorInit;
    Tcl_HashTable cursorNameTable;


    Tcl_HashTable cursorDataTable;


    Tcl_HashTable cursorIdTable;


    char cursorString[20];
    Font cursorFont;






    struct TkErrorHandler *errorPtr;



    int deleteCount;
# 215 "bltWindow.c"
    struct TkWindowEvent *delayedMotionPtr;
# 228 "bltWindow.c"
    int focusDebug;

    struct TkWindow *implicitWinPtr;





    struct TkWindow *focusPtr;
# 249 "bltWindow.c"
    Tcl_HashTable gcValueTable;

    Tcl_HashTable gcIdTable;
    int gcInit;






    Tcl_HashTable maintainHashTable;



    int geomInit;





    Tcl_HashTable uidTable;
    int uidInit;





    struct TkWindow *grabWinPtr;


    struct TkWindow *eventualGrabWinPtr;



    struct TkWindow *buttonWinPtr;



    struct TkWindow *serverWinPtr;







    TkGrabEvent *firstGrabEventPtr;





    TkGrabEvent *lastGrabEventPtr;


    int grabFlags;






    int gridInit;
    Tcl_HashTable gridHashTable;






    int imageId;





    int postCommandGeneration;
# 337 "bltWindow.c"
    int packInit;
    Tcl_HashTable packerHashTable;
# 347 "bltWindow.c"
    int placeInit;
    Tcl_HashTable masterTable;

    Tcl_HashTable slaveTable;







    struct TkSelectionInfo *selectionInfoPtr;




    Atom multipleAtom;

    Atom incrAtom;
    Atom targetsAtom;
    Atom timestampAtom;
    Atom textAtom;
    Atom compoundTextAtom;
    Atom applicationAtom;
    Atom windowAtom;
    Atom clipboardAtom;

    Atom utf8Atom;

    Tk_Window clipWindow;



    int clipboardActive;

    struct TkMainInfo *clipboardAppPtr;

    struct TkClipboardTarget *clipTargetPtr;
# 394 "bltWindow.c"
    Tk_Window commTkwin;



    Atom commProperty;
    Atom registryProperty;

    Atom appNameProperty;






    struct TkIdStack *idStackPtr;



    XID(*defaultAllocProc) (Display *display);

    struct TkIdStack *windowStackPtr;
# 423 "bltWindow.c"
    Tcl_TimerToken idCleanupScheduled;
# 439 "bltWindow.c"
    struct TkWmInfo *firstWmPtr;
    struct TkWmInfo *foregroundWmPtr;







    int destroyCount;

    unsigned long lastDestroyRequest;
# 460 "bltWindow.c"
    TkColormap *cmapPtr;







    XIM inputMethod;


    XFontSet inputXfs;



    Tcl_HashTable winTable;
    int refCount;







    int mouseButtonState;




    Window warpWindow;
    int warpX;
    int warpY;






    long deletionEpoch;
    unsigned int flags;

    TkCaret caret;


} TkDisplay;
# 779 "bltWindow.c"
struct TkWindowStruct {
    Display *display;
    TkDisplay *dispPtr;
    int screenNum;
    Visual *visual;
    int depth;
    Window window;
    TkWindow *childList;
    TkWindow *lastChildPtr;
    TkWindow *parentPtr;
    TkWindow *nextPtr;
    TkMainInfo *infoPtr;
    char *pathName;
    Tk_Uid nameUid;
    Tk_Uid classUid;
    XWindowChanges changes;
    unsigned int dirtyChanges;
    XSetWindowAttributes atts;
    unsigned long dirtyAtts;
    unsigned int flags;
    TkEventHandler *handlerList;

    XIC inputContext;

    ClientData *tagPtr;
    int nTags;
    int optionLevel;
    TkSelHandler *selHandlerList;
    Tk_GeomMgr *geomMgrPtr;
    ClientData geomData;
    int reqWidth, reqHeight;
    int internalBorderWidth;
    TkWinInfo *wmInfoPtr;

    TkClassProcs *classProcsPtr;
    ClientData instanceData;

    TkWindowPrivate *privatePtr;
};
# 858 "bltWindow.c"
Window
Blt_GetParent(display, window)
    Display *display;
    Window window;
{
    Window root, parent;
    Window *dummy;
    unsigned int count;

    if (XQueryTree(display, window, &root, &parent, &dummy, &count) > 0) {
        XFree(dummy);
        return parent;
    }
    return 0L;
}

static Window
GetWindowId(tkwin)
    Tk_Window tkwin;
{
    Window window;

    Tk_MakeWindowExist(tkwin);
    window = (((Tk_FakeWin *) (tkwin))->window);

    if ((((Tk_FakeWin *) (tkwin))->flags & 2)) {
        Window parent;

        parent = Blt_GetParent((((Tk_FakeWin *) (tkwin))->display), window);
        if (parent != 0L) {
            window = parent;
        }
        window = parent;
    }

    return window;
}
# 914 "bltWindow.c"
static void
DoConfigureNotify(winPtr)
    Tk_FakeWin *winPtr;

{
    XEvent event;

    event.type = 22;
    event.xconfigure.serial = (((_XPrivDisplay)winPtr->display)->last_request_read);
    event.xconfigure.send_event = 0;
    event.xconfigure.display = winPtr->display;
    event.xconfigure.event = winPtr->window;
    event.xconfigure.window = winPtr->window;
    event.xconfigure.x = winPtr->changes.x;
    event.xconfigure.y = winPtr->changes.y;
    event.xconfigure.width = winPtr->changes.width;
    event.xconfigure.height = winPtr->changes.height;
    event.xconfigure.border_width = winPtr->changes.border_width;
    if (winPtr->changes.stack_mode == 0) {
        event.xconfigure.above = winPtr->changes.sibling;
    } else {
        event.xconfigure.above = 0L;
    }
    event.xconfigure.override_redirect = winPtr->atts.override_redirect;
    Tk_HandleEvent(&event);
}
# 967 "bltWindow.c"
void
Blt_MakeTransparentWindowExist(tkwin, parent, isBusy)
    Tk_Window tkwin;
    Window parent;
    int isBusy;
{
    TkWindow *winPtr = (TkWindow *) tkwin;
    TkWindow *winPtr2;
    Tcl_HashEntry *hPtr;
    int notUsed;
    TkDisplay *dispPtr;






    long int mask;


    if (winPtr->window != 0L) {
        return;
    }
# 1015 "bltWindow.c"
    mask = (!isBusy) ? 0 : ((1L<<12) | (1L<<11));






    winPtr->atts.do_not_propagate_mask = ((1L<<0) | (1L<<1) | (1L<<2) | (1L<<3) | (1L<<6));
    winPtr->atts.event_mask = ((1L<<4) | (1L<<5) | (1L<<0) | (1L<<1) | (1L<<2) | (1L<<3) | (1L<<6));
    winPtr->changes.border_width = 0;
    winPtr->depth = 0;

    winPtr->window = XCreateWindow(winPtr->display, parent,
        winPtr->changes.x, winPtr->changes.y,
        (unsigned)winPtr->changes.width,
        (unsigned)winPtr->changes.height,
        (unsigned)winPtr->changes.border_width,
        winPtr->depth,
        2,
        winPtr->visual,
        mask,
        &(winPtr->atts) );

    printf("XCreateWindow: %d\n", (int)winPtr->window);



    dispPtr = winPtr->dispPtr;

    printf("XCreateWindow: %d\n", (int)winPtr->window);

    hPtr = (*((&(dispPtr->winTable))->createProc))(&(dispPtr->winTable), (char *)winPtr->window, &notUsed);

    ((hPtr)->clientData = (ClientData) (winPtr));
    winPtr->dirtyAtts = 0;
    winPtr->dirtyChanges = 0;

    winPtr->inputContext = ((void *)0);

    if (!(winPtr->flags & 2)) {
# 1065 "bltWindow.c"
        for (winPtr2 = winPtr->nextPtr; winPtr2 != ((void *)0);
            winPtr2 = winPtr2->nextPtr) {
            if ((winPtr2->window != 0L) && !(winPtr2->flags & 2)) {
                XWindowChanges changes;
                changes.sibling = winPtr2->window;
                changes.stack_mode = 1;
                XConfigureWindow(winPtr->display, winPtr->window,
                    (1<<5) | (1<<6), &changes);
                break;
            }
        }
    }







    if ((winPtr->flags & 8)
        && !(winPtr->flags & 4)) {
        winPtr->flags &= ~8;
        DoConfigureNotify((Tk_FakeWin *) tkwin);
    }
}
# 1110 "bltWindow.c"
Tk_Window
Blt_FindChild(parent, name)
    Tk_Window parent;
    char *name;
{
    register TkWindow *winPtr;
    TkWindow *parentPtr = (TkWindow *)parent;

    for (winPtr = parentPtr->childList; winPtr != ((void *)0);
        winPtr = winPtr->nextPtr) {
        if (__extension__ ({ size_t __s1_len, __s2_len; (__builtin_constant_p (name) && __builtin_constant_p (winPtr->nameUid) && (__s1_len = strlen (name), __s2_len = strlen (winPtr->nameUid), (!((size_t)(const void *)((name) + 1) - (size_t)(const void *)(name) == 1) || __s1_len >= 4) && (!((size_t)(const void *)((winPtr->nameUid) + 1) - (size_t)(const void *)(winPtr->nameUid) == 1) || __s2_len >= 4)) ? memcmp ((__const char *) (name), (__const char *) (winPtr->nameUid), (__s1_len < __s2_len ? __s1_len : __s2_len) + 1) : (__builtin_constant_p (name) && ((size_t)(const void *)((name) + 1) - (size_t)(const void *)(name) == 1) && (__s1_len = strlen (name), __s1_len < 4) ? (__builtin_constant_p (winPtr->nameUid) && ((size_t)(const void *)((winPtr->nameUid) + 1) - (size_t)(const void *)(winPtr->nameUid) == 1) ? (__extension__ ({ register int __result = (((__const unsigned char *) (__const char *) (name))[0] - ((__const unsigned char *) (__const char *)(winPtr->nameUid))[0]); if (__s1_len > 0 && __result == 0) { __result = (((__const unsigned char *) (__const char *) (name))[1] - ((__const unsigned char *) (__const char *) (winPtr->nameUid))[1]); if (__s1_len > 1 && __result == 0) { __result = (((__const unsigned char *) (__const char *) (name))[2] - ((__const unsigned char *) (__const char *) (winPtr->nameUid))[2]); if (__s1_len > 2 && __result == 0) __result = (((__const unsigned char *) (__const char *) (name))[3] - ((__const unsigned char *) (__const char *) (winPtr->nameUid))[3]); } } __result; })) : (__extension__ ({ __const unsigned char *__s2 = (__const unsigned char *) (__const char *) (winPtr->nameUid); register int __result = (((__const unsigned char *) (__const char *) (name))[0] - __s2[0]); if (__s1_len > 0 && __result == 0) { __result = (((__const unsigned char *) (__const char *) (name))[1] - __s2[1]); if (__s1_len > 1 && __result == 0) { __result = (((__const unsigned char *) (__const char *) (name))[2] - __s2[2]); if (__s1_len > 2 && __result == 0) __result = (((__const unsigned char *) (__const char *) (name))[3] - __s2[3]); } } __result; }))) : (__builtin_constant_p (winPtr->nameUid) && ((size_t)(const void *)((winPtr->nameUid) + 1) - (size_t)(const void *)(winPtr->nameUid) == 1) && (__s2_len = strlen (winPtr->nameUid), __s2_len < 4) ? (__builtin_constant_p (name) && ((size_t)(const void *)((name) + 1) - (size_t)(const void *)(name) == 1) ? (__extension__ ({ register int __result = (((__const unsigned char *) (__const char *) (name))[0] - ((__const unsigned char *) (__const char *)(winPtr->nameUid))[0]); if (__s2_len > 0 && __result == 0) { __result = (((__const unsigned char *) (__const char *) (name))[1] - ((__const unsigned char *) (__const char *) (winPtr->nameUid))[1]); if (__s2_len > 1 && __result == 0) { __result = (((__const unsigned char *) (__const char *) (name))[2] - ((__const unsigned char *) (__const char *) (winPtr->nameUid))[2]); if (__s2_len > 2 && __result == 0) __result = (((__const unsigned char *) (__const char *) (name))[3] - ((__const unsigned char *) (__const char *) (winPtr->nameUid))[3]); } } __result; })) : (__extension__ ({ __const unsigned char *__s1 = (__const unsigned char *) (__const char *) (name); register int __result = __s1[0] - ((__const unsigned char *) (__const char *) (winPtr->nameUid))[0]; if (__s2_len > 0 && __result == 0) { __result = (__s1[1] - ((__const unsigned char *) (__const char *) (winPtr->nameUid))[1]); if (__s2_len > 1 && __result == 0) { __result = (__s1[2] - ((__const unsigned char *) (__const char *) (winPtr->nameUid))[2]); if (__s2_len > 2 && __result == 0) __result = (__s1[3] - ((__const unsigned char *) (__const char *) (winPtr->nameUid))[3]); } } __result; }))) : strcmp (name, winPtr->nameUid)))); }) == 0) {
            return (Tk_Window)winPtr;
        }
    }
    return ((void *)0);
}
# 1145 "bltWindow.c"
Tk_Window
Blt_FirstChild(parent)
    Tk_Window parent;
{
    TkWindow *parentPtr = (TkWindow *)parent;
    return (Tk_Window)parentPtr->childList;
}
# 1172 "bltWindow.c"
Tk_Window
Blt_NextChild(tkwin)
    Tk_Window tkwin;
{
    TkWindow *winPtr = (TkWindow *)tkwin;

    if (winPtr == ((void *)0)) {
        return ((void *)0);
    }
    return (Tk_Window)winPtr->nextPtr;
}
# 1200 "bltWindow.c"
static void
UnlinkWindow(winPtr)
    TkWindow *winPtr;
{
    TkWindow *prevPtr;

    prevPtr = winPtr->parentPtr->childList;
    if (prevPtr == winPtr) {
        winPtr->parentPtr->childList = winPtr->nextPtr;
        if (winPtr->nextPtr == ((void *)0)) {
            winPtr->parentPtr->lastChildPtr = ((void *)0);
        }
    } else {
        while (prevPtr->nextPtr != winPtr) {
            prevPtr = prevPtr->nextPtr;
            if (prevPtr == ((void *)0)) {
                Blt_Panic("%s:%d %s", "bltWindow.c", 1216, ("UnlinkWindow couldn't find child in parent"));
            }
        }
        prevPtr->nextPtr = winPtr->nextPtr;
        if (winPtr->nextPtr == ((void *)0)) {
            winPtr->parentPtr->lastChildPtr = prevPtr;
        }
    }
}
# 1249 "bltWindow.c"
void
Blt_RelinkWindow(tkwin, newParent, x, y)
    Tk_Window tkwin;
    Tk_Window newParent;
    int x, y;
{
    TkWindow *winPtr, *parentWinPtr;

    if (Blt_ReparentWindow((((Tk_FakeWin *) (tkwin))->display), (((Tk_FakeWin *) (tkwin))->window),
            (((Tk_FakeWin *) (newParent))->window), x, y) != 0) {
        return;
    }
    winPtr = (TkWindow *)tkwin;
    parentWinPtr = (TkWindow *)newParent;

    winPtr->flags &= ~0x2000;
    UnlinkWindow(winPtr);


    winPtr->parentPtr = parentWinPtr;
    winPtr->nextPtr = ((void *)0);
    if (parentWinPtr->childList == ((void *)0)) {
        parentWinPtr->childList = winPtr;
    } else {
        parentWinPtr->lastChildPtr->nextPtr = winPtr;
    }
    parentWinPtr->lastChildPtr = winPtr;
}
# 1301 "bltWindow.c"
void
Blt_RelinkWindow2(tkwin, window, newParent, x, y)
    Tk_Window tkwin;
    Window window;
    Tk_Window newParent;
    int x, y;
{



    if (Blt_ReparentWindow((((Tk_FakeWin *) (tkwin))->display), window,
            (((Tk_FakeWin *) (newParent))->window), x, y) != 0) {
        return;
    }
# 1332 "bltWindow.c"
}

void
Blt_UnlinkWindow(tkwin)
    Tk_Window tkwin;
{
    TkWindow *winPtr;
    Window root;

    root = XRootWindow((((Tk_FakeWin *) (tkwin))->display), (((Tk_FakeWin *) (tkwin))->screenNum));
    if (Blt_ReparentWindow((((Tk_FakeWin *) (tkwin))->display), (((Tk_FakeWin *) (tkwin))->window),
            root, 0, 0) != 0) {
        return;
    }
    winPtr = (TkWindow *)tkwin;
    winPtr->flags &= ~0x2000;



}
# 1366 "bltWindow.c"
Tk_Window
Blt_Toplevel(tkwin)
    register Tk_Window tkwin;
{
    while (!(((Tk_FakeWin *) (tkwin))->flags & 2)) {
        tkwin = (((Tk_FakeWin *) (tkwin))->parentPtr);
    }
    return tkwin;
}

void
Blt_RootCoordinates(tkwin, x, y, rootXPtr, rootYPtr)
    Tk_Window tkwin;
    int x, y;
    int *rootXPtr, *rootYPtr;
{
    int vx, vy, vw, vh;
    int rootX, rootY;

    Tk_GetRootCoords(tkwin, &rootX, &rootY);
    x += rootX;
    y += rootY;
    Tk_GetVRootGeometry(tkwin, &vx, &vy, &vw, &vh);
    x += vx;
    y += vy;
    *rootXPtr = x;
    *rootYPtr = y;
}



int
Blt_RootX(tkwin)
    Tk_Window tkwin;
{
    int x;

    for (x = 0; tkwin != ((void *)0); tkwin = (((Tk_FakeWin *) (tkwin))->parentPtr)) {
        x += (((Tk_FakeWin *) (tkwin))->changes.x) + (&((Tk_FakeWin *) (tkwin))->changes)->border_width;
        if ((((Tk_FakeWin *) (tkwin))->flags & 2)) {
            break;
        }
    }
    return x;
}

int
Blt_RootY(tkwin)
    Tk_Window tkwin;
{
    int y;

    for (y = 0; tkwin != ((void *)0); tkwin = (((Tk_FakeWin *) (tkwin))->parentPtr)) {
        y += (((Tk_FakeWin *) (tkwin))->changes.y) + (&((Tk_FakeWin *) (tkwin))->changes)->border_width;
        if ((((Tk_FakeWin *) (tkwin))->flags & 2)) {
            break;
        }
    }
    return y;
}
# 1578 "bltWindow.c"
Window
Blt_GetRealWindowId(tkwin)
    Tk_Window tkwin;
{
    return GetWindowId(tkwin);
}
# 1595 "bltWindow.c"
void
Blt_RaiseToplevel(tkwin)
    Tk_Window tkwin;
{
    XRaiseWindow((((Tk_FakeWin *) (tkwin))->display), GetWindowId(tkwin));
}
# 1612 "bltWindow.c"
void
Blt_LowerToplevel(tkwin)
    Tk_Window tkwin;
{
    XLowerWindow((((Tk_FakeWin *) (tkwin))->display), GetWindowId(tkwin));
}
# 1629 "bltWindow.c"
void
Blt_ResizeToplevel(tkwin, width, height)
    Tk_Window tkwin;
    int width, height;
{
    XResizeWindow((((Tk_FakeWin *) (tkwin))->display), GetWindowId(tkwin), width, height);
}
# 1647 "bltWindow.c"
void
Blt_MoveResizeToplevel(tkwin, x, y, width, height)
    Tk_Window tkwin;
    int x, y, width, height;
{
    XMoveResizeWindow((((Tk_FakeWin *) (tkwin))->display), GetWindowId(tkwin), x, y,
              width, height);
}
# 1666 "bltWindow.c"
void
Blt_MoveToplevel(tkwin, x, y)
    Tk_Window tkwin;
    int x, y;
{
    XMoveWindow((((Tk_FakeWin *) (tkwin))->display), GetWindowId(tkwin), x, y);
}
# 1684 "bltWindow.c"
void
Blt_MapToplevel(tkwin)
    Tk_Window tkwin;
{
    XMapWindow((((Tk_FakeWin *) (tkwin))->display), GetWindowId(tkwin));
}
# 1701 "bltWindow.c"
void
Blt_UnmapToplevel(tkwin)
    Tk_Window tkwin;
{
    XUnmapWindow((((Tk_FakeWin *) (tkwin))->display), GetWindowId(tkwin));
}


static int
XReparentWindowErrorProc(clientData, errEventPtr)
    ClientData clientData;
    XErrorEvent *errEventPtr;
{
    int *errorPtr = clientData;

    *errorPtr = 1;
    return 0;
}

int
Blt_ReparentWindow(display, window, newParent, x, y)
    Display *display;
    Window window, newParent;
    int x, y;
{
    Tk_ErrorHandler handler;
    int result;
    int any = -1;

    result = 0;
    handler = Tk_CreateErrorHandler(display, any, 7, any,
        XReparentWindowErrorProc, &result);
    XReparentWindow(display, window, newParent, x, y);
    Tk_DeleteErrorHandler(handler);
    XSync(display, 0);
    return result;
}
# 1789 "bltWindow.c"
void
Blt_SetWindowInstanceData(tkwin, instanceData)
    Tk_Window tkwin;
    ClientData instanceData;
{
    TkWindow *winPtr = (TkWindow *)tkwin;

    winPtr->instanceData = instanceData;
}

ClientData
Blt_GetWindowInstanceData(tkwin)
    Tk_Window tkwin;
{
    TkWindow *winPtr = (TkWindow *)tkwin;

    return winPtr->instanceData;
}

void
Blt_DeleteWindowInstanceData(tkwin)
    Tk_Window tkwin;
{
}
