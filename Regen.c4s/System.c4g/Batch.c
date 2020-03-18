#strict
#appendto CLNK

// Local(0) = Zu erzeugende ID
// Local(1) = Objekt mithilfe dem man das verlangte Objekt erzeugen kann
// Local(2) = Objekt wohin es transportiert werden soll

public func ContextBatch(pCaller)
{
  [Beschaffen|Image=RSR3]
  var array, prod;
  array = InitializeArray();
  SetComDir(COMD_Stop());

  Local(0) = 0;
  Local(1) = 0;
  CreateMenu(CXCN, pCaller, this(), 1, "Keine Baupläne vorhanden");

  if (prod=IsProductedBy(WOOD, array))
    AddMenuItem("%s beschaffen","AcquireItMenu",WOOD,pCaller,0,prod);
  if (prod=IsProductedBy(SPHR, array))
    AddMenuItem("%s beschaffen","AcquireItMenu",SPHR,pCaller,0,prod);
  if (prod=IsProductedBy(SAND, array))
    AddMenuItem("%s beschaffen","AcquireItMenu",SAND,pCaller,0,prod);
  if (prod=IsProductedBy(METL, array))
    AddMenuItem("%s beschaffen","AcquireItMenu",METL,pCaller,0,prod);
  if (prod=IsProductedBy(GLAS, array))
    AddMenuItem("%s beschaffen","AcquireItMenu",GLAS,pCaller,0,prod);
  /*if (prod=IsProductedBy(GLAZ, array))
    AddMenuItem("%s beschaffen","AcquireItMenu",GLAZ,pCaller,0,prod);*/


  // Menü mit Bauplänen füllen
  var i = 0, def; SetVar(0,-1);
  while (def = GetPlrKnowledge(GetOwner(pCaller), 0, i++, C4D_Object()))
    if (prod=IsProductedBy(def, array))
      AddMenuItem("%s beschaffen","AcquireItMenu",def,pCaller,0,prod);

  RemoveObject(array);

  return(1);
}

InitializeArray:
  var array, i;
  array = CreateObject(ROCK,0,0,-1);
  // Nur Objekte mit typischen OCFs befragen damit's schneller geht.
  var obj, prod, ocf = OCF_Container () | OCF_Exclusive () | OCF_Entrance () | OCF_LineConstruct () | OCF_PowerConsumer () | OCF_Grab();
  while (obj = FindObject (0, -300, -60, 600, 80, ocf,0,0,0, obj))
    array->Local(i++)=obj;
  return(array);

IsProductedBy:
  var def = Par(0);
  var array = Par(1);
  var i = 0;
  var obj;
  while(obj=Local(i++, array)) {
    if(ObjectCall(obj, "IsProducerOf", this(), def))
      return(obj);
  }
  return(0);

AcquireItMenu:
  var select = 0;
  var count = 1;
  if(!Local(0)) {
    Local(0) = Par(0);
    Local(1) = Par(1);
  } else {
    select = Par(0);
    count = Par(1);
    if(select==2&&count<=1)
      select = 1;
  } 

  CreateMenu(CXCN, this(), this(), 1);  
  AddMenuItem(Format("%s %dx beschaffen", GetName(0, Local(0)), count),"AcquireItMenuContainer",Local(0),this(),count,count);
  AddMenuItem("Mehr","AcquireItMenuUp",SPIP,this(),0,count+1);
  if(count>1)
    AddMenuItem("Weniger","AcquireItMenuDown",DPIP,this(),0,count-1);

  SelectMenuItem(select, this());
  return(1);

AcquireItMenuUp:
  return(AcquireItMenu(1,Par(1)));

AcquireItMenuDown:
  return(AcquireItMenu(2,Par(1)));

AcquireItMenuContainer:
  var obj, prod, ocf = OCF_Container();
  var firstObj = Local(1);
  var count = Par(1);
  if(count==1) {
    Local(1)=this();
    return(AcquireIt(Local(0),1));
  }
  CreateMenu(CXCN, this(), this(), 1);
  AddMenuItem("Hierhin transportieren","AcquireItMenuContainerFinish",count,this(),0,firstObj,0,4,firstObj);
  while (obj = FindObject (0, -500, -60, 1000, 80, ocf,0,0,0, obj))
    if(obj != firstObj)
      AddMenuItem("Hierhin transportieren","AcquireItMenuContainerFinish",count,this(),0,obj,0,4,obj);
  return(1);

AcquireItMenuContainerFinish:
  Local(1)=Par(1);
  return(AcquireIt(Local(0),Par(0)));

AcquireIt:
  var count = Par(1);
  if(!count)
    return(AcquireItRepeatFailed());
  AddCommand(this(),"Call",this(),Par(0),count-1, 0, 0, "AcquireItRepeat");
  AddCommand(this(),"Wait",0,0,0,0,0,10);
  AddCommand(this(),"Put",Local(1),0,0,0, 0, Par(0));
  AddCommand(this(),"Acquire",0,0,0,Local(1), 0, Par(0));
  return(1);

AcquireItRepeatFailed:
  Local(0)=0;
  Local(1)=0;
  return(1);


AcquireItRepeat:
  return(AcquireIt(Par(1), Par(2)));