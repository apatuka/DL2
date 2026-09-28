// FUN_00453d9c @ 00453d9c size=299 sig=undefined FUN_00453d9c() cc=unknown
// callers: FUN_00454928
// callees: FUN_00447c2c,FUN_004480a8,FUN_00450da4,FUN_00451180,FUN_00453350,FUN_004412d4,FUN_00450f60,FUN_0043d630

void FUN_00453d9c(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int local_8;
  
  local_8 = 0;
  DAT_0057e244 = 9999;
  iVar1 = FUN_004480a8(param_1);
  for (iVar3 = *(int *)(DAT_0057cdf8 + 0x74); iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x44)) {
    if (((((&DAT_004faf8d)[*(int *)(iVar3 + 4) * 0x24] != '\x03') &&
         (iVar2 = FUN_00450f60(iVar3), iVar2 == 0)) && (*(char *)(iVar3 + 0x1d) != '\0')) &&
       (((*(char *)(param_1 + 0x1e) != *(char *)(iVar3 + 0x1e) &&
         (iVar2 = FUN_004412d4(*(undefined1 *)(iVar3 + 0x1e),*(undefined1 *)(param_1 + 0x1e),2),
         iVar2 == 0)) &&
        (iVar2 = FUN_00451180(param_1,*(undefined4 *)(iVar3 + 0x20),*(undefined4 *)(iVar3 + 0x24)),
        iVar2 <= iVar1)))) {
      iVar1 = iVar2;
      local_8 = iVar3;
    }
  }
  if ((local_8 != 0) &&
     ((*(char *)(local_8 + 9) != '\x04' || (iVar3 = FUN_00450da4(0x50), iVar3 == 0)))) {
    for (iVar3 = *(int *)(DAT_0057cdf8 + 0x74); iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x44)) {
      if (((((&DAT_004faf8d)[*(int *)(iVar3 + 4) * 0x24] != '\x03') &&
           (iVar2 = FUN_00450f60(iVar3), iVar2 == 0)) && (*(char *)(iVar3 + 0x1d) != '\0')) &&
         (iVar2 = FUN_00451180(param_1,*(undefined4 *)(iVar3 + 0x20),*(undefined4 *)(iVar3 + 0x24)),
         iVar2 <= iVar1)) {
        uVar5 = 0;
        uVar4 = FUN_00447c2c(param_1);
        FUN_00453350(iVar3,uVar4,uVar5);
        FUN_00453350(param_1,0x7f,0);
        if (DAT_004cf850 != 0) {
          FUN_0043d630(param_1);
        }
      }
    }
  }
  return;
}

