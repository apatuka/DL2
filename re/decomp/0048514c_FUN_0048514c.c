// FUN_0048514c @ 0048514c size=89 sig=undefined FUN_0048514c() cc=unknown
// callers: FUN_0046c49c,FUN_00485668
// callees: FUN_0046c9d8
// strings: \"Steal Tech\"

int FUN_0048514c(byte param_1,byte param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0046c9d8(0x30,s_Steal_Tech_005123c8);
  iVar2 = iVar1;
  do {
    if ((((int)(short)(&DAT_004fbbac)[iVar2 * 0x19] & 1 << (param_2 & 0x1f)) != 0) &&
       (((int)(short)(&DAT_004fbbac)[iVar2 * 0x19] & 1 << (param_1 & 0x1f)) == 0)) {
      return iVar2;
    }
    iVar2 = iVar2 + 1;
    if (0x2f < iVar2) {
      iVar2 = 0;
    }
  } while (iVar1 != iVar2);
  return 0;
}

