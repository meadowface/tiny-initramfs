/*
 * tiny_initramfs - Minimalistic initramfs implementation
 * Copyright (C) 2016 Christian Seiler <christian@iwakd.de>
 *
 * tiny_initramfs.h: function declarations
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TINY_INITRAMFS_H
#define TINY_INITRAMFS_H

#include <sys/types.h>
#include <fcntl.h>

#ifndef MAX_LINE_LEN
#define MAX_LINE_LEN              4096
#endif

#ifndef MAX_PATH_LEN
#define MAX_PATH_LEN              1024
#endif

#ifndef TARGET_DIRECTORY
#define TARGET_DIRECTORY          "/target"
#endif

#ifndef FSTAB_FILENAME
#define FSTAB_FILENAME            "/etc/fstab"
#endif

#ifndef PROC_FILESYSTEMS_FILENAME
#define PROC_FILESYSTEMS_FILENAME "/proc/filesystems"
#endif

#ifndef PROC_CMDLINE_FILENAME
#define PROC_CMDLINE_FILENAME     "/proc/cmdline"
#endif

#ifndef KMSG_FILENAME
#define KMSG_FILENAME             "/dev/ksmg"
#endif

#ifndef MAX_SUPPORTED_FILESYSTEMS
#define MAX_SUPPORTED_FILESYSTEMS  256
#endif

#ifndef MAX_FILESYSTEM_TYPE_LEN
#define MAX_FILESYSTEM_TYPE_LEN    32
#endif

#ifndef LOG_PREFIX
#define LOG_PREFIX                 "initramfs: "
#endif

#ifndef DEVTMPFS_MOUNTOPTS
#define DEVTMPFS_MOUNTOPTS         "size=10240k,mode=0755"
#endif

#ifndef DEVICE_TIMEOUT
#define DEVICE_TIMEOUT             180
#endif

#ifndef DEVICE_MESSAGE_TIMEOUT
#define DEVICE_MESSAGE_TIMEOUT     10
#endif

#ifndef DEVICE_POLL_MSEC
#define DEVICE_POLL_MSEC           50
#endif

/* Not all alternative libc implementations support this yet. */
#ifndef O_CLOEXEC
#define O_CLOEXEC                  02000000
#endif

/* io.c */
typedef int (*traverse_line_t)(void *data, const char *line, int line_is_incomplete);
int traverse_file_by_line(const char *filename, traverse_line_t fn, void *data);

/* fstab.c */
typedef struct fstab_info {
  char source[MAX_PATH_LEN];
  char dest[MAX_PATH_LEN];
  char type[MAX_PATH_LEN];
  char options[MAX_LINE_LEN];
  int dump;
  int pass;
} fstab_info;
int fstab_find_fs(const char *dest, fstab_info *info);

/* mount.c */
int parse_mount_options(char *syscall_data, size_t syscall_data_len, const char *option_string);
int mount_filesystem(const char *source, const char *target, const char *type, const char *flags, int override_flags_add, int override_flags_subtract);

/* log.c */
void panic(int err, ...) __attribute__((noreturn));
void warn(const char *str1, ...);

#endif /* !defined(TINY_INITRAMFS_H) */