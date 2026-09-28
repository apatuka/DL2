// FUN_0046c49c @ 0046c49c size=652 sig=undefined FUN_0046c49c() cc=unknown
// callers: FUN_0046c7d4
// callees: FUN_0046c3fc,FUN_0046bce4,FUN_0046bdfc,FUN_00423690,FUN_0046c254,DoRiot,FUN_004237d0,FUN_0048514c,FUN_00483d58,FUN_0046c9d8
// strings: \"Revolt\"|\"Revolt2\"|\"Revolt3\"

void FUN_0046c49c(int param_1)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  int local_1c [3];
  int local_10;
  int local_c;
  undefined1 local_8 [4];
  
  if ((*(short *)(param_1 + 0x30) != 0) && (*(char *)(param_1 + 0x20) != -1)) {
    FUN_0046c3fc(param_1,local_8,&local_c);
    uVar3 = FUN_0046c9d8(100,s_Revolt_004d58bd);
    uVar4 = FUN_0046bce4(param_1);
    if (uVar3 < uVar4) {
      local_1c[2] = local_c * 100;
      local_1c[1] = 100;
      if (local_c * 100 < 100) {
        piVar6 = local_1c + 1;
      }
      else {
        piVar6 = local_1c + 2;
      }
      iVar5 = FUN_0046c9d8(*piVar6,s_Revolt2_004d58c4);
      local_10 = iVar5 + 1;
      local_1c[0] = *(short *)(param_1 + 0x30) + -0x32;
      if (iVar5 + 1 < local_1c[0]) {
        piVar6 = &local_10;
      }
      else {
        piVar6 = local_1c;
      }
      local_10 = *piVar6;
      iVar5 = FUN_0046c254(param_1);
      if ((0 < local_10) && (iVar5 != 0)) {
        cVar1 = (&DAT_0059f162)[*(char *)(param_1 + 0x20) * 0x2d8];
        iVar7 = FUN_0048514c((int)*(char *)(iVar5 + 0x20),(int)*(char *)(param_1 + 0x20));
        *(short *)(param_1 + 0x30) = *(short *)(param_1 + 0x30) - (short)local_10;
        *(short *)(iVar5 + 0x30) = *(short *)(iVar5 + 0x30) + (short)local_10;
        FUN_00423690((int)*(char *)(param_1 + 0x20),0x55,local_10,param_1,
                     (&PTR_s_ChCh_t_00509038)
                     [(char)(&DAT_0059f162)[*(char *)(iVar5 + 0x20) * 0x2d8]],0);
        FUN_00423690((int)*(char *)(iVar5 + 0x20),0x57,local_10,(&PTR_s_ChCh_t_00509038)[cVar1],
                     iVar5,0);
        if (iVar7 != 0) {
          FUN_004237d0((int)*(char *)(iVar5 + 0x20),0x56,(&PTR_s_ChCh_t_00509038)[cVar1],
                       *(undefined4 *)((int)&PTR_s_Nothing_004fbbc0 + iVar7 * 0x32),0,0,iVar7,0);
        }
        FUN_00483d58((int)*(char *)(iVar5 + 0x20),&DAT_004fbbac + iVar7 * 0x19);
      }
    }
    else {
      FUN_0046bdfc(param_1);
      if (DAT_0058f178 <= DAT_0058f150) {
        cVar1 = *(char *)(param_1 + 0x27);
        sVar2 = *(short *)(&DAT_00559f7a +
                          (char)(&DAT_0059f162)[*(char *)(param_1 + 0x20) * 0x2d8] * 2);
        if ((int)cVar1 < (int)sVar2) {
          uVar3 = FUN_0046c9d8(100,s_Revolt3_004d58cc);
          if (uVar3 < (uint)((int)sVar2 - (int)cVar1)) {
            FUN_00423690((int)*(char *)(param_1 + 0x20),0x54,param_1,local_c * 0x32,0,0);
            DoRiot(param_1,local_c * 0x32);
          }
          else {
            FUN_00423690((int)*(char *)(param_1 + 0x20),0x59,param_1,0,0,0);
          }
        }
        else if ((int)*(char *)(param_1 + 0x27) <
                 *(short *)(&DAT_00559f7a +
                           (char)(&DAT_0059f162)[*(char *)(param_1 + 0x20) * 0x2d8] * 2) * 2) {
          FUN_00423690((int)*(char *)(param_1 + 0x20),0x58,param_1,0,0,0);
        }
      }
    }
  }
  return;
}

