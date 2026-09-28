// FUN_0048f507 @ 0048f507 size=86 sig=undefined FUN_0048f507() cc=unknown
// callers: FUN_00493784
// callees: 

undefined8 FUN_0048f507(int param_1,int param_2,int param_3,ushort *param_4,int param_5)

{
  int iVar1;
  undefined4 in_EAX;
  int iVar2;
  undefined4 in_EDX;
  ushort *puVar3;
  
  iVar1 = (&DAT_0069ee30)[param_3];
  iVar2 = param_2;
  puVar3 = param_4;
  do {
    do {
      *param_4 = (&DAT_0065ee30)
                 [(&DAT_0067ee30)[*param_4] & 0xffc0 |
                  *(ushort *)(iVar1 + ((ushort)(&DAT_0067ee30)[*param_4] & 0x3f) * 2)];
      iVar2 = iVar2 + -1;
      param_4 = param_4 + 1;
    } while (iVar2 != 0);
    param_4 = (ushort *)((int)puVar3 + param_5);
    param_1 = param_1 + -1;
    iVar2 = param_2;
    puVar3 = param_4;
  } while (param_1 != 0);
  return CONCAT44(in_EDX,in_EAX);
}

