Scriptname FalconEngine Hidden

; Native functions connecting to FalconEngine.dll
Function SetShip(ObjectReference akShip) global native
Function AddCrew(Actor akActor) global native
Function ClearCrew() global native

; Usage Example
Function StartEngine(ObjectReference akShipRef) global
    if !akShipRef
        return
    endif
    
    SetShip(akShipRef)
    Debug.Notification("Falcon Engine: Ship Registered")
    
    Actor player = Game.GetPlayer()
    Actor teammate = player.GetTeammate()
    
    if teammate
        AddCrew(teammate)
        Debug.Notification("Falcon Engine: Crew Added")
    endif
EndFunction
