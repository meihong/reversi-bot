/**
 * @file rule.hpp
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date 2019-10-22
 */

#ifndef REVERSI_RULE_HPP
#define REVERSI_RULE_HPP

#include "table.hpp"

/// Use to indicate upward.
#define REVERSI_RULE_DIR_UP     -1
/// Use to indicate downward.
#define REVERSI_RULE_DIR_DOWN    1
/// Use to indicate leftward.
#define REVERSI_RULE_DIR_LEFT   -1
/// Use to indicate rightward.
#define REVERSI_RULE_DIR_RIGHT   1
/// Use not to indicate any direction.
#define REVERSI_RULE_DIR_NEUTRAL 0

namespace Reversi
{
  /**
   * Reversi::Rule implements fundamental rules of reversi.
   *
   * @author Kenta ONISHI (kenta@0024s.com)
   * @date 2019-10-22
   */
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
