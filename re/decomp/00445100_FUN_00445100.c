// FUN_00445100 @ 00445100 size=86 sig=undefined FUN_00445100() cc=unknown
// callers: 
// callees: 

ushort * FUN_00445100(int param_1,int param_2)

{
  ushort *puVar1;
  
  puVar1 = DAT_00561a30;
  while( true ) {
    if (puVar1 == (ushort *)0x0) {
      return (ushort *)0x0;
    }
    if (((((*puVar1 & 0xc) == 0xc) && (-1 < param_1 - (short)puVar1[7])) &&
        (param_1 - (short)puVar1[7] < (int)(short)puVar1[9])) &&
       ((-1 < param_2 - (short)puVar1[8] && (param_2 - (short)puVar1[8] < (int)(short)puVar1[10]))))
    break;
    puVar1 = *(ushort **)(puVar1 + 0x1c);
  }
  return puVar1;
}

