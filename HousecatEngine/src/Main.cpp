#include "./Source.h"
#include "game/Game.h"
#include "editor/Editor.h"


//----------------------------------------------------//
//                    MAIN                            //
//     Entry point for the Housecat game engine.      //
// Manages the initial launch, directing to the game  //
//      or the editor based on user interaction.      //
//----------------------------------------------------//



int main(int argc, char* argv[]) {
    Source source;

    source.Initialize();
    source.Run();
    source.Destroy();
    
    //game launcher
    if (source.LaunchGame()) {
        Game game;

        game.Initialize();
        game.Run();
        game.Destroy();
    }
    //housecat editor launcher
    if (source.LaunchEditor()) {
        Editor editor;

        editor.Initialize();
        editor.Run();
        editor.Destroy();
    }

    return 0;
}