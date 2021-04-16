#ifndef TABLE_H
#define TABLE_H
#include "Cube.h"

class Table {
    int tableLength, tableWide, tableHeight;
    int leftPartition, rightPartition;
    int right_seat_up_pos_z, right_seat_down_pos_z;
    int left_pos_z;
    int side_panel_size_z;

   public:
    Table();
    Table(int len, int wide, int height, int ltparti, int rg_up, int rg_down, int lt_z);
    void drawTable();

   protected:
   private:
};

#endif  // TABLE_H
