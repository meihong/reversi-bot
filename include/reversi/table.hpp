#ifndef REVERSI_TABLE_HPP
#define REVERSI_TABLE_HPP

#define REVERSI_PIECE_WHITE 3
#define REVERSI_PIECE_BLACK 2
#define REVERSI_PIECE_VOID  1
#define REVERSI_PIECE_NULL  0

#define REVERSI_TABLE_SIZE  8
#define REVERSI_TABLE_AREA  REVERSI_TABLE_SIZE * REVERSI_TABLE_SIZE


namespace Reversi
{
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
