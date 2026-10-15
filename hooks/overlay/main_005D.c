__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_AddExpAndEVs_0x238(void) {
    __asm__ volatile (
        "MOV R0,R4\n\t"         // R0=>calcExpWork
        "LDR R1,[SP,#0x14]\n\t" // R1=>partyMonLevel
        "BL ExperienceGainCap\n\t"
    );
}
