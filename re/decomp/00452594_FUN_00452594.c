// FUN_00452594 @ 00452594 size=281 sig=undefined FUN_00452594() cc=unknown
// callers: FUN_004526b0
// callees: FUN_004b0a30,FUN_004b0b44,FUN_004412d4,FUN_004a68dc
// strings: \" and \"

undefined1 * FUN_00452594(int param_1,int param_2)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 local_2c [7];
  undefined4 *local_10;
  undefined4 *local_c;
  char *local_8;
  
  puVar1 = (undefined1 *)FUN_004b0b44(200);
  *puVar1 = 0;
  local_c = local_2c;
  puVar4 = &DAT_004d00ec;
  puVar5 = local_2c;
  for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
  }
  iVar6 = 0;
  local_8 = &DAT_0059f162;
  for (iVar3 = 0; iVar3 < DAT_004d5aec; iVar3 = iVar3 + 1) {
    if ((((1 << ((byte)iVar3 & 0x1f) & (uint)*(byte *)(DAT_0057cdf8 + 0xc)) != 0) &&
        (iVar3 != param_1)) &&
       (((iVar2 = FUN_004412d4(param_1,iVar3,2), param_2 != 0 && (iVar2 != 0)) ||
        ((param_2 == 0 && (iVar2 == 0)))))) {
      *local_c = (&PTR_s_ChCh_t_00509038)[*local_8];
      iVar6 = iVar6 + 1;
      local_c = local_c + 1;
    }
    local_8 = local_8 + 0x2d8;
  }
  if (iVar6 == 0) {
    FUN_004b0a30(puVar1);
    puVar1 = (undefined1 *)0x0;
  }
  else {
    FUN_004a68dc(puVar1,local_2c[0]);
    iVar3 = 1;
    local_10 = local_2c;
    if (1 < iVar6) {
      do {
        local_10 = local_10 + 1;
        if (iVar3 == iVar6 + -1) {
          FUN_004a68dc(puVar1,s_and_004d027c);
        }
        else {
          FUN_004a68dc(puVar1,&DAT_004d0282);
        }
        FUN_004a68dc(puVar1,*local_10);
        iVar3 = iVar3 + 1;
      } while (iVar3 < iVar6);
    }
  }
  return puVar1;
}

