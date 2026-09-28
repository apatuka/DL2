// FUN_00401440 @ 00401440 size=277 sig=undefined FUN_00401440() cc=unknown
// callers: FUN_0040c578,FUN_0040ecec,FUN_0040b644,FUN_0040f700,FUN_0040c538,FUN_0040db74,FUN_0040ec50,FUN_0040f154
// callees: FUN_004726cc,FUN_00416ca4,FUN_00401320,FUN_004013ec

undefined4 FUN_00401440(int param_1,int param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = FUN_004013ec((int)*(char *)(param_1 + 8),param_2);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = FUN_004726cc(*(undefined4 *)(param_1 + 0x38),param_2,(int)*(char *)(param_1 + 8));
  if ((iVar2 < 3) || (iVar3 = FUN_00416ca4(param_1), iVar3 != 0)) {
    if ((&DAT_004faf8d)[*(char *)(param_1 + 6) * 0x24] == '\x03') {
      iVar2 = FUN_00401320(param_1,param_2);
      if (iVar2 != 0) {
        return 1;
      }
    }
    else {
      if (((iVar2 < 2) || (iVar3 = FUN_00416ca4(param_1), iVar3 != 0)) &&
         (*(char *)(*(int *)(param_1 + 0x38) + 0x22) == *(char *)(param_2 + 0x22))) {
        return 1;
      }
      if (((iVar2 < 3) && ((&DAT_004faf8d)[*(char *)(param_1 + 6) * 0x24] == '\x01')) &&
         (*(char *)(param_2 + 0x21) != '\0')) {
        bVar1 = *(byte *)(*(int *)(param_1 + 0x38) + 0x22);
        if (((bVar1 == *(byte *)(param_2 + 0x22)) ||
            ((1 << (*(byte *)(param_2 + 0x22) & 0x1f) &
             *(uint *)((int)&DAT_0055a82c + (char)bVar1 * 0x1a2)) != 0)) && (param_3 != 0)) {
          return 1;
        }
      }
      if ((&DAT_004faf8d)[*(char *)(param_1 + 6) * 0x24] == '\x06') {
        return 1;
      }
    }
  }
  return 0;
}

