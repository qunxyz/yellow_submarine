#include <linux/kernel.h>
#include <linux/kdebug.h>

#include <ylsm/debug.h>
#include <ylsm/ksyms.h>
#include <ylsm/x86.h>

int get_syscall_table_addr(void)
{
	int i;
	unsigned long system_call;
	unsigned char *op;

        rdmsrl(MSR_LSTAR, system_call);

	op = (unsigned char *)system_call;
	for (i = 0; i < 512; i++) {
		/* find "call *sys_call_table(,%rax,8)" opcode */
		if (op[0] == 0xff && op[1] == 0x14 && op[2] == 0xc5) {
			ksyms.sys_call_table = (unsigned long *)((*(u32 *)&op[3]) | ~0xffffffffUL);
			ksyms.sys_call_table_call = (void *)op;
			return 0;
		}
		op++;
	}

	debug("failed");
	return -1;
}

int get_ia32_syscall_table_addr(void)
{
	unsigned long ia32_sysenter_target, ia32_syscall;

	rdmsrl(MSR_IA32_SYSENTER_EIP, ia32_sysenter_target);
	ia32_syscall = get_idt_handler(0x80);

	return 0;
}
