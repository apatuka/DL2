// FUN_004538b4 @ 004538b4 size=74 sig=undefined FUN_004538b4() cc=unknown
// callers: FUN_00453ec8,FUN_00453954,FUN_00454690,FUN_00454160,FUN_004543f8
// callees: FUN_00450f84

undefined4 FUN_004538b4(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = *(int *)(DAT_0057cdf8 + 0x74);
  iVar3 = 0;
  do {
    if (iVar1 == 0) {
      return 0;
    }
    if ((param_1 == *(int *)(iVar1 + 0x3c)) && (iVar2 = FUN_00450f84(iVar1), iVar2 != 0)) {
      if (iVar3 == DAT_005649dc) {
        return 1;
      }
      iVar3 = iVar3 + 1;
    }
    iVar1 = *(int *)(iVar1 + 0x44);
  } while( true );
}

