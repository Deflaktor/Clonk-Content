Initialize:
  SetAction("Los");
  return(1);

Test:
  if(FindObject(0,-180,-60,360,240,OCF_CrewMember())) SetAction("AbdiePost");
  return(1);

Start:
  SetGlobal(7,1);
  Message("Ihr hört eine Stimme:|Ihr seid weit gekommen, aber nun ist es Zeit,| dass ich euch persönlich Einhalt gebiete!");
  Music("finalfight.mid");
  return(1);

Demon:
  SetLocal(1,CreateObject(_BAR,-150,30));
  CreateObject(KS3A);
  CreateObject(KS3A);
  return(1);

WhileFight:
  if(SetVar(1,FindObject(WL3A,-180,-60,360,240,0,"Dead")))  RemoveObject(Var(1));
  if(SetVar(2,FindObject(MA3A,-180,-60,360,240,0,"Dead")))  RemoveObject(Var(2));
  if(SetVar(3,FindObject(KR3A,-180,-60,360,240,0,"Dead")))  RemoveObject(Var(3));
  SetLocal(2,GetX(Local(1)));
  SetLocal(3,GetY(Local(1)));
  if(Not(Local(1))) Call("Ende");
  return(1);

Ende:
  while(SetVar(1,FindObject(KB3A,-220,-80,450,280))) RemoveObject(Var(1));
  while(SetVar(2,FindObject(KA3A,-220,-80,450,280))) RemoveObject(Var(2));
  while(SetVar(3,FindObject(KS3A,-220,-80,450,280))) RemoveObject(Var(3));

  while(SetVar(4,FindObject(KT3A,-220,-80,450,280))) RemoveObject(Var(4));
  SetGlobal(7,2);
  CreateObject(_ABS);
  Music();
  Sound("Victory");
  RemoveObject();
  return(1);