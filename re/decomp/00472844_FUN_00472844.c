// FUN_00472844 @ 00472844 size=304 sig=undefined FUN_00472844() cc=unknown
// callers: ConsumeFood,FUN_00472974
// callees: FUN_00472578,FUN_0045dfb0,FUN_00472730,FUN_00446b08

undefined4 FUN_00472844(undefined4 *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *local_8;
  
  DAT_00653434 = 0;
  local_8 = (undefined4 *)0x0;
  puVar2 = &DAT_005a4eac;
  do {
    if (&DAT_005a43d0 + DAT_004d5b18 * 0xadc < puVar2) {
      return 0;
    }
    if (((puVar2 != param_1) && (*(char *)(puVar2 + 8) == param_2)) &&
       (*(int *)((int)puVar2 + param_3 * 4 + 0xa7e) < *(int *)((int)puVar2 + param_3 * 4 + 0x3a))) {
      DAT_00653434 = 1;
      DAT_00653430 = 0;
      for (iVar3 = 0; (DAT_00653430 == 0 && (iVar3 <= param_4)); iVar3 = iVar3 + 1) {
        FUN_0045dfb0(0x2000 << (*(byte *)(puVar2 + 8) & 0x1f));
        FUN_00446b08(0,(int)*(char *)(puVar2 + 8));
        FUN_00472578(puVar2,param_1,1,(int)*(char *)(puVar2 + 8),iVar3);
        if ((DAT_00653430 != 0) && (param_4 = iVar3, local_8 = puVar2, iVar3 == 0))
        goto LAB_00472918;
      }
    }
    iVar3 = param_4;
    if (local_8 != (undefined4 *)0x0) {
LAB_00472918:
      iVar1 = FUN_00472730(iVar3,param_2);
      if (iVar1 <= (int)(&DAT_0059f16c)[param_2 * 0xb6]) {
        *(undefined4 **)((int)param_1 + 0xad6) = local_8;
        *(short *)((int)param_1 + 0xada) = (short)iVar1;
        return 1;
      }
    }
    puVar2 = puVar2 + 0x2b7;
    param_4 = iVar3;
  } while( true );
}

