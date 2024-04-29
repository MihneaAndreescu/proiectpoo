#include "GameEngine.h"
#include <Helper.h>
//////////////////////////////////////////////////////////////////////
/// NOTE: this include is needed for environment-specific fixes     //
/// You can remove this include and the call from main              //
/// if you have tested on all environments, and it works without it //
#include "env_fixes.h"                                              //
//////////////////////////////////////////////////////////////////////
int main() {
    init_threads();
    Helper helper;
    helper.help();
    GameEngine& engine = GameEngine::getInstance();
    engine.gameLoop();
    return 0;
}