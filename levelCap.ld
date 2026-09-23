OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)

SECTIONS
{
    . = 0x02011168;
    .FUN_02011168 : {
        *(.FUN_02011168)
    }
    . = 0x21CB50C;
    .AddExpAndEVs_0x238 : {
        *(.AddExpAndEVs_0x238)
    }
}
