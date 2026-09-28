// FUN_004a52db @ 004a52db size=467 sig=undefined FUN_004a52db() cc=unknown
// callers: 
// callees: GlobalUnlock,FUN_0048d391,FUN_0048c3f4,FUN_004906e3,FUN_00499f98,FUN_0048c2c5,FUN_0048c4eb,FUN_0048d1a2,FUN_0048c28d,FUN_0048d76a,FUN_0048fe90,GlobalLock,FUN_0048fee9,FUN_0048c62f,FUN_0048d13d,FUN_0048d1eb

int FUN_004a52db(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5,
                int param_6,undefined4 param_7)

{
  ushort *puVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  HGLOBAL hMem;
  undefined2 *puVar6;
  int iVar7;
  undefined1 local_28 [2];
  short local_26;
  short local_24;
  short local_22;
  ushort local_20;
  short local_14;
  int local_c;
  undefined4 local_8;
  
  iVar7 = 0;
  if (param_5 == 2) {
    if (*(int *)(param_4 + 0x1c) != 0) {
      if (*(int *)(param_4 + 0x24) == 2) {
        iVar7 = *(int *)(param_4 + 0x1c);
        puVar1 = (ushort *)(iVar7 + 0x28);
        *puVar1 = *puVar1 & 0xfff7;
        FUN_0048d13d(iVar7);
        FUN_0048fe90(param_4);
        iVar7 = 1;
      }
      else {
        iVar7 = FUN_0048fee9(param_1,param_2,param_3,param_4,2,param_6,param_7);
      }
    }
  }
  else if (param_5 == 3) {
    if (param_6 == 2) {
      iVar2 = FUN_004906e3(param_1,*(undefined4 *)(param_4 + 0x14),0x1a,local_28);
      if (iVar2 == 0) {
        uVar3 = FUN_0048d1eb();
        local_8 = FUN_0048d1a2(uVar3 & 0xfffffffc | 1);
        uVar4 = FUN_00499f98(((int)(short)local_20 & 3U) + 1);
        puVar5 = (undefined4 *)FUN_0048c28d((int)local_24,(int)local_26,uVar4);
        if (puVar5 != (undefined4 *)0x0) {
          iVar2 = FUN_0048c2c5(puVar5);
          if (iVar2 != 0) {
            local_c = (int)local_22 * (int)local_26;
            iVar2 = FUN_004906e3(param_1,0xffffffff,local_c,*puVar5);
            if (iVar2 == 0) {
              *(ushort *)(puVar5 + 10) = *(ushort *)(puVar5 + 10) | 8;
              if (puVar5[3] == 0x10) {
                if ((local_20 & 0xc) == 0) {
                  *(undefined2 *)((int)puVar5 + 0x26) = 2;
                }
                else {
                  *(undefined2 *)((int)puVar5 + 0x26) = 3;
                }
              }
              FUN_0048c4eb(puVar5,(int)local_22);
              FUN_0048c62f(puVar5,DAT_0065e5ac);
              FUN_0048fe90(param_4);
              *(undefined4 **)(param_4 + 0x1c) = puVar5;
              *(undefined4 *)(param_4 + 0x24) = 2;
              if ((local_14 != 0) && (hMem = (HGLOBAL)FUN_0048d76a(0x100,0), hMem != (HGLOBAL)0x0))
              {
                puVar6 = GlobalLock(hMem);
                iVar7 = FUN_004906e3(param_1,0xffffffff,(short)puVar6[1] * 4 + 8,puVar6);
                if (iVar7 == 0) {
                  *puVar6 = 0;
                  FUN_0048d391(puVar5,hMem);
                }
                GlobalUnlock(hMem);
              }
              iVar7 = 1;
            }
            FUN_0048c3f4(puVar5);
          }
          if (iVar7 != 1) {
            FUN_0048d13d(puVar5);
          }
        }
        FUN_0048d1a2(local_8);
      }
    }
    else {
      iVar7 = FUN_0048fee9(param_1,param_2,param_3,param_4,3,param_6,param_7);
    }
  }
  else {
    iVar7 = 0;
  }
  return iVar7;
}

