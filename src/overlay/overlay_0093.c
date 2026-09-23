#include "ARM9.h"

__attribute__((naked, section(".AddExpAndEVs_0x238"), target("thumb")))
void AddExpAndEVs_0x238(void) {
    __asm__ volatile (
        ".thumb\n\t"
        "MOV R0,R4\n\t"         // R0=>calcExpWork
        "LDR R1,[SP,#0x14]\n\t" // R1=>partyMonLevel
        "BL FUN_02011168\n\t"
    );
}
