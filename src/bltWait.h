/*
 * bltWait.h --
 *
 *	Copyright 1993-2004 George A Howlett.
 *
 *	Permission is hereby granted, free of charge, to any person
 *	obtaining a copy of this software and associated documentation
 *	files (the "Software"), to deal in the Software without
 *	restriction, including without limitation the rights to use,
 *	copy, modify, merge, publish, distribute, sublicense, and/or
 *	sell copies of the Software, and to permit persons to whom the
 *	Software is furnished to do so, subject to the following
 *	conditions:
 *
 *	The above copyright notice and this permission notice shall be
 *	included in all copies or substantial portions of the
 *	Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
 *	KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 *	WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 *	PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 *	OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *	OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 *	OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 *	SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _BLT_WAIT_H
#define _BLT_WAIT_H

#ifdef HAVE_WAITFLAGS_H
#   include <waitflags.h>
#endif
#ifdef HAVE_SYS_WAIT_H
#   include <sys/wait.h>
#endif
#ifdef HAVE_ERRNO_H
#   include <errno.h>
#endif

/*
 * Define EINPROGRESS in terms of WSAEINPROGRESS.
 */

#ifndef	EINPROGRESS
#define EINPROGRESS WSAEINPROGRESS
#endif

/*
 * If ENOTSUP is not defined, define it to a value that will never occur.
 */

#ifndef ENOTSUP
#define	ENOTSUP		-1030507
#endif

/*
 * The following defines redefine the Windows Socket errors as
 * BSD errors so Tcl_PosixError can do the right thing.
 */

#ifndef EWOULDBLOCK
#define EWOULDBLOCK             EAGAIN
#endif
#ifndef EALREADY
#define EALREADY	149	/* operation already in progress */
#endif
#ifndef ENOTSOCK
#define ENOTSOCK	95	/* Socket operation on non-socket */
#endif
#ifndef EDESTADDRREQ
#define EDESTADDRREQ	96	/* Destination address required */
#endif
#ifndef EMSGSIZE
#define EMSGSIZE	97	/* Message too long */
#endif
#ifndef EPROTOTYPE
#define EPROTOTYPE	98	/* Protocol wrong type for socket */
#endif
#ifndef ENOPROTOOPT
#define ENOPROTOOPT	99	/* Protocol not available */
#endif
#ifndef EPROTONOSUPPORT
#define EPROTONOSUPPORT	120	/* Protocol not supported */
#endif
#ifndef ESOCKTNOSUPPORT
#define ESOCKTNOSUPPORT	121	/* Socket type not supported */
#endif
#ifndef EOPNOTSUPP
#define EOPNOTSUPP	122	/* Operation not supported on socket */
#endif
#ifndef EPFNOSUPPORT
#define EPFNOSUPPORT	123	/* Protocol family not supported */
#endif
#ifndef EAFNOSUPPORT
#define EAFNOSUPPORT	124	/* Address family not supported */
#endif
#ifndef EADDRINUSE
#define EADDRINUSE	125	/* Address already in use */
#endif
#ifndef EADDRNOTAVAIL
#define EADDRNOTAVAIL	126	/* Can't assign requested address */
#endif
#ifndef ENETDOWN
#define ENETDOWN	127	/* Network is down */
#endif
#ifndef ENETUNREACH
#define ENETUNREACH	128	/* Network is unreachable */
#endif
#ifndef ENETRESET
#define ENETRESET	129	/* Network dropped connection on reset */
#endif
#ifndef ECONNABORTED
#define ECONNABORTED	130	/* Software caused connection abort */
#endif
#ifndef ECONNRESET
#define ECONNRESET	131	/* Connection reset by peer */
#endif
#ifndef ENOBUFS
#define ENOBUFS		132	/* No buffer space available */
#endif
#ifndef EISCONN
#define EISCONN		133	/* Socket is already connected */
#endif
#ifndef ENOTCONN
#define ENOTCONN	134	/* Socket is not connected */
#endif
#ifndef ESHUTDOWN
#define ESHUTDOWN	143	/* Can't send after socket shutdown */
#endif
#ifndef ETOOMANYREFS
#define ETOOMANYREFS	144	/* Too many references: can't splice */
#endif
#ifndef ETIMEDOUT
#define ETIMEDOUT	145	/* Connection timed out */
#endif
#ifndef ECONNREFUSED
#define ECONNREFUSED	146	/* Connection refused */
#endif
#ifndef ELOOP
#define ELOOP		90	/* Symbolic link loop */
#endif
#ifndef EHOSTDOWN
#define EHOSTDOWN	147	/* Host is down */
#endif
#ifndef EHOSTUNREACH
#define EHOSTUNREACH	148	/* No route to host */
#endif
#ifndef ENOTEMPTY
#define ENOTEMPTY 	93	/* directory not empty */
#endif
#ifndef EUSERS
#define EUSERS		94	/* Too many users (for UFS) */
#endif
#ifndef EDQUOT
#define EDQUOT		49	/* Disc quota exceeded */
#endif
#ifndef ESTALE
#define ESTALE		151	/* Stale NFS file handle */
#endif
#ifndef EREMOTE
#define EREMOTE		66	/* The object is remote */
#endif

