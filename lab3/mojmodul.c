#include <linux/jiffies.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Jednostavan modul");
MODULE_AUTHOR("Matija Osrečki");

/* Ova funkcija se poziva prilikom učitavanja modula. */
int simple_init(void) {
    printk(KERN_INFO "Ucitavam modul\n");
    printk(KERN_INFO "%lu - %lu - %d\n", jiffies, jiffies / HZ, HZ);
    return 0;
}

/* Ova funkcija se poziva prilikom uklanjanja modula. */
void simple_exit(void) {
    printk(KERN_INFO "Uklanjanje jezgrenog modula\n");
    printk(KERN_INFO "%lu - %lu - %d\n", jiffies, jiffies / HZ, HZ);
}

/* Makro za registraciju modula: ulazna i izlazna točka. */
module_init(simple_init);
module_exit(simple_exit);
