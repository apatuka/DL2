// FUN_004055f8 @ 004055f8 size=259 sig=undefined FUN_004055f8() cc=unknown
// callers: 
// callees: FUN_0046ac44,FUN_0040552c,FUN_0046bdfc,FUN_004055c4

undefined4 FUN_004055f8(undefined4 param_1,int *param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined1 local_7c [80];
  int local_2c;
  int local_28;
  
  if ((param_2 != (int *)0x0) && (*param_2 == 3)) {
    iVar3 = param_2[7];
    if ((iVar3 != -1) &&
       ((param_2[8] != -1 && ((&DAT_005a4524)[iVar3 * 0x2b7 + param_2[8] * 0xd] != 0)))) {
      cVar1 = (&DAT_004f9dc3)
              [*(char *)((&DAT_005a4524)[iVar3 * 0x2b7 + param_2[8] * 0xd] + 4) * 0x32];
      if (cVar1 == '\x01') {
        FUN_0046ac44(local_7c,param_1);
        iVar3 = FUN_004055c4(0xc,1);
        if (iVar3 + local_2c < 0) {
          return 1;
        }
      }
      else if (cVar1 == '\x03') {
        FUN_0046ac44(local_7c,param_1);
        iVar3 = FUN_004055c4(0xf,1);
        if (iVar3 + local_28 < 0) {
          return 1;
        }
      }
      else if (cVar1 == '\x06') {
        iVar2 = FUN_0046bdfc(&DAT_005a43d0 + iVar3 * 0xadc);
        iVar3 = FUN_0040552c(&DAT_005a43d0 + iVar3 * 0xadc,7,1);
        if (iVar3 + iVar2 < 100) {
          return 1;
        }
      }
    }
  }
  return 0;
}

