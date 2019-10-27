/**
 * Reversi::Table implements a table of reversi and its cells' status.
 *
 * @file table.cpp
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date 2019-10-22
 */
#include <string>
#include <stdio.h>
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
 *Set a status of a cell whether a white piece is placed or a black one,
 * or nothing is placed.
 * @param  x     horizontal coordinate to be set
 * @param  y     vertical coordinate to be set
 * @param  piece which color to be set.  This must be specified with
 *  constants: `REVERSI_PIECE_WHITE` or `REVERSI_PIECE_BLACK`.
 * @return true if successfully set.
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date   2019-10-22
 */
bool Reversi::Table::set(unsigned int x, unsigned int y, unsigned int piece)
{
  int position;

  if (is_valid_coordinates(x, y)) {
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
 * @return the current status of a specified cell.  This value must be `REVERSI_PIECE_WHITE`, `REVERSI_PIECE_BLACK` or `REVERSI_PIECE_INVALID`.
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date   2019-10-22
 */
unsigned int Reversi::Table::get(unsigned int x, unsigned int y)
{
  if (is_valid_coordinates(x, y)) {
    return table[_get_pointer(x, y)];
  } else {
    return REVERSI_PIECE_INVALID;
  }
}


/**
 * Validate if given coordinates are valid.
 * @param  x     horizontal coordinate to be set
 * @param  y     vertical coordinate to be set
 * @return true if given cordnates are valid.
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date   2019-10-22
 */
bool Reversi::Table::is_valid_coordinates(unsigned int x, unsigned int y)
{
  return x < REVERSI_TABLE_SIZE && y < REVERSI_TABLE_SIZE;
}


/**
 * Tokenize the table into hexadecimal string.  Every cell is described
 * in 2 bits, therefore the length of tokenized string should be 128 bits
 * in byte sequence and 16 letters if the size of table is 8 by 8.
 * @return the tokenized table.
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date   2019-10-27
 */
std::string Reversi::Table::tokenize(void)
{
  std::string tokenized;
  unsigned char tokenizing = 0;
  char hexel[3]; // use it to convert a tokenized piece into hex string.
  unsigned int x = 0, y = 0, cell;

  // Table size must be multipes of 8 because this function needs to be.
  for (int i = 0; i < REVERSI_TABLE_AREA; i++) {
    cell = table[i];
    // Describes 1 cell with 2 bits.
    tokenizing <<= 2;
    if (cell == REVERSI_PIECE_WHITE)
      tokenizing |= 2;
    else if (cell == REVERSI_PIECE_BLACK)
      tokenizing |= 1;

    x++;
    if (x >= REVERSI_TABLE_SIZE) {
      x = 0;
      y++;
    }

    // Tokenize every 2 cells.
    if ((i & 0x01) == 0x01) {
      tokenized += (tokenizing < 0x0a ?
		    '0' + tokenizing :
		    'a' + (tokenizing - 0x0a));
      tokenizing = 0;
    }
  }

  return tokenized;
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
 * @return true if given coordnates are valid.
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date   2019-10-22
 */
unsigned int Reversi::Table::_get_pointer(unsigned int x, unsigned int y)
{
  return y * REVERSI_TABLE_SIZE + x;
}
