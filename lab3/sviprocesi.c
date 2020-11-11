#include <linux/kernel.h>
#include <linux/module.h>
//#include <linux/signal.h>
#include <linux/sched/signal.h>


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Modul za izlistanje svih procesa");
MODULE_AUTHOR("Matija Osrečki");

int simple_init(void) {
    printk(KERN_INFO "Ucitavam modul\n");
    struct task_struct *task = NULL;
    int task_count = 0;
    for_each_process(task) {
        printk(KERN_INFO "TASK: %s, pid: %d, state: %ld\n", task->comm, task->pid, task->state);
        printk(KERN_INFO "PARENT: %s, pid: %d, state: %ld\n\n", task->parent->comm, task->parent->pid,  task->parent->state);
        task_count++;
    }
    printk(KERN_INFO "Number of tasks: %d\n", task_count);
    return 0;
}

void simple_exit(void) {
}

module_init(simple_init);
module_exit(simple_exit);
