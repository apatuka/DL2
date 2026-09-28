// FUN_00453954 @ 00453954 size=227 sig=undefined FUN_00453954() cc=unknown
// callers: FUN_00453a38
// callees: FUN_00450f84,FUN_004480a8,FUN_004538b4,FUN_00447da4,FUN_00451180

uint FUN_00453954(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int local_14;
  uint local_10;
  int local_c;
  
  iVar4 = FUN_00450f84(param_1);
  local_c = 0;
  local_10 = 0xffffffff;
  local_14 = 1000;
  iVar2 = local_c;
  uVar3 = local_10;
  for (iVar1 = *(int *)(DAT_0057cdf8 + 0x74); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x44)) {
    local_10 = uVar3;
    local_c = iVar2;
    if (((((((&DAT_004faf87)[*(int *)(iVar1 + 4) * 0x24] == '\n') &&
           (*(char *)(iVar1 + 0x1d) != '\0')) &&
          (*(char *)(param_1 + 0x1e) != *(char *)(iVar1 + 0x1e))) &&
         ((iVar4 == 0 || (iVar5 = FUN_004538b4(iVar1), iVar5 == 0)))) &&
        ((uVar6 = FUN_00451180(param_1,*(undefined4 *)(iVar1 + 0x20),*(undefined4 *)(iVar1 + 0x24)),
         param_2 == 0 || (uVar7 = FUN_004480a8(param_1), uVar6 <= uVar7)))) &&
       ((local_10 = uVar6, local_c = iVar1, uVar3 <= uVar6 &&
        (local_10 = uVar3, local_c = iVar2, uVar6 == uVar3)))) {
      iVar5 = FUN_00447da4(iVar1);
      iVar5 = iVar5 - *(short *)(iVar1 + 0x32);
      if (iVar5 < local_14) {
        local_14 = iVar5;
        local_c = iVar1;
      }
    }
    iVar2 = local_c;
    uVar3 = local_10;
  }
  *(int *)(param_1 + 0x3c) = iVar2;
  DAT_0057e244 = uVar3;
  return uVar3;
}

