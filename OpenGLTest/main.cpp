#include "loop/gameloop.hpp"
#include "loop/render_delegate.hpp"


int
main(int argc, char *argv[])
{
    SceneDelegate del;
    GameLoop loop(100, del);
    
    loop.start();
    
    return 0;
}