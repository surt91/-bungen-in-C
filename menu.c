#include "menu.h"

int menu(int argc, char **argv)
{
    int aufgnr=0, kapitel=0;
    srand( (unsigned) time(NULL) ) ;

    if(argc != 3)
    {
		if(argc == 2)
		{
			help(atoi(argv[1]));
		}
		else
		{
			version();
			help(0);
			todo();
		}
	}
    else
    {
        kapitel=atoi(argv[1]);
        aufgnr =atoi(argv[2]);
    }
    switch (kapitel)
    {
        case MAT:
            switch (aufgnr)
            {
				case 1:
                    aufg_MAT_1();
                    break;
                case 2:
                    aufg_MAT_2();
                    break;
                case 3:
                    aufg_MAT_3();
                    break;
                case 4:
                    aufg_MAT_4();
                    break;
                case 5:
                    aufg_MAT_5();
                    break;
                case 6:
                    aufg_MAT_6();
                    break;
                case 7:
                    aufg_MAT_7();
                    break;
                case 8:
                    aufg_MAT_8();
                    break;
                case 9:
                    aufg_MAT_9();
                    break;
                case 10:
                    aufg_MAT_10();
                    break;
                case 11:
                    aufg_MAT_11();
                    break;
                case 12:
                    aufg_MAT_12();
                    break;
                case 13:
                    aufg_MAT_13();
                    break;
                case 14:
                    aufg_MAT_14();
                    break;
                //~ case 15:
                    //~ aufg_MAT_15();
                    //~ break;
                case 16:
                    aufg_MAT_16();
                    break;
                case 17:
                    aufg_MAT_17();
                    break;
			}
			break;
        case GAME:
            switch (aufgnr)
            {
                case 1:
                    aufg_GAME_1();
                    break;
                case 2:
                    aufg_GAME_2();
                    break;
                case 3:
                    aufg_GAME_3();
                    break;
                case 4:
                    aufg_GAME_4();
                    break;
                case 5:
                    aufg_GAME_5();
                    break;
                case 6:
                    aufg_GAME_6();
                    break;
            }
            break;
        case PRIM:
            switch (aufgnr)
            {
                case 1:
                    aufg_PRIM_1();
                    break;
				case 2:
					aufg_PRIM_2();
					break;
                case 3:
                    aufg_PRIM_3();
                    break;
                case 4:
                    aufg_PRIM_4();
                    break;
                case 5:
                    aufg_PRIM_5();
                    break;
                case 6:
                    aufg_PRIM_6();
                    break;
            }
            break;
        //~ case POLY:
            //~ switch (aufgnr)
            //~ {
                //~ case 1:
                    //~ aufg_POLY_1();
                    //~ break;
				//~ case 2:
					//~ aufg_POLY_2();
					//~ break;
                //~ case 3:
                    //~ aufg_POLY_3();
                    //~ break;
                //~ case 4:
                    //~ aufg_POLY_4();
                    //~ break;
            //~ }
            //~ break;
        case TRIV:
            switch (aufgnr)
            {
                case 1:
                    aufg_TRIV_1();
                    break;
				case 2:
					aufg_TRIV_2();
					break;
                case 3:
                    aufg_TRIV_3();
                    break;
                case 4:
                    aufg_TRIV_4();
                    break;
                case 5:
                    aufg_TRIV_5();
                    break;
                case 6:
                    aufg_TRIV_6();
                    break;
                case 7:
                    aufg_TRIV_7();
                    break;
                case 8:
                    aufg_TRIV_8();
                    break;
                case 9:
                    aufg_TRIV_9();
                    break;
                case 10:
                    aufg_TRIV_10();
                    break;
                case 11:
                    aufg_TRIV_11();
                    break;
//                case 12:
//                    aufg_TRIV_12();
//                    break;
                case 13:
                    aufg_TRIV_13();
                    break;
                case 15:
                    aufg_TRIV_15();
                    break;
            }
            break;
    }
    return 0;
}

