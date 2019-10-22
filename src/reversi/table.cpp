#include "table.hpp"

Reversi::Table::Table()
{
  _init();
}

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

unsigned int Reversi::Table::get(unsigned int x, unsigned int y)
{
  if (is_valid_cordinates(x, y)) {
    return table[_get_pointer(x, y)];
  } else {
    return REVERSI_PIECE_NULL;
  }
}

bool Reversi::Table::is_valid_cordinates(unsigned int x, unsigned int y) {
  return x < REVERSI_TABLE_SIZE && y < REVERSI_TABLE_SIZE;
}


// private
void Reversi::Table::_clear()
{
  for (int i = 0; i < REVERSI_TABLE_AREA; i++) {
    this->table[i] = REVERSI_PIECE_VOID;
  }
}

void Reversi::Table::_init()
{
  _clear();

  set(REVERSI_TABLE_SIZE / 2 - 1, REVERSI_TABLE_SIZE / 2 - 1, REVERSI_PIECE_WHITE);
  set(REVERSI_TABLE_SIZE / 2,     REVERSI_TABLE_SIZE / 2,     REVERSI_PIECE_WHITE);
  set(REVERSI_TABLE_SIZE / 2 - 1, REVERSI_TABLE_SIZE / 2,     REVERSI_PIECE_BLACK);
  set(REVERSI_TABLE_SIZE / 2,     REVERSI_TABLE_SIZE / 2 - 1, REVERSI_PIECE_BLACK);
}

unsigned int Reversi::Table::_get_pointer(unsigned int x, unsigned int y)
{
  return y * REVERSI_TABLE_SIZE + x;
}
