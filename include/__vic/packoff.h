// Restore structures alignment turned off by packon.h
#ifndef __VIC_STRUCT_PACK_ENABLED
#error __vic/packoff.h without corresponging __vic/packon.h
#endif
#pragma pack(pop)
#undef __VIC_STRUCT_PACK_ENABLED