#ifndef WIFEXITED
#   define WIFEXITED(stat)  (((*((int *) &(stat))) & 0xff) == 0)
#endif

#ifndef WEXITSTATUS
#   define WEXITSTATUS(stat) (((*((int *) &(stat))) >> 8) & 0xff)
#endif

#ifndef WIFSIGNALED
#   define WIFSIGNALED(stat) (((*((int *) &(stat)))) && ((*((int *) &(stat))) == ((*((int *) &(stat))) & 0x00ff)))
#endif

#ifndef WTERMSIG
#   define WTERMSIG(stat)    ((*((int *) &(stat))) & 0x7f)
#endif

#ifndef WIFSTOPPED
#   define WIFSTOPPED(stat)  (((*((int *) &(stat))) & 0xff) == 0177)
#endif

#ifndef WSTOPSIG
#   define WSTOPSIG(stat)    (((*((int *) &(stat))) >> 8) & 0xff)
#endif

/*
 * Define constants for waitpid() system call if they aren't defined
 * by a system header file.
 */

#ifndef WNOHANG
#   define WNOHANG 1
#endif
#ifndef WUNTRACED
#   define WUNTRACED 2
#endif

/*
 * The type of the status returned by wait varies from UNIX system
 * to UNIX system.  The macro below defines it:
 */

#ifdef AIX
#   define WAIT_STATUS_TYPE pid_t
#else
#ifdef HAVE_UNION_WAIT
#   define WAIT_STATUS_TYPE union wait
#else
#   define WAIT_STATUS_TYPE int
#endif
#endif

/*
 * Supply definitions for macros to query wait status, if not already
 * defined in header files above.
 */

#ifndef WIFEXITED
#   define WIFEXITED(stat)  (((*((int *) &(stat))) & 0xff) == 0)
#endif

#ifndef WEXITSTATUS
#   define WEXITSTATUS(stat) (((*((int *) &(stat))) >> 8) & 0xff)
#endif

#ifndef WIFSIGNALED
#   define WIFSIGNALED(stat) (((*((int *) &(stat)))) && ((*((int *) &(stat))) == ((*((int *) &(stat))) & 0x00ff)))
#endif

#ifndef WTERMSIG
#   define WTERMSIG(stat)    ((*((int *) &(stat))) & 0x7f)
#endif

#ifndef WIFSTOPPED
#   define WIFSTOPPED(stat)  (((*((int *) &(stat))) & 0xff) == 0177)
#endif

#ifndef WSTOPSIG
#   define WSTOPSIG(stat)    (((*((int *) &(stat))) >> 8) & 0xff)
#endif

#endif /* _BLT_WAIT_H */
