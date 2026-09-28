// FUN_00443830 @ 00443830 size=143 sig=undefined FUN_00443830() cc=unknown
// callers: 
// callees: FUN_00481da0,InvalidateRect,FUN_00482320

void FUN_00443830(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  RECT *pRVar7;
  RECT local_20;
  
  iVar4 = DAT_004c5484;
  iVar3 = DAT_004c5480;
  iVar2 = DAT_004c547c;
  iVar1 = DAT_004c5478;
  FUN_00482320();
  FUN_00481da0(iVar1,iVar2,DAT_00657dec,DAT_00657df0,4,DAT_0058f1e0 == 0);
  puVar6 = &DAT_004c4b34;
  pRVar7 = &local_20;
  for (iVar5 = 4; iVar5 != 0; iVar5 = iVar5 + -1) {
    pRVar7->left = *puVar6;
    puVar6 = puVar6 + 1;
    pRVar7 = (RECT *)((int)pRVar7 + 4);
  }
  local_20.left = iVar1;
  local_20.top = iVar2;
  local_20.right = iVar3 + 1 + iVar1;
  local_20.bottom = iVar4 + 1 + iVar2;
  InvalidateRect(DAT_004d5974,&local_20,0);
  return;
}

