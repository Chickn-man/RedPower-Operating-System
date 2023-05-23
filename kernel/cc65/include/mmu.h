#ifndef _MMU_H
#define _MMU_H

void __fastcall__ setMappedRedbusDev(unsigned char device);
unsigned char __fastcall__ getMappedRedbusDev();
void __fastcall__ setRedbusWindowOffset(unsigned short offset);
unsigned short getRedbusWindowOffset(void);
void enableRedbus(void);
void disableRedbus(void);
void __fastcall__ setMemoryMappedWindow(unsigned short offset);
unsigned short getMemoryMappedWindow(void);
void __fastcall__ setBrkAddress(void (*fcnAddr)(void));
void (*getBrkAddress(void))(void);
void __fastcall__ setPorAddress(void (*fcnAddr)(.void));
void (*getPorAddress(void))(void);
void _logRegisterA(void);

#endif