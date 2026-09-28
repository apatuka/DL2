// FUN_004a6964 @ 004a6964 size=47 sig=undefined FUN_004a6964() cc=unknown
// callers: FUN_0049d315,FUN_004a58ce,FUN_0048e530,FUN_004a43da,FUN_0048937d,FUN_004894d4,FUN_00495b28,FUN_00490bca,FUN_004988fc,FUN_00489406,FUN_00489481,FUN_004893b4,FUN_004a18c5,FUN_004a1c75,FUN_00489084,FUN_00489466,FUN_0049512a,FUN_004893dd,FUN_0049d27f,FUN_0049d1dd
// callees: 

char * FUN_004a6964(char *param_1,char *param_2)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  
  uVar2 = 0xffffffff;
  pcVar4 = param_2;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  pcVar4 = param_1;
  for (uVar3 = ~uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar4 = *(undefined4 *)param_2;
    param_2 = param_2 + 4;
    pcVar4 = pcVar4 + 4;
  }
  for (uVar2 = ~uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar4 = *param_2;
    param_2 = param_2 + 1;
    pcVar4 = pcVar4 + 1;
  }
  return param_1;
}

