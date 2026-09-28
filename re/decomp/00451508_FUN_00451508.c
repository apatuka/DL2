// FUN_00451508 @ 00451508 size=69 sig=undefined FUN_00451508() cc=unknown
// callers: FUN_00451550
// callees: FUN_00450de0,FUN_00450f84,FUN_00448314

undefined4 FUN_00451508(int *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  iVar2 = FUN_00450de0(param_1);
  if (iVar2 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = *(undefined4 *)(DAT_0057cdf8 + 4);
    uVar1 = *(undefined4 *)(*param_1 + 0x40);
    uVar4 = FUN_00450f84(param_1);
    uVar3 = FUN_00448314(uVar1,uVar3,uVar4);
    *(byte *)(DAT_0057cdf8 + 0x84) = *(byte *)(DAT_0057cdf8 + 0x84) | (byte)uVar3;
  }
  return uVar3;
}

