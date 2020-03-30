Initialize:
  return(1);

Activate:
  SetLocal(0,Par(0));
  if(Not(Equal(GetID(Local(0)),MA3A))) Message("Nur Magier sind gebildet genug, um Alchimie zu betreiben!",this());
  if(Equal(GetID(Local(0)),MA3A)) Call("Hexenhuetli");
  return(1);

Hexenhuetli:
  CreateMenu(0,Local(0),this(),1);
  if(Contents())  AddMenuItem("Rezepte rausnehmen","DannHaltNicht",RZ3A,Local(0));
  if(FindContents(R13A))  AddMenuItem("Heiltrank C","Brauen",R13A,Local(0));
  if(FindContents(R23A))  AddMenuItem("Heiltrank E","Brauen",R23A,Local(0));
  if(FindContents(R33A))  AddMenuItem("Zaubertrank C","Brauen",R33A,Local(0));
  if(FindContents(R43A))  AddMenuItem("Zaubertrank F","Brauen",R43A,Local(0));
  if(FindContents(R53A))  AddMenuItem("Hylaier Feuer","Brauen",R53A,Local(0));
  if(FindContents(R63A))  AddMenuItem("Giftpfeil","Brauen",R63A,Local(0));
  if(FindContents(R73A))  AddMenuItem("Hylaier Pfeil","Brauen",R73A,Local(0));
  return(1);

Brauen:
  if(Equal(Par(0),R13A)) if(Enter(this(),SetLocal(3,ComposeContents(HC3A,Contained()), Contained())))  ObjectSetAction(Contained(),"Alchimie");
  if(Equal(Par(0),R23A)) if(Enter(this(),SetLocal(3,ComposeContents(HE3A,Contained()), Contained())))  ObjectSetAction(Contained(),"Alchimie");
  if(Equal(Par(0),R33A)) if(Enter(this(),SetLocal(3,ComposeContents(ZC3A,Contained()), Contained())))  ObjectSetAction(Contained(),"Alchimie");
  if(Equal(Par(0),R43A)) if(Enter(this(),SetLocal(3,ComposeContents(ZF3A,Contained()), Contained())))  ObjectSetAction(Contained(),"Alchimie");
  if(Equal(Par(0),R53A)) if(Enter(this(),SetLocal(3,ComposeContents(HB3A,Contained()), Contained())))  ObjectSetAction(Contained(),"Alchimie");
  if(Equal(Par(0),R63A)) if(Enter(this(),SetLocal(3,ComposeContents(P33A,Contained()), Contained())))  ObjectSetAction(Contained(),"Alchimie");
  if(Equal(Par(0),R73A)) if(Enter(this(),SetLocal(3,ComposeContents(P23A,Contained()), Contained())))  ObjectSetAction(Contained(),"Alchimie");
  return(1);


DannHaltNicht:
  while(Contents())  Exit(Contents());
  Sound("Paper*");
  return(1);

AlleNull:
  SetLocal(0,0);
  SetLocal(1,0);
  SetLocal(2,0);
  SetLocal(3,0);
  SetLocal(4,0);
  SetLocal(5,0);
  SetLocal(6,0);
  SetLocal(7,0);
  SetLocal(8,0);
  SetLocal(9,0);
  return(1);