/**
 * Reversi::Table implements a table of reversi and its cells' status.
 *
 * @file table.cpp
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date 2019-10-22
 */
#include "table.hpp"


/**
 * Constructor.
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date   2019-10-22
 */
Reversi::Table::Table()
{
  _init();
}


/**
 *Set a status of a cell whether a white piece is placed or a black one, or nothing is placed.
 * @param  x     horizontal coordinate to be set
 * @param  y     vertical coordinate to be set
 * @param  piece which color to be set.  This must be specified with constants: `REVERSI_PIECE_WHITE` or `REVERSI_PIECE_BLACK`.
 * @return true if successfully set.
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date   2019-10-22
 */
bool Reversi::Table::set(unsigned int x, unsigned int y, unsigned int piece)
{
  int position;

  if (is_valid_cordinates(x, y)) {
    position = _get_pointer(x, y);
    table[position] = piece;
    return true;
  } else {
    return false;
  }
}


/**
 * Get a status of a cell whether a white piece is placed or a black one, or nothing is placed.
 * @param  x     horizontal coordinate to be set
 * @param  y     vertical coordinate to be set
 * @return the current status of a specified cell.  This value must be `REVERSI_PIECE_WHITE`, `REVERSI_PIECE_BLACK` or `REVERSI_PIECE_NULL`.
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date   2019-10-22
 */
unsigned int Reversi::Table::get(unsigned int x, unsigned int y)
{
  if (is_valid_cordinates(x, y)) {
    return table[_get_pointer(x, y)];
  } else {
    return REVERSI_PIECE_NULL;
  }
}


/**
 * Validate if given cordinates are valid.
 * @param  x     horizontal coordinate to be set
 * @param  y     vertical coordinate to be set
 * @return true if given cordnates are valid.
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date   2019-10-22
 */
bool Reversi::Table::is_valid_cordinates(unsigned int x, unsigned int y) {
  return x < REVERSI_TABLE_SIZE && y < REVERSI_TABLE_SIZE;
}


// private


/**
 * Initialize the table with `REVERSI_PIECE_VOID`
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date   2019-10-22
 */
void Reversi::Table::_clear()
{
  for (int i = 0; i < REVERSI_TABLE_AREA; i++) {
    this->table[i] = REVERSI_PIECE_VOID;
  }
}


/**
 * Set initial pieces on the table.
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date   2019-10-22
 */
void Reversi::Table::_init()
{
  _clear();

  set(REVERSI_TABLE_SIZE / 2 - 1, REVERSI_TABLE_SIZE / 2 - 1, REVERSI_PIECE_WHITE);
  set(REVERSI_TABLE_SIZE / 2,     REVERSI_TABLE_SIZE / 2,     REVERSI_PIECE_WHITE);
  set(REVERSI_TABLE_SIZE / 2 - 1, REVERSI_TABLE_SIZE / 2,     REVERSI_PIECE_BLACK);
  set(REVERSI_TABLE_SIZE / 2,     REVERSI_TABLE_SIZE / 2 - 1, REVERSI_PIECE_BLACK);
}


/**
 * Calcurate the pointer digignated by x and y coordinates.
 * @param  x     horizontal coordinate to be speficied
 * @param  y     vertical coordinate to be specified
 * @return the pointer of `table` array
 * @return true if given cordnates are valid.
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date   2019-10-22
 */
unsigned int Reversi::Table::_get_pointer(unsigned int x, unsigned int y)
{
  return y * REVERSI_TABLE_SIZE + x;
}
