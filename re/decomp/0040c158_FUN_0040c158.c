// FUN_0040c158 @ 0040c158 size=87 sig=undefined FUN_0040c158() cc=unknown
// callers: 
// callees: 

undefined4 FUN_0040c158(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = 0;
  do {
    iVar1 = 0;
    piVar2 = &DAT_005225c8 + iVar3 * 0x31 + param_1 * 0x992;
    do {
      if ((*piVar2 == param_2) && ((iVar3 != param_3 || (iVar1 != param_4)))) {
        return 1;
      }
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar1 < 0x10);
    iVar3 = iVar3 + 1;
    if (0x31 < iVar3) {
      return 0;
    }
  } while( true );
}

