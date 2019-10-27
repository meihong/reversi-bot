/**
 * @file table.hpp
 * @author Kenta ONISHI (kenta@0024s.com)
 * @date 2019-10-22
 */

#ifndef REVERSI_TABLE_HPP
#define REVERSI_TABLE_HPP

/// indicates the piece is white.
#define REVERSI_PIECE_WHITE   3
/// indicates the piece is black.
#define REVERSI_PIECE_BLACK   2
/// indicates the piece is void.
#define REVERSI_PIECE_VOID    1
/// indicates the piece is invalid.
#define REVERSI_PIECE_INVALID 0

/// Maximum size of a table.
#define REVERSI_TABLE_SIZE  8
/// Square measure of a table.  A table must be a square.
#define REVERSI_TABLE_AREA  REVERSI_TABLE_SIZE * REVERSI_TABLE_SIZE


namespace Reversi
{
  /**
   * Reversi::Table implements a table of reversi and its cells' status.
   *
   * @author Kenta ONISHI (kenta@0024s.com)
   * @date 2019-10-22
   */
  class Table
  {
    unsigned int table[64];

  public:
    Table();
    bool set(unsigned int, unsigned int, unsigned int);
    unsigned int get(unsigned int, unsigned int);
    bool is_valid_cordinates(unsigned int, unsigned int);

  private:
    void _init();
    void _clear();
    unsigned int _get_pointer(unsigned int, unsigned int);
  };
}
#endif // REVERSI_TABLE_HPP
