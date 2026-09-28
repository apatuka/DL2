// FUN_00456214 @ 00456214 size=67 sig=undefined FUN_00456214() cc=unknown
// callers: FUN_0045640c,FUN_00456258,FUN_00457624,FUN_004566c4,FUN_004568c8
// callees: 

ushort * FUN_00456214(ushort *param_1,int param_2)

{
  ushort *puVar1;
  uint uVar2;
  
  puVar1 = (ushort *)0x0;
  uVar2 = 0xffffffff;
  for (; param_1 != (ushort *)0x0; param_1 = *(ushort **)(param_1 + 0x2a)) {
    if ((param_2 < (int)(uint)*param_1) &&
       ((uVar2 == 0xffffffff || ((int)(uint)*param_1 < (int)uVar2)))) {
      uVar2 = (uint)*param_1;
      puVar1 = param_1;
    }
  }
  if (puVar1 == (ushort *)0x0) {
    puVar1 = (ushort *)0x0;
  }
  return puVar1;
}

