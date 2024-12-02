function onClick()
    print("Script: onClick")
    local gameobject = findGameObjectByName("HelloWorld")

    if (not gameobject) then 
        print("Script: gameobject could not be found")
        return
    end

    gameobject:setText("CLICKED!")
end