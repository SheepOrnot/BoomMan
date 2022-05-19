#include"setting.h"

QLabel *Build[16][16];
int Map[2][16][16] = {{
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//

                          {0,    0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
                          {0,    0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},
                          {0,    1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
                          {0,    0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
                          {0,    1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                          {0,    0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
                          {0,    0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0},
                          {0,    1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0},
                          {0,    0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0},
                          {0,    1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0},
                          {0,    1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
                          {0,    1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0},
                          {0,    1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
                          {0,    1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0},
                          {0,    0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0}
                          //
                      },
                      {
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//

                          {0,    0, 3, 0, 0, 0, 0, 1, 0, 2, 0, 2, 0, 0, 0, 0},
                          {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0,    4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                          {0,    0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0,    0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0, 1, 0},
                          {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0,    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0},
                          {0,    0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                          {0,    0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0}
                                                //
                                            }
                     };
