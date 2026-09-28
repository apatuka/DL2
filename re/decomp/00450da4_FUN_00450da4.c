// FUN_00450da4 @ 00450da4 size=41 sig=undefined FUN_00450da4() cc=unknown
// callers: FUN_00456508,FUN_00455c88,FUN_00454928,FUN_00453d9c,FUN_00451550,FUN_00455a04,FUN_004526b0
// callees: 

uint FUN_00450da4(uint param_1)

{
  DAT_0057e240 = DAT_0057e240 * 0x41c64e6d + 0x3039;
  return (DAT_0057e240 >> 0x10) % param_1;
}

