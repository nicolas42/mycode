/*
Try this version first http://www.99-bottles-of-beer.net/language-c-820.html.
The code above has a read write interface and registers as a linux device and can handle multiple instantiations.

The code below is untested.  

Kernel modules do not have a main() function; instead, they use init_module() and cleanup_module() for initialization and cleanup respectively. It uses printk() instead of printf() since kernel modules operate in kernel space where standard C library functions aren't available.
*/


#include <linux/module.h>
#include <linux/kernel.h>

static int __init beer_song_init(void)
{
    int b;

    for (b = 99; b >= 3; b--) {
        printk(KERN_INFO "%d bottles of beer on the wall, %d bottles of beer.\n", b, b);
        printk(KERN_INFO "Take one down and pass it around, %d bottles of beer on the wall.\n\n", b - 1);
    }

    printk(KERN_INFO "2 bottles of beer on the wall, 2 bottles of beer.\n");
    printk(KERN_INFO "Take one down and pass it around, 1 bottle of beer on the wall\n\n");
    b--;

    printk(KERN_INFO "1 bottle of beer on the wall, 1 bottle of beer.\n");
    printk(KERN_INFO "Take one down and pass it around, no more bottles of beer on the wall\n\n");
    b--;

    printk(KERN_INFO "No more bottles of beer on the wall, no more bottles of beer.\n");
    printk(KERN_INFO "Go to the store and buy some more, 99 bottles of beer on the wall.\n\n");

    return 0;
}

static void __exit beer_song_exit(void)
{
    printk(KERN_INFO "Beer song module unloaded\n");
}

module_init(beer_song_init);
module_exit(beer_song_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A kernel module that prints the 99 Bottles of Beer song");
MODULE_VERSION("1.0");
