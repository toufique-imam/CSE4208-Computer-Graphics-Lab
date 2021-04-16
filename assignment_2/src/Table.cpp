#include "Table.h"
#define debug(x) cerr << #x << " " << x << "\n";

Table::Table() {
    // table t(30, 20, 40, 20, 10, 2, 25);
    // t.drawTable();
    //ctor
}

Table::Table(int len, int wide, int height, int ltparti, int rg_up, int rg_down, int lt_z) {
    tableLength = len;
    tableWide = wide;
    tableHeight = height;

    leftPartition = ltparti;
    rightPartition = tableLength - ltparti;

    right_seat_up_pos_z = rg_up;
    right_seat_down_pos_z = rg_down;

    left_pos_z = lt_z;

    side_panel_size_z = tableHeight - left_pos_z;

    //    debug(tableLength);
    //    debug(tableWide);
    //    debug(tableHeight);
    //    debug(leftPartition);
    //    debug(rightPartition);
    //    debug(right_seat_down_pos_z);
    //    debug(right_seat_up_pos_z);
    //    debug(left_pos_z);
    //    debug(side_panel_size_z);
}

void Table::drawTable() {
    Cube c;
    c.setSurfaceColors(c.woodColor);
    //right stand1
    glPushMatrix();
    c.setValue(1, tableWide, tableHeight);
    c.drawCube(false);
    glPopMatrix();

    //left stand
    glPushMatrix();
    glTranslatef(tableLength, 0, 0);
    //c.setValue(1, tableWide, tableHeight);
    c.drawCube(false);
    glPopMatrix();

    //middle stand
    glPushMatrix();
    glTranslatef(rightPartition, 0, 0);
    c.setSurfaceColors(c.offwhite2);
    //c.setValue(1, tableWide, tableHeight);
    c.drawCube(false);
    glPopMatrix();

    //table surface
    glPushMatrix();
    glTranslatef(0, -.5, tableHeight - .1);
    c.setSurfaceColors(c.woodColor);
    c.setValue(tableLength + 1, tableWide + 1, 1);
    c.drawCube(false);
    glPopMatrix();

    //table-partition-right-up
    glPushMatrix();
    glTranslatef(0, 0, right_seat_up_pos_z);
    c.setValue(rightPartition, tableWide, 1);
    c.drawCube(false);
    glPopMatrix();

    //sub-seat-right-down
    glPushMatrix();
    glTranslatef(0, 0, right_seat_down_pos_z);
    c.setValue(rightPartition, tableWide, 1);
    c.drawCube(false);
    glPopMatrix();

    //sub-seat-left-up
    glPushMatrix();
    glTranslatef(rightPartition, 0, left_pos_z);
    c.setValue(leftPartition, tableWide, 1);
    c.drawCube(false);
    glPopMatrix();

    // piser side panel
    glPushMatrix();
    glTranslatef(rightPartition, 0, left_pos_z);
    c.setValue(leftPartition, 1, side_panel_size_z);
    c.setSurfaceColors(c.offwhite1);
    c.drawCube(false);
    glPopMatrix();
}
