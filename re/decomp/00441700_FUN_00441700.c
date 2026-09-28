// FUN_00441700 @ 00441700 size=359 sig=undefined FUN_00441700() cc=unknown
// callers: NetMakePact,FUN_0047c730
// callees: FUN_004415d0,FUN_0044fe58,FUN_0044fe1c,FUN_004237d0

undefined4 FUN_00441700(int param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  char *local_8;
  
  if (DAT_004d5af4 == 0) {
    uVar1 = 0;
  }
  else {
    iVar2 = FUN_0044fe1c(1);
    if (((iVar2 != 0) && ((param_1 == DAT_0058f1f4 || (DAT_0058f1f4 == param_2)))) &&
       ((param_3 == 2 || (param_3 == 0x10)))) {
      FUN_0044fe58(1);
    }
    if ((param_3 & 1) != 0) {
      FUN_004415d0(param_1,param_2,2);
    }
    if ((param_3 & 2) != 0) {
      FUN_004415d0(param_1,param_2,1);
    }
    iVar2 = 0;
    (&DAT_0059f3da)[param_1 * 0xb6 + param_2] = (&DAT_0059f3da)[param_1 * 0xb6 + param_2] | param_3;
    (&DAT_0059f3da)[param_2 * 0xb6 + param_1] = (&DAT_0059f3da)[param_2 * 0xb6 + param_1] | param_3;
    (&DAT_0059f3f6)[param_1 * 0xb6 + param_2] = (&DAT_0059f3f6)[param_1 * 0xb6 + param_2] | param_3;
    (&DAT_0059f3f6)[param_2 * 0xb6 + param_1] = (&DAT_0059f3f6)[param_2 * 0xb6 + param_1] | param_3;
    local_8 = &DAT_0059f161;
    do {
      if ((('\x02' < *local_8) && (param_1 != iVar2)) && (param_2 != iVar2)) {
        FUN_004237d0(iVar2,0x72,(&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_1 * 0x2d8]],
                     (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_2 * 0x2d8]],
                     (int)*(char *)((int)&PTR_DAT_00508fb8 + param_3),0,param_1,param_2);
      }
      iVar2 = iVar2 + 1;
      local_8 = local_8 + 0x2d8;
    } while (iVar2 < 7);
    uVar1 = 1;
  }
  return uVar1;
}

