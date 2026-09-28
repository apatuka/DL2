// FUN_004a5a62 @ 004a5a62 size=119 sig=undefined FUN_004a5a62() cc=unknown
// callers: FUN_004a5b30
// callees: 

undefined4 FUN_004a5a62(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 local_c;
  undefined4 local_8;
  
  iVar2 = 0;
  while (((&DAT_0069f04c)[iVar2 * 4] == 0 ||
         (iVar1 = (*(code *)(&DAT_0069f058)[iVar2 * 4])
                            (&DAT_0069f04c + iVar2 * 4,param_1,param_2,1,&local_8,&local_c),
         iVar1 == 0))) {
    iVar2 = iVar2 + 1;
    if (9 < iVar2) {
      return 0;
    }
  }
  DAT_0069f024 = local_8;
  DAT_0069f028 = local_c;
  DAT_0069f02c = iVar2;
  return 1;
}

