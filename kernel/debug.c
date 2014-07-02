#include <ylsm/config.h>
#include <ylsm/debug.h>
#include <ylsm/hooks.h>
#include <ylsm/ksyms.h>
#include <ylsm/x86.h>

#ifdef ROOTKIT_DEBUG

#include <linux/kernel.h>

struct syscall_stat sys_stats[NR_SYSCALLS] = { {0} };

void __debug(const char *func, const char *fmt, ...)
{
        va_list args;

        va_start(args, fmt);
        ksyms.printk(KERN_DEBUG "ylsm: %s: ", func);
        ksyms.vprintk(fmt, args);
        ksyms.printk("\n");
        va_end(args);
}

void debug_rk(u64 *inodes, pid_t *pids)
{
	int i;
	unsigned long dr = 0;

	debug("hidden inodes");
	for (i = 0; i < MAX_HIDDEN_INODES; i++)
		if (inodes[i])
			ksyms.printk(KERN_DEBUG "%llu ", inodes[i]);

	debug("hidden pids");
	for (i = 0; i < MAX_HIDDEN_PIDS; i++)
		if (pids[i])
			ksyms.printk(KERN_DEBUG "%d ", pids[i]);

	for (i = 0; i <= 7; i++) {
		if (i == 4 || i == 5)
			continue;
		debug("accessing debug register %d", i);
		get_dr(i, &dr);
		debug("dr%d=%lx", i, dr);
	}

}

void debug_sys_stats(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(sys_stats); i++) {
		if (sys_stats[i].nr_call)
			debug("sys_stats[%d].nr_call = %d", i, sys_stats[i].nr_call);
	}
}

#else

void __debug(const char *func, const char *fmt, ...)
{
}

void debug_rk(u64 *inodes, pid_t *pid)
{
}

void debug_sys_stats(void)
{
}

#endif
