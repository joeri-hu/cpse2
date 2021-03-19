#include "game-controller.hpp"
#ifdef CLI
#  include "cmd-line-interface.hpp"
#  define interface cmd_line_interface
#elif GUI
#  include "graphical-interface.hpp"
#  define interface graphical_interface
#endif

auto main() -> int {
    interface user_interface;
    return game_controller{user_interface}.run();
}
