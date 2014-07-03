#ifndef __KSYMS_H
#define __KSYMS_H

#include <linux/kdebug.h>
#include <linux/notifier.h>

struct kernel_syms {
	unsigned long *sys_call_table;
	void *sys_call_table_call;

	/* syscalls */
	long (*old_sys_chdir)(char *);
	long (*old_sys_stat)(char *, void *);
	long (*old_sys_lstat)(char *, void *);
	long (*old_sys_fstat)(int, void *);
	long (*old_sys_fstatat)(int, char *, void *, int);
	long (*old_sys_open)(char *, int, umode_t);
        long (*old_sys_getdents)(unsigned int, void *, unsigned int);
        long (*old_sys_getdents64)(unsigned int, void *, unsigned int);

	/* PID syscalls */
	long (*old_sys_getpgid)(pid_t);
	long (*old_sys_setpgid)(pid_t, pid_t);
	long (*old_sys_getsid)(pid_t);
	long (*old_sys_getpriority)(int, int);
	long (*old_sys_kill)(pid_t, int);
	long (*old_sys_sched_setscheduler)(pid_t, int, void *);
	long (*old_sys_sched_setparam)(pid_t, void *);
	long (*old_sys_sched_getscheduler)(pid_t);
	long (*old_sys_sched_getparam)(pid_t, void *);
	long (*old_sys_sched_setaffinity)(pid_t, size_t, void *);
	long (*old_sys_sched_getaffinity)(pid_t, size_t, void *);
	long (*old_sys_sched_rr_get_interval)(pid_t, void *);
	long (*old_sys_wait4)(pid_t, int *, int, void *);
	long (*old_sys_get_robust_list)(int, void **, size_t *);
	long (*old_sys_perf_event_open)(void *, pid_t, int, int,
					unsigned long);
	void (*old_sys_exit)(int);
	void (*old_sys_exit_group)(int);
	long (*old_sys_getpid)(void);
	long (*old_sys_getppid)(void);
	long (*old_sys_getpgrp)(void);
	long (*old_sys_waitid)(int, pid_t, void *, int, void *);
	long (*old_sys_uname)(void *);
	long (*old_sys_rt_tgsigqueueinfo)(pid_t, pid_t, int, void *);
	long (*old_sys_rt_sigqueueinfo)(int, int, void *);
	long (*old_sys_prlimit64)(pid_t, unsigned int, void *, void *);
	long (*old_sys_ptrace)(long, pid_t, void *, void *);
	long (*old_sys_migrate_pages)(pid_t, unsigned long,
					unsigned long *, unsigned long *);
	long (*old_sys_move_pages)(pid_t, unsigned long, void **,
					int *, int *, int);
	long (*old_sys_fork)(void);
	long (*old_sys_vfork)(void);

	/* kernel functions */
	void (*old_do_debug)(struct pt_regs *, long);

	/* kernel data */
	void *die_chain;

	/* kernel API */
	int (*printk)(const char *, ...);
	int (*vprintk)(const char *, va_list);
	unsigned long (*_copy_from_user)(void *, const void *, unsigned int);
	unsigned long (*_copy_to_user)(void *, const void *, unsigned int);
	int (*register_die_notifier)(struct notifier_block *);
	int (*unregister_die_notifier)(struct notifier_block *);

};

extern struct kernel_syms ksyms;

int get_kernel_syms(void);

#endif
