// FUN_0044b924 @ 0044b924 size=192 sig=undefined FUN_0044b924() cc=unknown
// callers: FUN_0044b9e4,FUN_00453568
// callees: FUN_004237d0,FUN_00423690

void FUN_0044b924(int param_1,undefined4 param_2)

{
  undefined *puVar1;
  int *piVar2;
  int iVar3;
  int local_c;
  int local_8;
  
  FUN_00423690(param_1,0x50,param_2,0,0,0);
  iVar3 = 0;
  do {
    if (param_1 != iVar3) {
      FUN_004237d0(iVar3,0x51,(&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_1 * 0x2d8]],
                   param_2,0,0,param_1,0);
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 7);
  for (puVar1 = &DAT_005a43d0; puVar1 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar1 = puVar1 + 0xadc) {
    if (param_1 == (char)puVar1[0x20]) {
      local_8 = (char)puVar1[0x27] + -0x14;
      local_c = 0;
      if ((char)puVar1[0x27] + -0x14 < 0) {
        piVar2 = &local_c;
      }
      else {
        piVar2 = &local_8;
      }
      puVar1[0x27] = (char)*piVar2;
    }
  }
  (&DAT_00657df8)[param_1 * 6] = (&DAT_00657df8)[param_1 * 6] + '\x01';
  return;
}

