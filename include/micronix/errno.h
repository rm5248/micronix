#ifndef MICRONIX_ERRNO_H
#define MICRONIX_ERRNO_H

#define SUCCESS 0 /* Not actually defined by POSIX */

/* Errnos as defined by POSIX */
#define E2BIG         1   /* Argument list too long */
#define EACCESS       2   /* Permission denied */
#define EADDRINUSE    3   /* Address in use */
#define EADDRNOTAVAIL 4   /* Address not available */
#define EAFNOSUPPORT  5   /* Address family not supported */
#define EAGAIN        6   /* Resource unavailable(same as EWOULDBLOCK) */
#define EWOULDBLOCK   EAGAIN
#define EALREADY      7   /* Connection already in progress */
#define EBADF         8   /* Bad file descriptor */
#define EBADMSG       9   /* Bad message */
#define EBUSY         10  /* Device or resource busy */
#define ECANCELED     11  /* Operation canceled */
#define ECHILD        12  /* No child process */
#define ECONNABORTED  13  /* Connection aborted */
#define ECONNREFUSED  14  /* Connection refused */
#define ECONNRESET    15  /* Connection reset */
#define EDEADLK       16  /* Resource deadlock would occur */
#define EDESTADDRREQ  17  /* Destination address required */
#define EDOM          18  /* Mathematics argument out of domain of function */
#define EDQUOT        19  /* Reserved */
#define EEXIST        20  /* File exists */
#define EFAULT        21  /* Bad address */
#define EFBIG         22  /* File too large */
#define EHOSTUNREACH  23  /* Host is unreachable */
#define EIDRM         24  /* Identifier removed */
#define EILSEQ        25  /* Illegal byte sequence */
#define EINPROGRESS   26  /* Operation in progress */
#define EINTR         28  /* Interrupted function */
#define EINVAL        29  /* Invalid argument */
#define EIO           30  /* I/O error */
#define EISCONN       31  /* Socket is connected */
#define EISDIR        32  /* Is a directory */
#define ELOOP         33  /* Too many levels of symbolic links */
#define EMFILE        34  /* File descriptor value too large */
#define EMLINK        35  /* Too many links */
#define EMSGSIZE      36  /* Message too large */
#define EMULTIHOP     37  /* Reserved */
#define ENAMETOOLONG  38  /* File name too long */
#define ENETDOWN      39  /* Network is down */
#define ENETRESET     40  /* Connection aborted by network */
#define ENETUNREACH   41  /* Network is unreachable */
#define ENFILE        42  /* Too many files open in system */
#define ENOBUFS       43  /* No buffer space available */
#define ENODATA       44  /* No message data is available on the STREAM head request queue */
#define ENODEV        45  /* No such device */
#define ENOENT        46  /* No such file or directory */
#define ENOEXEC       47  /* Executable file format error */
#define ENOLCK        48  /* No locks available */
#define ENOLINK       49  /* Reserved */
#define ENOMEM        50  /* Not enough space */
#define ENOMSG        51  /* No message of the desired type */
#define ENOPROTOOPT   52  /* Protocol not available */
#define ENOSPC        53  /* No space left on device */
#define ENOSR         54  /* No STREAM resources */
#define ENOSTR        55  /* Not a STREAM */
#define ENOSYS        56  /* Functionality not supported */
#define ENOTCONN      57  /* The socket is not connected */
#define ENOTDIR       58  /* Not a directory or a symbolic link to a directory */
#define ENOTEMPTY     59  /* Directory not empty */
#define ENOTRECOVERABLE 60 /* State not revoerable */
#define ENOTSOCK      61  /* Not a socket */
#define ENOTSUP       62  /* Not supported(may be same value as EOPNOTSUPP */
#define ENOTTY        63  /* Inappropriate I/O control operation */
#define ENXIO         64  /* No such device or address */
#define EOPNOTSUPP ENOTSUP /* Operation not supported on a socket */
#define EOVERFLOW     65  /* Value too large to be stored in data type */
#define EOWNERDEAD    66  /* Previous owner died */
#define EPERM         67  /* Operation not permitted */
#define EPIPE         68  /* Broken pipe */
#define EPROTO        69  /* Protocol error */
#define EPROTONOSUPPORT 70 /* Protocol not supported */
#define EPROTOTYPE    71  /* Prtocol wrong type for socket */
#define ERANGE        72  /* Result too large */
#define EROFS         73  /* Read-only file system */
#define ESPIPE        74  /* Invalid seek */
#define ESRCH         75  /* No such process */
#define ESTALE        76  /* Reserved */
#define ETIME         77  /* Stream ioctl() timeout */
#define ETIMEDOUT     78  /* Connection timed out */
#define ETXTBSY       79  /* Text file busy */
#define EXDEV         80  /* Cross-device link */

#endif
