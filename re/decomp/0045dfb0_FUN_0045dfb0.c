// FUN_0045dfb0 @ 0045dfb0 size=34 sig=undefined FUN_0045dfb0() cc=unknown
// callers: FUN_004467e8,FUN_00421fc4,FUN_00446b94,FUN_00432ad0,FUN_00441fa4,FUN_0042f680,FUN_00441eb8,FUN_004726cc,FUN_00446b3c,FUN_00432824,FUN_00426f20,FUN_00472844,FUN_00426cd8,FUN_0042f224,FUN_0045c384,CheckSubInfo,FUN_004226a0,FUN_00401670,FUN_00421fb4
// callees: 

void FUN_0045dfb0(uint param_1)

{
  undefined2 *puVar1;
  
  for (puVar1 = (undefined2 *)&DAT_005a43d0; puVar1 < &DAT_005f0410; puVar1 = puVar1 + 0x56e) {
    *(uint *)(puVar1 + 0xe) = *(uint *)(puVar1 + 0xe) & ~param_1;
  }
  return;
}

