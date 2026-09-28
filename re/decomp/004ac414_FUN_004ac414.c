// FUN_004ac414 @ 004ac414 size=183 sig=undefined FUN_004ac414() cc=unknown
// callers: FUN_004ac4cc
// callees: memcpy,FUN_004a67a8

/* WARNING: Type propagation algorithm not settling */

int FUN_004ac414(int param_1,int *param_2,undefined1 *param_3,int param_4)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  int iVar6;
  int local_14;
  
  iVar1 = *param_2;
  *param_2 = 0;
  local_14 = 0;
  puVar5 = param_3;
  iVar6 = param_1;
  while( true ) {
    puVar4 = (undefined1 *)(param_1 + (iVar1 - iVar6));
    iVar2 = FUN_004a67a8(iVar6,10,puVar4);
    if (iVar2 != 0) {
      puVar4 = (undefined1 *)(iVar2 - iVar6);
    }
    puVar3 = param_3 + (param_4 - (int)puVar5);
    if (puVar3 < puVar4) break;
    memcpy(puVar5,iVar6,puVar4);
    puVar5 = puVar5 + (int)puVar4;
    if ((iVar2 == 0) || ((int)(param_3 + (param_4 - (int)puVar5)) < 2)) {
      *param_2 = (int)(puVar4 + *param_2);
LAB_004ac4c4:
      return local_14 + (int)puVar4;
    }
    *puVar5 = 0xd;
    puVar5[1] = 10;
    puVar5 = puVar5 + 2;
    local_14 = local_14 + (int)(puVar4 + 2);
    iVar6 = iVar6 + (int)(puVar4 + 1);
    *param_2 = (int)(puVar4 + 1 + *param_2);
  }
  memcpy(puVar5,iVar6,puVar3);
  *param_2 = (int)(puVar3 + *param_2);
  puVar4 = puVar3;
  goto LAB_004ac4c4;
}

