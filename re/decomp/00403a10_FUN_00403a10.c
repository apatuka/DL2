// FUN_00403a10 @ 00403a10 size=252 sig=undefined FUN_00403a10() cc=unknown
// callers: 
// callees: FUN_00403970,FUN_00476448,FUN_004021e0,FUN_0044c8ac,FUN_004023dc,FUN_004063c0

bool FUN_00403a10(undefined4 param_1,undefined4 param_2,int param_3,int param_4,undefined4 param_5)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined2 *puVar5;
  undefined *puVar6;
  
  iVar2 = FUN_00403970(param_1,param_2);
  for (puVar5 = &DAT_005f0410; puVar5 < &DAT_00645370; puVar5 = puVar5 + 0x91) {
    puVar5[9] = 0;
  }
  while ((iVar2 < param_3 && (iVar3 = FUN_004021e0(param_1,param_2,0,param_5), iVar3 != 0))) {
    puVar6 = &DAT_005a43d0 + *(short *)(iVar3 + 8) * 0xadc;
    uVar4 = FUN_004023dc(iVar3,param_2);
    iVar2 = FUN_0044c8ac(puVar6,iVar3,uVar4);
    if (iVar2 == 0) {
      bVar1 = false;
      if (((0x18 < param_4) && (iVar2 = FUN_004063c0(param_1,puVar6,param_5), iVar2 != 0)) &&
         (iVar2 = FUN_00476448(iVar2,puVar6,100,0,0xffffffff,0xffffffff), iVar2 != 0)) {
        uVar4 = FUN_004023dc(iVar3,param_2);
        FUN_0044c8ac(puVar6,iVar3,uVar4);
        param_4 = param_4 + -0x19;
        bVar1 = true;
      }
      if (!bVar1) {
        *(undefined2 *)(iVar3 + 0x12) = 1;
      }
    }
    iVar2 = FUN_00403970(param_1,param_2);
  }
  return param_3 <= iVar2;
}

