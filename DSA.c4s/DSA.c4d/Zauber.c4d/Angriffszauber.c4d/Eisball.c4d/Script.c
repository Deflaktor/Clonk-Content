//von major}

#strict

public func Activate(ziel)
{
Sound("Magic1");
CreateObject(_FSE,0,0,-1)->Activate(ziel);
return(RemoveObject());}


         