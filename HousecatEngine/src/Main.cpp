#include "./Source.h"
#include "game/Game.h"
#include "editor/Editor.h"


int main(int argc, char* argv[]) {
    Source source;

    source.Initialize();
    source.Run();
    source.Destroy();

    //TODO: improve error handling, use Logger
    // initializer handling
    
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