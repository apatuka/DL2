// FUN_0048f670 @ 0048f670 size=189 sig=undefined FUN_0048f670() cc=unknown
// callers: FUN_00493784
// callees: 

undefined8 FUN_0048f670(int param_1,int param_2,uint param_3,ushort *param_4,int param_5)

{
  int iVar1;
  undefined4 in_EAX;
  undefined4 in_EDX;
  ushort *puVar2;
  int local_8;
  
  iVar1 = DAT_0051d6e0;
  do {
    local_8 = param_2;
    puVar2 = param_4;
    do {
      *puVar2 = *(short *)(iVar1 + ((int)((*puVar2 & 0x7e0) - (param_3 & 0x7e0)) >> 5 & 0x1ffU) * 2)
                * 0x20 + (short)(param_3 & 0x7e0) & 0x7e0U |
                *(short *)(iVar1 + ((int)((*puVar2 & 0xf800) - (param_3 & 0xf800)) >> 0xb & 0x1ffU)
                                   * 2) * 0x800 + (short)(param_3 & 0xf800) |
                *(short *)(iVar1 + ((*puVar2 & 0x1f) - (param_3 & 0x1f) & 0x1ff) * 2) +
                (short)(param_3 & 0x1f) & 0x1fU;
      puVar2 = puVar2 + 1;
      local_8 = local_8 + -1;
    } while (local_8 != 0);
    param_4 = (ushort *)((int)param_4 + param_5);
    param_1 = param_1 + -1;
  } while (param_1 != 0);
  return CONCAT44(in_EDX,in_EAX);
}

