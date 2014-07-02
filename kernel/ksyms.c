#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <asm/unistd.h>

#include <ylsm/debug.h>
#include <ylsm/ksyms.h>
#include <ylsm/x86.h>

struct kernel_syms ksyms;

int get_kernel_syms(void)
{
	if (get_syscall_table_addr())
		return -1;

	if (get_ia32_syscall_table_addr())
		return -1;

	ksyms.old_sys_stat =
		(void *)ksyms.sys_call_table[__NR_stat];
	ksyms.old_sys_lstat =
		(void *)ksyms.sys_call_table[__NR_lstat];
	ksyms.old_sys_fstat =
		(void *)ksyms.sys_call_table[__NR_fstat];
	ksyms.old_sys_fstatat =
		(void *)ksyms.sys_call_table[__NR_newfstatat];
	ksyms.old_sys_chdir =
		(void *)ksyms.sys_call_table[__NR_chdir];
	ksyms.old_sys_open =
		(void *)ksyms.sys_call_table[__NR_open];
	ksyms.old_sys_getdents =
		(void *)ksyms.sys_call_table[__NR_getdents];
	ksyms.old_sys_getdents64 =
		(void *)ksyms.sys_call_table[__NR_getdents64];
	ksyms.old_sys_getpid =
		(void *)ksyms.sys_call_table[__NR_getpid];
	ksyms.old_sys_getppid =
		(void *)ksyms.sys_call_table[__NR_getppid];
	ksyms.old_sys_getpgrp =
		(void *)ksyms.sys_call_table[__NR_getpgrp];
	ksyms.old_sys_getpgid =
		(void *)ksyms.sys_call_table[__NR_getpgid];
	ksyms.old_sys_setpgid =
		(void *)ksyms.sys_call_table[__NR_setpgid];
	ksyms.old_sys_getsid =
		(void *)ksyms.sys_call_table[__NR_getsid];
	ksyms.old_sys_getpriority =
		(void *)ksyms.sys_call_table[__NR_getpriority];
	ksyms.old_sys_kill =
		(void *)ksyms.sys_call_table[__NR_kill];
	ksyms.old_sys_sched_setscheduler =
		(void *)ksyms.sys_call_table[__NR_sched_setscheduler];
	ksyms.old_sys_sched_setparam =
		(void *)ksyms.sys_call_table[__NR_sched_setparam];
	ksyms.old_sys_sched_getscheduler =
		(void *)ksyms.sys_call_table[__NR_sched_getscheduler];
	ksyms.old_sys_sched_getparam =
		(void *)ksyms.sys_call_table[__NR_sched_getparam];
	ksyms.old_sys_sched_setaffinity =
		(void *)ksyms.sys_call_table[__NR_sched_setaffinity];
	ksyms.old_sys_sched_getaffinity =
		(void *)ksyms.sys_call_table[__NR_sched_getaffinity];
	ksyms.old_sys_sched_rr_get_interval =
		(void *)ksyms.sys_call_table[__NR_sched_rr_get_interval];
	ksyms.old_sys_wait4 =
		(void *)ksyms.sys_call_table[__NR_wait4];
	ksyms.old_sys_get_robust_list =
		(void *)ksyms.sys_call_table[__NR_get_robust_list];
	ksyms.old_sys_exit =
		(void *)ksyms.sys_call_table[__NR_exit];
	ksyms.old_sys_exit_group =
		(void *)ksyms.sys_call_table[__NR_exit_group];
	ksyms.old_sys_uname =
		(void *)ksyms.sys_call_table[__NR_uname];
	ksyms.old_sys_waitid =
		(void *)ksyms.sys_call_table[__NR_waitid];
	ksyms.old_sys_rt_tgsigqueueinfo =
		(void *)ksyms.sys_call_table[__NR_rt_tgsigqueueinfo];
	ksyms.old_sys_rt_sigqueueinfo =
		(void *)ksyms.sys_call_table[__NR_rt_sigqueueinfo];
	ksyms.old_sys_prlimit64 =
		(void *)ksyms.sys_call_table[__NR_prlimit64];
	ksyms.old_sys_ptrace =
		(void *)ksyms.sys_call_table[__NR_ptrace];
	ksyms.old_sys_migrate_pages =
		(void *)ksyms.sys_call_table[__NR_migrate_pages];
	ksyms.old_sys_move_pages =
		(void *)ksyms.sys_call_table[__NR_move_pages];
	ksyms.old_sys_perf_event_open =
		(void *)ksyms.sys_call_table[__NR_perf_event_open];
	ksyms.old_sys_fork =
		(void *)ksyms.sys_call_table[__NR_fork];
	ksyms.old_sys_vfork =
		(void *)ksyms.sys_call_table[__NR_vfork];

	/* kernel data */
	ksyms.die_chain = (void *)COMPILE_TIME_DIE_CHAIN;

	/* kernel API */
	ksyms.printk = printk;
	ksyms.vprintk = vprintk;
	ksyms._copy_from_user = _copy_from_user;
	ksyms._copy_to_user = _copy_to_user;
	ksyms.register_die_notifier = register_die_notifier;
	ksyms.unregister_die_notifier = unregister_die_notifier;

	return 0;
}
