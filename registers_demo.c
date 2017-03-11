static int __init opi0_init(void){
__u32 data32bit;
__u16 data16bit;
void __iomem *p;

  p = ioremap (SW_PORTC_IO_BASE, 2);
  data16bit = ioread16 (p);
  printk(KERN_INFO "physical addr: %#x, virtual addr: %#x, value: %#x\n",
    (__u32) SW_PORTC_IO_BASE, (__u32)p, data16bit);
  iounmap (p);

  p = ioremap (PWM_CH_CTRL, 4);
  data32bit = ioread32 (p);
  printk(KERN_INFO "physical addr: %#x, virtual addr: %#x, value: %#x\n",
    (__u32) PWM_CH_CTRL, (__u32)p, data32bit);
  iounmap (p);

  return 0;
}
