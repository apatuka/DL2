// FUN_00437a3c @ 00437a3c size=657 sig=undefined FUN_00437a3c() cc=unknown
// callers: WriteUnitData
// callees: lstrcatA,FUN_00447b30,FUN_004ae068,FUN_00447b78,FUN_00447190,sprintf,FUN_004ae230,FUN_0049eb44,wsprintfA,FUN_00447b9c,lstrcpyA,FUN_00447b54,FUN_00447b0c
// strings: \"Ultra Slow\"|\" round/sec.\"|\" rounds/sec.\"|\"Does Not Shoot\"|\"%d.3 squares\"|\"%d.6 squares\"|\"%d square\"|\"%d squares\"|\"Does Not Move\"|\"point\"|\"points\"|\"%d %s\"|\"credit\"|\"credits\"

void FUN_00437a3c(int param_1)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined *puVar6;
  CHAR *pCVar7;
  CHAR *pCVar8;
  CHAR *pCVar9;
  undefined8 uVar10;
  undefined1 local_180 [256];
  CHAR local_80 [20];
  CHAR local_6c [20];
  CHAR local_58 [20];
  CHAR local_44 [20];
  CHAR local_30 [20];
  int local_1c [3];
  int local_10 [3];
  
  iVar2 = FUN_00447b54();
  local_10[2] = iVar2 + 1;
  local_10[1] = 7;
  if (iVar2 + 1 < 8) {
    piVar3 = local_10 + 2;
  }
  else {
    piVar3 = local_10 + 1;
  }
  local_10[0] = 0;
  if (*piVar3 < 0) {
    piVar3 = local_10;
  }
  lstrcpyA(local_30,(&PTR_s_Does_Not_Move_00509a64)[*piVar3]);
  iVar2 = FUN_00447b9c();
  local_1c[2] = iVar2 + 1;
  local_1c[1] = 9;
  if (iVar2 + 1 < 10) {
    piVar3 = local_1c + 2;
  }
  else {
    piVar3 = local_1c + 1;
  }
  local_1c[0] = 0;
  if (*piVar3 < 0) {
    piVar3 = local_1c;
  }
  iVar2 = *piVar3;
  lstrcpyA(local_44,(&PTR_s_Does_Not_Shoot_00509a84)[iVar2]);
  if (iVar2 == 1) {
    lstrcatA(local_44,PTR_s_round_sec__00509aac);
  }
  else if (1 < iVar2) {
    lstrcatA(local_44,PTR_s_rounds_sec__00509ab0);
  }
  iVar2 = FUN_00447b78();
  FUN_004ae230((double)iVar2);
  iVar2 = FUN_004ae068();
  if (iVar2 == 0) {
    wsprintfA(local_58,PTR_s_Does_Not_Shoot_00509ab4);
  }
  else if (iVar2 % 3 == 1) {
    wsprintfA(local_58,PTR_s__d_3_squares_00509ab8);
  }
  else if (iVar2 % 3 == 2) {
    wsprintfA(local_58,PTR_s__d_6_squares_00509abc);
  }
  else if (iVar2 == 3) {
    wsprintfA(local_58,PTR_s__d_square_00509ac0);
  }
  else {
    wsprintfA(local_58,PTR_s__d_squares_00509ac4);
  }
  cVar1 = FUN_00447190();
  if (cVar1 == 0) {
    wsprintfA(local_6c,PTR_s_Does_Not_Move_00509ac8);
  }
  else {
    wsprintfA(local_6c,s__d__s_004c473c,(int)cVar1);
  }
  iVar2 = (int)(char)(&DAT_004faf8a)[*(char *)(param_1 + 6) * 0x24];
  if (iVar2 == 0) {
    wsprintfA(local_80,PTR_DAT_00509ad4);
  }
  else {
    puVar6 = PTR_s_credits_00509adc;
    if (iVar2 == 1) {
      puVar6 = PTR_s_credit_00509ad8;
    }
    wsprintfA(local_80,s__d__s_004c473c,iVar2,puVar6);
  }
  uVar10 = CONCAT44(local_80,local_6c);
  pCVar9 = local_58;
  pCVar8 = local_44;
  pCVar7 = local_30;
  uVar4 = FUN_00447b30(param_1);
  uVar5 = FUN_00447b0c(param_1);
  sprintf(local_180,&DAT_00559341,uVar5,uVar4,pCVar7,pCVar8,pCVar9,uVar10);
  FUN_0049eb44(DAT_004c46b4,0xe,1,0xf,0,local_180);
  return;
}

