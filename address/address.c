#include <linux/init.h>             // Macros used to mark up functions e.g., __init __exit
#include <linux/module.h>           // Core header for loading LKMs into the kernel
#include <linux/kernel.h>           // Contains types, macros, functions for the kernel
#include <linux/ion_sunxi.h>
#include <asm/io.h>
 
MODULE_LICENSE("GPL");              ///< The license type -- this affects runtime behavior
MODULE_AUTHOR("Igor Boguslavsky");      ///< The author -- visible when you use modinfo
MODULE_DESCRIPTION("A simple Linux driver for the Orage Pi Zero");  ///< The description -- see modinfo
MODULE_VERSION("0.1");              ///< The version of the module
 
static char *name = "address";        ///< An example LKM argument -- default value is "world"
module_param(name, charp, S_IRUGO); ///< Param desc. charp = char ptr, S_IRUGO can be read/not changed
MODULE_PARM_DESC(name, "Memory Address / port to display");  ///< parameter description
 
typedef unsigned int __u32;

static __u32 *p;

#define SW_PORTC_IO_BASE  0x01c20800 	// dataregister 
#define PWM_CH_CTRL  0x01c21400 	// pwm control register
#define PWM_CH0_PERIOD  0x01c21404 	// pwm0 period register

/** @brief The LKM initialization function
 *  The static keyword restricts the visibility of the function to within this C file. The __init
 *  macro means that for a built-in driver (not a LKM) the function is only used at initialization
 *  time and that it can be discarded and its memory freed up after that point.
 *  @return returns 0 if successful
 */
static int __init opi0_init(void){
__u32 data;

   printk(KERN_INFO "Module %s has been initialized\n", name);

   p = ioremap ((__u32)SW_PORTC_IO_BASE, 4);

   data = *p;

   data |= (1<<20);	//set port PA5 to pwm (011)
   data |= (1<<21);
   data &= ~(1<<22);

   (*p) = data;

   printk(KERN_INFO "PORT C: %0#x\n", data); 

   iounmap (p);

   p = ioremap ((__u32)PWM_CH_CTRL, 4);
   
   data = *p;

   data |= (1<<4);                              //pwm channel 0 enable
   data |= (1<<5);                              //low - high level
   data |= (1<<6);                              //clock gating
   data |= (1<<8);                              //control register

   (*p) = data;

   printk(KERN_INFO "CTRL: %#0x\n", data); 

   iounmap (p);

   p = ioremap ((__u32)PWM_CH0_PERIOD, 4);

   // p += 0x04;
   
   data = 0x00010001;      //100Khz 50% duty 
    *(p) = data;
  
   printk(KERN_INFO "CADENCE: %0#x\n", data); 

   iounmap (p);

   printk(KERN_INFO "PWM set up OK.\n");

   return 0;
}
 
/** @brief The LKM cleanup function
 *  Similar to the initialization function, it is static. The __exit macro notifies that if this
 *  code is used for a built-in driver (not a LKM) that this function is not required.
 */
static void __exit opi0_exit(void){
   printk(KERN_INFO "Module %s exit\n", name);
}
 
/** @brief A module must use the module_init() module_exit() macros from linux/init.h, which
 *  identify the initialization function at insertion time and the cleanup function (as
 *  listed above)
 */
module_init(opi0_init);
module_exit(opi0_exit);

