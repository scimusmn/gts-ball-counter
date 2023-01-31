#pragma once

/*
 * physical layout:
 *
 *  [d] GND    1 || 2   
 *             3 || 4    D2 [a] 
 *             5 || 6    C2 [a]
 *  [d] 5V     7 || 8    D1 [a]
 *             9 || 10   C1 [a]
 *            11 || 12   D0 [a]
 *  [d] B9    13 || 14   C0 [a]
 *  [d] B10   15 || 16   B2 [a]
 *  [d] C9    17 || 18   B1 [a]
 * [c] B6     19 || 20   B0 [a]
 * [c] B7     21 || 22    D10 [d]
 * [c] B8     23 || 24    C10 [d]
 * [c] C6     25 || 26    D9  [d]
 * [c] D6     27 || 28   D5 [b]
 * [c] C7     29 || 30   C5 [b]
 * [c] D7     31 || 32   D4 [b]
 * [c] C8     33 || 34   C4 [b]
 * [c] D8     35 || 36   D3 [b]
 *  [b] B3    37 || 38   C3 [b]
 *  [b] B4    39 || 40   B5 [b]
 */

#define DATA0 20
#define CLOCK0 13

#define DATA1 22
#define CLOCK1 21

#define DATA2 24
#define CLOCK2 23

#define DATA3 2
#define CLOCK3 1

#define DATA4 4
#define CLOCK4 3

#define DATA5 6
#define CLOCK5 5

#define DATA6 A15
#define CLOCK6 A13

#define DATA7 18
#define CLOCK7 19

#define DATA8 16
#define CLOCK8 17

#define DATA9 7
#define CLOCK9 A10

#define DATA10 9
#define CLOCK10 8

#define BEAM0 10
#define BEAM1 11
#define BEAM2 12
#define BEAM3 15
#define BEAM4 14
#define BEAM5 0
#define BEAM6 A11
#define BEAM7 A12
#define BEAM8 A13
#define BEAM9 A8
#define BEAM10 A9
