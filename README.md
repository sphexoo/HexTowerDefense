# HexTowerDefense

3D Tower Defense Game with hexagon based map. 
Using C++, OpenGl and GLFW.

## Controls:
   ### General:
    Mouse: Move Camera by getting close to screen edges.
    Middle Mouse Button: Rotate camera.
    Scroll Wheel: Zoom in / out
    R: Reset Camera View
    ESC: Pause Menue (depending on current screen)
   ### Level Editor:
    Mouse 1: Change Tile Type with multiple clicks onto the same tile (Green: Path, Red: Spawn, Gold: Target)
    Mouse 2: Reset Tile Type
   ### Running game:
    Mouse 1: Place tower / remove tower.

 ## Level Editor Readme:
  A valid path must have one Spawn and one Target connected by a variable number of path tiles (minimum is one tile). 
  If a path is not valid it cannot be saved. 
  After successfully creating and saving a path it is used as a level.
    
  
