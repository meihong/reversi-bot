/**
 * Reversi::Rule implements fundamental rules of reversi.
 *
 * @file table.cpp
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date 2019-10-22
 */

#include "table.hpp"
#include "rule.hpp"


/**
 * Constructor.  The player moves first must be black.
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date   2019-10-22
 */
Reversi::Rule::Rule(void)
{
  turn = REVERSI_PIECE_BLACK;
}


/**
 * Sets a piece at the cell digignated by x and y coordinates.
 * The cordinates must be valid according to the rules.
 *
 * @param  x x-coordinate to be set.
 * @param  y y-coordinate to be set.
 * @return true if successfully set.
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date   2019-10-22
 */
bool Reversi::Rule::set(unsigned int x, unsigned int y)
{
  if (_count(x, y, turn, false) > 0) {
    // if made it, turn must be changed.
    turn = turn == REVERSI_PIECE_WHITE ? REVERSI_PIECE_BLACK : REVERSI_PIECE_WHITE;
    return true;
  } else {
    return false;
  }
}


/**
 * Counts how much pieces a player gets if a new piece is set to the
 * digignated cell.
 *
 * @param  x x-coordinate to be set.
 * @param  y y-coordinate to be set.
 * @return number how much pieces they get.  If the digignated cell is
 * irrelevant, it returns -1.
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date   2019-10-22
 */
int Reversi::Rule::count_potential(unsigned int x, unsigned int y, unsigned int side)
{
  return _count(x, y, side, true);
}


/**
 * Gets who can move now.
 *
 * @return player who can move.  It is specified by `REVERSI_PIECE_BLACK`
 * or `REVERSI_PIECE_WHITE`.
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date   2019-10-22
 */
unsigned int Reversi::Rule::get_current_turn(void)
{
  return turn;
}


/**
 * Gets who can move next.
 *
 * @return player who can move NEXT.  It is specified by `REVERSI_PIECE_BLACK` or `REVERSI_PIECE_WHITE`.
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date   2019-10-22
 */
unsigned int Reversi::Rule::get_counterpart(void)
{
  return turn == REVERSI_PIECE_WHITE ? REVERSI_PIECE_BLACK : REVERSI_PIECE_WHITE;
}

// private

/**
 * Changes cells which can be get and returns the number how much
 * the player actually got.  If given true to `count_only` it returns
 * only the number and nothing is changed on the table.  Please note
 * that this function never set a piece to the digignated cell.
 *
 * @param  x    x-coordinate to be set.
 * @param  y    y-coordinate to be set.
 * @param  side Which side move to the digignated cell.
 * @param  count_only If true is set, the function returns the number
 * but never change anything on the table.
 * @retur The number the player get.  If the digignated cell is
 * irrelevant, it returns -1.
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date   2019-10-22
 */
int Reversi::Rule::_count(unsigned int x, unsigned int y, unsigned int side, bool count_only)
{
  int count = 0;
  int change;

  // Check if coordinates are relevant.
  if (!table.is_valid_cordinates(x, y) || table.get(x, y) != REVERSI_PIECE_VOID) {
    return -1;
  }

  // Counts while it changes its direction from UP to DOWN.
  // Their constants are so sequential that these for loops work
  // as we expect, which means, we can never change these constants
  // as they are in order to work properly.
  for (int dx = REVERSI_RULE_DIR_UP; dx <= REVERSI_RULE_DIR_DOWN; dx++) {
    for (int dy = REVERSI_RULE_DIR_LEFT; dy <= REVERSI_RULE_DIR_RIGHT; dy++) {
      change = _count_by_dir(x, y, dx, dy, side);
      count += change;
      // If count_only is not set to true and some cells are changable,
      // we should change them here.
      if (!count_only && change > 0) {
	_change(x, y, dx, dy, side);
      }
    }
  }

  return count;
}

/**
 * Changes cells in the digignated direction by `direction_x` and
 * `direction_y`, which can be get and returns the number how much
 * the player actually got.  If given true to `count_only` it returns
 * only the number and nothing is changed on the table.  Please note
 * that this function never set a piece to the digignated cell.
 *
 * @param  x    x-coordinate to be set.
 * @param  y    y-coordinate to be set.
 * @param  x_direction horizontal direction to be changed.
 * @param  x_direction vertical direction to be changed.
 * @param  side Which side move to the digignated cell.
 * @param  count_only If true is set, the function returns the number
 * but never change anything on the table.
 * @return The number the player get.  If the digignated cell is
 * irrelevant, it returns -1.
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date   2019-10-22
 */
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
  // If the direction is toward the edge and the coordinates are located
  // right next to the edge, we do not need to check because we can
  // clearly figure out that we cannot change anything toward that
  // direction.
  if ((direction_x != REVERSI_RULE_DIR_NEUTRAL && (examine_x < 0 || examine_x >= REVERSI_TABLE_SIZE))
      || (direction_y != REVERSI_RULE_DIR_NEUTRAL && (examine_y < 0 || examine_y >= REVERSI_TABLE_SIZE)))
    return 0;

  // We need to check only when the next cell is owned by the counterpart.
  if (table.get(x + direction_x, y + direction_y) == counterpart) {
    do {
      // Checking loop.
      // The loop will end and return 0 when it
      // - reaches the edge.
      // - finds a void cell.
      // When it finds the same side, it means the coordinates are
      // relevant.  Therefore, this function returns the actual number.
      examinee = table.get(examine_x, examine_y);
      if (examinee == side) {
	return count;
      } else if (examinee != counterpart) {
	return 0;
      }
      examine_x += direction_x;
      examine_y += direction_y;
      count++;
      // tries until the edge.
    } while (examine_x >= 0 && examine_x < REVERSI_TABLE_SIZE &&
	     examine_y >= 0 && examine_y < REVERSI_TABLE_SIZE);
  }

  return 0;
}


/**
 * Actually changes cells in the digignated direction by `direction_x`
 *  and `direction_y`.  This function should be called only by
 * `_count_by_dir`.
 *
 * @param  x    x-coordinate to be set.
 * @param  y    y-coordinate to be set.
 * @param  x_direction horizontal direction to be changed.
 * @param  x_direction vertical direction to be changed.
 * @param  side Which side move to the digignated cell.
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date   2019-10-22
 */
void Reversi::Rule::_change(unsigned int x, unsigned int y,
			    int direction_x, int direction_y,
			    unsigned int side)
{
  int cx = x,
      cy = y;

  // This loop ends with a simple condition because we must already know
  // we can move towards the digignated direction by `_count_by_dir`.
  // If we called this without `_count_by_dir`, the consequence will be
  // unstable and unpredictable.  It may cause segfault.
  do {
    table.set(cx, cy, side);
    cx += direction_x;
    cy += direction_y;
  } while (table.get(cx, cy) != side);
}
