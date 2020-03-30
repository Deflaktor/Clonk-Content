Initialize:
  SetAction("Los");
  return(1);

Test:
  if(FindObject(0,-150,-200,300,300,OCF_CrewMember())) SetAction("AbdiePost");
  return(1);

Start:
  Music("finalfight");
  Message("Ihr hört eine Stimme:|Hier ist eure Reise zu Ende!");
  return(1);

Demon:
  SetLocal(1,CreateObject(HT3A));
  CreateObject(KA3A);
  CreateObject(KA3A);
  return(1);

WhileFight:
  SetLocal(2,GetX(Local(1)));
  SetLocal(3,GetY(Local(1)));
  if(Not(FindObject(HT3A,-285,-190,570,240))) Call("Ende");
  return(1);

Ende:
  SetPosition(0,0);
  Music();
  Sound("Victory");
  SetPosition(Local(2),Local(3),FindObject(MS3A,2170,150,200,200));
  SetGlobal(1,3);
  SetAction("Musik");
  return(1);

Weiter:
  Music("braveheart");
  RemoveObject();
  return(1);