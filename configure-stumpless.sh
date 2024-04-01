#!/bin/sh

cmake \
  -DENABLE_JOURNALD_TARGETS=OFF \
  -DENABLE_NETWORK_TARGETS=OFF \
  -DENABLE_SOCKET_TARGETS=OFF \
  -DENABLE_SQLITE3_TARGETS=OFF \
  -DENABLE_WINDOWS_EVENT_LOG_TARGETS=OFF \
  -DENABLE_THREAD_SAFETY=OFF \
  -DHAVE_PTHREAD_H=0 \
  -DHAVE_STDATOMIC_H=0 \
  -DHAVE_SQLITE3_H=0 \
  -DHAVE_SYS_SOCKET_H=0 \
  -DSTUMPLESS_SYSLOG_H_COMPATIBLE=0 \
  -DHAVE_SYSTEMD_SD_JOURNAL_H=0 \
  -DHAVE_UNISTD_H=0 \
  -DHAVE_WINDOWS_H=0 \
  -DHAVE_WINSOCK2_H=0 \
  -DHAVE_FOPEN_S=0 \
  -DHAVE_GETADDRINFO=0 \
  -DHAVE_UNISTD_GETHOSTNAME=0 \
  -DHAVE_GETHOSTBYNAME=0 \
  -DHAVE_GETHOSTBYNAME2=0 \
  -DHAVE_UNISTD_GETPAGESIZE=0 \
  -DHAVE_GMTIME=1 \
  -DHAVE_GMTIME_R=0 \
  -DHAVE_UNISTD_SC_PAGESIZE=0 \
  -DHAVE_SPRINTF_S=0 \
  -DHAVE_UNISTD_SYSCONF=0 \
  -DHAVE_VSNPRINTF_S=0 \
  -DHAVE_WCSRTOMBS_S=0 \
  -DHAVE_WCSTOMBS_S=0 \
  -DDEFAULT_FILE="STMPLSS.LOG" \
  "$1"

make single-file

sed -i 's/__attribute__.*$/ /' stumpless.c
sed -i 's/__builtin_expect.*$/( EXPRESSION )/' stumpless.c
cp stumpless.c SRC/STMPLSS.C

sed -i 's/__attribute__.*$/ /' include/single_file/stumpless.h
sed -i 's/__builtin_expect.*$/( EXPRESSION )/' include/single_file/stumpless.h
cp include/single_file/stumpless.h SRC/STMPLSS.H