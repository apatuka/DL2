// FindTresure @ 0046dca8 size=379 sig=undefined FindTresure() cc=unknown
// callers: FindArtifact
// callees: FUN_0046c9d8,FUN_00423690,FUN_0044e600
// strings: \"FindTresure\"

/* auto-named from string evidence: FindTresure */

undefined4 FindTresure(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  undefined4 local_c;
  int local_8;
  
  local_8 = 0;
  piVar6 = (int *)(param_1 + 0x154);
  do {
    if ((*piVar6 != 0) && ((cVar1 = *(char *)(*piVar6 + 4), cVar1 == '.' || (cVar1 == '/')))) {
      iVar2 = FUN_0044e600(*piVar6,1);
      iVar2 = *(int *)(&DAT_004b6578 + iVar2 * 4);
      if (iVar2 != -1) {
        switch(iVar2) {
        case 0:
          local_c = 1000;
          break;
        default:
          local_c = 200;
          break;
        case 2:
        case 4:
          local_c = 400;
          break;
        case 8:
        case 9:
          local_c = 100;
          break;
        case 10:
          local_c = 0x19;
        }
        iVar3 = FUN_0046c9d8(local_c,s_FindTresure_004d5c6e);
        if (iVar2 == 0) {
          (&DAT_0059f16c)[param_2 * 0xb6] = (&DAT_0059f16c)[param_2 * 0xb6] + iVar3;
          goto LAB_0046ddfa;
        }
        if ((&DAT_0059f166)[param_2 * 0x16c] == -1) {
          iVar5 = 1;
          break;
        }
        *(int *)(&DAT_005a440a + iVar2 * 4 + (short)(&DAT_0059f166)[param_2 * 0x16c] * 0xadc) =
             *(int *)(&DAT_005a440a + iVar2 * 4 + (short)(&DAT_0059f166)[param_2 * 0x16c] * 0xadc) +
             iVar3;
        goto LAB_0046ddfa;
      }
    }
    local_8 = local_8 + 1;
    piVar6 = piVar6 + 0xd;
    if (0x23 < local_8) {
      return 0;
    }
  } while( true );
LAB_0046ddef:
  if (DAT_004d5b18 < iVar5) {
LAB_0046ddfa:
    FUN_00423690(param_2,0x4f,param_1,iVar3,(&PTR_s_credits_00509098)[iVar2],0);
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) & 0xffffffef;
    return 1;
  }
  iVar4 = iVar5 * 0xadc;
  if ((((&DAT_005a444e)[iVar4] != '\0') && ((*(byte *)((int)&DAT_005a43ec + iVar4 + 1) & 1) == 0))
     && ((char)(&DAT_005a43f0)[iVar4] == DAT_0058f1f4)) {
    *(int *)(&DAT_005a440a + iVar2 * 4 + iVar4) =
         *(int *)(&DAT_005a440a + iVar2 * 4 + iVar4) + iVar3;
    goto LAB_0046ddfa;
  }
  iVar5 = iVar5 + 1;
  goto LAB_0046ddef;
}

