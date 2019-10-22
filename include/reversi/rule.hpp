#ifndef REVERSI_RULE_H
#define REVERSI_RULE_H

#include "table.hpp"

#define REVERSI_RULE_DIR_UP     -1
#define REVERSI_RULE_DIR_DOWN    1
#define REVERSI_RULE_DIR_LEFT   -1
#define REVERSI_RULE_DIR_RIGHT   1
#define REVERSI_RULE_DIR_NEUTRAL 0

namespace Reversi
{
  class Rule
  {
  public:
    Reversi::Table table;
    Rule(void);
    bool set(unsigned int, unsigned int);
    int count_potential(unsigned int, unsigned int, unsigned int);
    unsigned int get_current_turn(void);
    unsigned int get_counterpart(void);

  private:
    unsigned int   turn;

    int _count(unsigned int, unsigned int, unsigned int, bool);
    unsigned int _count_by_dir(unsigned int, unsigned int, int, int, unsigned int);
    void _change(unsigned int, unsigned int, int, int, unsigned int);
  };
}

#endif // REVERSI_RULE_HPP
