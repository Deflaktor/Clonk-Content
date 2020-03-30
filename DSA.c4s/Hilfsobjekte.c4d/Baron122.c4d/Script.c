Initialize:
  SetAction("Los");
  return(1);

Test:
  if(FindObject(0,-180,-60,360,240,OCF_CrewMember())) SetAction("AbdiePost");
  return(1);

Start:
  SetGlobal(7,1);
  Message("Ihr hört eine Stimme:|Ihr seid weit gekommen, aber hier endet eure Reise! Jetzt kommt ein Zauberer, |der euch das Leben schwer macht!");
  Music("finalfight.mid");
  return(1);

Demon:
  SetLocal(1,1,FindObject(_GS8,-2000,-2000,4000,4000));

  while(SetVar(0,FindObject(_GS1,-400,-500,800,1000, 0, 0,0, NoContainer(), Var(0)))) 
    SetLocal(1,1,Var(0));

  return(1);