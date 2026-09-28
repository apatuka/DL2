// FUN_00411808 @ 00411808 size=390 sig=undefined FUN_00411808() cc=unknown
// callers: FUN_00411ab0,FUN_00411b54
// callees: GlobalUnlock,FUN_0048d07b,FUN_0049b268,FUN_0048c3f4,FUN_0048d76a,GlobalLock,FUN_0048c2c5,FUN_004989ed,FUN_0048c28d

int * FUN_00411808(undefined4 param_1,int param_2)

{
  undefined1 *puVar1;
  int iVar2;
  int *piVar3;
  HGLOBAL hMem;
  LPVOID pvVar4;
  int iVar5;
  int iVar6;
  undefined1 *puVar7;
  int iVar8;
  undefined1 *puVar9;
  int iVar10;
  int iVar11;
  
  if (*(short *)(param_2 + 0x1c) == 8) {
    piVar3 = (int *)FUN_0048c28d(200,200,0x10);
    if (piVar3 == (int *)0x0) {
      piVar3 = (int *)0x0;
    }
    else {
      hMem = (HGLOBAL)FUN_0048d76a(0x100,0);
      pvVar4 = GlobalLock(hMem);
      if (pvVar4 == (LPVOID)0x0) {
        GlobalUnlock(hMem);
        FUN_004989ed(hMem);
        FUN_0048d07b(piVar3);
        piVar3 = (int *)0x0;
      }
      else {
        iVar5 = 0;
        puVar9 = (undefined1 *)((int)pvVar4 + 10);
        puVar7 = (undefined1 *)(param_2 + 0x36);
        do {
          iVar5 = iVar5 + 1;
          *puVar9 = *puVar7;
          puVar9[-2] = puVar7[2];
          puVar1 = puVar7 + 1;
          puVar7 = puVar7 + 4;
          puVar9[-1] = *puVar1;
          puVar9[1] = 1;
          puVar9 = puVar9 + 4;
        } while (iVar5 < 0x100);
        if (*(short *)((int)piVar3 + 0x26) == 2) {
          FUN_0049b268(pvVar4,1);
        }
        else {
          FUN_0049b268(pvVar4,2);
        }
        iVar5 = FUN_0048c2c5(piVar3);
        if (iVar5 == 0) {
          GlobalUnlock(hMem);
          FUN_004989ed(hMem);
          FUN_0048d07b(piVar3);
          piVar3 = (int *)0x0;
        }
        else {
          iVar5 = *piVar3;
          iVar6 = 0;
          do {
            iVar11 = 0;
            iVar8 = iVar5;
            iVar10 = param_2 + 0x436;
            do {
              iVar11 = iVar11 + 1;
              iVar2 = iVar10 + -200;
              iVar10 = iVar10 + 1;
              *(short *)(iVar8 + (piVar3[4] * iVar6 & 0xfffffffeU)) =
                   (short)*(undefined4 *)
                           ((int)pvVar4 + (uint)*(byte *)(iVar2 + (200 - iVar6) * 200) * 2 + 8);
              iVar8 = iVar8 + 2;
            } while (iVar11 < 200);
            iVar6 = iVar6 + 1;
          } while (iVar6 < 200);
          GlobalUnlock(hMem);
          FUN_004989ed(hMem);
          FUN_0048c3f4(piVar3);
        }
      }
    }
  }
  else {
    piVar3 = (int *)0x0;
  }
  return piVar3;
}

