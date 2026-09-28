// FUN_00494c15 @ 00494c15 size=291 sig=undefined FUN_00494c15() cc=unknown
// callers: FUN_00494d38,FUN_00494e62
// callees: FUN_00494b06,FUN_00494449,FUN_00496a97,FUN_0048de03,FUN_00496945,FUN_0048e3f1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00494c15(void)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  int local_c;
  int local_8;
  
  bVar1 = false;
  if ((DAT_0051dc9c != 0) && (DAT_0065ec7c != 0)) {
    FUN_0048e3f1(&local_8,&local_c);
    if (((DAT_0065ecb0 != 0) &&
        (((1 < DAT_0051dc74 && (uVar2 = FUN_0048de03(), DAT_0051dc7c + _DAT_0051dc80 < uVar2)) &&
         (iVar3 = FUN_00496945(DAT_0065ecb0,DAT_0051dc78), iVar3 != 0)))) &&
       (iVar3 = FUN_00496a97(DAT_0065ecb0,DAT_0051dc78,0), iVar3 != 0)) {
      DAT_0051dc70 = DAT_0051dc70 + 1;
      if ((int)(uint)*(ushort *)(iVar3 + 0x1e) <= DAT_0051dc70) {
        DAT_0051dc70 = 0;
      }
      bVar1 = true;
      DAT_0051dc7c = uVar2;
    }
    if (((DAT_0065ec84 != local_8) || (DAT_0065ec88 != local_c)) || (bVar1)) {
      DAT_0065ec84 = local_8;
      DAT_0065ec88 = local_c;
      if (DAT_0051dc98 == 0) {
        FUN_00494b06();
        if (DAT_0051dc94 != (code *)0x0) {
          (*DAT_0051dc94)(DAT_0051dc90,2,DAT_0065ec84,DAT_0065ec88);
        }
      }
      else {
        FUN_00494449();
      }
      return 1;
    }
  }
  return 0;
}

