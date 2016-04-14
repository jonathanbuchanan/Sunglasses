require("math")
package.path = package.path .. ";../../Engine/Scripts/?.lua"
require("GLFWKeys")
require("vec3")

function hide()
    menu.set_visible(false)
    globalenvironment.setBoolean("doCameraInput", true)
    cursor_manager.disableCursor()
end

function show()
    menu.set_visible(true)
    globalenvironment.setBoolean("doCameraInput", false)
    plane.rotation.set_x(20.0);
    cursor_manager.enableCursor()
end

function close()
    window_manager.setWindowShouldClose()
end




function keyPressed(key)
    if key == keys.escape then
        escapePressed()
    end
end




function escapePressed()
    if menu.visible() == true then
        hide()
    elseif menu.visible() == false then
        show()
    end
end

function exitPressed()
    close()
end
