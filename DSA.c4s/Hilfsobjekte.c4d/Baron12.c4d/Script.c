Initialize:
  SetAction("Los");
  return(1);

Test:
  if(FindObject(0,-180,-60,360,240,OCF_CrewMember())) SetAction("AbdiePost");
  return(1);

Start:
  SetGlobal(7,1);
  Message("Ihr hört eine Stimme:|Ihr seid weit gekommen, aber hier endet eure Reise! Jetzt kommt, eine Horde Skelette");
  Music("finalfight.mid");
  return(1);

Demon:
CastObjects(_G02,20,2000);
  SetLocal(1,1,FindObject(FT35,-5000,-2500,10000,5000));
  RemoveObject();
  return(1);

WhileFight:
  while(SetVar(1,FindObject(WL3A,-500,-250,1000,500,0,"Dead")))  SetAction("Allesvonvorn");
  while(SetVar(2,FindObject(MA3A,-500,-250,1000,500,0,"Dead")))  SetAction("Allesvonvorn");
  while(SetVar(3,FindObject(KR3A,-500,-250,1000,500,0,"Dead")))  SetAction("Allesvonvorn");
  while(SetVar(4,FindObject(_G02,-500,-250,1000,500,0,"Dead")))  RemoveObject(Var(4));
  SetLocal(1,1,FindObject(FT35,-5000,-2500,10000,5000));
  Music("Ungewissheit.mid");
  Sound("Victory");
  RemoveObject();
  return(1);

Ende:
  SetGlobal(7,2);
  while(SetVar(1,FindObject(_S09,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_S09,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_S09,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  SetLocal(1,1,FindObject(FT35,-5000,-2500,10000,5000));
  Music("Ungewissheit.mid");
  Sound("Victory");
  RemoveObject();
  return(1);

Allesvonvorn2:
  while(SetVar(1,FindObject(_S09,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_S09,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_S09,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  while(SetVar(1,FindObject(_G02,-500,-250,1000,500)))  RemoveObject(Var(1));
  SetAction("Los");