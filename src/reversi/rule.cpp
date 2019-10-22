#include "table.hpp"
#include "rule.hpp"

Reversi::Rule::Rule(void)
{
  turn = REVERSI_PIECE_BLACK;
}

bool Reversi::Rule::set(unsigned int x, unsigned int y)
{
  if (_count(x, y, turn, false) > 0) {
    turn = turn == REVERSI_PIECE_WHITE ? REVERSI_PIECE_BLACK : REVERSI_PIECE_WHITE;
    return true;
  } else {
    return false;
  }
}

int Reversi::Rule::count_potential(unsigned int x, unsigned int y, unsigned int side)
{
  return _count(x, y, side, true);
}

unsigned int Reversi::Rule::get_current_turn(void)
{
  return turn;
}

unsigned int Reversi::Rule::get_counterpart(void)
{
  return turn == REVERSI_PIECE_WHITE ? REVERSI_PIECE_BLACK : REVERSI_PIECE_WHITE;
}

int Reversi::Rule::_count(unsigned int x, unsigned int y, unsigned int side, bool count_only)
{
  int count = 0;
  int change;

  if (!table.is_valid_cordinates(x, y) || table.get(x, y) != REVERSI_PIECE_VOID) {
    return -1;
  }

  for (int dx = REVERSI_RULE_DIR_UP; dx <= REVERSI_RULE_DIR_DOWN; dx++) {
    for (int dy = REVERSI_RULE_DIR_LEFT; dy <= REVERSI_RULE_DIR_RIGHT; dy++) {
      change = _count_by_dir(x, y, dx, dy, side);
      count += change;
      if (!count_only && change > 0) {
	_change(x, y, dx, dy, side);
      }
    }
  }

  return count;
}

unsigned int Reversi::Rule::_count_by_dir(unsigned int x, unsigned int y,
					  int direction_x, int direction_y,
					  unsigned int side)
{
  int examine_x, examine_y;
  unsigned int examinee;
  int count = 1,
      counterpart = side == REVERSI_PIECE_WHITE ? REVERSI_PIECE_BLACK : REVERSI_PIECE_WHITE;

  examine_x = (signed int)x + direction_x * 2;
  examine_y = (signed int)y + direction_y * 2;
  if ((direction_x != REVERSI_RULE_DIR_NEUTRAL && (examine_x < 0 || examine_x >= REVERSI_TABLE_SIZE))
      || (direction_y != REVERSI_RULE_DIR_NEUTRAL && (examine_y < 0 || examine_y >= REVERSI_TABLE_SIZE)))
    return 0;

  if (table.get(x + direction_x, y + direction_y) == counterpart) {
    do {
      examinee = table.get(examine_x, examine_y);
      if (examinee == side) {
	return count;
      } else if (examinee != counterpart) {
	return 0;
      }
      examine_x += direction_x;
      examine_y += direction_y;
      count++;
    } while (examine_x >= 0 && examine_x < REVERSI_TABLE_SIZE &&
	     examine_y >= 0 && examine_y < REVERSI_TABLE_SIZE);
  }

  return 0;
}

void Reversi::Rule::_change(unsigned int x, unsigned int y,
			    int direction_x, int direction_y,
			    unsigned int side)
{
  int cx = x,
      cy = y;

  do {
    table.set(cx, cy, side);
    cx += direction_x;
    cy += direction_y;
  } while (table.get(cx, cy) != side);
}
