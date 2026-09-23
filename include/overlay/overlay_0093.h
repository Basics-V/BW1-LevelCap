#pragma once

// ROM-conditional addresses
#if   defined IRBO // Black American
    #define ADDR_AddExpAndEVs_0x238    0x021CB50C
#elif defined IRBI // Black Italian
    #define ADDR_AddExpAndEVs_0x238    0x021cb40c
#elif defined IRAI // White Italian
    #define ADDR_AddExpAndEVs_0x238    0x021cb42c
#else
    #error "That ROM does not have defined addresses yet!"
#endif

#ifndef __LINKER__
// ...
#endif // __LINKER__
