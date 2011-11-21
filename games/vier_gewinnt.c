/***
 *  Vier gewinnt
 *
 *  21.11.2011
 *
 *  License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.
 *  This is free software: you are free to change and redistribute it."
 *  There is NO WARRANTY, to the extent permitted by law.
 *
 *  Hendrik Schawe <hendrik.schawe@gmail.com>
 *
 ***/

#include "vier_gewinnt.h"

void vier_gewinnt_start()
{
    int i, j, spieler = VG_KREIS;
    char *spl_str="Kreis", spl_chr='O';

    struct vg_feld map;
    map.runde = 0;
    for(i=0;i<VG_X;i++)
        for(j=0;j<VG_Y;j++)
            map.status[i][j] = VG_LEER;

    initscr();
    raw();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    vg_draw(&map);
    while(1)
    {
        mvprintw(1,13,"%s ist am Zug!", spl_str);
        i = vg_steuern(&map, spl_chr);
        vg_setzen(&map, i, spieler);
        vg_draw(&map);

        move(1,13);
        if(vg_prufe_gewinn(&map))
            break;

        if(spieler == VG_KREIS)
        {
            spieler = VG_KREUZ;
            spl_str = "Kreuz";
            spl_chr = 'X';
        }
        else
        {
            spieler = VG_KREIS;
            spl_str = "Kreis";
            spl_chr = 'O';
        }
    }

    mvprintw(1,13,"%s gewinnt!   ", spl_str);
    getch();
    endwin();
}

void vg_draw(struct vg_feld *map)
{
    int i,j;

    move(1,0);
    for(j=0; j < VG_Y; j++)
    {
        addch(ACS_VLINE);
        for(i=0; i < VG_X; i++)
        {
            if(map->status[i][j] == VG_LEER)
                addch('.');
            else if(map->status[i][j] == VG_KREIS)
                addch('O');
            else if(map->status[i][j] == VG_KREUZ)
                addch('X');
            else
                addch(' ');
        }
        addch(ACS_VLINE);
        move(j+2,0);
    }
    addch(ACS_LLCORNER);
    for(i=0; i < VG_X; i++)
        addch(ACS_HLINE);
    addch(ACS_LRCORNER);
    mvaddch(1,0,ACS_TTEE);
    mvaddch(1,8,ACS_TTEE);
    return;
}

int vg_steuern(struct vg_feld *map, char sym)
{
    int k = '1';
    int i = 3;
    while(k != ' ')
    {
        move(0,0);
        clrtoeol();
        mvaddch(0, i+1, sym | A_BOLD);
        move(0,i+1);
        k = getch();
        switch (k)
        {
            case 'a':
            case 'A':
            case KEY_LEFT:
                if(!(i<=0))
                    i--;
                break;
            case 'd':
            case 'D':
            case KEY_RIGHT:
                if(!(i>=VG_X-1))
                    i++;
                break;
            case ' ':
            case 's':
            case 'S':
            case KEY_DOWN:
                k = ' ';
                if(map->status[i][0] != VG_LEER)
                    k='x';
                break;
        }
    }
    return i;
}

void vg_setzen(struct vg_feld *map, int x, int spieler)
{
    int y=VG_Y-1;
    while(map->status[x][y] != VG_LEER)
        y--;
    map->status[x][y] = spieler;
}

int vg_prufe_gewinn(struct vg_feld *map)
{
    int i,j, win;
    for(i=0;i<VG_X;i++)
        for(j=0;j<VG_Y;j++)
            if(map->status[i][j] != VG_LEER)
            {
                win = vg_vier(map, i, j);
                if(win)
                {
                    vg_highlight(win, i, j);
                    return 1;
                }
            }
    return 0;
}

int vg_vier(struct vg_feld *map, int x, int y)
{
    int win = 0b1111;
    int now,j;

    // Da von links -> rechts, oben -> unten gesucht wird, braucht man nur hier suchen:
    // 1. nach rechts in gleicher x-Zeile
    // 2. nach unten in gleicher y-Spalte
    // 3. nach unten rechts in Diagonaler
    // 3. nach unten links in Diagonaler
    now = map->status[x][y];
    for(j=1;j<4;j++)
    {
        // 1. Gleiche Zeile nach rechts
        if(x<=VG_X-3-1)
        {
            if(now != map->status[x+j][y])
                win = ~WINX & win;
        }
        else
            win = ~WINX & win;
        // 2. Gleiche Spalte nach unten
        if(y<=VG_Y-3-1)
        {
            if(now != map->status[x][y+j])
                win = ~WINY & win;
        }
        else
            win = ~WINY & win;
        // 3. Diagonale nach rechts unten
        if(x<=VG_X-3-1 && y<=VG_Y-3-1)
        {
            if(now != map->status[x+j][y+j])
                win = ~WINR & win;
        }
        else
            win = ~WINR & win;
        // 4. Diagonale nach unten links
        if(x>=3 && y<=VG_Y-3-1)
        {
            if(now != map->status[x-j][y+j])
                win = ~WINL & win;
        }
        else
            win = ~WINL & win;
    }
    return win;
}

void vg_highlight(int win, int x, int y)
{
    int j;
    const static int modus = A_BOLD;
    move(0,0);
    clrtoeol();

    //Nötig, da der Rand 1 dick ist
    x++;
    y++;

    // Hebe die gewinnende Kombination hervor
    if(win & WINX)
        for(j=0;j<4;j++)
            mvchgat(y, x+j, 1, modus, 0, NULL);
    if(win & WINY)
        for(j=0;j<4;j++)
            mvchgat(y+j, x, 1, modus, 0, NULL);
    if(win &WINR)
        for(j=0;j<4;j++)
            mvchgat(y+j, x+j, 1, modus, 0, NULL);
    if(win & WINL)
        for(j=0;j<4;j++)
            mvchgat(y+j, x-j, 1, modus, 0, NULL);
}
