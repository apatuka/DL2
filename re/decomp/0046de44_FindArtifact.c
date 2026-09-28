// FindArtifact @ 0046de44 size=404 sig=undefined FindArtifact() cc=unknown
// callers: CheckDiscovery
// callees: FUN_00450150,FUN_0046c9d8,FindTresure,FUN_004412d4,FUN_004237d0,FUN_00483d58
// strings: \"FindArtifact\"|\"Metallurgy\"

/* auto-named from string evidence: FindArtifact */

void FindArtifact(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  short *psVar3;
  int iVar4;
  int iVar5;
  int local_c;
  
  uVar1 = 1 << ((byte)param_2 & 0x1f);
  local_c = FUN_0046c9d8(6,s_FindArtifact_004d5c7a);
  local_c = local_c + 1;
  iVar4 = 0;
  iVar2 = FindTresure(param_1,param_2);
  if (iVar2 == 0) {
    iVar2 = 1;
    do {
      psVar3 = &DAT_004fbbac + iVar2 * 0x19;
      if (((int)*psVar3 & uVar1) == 0) {
        local_c = local_c + -1;
        if (local_c < 1) {
          iVar5 = iVar2;
          if (iVar4 + 2 < (int)(short)(&DAT_004fbbcc)[iVar2 * 0x19]) goto LAB_0046deeb;
          break;
        }
      }
      else {
        iVar4 = (int)(short)(&DAT_004fbbcc)[iVar2 * 0x19];
      }
      iVar2 = iVar2 + 1;
      iVar5 = 0;
    } while (iVar2 < 0x30);
LAB_0046deff:
    if ((iVar5 != 0) &&
       (iVar2 = FUN_00450150((int)(char)(&DAT_0059f162)[param_2 * 0x2d8],iVar5), iVar2 != 0)) {
      FUN_004237d0(param_2,0x52,param_1,*(undefined4 *)((int)&PTR_s_Nothing_004fbbc0 + iVar5 * 0x32)
                   ,0,0,iVar5,0);
      FUN_00483d58(param_2,&DAT_004fbbac + iVar5 * 0x19);
      iVar2 = 0;
      do {
        if ((iVar2 != param_2) && (iVar4 = FUN_004412d4(param_2,iVar2,8), iVar4 != 0)) {
          FUN_004237d0(iVar2,0x38,*(undefined4 *)((int)&PTR_s_Nothing_004fbbc0 + iVar5 * 0x32),0,0,0
                       ,param_2,0);
          FUN_00483d58(iVar2,&DAT_004fbbac + iVar5 * 0x19);
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 < 7);
      *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) & 0xffffffef;
    }
  }
  return;
LAB_0046deeb:
  iVar5 = 0;
  if (psVar3 < (short *)((int)&DAT_004fbbac + 1)) goto LAB_0046deff;
  if ((((int)*psVar3 & uVar1) == 0) && ((int)psVar3[0x10] <= iVar4 + 2)) {
    iVar5 = (int)(psVar3 + -0x27ddd6) / 0x32;
    goto LAB_0046deff;
  }
  psVar3 = psVar3 + -0x19;
  goto LAB_0046deeb;
}

