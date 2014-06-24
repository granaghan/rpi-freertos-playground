/**
 * BlueThunder Linker Script for the raspberry Pi!
 *
 *
 *
 **/
MEMORY
{
   RESERVED   (r)     : ORIGIN = 0x00000000, LENGTH = 32K
   INIT_RAM   (rwx)   : ORIGIN = 0x00008000, LENGTH = 32K
   RAM        (rwx)   : ORIGIN = 0x00010000, LENGTH = 128M
}

ENTRY(_start)

SECTIONS
{
    /*
    * Our init section allows us to place the bootstrap code at address 0x8000
    *
    * This is where the Graphics processor forces the ARM to start execution.
    * However the interrupt vector code remains at 0x0000, and so we must copy the correct
    * branch instructions to 0x0000 - 0x001C in order to get the processor to handle interrupts.
    *
    */
   .init :
   {
      KEEP(*(.init))
   } > INIT_RAM = 0

   .module_entries :
   {
      __module_entries_start = .;
      KEEP(*(.module_entries))
      KEEP(*(.module_entries.*))
      __module_entries_end = .;
      __module_entries_size = SIZEOF(.module_entries);
   } > INIT_RAM


   /* Place code in RAM. */
   .text :
   {
      *(.text)
   } > RAM

   /*
   * Next we put the data.
   */
   .data :
   {
      *(.data)
   } > RAM

   .bss :
   {
      __bss_start = .;
      *(.bss)
      *(.bss.*)
      __bss_end = .;
   } > RAM

   /* Global constructor array */
   .init_array ALIGN(4) :
   {
      _init_array_start = .;
      KEEP (*(.init_array*))
      _init_array_end = .;
   } > RAM

   /* No need for global destructors-- just reset! */

   /* No heap */


   /* Stack starts at top and grows down */
   _estack = ORIGIN(RAM) + LENGTH(RAM);
}

